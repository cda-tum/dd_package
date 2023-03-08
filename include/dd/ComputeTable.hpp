/*
 * This file is part of the MQT DD Package which is released under the MIT license.
 * See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_COMPUTETABLE_HPP
#define DDpackage_COMPUTETABLE_HPP

#include "Definitions.hpp"
#include "Node.hpp"

#include <array>
#include <cstddef>
#include <iostream>
#include <utility>

namespace dd {

    /// Data structure for caching computed results
    /// \tparam LeftOperandType type of the operation's left operand
    /// \tparam RightOperandType type of the operation's right operand
    /// \tparam ResultType type of the operation's result
    /// \tparam NBUCKET number of hash buckets to use (has to be a power of two)
    template<class LeftOperandType, class RightOperandType, class ResultType, std::size_t NBUCKET = 16384>
    class ComputeTable {
    public:
        ComputeTable() = default;

        struct Entry {
            LeftOperandType  leftOperand;
            RightOperandType rightOperand;
            ResultType       result;
        };

        static constexpr std::size_t MASK = NBUCKET - 1;

        static std::size_t hash(const LeftOperandType& leftOperand, const RightOperandType& rightOperand) {
            const auto h1   = std::hash<LeftOperandType>{}(leftOperand);
            const auto h2   = std::hash<RightOperandType>{}(rightOperand);
            const auto hash = dd::combineHash(h1, h2);
            return hash & MASK;
        }

        // access functions
        [[nodiscard]] const auto& getTable() const { return table; }

        void insert(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, const ResultType& result) {
            const auto key = hash(leftOperand, rightOperand);
            table[key]     = {leftOperand, rightOperand, result};
            ++count;
        }

        ResultType lookup(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, [[maybe_unused]] const bool useDensityMatrix = false) {
            ResultType result{};
            lookups++;
            const auto key   = hash(leftOperand, rightOperand);
            auto&      entry = table[key];
            if (entry.result.p == nullptr) return result;

            //            auto first  = (LimEntry<>::Equal(entry.trueLimX, trueLimX)) && (LimEntry<>::Equal(entry.trueLimY, trueLimY));
            //            auto second = (LimEntry<>::Equal(entry.leftOperand.l, leftOperand.l) && LimEntry<>::Equal(entry.rightOperand.l, rightOperand.l));
            //            Log::log << "[ComputeTable] Lookup hit (key=" << std::to_string(key)
            //                     << ")result with l=" << LimEntry<>::to_string(result.l)
            //                     << ")\nleftOperand with l=" << LimEntry<>::to_string(leftOperand.l)
            //                     << " rightOperand with l=" << LimEntry<>::to_string(rightOperand.l)
            //                     << " and trueLimX=" << LimEntry<>::to_string(trueLimX)
            //                     << " and trueLimY=" << LimEntry<>::to_string(trueLimY)
            //                     << " \nentry.leftOperand with l=" << LimEntry<>::to_string(entry.leftOperand.l)
            //                     << " entry.rightOperand with l=" << LimEntry<>::to_string(entry.rightOperand.l)
            //                     << " and entry.trueLimX=" << LimEntry<>::to_string(entry.trueLimX)
            //                     << " and entry.trueLimY=" << LimEntry<>::to_string(entry.trueLimY)
            //                     << "\n";

            if (entry.leftOperand != leftOperand) return result;
            if (entry.rightOperand != rightOperand) return result;
            //            if (entry.leftOperand.p != leftOperand.p) return result;
            //            if (!entry.leftOperand.w.approximatelyEquals(leftOperand.w)) return result;
            //
            //            if (entry.rightOperand.p != rightOperand.p) return result;
            //            if (!entry.rightOperand.w.approximatelyEquals(rightOperand.w)) return result;

            //            if (entry.rightOperand != rightOperand) return result;

            if constexpr (std::is_same_v<RightOperandType, dEdge>) {
                // Since density matrices are reduced representations of matrices, a density matrix may not be returned when a matrix is required and vice versa
                if (dNode::isDensityMatrixNode(entry.result.p->flags) != useDensityMatrix) return result;
            }
            hits++;
            return entry.result;
        }

        void clear() {
            if (count > 0) {
                for (auto& entry: table)
                    entry.result.p = nullptr;
                count = 0;
            }
        }

        [[nodiscard]] fp hitRatio() const { return static_cast<fp>(hits) / lookups; }
        std::ostream&    printStatistics(std::ostream& os = std::cout) {
            os << "hits: " << hits << ", looks: " << lookups << ", ratio: " << hitRatio() << std::endl;
            return os;
        }

    public:
        size_t getHits() const {
            return hits;
        }

        size_t getLookups() const {
            return lookups;
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
