/*
* This file is part of the MQT DD Package which is released under the MIT license.
* See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
*/

#pragma once

#include "Definitions.hpp"
#include "Edge.hpp"

#include <array>

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
    };
    using dEdge       = Edge<dNode>;
    using dCachedEdge = CachedEdge<dNode>;
    inline dNode dNode::terminalNode{{{{nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}}}, nullptr, 0, -1, 0};

    template<>
    constexpr bool dEdge::operator==(const dEdge& other) const {
        assert(p != nullptr && other.p != nullptr);
        return p == other.p && tempDensityMatrixFlagsEqual(p->flags, other.p->flags) && w.approximatelyEquals(other.w);
    }

} // namespace dd

namespace std {
    template<>
    struct hash<dd::dEdge> {
        std::size_t operator()(dd::dEdge const& e) const noexcept {
            auto h1 = dd::murmur64(reinterpret_cast<std::size_t>(e.p));
            auto h2 = std::hash<dd::Complex>{}(e.w);
            assert((dd::dEdge::isDensityMatrix((long)e.p)) == false);
            auto h3 = std::hash<std::uint_least8_t>{}(dd::dEdge::returnTempDensityMatrixFlags(e.p->flags));
            //           auto h3  = std::hash<short int>{}(e.p->flags);
            auto tmp = dd::combineHash(h1, h2);
            return dd::combineHash(tmp, h3);
        }
    };
} // namespace std
