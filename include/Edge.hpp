/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DD_PACKAGE_EDGE_HPP
#define DD_PACKAGE_EDGE_HPP

#include "DDcomplex.hpp"
#include "Definitions.hpp"

namespace dd {
    template<class Node>
    struct Edge {
        Node*   p;
        Complex w;

        constexpr bool operator==(const Edge& other) const {
            return p == other.p && CN::equals(w, other.w);
        }
        constexpr bool operator!=(const Edge& other) const {
            return !operator==(other);
        }

        [[nodiscard]] constexpr bool isTerminal() const { return Node::isTerminal(p); }

        // edges pointing to zero and one terminals
        static inline Edge one{Node::terminal, CN::ONE};
        static inline Edge zero{Node::terminal, CN::ZERO};

        [[nodiscard]] static constexpr Edge terminal(const Complex& w) { return {Node::terminal, w}; }
        [[nodiscard]] constexpr bool        isZeroTerminal() const { return Node::isTerminal(p) && w == CN::ZERO; }
        [[nodiscard]] constexpr bool        isOneTerminal() const { return Node::isTerminal(p) && w == CN::ONE; }
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
            w.r = CN::val(c.r);
            w.i = CN::val(c.i);
        }
        bool operator==(const CachedEdge& other) const {
            return p == other.p && CN::equals(w, other.w);
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
            auto h1 = std::hash<Node*>{}(e.p);
            auto h2 = std::hash<dd::Complex>{}(e.w);
            return h1 ^ (h2 << 1);
        }
    };

    template<class Node>
    struct hash<dd::CachedEdge<Node>> {
        std::size_t operator()(dd::CachedEdge<Node> const& e) const noexcept {
            auto h1 = std::hash<Node*>{}(e.p);
            auto h2 = std::hash<dd::ComplexValue>{}(e.w);
            return h1 ^ (h2 << 1);
        }
    };
} // namespace std

#endif //DD_PACKAGE_EDGE_HPP
