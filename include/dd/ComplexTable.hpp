/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DD_PACKAGE_COMPLEXTABLE_HPP
#define DD_PACKAGE_COMPLEXTABLE_HPP

#include "Definitions.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <forward_list>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

namespace dd {
    template<std::size_t NBUCKET = 32768, std::size_t INITIAL_ALLOCATION_SIZE = 2048, std::size_t GROWTH_FACTOR = 2, std::size_t INITIAL_GC_LIMIT = 100000, std::size_t GC_INCREMENT = 0>
    class ComplexTable {
    public:
        struct Entry {
            fp       value{};
            RefCount refCount{};

            ///
            /// The sign of number is encoded in the least significant bit of its entry pointer
            /// If not handled properly, this causes misaligned access
            /// These routines allow to obtain safe pointers
            ///
            [[nodiscard]] static inline Entry* getAlignedPointer(const Entry* e) {
                return reinterpret_cast<Entry*>(reinterpret_cast<std::uintptr_t>(e) & (~1ULL));
            }
            [[nodiscard]] static inline Entry* getNegativePointer(const Entry* e) {
                return reinterpret_cast<Entry*>(reinterpret_cast<std::uintptr_t>(e) | 1ULL);
            }
            [[nodiscard]] static inline Entry* flipPointerSign(const Entry* e) {
                return reinterpret_cast<Entry*>(reinterpret_cast<std::uintptr_t>(e) ^ 1ULL);
            }
            [[nodiscard]] static inline bool isNegativePointer(const Entry* e) {
                return reinterpret_cast<std::uintptr_t>(e) & 1ULL;
            }

            [[nodiscard]] static inline fp val(const Entry* e) {
                if (isNegativePointer(e)) {
                    return -getAlignedPointer(e)->value;
                }
                return e->value;
            }

            [[nodiscard]] static inline RefCount ref(const Entry* e) {
                if (isNegativePointer(e)) {
                    return -getAlignedPointer(e)->refCount;
                }
                return e->refCount;
            }

            [[nodiscard]] static inline bool approximatelyEquals(const Entry* left, const Entry* right) {
                return std::abs(val(left) - val(right)) < TOLERANCE;
            }

            [[nodiscard]] static inline bool approximatelyZero(const Entry* e) {
                return e == &zero || std::abs(val(e)) < TOLERANCE;
            }

            [[nodiscard]] static inline bool approximatelyOne(const Entry* e) {
                return e == &one || std::abs(val(e) - 1) < TOLERANCE;
            }

            static void writeBinary(const Entry* e, std::ostream& os) {
                auto temp = val(e);
                os.write(reinterpret_cast<const char*>(&temp), sizeof(decltype(temp)));
            }
        };

        static inline Entry zero{0., 1};
        static inline Entry one{1., 1};

        ComplexTable():
            chunkID(0), allocationSize(INITIAL_ALLOCATION_SIZE), gcLimit(INITIAL_GC_LIMIT) {
            // allocate first chunk of numbers
            chunks.emplace_back(allocationSize);
            allocations += allocationSize;
            allocationSize *= GROWTH_FACTOR;
            chunkIt    = chunks[0].begin();
            chunkEndIt = chunks[0].end();

            // emplace static zero and one in the table
            table[0].push_front(&zero);
            table[NBUCKET - 1].push_front(&one);
            count     = 2;
            peakCount = 2;

            // add 1/2 and 1/sqrt(2) to the complex table and increase their ref count (so that they are not collected)
            lookup(0.5L)->refCount++;
            lookup(SQRT2_2)->refCount++;
        }

        ~ComplexTable() = default;

        static fp tolerance() {
            return TOLERANCE;
        }
        static void setTolerance(fp tol) {
            TOLERANCE = tol;
        }

        static constexpr std::size_t MASK = NBUCKET - 1;

        // linear (clipped) hash function
        static std::size_t hash(const fp val) {
            assert(val >= 0);
            auto key = static_cast<std::size_t>(val * MASK);
            return std::min(key, MASK);
        }

        // access functions
        [[nodiscard]] std::size_t getCount() const { return count; }
        [[nodiscard]] std::size_t getPeakCount() const { return peakCount; }
        [[nodiscard]] std::size_t getAllocations() const { return allocations; }
        [[nodiscard]] std::size_t getGrowthFactor() const { return GROWTH_FACTOR; }
        [[nodiscard]] const auto& getTable() const { return table; }

        Entry* lookup(const fp& val) {
            assert(!std::isnan(val));

            // special treatment of zero and one (these are not counted as lookups)
            if (std::abs(val) < TOLERANCE)
                return &zero;

            if (std::abs(val - 1.) < TOLERANCE)
                return &one;

            lookups++;

            // search in intended bucket
            const auto  key    = hash(val);
            const auto& bucket = table[key];
            auto        it     = find(bucket, val);
            if (it != bucket.end()) {
                return (*it);
            }

            // search in (potentially) lower bucket
            if (val - TOLERANCE >= 0) {
                const auto lowerKey = hash(val - TOLERANCE);
                if (lowerKey != key) {
                    const auto& lowerBucket = table[lowerKey];
                    it                      = find(lowerBucket, val);
                    if (it != lowerBucket.end()) {
                        return (*it);
                    }
                }
            }

            // search in (potentially) higher bucket
            const auto upperKey = hash(val - TOLERANCE);
            if (upperKey != key) {
                const auto& upperBucket = table[upperKey];
                it                      = find(upperBucket, val);
                if (it != upperBucket.end()) {
                    return (*it);
                }
            }

            // value was not found in the table -> get a new entry and add it to the central bucket
            table[key].emplace_front(getEntry());
            table[key].front()->value = val;
            count++;
            peakCount = std::max(peakCount, count);
            return table[key].front();
        }

        [[nodiscard]] Entry* getEntry() {
            // an entry is available on the stack
            if (!available.empty()) {
                auto& entry = available.top();
                available.pop();
                // returned entries could have a ref count != 0
                entry->refCount = 0;
                return entry;
            }

            // new chunk has to be allocated
            if (chunkIt == chunkEndIt) {
                chunks.emplace_back(allocationSize);
                allocations += allocationSize;
                allocationSize *= GROWTH_FACTOR;
                chunkID++;
                chunkIt    = chunks[chunkID].begin();
                chunkEndIt = chunks[chunkID].end();
            }

            auto entry = &(*chunkIt);
            ++chunkIt;
            return entry;
        }

        void returnEntry(Entry* entry) {
            available.emplace(entry);
        }

        // increment reference count for corresponding entry
        static void incRef(Entry* entry) {
            if (entry == nullptr)
                return;

            // get valid pointer
            auto entryPtr = Entry::getAlignedPointer(entry);

            // `zero` and `one` are static and never altered
            if (entryPtr != &one && entryPtr != &zero) {
                if (entryPtr->refCount == std::numeric_limits<RefCount>::max()) {
                    std::clog << "[WARN] MAXREFCNT reached for " << entryPtr->value << ". Number will never be collected." << std::endl;
                    return;
                }

                // increase reference count
                entryPtr->refCount++;
            }
        }

        // decrement reference count for corresponding entry
        static void decRef(Entry* entry) {
            if (entry == nullptr)
                return;

            // get valid pointer
            auto entryPtr = Entry::getAlignedPointer(entry);

            // `zero` and `one` are static and never altered
            if (entryPtr != &one && entryPtr != &zero) {
                assert(entryPtr->refCount > 0);

                // decrease reference count
                entryPtr->refCount--;
            }
        }

        std::size_t garbageCollect(bool force = false) {
            gcCalls++;
            if (!force && count < gcLimit)
                return 0;

            gcRuns++;
            std::size_t collected = 0;
            std::size_t remaining = 0;
            for (auto& bucket: table) {
                auto it     = bucket.begin();
                auto lastit = bucket.before_begin();
                while (it != bucket.end()) {
                    if ((*it)->refCount == 0) {
                        auto entry = (*it);
                        it         = bucket.erase_after(lastit); // erases the element at `it`
                        returnEntry(entry);
                        collected++;
                    } else {
                        ++it;
                        ++lastit;
                        remaining++;
                    }
                }
            }
            gcLimit += GC_INCREMENT;
            count = remaining;
            return collected;
        }

        void clear() {
            // clear table buckets
            for (auto& bucket: table) {
                bucket.clear();
            }

            // clear available stack
            while (!available.empty())
                available.pop();

            // release memory of all but the first chunk TODO: it could be desirable to keep the memory
            while (chunkID > 0) {
                chunks.pop_back();
                chunkID--;
            }
            // restore initial chunk setting
            chunkIt        = chunks[0].begin();
            chunkEndIt     = chunks[0].end();
            allocationSize = INITIAL_ALLOCATION_SIZE * GROWTH_FACTOR;
            allocations    = INITIAL_ALLOCATION_SIZE;

            count     = 0;
            peakCount = 0;

            collisions = 0;
            hits       = 0;
            lookups    = 0;

            gcCalls = 0;
            gcRuns  = 0;
            gcLimit = INITIAL_GC_LIMIT;
        };

        void print() {
            for (std::size_t key = 0; key < table.size(); ++key) {
                auto& bucket = table[key];
                if (!bucket.empty())
                    std::cout << key << ": ";

                for (const auto& node: bucket)
                    std::cout << "\t\t" << reinterpret_cast<std::uintptr_t>(node) << " " << node->refCount << "\t";

                if (!bucket.empty())
                    std::cout << "\n";
            }
        }

        [[nodiscard]] fp hitRatio() const { return static_cast<fp>(hits) / lookups; }
        [[nodiscard]] fp colRatio() const { return static_cast<fp>(collisions) / lookups; }

        std::ostream& printStatistics(std::ostream& os = std::cout) {
            os << "hits: " << hits << ", collisions: " << collisions << ", looks: " << lookups << ", hitRatio: " << hitRatio() << ", colRatio: " << colRatio() << ", gc calls: " << gcCalls << ", gc runs: " << gcRuns << "\n";
            return os;
        }

    private:
        using Bucket = std::forward_list<Entry*>;
        /// gcc is having serious troubles compiling this using std::array (compilation times >15min).
        /// std::vector shouldn't be any less efficient in our application scenario
        /// TODO: revisit this in the future
        using Table = std::vector<Bucket>;

        Table table{NBUCKET};

        // numerical tolerance to be used for floating point values
        static inline fp TOLERANCE = 1e-13;

        std::stack<Entry*>                    available{};
        std::vector<std::vector<Entry>>       chunks{};
        std::size_t                           chunkID;
        typename std::vector<Entry>::iterator chunkIt;
        typename std::vector<Entry>::iterator chunkEndIt;
        std::size_t                           allocationSize;

        std::size_t allocations = 0;
        std::size_t count       = 0;
        std::size_t peakCount   = 0;

        // table lookup statistics
        std::size_t collisions = 0;
        std::size_t hits       = 0;
        std::size_t lookups    = 0;

        // garbage collection
        std::size_t gcCalls = 0;
        std::size_t gcRuns  = 0;
        std::size_t gcLimit = 250000;

        inline typename Bucket::const_iterator find(const Bucket& bucket, const fp& val) {
            auto it = bucket.cbegin();
            while (it != bucket.cend()) {
                if (std::abs((*it)->value - val) < TOLERANCE) {
                    ++hits;
                    return it;
                }
                ++collisions;
                ++it;
            }
            return it;
        }
    };
} // namespace dd
#endif //DD_PACKAGE_COMPLEXTABLE_HPP
