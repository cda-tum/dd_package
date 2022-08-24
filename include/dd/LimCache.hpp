/*
* This file is part of the MQT DD Package which is released under the MIT license.
* See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
*/

#ifndef DDPACKAGE_LIMCACHE_HPP
#define DDPACKAGE_LIMCACHE_HPP

#include "LimTable.hpp"

#include <cassert>
#include <cstddef>
#include <vector>

namespace dd {
    template<std::size_t INITIAL_ALLOCATION_SIZE = 2048, std::size_t GROWTH_FACTOR = 2>
    class LimCache {
        using Entry = LimTable<>::Entry;

    public:
        LimCache():
            chunkID(0), allocationSize(INITIAL_ALLOCATION_SIZE) {
            // allocate first chunk of cache entries
            chunks.emplace_back(allocationSize);
            allocations += allocationSize;
            allocationSize *= GROWTH_FACTOR;
            chunkIt    = chunks[0].begin();
            chunkEndIt = chunks[0].end();
        }

        ~LimCache() = default;

        // access functions
        [[nodiscard]] std::size_t getCount() const { return count; }
        [[nodiscard]] std::size_t getPeakCount() const { return peakCount; }
        [[nodiscard]] std::size_t getAllocations() const { return allocations; }
        [[nodiscard]] std::size_t getGrowthFactor() const { return GROWTH_FACTOR; }

        [[nodiscard]] LimEntry<>* getCachedLim() {
            // an entry is available on the stack
            if (available != nullptr) {
                assert(available->next != nullptr);
                auto entry = available;
                available  = entry->next;
                count++;
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

            ++chunkIt;

            count += 1;
            return &(*chunkIt);
        }

        [[nodiscard]] LimEntry<>* getTemporaryLim() {
            // an entry is available on the stack
            if (available != nullptr) {
                return available;
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
            return &(*chunkIt);
        }

        void returnToCache(LimEntry<>* c) {
            assert(count >= 1);
            c->next    = available;
            available = c;
            count -= 1;
        }

        void clear() {
            // clear available stack
            available = nullptr;

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
        };

    private:
        Entry*                                available{};
        std::vector<std::vector<Entry>>       chunks{};
        std::size_t                           chunkID;
        typename std::vector<Entry>::iterator chunkIt;
        typename std::vector<Entry>::iterator chunkEndIt;
        std::size_t                           allocationSize;

        std::size_t allocations = 0;
        std::size_t count       = 0;
        std::size_t peakCount   = 0;
    };
} // namespace dd

#endif //DDPACKAGE_LIMCACHE_HPP
