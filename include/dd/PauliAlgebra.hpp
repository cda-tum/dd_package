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

    // Choose the label on the High edge, in the Z group
    template <class Node>
    static LimEntry<>* highLabelZ(const Node* u, const Node* v, LimEntry<>* vLabel) {
        LimEntry<>* l = LimEntry<>::getIdentityOperator();
        StabilizerGroup intersect = intersectGroupsZ(u->limVector, v->limVector);

        return l;
    }

    template <class Node>
    static LimEntry<>* getIsomorphismZ(const Node* u, const Node* v) {
        LimEntry<>* iso = nullptr;

        return iso;
    }

    // This function does nothing; it just 'catches' the mNode case
//    static LimEntry<>* highLabelZ(const mNode u, const mNode v, LimEntry<>* vLabel) {
//        return vlabel;
//    }

    static LimEntry<>* multiply(const LimEntry<>* a, const LimEntry<>* b) {
        LimEntry<>* c = LimEntry<>::getIdentityOperator();
        c->multiplyBy(*a);
        c->multiplyBy(*b);
        return c;
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

    static StabilizerGroup intersectGroupsZ(const StabilizerGroup& G, const StabilizerGroup& H) {
        StabilizerGroup intersection;

        return intersection;
    }

    // Performs Gaussian elimination on G
    // TODO this procedure has an inefficiency: it produces many LIMs, each of which is separately allocated
    // It would be better if this was done 'in place', without allocating new memory
    // There is also a memory leak
    static void GaussianElimination(StabilizerGroup& G) {
        if (G.size() <= 1) return;

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

};



} // namespace dd
#endif //DDPACKAGE_PAULIALGEBRA_HPP
