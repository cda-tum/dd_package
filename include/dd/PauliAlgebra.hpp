//
// Created by lieuwe on 13/12/2021.
//

#ifndef DDPACKAGE_PAULIALGEBRA_HPP
#define DDPACKAGE_PAULIALGEBRA_HPP

#include "Edge.hpp"
#include "Nodes.hpp"
#include "LimTable.hpp"

#include <iostream>

// note: my package won't compile unless I put my functions in a class
// for now, I've called this class Pauli
// - Lieuwe

namespace dd {

typedef std::vector<LimEntry<>*> StabilizerGroup;

class Pauli {
public:

    // Returns whether the two groups have the same vector of generators
    // Note that, mathematically speaking, two generator sets G and H can still generate the same groups,
    // even if they have different orders
    static bool stabilizerGroupsEqual(const StabilizerGroup& G, const StabilizerGroup& H) {
        std::cout << "[stabilizerGroupsEqual] start.\n";  std::cout.flush();
        if (G.size() != H.size()) return false;
        for (unsigned int i=0; i<G.size(); i++) {
            if (G[i]->operator!=(*H[i])) return false;
        }
        std::cout << "[stabilizerGroupsEqual] groups are equal.\n"; std::cout.flush();
        return true;
    }

    // Returns whether the group G is sorted descending,
    // i.e., whether all the zeros are in the top right quadrant
    static bool stabilizerGroupIsSorted(const StabilizerGroup& G) {
        for (unsigned int i=0; i+1<G.size(); i++) {
            if (LimEntry<>::leneq(G[i], G[i+1]))
                return false;
        }
        return true;
    }

    static void printStabilizerGroup(const StabilizerGroup& G) {
        std::cout << "Stabilizer group (" << G.size() << " elements)\n";  std::cout.flush();
        for (unsigned int i=0; i<G.size(); i++) {
            std::cout << LimEntry<>::to_string(G[i]) << std::endl;  std::cout.flush();
        }
        std::cout.flush();
    }

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

    static LimEntry<>* multiply(const LimEntry<>* a, const LimEntry<>* b) {
        LimEntry<>* c = LimEntry<>::getIdentityOperator();
        c->multiplyBy(a);
        c->multiplyBy(b);
        return c;
    }

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
    //   here Id has a '1' in every other row, to avoid getting 'Y' and 'X' entries, which can mess up multiplication
    // TODO this is not very space-efficient, so we may want to improve this
    // (Returns a fresh Stabilizergroup object; the group G is unchanged)
    static StabilizerGroup appendIdentityMatrix(const StabilizerGroup& G, unsigned int height) {
        StabilizerGroup GI = deepcopy(G);
        for (unsigned int i=0; i<G.size(); i++) {
            // Make column G[i][height ... height + width-1] into the column [0 ...0 1 0 ... 0]
            for (unsigned int h=height; h<G.size(); h++) {
                GI[i]->paulis.set(h, 0);
            }
//            for (unsigned int h=height+i+1; h<G.size(); h++) {
//                GI[i]->paulis.set(h, 0);
//            }
            GI[i]->paulis.set(height+2*i, 1);
        }
        return GI;
    }

    // Performs Gaussian elimination on G
    // We assume that G is not stored in the LimTable.
    // In more detail: the elements of G are modified in place
    // Therefore, the LimEntry objects should NOT be stored in the LimTable;
    template <std::size_t NUM_QUBITS>
    static void GaussianElimination(std::vector<LimEntry<NUM_QUBITS>*>& G) {
        if (G.size() <= 1) return;
        unsigned int pauli_height = 2*NUM_QUBITS; // length of the columns as far as they contain Pauli operators
        unsigned int reducingColId;
        for (unsigned int h=0; h<pauli_height; h++) {
            // Step 1: Find a column with a '1' at position h
            // TODO AND position h should be the pivot of that column. Right?
            reducingColId = -1;
            for (unsigned int i=0; i<G.size(); i++) {
                if (G[i]->pivotPosition() == h) {
                    reducingColId = i;
                    break;
                }
            }
            if (reducingColId == (unsigned int)-1) continue;
            // Step 2: Reduce all other columns via G[reducingColId]
            for (unsigned int reduceColId =0; reduceColId < G.size(); reduceColId++) {
                if (reduceColId == reducingColId) continue;
                if (G[reduceColId]->paulis.test(h)) {
                    G[reduceColId] = Pauli::multiply(G[reduceColId], G[reducingColId]);
                }
            }
        }
    }

    template <std::size_t NUM_QUBITS>
    static void pruneZeroColumns(std::vector<LimEntry<NUM_QUBITS>*>& G) {
        unsigned int i=0;
        while (i<G.size()) {
            if (G[i]->isAllZeroVector()) {
                // Remove this all-zero vector from the matrix
                // Step 1: replace it with the last vector in the matrix
                G[i] = G[G.size()-1];
                G.pop_back();
            } else {
                i++;
            }
        }
    }

    // Puts the stabilizer group in column echelon form; specifically:
    //   1. performs Gaussian elimination on G
    //   2. prunes the all-zero columns
    //   3. sorts the columns lexicographically, i.e., so that 'pivots' appear in the matrix
    static void toColumnEchelonForm(StabilizerGroup& G) {
        std::cout << "[toColumnEchelonForm] Before CEF, group is:\n"; std::cout.flush();
        printStabilizerGroup(G);
        GaussianElimination(G);
        pruneZeroColumns(G);
        // To obtain a lower triangular form, we now sort the vectors descending lexicographically, descending
        std::sort(G.begin(), G.end(), LimEntry<>::geq);
        std::cout << "[toColumnEchelonForm] After CEF, group is:\n"; std::cout.flush();
        printStabilizerGroup(G);
    }

    // Reduces a vector 'x' via a group 'G' via the Gram-Schmidt procedure
    // Returns the reduced vector
    // TODO this is not correct; the procedure should check on line 7, whether v has its FIRST '1' entry at position h, not just any '1'
    template<std::size_t NUM_QUBITS>
    static LimEntry<NUM_QUBITS>* GramSchmidt(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* x) {
        std::cout << "[GramSchmidt] |G|=" << G.size() << "  x = " << LimEntry<>::to_string(x) << "\n";
        LimEntry<NUM_QUBITS>* y = new LimEntry<NUM_QUBITS>(x);
        if (G.size() == 0) return y;
        std::size_t height = 2*NUM_QUBITS;
        for (unsigned int h=0; h<height; h++) {
            if (y->paulis[h]) {
                std::cout << "[GramSchmidt] h=" << h << ".\n";
                // Look for a vector whose first '1' entry is at position h
                for (unsigned int v=0; v<G.size(); v++) {
                    if (G[v]->pivotPosition() == h) {
                        std::cout << "[GramSchmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << LimEntry<>::to_string(G[v]) << "\n";
                        y = Pauli::multiply(*y, *G[v]);
                    }
                }
            }
        }
        return y;
    }

    // Interprets G as a 0/1 matrix, where each operator (i.e., LimEntry object) forms a column
    // returns the kernel of G in column echelon form
    // TODO this method requires LimEntry objects of length 4*NUM_QUBITS,
    // TODO bug: this method doesn't deal correctly with the groups G={Z}  H={-Z}
    //    but the LimEntry objects only give it vectors of length 2*NUM_QUBITS
    //    so right now, we can 'only' do simulations of up to 15 qubits
    static StabilizerGroup getKernelZ(const StabilizerGroup& G, unsigned int nqubits) {
        std::cout << "[get Kernel Z] start  |G| = " << G.size() << "\n"; std::cout.flush();
        StabilizerGroup kernel;
        unsigned int width = G.size();  // minor note: size of G may change during toColumnEchelonForm(G)
        // TODO the next line used to say "(G, nqubits)", but now says "(G, 2*nqubits)". Is this right? since there are both Z and X bits
        StabilizerGroup GI = appendIdentityMatrix(G, 2*nqubits);
        toColumnEchelonForm(GI);
        LimEntry<>* kernelColumn;
        for (unsigned int i=0; i<GI.size(); i++) {
            // Check if GI[i] is an all-zero column
            std::cout << "[getKernel Z] testing GI column " << i << "\n"; std::cout.flush();
            // TODO && LimEntry<>::getPhase(GI[i])==phases::phase_one
            if (!LimEntry<>::isIdentity(GI[i]) && GI[i]->isZeroInRange(0, 2*nqubits)) {
                // Copy bits [2*nqubits ... 2*nqubits + width -1] to kernel[i][0 ... width-1]
                std::cout << "[getKernel Z] Adding column " << i << " to kernel.\n"; std::cout.flush();
                kernelColumn = new LimEntry<>();
                for (unsigned int b=0; b<width; b++) {  // TODO should this be b<GI.size() ?
                    std::cout << "[getKernel Z] In column " << i << ", setting bit " << b << "\n"; std::cout.flush();
                    kernelColumn->paulis.set(b, GI[i]->paulis.test(2*nqubits+2*b));
                }
                kernel.push_back(kernelColumn);
            }
        }
        std::cout << "[get kernel Z] putting kernel in CEF.\n"; std::cout.flush();
        toColumnEchelonForm(kernel);
        return kernel;
    }

    static StabilizerGroup intersectGroupsZ(const StabilizerGroup& G, const StabilizerGroup& H, unsigned int nqubits) {
        std::cout << "[intersectGroups Z] start  |G|=" << G.size() << "  |H| = " << H.size() << std::endl;
        StabilizerGroup intersection;
        std::cout << "[intersectGroups Z] Group G:\n";
        printStabilizerGroup(G);
        std::cout << "[intersectGroups Z] Group H:\n";
        printStabilizerGroup(H);
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
        std::cout << "[intersectGroups Z] Found intersection: \n";
        printStabilizerGroup(intersection);

        return intersection;
    }

    // Returns an element in the coset <G> intersect (b + <H>)
    // Here <G> is the group generated by G; likewise for H
    // Note that b + <H> is therefore a coset.
    // If the coset <G> intersect (b + <H>) is empty, nullptr is returned
    // TODO this function always returns nullptr??
    // TODO I'm not convinced this function works...
    static LimEntry<>* getCosetIntersectionElementZ(const StabilizerGroup& G, const StabilizerGroup& H, const LimEntry<>* b) {
        std::cout << "[coset elZ] start; |G|=" << G.size() << " |H|=" << G.size() << " b = " << LimEntry<>::to_string(b) << "\n"; std::cout.flush();
        // TODO handle the case b == nullptr (so b is identity)
        if (!stabilizerGroupIsSorted(G)) {
            std::cout << "[coset elZ] group G is not sorted. Quitting G = \n";
            printStabilizerGroup(G);
            return nullptr;
        }
        if (!stabilizerGroupIsSorted(H)) {
            std::cout << "[coset elZ] group H is not sorted. Quitting.\n";
            printStabilizerGroup(H);
            return nullptr;
        }
        std::cout << "[coset elZ] both groups are sorted.\n"; std::cout.flush();
        LimEntry<>* b2;
        LimEntry<>* bOrth;
        b2 = new LimEntry<>(b);
        std::cout << "[coset elZ] Made b2.\n"; std::cout.flush();
        b2 = GramSchmidt(H, b2);
        std::cout << "[coset elZ] performed Gram-Schmidt; b2 = " << LimEntry<>::to_string(b2) << ".\n"; std::cout.flush();
        bOrth = new LimEntry<>(b2);
        // TODO maybe use an 'elementIsInGroupZ' function, instead of GramSchmidt and then checking identity? maybe not; doesn't work for Pauli group
        bOrth = GramSchmidt(G, bOrth);
        std::cout << "[coset elZ] performed Gram-Schmidt; borth = " << LimEntry<>::to_string(bOrth) << "\n"; std::cout.flush();
        if (bOrth->isIdentityOperator()) {
//            bOrth->multiplyBy(b2);
//            std::cout << "[coset elZ] multiplied by b2.\n"; std::cout.flush();
            std::cout << "[coset elZ] the coset contains an element: " << LimEntry<>::to_string(b2) << "\n";
            return b2;
        }
        return nullptr;
    }

    // For now, we assume that only vNodes are passed
//    template <class Node>
    static StabilizerGroup constructStabilizerGeneratorSetZ(const vNode node) {
        //empty
        Edge<vNode> low, high;
        low  = node.e[0];
        high = node.e[1];
        unsigned int n = node.v;

        StabilizerGroup stabgenset;
        // Case 0: Check if this node is the terminal node (aka the Leaf)
        if (n == (unsigned int)-1) {
            // Return the trivial group.
            // This group is generated by the empty set; therefore, we just return the empty stabgenset
            return stabgenset;
        }
        // Case 1: right child is zero
        else if (high.isZeroTerminal()) {
            std::cout << "[stab genZ] |0> knife case  n = " << n << ". Low stabilizer group is:\n";
            stabgenset = low.p->limVector; // copies the stabilizer group of the left child
            printStabilizerGroup(stabgenset);
            LimEntry<>* idZ = LimEntry<>::getIdentityOperator();
            idZ->setOperator(n, 'Z');
            stabgenset.push_back(idZ);
            std::cout << "[stab genZ] Added Z. Now stab gen set is:\n";
            printStabilizerGroup(stabgenset);
            // the matrix set is already in column echelon form,
            // so we do not need to perform that step here
        }
        // Case 2: left child is zero
        else if (low.isZeroTerminal()) {
            std::cout << "[stab genZ] |1> knife case. n = " << n << ". High stabilizer group is:\n";
            stabgenset = high.p->limVector;
            printStabilizerGroup(stabgenset);
            LimEntry<>* minusIdZ = LimEntry<>::getMinusIdentityOperator();
            minusIdZ->setOperator(n, 'Z');
            stabgenset.push_back(minusIdZ);
            std::cout << "[stab genZ] Added -Z. now stab gen set is:\n";
            printStabilizerGroup(stabgenset);
        }
        // Case 3: the node is a 'fork': both its children are nonzero
        else {
            // Gather the stabilizer groups of the two children
            std::cout << "[constructStabilizerGeneratorSet] Case fork.\n";
            StabilizerGroup* stabLow  = &(low. p->limVector);
            StabilizerGroup* stabHigh = &(high.p->limVector);
            // Step 1: Compute the intersection
            stabgenset = intersectGroupsZ(*stabLow, *stabHigh, n);

            // Step 2:
            LimEntry<>* minus = LimEntry<>::getMinusIdentityOperator();
            LimEntry<>* m = getCosetIntersectionElementZ(*stabLow, *stabHigh, minus);
            if (m != nullptr) {
                m->setOperator(n, 'Z');
                stabgenset.push_back(m);
            }
            // The matrix is now guaranteed to be in column echelon form
        }

        return stabgenset;
    }

    // Returns an isomorphism between u and v,
    // or -1 if u and v are not isomorphic
    // Assumes that the low edges of u and v have an Identity LIM
    // TODO should we add assertions that u and v do not represent zero vectors?
    // TODO this function does not take into account the different phases... but maybe it doesn't need to...
    static LimEntry<>* getIsomorphismZ(const vNode* u, const vNode* v) {
        assert( u != nullptr );
        assert( v != nullptr );
        std::cout << "[getIsomorphismZ] Start.\n";
        LimEntry<>* iso = nullptr;
//         TODO add assertion that the nodes are on the same number of qubits u->v == v->v
//        assert (u->v == v->v);
        Edge<vNode> uLow  = u->e[0];
        Edge<vNode> uHigh = u->e[1];
        Edge<vNode> vLow  = v->e[0];
        Edge<vNode> vHigh = v->e[1];
        assert (!(uLow.isZeroTerminal() && uHigh.isZeroTerminal()));
        assert (!(vLow.isZeroTerminal() && vHigh.isZeroTerminal()));
        // TODO this assertion is not necessarily true; in the normalizeLIMDD function, we hve vLow.l != nullptr
        assert (uLow.l == nullptr && vLow.l == nullptr);
        // Case 0.1: the nodes are equal
        if (u == v) {
            std::cout << "[getIsomorphismZ] case u == v.\n"; std::cout.flush();
            // In this case, we return the Identity operator, which is represented by a null pointer
            return nullptr;
        }
        // Case 0.2: The leaf case.
        // TODO this case should already be covered by case 0.1, since in this case v is also the terminal node
        //   Do we need this extra check?
        else if (vNode::isTerminal(u)) {
            std::cout << "[getIsomorphismZ] Case u is terminal.\n"; std::cout.flush();
            // Return the identity operator, which is represented by a null pointer
            return nullptr;
        }
        // Case 1 ("Left knife"): Left child is nonzero, right child is zero
        else if (uHigh.isZeroTerminal()) {
            std::cout << "[getIsomorphismZ] Case uHigh is terminal\n";
            if (!vHigh.isZeroTerminal()) return (LimEntry<>*)-1;
            if (uHigh.p != vHigh.p) return (LimEntry<>*) -1;
            return multiply(*uHigh.l, *vHigh.l);
        }
        // Case 2 ("Right knife"): Left child is zero, right child is nonzero
        else if (uLow.isZeroTerminal()) {
            std::cout << "[getIsomorphismZ] case uLow is terminal.\n";
            if (!vLow.isZeroTerminal()) return (LimEntry<>*)-1; // not isomorphic
            if (uLow.p != vLow.p) return (LimEntry<>*) -1;
            return nullptr;  // return the Identity isomorphism
        }
        // Case 3 ("Fork"): Both children are nonzero
        else {
            std::cout << "[getIsomorphismZ] case Fork.\n"; std::cout.flush();
            // Step 1: check if the amplitudes are equal, up to a sign
            if (!uLow.w.approximatelyEquals(vLow.w) || !uHigh.w.approximatelyEquals(vHigh.w)) return (LimEntry<>*) -1;
            std::cout << "[getIsomorphismZ] children are approximately equal.\n"; std::cout.flush();
            // TODO check if the amplitudes satisfy uHigh = -1 * vHigh
            bool amplitudeOppositeSign = false;
            // Step 2: Check if nodes u and v have the same children
            if (uLow.p != vLow.p || uHigh.p != vHigh.p) return (LimEntry<>*) -1;
            std::cout << "[getIsomorphismZ] children of u and v are the same nodes.\n"; std::cout.flush();
            // Step 3: check if the automorphism groups are equal
            if (!stabilizerGroupsEqual(u->limVector, v->limVector)) {
                return (LimEntry<>*) -1;
            }
            std::cout << "[getIsomorphismZ] the stabilizer Groups of u and v are equal.\n"; std::cout.flush();
            // Step 4: If G intersect (H+isoHigh) contains an element P, then Id tensor P is an isomorphism
            LimEntry<>* isoHigh = multiply(uHigh.l, vHigh.l);
            std::cout << "[getIsomorphismZ] multiplied high isomorphisms:" << LimEntry<>::to_string(isoHigh) << ".\n"; std::cout.flush();
            if (amplitudeOppositeSign) {
                std::cout << "[getIsomorphismZ] multiplying Phase by -1?\n"; std::cout.flush();
                isoHigh->multiplyPhaseBy(phases::phase_minus_one); // multiply by -1
                std::cout << "[getIsomorphismZ] multiplied phase by -1.\n"; std::cout.flush();
            }
            iso = getCosetIntersectionElementZ(uLow.p->limVector, uHigh.p->limVector, isoHigh);
            std::cout << "[getIsomorphismZ] completed coset intersection element.\n"; std::cout.flush();
            if (iso != nullptr) {
                std::cout << "[getIsomorphismZ] The coset was non-empty; returning element.\n"; std::cout.flush();
                return iso;
            }
            // Step 5: If G intersect (H-isomorphism) contains an element P, then Z tensor P is an isomorphism
            std::cout << "[getIsomorphismZ] multiplying phase by 2.\n"; std::cout.flush();
            isoHigh->multiplyPhaseBy(2);
            std::cout << "[getIsomorphismZ] multiplied phase by 2.\n"; std::cout.flush();
            iso = getCosetIntersectionElementZ(uLow.p->limVector, uHigh.p->limVector, isoHigh);
//            std::cout << "[getIsomorphismZ] found coset intersection element.\n"; std::cout.flush();
            if (iso != nullptr) {
                std::cout << "[getIsomorphismZ] Coset was not empty; returning result.\n"; std::cout.flush();
                return iso;
            }
            else {
                std::cout << "[getIsomorphismZ] Coset was empty; returning -1.\n"; std::cout.flush();
                return (LimEntry<>*) -1;
            }
        }

        return iso;
    }

    // Choose the label on the High edge, in the Z group
//    template <class Node>
    static LimEntry<>* highLabelZ(const vNode* u, const vNode* v, LimEntry<>* vLabel) {
        std::cout << "[highLabelZ] Start; |Gu| = " << u->limVector.size() << " |Gv| = " << v->limVector.size() << ".\n"; std::cout.flush();
        StabilizerGroup GH = groupConcatenate(u->limVector, v->limVector);
        std::cout << "[highLabelZ] Concatenated; |GH| = " << GH.size() << std::endl;
        toColumnEchelonForm(GH);
        std::cout << "[highLabelZ] to CEF'ed; now |GH| = " << GH.size() << std::endl;
        LimEntry<>* newHighLabel = GramSchmidt(GH, vLabel);
        // Set the new phase to +1
        newHighLabel->setPhase(phases::phase_one);
        // TODO we used to set the phase to -1, why? was that a mistake?
//        newHighLabel->paulis.set(LimEntry<>::NUM_BITSETBITS-1, 0);
        std::cout << "[highLabelZ] end.\n"; std::cout.flush();
        return newHighLabel;
    }

    static LimEntry<>* highLabelZ(const mNode* u, const mNode* v, LimEntry<>* vLabel) {
        std::cout << u << v << vLabel << std::endl;
        throw std::exception();
    }

    static LimEntry<>* getIsomorphismZ(const mNode* u, const mNode* v) {
        std::cout << u << v << std::endl;
        throw std::exception();
    }

};



} // namespace dd
#endif //DDPACKAGE_PAULIALGEBRA_HPP
