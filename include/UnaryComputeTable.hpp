/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_UNARYCOMPUTETABLE_HPP
#define DDpackage_UNARYCOMPUTETABLE_HPP

#include "Definitions.hpp"

#include <array>
#include <iostream>
#include <tuple>

namespace dd {

    template<class A, class R, std::size_t NBUCKET = 32768>
    class UnaryComputeTable {
    public:
        UnaryComputeTable() = default;

        struct Entry {
            A a;
            R r;
        };

        static constexpr size_t MASK = NBUCKET - 1;

        // access functions
        [[nodiscard]] const auto& getTable() const { return table; }

        static std::size_t hash(const A& a) {
            const auto node_pointer = reinterpret_cast<std::uintptr_t>(a.p) >> 3U;
            const auto weights      = reinterpret_cast<std::uintptr_t>(a.w.i) + reinterpret_cast<std::uintptr_t>(a.w.r);
            return (node_pointer + weights) & MASK;
        }

        void insert(const A& a, const R& r) {
            const auto key = hash(a);
            table[key]     = {.a = a, .r = r};
            ++count;
        }

        R lookup(const A& a) {
            R r{};
            lookups++;
            const auto key   = hash(a);
            auto&      entry = table[key];
            if (entry.r.p == nullptr) return r;
            if (entry.a != a) return r;

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

#endif //DDpackage_UNARYCOMPUTETABLE_HPP
