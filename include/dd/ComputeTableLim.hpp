/*
* This file is part of the MQT DD Package which is released under the MIT license.
* See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
*/

#pragma once

#include "ComplexTable.hpp"
#include "Definitions.hpp"
#include "LimTable.hpp"
#include "Node.hpp"
#include "Package.hpp"
#include "Export.hpp"

#include <array>
#include <cstddef>
#include <iostream>
#include <utility>

namespace dd {
    template<class LeftOperandType, class RightOperandType, class ResultType, std::size_t NBUCKET = 16384>
    class ComputeTableOneLim: public ComputeTable<LeftOperandType, RightOperandType, ResultType, NBUCKET> {
        using base = dd::ComputeTable<LeftOperandType, RightOperandType, ResultType, NBUCKET>;

    public:
        struct Entry {
            LeftOperandType              leftOperand;
            RightOperandType             rightOperand;
            ResultType                   result;
            LimTable<NUM_QUBITS>::Entry* trueLim = nullptr;
        };

        static constexpr std::size_t MASK = NBUCKET - 1;

        static std::size_t hash(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, const LimTable<>::Entry* trueLim) {
            const auto h1   = std::hash<LeftOperandType>{}(leftOperand);
            const auto h2   = std::hash<RightOperandType>{}(rightOperand);
            const auto h3   = LimTable<>::hash(trueLim);
            const auto h4   = dd::combineHash(h1, h2);
            const auto hash = dd::combineHash(h4, h3);
            return hash & MASK;
        }

        void insert(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, const ResultType& result, LimTable<>::Entry* trueLim = {}) {
            const auto key = hash(leftOperand, rightOperand, trueLim);
            table[key]     = {leftOperand, rightOperand, result, trueLim};

            Log::log << "[ComputeTable] Inserting (key=" << std::to_string(key)
                     << ") rightOperand with l=" << LimEntry<>::to_string(rightOperand.l)
                     << " and trueLim=" << LimEntry<>::to_string(trueLim)
                     << "\n";
            ++base::count;
        }

        ResultType lookup(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, [[maybe_unused]] const bool useDensityMatrix = false, LimTable<>::Entry* trueLim = {}) {
            ResultType result{};
            base::lookups++;
            const auto key   = hash(leftOperand, rightOperand, trueLim);
            auto&      entry = table[key];
            if (entry.result.p == nullptr) return result;
            if (entry.leftOperand != leftOperand) return result;
            if (entry.rightOperand != rightOperand) return result;
            if (!LimEntry<>::Equal(entry.trueLim, trueLim)) return result;

            if constexpr (std::is_same_v<RightOperandType, dEdge>) {
                // Since density matrices are reduced representations of matrices, a density matrix may not be returned when a matrix is required and vice versa
                if (dNode::isDensityMatrixNode(entry.result.p->flags) != useDensityMatrix) return result;
            }
            base::hits++;
            Log::log << "[ComputeTable] Lookup hit (key=" << std::to_string(key)
                     << ") rightOperand with l=" << LimEntry<>::to_string(rightOperand.l)
                     << " and trueLim=" << LimEntry<>::to_string(trueLim)
                     << "\n";
            return entry.result;
        }

    protected:
        std::array<Entry, NBUCKET> table{};
    };

    template<class LeftOperandType, class RightOperandType, class ResultType, std::size_t NBUCKET = 16384>
    class ComputeTableTwoLim: public ComputeTable<LeftOperandType, RightOperandType, ResultType, NBUCKET> {
        using base = dd::ComputeTable<LeftOperandType, RightOperandType, ResultType, NBUCKET>;

    public:
        struct Entry {
            LeftOperandType              leftOperand;
            RightOperandType             rightOperand;
            ResultType                   result;
            LimTable<NUM_QUBITS>::Entry* trueLimX = nullptr;
            LimTable<NUM_QUBITS>::Entry* trueLimY = nullptr;
        };

        static std::size_t hash(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, LimTable<>::Entry* trueLimX, LimTable<>::Entry* trueLimY) {
            const auto h1 = std::hash<LeftOperandType>{}(leftOperand);
            const auto h2 = std::hash<RightOperandType>{}(rightOperand);
            //            const auto h3   = LimTable<>::hash(trueLimX);
            //            const auto h4   = LimTable<>::hash(trueLimY);
            const auto h5 = dd::combineHash(h1, h2);
            //            const auto h6   = dd::combineHash(h3, h4);
            //            const auto hash = dd::combineHash(h5, h6);
            return h5 & base::MASK;
        }

        void insert(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, const ResultType& result, LimTable<>::Entry* trueLimX = {}, LimTable<>::Entry* trueLimY = {}) {
            const auto key = hash(leftOperand, rightOperand, trueLimX, trueLimY);
            table[key]     = {leftOperand, rightOperand, result, trueLimX, trueLimY};

            Log::log << "[ComputeTable] Inserting (key=" << std::to_string(key)
                     << ") leftOperand with l=" << LimEntry<>::to_string(leftOperand.l)
                     << ") rightOperand with l=" << LimEntry<>::to_string(rightOperand.l)
                     << " and trueLimX=" << LimEntry<>::to_string(trueLimX)
                     << " and trueLimY=" << LimEntry<>::to_string(trueLimY)
                     << "\n";
            ++base::count;
        }

        ResultType lookup(const LeftOperandType& leftOperand, const RightOperandType& rightOperand, [[maybe_unused]] const bool useDensityMatrix = false, LimTable<>::Entry* trueLimX = {}, LimTable<>::Entry* trueLimY = {}) {
            ResultType result{};
            base::lookups++;
            const auto key   = hash(leftOperand, rightOperand, trueLimX, trueLimY);
            auto&      entry = table[key];
            if (entry.result.p == nullptr) return result;
            if (entry.leftOperand != leftOperand) return result;
            if (entry.rightOperand != rightOperand) return result;
            if (!LimEntry<>::Equal(entry.trueLimX, trueLimX)) return result;
            if (!LimEntry<>::Equal(entry.trueLimY, trueLimY)) return result;

            if constexpr (std::is_same_v<RightOperandType, dEdge>) {
                // Since density matrices are reduced representations of matrices, a density matrix may not be returned when a matrix is required and vice versa
                if (dNode::isDensityMatrixNode(entry.result.p->flags) != useDensityMatrix) return result;
            }
            base::hits++;
            Log::log << "[ComputeTable] Lookup hit (key=" << std::to_string(key)
                     << ") leftOperand with l=" << LimEntry<>::to_string(leftOperand.l)
                     << ") rightOperand with l=" << LimEntry<>::to_string(rightOperand.l)
                     << " and trueLimX=" << LimEntry<>::to_string(trueLimX)
                     << " and trueLimY=" << LimEntry<>::to_string(trueLimY)
                     << "\n";
            return entry.result;
        }

    protected:
        std::array<Entry, NBUCKET> table{};
    };

} // namespace dd
