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

};



} // namespace dd
#endif //DDPACKAGE_PAULIALGEBRA_HPP
