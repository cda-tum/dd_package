/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_OPERATIONTABLE_HPP
#define DDpackage_OPERATIONTABLE_HPP

#include "Definitions.hpp"

#include <array>
#include <cstdint>

namespace dd {
    // operation kinds (related to noise)
    enum OperationKind : std::uint_fast8_t {
        none,
        I,
        X,
        Y,
        Z,
        ATrue,
        AFalse
    };

    template<class Edge, std::size_t NBUCKET = 32768>
    class OperationTable {
    public:
        OperationTable() = default;

        struct Entry {
            OperationKind               kind;
            Edge                        r;
            std::array<Qubit, dd::MAXN> line;
        };

        static constexpr size_t MASK = NBUCKET - 1;

        // access functions
        [[nodiscard]] const auto& getTable() const { return table; }

        void insert(Qubit mostSignificantQubit, OperationKind kind, const std::array<Qubit, dd::MAXN>& line, const Edge& r) {
            const auto key = hash(mostSignificantQubit, kind, line);
            table[key]     = {.kind = kind, .r = r, .line = line};
            ++count;
        }

        Edge lookup(Qubit mostSignificantQubit, OperationKind kind, const std::array<Qubit, dd::MAXN>& line) {
            lookups++;
            Edge        r{};
            const auto  key   = hash(mostSignificantQubit, kind, line);
            const auto& entry = table[key];
            if (entry.r.p == nullptr) return r;
            if (entry.kind != kind) return r;
            if (entry.r.p->v != mostSignificantQubit) return r;
            if (entry.line != line) return r;
            hits++;
            return entry.r;
        }

        static size_t hash(Qubit mostSignificantQubit, OperationKind kind, const std::array<Qubit, dd::MAXN>& line) {
            size_t key = kind;
            for (auto i = 0; i <= mostSignificantQubit; ++i) {
                key = (key << 3U) + key * i + line[i];
            }
            return key & MASK;
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

        // operation table lookup statistics
        std::size_t hits    = 0;
        std::size_t lookups = 0;
        std::size_t count   = 0;
    };
} // namespace dd

#endif //DDpackage_OPERATIONTABLE_HPP
