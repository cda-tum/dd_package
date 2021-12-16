#ifndef DDPACKAGE_NODES_HPP
#define DDPACKAGE_NODES_HPP

#include "Definitions.hpp"
#include "Edge.hpp"

#include <vector>

namespace dd {
    struct vNode {
        std::array<Edge<vNode>, RADIX>  e{};         // edges out of this node
        vNode*                          next{};      // used to link nodes in unique table
        RefCount                        ref{};       // reference count
        Qubit                           v{};         // variable index (nonterminal) value (-1 for terminal)
        std::vector<LimTable<>::Entry*> limVector{}; // a vector of pointers to lims, might be nullptr for all identity

        static vNode            terminalNode;
        constexpr static vNode* terminal{&terminalNode};

        static constexpr bool isTerminal(const vNode* p) { return p == terminal; }
    };

    struct mNode {
        std::array<Edge<mNode>, NEDGE>  e{};           // edges out of this node
        mNode*                          next{};        // used to link nodes in unique table
        RefCount                        ref{};         // reference count
        Qubit                           v{};           // variable index (nonterminal) value (-1 for terminal)
        bool                            symm  = false; // node is symmetric
        bool                            ident = false; // node resembles identity
        std::vector<LimTable<>::Entry*> limVector{};   // a vector of pointers to lims, might be nullptr for all identity

        static mNode            terminalNode;
        constexpr static mNode* terminal{&terminalNode};

        static constexpr bool isTerminal(const mNode* p) { return p == terminal; }
    };
}

#endif //DDPACKAGE_NODES_HPP
