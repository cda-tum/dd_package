/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_COMPUTETABLE_HPP
#define DDpackage_COMPUTETABLE_HPP

#include "Definitions.hpp"

#include <array>
#include <functional>
#include <iostream>

namespace dd {

    template<class A, class B, class R, std::size_t NBUCKET = 16384>
    class ComputeTable {
    public:
        ComputeTable() = default;

        struct Entry {
            A a;
            B b;
            R r;
        };

        static constexpr std::size_t MASK = NBUCKET - 1; // must be CTSLOTS-1

        static std::size_t hash(const A& a, const B& b) {
            const auto h1   = std::hash<A>{}(a);
            const auto h2   = std::hash<B>{}(b);
            const auto hash = h1 ^ (h2 << 1);
            return hash & MASK;
        }

        // access functions
        [[nodiscard]] const auto& getTable() const { return table; }

        void insert(const A& a, const B& b, const R& r) {
            const auto key = hash(a, b);
            table[key]     = {.a = a, .b = b, .r = r};
            ++count;
        }

        R lookup(const A& a, const B& b) {
            R r{};
            lookups++;
            const auto key   = hash(a, b);
            auto&      entry = table[key];
            if (entry.r.p == nullptr) return r;
            if (entry.a != a) return r;
            if (entry.b != b) return r;

            hits++;
            return entry.r;
        }

        void clear() {
            if (count > 0) {
                for (auto& entry: table)
                    entry.r.p = nullptr;
                count = 0;
            }
            hits    = 0;
            lookups = 0;
        }

        [[nodiscard]] fp hitRatio() const { return static_cast<fp>(hits) / lookups; }
        std::ostream&    printStatistics(std::ostream& os = std::cout) {
            os << "hits: " << hits << ", looks: " << lookups << ", ratio: " << hitRatio() << std::endl;
            return os;
        }

    private:
        std::array<Entry, NBUCKET> table{};
        // compute table lookup statistics
        std::size_t hits    = 0;
        std::size_t lookups = 0;
        std::size_t count   = 0;
    };
} // namespace dd

#endif //DDpackage_COMPUTETABLE_HPP
