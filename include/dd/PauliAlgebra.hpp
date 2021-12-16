//
// Created by lieuwe on 13/12/2021.
//

#ifndef DDPACKAGE_PAULIALGEBRA_HPP
#define DDPACKAGE_PAULIALGEBRA_HPP

#include "Edge.hpp"
#include "LimTable.hpp"

// note: my package won't compile unless I put my functions in a class
// for now, I've called this class Pauli
// - Lieuwe

namespace dd {

typedef std::vector<LimEntry<>*> StabilizerGroup;

class Pauli {
public:

    static StabilizerGroup groupConcatenate(const StabilizerGroup& G, const StabilizerGroup& H) {
        StabilizerGroup concat = G;
        for (unsigned int i=0; i<H.size(); i++) {
            concat.push_back(H[i]);
        }
        return concat;
    }

    // This function does nothing; it just 'catches' the mNode case
//    static LimEntry<>* highLabelZ(const mNode u, const mNode v, LimEntry<>* vLabel) {
//        return vlabel;
//    }

    // Returns the LIM a * b
    static LimEntry<>* multiply(const LimEntry<>& a, const LimEntry<>& b) {
        LimEntry<>* c = LimEntry<>::getIdentityOperator();
        c->multiplyBy(a);
        c->multiplyBy(b);
        return c;
    }

    static StabilizerGroup deepcopy(const StabilizerGroup& G) {
        StabilizerGroup copy;
        for (unsigned int i=0; i<G.size(); i++) {
            copy.push_back(new LimEntry<>(G[i]));
        }
        return copy;
    }

    // Appends an Identity matrix below the group G, i.e., returns the matrix
    //   [ G  ]
    //   [ Id ]
    static StabilizerGroup appendIdentityMatrix(const StabilizerGroup& G, unsigned int height) {
        StabilizerGroup GI = deepcopy(G);
        for (unsigned int i=0; i<G.size(); i++) {
            // Make column G[i][height ... height + width-1] into the column [0 ...0 1 0 ... 0]
            for (unsigned int h=height; h<height + i; h++) {
                GI[i]->paulis.set(h, 0);
            }
            GI[i]->paulis.set(height+i, 1);
            for (unsigned int h=height+i+1; h<G.size(); h++) {
                GI[i]->paulis.set(h, 0);
            }
        }
        return GI;
    }

    // Performs Gaussian elimination on G
    // We assume that G is not stored in the LimTable.
    // In more detail: the elements of G are modified in place
    // Therefore, the LimEntry objects should NOT be stored in the LimTable;
    template <std::size_t NUM_QUBITS>
    static void GaussianElimination(const std::vector<LimEntry<NUM_QUBITS>*>& G) {
        if (G.size() <= 1) return;
        unsigned int pauli_height = 2*NUM_QUBITS; // length of the columns as far as they contain Pauli operators
        unsigned int reducingColId;
        for (unsigned int h=0; h<pauli_height; h++) {
            // Step 1: Find a column with a '1' at position h
            reducingColId = -1;
            for (unsigned int i=0; i<G.size(); i++) {
                if (G[i]->paulis.test(h)) {
                    reducingColId = i;
                    break;
                }
            }
            if (reducingColId == -1) continue;
            // Step 2: Reduce all other columns via G[reducingColId]
            for (unsigned int reduceColId =0; reduceColId < G.size(); reduceColId++) {
                if (reduceColId == reducingColId) continue;
                if (G[reduceColId]->paulis.test(h)) {
                    G[reduceColId]->multiplyBy(*G[reducingColId]);
                }
            }
        }
    }

    // Puts the stabilizer group in column echelon form; specifically:
    //   1. performs Gaussian elimination on G
    //   2. prunes the all-zero columns
    //   3. sorts the columns lexicographically, i.e., so that 'pivots' appear in the matrix
    static void toColumnEchelonForm(StabilizerGroup& G) {
        GaussianElimination(G);
        // prune all-zero columns
        std::sort(G.begin(), G.end(), LimEntry<>::leq);
    }

    // Reduces a vector 'x' via a group 'G' via the Gram-Schmidt procedure
    // Returns the reduced vector
    template<std::size_t NUM_QUBITS>
    static LimEntry<NUM_QUBITS>* GramSchmidt(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<>* x) {
        LimEntry<>* y = new LimEntry<>(x);
        if (G.size() == 0) return y;
        std::size_t height = 2*NUM_QUBITS;
        for (unsigned int h=0; h<height; h++) {
            // Look for a vector with a '1' in place h
            for (unsigned int v=0; v<G.size(); v++) {
                if (G[v]->paulis.test(h)) {
                    y = Pauli::multiply(y, G[v]);
                }
            }
        }
        return y;
    }

    // Interprets G as a 0/1 matrix, where each operator (i.e., LimEntry object) forms a column
    // returns the kernel of G in column echelon form
    static StabilizerGroup getKernelZ(const StabilizerGroup& G, unsigned int nqubits) {
        StabilizerGroup kernel;
        unsigned int width = G.size();  // minor note: size of G may change during toColumnEchelonForm(G)
        StabilizerGroup GI = appendIdentityMatrix(G, nqubits);
        toColumnEchelonForm(GI);
        for (unsigned int i=0; i<GI.size(); i++) {
            // Copy bits [2*nqubits ... 2*nqubits + width -1] to kernel[i][0 ... width-1]
            kernel.push_back(new LimEntry<>());
            for (unsigned int b=0; b<width; b++) {
                kernel[i]->paulis.set(b, GI[i]->paulis.test(2*nqubits+b));
            }
        }
        toColumnEchelonForm(kernel);
        return kernel;
    }

    static StabilizerGroup intersectGroupsZ(const StabilizerGroup& G, const StabilizerGroup& H, unsigned int nqubits) {
        StabilizerGroup intersection;
        StabilizerGroup concat = groupConcatenate(G, H);
        StabilizerGroup kernel = getKernelZ(concat, nqubits);
        LimEntry<>* g;
        for (unsigned int i=0; i<kernel.size(); i++) {
            g = LimEntry<>::getIdentityOperator();
            for (unsigned int j=0; j<G.size(); j++) {
                if (kernel[i]->paulis.test(j)) {
                    g->multiplyBy(*G[j]);
                }
            }
            intersection.push_back(g);
        }

        return intersection;
    }

    // For now, we assume that only vNodes are passed
    template <class Node>
    static std::vector<dd::LimTable<>::Entry*> constructStabilizerGeneratorSet(const Node v) {
        //empty
        Node* low, high;
        low = v.e[0];
        high = v.e[1];

        std::vector<dd::LimTable<>::Entry*> stabgenset;


        return stabgenset;
    }

    // Choose the label on the High edge, in the Z group
    template <class Node>
    static LimEntry<>* highLabelZ(const Node* u, const Node* v, LimEntry<>* vLabel) {
        LimEntry<>* l = LimEntry<>::getIdentityOperator();
        unsigned int nqubits = u->v;
        StabilizerGroup intersect = intersectGroupsZ(u->limVector, v->limVector, nqubits);

        return l;
    }

    template <class Node>
    static LimEntry<>* getIsomorphismZ(const Node* u, const Node* v) {
        LimEntry<>* iso = nullptr;

        return iso;
    }

};



} // namespace dd
#endif //DDPACKAGE_PAULIALGEBRA_HPP
