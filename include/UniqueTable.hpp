/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_UNIQUETABLE_HPP
#define DDpackage_UNIQUETABLE_HPP

#include "Definitions.hpp"

#include <array>
#include <forward_list>
#include <functional>
#include <limits>
#include <numeric>
#include <stack>
#include <vector>

namespace dd {

    template<class Node, std::size_t NBUCKET = 32768, std::size_t INITIAL_ALLOCATION_SIZE = 2000>
    class UniqueTable {
    public:
        explicit UniqueTable(std::size_t nvars, std::size_t gcLimit = 250000, std::size_t gcIncrement = 0, float growthFactor = 1.5):
            chunkID(0), growthFactor(growthFactor), nvars(nvars), gcInitialLimit(gcLimit), gcLimit(gcLimit), gcIncrement(gcIncrement) {
            // allocate first chunk of nodes
            allocationSize = INITIAL_ALLOCATION_SIZE;
            chunks.emplace_back(allocationSize);
            allocations += allocationSize;
            allocationSize *= growthFactor;
            chunkIt    = chunks[0].begin();
            chunkEndIt = chunks[0].end();
        }

        ~UniqueTable() = default;

        static constexpr size_t MASK = NBUCKET - 1;

        void resize(std::size_t nq) {
            nvars = nq;
            tables.resize(nq);
            // TODO: if the new size is smaller than the old one we might have to release the unique table entries for the superfluous variables
            active.resize(nq);
            activeNodeCount = std::accumulate(active.begin(), active.end(), 0UL);
        }

        static std::size_t hash(const Node* p) {
            std::uintptr_t key = 0;
            for (std::size_t i = 0; i < p->e.size(); ++i) {
                key += ((reinterpret_cast<std::uintptr_t>(p->e[i].p) >> i) +
                        (reinterpret_cast<std::uintptr_t>(p->e[i].w.r) >> i) +
                        (reinterpret_cast<std::uintptr_t>(p->e[i].w.i) >> (i + 1))) &
                       MASK;
                key &= MASK;
            }
            return key;
        }

        // access functions
        [[nodiscard]] auto        getNodeCount() const { return nodeCount; }
        [[nodiscard]] auto        getPeakNodeCount() const { return peakNodeCount; }
        [[nodiscard]] auto        getAllocations() const { return allocations; }
        [[nodiscard]] auto        getGrowthFactor() const { return growthFactor; }
        [[nodiscard]] const auto& getTables() const { return tables; }

        // lookup a node in the unique table for the appropriate variable; insert it, if it has not been found
        // NOTE: reference counting is to be adjusted by function invoking the table lookup and only normalized nodes shall be stored.
        Edge<Node> lookup(const Edge<Node>& e, bool keepNode = false) {
            // there are unique terminal nodes
            if (e.isTerminal())
                return e;

            lookups++;
            auto key = hash(e.p);
            auto v   = e.p->v;

            // successors of a node shall either have successive variable numbers or be terminals
            for ([[maybe_unused]] const auto& edge: e.p->e)
                assert(edge.p->v == v - 1 || edge.isTerminal());

            auto& bucket = tables[v][key];
            auto  it     = bucket.begin();
            while (it != bucket.end()) {
                if (e.p->e == (*it)->e) {
                    // Match found
                    if (e.p != (*it) && !keepNode) {
                        // put node pointed to by e.p on available chain
                        returnNode(e.p);
                    }
                    hits++;

                    // variables should stay the same
                    assert((*it)->v == e.p->v);

                    // successors of a node shall either have successive variable numbers or be terminals
                    for ([[maybe_unused]] const auto& edge: e.p->e)
                        assert(edge.p->v == v - 1 || edge.isTerminal());

                    return {(*it), e.w};
                }
                collisions++;
                ++it;
            }

            // node was not found -> add it to front of unique table bucket
            bucket.push_front(e.p);
            nodeCount++;
            peakNodeCount = std::max(peakNodeCount, nodeCount);

            return e;
        }

        [[nodiscard]] Node* getNode() {
            // a node is available on the stack
            if (!available.empty()) {
                auto p = available.top();
                available.pop();
                // returned nodes could have a ref count != 0
                p->ref = 0;
                return p;
            }

            // new chunk has to be allocated
            if (chunkIt == chunkEndIt) {
                chunks.emplace_back(allocationSize);
                allocations += allocationSize;
                allocationSize *= growthFactor;
                chunkID++;
                chunkIt    = chunks[chunkID].begin();
                chunkEndIt = chunks[chunkID].end();
            }

            auto p = &(*chunkIt);
            ++chunkIt;
            return p;
        }

        void returnNode(Node* p) {
            available.push(p);
        }

        // increment reference counter for node e points to
        // and recursively increment reference counter for
        // each child if this is the first reference
        void incRef(const Edge<Node>& e) {
            dd::ComplexNumbers::incRef(e.w);
            if (e.isTerminal())
                return;

            if (e.p->ref == std::numeric_limits<decltype(e.p->ref)>::max()) {
                std::clog << "[WARN] MAXREFCNT reached for p=" << reinterpret_cast<uintptr_t>(e.p) << ". Node will never be collected." << std::endl;
                return;
            }

            e.p->ref++;

            if (e.p->ref == 1) {
                for (const auto& edge: e.p->e) {
                    if (edge.p != nullptr) {
                        incRef(edge);
                    }
                }
                active[e.p->v]++;
                activeNodeCount++;
                maxActive = std::max(maxActive, activeNodeCount);
            }
        }

        // decrement reference counter for node e points to
        // and recursively decrement reference counter for
        // each child if this is the last reference
        void decRef(const Edge<Node>& e) {
            dd::ComplexNumbers::decRef(e.w);
            if (e.isTerminal()) return;
            if (e.p->ref == std::numeric_limits<decltype(e.p->ref)>::max()) return;

            if (e.p->ref == 0) {
                throw std::runtime_error("In decref: ref==0 before decref\n");
            }

            e.p->ref--;

            if (e.p->ref == 0) {
                for (const auto& edge: e.p->e) {
                    if (edge.p != nullptr) {
                        decRef(edge);
                    }
                }
                active[e.p->v]--;
                activeNodeCount--;
            }
        }

        std::size_t garbageCollect(bool force = false) {
            gcCalls++;
            if (!force && nodeCount < gcLimit)
                return 0;

            gcRuns++;
            std::size_t collected = 0;
            std::size_t remaining = 0;
            for (auto& table: tables) {
                for (auto& bucket: table) {
                    auto it     = bucket.begin();
                    auto lastit = bucket.before_begin();
                    while (it != bucket.end()) {
                        if ((*it)->ref == 0) {
                            assert(!Node::isTerminal(*it));

                            auto node = (*it);
                            bucket.erase_after(lastit); // erases the element at `it`
                            returnNode(node);
                            it = ++lastit;
                            collected++;
                        } else {
                            ++it;
                            ++lastit;
                            remaining++;
                        }
                    }
                }
            }
            gcLimit += gcIncrement;
            nodeCount = remaining;
            return collected;
        }

        void clear() {
            // clear unique table buckets
            for (auto& table: tables) {
                for (auto& bucket: table) {
                    bucket.clear();
                }
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
            allocationSize = INITIAL_ALLOCATION_SIZE * growthFactor;
            allocations    = INITIAL_ALLOCATION_SIZE;

            nodeCount     = 0;
            peakNodeCount = 0;

            collisions = 0;
            hits       = 0;
            lookups    = 0;

            std::fill(active.begin(), active.end(), 0);
            activeNodeCount = 0;
            maxActive       = 0;

            gcCalls = 0;
            gcRuns  = 0;
            gcLimit = gcInitialLimit;
        };

        void print() {
            Qubit q = nvars - 1;
            for (auto it = tables.rbegin(); it != tables.rend(); ++it) {
                auto& table = *it;
                std::cout << "\t" << static_cast<std::size_t>(q) << ":" << std::endl;
                for (size_t key = 0; key < table.size(); ++key) {
                    auto& bucket = table[key];
                    if (!bucket.empty())
                        std::cout << key << ": ";

                    for (const auto& node: bucket)
                        std::cout << "\t\t" << reinterpret_cast<uintptr_t>(node) << " " << node->ref << "\t";

                    if (!bucket.empty())
                        std::cout << std::endl;
                }
                --q;
            }
        }

        void printActive() {
            std::cout << "#printActive: " << activeNodeCount << ", ";
            for (const auto& a: active)
                std::cout << a << " ";
            std::cout << std::endl;
        }

        [[nodiscard]] fp hitRatio() const { return static_cast<fp>(hits) / lookups; }
        [[nodiscard]] fp colRatio() const { return static_cast<fp>(collisions) / lookups; }

        [[nodiscard]] auto getActiveNodeCount() const {
            return activeNodeCount;
        }
        [[nodiscard]] auto getActiveNodeCount(Qubit var) { return active.at(var); }

        std::ostream& printStatistics(std::ostream& os = std::cout) {
            os << "hits: " << hits << ", collisions: " << collisions << ", looks: " << lookups << ", hitRatio: " << hitRatio() << ", colRatio: " << colRatio() << ", gc calls: " << gcCalls << ", gc runs: " << gcRuns << std::endl;
            return os;
        }

    private:
        std::stack<Node*>                    available{};
        std::vector<std::vector<Node>>       chunks{};
        std::size_t                          chunkID;
        typename std::vector<Node>::iterator chunkIt;
        typename std::vector<Node>::iterator chunkEndIt;
        std::size_t                          allocationSize;
        float                                growthFactor;

        using NodeBucket = std::forward_list<Node*>;
        using Table      = std::array<NodeBucket, NBUCKET>;

        // unique tables (one per input variable)
        std::size_t        nvars = 0;
        std::vector<Table> tables{nvars};

        std::size_t allocations   = 0;
        std::size_t nodeCount     = 0;
        std::size_t peakNodeCount = 0;

        // unique table lookup statistics
        std::size_t collisions = 0;
        std::size_t hits       = 0;
        std::size_t lookups    = 0;

        // (max) active nodes
        // number of active vector nodes for each variable
        std::vector<std::size_t> active{nvars};
        std::size_t              activeNodeCount = 0;
        std::size_t              maxActive       = 0;

        // garbage collection
        std::size_t gcCalls        = 0;
        std::size_t gcRuns         = 0;
        std::size_t gcInitialLimit = 250000;
        std::size_t gcLimit        = 250000;
        std::size_t gcIncrement    = 0;
    };

} // namespace dd

#endif //DDpackage_UNIQUETABLE_HPP
