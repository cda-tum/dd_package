/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DD_PACKAGE_EDGE_HPP
#define DD_PACKAGE_EDGE_HPP

#include "Complex.hpp"
#include "ComplexValue.hpp"

#include <cstddef>
#include <utility>

namespace dd {
    template<class Node>
    struct Edge {
        Node*   p;
        Complex w;

        /// Comparing two DD edges with another involves comparing the respective pointers
        /// and checking whether the corresponding weights are "close enough" according to a given tolerance
        /// this notion of equivalence is chosen to counter floating point inaccuracies
        constexpr bool operator==(const Edge& other) const {
            return p == other.p && w.approximatelyEquals(other.w);
        }
        constexpr bool operator!=(const Edge& other) const {
            return !operator==(other);
        }

        [[nodiscard]] constexpr bool isTerminal() const { return Node::isTerminal(p); }

        // edges pointing to zero and one terminals
        static inline Edge one{Node::terminal, Complex::one};
        static inline Edge zero{Node::terminal, Complex::zero};

        [[nodiscard]] static constexpr Edge terminal(const Complex& w) { return {Node::terminal, w}; }
        [[nodiscard]] constexpr bool        isZeroTerminal() const { return Node::isTerminal(p) && w == Complex::zero; }
        [[nodiscard]] constexpr bool        isOneTerminal() const { return Node::isTerminal(p) && w == Complex::one; }

        [[nodiscard]] static inline Node* setDensityConjugateTrue(const Node* p) {
            return reinterpret_cast<Node*>(reinterpret_cast<std::uintptr_t>(p) | 1ULL);
        }

        [[nodiscard]] static inline Node* setFirstEdgeDensityPathTrue(const Node* p) {
            return reinterpret_cast<Node*>(reinterpret_cast<std::uintptr_t>(p) | 2ULL);
        }

        [[nodiscard]] static inline Node* setDensityMatrixTrue(const Node* p) {
            return reinterpret_cast<Node*>(reinterpret_cast<std::uintptr_t>(p) | 4ULL);
        }

        [[nodiscard]] static inline bool isDensityConjugateSet(const Node* p) {
            return reinterpret_cast<std::uintptr_t>(p) & 1ULL;
        }

        [[nodiscard]] static inline bool isFirstEdgeDensityPath(const Node* p) {
            return reinterpret_cast<std::uintptr_t>(p) & 2ULL;
        }

        [[nodiscard]] static inline bool isDensityMatrix(const Node* p) {
            return reinterpret_cast<std::uintptr_t>(p) & 4ULL;
        }

        [[nodiscard]] static inline Node* getAlignedDensityNode(const Node* p) {
            return reinterpret_cast<Node*>(reinterpret_cast<std::uintptr_t>(p) & (~7ULL));
        }

        static inline void getAlignedDensityEdgeAlignSubEdges(Node* node, Edge<Node>* e) {
            if (isFirstEdgeDensityPath(node) && !isDensityConjugateSet(node)) {
                // Before I do anything else, i must aline the pointer
                e->p = getAlignedDensityNode(e->p);

                // first edge paths are not modified I only have to remove the first edge property
                e->p->e[0].p = getAlignedDensityNode(e->p->e[0].p);
                e->p->e[1].p = getAlignedDensityNode(e->p->e[1].p);
                e->p->e[2].p = getAlignedDensityNode(e->p->e[2].p);
                e->p->e[3].p = getAlignedDensityNode(e->p->e[3].p);
            } else if (!isDensityConjugateSet(node)) {
                // Before I do anything else, i must aline the pointer
                e->p = getAlignedDensityNode(e->p);

                // Conjugate the second edge (i.e. negate the complex part of the second edge)
                e->p->e[2].p   = getAlignedDensityNode(e->p->e[2].p);
                e->p->e[2].w.i = dd::CTEntry::flipPointerSign(e->p->e[2].w.i);

                // Unmark the first edge
                e->p->e[1].p = getAlignedDensityNode(e->p->e[1].p);
            } else {
                // Before I do anything else, i must aline the pointer
                e->p = getAlignedDensityNode(e->p);

                e->p->e[0].w.i = dd::CTEntry::flipPointerSign(e->p->e[0].w.i);
                e->p->e[1].w.i = dd::CTEntry::flipPointerSign(e->p->e[1].w.i);
                e->p->e[2].w.i = dd::CTEntry::flipPointerSign(e->p->e[2].w.i);
                e->p->e[3].w.i = dd::CTEntry::flipPointerSign(e->p->e[3].w.i);

                std::swap(e->p->e[2], e->p->e[1]);
            }

            // Conjugate all edges
            e->p->e[0].p = getAlignedDensityNode(e->p->e[0].p);
            e->p->e[1].p = getAlignedDensityNode(e->p->e[1].p);
            e->p->e[2].p = getAlignedDensityNode(e->p->e[2].p);
            e->p->e[3].p = getAlignedDensityNode(e->p->e[3].p);
        }

        static inline void revertDmChangesToEdges(Node* xNode, Edge<Node>* x, Node* yNode, Edge<Node>* y) {
            // Align the node pointers
            if (isDensityMatrix(xNode)) {
                getAlignedDensityEdgeAlignSubEdges(xNode, x);
            }
            if (isDensityMatrix(yNode)) {
                getAlignedDensityEdgeAlignSubEdges(yNode, y);
            }
        }

        static inline void applyDmChangesToEdges(Edge<Node>* x, Edge<Node>* y) {
            // Align the node pointers
            if (isDensityMatrix(x->p)) {
                alignDensityNode(x);
            }
            if (isDensityMatrix(y->p)) {
                alignDensityNode(y);
            }
        }

        // todo make arguments const
        static inline void alignDensityNode(Edge<Node>* e) {
            Node* alignedNode = getAlignedDensityNode(e->p);

            //todo make this more elegant
            if (alignedNode == nullptr || alignedNode->v <= -1) {
                e->p = getAlignedDensityNode(e->p);
            }

            if (isFirstEdgeDensityPath(e->p) && !isDensityConjugateSet(e->p)) {
                e->p = alignedNode;

                // first edge paths are not modified and the property is inherited by all child paths
                e->p->e[0].p = setFirstEdgeDensityPathTrue(e->p->e[0].p);
                e->p->e[1].p = setFirstEdgeDensityPathTrue(e->p->e[1].p);
                e->p->e[2].p = setFirstEdgeDensityPathTrue(e->p->e[2].p);
                e->p->e[3].p = setFirstEdgeDensityPathTrue(e->p->e[3].p);
            } else if (!isDensityConjugateSet(e->p)) {
                e->p = alignedNode;

                // Conjugate the second edge (i.e. negate the complex part of the second edge)
                e->p->e[2].w.i = dd::CTEntry::flipPointerSign(e->p->e[2].w.i);
                e->p->e[2].p   = setDensityConjugateTrue(e->p->e[2].p);
                // Mark the first edge
                e->p->e[1].p = setFirstEdgeDensityPathTrue(e->p->e[1].p);
            } else {
                e->p = alignedNode;

                std::swap(e->p->e[2], e->p->e[1]);

                // Conjugate all edges
                e->p->e[0].w.i = dd::CTEntry::flipPointerSign(e->p->e[0].w.i);
                e->p->e[0].p   = setDensityConjugateTrue(e->p->e[0].p);
                e->p->e[1].w.i = dd::CTEntry::flipPointerSign(e->p->e[1].w.i);
                e->p->e[1].p   = setDensityConjugateTrue(e->p->e[1].p);
                e->p->e[2].w.i = dd::CTEntry::flipPointerSign(e->p->e[2].w.i);
                e->p->e[2].p   = setDensityConjugateTrue(e->p->e[2].p);
                e->p->e[3].w.i = dd::CTEntry::flipPointerSign(e->p->e[3].w.i);
                e->p->e[3].p   = setDensityConjugateTrue(e->p->e[3].p);
            }
            e->p->e[0].p = setDensityMatrixTrue(e->p->e[0].p);
            e->p->e[1].p = setDensityMatrixTrue(e->p->e[1].p);
            e->p->e[2].p = setDensityMatrixTrue(e->p->e[2].p);
            e->p->e[3].p = setDensityMatrixTrue(e->p->e[3].p);
        }

        // todo make arguments const
        [[nodiscard]] static inline Edge<Node> getAlignedDensityNodeCopy(Edge<Node> e, Edge<Node> newEdge) {
            Node* alignedNode = getAlignedDensityNode(e.p);

            //todo make this more elegant
            if (alignedNode == nullptr || alignedNode->v <= -1) {
                e.p = getAlignedDensityNode(e.p);
                return e;
            }

            newEdge.p->v    = alignedNode->v;
            newEdge.p->e[0] = alignedNode->e[0];
            newEdge.p->e[1] = alignedNode->e[1];
            newEdge.p->e[2] = alignedNode->e[2];
            newEdge.p->e[3] = alignedNode->e[3];

            if (isFirstEdgeDensityPath(e.p) && !isDensityConjugateSet(e.p)) {
                // first edge paths are not modified and the property is inherited by all child paths
                newEdge.p->e[0].p = setFirstEdgeDensityPathTrue(newEdge.p->e[0].p);
                newEdge.p->e[1].p = setFirstEdgeDensityPathTrue(newEdge.p->e[1].p);
                newEdge.p->e[2].p = setFirstEdgeDensityPathTrue(newEdge.p->e[2].p);
                newEdge.p->e[3].p = setFirstEdgeDensityPathTrue(newEdge.p->e[3].p);
            } else if (!isDensityConjugateSet(e.p)) {
                // Conjugate the second edge (i.e. negate the complex part of the second edge)
                newEdge.p->e[2].w.i = dd::CTEntry::flipPointerSign(newEdge.p->e[2].w.i);
                newEdge.p->e[2].p   = setDensityConjugateTrue(newEdge.p->e[2].p);
                // Mark the first edge
                newEdge.p->e[1].p = setFirstEdgeDensityPathTrue(newEdge.p->e[1].p);
            } else {
                std::swap(newEdge.p->e[2], newEdge.p->e[1]);

                // Conjugate all edges
                newEdge.p->e[0].w.i = dd::CTEntry::flipPointerSign(newEdge.p->e[0].w.i);
                newEdge.p->e[0].p   = setDensityConjugateTrue(newEdge.p->e[0].p);
                newEdge.p->e[1].w.i = dd::CTEntry::flipPointerSign(newEdge.p->e[1].w.i);
                newEdge.p->e[1].p   = setDensityConjugateTrue(newEdge.p->e[1].p);
                newEdge.p->e[2].w.i = dd::CTEntry::flipPointerSign(newEdge.p->e[2].w.i);
                newEdge.p->e[2].p   = setDensityConjugateTrue(newEdge.p->e[2].p);
                newEdge.p->e[3].w.i = dd::CTEntry::flipPointerSign(newEdge.p->e[3].w.i);
                newEdge.p->e[3].p   = setDensityConjugateTrue(newEdge.p->e[3].p);
            }

            newEdge.p->e[0].p = setDensityMatrixTrue(newEdge.p->e[0].p);
            newEdge.p->e[1].p = setDensityMatrixTrue(newEdge.p->e[1].p);
            newEdge.p->e[2].p = setDensityMatrixTrue(newEdge.p->e[2].p);
            newEdge.p->e[3].p = setDensityMatrixTrue(newEdge.p->e[3].p);

            return newEdge;
        }
    };

    template<typename Node>
    struct CachedEdge {
        Node*        p{};
        ComplexValue w{};

        CachedEdge() = default;
        CachedEdge(Node* p, const ComplexValue& w):
            p(p), w(w) {}
        CachedEdge(Node* p, const Complex& c):
            p(p) {
            w.r = CTEntry::val(c.r);
            w.i = CTEntry::val(c.i);
        }

        /// Comparing two DD edges with another involves comparing the respective pointers
        /// and checking whether the corresponding weights are "close enough" according to a given tolerance
        /// this notion of equivalence is chosen to counter floating point inaccuracies
        bool operator==(const CachedEdge& other) const {
            return p == other.p && w.approximatelyEquals(other.w);
        }
        bool operator!=(const CachedEdge& other) const {
            return !operator==(other);
        }
    };

} // namespace dd

namespace std {
    template<class Node>
    struct hash<dd::Edge<Node>> {
        std::size_t operator()(dd::Edge<Node> const& e) const noexcept {
            auto h1 = dd::murmur64(reinterpret_cast<std::size_t>(e.p));
            auto h2 = std::hash<dd::Complex>{}(e.w);
            return dd::combineHash(h1, h2);
        }
    };

    template<class Node>
    struct hash<dd::CachedEdge<Node>> {
        std::size_t operator()(dd::CachedEdge<Node> const& e) const noexcept {
            auto h1 = dd::murmur64(reinterpret_cast<std::size_t>(e.p));
            auto h2 = std::hash<dd::ComplexValue>{}(e.w);
            return dd::combineHash(h1, h2);
        }
    };

//    template<> struct hash<dd::CachedEdge<dd::dNode>> {
//        std::size_t operator()(dd::CachedEdge<Node> const& e) const noexcept {
//            auto h1 = dd::murmur64(reinterpret_cast<std::size_t>(e.p));
//            auto h2 = std::hash<dd::ComplexValue>{}(e.w);
//            return dd::combineHash(h1, h2);
//        }
//    };

} // namespace std

#endif //DD_PACKAGE_EDGE_HPP
