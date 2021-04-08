/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_OPERATIONTABLE_HPP
#define DDpackage_OPERATIONTABLE_HPP

#include "Definitions.hpp"

#include <cstdint>
#include <set>

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
            QubitCount        n    = 0;
            OperationKind     kind = none;
            std::set<Control> controls{}; // TODO: I suppose this is not necessary
            Qubit             target = 0;
            Edge              r{};
        };

        static constexpr size_t MASK = NBUCKET - 1;

        // access functions
        [[nodiscard]] const auto& getTable() const { return table; }

        void insert(QubitCount n, OperationKind kind, Qubit target, const Edge& r) {
            insert(n, kind, {}, target, r);
        }
        void insert(QubitCount n, OperationKind kind, const std::set<Control>& controls, Qubit target, const Edge& r) {
            const auto key = hash(kind, controls, target);
            table[key]     = {.n = n, .kind = kind, .controls = controls, .target = target, .r = r};
            ++count;
        }

        Edge lookup(QubitCount n, OperationKind kind, Qubit target) {
            return lookup(n, kind, {}, target);
        }
        Edge lookup(QubitCount n, OperationKind kind, const std::set<Control>& controls, Qubit target) {
            lookups++;
            Edge        r{};
            const auto  key   = hash(kind, controls, target);
            const auto& entry = table[key];
            if (entry.r.p == nullptr) return r;
            if (entry.kind != kind) return r;
            if (entry.n != n) return r;
            if (entry.target != target) return r;
            if (entry.controls != controls) return r;
            hits++;
            return entry.r;
        }

        static size_t hash(OperationKind kind, const std::set<Control>& controls, Qubit target) {
            std::size_t key = kind + (target << 3U);
            for (const auto& control: controls) {
                if (control.type == dd::Control::Type::pos) {
                    key *= 29u * control.qubit;
                } else {
                    key *= 71u * control.qubit;
                }
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
        /// gcc is having serious troubles compiling this using std::array (compilation times >15min).
        /// std::vector shouldn't be any less efficient in our application scenario
        /// TODO: revisit this in the future
        std::vector<Entry> table{NBUCKET};

        // operation table lookup statistics
        std::size_t hits    = 0;
        std::size_t lookups = 0;
        std::size_t count   = 0;
    };
} // namespace dd

#endif //DDpackage_OPERATIONTABLE_HPP
