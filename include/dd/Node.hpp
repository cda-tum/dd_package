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
        std::int_fast8_t               flags = 0;

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
        std::int_fast8_t               flags = 0;
        bool                           symm  = false; // node is symmetric
        bool                           ident = false; // node resembles identity

        static mNode            terminalNode;
        constexpr static mNode* terminal{&terminalNode};

        static constexpr bool isTerminal(const mNode* p) { return p == terminal; }
    };
    using mEdge       = Edge<mNode>;
    using mCachedEdge = CachedEdge<mNode>;

    inline mNode mNode::terminalNode{{{{nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}}}, nullptr, 0U, -1, 0, true, true};

    struct dNode {
        std::array<Edge<dNode>, NEDGE> e{};    // edges out of this node
        dNode*                         next{}; // used to link nodes in unique table
        RefCount                       ref{};  // reference count
        Qubit                          v{};    // variable index (nonterminal) value (-1 for terminal)
        std::int_fast8_t               flags = 0;
        // 8 = marks a reduced dm node,
        // 4 = marks a dm (tmp flag),
        // 2 = mark first path edge (tmp flag),
        // 1 = mark path is conjugated (tmp flag))

        static dNode            terminalNode;
        constexpr static dNode* terminal{&terminalNode};

        static constexpr bool isTerminal(const dNode* p) { return p == terminal; }
        //static constexpr bool isDensity() { return true; }
    };
    using dEdge       = Edge<dNode>;
    using dCachedEdge = CachedEdge<dNode>;
    inline dNode dNode::terminalNode{{{{nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}}}, nullptr, 0, -1, 0};

} // namespace dd
