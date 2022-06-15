/*
* This file is part of the MQT DD Package which is released under the MIT license.
* See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
*/

#pragma once

#include "Complex.hpp"
#include "ComplexValue.hpp"
#include "Definitions.hpp"
#include "Edge.hpp"

#include <array>
#include <cstddef>
#include <utility>

namespace dd {
    struct vNode {
        std::array<Edge<vNode>, RADIX> e{};    // edges out of this node
        vNode*                         next{}; // used to link nodes in unique table
        RefCount                       ref{};  // reference count
        Qubit                          v{};    // variable index (nonterminal) value (-1 for terminal)

        static vNode            terminalNode;
        constexpr static vNode* terminal{&terminalNode};

        static constexpr bool isTerminal(const vNode* p) { return p == terminal; }
    };
    using vEdge       = Edge<vNode>;
    using vCachedEdge = CachedEdge<vNode>;

    inline vNode vNode::terminalNode{{{{nullptr, Complex::zero}, {nullptr, Complex::zero}}}, nullptr, 0U, -1};

    struct mNode {
        std::array<Edge<mNode>, NEDGE> e{};    // edges out of this node
        mNode*                         next{}; // used to link nodes in unique table
        RefCount                       ref{};  // reference count
        Qubit                          v{};    // variable index (nonterminal) value (-1 for terminal)
        std::uint_least8_t             flags = 0;
        // 32 = marks a node with is symmetric.
        // 16 = marks a node resembling identity
        // 8 = marks a reduced dm node,
        // 4 = marks a dm (tmp flag),
        // 2 = mark first path edge (tmp flag),
        // 1 = mark path is conjugated (tmp flag))

        static mNode            terminalNode;
        constexpr static mNode* terminal{&terminalNode};

        static constexpr bool isTerminal(const mNode* p) { return p == terminal; }

        [[nodiscard]] inline bool isIdentity() const { return flags & 16; }
        [[nodiscard]] inline bool isSymmetric() const { return flags & 32; }
        inline void               setIdentity(bool identity) {
            if (identity)
                flags = (flags | 16);
            else
                flags = (flags & (~16));
        }
        inline void setSymmetric(bool symmetric) {
            if (symmetric)
                flags = (flags | 32);
            else
                flags = (flags & (~32));
        }
    };
    using mEdge       = Edge<mNode>;
    using mCachedEdge = CachedEdge<mNode>;

    inline mNode mNode::terminalNode{{{{nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}}}, nullptr, 0U, -1, 32 + 16};

    struct dNode {
        std::array<Edge<dNode>, NEDGE> e{};    // edges out of this node
        dNode*                         next{}; // used to link nodes in unique table
        RefCount                       ref{};  // reference count
        Qubit                          v{};    // variable index (nonterminal) value (-1 for terminal)
        std::uint_least8_t             flags = 0;
        // 32 = marks a node with is symmetric.
        // 16 = marks a node resembling identity
        // 8 = marks a reduced dm node,
        // 4 = marks a dm (tmp flag),
        // 2 = mark first path edge (tmp flag),
        // 1 = mark path is conjugated (tmp flag))

        static dNode            terminalNode;
        constexpr static dNode* terminal{&terminalNode};
        static constexpr bool   isTerminal(const dNode* p) { return p == terminal; }

        [[nodiscard]] static inline bool compareTempDensityMatrixFlags(const std::uint_least8_t a, const std::uint_least8_t b) { return (a & (7U)) == (b & (7U)); }
        [[nodiscard]] static inline bool isDensityConjugateSet(const long p) { return p & 1ULL; }
        [[nodiscard]] static inline bool isFirstEdgeDensityPath(const long p) { return p & 2ULL; }
        [[nodiscard]] static inline bool isDensityMatrix(const long p) { return p & 7ULL; }
        [[nodiscard]] static inline bool isDensityMatrixNode(const long p) { return p & 8U; }

        [[nodiscard]] static inline std::uint_least8_t getTempDensityMatrixFlags(const std::uint_least8_t a) { return a & (7U); }

        void unsetTempDensityMatrixFlags() { flags = flags & (~7U); }

        inline void setDensityMatrixNodeFlag(bool densityMatrix) {
            if (densityMatrix)
                flags = (flags | 8);
            else
                flags = (flags & (~8));
        }
    };
    using dEdge       = Edge<dNode>;
    using dCachedEdge = CachedEdge<dNode>;
    inline dNode dNode::terminalNode{{{{nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}}}, nullptr, 0, -1, 0};

} // namespace dd
