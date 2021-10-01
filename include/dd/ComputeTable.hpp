/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_COMPUTETABLE_HPP
#define DDpackage_COMPUTETABLE_HPP

#include "Definitions.hpp"

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
            unsigned short   leftNodeFlags;
            unsigned short   rightNodeFlags;
            short            successorEdge;
            ResultType       result;
        };

        static constexpr std::size_t MASK = NBUCKET - 1;

        static std::size_t hash(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, const unsigned long leftNodeFlags, const unsigned long rightNodeFlags, const short successorEdge) {
            const auto h1 = std::hash<LeftOperandType>{}(leftOperand);
            const auto h2 = std::hash<RightOperandType>{}(rightOperand);
            // todo improve the hashing scheme
            const auto hash = dd::combineHash(h1, h2) ^ leftNodeFlags ^ ~rightNodeFlags ^ successorEdge + 32;
            return hash & MASK;
        }

        // access functions
        [[nodiscard]] const auto& getTable() const { return table; }

        void insert(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, const ResultType& result, const unsigned long leftNodeFlags = 0, const unsigned long rightNodeFlags = 0, const short successorEdge = 0) {
            unsigned short leftFlags  = leftNodeFlags & 7;
            unsigned short rightFlags = rightNodeFlags & 7;

            const auto key = hash(leftOperand, rightOperand, leftFlags, rightFlags, successorEdge);
            table[key]     = {leftOperand, rightOperand, leftFlags, rightFlags, successorEdge, result};
            ++count;
        }

        ResultType lookup(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, const unsigned long leftNodeFlags = 0, const unsigned long rightNodeFlags = 0, const short successorEdge = 0) {
            unsigned short leftFlags  = leftNodeFlags & 7;
            unsigned short rightFlags = rightNodeFlags & 7;
            ResultType     result{};
            lookups++;
            const auto key   = hash(leftOperand, rightOperand, leftFlags, rightFlags, successorEdge);
            auto&      entry = table[key];
//            return result;
            if (entry.result.p == nullptr) return result;
            if (entry.leftNodeFlags != leftFlags) return result;
            if (entry.rightNodeFlags != rightFlags) return result;
            if (entry.successorEdge != successorEdge) return result;
            if (entry.leftOperand != leftOperand) return result;
            if (entry.rightOperand != rightOperand) return result;

            hits++;
            return entry.result;
        }

        void clear() {
            if (count > 0) {
                for (auto& entry: table)
                    entry.result.p = nullptr;
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
