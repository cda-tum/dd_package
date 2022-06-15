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

        [[nodiscard]] static inline bool isDensityConjugateSet(const std::uintptr_t p) { return p & 1ULL; }
        [[nodiscard]] static inline bool isFirstEdgeDensityPath(const std::uintptr_t p) { return p & 2ULL; }
        [[nodiscard]] static inline bool isDensityMatrix(const std::uintptr_t p) { return p & 7ULL; }
        [[nodiscard]] static inline bool isDensityMatrixNode(const std::uintptr_t p) { return p & 8ULL; }

        [[nodiscard]] static inline bool isDensityConjugateSet(const dNode* p) { return isDensityConjugateSet((std::uintptr_t)p); }
        [[nodiscard]] static inline bool isFirstEdgeDensityPath(const dNode* p) { return isFirstEdgeDensityPath((std::uintptr_t)p); }
        [[nodiscard]] static inline bool isDensityMatrix(const dNode* p) { return isDensityMatrix((std::uintptr_t)p); }
        [[nodiscard]] static inline bool isDensityMatrixNode(const dNode* p) { return isDensityMatrixNode((std::uintptr_t)p); }

        static inline void setDensityConjugateTrueNode(dNode*& p) { p = reinterpret_cast<dNode*>(reinterpret_cast<std::uintptr_t>(p) | 1ULL); }
        static inline void setFirstEdgeDensityPathTrueNode(dNode*& p) { p = reinterpret_cast<dNode*>(reinterpret_cast<std::uintptr_t>(p) | 2ULL); }
        static inline void setDensityMatrixTrueNode(dNode*& p) { p = reinterpret_cast<dNode*>(reinterpret_cast<std::uintptr_t>(p) | 4ULL); }
        static inline void getAlignedDensityNode(dNode*& p) { p = reinterpret_cast<dNode*>(reinterpret_cast<std::uintptr_t>(p) & (~7ULL)); }

        [[nodiscard]] static inline std::uintptr_t getTempDensityMatrixFlags(dNode*& p) { return getTempDensityMatrixFlags((std::uintptr_t)p); }
        [[nodiscard]] static inline std::uintptr_t getTempDensityMatrixFlags(std::uintptr_t a) { return a & (7U); }

        void unsetTempDensityMatrixFlags() { flags = flags & (~7U); }

        inline void setDensityMatrixNodeFlag(bool densityMatrix) {
            if (densityMatrix)
                flags = (flags | 8);
            else
                flags = (flags & (~8));
        }

        static inline std::uint_least8_t alignDensityNodeNode(dNode*& p) {
            std::uint_least8_t flags = getTempDensityMatrixFlags(p);
            getAlignedDensityNode(p);

            if (p == nullptr || p->v <= -1) {
                return 0;
            }

            if (isFirstEdgeDensityPath(flags) && !isDensityConjugateSet(flags)) {
                // first edge paths are not modified and the property is inherited by all child paths
                return flags;
            } else if (!isDensityConjugateSet(flags)) {
                // Conjugate the second edge (i.e. negate the complex part of the second edge)
                p->e[2].w.i = dd::CTEntry::flipPointerSign(p->e[2].w.i);
                setDensityConjugateTrueNode(p->e[2].p);
                // Mark the first edge
                setFirstEdgeDensityPathTrueNode(p->e[1].p);

                for (auto& edge: p->e) {
                    setDensityMatrixTrueNode(edge.p);
                }

            } else {
                std::swap(p->e[2], p->e[1]);
                for (auto& edge: p->e) {
                    // Conjugate all edges
                    edge.w.i = dd::CTEntry::flipPointerSign(edge.w.i);
                    setDensityConjugateTrueNode(edge.p);
                    setDensityMatrixTrueNode(edge.p);
                }
            }
            return flags;
        }

        static inline void getAlignedNodeRevertModificationsOnSubEdges(dNode* p) {
            // Before I do anything else, I must align the pointer
            getAlignedDensityNode(p);

            for (auto& edge: p->e) {
                // first edge paths are not modified I only have to remove the first edge property
                getAlignedDensityNode(edge.p);
            }

            if (isFirstEdgeDensityPath(p->flags) && !isDensityConjugateSet(p->flags)) {
                ;

            } else if (!isDensityConjugateSet(p->flags)) {
                // Conjugate the second edge (i.e. negate the complex part of the second edge)
                p->e[2].w.i = dd::CTEntry::flipPointerSign(p->e[2].w.i);

            } else {
                for (auto& edge: p->e) {
                    // Align all nodes and conjugate the weights
                    edge.w.i = dd::CTEntry::flipPointerSign(edge.w.i);
                }
                std::swap(p->e[2], p->e[1]);
            }
        }

        static inline void applyDmChangesToNode(dNode*& p) {
            // Align the node pointers
            if (isDensityMatrix(p)) {
                auto tmp = alignDensityNodeNode(p);
                assert(getTempDensityMatrixFlags(p->flags) == 0);
                p->flags = p->flags | tmp;
            }
        }

        static inline void revertDmChangesToNode(dNode*& p) {
            // Align the node pointers
            if (isDensityMatrix(p->flags)) {
                getAlignedNodeRevertModificationsOnSubEdges(p);
                p->unsetTempDensityMatrixFlags();
            }
        }
    };
    using dEdge       = Edge<dNode>;
    using dCachedEdge = CachedEdge<dNode>;
    inline dNode dNode::terminalNode{{{{nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}, {nullptr, Complex::zero}}}, nullptr, 0, -1, 0};

    template<>
    constexpr bool dEdge::operator==(const dEdge& other) const { // todo check if this function is necessary
        assert(p != nullptr && other.p != nullptr);
        return p == other.p && dNode::compareTempDensityMatrixFlags(p->flags, other.p->flags) && w.approximatelyEquals(other.w);
    }

} // namespace dd

namespace std {
    template<>
    struct hash<dd::dEdge> {
        std::size_t operator()(dd::dEdge const& e) const noexcept { // todo check if this function is necessary
            auto h1 = dd::murmur64(reinterpret_cast<std::size_t>(e.p));
            auto h2 = std::hash<dd::Complex>{}(e.w);
            assert((dd::dNode::isDensityMatrix((long)e.p)) == false);
            auto h3 = std::hash<std::uint_least8_t>{}(dd::dNode::getTempDensityMatrixFlags(e.p->flags));
            //           auto h3  = std::hash<short int>{}(e.p->flags);
            auto tmp = dd::combineHash(h1, h2);
            return dd::combineHash(tmp, h3);
        }
    };
} // namespace std
