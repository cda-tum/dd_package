/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "DDexport.hpp"

#include <regex>
#include <stack>

namespace dd {

    RGB hlsToRGB(const fp& h, const fp& l, const fp& s) {
        if (s == 0.0) {
            return {l, l, l};
        }
        fp m2;
        if (l <= 0.5) {
            m2 = l * (1 + s);
        } else {
            m2 = l + s - (l * s);
        }
        auto m1 = 2 * l - m2;

        auto v = [](const fp& m1, const fp& m2, fp hue) -> fp {
            while (hue < 0) hue += 1.0;
            while (hue > 1) hue -= 1.0;
            if (hue < 1. / 6)
                return m1 + (m2 - m1) * hue * 6.0;
            if (hue < 0.5)
                return m2;
            if (hue < 2. / 3)
                return m1 + (m2 - m1) * (2. / 3 - hue) * 6.0;
            return m1;
        };

        return {v(m1, m2, h + 1. / 3), v(m1, m2, h), v(m1, m2, h - 1. / 3)};
    }

    RGB colorFromPhase(const Complex& a) {
        auto phase = CN::arg(a);
        auto twopi = 2 * CN::PI;
        phase      = (phase) / twopi;
        return hlsToRGB(phase, 0.5, 0.5);
    }

    fp thicknessFromMagnitude(const Complex& a) {
        return 3.0 * std::max(CN::mag(a), 0.10);
    }

    void writeBinaryAmplitude(std::ostream& os, const Complex& w) {
        fp temp = CN::val(w.r);
        os.write(reinterpret_cast<const char*>(&temp), sizeof(fp));
        temp = CN::val(w.i);
        os.write(reinterpret_cast<const char*>(&temp), sizeof(fp));
    }

    std::ostream& modernNode(const Package::mEdge& e, std::ostream& os) {
        auto nodelabel = (reinterpret_cast<uintptr_t>(e.p) & 0x001fffffU) >> 1U; // this allows for 2^20 (roughly 1e6) unique nodes
        os << nodelabel << "[label=<";
        os << R"(<font point-size="10"><table border="1" cellspacing="0" cellpadding="2" style="rounded">)";
        os << R"(<tr><td colspan="2" rowspan="2" port="0" href="javascript:;" border="0" tooltip=")" << e.p->e[0].w << "\">" << (CN::equalsZero(e.p->e[0].w) ? "&nbsp;0 " : "<font color=\"white\">&nbsp;0 </font>")
           << R"(</td><td sides="R"></td><td sides="L"></td>)"
           << R"(<td colspan="2" rowspan="2" port="1" href="javascript:;" border="0" tooltip=")" << e.p->e[1].w << "\">" << (CN::equalsZero(e.p->e[1].w) ? "&nbsp;0 " : "<font color=\"white\">&nbsp;0 </font>") << R"(</td></tr>)";
        os << R"(<tr><td sides="R"></td><td sides="L"></td></tr>)";
        os << R"(<tr><td colspan="2" sides="B"></td><td colspan="2" rowspan="2" border="0"><font point-size="24">q<sub><font point-size="16">)" << static_cast<std::size_t>(e.p->v) << R"(</font></sub></font></td><td colspan="2" sides="B"></td></tr>)";
        os << R"(<tr><td sides="T" colspan="2"></td><td sides="T" colspan="2"></td></tr>)";
        os << R"(<tr><td colspan="2" rowspan="2" port="2" href="javascript:;" border="0" tooltip=")" << e.p->e[2].w << "\">" << (CN::equalsZero(e.p->e[2].w) ? "&nbsp;0 " : "<font color=\"white\">&nbsp;0 </font>")
           << R"(</td><td sides="R"></td><td sides="L"></td>)"
           << R"(<td colspan="2" rowspan="2" port="3" href="javascript:;" border="0" tooltip=")" << e.p->e[3].w << "\">" << (CN::equalsZero(e.p->e[3].w) ? "&nbsp;0 " : "<font color=\"white\">&nbsp;0 </font>") << "</td></tr>";
        os << R"(<tr><td sides="R"></td><td sides="L"></td></tr>)";
        os << "</table></font>>,tooltip=\"q" << static_cast<std::size_t>(e.p->v) << "\"]\n";
        return os;
    }
    std::ostream& classicNode(const Package::mEdge& e, std::ostream& os) {
        auto nodelabel = (reinterpret_cast<uintptr_t>(e.p) & 0x001fffffU) >> 1U; // this allows for 2^20 (roughly 1e6) unique nodes
        os << nodelabel << "[shape=circle, width=0.53, fixedsize=true, label=<";
        os << R"(<font point-size="6"><table border="0" cellspacing="0" cellpadding="0">)";
        os << R"(<tr><td colspan="4"><font point-size="18">q<sub><font point-size="10">)" << static_cast<std::size_t>(e.p->v) << R"(</font></sub></font></td></tr><tr>)";
        os << R"(<td port="0" tooltip=")" << e.p->e[0].w << R"(" href="javascript:;">)";
        if (CN::equalsZero(e.p->e[0].w)) {
            os << R"(<font point-size="8">&nbsp;0 </font>)";
        } else {
            os << R"(<font color="white">&nbsp;0 </font>)";
        }
        os << "</td>";
        os << "<td></td><td></td>";
        os << R"(<td port="3" tooltip=")" << e.p->e[3].w << R"(" href="javascript:;">)";
        if (CN::equalsZero(e.p->e[3].w)) {
            os << R"(<font point-size="8">&nbsp;0 </font>)";
        } else {
            os << R"(<font color="white">&nbsp;0 </font>)";
        }
        os << "</td>";
        os << "</tr><tr><td></td>";
        os << R"(<td port="1" tooltip=")" << e.p->e[1].w << R"(" href="javascript:;">)";
        if (CN::equalsZero(e.p->e[1].w)) {
            os << R"(<font point-size="8">&nbsp;0 </font>)";
        } else {
            os << R"(<font color="white">&nbsp;0 </font>)";
        }
        os << "</td>";
        os << R"(<td port="2" tooltip=")" << e.p->e[2].w << R"(" href="javascript:;">)";
        if (CN::equalsZero(e.p->e[2].w)) {
            os << R"(<font point-size="8">&nbsp;0 </font>)";
        } else {
            os << R"(<font color="white">&nbsp;0 </font>)";
        }
        os << "</td>";
        os << "<td></td></tr></table></font>>,tooltip=\"q" << static_cast<std::size_t>(e.p->v) << "\"]\n";
        return os;
    }

    std::ostream& modernNode(const Package::vEdge& e, std::ostream& os) {
        auto nodelabel = (reinterpret_cast<uintptr_t>(e.p) & 0x001fffffU) >> 1U; // this allows for 2^20 (roughly 1e6) unique nodes
        os << nodelabel << "[label=<";
        os << R"(<font point-size="8"><table border="1" cellspacing="0" cellpadding="0" style="rounded">)";
        os << R"(<tr><td colspan="2" border="0" cellpadding="1"><font point-size="20">q<sub><font point-size="12">)" << static_cast<std::size_t>(e.p->v) << R"(</font></sub></font></td></tr><tr>)";
        os << R"(<td height="6" width="14" port="0" tooltip=")" << e.p->e[0].w << R"(" href="javascript:;" sides="RT">)" << (CN::equalsZero(e.p->e[0].w) ? "&nbsp;0 " : R"(<font color="white">&nbsp;0 </font>)") << "</td>";
        os << R"(<td height="6" width="14" port="1" tooltip=")" << e.p->e[1].w << R"(" href="javascript:;" sides="LT">)" << (CN::equalsZero(e.p->e[1].w) ? "&nbsp;0 " : R"(<font color="white">&nbsp;0 </font>)") << "</td>";
        os << "</tr></table></font>>,tooltip=\"q" << static_cast<std::size_t>(e.p->v) << "\"]\n";
        return os;
    }

    std::ostream& classicNode(const Package::vEdge& e, std::ostream& os) {
        auto nodelabel = (reinterpret_cast<uintptr_t>(e.p) & 0x001fffffU) >> 1U; // this allows for 2^20 (roughly 1e6) unique nodes
        os << nodelabel << "[shape=circle, width=0.46, fixedsize=true, label=<";
        os << R"(<font point-size="6"><table border="0" cellspacing="0" cellpadding="0">)";
        os << R"(<tr><td colspan="2"><font point-size="18">q<sub><font point-size="10">)" << static_cast<std::size_t>(e.p->v) << R"(</font></sub></font></td></tr><tr>)";
        os << R"(<td port="0" tooltip=")" << e.p->e[0].w << R"(" href="javascript:;">)";
        if (CN::equalsZero(e.p->e[0].w)) {
            os << R"(<font point-size="10">&nbsp;0 </font>)";
        } else {
            os << R"(<font color="white">&nbsp;0 </font>)";
        }
        os << "</td>";
        os << R"(<td port="1" tooltip=")" << e.p->e[1].w << R"(" href="javascript:;">)";
        if (CN::equalsZero(e.p->e[1].w)) {
            os << R"(<font point-size="10">&nbsp;0 </font>)";
        } else {
            os << R"(<font color="white">&nbsp;0 </font>)";
        }
        os << "</td>";
        os << "</tr></table></font>>,tooltip=\"q" << static_cast<std::size_t>(e.p->v) << "\"]\n";
        return os;
    }

    std::ostream& classicEdge(const Package::mEdge& from, const Package::mEdge& to, short idx, std::ostream& os, bool edgeLabels) {
        auto fromlabel = (reinterpret_cast<uintptr_t>(from.p) & 0x001fffffU) >> 1U;
        auto tolabel   = (reinterpret_cast<uintptr_t>(to.p) & 0x001fffffU) >> 1U;

        os << fromlabel << ":" << idx << ":";
        if (idx == 0)
            os << "sw";
        else if (idx == 1 || idx == 2)
            os << "s";
        else
            os << "se";

        os << "->";
        if (to.isTerminal()) {
            os << "t";
        } else {
            os << tolabel;
        }

        auto mag = thicknessFromMagnitude(to.w);
        os << "[penwidth=\"" << mag << "\",tooltip=\"" << to.w << "\"";
        if (!CN::equalsOne(to.w)) {
            os << ",style=dashed";
        }
        if (edgeLabels) {
            os << ",label=<<font point-size=\"8\">&nbsp;" << to.w << "</font>>";
        }
        os << "]\n";

        return os;
    }

    std::ostream& coloredEdge(const Package::mEdge& from, const Package::mEdge& to, short idx, std::ostream& os, bool edgeLabels) {
        auto fromlabel = (reinterpret_cast<uintptr_t>(from.p) & 0x001fffffU) >> 1U;
        auto tolabel   = (reinterpret_cast<uintptr_t>(to.p) & 0x001fffffU) >> 1U;

        os << fromlabel << ":" << idx << ":";
        if (idx == 0)
            os << "sw";
        else if (idx == 1)
            os << "se";
        else
            os << 's';
        os << "->";
        if (to.isTerminal()) {
            os << "t";
        } else {
            os << tolabel << ":n";
        }

        auto mag   = thicknessFromMagnitude(to.w);
        auto color = colorFromPhase(to.w);
        os << "[penwidth=\"" << mag << "\",tooltip=\"" << to.w << "\" color=\"#" << color << "\"";
        if (edgeLabels) {
            os << ",label=<<font point-size=\"8\">&nbsp;" << to.w << "</font>>";
        }
        os << "]\n";

        return os;
    }

    std::ostream& classicEdge(const Package::vEdge& from, const Package::vEdge& to, short idx, std::ostream& os, bool edgeLabels) {
        auto fromlabel = (reinterpret_cast<uintptr_t>(from.p) & 0x001fffffU) >> 1U;
        auto tolabel   = (reinterpret_cast<uintptr_t>(to.p) & 0x001fffffU) >> 1U;

        os << fromlabel << ":" << idx << ":";
        os << (idx == 0 ? "sw" : "se") << "->";
        if (to.isTerminal()) {
            os << "t";
        } else {
            os << tolabel;
        }

        auto mag = thicknessFromMagnitude(to.w);
        os << "[penwidth=\"" << mag << "\",tooltip=\"" << to.w << "\"";
        if (!CN::equalsOne(to.w)) {
            os << ",style=dashed";
        }
        if (edgeLabels) {
            os << ",label=<<font point-size=\"8\">&nbsp;" << to.w << "</font>>";
        }
        os << "]\n";

        return os;
    }

    std::ostream& coloredEdge(const Package::vEdge& from, const Package::vEdge& to, short idx, std::ostream& os, bool edgeLabels) {
        auto fromlabel = (reinterpret_cast<uintptr_t>(from.p) & 0x001fffffU) >> 1U;
        auto tolabel   = (reinterpret_cast<uintptr_t>(to.p) & 0x001fffffU) >> 1U;

        os << fromlabel << ":" << idx << ":";
        os << (idx == 0 ? "sw" : "se") << "->";
        if (to.isTerminal()) {
            os << "t";
        } else {
            os << tolabel;
        }

        auto mag   = thicknessFromMagnitude(to.w);
        auto color = colorFromPhase(to.w);
        os << "[penwidth=\"" << mag << "\",tooltip=\"" << to.w << "\" color=\"#" << color << "\"";
        if (edgeLabels) {
            os << ",label=<<font point-size=\"8\">&nbsp;" << to.w << "</font>>";
        }
        os << "]\n";

        return os;
    }

    void serializeMatrix(const Package::mEdge& basic, std::int_fast64_t& idx, std::unordered_map<Package::mNode*, std::int_fast64_t>& node_index, std::unordered_set<Package::mNode*>& visited, std::ostream& os, bool writeBinary) {
        if (!basic.isTerminal()) {
            for (auto& e: basic.p->e) {
                if (auto [iter, success] = visited.insert(e.p); success) {
                    serializeMatrix(e, idx, node_index, visited, os, writeBinary);
                }
            }

            if (node_index.find(basic.p) == node_index.end()) {
                node_index[basic.p] = idx;
                ++idx;
            }

            if (writeBinary) {
                os.write(reinterpret_cast<const char*>(&node_index[basic.p]), sizeof(std::int_fast64_t));
                os.write(reinterpret_cast<const char*>(&basic.p->v), sizeof(Qubit));

                // iterate over edges in reverse to guarantee correct processing order
                for (auto& edge: basic.p->e) {
                    std::int_fast64_t edge_idx = edge.isTerminal() ? -1 : node_index[edge.p];
                    os.write(reinterpret_cast<const char*>(&edge_idx), sizeof(std::int_fast64_t));
                    writeBinaryAmplitude(os, edge.w);
                }
            } else {
                os << node_index[basic.p] << " " << static_cast<std::size_t>(basic.p->v);

                // iterate over edges in reverse to guarantee correct processing order
                for (auto& edge: basic.p->e) {
                    os << " (";
                    if (!CN::equalsZero(edge.w)) {
                        std::int_fast64_t edge_idx = edge.isTerminal() ? -1 : node_index[edge.p];
                        os << edge_idx << " " << CN::toString(edge.w, false, 16);
                    }
                    os << ")";
                }
                os << "\n";
            }
        }
    }

    void serialize(const Package::vEdge& basic, std::ostream& os, bool writeBinary) {
        if (writeBinary) {
            os.write(reinterpret_cast<const char*>(&SERIALIZATION_VERSION), sizeof(fp));
            writeBinaryAmplitude(os, basic.w);
        } else {
            os << SERIALIZATION_VERSION << "\n";
            os << CN::toString(basic.w, false, 16) << "\n";
        }
        std::int_fast64_t                                      next_index = 0;
        std::unordered_map<Package::vNode*, std::int_fast64_t> node_index{};

        // POST ORDER TRAVERSAL USING ONE STACK   https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
        std::stack<const Package::vEdge*> stack{};

        auto node = &basic;
        if (!node->isTerminal()) {
            do {
                while (node != nullptr && !node->isTerminal()) {
                    for (short i = RADIX - 1; i > 0; --i) {
                        auto& edge = node->p->e[i];
                        if (edge.isTerminal()) continue;
                        if (CN::equalsZero(edge.w)) continue;
                        if (node_index.find(edge.p) != node_index.end()) continue;

                        // non-zero edge to be included
                        stack.push(&edge);
                    }
                    stack.push(node);
                    node = &node->p->e[0];
                }
                node = stack.top();
                stack.pop();

                bool hasChild = false;
                for (auto i = 1U; i < RADIX && !hasChild; ++i) {
                    auto& edge = node->p->e[i];
                    if (CN::equalsZero(edge.w)) continue;
                    if (node_index.find(edge.p) != node_index.end()) continue;
                    if (!stack.empty())
                        hasChild = edge.p == stack.top()->p;
                }

                if (hasChild) {
                    const auto temp = stack.top();
                    stack.pop();
                    stack.push(node);
                    node = temp;
                } else {
                    if (node_index.find(node->p) != node_index.end()) {
                        node = nullptr;
                        continue;
                    }
                    node_index[node->p] = next_index;
                    next_index++;

                    if (writeBinary) {
                        os.write(reinterpret_cast<const char*>(&node_index[node->p]), sizeof(std::int_fast64_t));
                        os.write(reinterpret_cast<const char*>(&node->p->v), sizeof(Qubit));

                        // iterate over edges in reverse to guarantee correct processing order
                        for (auto i = 0U; i < RADIX; ++i) {
                            auto&             edge     = node->p->e[i];
                            std::int_fast64_t edge_idx = edge.isTerminal() ? -1 : node_index[edge.p];
                            os.write(reinterpret_cast<const char*>(&edge_idx), sizeof(std::int_fast64_t));
                            writeBinaryAmplitude(os, edge.w);
                        }
                    } else {
                        os << node_index[node->p] << " " << static_cast<std::size_t>(node->p->v);

                        // iterate over edges in reverse to guarantee correct processing order
                        for (auto i = 0U; i < RADIX; ++i) {
                            os << " (";
                            auto& edge = node->p->e[i];
                            if (!CN::equalsZero(edge.w)) {
                                std::int_fast64_t edge_idx = edge.isTerminal() ? -1 : node_index[edge.p];
                                os << edge_idx << " " << CN::toString(edge.w, false, 16);
                            }
                            os << ")";
                        }
                        os << "\n";
                    }
                    node = nullptr;
                }
            } while (!stack.empty());
        }
    }

    void serialize(const Package::mEdge& basic, std::ostream& os, bool writeBinary) {
        if (writeBinary) {
            os.write(reinterpret_cast<const char*>(&SERIALIZATION_VERSION), sizeof(fp));
            writeBinaryAmplitude(os, basic.w);
        } else {
            os << SERIALIZATION_VERSION << "\n";
            os << CN::toString(basic.w, false, 16) << "\n";
        }
        std::int_fast64_t                                      idx = 0;
        std::unordered_map<Package::mNode*, std::int_fast64_t> node_index{};
        std::unordered_set<Package::mNode*>                    visited{};
        serializeMatrix(basic, idx, node_index, visited, os, writeBinary);
    }
} // namespace dd
