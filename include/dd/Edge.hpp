/*
 * This file is part of the MQT DD Package which is released under the MIT license.
 * See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
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

        [[nodiscard]] static inline bool tempDensityMatrixFlagsEqual(const std::uint8_t a, const std::uint8_t b) {
            return (a & (7U)) == (b & (7U));
        }


        [[nodiscard]] static inline bool isDensityConjugateSet(const long p) {
            return p & 1ULL;
        }

        [[nodiscard]] static inline bool isFirstEdgeDensityPath(const long p) {
            return p & 2ULL;
        }

        [[nodiscard]] static inline bool isDensityMatrix(const long p) {
            return p & 7ULL;
        }

        [[nodiscard]] static inline bool isDensityMatrixNode(const long p) {
            return p & 8U;
        }

        [[nodiscard]] static inline Node* getAlignedDensityNode(const Node* p) {
            return reinterpret_cast<Node*>(reinterpret_cast<std::uintptr_t>(p) & (~7ULL));
        }

        static inline void revertDmChangesToEdges(Edge<Node>* x, Edge<Node>* y) {
            // Align the node pointers
            if (x != nullptr && isDensityMatrix((long)x->p->flags)) {
                getAlignedEdgeRevertModificationsOnSubEdges(x);
                x->p->flags = x->p->flags & (8U);
            }
            if (y != nullptr && isDensityMatrix((long)y->p->flags)) {
                getAlignedEdgeRevertModificationsOnSubEdges(y);
                y->p->flags = x->p->flags & (8U);
            }
        }

        static inline void applyDmChangesToEdges(Edge<Node>* x, Edge<Node>* y) {
            // Align the node pointers
            if (x != nullptr) {
                if (isDensityMatrix((long)x->p)) {
                    auto tmp = alignDensityNode(x);
                    assert((x->p->flags & (7U)) == 0);
                    x->p->flags = x->p->flags | tmp;
                }
            }

            if (y != nullptr) {
                if (isDensityMatrix((long)y->p)) {
                    auto tmp = alignDensityNode(y);
                    assert((y->p->flags & (7U)) == 0);
                    y->p->flags = x->p->flags | tmp;
                }
            }
        }

        static inline short int alignDensityNode(Edge<Node>* e) {
            Node*     alignedNode = getAlignedDensityNode(e->p);
            short int flags       = (long)e->p & (7U);

            if (alignedNode == nullptr || alignedNode->v <= -1) {
                e->p = alignedNode;
                return 0;
            }

            if (isFirstEdgeDensityPath((long)e->p) && !isDensityConjugateSet((long)e->p)) {
                e->p = alignedNode;

                // first edge paths are not modified and the property is inherited by all child paths
                return flags;
            } else if (!isDensityConjugateSet((long)e->p)) {
                e->p = alignedNode;

                // Conjugate the second edge (i.e. negate the complex part of the second edge)
                e->p->e[2].w.i = dd::CTEntry::flipPointerSign(e->p->e[2].w.i);
                e->p->e[2].p   = setDensityConjugateTrue(e->p->e[2].p);
                // Mark the first edge
                e->p->e[1].p = setFirstEdgeDensityPathTrue(e->p->e[1].p);

                for (auto& edge: e->p->e) {
                    edge.p = setDensityMatrixTrue(edge.p);
                }

            } else {
                e->p = alignedNode;

                std::swap(e->p->e[2], e->p->e[1]);
                for (auto& edge: e->p->e) {
                    // Conjugate all edges
                    edge.w.i = dd::CTEntry::flipPointerSign(edge.w.i);
                    edge.p   = setDensityConjugateTrue(edge.p);
                    edge.p   = setDensityMatrixTrue(edge.p);
                }
            }
            return flags;
        }

        static inline void getAlignedEdgeRevertModificationsOnSubEdges(Edge<Node>* e) {
            if (isFirstEdgeDensityPath(e->p->flags) && !isDensityConjugateSet(e->p->flags)) {
                // Before I do anything else, I must align the pointer
                e->p = getAlignedDensityNode(e->p);

                for (auto& edge: e->p->e) {
                    // first edge paths are not modified I only have to remove the first edge property
                    edge.p = getAlignedDensityNode(edge.p);
                }

            } else if (!isDensityConjugateSet(e->p->flags)) {
                // Before I do anything else, I must align the pointer
                e->p = getAlignedDensityNode(e->p);

                for (auto& edge: e->p->e) {
                    // align all nodes
                    edge.p = getAlignedDensityNode(edge.p);
                }

                // Conjugate the second edge (i.e. negate the complex part of the second edge)
                e->p->e[2].w.i = dd::CTEntry::flipPointerSign(e->p->e[2].w.i);

            } else {
                // Before I do anything else, I must align the pointer
                e->p = getAlignedDensityNode(e->p);

                for (auto& edge: e->p->e) {
                    // Align all nodes and conjugate the weights
                    edge.p   = getAlignedDensityNode(edge.p);
                    edge.w.i = dd::CTEntry::flipPointerSign(edge.w.i);
                }
                std::swap(e->p->e[2], e->p->e[1]);
            }
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
} // namespace std

#endif //DD_PACKAGE_EDGE_HPP
