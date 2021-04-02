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

    ComplexValue toComplexValue(const std::string& real_str, std::string imag_str) {
        fp real = real_str.empty() ? 0. : std::stod(real_str);

        imag_str.erase(remove(imag_str.begin(), imag_str.end(), ' '), imag_str.end());
        imag_str.erase(remove(imag_str.begin(), imag_str.end(), 'i'), imag_str.end());
        if (imag_str == "+" || imag_str == "-") imag_str = imag_str + "1";
        fp imag = imag_str.empty() ? 0. : std::stod(imag_str);
        return ComplexValue{real, imag};
    }

    ComplexValue readBinaryAmplitude(std::istream& is) {
        ComplexValue temp{};
        is.read(reinterpret_cast<char*>(&temp.r), sizeof(fp));
        is.read(reinterpret_cast<char*>(&temp.i), sizeof(fp));
        return temp;
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

    std::ostream& classicEdge(const Package::mEdge& from, const Package::mEdge& to, short idx, std::ostream& os, bool edgeLabels, bool classic) {
        auto fromlabel = (reinterpret_cast<uintptr_t>(from.p) & 0x001fffffU) >> 1U;
        auto tolabel   = (reinterpret_cast<uintptr_t>(to.p) & 0x001fffffU) >> 1U;

        os << fromlabel << ":" << idx << ":";
        if (classic) {
            if (idx == 0)
                os << "sw";
            else if (idx == 1 || idx == 2)
                os << "s";
            else
                os << "se";
        } else {
            if (idx == 0)
                os << "sw";
            else if (idx == 1)
                os << "se";
            else
                os << 's';
        }
        os << "->";
        if (Package::isTerminal(to)) {
            os << "t";
        } else {
            os << tolabel;
            if (!classic)
                os << ":n";
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

    std::ostream& coloredEdge(const Package::mEdge& from, const Package::mEdge& to, short idx, std::ostream& os, bool edgeLabels, bool classic) {
        auto fromlabel = (reinterpret_cast<uintptr_t>(from.p) & 0x001fffffU) >> 1U;
        auto tolabel   = (reinterpret_cast<uintptr_t>(to.p) & 0x001fffffU) >> 1U;

        os << fromlabel << ":" << idx << ":";
        if (classic) {
            if (idx == 0)
                os << "sw";
            else if (idx == 1 || idx == 2)
                os << "s";
            else
                os << "se";
        } else {
            if (idx == 0)
                os << "sw";
            else if (idx == 1)
                os << "se";
            else
                os << 's';
        }
        os << "->";
        if (Package::isTerminal(to)) {
            os << "t";
        } else {
            os << tolabel;
            if (!classic)
                os << ":n";
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
        if (Package::isTerminal(to)) {
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
        if (Package::isTerminal(to)) {
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
        if (!dd::Package::isTerminal(basic)) {
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
                    std::int_fast64_t edge_idx = Package::isTerminal(edge) ? -1 : node_index[edge.p];
                    os.write(reinterpret_cast<const char*>(&edge_idx), sizeof(std::int_fast64_t));
                    writeBinaryAmplitude(os, edge.w);
                }
            } else {
                os << node_index[basic.p] << " " << static_cast<std::size_t>(basic.p->v);

                // iterate over edges in reverse to guarantee correct processing order
                for (auto& edge: basic.p->e) {
                    os << " (";
                    if (!CN::equalsZero(edge.w)) {
                        std::int_fast64_t edge_idx = Package::isTerminal(edge) ? -1 : node_index[edge.p];
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
        if (!Package::isTerminal(*node)) {
            do {
                while (node != nullptr && !Package::isTerminal(*node)) {
                    for (short i = RADIX - 1; i > 0; --i) {
                        auto& edge = node->p->e[i];
                        if (Package::isTerminal(edge)) continue;
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
                            std::int_fast64_t edge_idx = Package::isTerminal(edge) ? -1 : node_index[edge.p];
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
                                std::int_fast64_t edge_idx = Package::isTerminal(edge) ? -1 : node_index[edge.p];
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

    Package::vEdge createDeserializedNode(std::unique_ptr<Package>& dd, std::int_fast64_t index, Qubit v, std::array<std::int_fast64_t, RADIX>& edge_idx, std::array<ComplexValue, RADIX>& edge_weight, std::unordered_map<std::int_fast64_t, Package::vNode*>& nodes) {
        if (index == -1) {
            return dd->makeVectorTerminal(CN::ZERO);
        }

        std::array<Package::vEdge, RADIX> edges{};
        for (auto i = 0U; i < RADIX; ++i) {
            if (edge_idx[i] == -2) {
                edges[i] = dd->makeVectorTerminal(CN::ZERO);
            } else {
                if (edge_idx[i] == -1) {
                    edges[i] = dd->makeVectorTerminal(CN::ONE);
                } else {
                    edges[i].p = nodes[edge_idx[i]];
                }
                edges[i].w = dd->cn.lookup(edge_weight[i]);
            }
        }

        auto newedge = dd->makeVectorNode(v, edges);
        nodes[index] = newedge.p;

        // reset
        edge_idx.fill(-2);

        return newedge;
    }

    Package::mEdge createDeserializedNode(std::unique_ptr<Package>& dd, std::int_fast64_t index, Qubit v, std::array<std::int_fast64_t, NEDGE>& edge_idx, std::array<ComplexValue, NEDGE>& edge_weight, std::unordered_map<std::int_fast64_t, Package::mNode*>& nodes) {
        if (index == -1) {
            return dd->makeMatrixTerminal(CN::ZERO);
        }

        std::array<Package::mEdge, NEDGE> edges{};
        for (auto i = 0U; i < NEDGE; ++i) {
            if (edge_idx[i] == -2) {
                edges[i] = dd->makeMatrixTerminal(CN::ZERO);
            } else {
                if (edge_idx[i] == -1) {
                    edges[i] = dd->makeMatrixTerminal(CN::ONE);
                } else {
                    edges[i].p = nodes[edge_idx[i]];
                }
                edges[i].w = dd->cn.lookup(edge_weight[i]);
            }
        }

        auto newedge = dd->makeMatrixNode(v, edges);
        nodes[index] = newedge.p;

        // reset
        edge_idx.fill(-2);

        return newedge;
    }

    Package::vEdge deserializeVector(std::unique_ptr<dd::Package>& dd, std::istream& is, bool readBinary) {
        auto         result = dd->makeVectorTerminal(CN::ZERO);
        ComplexValue rootweight{};

        std::unordered_map<std::int_fast64_t, Package::vNode*> nodes{};
        std::int_fast64_t                                      node_index;
        Qubit                                                  v;
        std::array<std::int_fast64_t, RADIX>                   edge_indices{};
        edge_indices.fill(-2);
        std::array<ComplexValue, RADIX> edge_weights{};

        if (readBinary) {
            double version;
            is.read(reinterpret_cast<char*>(&version), sizeof(double));
            if (version != SERIALIZATION_VERSION) {
                throw std::runtime_error("Wrong Version of serialization file version. version of file: " + std::to_string(version) + "; current version: " + std::to_string(SERIALIZATION_VERSION));
            }

            if (!is.eof()) {
                rootweight = readBinaryAmplitude(is);
            }

            while (is.read(reinterpret_cast<char*>(&node_index), sizeof(std::int_fast64_t))) {
                is.read(reinterpret_cast<char*>(&v), sizeof(Qubit));
                for (auto i = 0U; i < RADIX; i++) {
                    is.read(reinterpret_cast<char*>(&edge_indices[i]), sizeof(std::int_fast64_t));
                    edge_weights[i] = readBinaryAmplitude(is);
                }
                result = createDeserializedNode(dd, node_index, v, edge_indices, edge_weights, nodes);
            }
        } else {
            std::string version;
            std::getline(is, version);
            // ifs >> version;
            if (std::stod(version) != SERIALIZATION_VERSION) {
                throw std::runtime_error("Wrong Version of serialization file version. version of file: " + version + "; current version: " + std::to_string(SERIALIZATION_VERSION));
            }

            std::string line;
            std::string complex_real_regex = R"(([+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?(?![ \d\.]*(?:[eE][+-])?\d*[iI]))?)";
            std::string complex_imag_regex = R"(( ?[+-]? ?(?:(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)?[iI])?)";
            std::string edge_regex         = " \\(((-?\\d+) (" + complex_real_regex + complex_imag_regex + "))?\\)";
            std::regex  complex_weight_regex(complex_real_regex + complex_imag_regex);
            std::regex  line_regex("(\\d+) (\\d+)(?:" + edge_regex + ")(?:" + edge_regex + ") *(?:#.*)?");
            // std::regex e ("(\\d+) (\\d+)(?:" + edge_regex + "){4} *#.*"); // TODO {4} overwrites groups
            std::smatch m;

            if (std::getline(is, line)) {
                if (!std::regex_match(line, m, complex_weight_regex)) {
                    throw std::runtime_error("Regex did not match second line: " + line);
                }
                rootweight = toComplexValue(m.str(1), m.str(2));
            }
            // std::cout << "rootweight = " << rootweight << std::endl;

            while (std::getline(is, line)) {
                if (line.empty() || line.size() == 1) continue;

                if (!std::regex_match(line, m, line_regex)) {
                    throw std::runtime_error("Regex did not match line: " + line);
                }

                // match 1: node_idx
                // match 2: qubit_idx

                // repeats for every edge
                // match 3: edge content
                // match 4: edge_target_idx
                // match 5: real + imag (without i)
                // match 6: real
                // match 7: imag (without i)
                node_index = std::stoll(m.str(1));
                v          = static_cast<Qubit>(std::stoi(m.str(2)));

                // std::cout << "nidx: " << node_index << " v: " << v << std::endl;

                if (!m.str(3).empty()) {
                    edge_indices[0] = std::stoll(m.str(4));
                    edge_weights[0] = toComplexValue(m.str(6), m.str(7));
                }
                if (!m.str(8).empty()) {
                    edge_indices[1] = std::stoll(m.str(9));
                    edge_weights[1] = toComplexValue(m.str(11), m.str(12));
                }
                result = createDeserializedNode(dd, node_index, v, edge_indices, edge_weights, nodes);
            }
        }

        Complex w = dd->cn.getCachedComplex(rootweight.r, rootweight.i);
        CN::mul(w, result.w, w);
        result.w = dd->cn.lookup(w);
        dd->cn.releaseCached(w);

        return result;
    }

    Package::mEdge deserializeMatrix(std::unique_ptr<dd::Package>& dd, std::istream& is, bool readBinary) {
        auto         result = dd->makeMatrixTerminal(CN::ZERO);
        ComplexValue rootweight{};

        std::unordered_map<std::int_fast64_t, Package::mNode*> nodes{};
        std::int_fast64_t                                      node_index;
        Qubit                                                  v;
        std::array<std::int_fast64_t, NEDGE>                   edge_indices{};
        edge_indices.fill(-2);
        std::array<ComplexValue, NEDGE> edge_weights{};

        if (readBinary) {
            double version;
            is.read(reinterpret_cast<char*>(&version), sizeof(double));
            if (version != SERIALIZATION_VERSION) {
                throw std::runtime_error("Wrong Version of serialization file version. version of file: " + std::to_string(version) + "; current version: " + std::to_string(SERIALIZATION_VERSION));
            }

            if (!is.eof()) {
                rootweight = readBinaryAmplitude(is);
            }

            while (is.read(reinterpret_cast<char*>(&node_index), sizeof(std::int_fast64_t))) {
                is.read(reinterpret_cast<char*>(&v), sizeof(Qubit));
                for (auto i = 0U; i < NEDGE; i++) {
                    is.read(reinterpret_cast<char*>(&edge_indices[i]), sizeof(std::int_fast64_t));
                    edge_weights[i] = readBinaryAmplitude(is);
                }
                result = createDeserializedNode(dd, node_index, v, edge_indices, edge_weights, nodes);
            }
        } else {
            std::string version;
            std::getline(is, version);
            // ifs >> version;
            if (std::stod(version) != SERIALIZATION_VERSION) {
                throw std::runtime_error("Wrong Version of serialization file version. version of file: " + version + "; current version: " + std::to_string(SERIALIZATION_VERSION));
            }

            std::string line;
            std::string complex_real_regex = R"(([+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?(?![ \d\.]*(?:[eE][+-])?\d*[iI]))?)";
            std::string complex_imag_regex = R"(( ?[+-]? ?(?:(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)?[iI])?)";
            std::string edge_regex         = " \\(((-?\\d+) (" + complex_real_regex + complex_imag_regex + "))?\\)";
            std::regex  complex_weight_regex(complex_real_regex + complex_imag_regex);
            std::regex  line_regex("(\\d+) (\\d+)(?:" + edge_regex + ")(?:" + edge_regex + ")(?:" + edge_regex + ")(?:" + edge_regex + ") *(?:#.*)?");
            // std::regex e ("(\\d+) (\\d+)(?:" + edge_regex + "){4} *#.*"); // TODO {4} overwrites groups
            std::smatch m;

            if (std::getline(is, line)) {
                if (!std::regex_match(line, m, complex_weight_regex)) {
                    throw std::runtime_error("Regex did not match second line: " + line);
                }
                rootweight = toComplexValue(m.str(1), m.str(2));
            }
            // std::cout << "rootweight = " << rootweight << std::endl;

            while (std::getline(is, line)) {
                if (line.empty() || line.size() == 1) continue;

                if (!std::regex_match(line, m, line_regex)) {
                    throw std::runtime_error("Regex did not match line: " + line);
                }

                // match 1: node_idx
                // match 2: qubit_idx

                // repeats for every edge
                // match 3: edge content
                // match 4: edge_target_idx
                // match 5: real + imag (without i)
                // match 6: real
                // match 7: imag (without i)
                node_index = std::stoi(m.str(1));
                v          = static_cast<Qubit>(std::stoi(m.str(2)));

                // std::cout << "nidx: " << node_index << " v: " << v << std::endl;

                for (auto edge_idx = 3U, i = 0U; i < NEDGE; i++, edge_idx += 5) {
                    if (m.str(edge_idx).empty()) {
                        // std::cout << "index " << i << " is empty " << std::endl;
                        continue;
                    }

                    edge_indices[i] = std::stoi(m.str(edge_idx + 1));
                    edge_weights[i] = toComplexValue(m.str(edge_idx + 3), m.str(edge_idx + 4));
                }

                result = createDeserializedNode(dd, node_index, v, edge_indices, edge_weights, nodes);
            }
        }

        Complex w = dd->cn.getCachedComplex(rootweight.r, rootweight.i);
        CN::mul(w, result.w, w);
        result.w = dd->cn.lookup(w);
        dd->cn.releaseCached(w);

        return result;
    }

    Package::vEdge deserializeVector(std::unique_ptr<dd::Package>& dd, const std::string& inputFilename, bool readBinary) {
        auto ifs = std::ifstream(inputFilename);

        if (!ifs.good()) {
            std::cerr << "Cannot open serialized file: " << inputFilename << std::endl;
            return dd->makeVectorTerminal(CN::ZERO);
        }

        return deserializeVector(dd, ifs, readBinary);
    }

    Package::mEdge deserializeMatrix(std::unique_ptr<dd::Package>& dd, const std::string& inputFilename, bool readBinary) {
        auto ifs = std::ifstream(inputFilename);

        if (!ifs.good()) {
            std::cerr << "Cannot open serialized file: " << inputFilename << std::endl;
            return dd->makeMatrixTerminal(CN::ZERO);
        }

        return deserializeMatrix(dd, ifs, readBinary);
    }
} // namespace dd
