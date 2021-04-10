/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDexport_H
#define DDexport_H

#include "DDpackage.hpp"

#include <iomanip>
#include <regex>
#include <unordered_map>

namespace dd {

    struct RGB {
        fp R = 0., G = 0., B = 0.;
        RGB(fp R, fp G, fp B):
            R(R), G(G), B(B){};

        std::ostream& printHex(std::ostream& os) const {
            std::ostringstream oss{};
            oss.flags(std::ios_base::hex);
            oss.fill('0');
            oss << std::setw(2) << static_cast<short>(R * 255.) << std::setw(2) << static_cast<short>(G * 255.) << std::setw(2) << static_cast<short>(B * 255.);
            os << oss.str();
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const RGB& rgb) {
            return rgb.printHex(os);
        }
    };

    fp  hueToRGB(fp hue);
    RGB hlsToRGB(const fp& h, const fp& l, const fp& s);

    RGB colorFromPhase(const Complex& a);
    fp  thicknessFromMagnitude(const Complex& a);

    template<class Edge>
    std::ostream& header(const Edge& e, std::ostream& os, bool edgeLabels) {
        os << "digraph \"DD\" {graph[];node[shape=plain];edge[arrowhead=none]\n";
        os << "root [label=\"\",shape=point,style=invis]\n";
        os << "t [label=<<font point-size=\"20\">1</font>>,shape=box,tooltip=\"1\",width=0.3,height=0.3]\n";
        auto toplabel = (reinterpret_cast<uintptr_t>(e.p) & 0x001fffffU) >> 1U;
        auto mag      = thicknessFromMagnitude(e.w);
        os << "root->";
        if (dd::Package::isTerminal(e)) {
            os << "t";
        } else {
            os << toplabel;
        }
        os << "[penwidth=\"" << mag << "\",tooltip=\"" << e.w << "\"";
        if (!CN::equalsOne(e.w)) {
            os << ",style=dashed";
        }
        if (edgeLabels) {
            os << ",label=<<font point-size=\"8\">&nbsp;" << e.w << "</font>>";
        }

        os << "]\n";

        return os;
    }
    template<class Edge>
    std::ostream& coloredHeader(const Edge& e, std::ostream& os, bool edgeLabels) {
        os << "digraph \"DD\" {graph[];node[shape=plain];edge[arrowhead=none]\n";
        os << "root [label=\"\",shape=point,style=invis]\n";
        os << "t [label=<<font point-size=\"20\">1</font>>,shape=box,tooltip=\"1\",width=0.3,height=0.3]\n";

        auto toplabel = (reinterpret_cast<uintptr_t>(e.p) & 0x001fffffU) >> 1U;
        auto mag      = thicknessFromMagnitude(e.w);
        auto color    = colorFromPhase(e.w);
        os << "root->";
        if (dd::Package::isTerminal(e)) {
            os << "t";
        } else {
            os << toplabel;
        }
        os << "[penwidth=\"" << mag << "\",tooltip=\"" << e.w << "\",color=\"#" << color << "\"";
        if (edgeLabels) {
            os << ",label=<<font point-size=\"8\">&nbsp;" << e.w << "</font>>";
        }
        os << "]\n";
        return os;
    }

    std::ostream& modernNode(const Package::mEdge& e, std::ostream& os);
    std::ostream& modernNode(const Package::vEdge& e, std::ostream& os);
    std::ostream& classicNode(const Package::mEdge& e, std::ostream& os);
    std::ostream& classicNode(const Package::vEdge& e, std::ostream& os);

    std::ostream& classicEdge(const Package::mEdge& from, const Package::mEdge& to, short idx, std::ostream& os, bool edgeLabels = false, bool classic = false);
    std::ostream& classicEdge(const Package::vEdge& from, const Package::vEdge& to, short idx, std::ostream& os, bool edgeLabels = false);
    std::ostream& coloredEdge(const Package::mEdge& from, const Package::mEdge& to, short idx, std::ostream& os, bool edgeLabels = false, bool classic = false);
    std::ostream& coloredEdge(const Package::vEdge& from, const Package::vEdge& to, short idx, std::ostream& os, bool edgeLabels = false);

    template<class Edge>
    void toDot(const Edge& e, std::ostream& os, bool colored = true, bool edgeLabels = false, bool classic = false) {
        std::ostringstream oss{};
        // header, root and terminal declaration

        if (colored) {
            coloredHeader(e, oss, edgeLabels);
        } else {
            header(e, oss, edgeLabels);
        }

        std::unordered_set<decltype(e.p)> nodes{};

        auto priocmp = [](const Edge* left, const Edge* right) { return left->p->v < right->p->v; };

        std::priority_queue<const Edge*, std::vector<const Edge*>, decltype(priocmp)> q(priocmp);
        q.push(&e);

        // bfs until finished
        while (!q.empty()) {
            auto node = q.top();
            q.pop();

            // base case
            if (Package::isTerminal(*node))
                continue;

            // check if node has already been processed
            auto ret = nodes.emplace(node->p);
            if (!ret.second) continue;

            // node definition as HTML-like label (href="javascript:;" is used as workaround to make tooltips work)
            if (classic) {
                classicNode(*node, oss);
            } else {
                modernNode(*node, oss);
            }

            // iterate over edges in reverse to guarantee correct proceossing order
            for (auto i = static_cast<Qubit>(node->p->e.size() - 1); i >= 0; --i) {
                auto& edge = node->p->e[i];
                if (CN::equalsZero(edge.w)) {
                    // potentially add zero stubs here
                    continue;
                }

                // non-zero edge to be included
                q.push(&edge);

                if (colored) {
                    coloredEdge(*node, edge, i, oss, edgeLabels);
                } else {
                    classicEdge(*node, edge, i, oss, edgeLabels);
                }
            }
        }
        oss << "}\n";

        os << oss.str() << std::flush;
    }

    template<class Edge>
    void export2Dot(Edge basic, const std::string& outputFilename, bool colored = true, bool edgeLabels = false, bool classic = false, bool show = true) {
        std::ofstream init(outputFilename);
        toDot(basic, init, colored, edgeLabels, classic);
        init.close();

        if (show) {
            std::ostringstream oss;
            oss << "dot -Tsvg " << outputFilename << " -o " << outputFilename.substr(0, outputFilename.find_last_of('.')) << ".svg";
            auto                  str = oss.str(); // required to avoid immediate deallocation of temporary
            [[maybe_unused]] auto rc  = std::system(str.c_str());
        }
    }

    ComplexValue toComplexValue(const std::string& real_str, std::string imag_str);
    ComplexValue readBinaryAmplitude(std::istream& is);
    void         writeBinaryAmplitude(std::ostream& os, const Complex& w);

    void serialize(const Package::vEdge& basic, std::ostream& os, bool writeBinary = false);
    void serialize(const Package::mEdge& basic, std::ostream& os, bool writeBinary = false);
    void serializeMatrix(const Package::mEdge& basic, std::int_fast64_t& idx, std::unordered_map<Package::mNode*, std::int_fast64_t>& node_index, std::unordered_set<Package::mNode*>& visited, std::ostream& os, bool writeBinary = false);

    template<class Edge>
    void serialize(const Edge& basic, const std::string& outputFilename, bool writeBinary = false) {
        std::ofstream ofs(outputFilename);

        if (!ofs.good()) {
            std::cerr << "Cannot open file: " << outputFilename << std::endl;
            return;
        }

        serialize(basic, ofs, writeBinary);
    }

    Package::vEdge createDeserializedNode(std::unique_ptr<Package>& dd, std::int_fast64_t index, Qubit v, std::array<std::int_fast64_t, RADIX>& edge_idx, std::array<ComplexValue, RADIX>& edge_weight, std::unordered_map<std::int_fast64_t, Package::vNode*>& nodes);
    Package::mEdge createDeserializedNode(std::unique_ptr<Package>& dd, std::int_fast64_t index, Qubit v, std::array<std::int_fast64_t, NEDGE>& edge_idx, std::array<ComplexValue, NEDGE>& edge_weight, std::unordered_map<std::int_fast64_t, Package::mNode*>& nodes);

    // isVector only used if readBinary is true
    Package::vEdge deserializeVector(std::unique_ptr<dd::Package>& dd, std::istream& is, bool readBinary = false);
    Package::vEdge deserializeVector(std::unique_ptr<dd::Package>& dd, const std::string& inputFilename, bool readBinary = false);
    Package::mEdge deserializeMatrix(std::unique_ptr<dd::Package>& dd, std::istream& is, bool readBinary = false);
    Package::mEdge deserializeMatrix(std::unique_ptr<dd::Package>& dd, const std::string& inputFilename, bool readBinary = false);

} // namespace dd

#endif //DDexport_H
