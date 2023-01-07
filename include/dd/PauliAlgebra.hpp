//
// Created by lieuwe on 13/12/2021.
//

#ifndef DDPACKAGE_PAULIALGEBRA_HPP
#define DDPACKAGE_PAULIALGEBRA_HPP

#include "ComplexNumbers.hpp"
#include "Edge.hpp"
#include "LimTable.hpp"
#include "Log.hpp"
#include "Node.hpp"
#include "Package.hpp"
#include "PauliUtilities.hpp"
#include "QuantumGate.hpp"

#include <algorithm>
#include <array>
#include <iostream>

// note: my package won't compile unless I put my functions in a class
// for now, I've called this class Pauli
// - Lieuwe

namespace dd {

    // time taken, for profiling
    clock_t groupIntersectTime       = 0;
    clock_t cosetIntersectModPTime   = 0;
    clock_t cosetIntersectPauliTime  = 0;
    clock_t constructStabilizerTime  = 0;
    clock_t recoverPhaseTime         = 0;
    clock_t gramSchmidtTime          = 0;
    clock_t gaussianEliminationTime  = 0;
    // call counts
    long cosetIntersectCallCount     = 0;
    long groupIntersectCallCount     = 0;
    long recoverPhaseCallCount       = 0;
    long gramSchmidtCallCount        = 0;
    long gaussianEliminationCallCount= 0;
    long intersectionMemoizationHits = 0;
    // memoized data
    std::vector<LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>> GH_Id_CEF_memoized;
    std::vector<LimEntry<NUM_QUBITS>>                  GintersectH_memoized;
    bool                                               memoizedGintersectH;


// TODO write a test
    // TODO refactor to use recoverElement
    // precondition: group is in column echelon form
    template<std::size_t NUM_QUBITS>
    inline phase_t recoverPhase(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* a) {
        if (a == LimEntry<NUM_QUBITS>::noLIM) {
            throw std::runtime_error("[recoverPhase] a is noLIM.\n");
        }
        recoverPhaseCallCount++;
        clock_t begin = clock();
        LimEntry<NUM_QUBITS> A(a);
        LimEntry<NUM_QUBITS> B;
        for (std::size_t g = 0; g < G.size(); g++) {
            auto const pivot = G[g]->pivotPosition();
            if (A.paulis.test(pivot)) {
                A.multiplyBy(G[g]);
                B.multiplyBy(G[g]);
            }
        }
        recoverPhaseTime += clock() - begin;
        return B.getPhase();
    }

    // precondition: group is in column echelon form
    template<std::size_t NUM_QUBITS>
    inline phase_t recoverPhase(const std::vector<LimEntry<NUM_QUBITS>>& G, const LimEntry<NUM_QUBITS>* a) {
        clock_t begin = clock();
        recoverPhaseCallCount++;
        LimEntry<NUM_QUBITS> A(a);
        LimEntry<NUM_QUBITS> B;
        for (std::size_t g = 0; g < G.size(); g++) {
            auto const pivot = G[g].pivotPosition();
            if (A.paulis.test(pivot)) {
                A.multiplyBy(G[g]);
                B.multiplyBy(G[g]);
            }
        }
        recoverPhaseTime += clock() - begin;
        return B.getPhase();
    }

    // TODO implement
    // TODO write a test
    // precondition: group is in column echelon form
    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> recoverElement(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* a) {
        if (a == LimEntry<NUM_QUBITS>::noLIM) {
            throw std::runtime_error("[recoverPhase] a is noLIM.\n");
        }
        clock_t begin = clock();
        recoverPhaseCallCount++;
        LimEntry<NUM_QUBITS> A(a);
        LimEntry<NUM_QUBITS> B;
        for (std::size_t g = 0; g < G.size(); g++) {
            auto const pivot = G[g]->pivotPosition();
            if (A.paulis.test(pivot)) {
                A.multiplyBy(G[g]);
                B.multiplyBy(G[g]);
            }
        }
        recoverPhaseTime += clock() - begin;
        return B;
    }
    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> createCanonicalLabel(const LimEntry<NUM_QUBITS>& x, const LimEntry<NUM_QUBITS>& y, const vEdge w) {
        auto c = x;
        c.setPhase(getPhaseInverse(c.getPhase()));
        c.multiplyBy(y);
        const auto d = getRootLabel(w.p, &c);
        //            if (d==c){
        //                std::cout << "RootLabelEqual" << std::endl;
        //            } else {
        //                std::cout << "RootLabelNotEqual" << std::endl;
        //            }
        return d;
    }

    template<std::size_t NUM_QUBITS, class Node>
    inline LimEntry<NUM_QUBITS> createCanonicalLabel([[maybe_unused]] const LimEntry<NUM_QUBITS>& x, [[maybe_unused]] const LimEntry<NUM_QUBITS>& y, [[maybe_unused]] const Edge<Node> w) {
        throw std::runtime_error("canonical labels may only be created for vectors; not for matrices.");
    }

    inline static void movePhaseIntoWeight(LimEntry<>& lim, Complex& weight) {
        if (lim.getPhase() != phase_one) {
            weight.multiplyByPhase(lim.getPhase());
            lim.setPhase(phase_one);
        }
    }

    inline static void movePhaseIntoWeight(LimEntry<>* lim, Complex& weight) {
        if (lim == nullptr) return;
        if (lim == LimEntry<>::noLIM) return;
        movePhaseIntoWeight(*lim, weight);
    }

    // Performs Gaussian elimination on G
    // We assume that G is not stored in the LimTable.
    // In more detail: the elements of G are modified in place
    // Therefore, the LimEntry objects should NOT be stored in the LimTable;
    // todo this algorithm allocates many new LIMs; by modifying in place, less memory can be allocated, and we solve a memory leak
    template<std::size_t NUM_QUBITS>
    inline void GaussianElimination(std::vector<LimEntry<NUM_QUBITS>*>& G) {
        gaussianEliminationCallCount++;
        clock_t begin = clock();
        if (G.size() <= 1) {
            return;
        }
        //        Log::log << "[Gaussian Elimination] start. |G| = " << G.size() << ".\n"; Log::log.flush();
        constexpr std::size_t pauli_height = 2 * NUM_QUBITS; // length of the columns as far as they contain Pauli operators
        for (std::size_t h = 0; h < pauli_height; h++) {
            // Step 1: Find a column with a '1' at position h
            std::size_t reducingColId = std::numeric_limits< decltype(reducingColId)>::max();
            for (std::size_t i = 0; i < G.size(); i++) {
                if (G[i]->pivotPosition() == h) {
                    reducingColId = i;
                    break;
                }
            }
            if (reducingColId == std::numeric_limits< decltype(reducingColId)>::max()) {
                continue;
            }
            // Step 2: Reduce all other columns via G[reducingColId]
            for (std::size_t reduceColId = 0; reduceColId < G.size(); reduceColId++) {
                if (reduceColId == reducingColId) {
                    continue;
                }
                if (G[reduceColId]->paulis.test(h)) {
                    //                    Log::log << "[Gaussian Elimination] Multiplying col " << reduceColId << " with col " << reducingColId << ".\n"; Log::log.flush();
                    G[reduceColId] = LimEntry<NUM_QUBITS>::multiply(G[reduceColId], G[reducingColId]);
                    //G[reduceColId]->multiplyBy(G[reducingColId]); // TODO this would solve the memory leak; but it leads to failed tests
                }
            }
        }
        gaussianEliminationTime += clock() - begin;
    }

    //    // precondition: G is sorted
    //    template<std::size_t NUM_QUBITS>
    //    inline void GaussianEliminationSortedFast(std::vector<LimEntry<NUM_QUBITS>*>& G) {
    //        if (G.size() <= 1) return;
    //        unsigned int pivot;
    //
    //        for (unsigned int g = 0; g + 1 < G.size(); g++) {
    //            pivot = G[g]->pivotPosition();
    //            if (pivot >= 2 * NUM_QUBITS) continue; // In this case G[g] is an all-zero column (i.e., is the identity)
    //            for (unsigned int h = g + 1; h < G.size(); h++) {
    //                if (G[h]->paulis.test(pivot)) {
    //                    G[h] = LimEntry<NUM_QUBITS>::multiply(G[h], G[g]);
    //                }
    //            }
    //        }
    //    }

    template<std::size_t NUM_QUBITS>
    inline void GaussianEliminationSortedFast(std::vector<LimEntry<NUM_QUBITS>>& G) {
        gaussianEliminationCallCount++;
        clock_t begin = clock();
        if (G.size() <= 1) {
            return;
        }

        for (std::size_t g = 0; g + 1 < G.size(); g++) {
            auto const pivot = G[g].pivotPosition();
            if (pivot >= 2 * NUM_QUBITS) {
                continue; // In this case G[g] is an all-zero column (i.e., is the identity)
            }
            for (std::size_t h = g + 1; h < G.size(); h++) {
                if (G[h].paulis.test(pivot)) {
                    G[h].multiplyBy(G[g]);
                }
            }
        }
        gaussianEliminationTime += clock() - begin;
    }

    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline void GaussianEliminationModuloPhaseSortedFast(std::vector<LimBitset<NUM_QUBITS, NUM_BITS>*>& G) {
        gaussianEliminationCallCount++;
        clock_t begin = clock();
        if (G.size() <= 1) {
            return;
        }

        for (std::size_t g = 0; g + 1 < G.size(); g++) {
            auto const pivot = G[g]->lim.pivotPosition();
            if (pivot >= 2 * NUM_QUBITS) {
                continue;
            }
            for (std::size_t h = g + 1; h < G.size(); h++) {
                if (G[h]->lim.paulis.test(pivot)) {
                    G[h] = LimBitset<NUM_QUBITS, NUM_BITS>::multiply(G[h], G[g]);
                }
            }
        }
        gaussianEliminationTime += clock() - begin;
    }

    // TODO make faster by telling the multiply() routine how many qubits there are (!)
    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline void GaussianEliminationModuloPhaseSortedFast(std::vector<LimBitset<NUM_QUBITS, NUM_BITS>>& G) {
        gaussianEliminationCallCount++;
        clock_t begin = clock();
        if (G.size() <= 1) {
            return;
        }

        for (std::size_t g = 0; g + 1 < G.size(); g++) {
            auto const pivot = G[g].lim.pivotPosition();
            if (pivot >= 2 * NUM_QUBITS) {
                continue;
            }
            for (std::size_t h = g + 1; h < G.size(); h++) {
                if (G[h].lim.paulis.test(pivot)) {
                    G[h] = LimBitset<NUM_QUBITS, NUM_BITS>::multiply(G[h], G[g]); // TODO use multiplyBy (this avoids a copy constructor)
                }
            }
        }
        gaussianEliminationTime += clock() - begin;
    }

    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline bool isAbelian(const std::vector<LimBitset<NUM_QUBITS, NUM_BITS>*>& G) {
        for (std::size_t i = 0; i < G.size(); i++) {
            for (std::size_t j = i + 1; j < G.size(); j++) {
                if (!G[i]->lim.commutesWith(G[j]->lim)) {
                    return false;
                }
            }
        }
        return true;
    }

    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline bool isAbelian(const std::vector<LimBitset<NUM_QUBITS, NUM_BITS>>& G) {
        for (std::size_t i = 0; i < G.size(); i++) {
            for (std::size_t j = i + 1; j < G.size(); j++) {
                if (!G[i].lim.commutesWith(G[j].lim)) {
                    return false;
                }
            }
        }
        return true;
    }

    // Performs Gaussian Elimination on the group G, ignoring the phase of the LIMs involved
    // todo it is possible to write a faster procedure, if we are allowed to assume that G is sorted
    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline void GaussianEliminationModuloPhase(std::vector<LimBitset<NUM_QUBITS, NUM_BITS>*>& G) {
        if (G.size() <= 1) {
            return;
        }
        //        Log::log << "[Gaussian Elimination Bitset] start. |G| = " << G.size() << ".\n"; Log::log.flush();
        constexpr std::size_t pauli_height = 2 * NUM_QUBITS; // length of the columns as far as they contain Pauli operators
        for (std::size_t row = 0; row < pauli_height; row++) {
            // Step 1: Find a column with a '1' at position row
            std::size_t reducingColId = std::numeric_limits<decltype(reducingColId)>::max();

            for (std::size_t i = 0; i < G.size(); i++) {
                if (G[i]->lim.pivotPosition() == row) {
                    reducingColId = i;
                    break;
                }
            }
            if (reducingColId == std::numeric_limits<decltype(reducingColId)>::max()) {
                continue;
            }
            // Step 2: Reduce all other columns via G[reducingColId]
            for (std::size_t reduceColId = 0; reduceColId < G.size(); reduceColId++) {
                if (reduceColId == reducingColId) {
                    continue;
                }
                if (G[reduceColId]->lim.paulis.test(row)) {
                    //                    Log::log << "[Gaussian Elimination Bitset] Multiplying col " << reduceColId << " with col " << reducingColId << ".\n"; Log::log.flush();
                    G[reduceColId] = LimBitset<NUM_QUBITS, NUM_BITS>::multiply(G[reduceColId], G[reducingColId]);
                }
            }
        }
    }

    //    // Puts the stabilizer group in column echelon form; specifically:
    //    //   1. performs Gaussian elimination on G
    //    //   2. prunes the all-zero columns
    //    //   3. sorts the columns lexicographically, i.e., so that 'pivots' appear in the matrix
    //    inline void toColumnEchelonForm(StabilizerGroup& G) {
    //        std::sort(G.begin(), G.end(), LimEntry<>::geq);
    //        GaussianEliminationSortedFast(G);
    //        //        Log::log << "[toColumnEchelonForm] After Gaussian Elimination, before pruning zero col's, group is:\n";Log::log.flush();
    //        //        printStabilizerGroup(G);
    //        pruneZeroColumns(G);
    //        // To obtain a lower triangular form, we now sort the vectors descending lexicographically, descending
    //        std::sort(G.begin(), G.end(), LimEntry<>::geq);
    //        //        Log::log << "[toColumnEchelonForm] After CEF, group is:\n"; Log::log.flush();
    //        //        printStabilizerGroup(G);
    //    }

    inline void toColumnEchelonForm(StabilizerGroupValue& G) {
        std::sort(G.begin(), G.end(), LimEntry<>::greaterValue);
        GaussianEliminationSortedFast(G);
        pruneZeroColumns(G);
        std::sort(G.begin(), G.end(), LimEntry<>::greaterValue);
    }

    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline void toColumnEchelonFormModuloPhase(std::vector<LimBitset<NUM_QUBITS, NUM_BITS>>& G) {
        std::sort(G.begin(), G.end(), LimBitset<NUM_QUBITS, NUM_BITS>::greaterValue);
        GaussianEliminationModuloPhaseSortedFast(G);
        pruneZeroColumnsModuloPhase(G);
        std::sort(G.begin(), G.end(), LimBitset<NUM_QUBITS, NUM_BITS>::greaterValue);
    }

    // Reduces a vector 'x' via a group 'G' via the Gram-Schmidt procedure
    // Returns the reduced vector
    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> GramSchmidt(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* x) {
        gramSchmidtCallCount++;
        //        Log::log << "[GramSchmidt] |G|=" << G.size() << "  x = " << LimEntry<>::to_string(x) << "\n"; Log::log.flush();
        LimEntry<NUM_QUBITS> y(x); // = new LimEntry<NUM_QUBITS>(x);
        if (G.empty()) {
            return y;
        }
        constexpr std::size_t height = 2 * NUM_QUBITS;
        for (std::size_t h = 0; h < height; h++) {
            if (y.paulis[h]) {
                //                Log::log << "[GramSchmidt] h=" << h << ".\n";
                // Look for a vector whose first '1' entry is at position h
                for (std::size_t v = 0; v < G.size(); v++) {
                    if (G[v]->pivotPosition() == h) {
                        //                        Log::log << "[GramSchmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << LimEntry<>::to_string(G[v]) << "\n";
                        y.multiplyBy(*G[v]);
                    }
                }
            }
        }
        return y;
    }

    // Reduces a vector 'x' via a group 'G' via the Gram-Schmidt procedure
    // Returns the reduced vector
    // Precondition: the group G is in column echelon form
    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> GramSchmidtFastSorted(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* x) {
        gramSchmidtCallCount++;
        clock_t begin = clock();
        LimEntry<NUM_QUBITS> y(x);
        for (std::size_t g = 0; g < G.size(); g++) {
            auto const pivot = G[g]->pivotPosition();
            if (pivot == std::numeric_limits<decltype(pivot)>::max()) continue;
            if (y.paulis.test(pivot)) {
                y.multiplyBy(*G[g]);
            }
        }
        gramSchmidtTime += clock() - begin;
        return y;
    }

    // Reduces a vector 'x' via a group 'G' via the Gram-Schmidt procedure
    // Returns the reduced vector
    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> GramSchmidt(const std::vector<LimEntry<NUM_QUBITS>>& G, const LimEntry<NUM_QUBITS>* x) {
        gramSchmidtCallCount++;
        //        Log::log << "[GramSchmidt] |G|=" << G.size() << "  x = " << LimEntry<>::to_string(x) << "\n"; Log::log.flush();
        clock_t begin = clock();
        LimEntry<NUM_QUBITS> y(x); // = new LimEntry<NUM_QUBITS>(x);
        if (G.size() == 0) {
            return y;
        }
        constexpr std::size_t height = 2 * NUM_QUBITS;
        for (std::size_t h = 0; h < height; h++) {
            if (y.paulis[h]) {
                //                Log::log << "[GramSchmidt] h=" << h << ".\n";
                // Look for a vector whose first '1' entry is at position h
                for (std::size_t v = 0; v < G.size(); v++) {
                    if (G[v].pivotPosition() == h) {
                        //                        Log::log << "[GramSchmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << LimEntry<>::to_string(G[v]) << "\n";
                        y.multiplyBy(G[v]);
                    }
                }
            }
        }
        gramSchmidtTime += clock() - begin;
        return y;
    }

    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> GramSchmidtFastSorted(const std::vector<LimEntry<NUM_QUBITS>>& G, const LimEntry<NUM_QUBITS>* x) {
        gramSchmidtCallCount++;
        clock_t begin = clock();
        LimEntry<NUM_QUBITS> y(x);
        for (std::size_t g = 0; g < G.size(); g++) {
            auto const pivot = G[g].pivotPosition();
            if (pivot == std::numeric_limits<decltype(pivot)>::max()) {
                continue;
            }
            if (y.paulis.test(pivot)) {
                y.multiplyBy(G[g]);
            }
        }
        gramSchmidtTime += clock() - begin;
        return y;
    }

    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline LimBitset<NUM_QUBITS, NUM_BITS> GramSchmidt(const std::vector<LimBitset<NUM_QUBITS, NUM_BITS>*>& G, const LimBitset<NUM_QUBITS, NUM_BITS>* x) {
        gramSchmidtCallCount++;
        clock_t begin = clock();
        LimBitset<NUM_QUBITS, NUM_BITS> y(x);
        if (G.size() == 0) return y;
        constexpr std::size_t height = 2 * NUM_QUBITS;
        //        Log::log << "[Gram Schmidt] start y = " << y << "\n";
        for (std::size_t h = 0; h < height; h++) {
            if (y.lim.paulis[h]) {
                //                Log::log << "[GramSchmidt] h=" << h << ".\n";
                // Look for a vector whose first '1' entry is at position h
                for (std::size_t v = 0; v < G.size(); v++) {
                    if (G[v]->lim.pivotPosition() == h) {
                        //                        Log::log << "[Gram Schmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << *G[v] << "\n";
                        y.multiplyBy(*G[v]);
                        //                        Log::log << "[Gram Schmidt] after multiplication, y = " << y << "\n";
                    }
                }
            }
        }
        gramSchmidtTime += clock() - begin;
        return y;
    }

    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline LimBitset<NUM_QUBITS, NUM_BITS> GramSchmidt(const std::vector<LimBitset<NUM_QUBITS, NUM_BITS>>& G, const LimBitset<NUM_QUBITS, NUM_BITS>& x) {
        gramSchmidtCallCount++;
        clock_t begin = clock();
        LimBitset<NUM_QUBITS, NUM_BITS> y(x);
        if (G.size() == 0) return y;
        constexpr std::size_t height = 2 * NUM_QUBITS;
        //        Log::log << "[Gram Schmidt] start y = " << y << "\n";
        for (std::size_t h = 0; h < height; h++) {
            if (y.lim.paulis[h]) {
                //                Log::log << "[GramSchmidt] h=" << h << ".\n";
                // Look for a vector whose first '1' entry is at position h
                for (std::size_t v = 0; v < G.size(); v++) {
                    if (G[v].lim.pivotPosition() == h) {
                        //                        Log::log << "[Gram Schmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << *G[v] << "\n";
                        y.multiplyBy(G[v]);
                        //                        Log::log << "[Gram Schmidt] after multiplication, y = " << y << "\n";
                    }
                }
            }
        }
        gramSchmidtTime += clock() - begin;
        return y;
    }

    // Precondition: G is in column echelon form
    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline LimBitset<NUM_QUBITS, NUM_BITS> GramSchmidtFastSorted(const std::vector<LimBitset<NUM_QUBITS, NUM_BITS>>& G, const LimBitset<NUM_QUBITS, NUM_BITS>& x) {
        gramSchmidtCallCount++;
        clock_t begin = clock();
        LimBitset<NUM_QUBITS, NUM_BITS> y(x);
        for (std::size_t g = 0; g < G.size(); g++) {
            auto const pivot = G[g].lim.pivotPosition();
            if (y.lim.paulis.test(pivot)) {
                y.multiplyBy(G[g]);
            }
        }
        gramSchmidtTime += clock() - begin;
        return y;
    }

    // Performs the GramSchmidt algorithm,, i.e.,
    //   given a group G and a vector x,
    //   reduces the vector x via G, and returns this reduced vector
    //   The decomposition that is found, is recorded in the bitset 'indicator'
    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline void GramSchmidt(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* x, std::bitset<NUM_BITS>& indicator) {
        gramSchmidtCallCount++;
        clock_t begin = clock();
        //        Log::log << "[GramSchmidt] |G|=" << G.size() << "  x = " << LimEntry<>::to_string(x) << "\n";
        //        LimEntry<NUM_QUBITS>* y = new LimEntry<NUM_QUBITS>(x);
        LimEntry<NUM_QUBITS> y(x);
        constexpr std::size_t          height = 2 * NUM_QUBITS;
        for (std::size_t i = 0; i < height && i < NUM_QUBITS; i++) {
            indicator.set(i, 0);
        }
        if (G.size() == 0) {
            return;
        }
        for (std::size_t h = 0; h < height; h++) {
            if (y.paulis[h]) {
                //                Log::log << "[GramSchmidt] h=" << h << ".\n";
                // Look for a vector whose first '1' entry is at position h
                for (std::size_t v = 0; v < G.size(); v++) {
                    if (G[v]->pivotPosition() == h) {
                        //                        Log::log << "[GramSchmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << LimEntry<>::to_string(G[v]) << "\n";
                        //                        y = LimEntry<NUM_QUBITS>::multiply(*G[v], *y);
                        y.multiplyBy(*G[v]);
                        //                        Log::log << "[GramSchmidt] after multiplication, y = " << y << Log::endl;
                        indicator.set(v, 1);
                    }
                }
            }
        }
        //        return y;
        gramSchmidtTime += clock() - begin;
    }

    // Given a group G and a 0/1 indicator vector,
    //   returns the product of the indicated elements of G
    //   e.g., with G={ZIZ, IZZ, IXY} and indicator = '110', we return ZZI
    template<std::size_t NUM_QUBITS, std::size_t NUM_BITS>
    inline LimEntry<NUM_QUBITS> getProductOfElements(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::bitset<NUM_BITS>& indicator) {
        LimEntry<NUM_QUBITS> g = LimEntry<NUM_QUBITS>();
        assert(G.size() <= NUM_BITS);
        for (std::size_t i = 0; i < G.size(); i++) {
            if (indicator.test(i)) {
                g.multiplyBy(G[i]);
            }
        }
        return g;
    }

    //    // TODO free / deallocate G_Id and its elements
    template<std::size_t NUM_QUBITS>
    inline std::vector<std::bitset<NUM_QUBITS>> getKernelZ([[maybe_unused]] const std::vector<LimEntry<NUM_QUBITS>*>& G) {
        std::vector<std::bitset<NUM_QUBITS>> kernel;
        return kernel;
        //        std::vector<LimBitset<NUM_QUBITS>*> G_Id = appendIdentityMatrixBitset(G);
        //        GaussianElimination(G_Id);
        //        //        Log::log << "[getKernelZ] after Gaussian elimination, G_Id:\n";
        //        //        printStabilizerGroup(G_Id);
        //        for (unsigned int i = 0; i < G_Id.size(); i++) {
        //            if (G_Id[i]->lim.isIdentityOperator()) {
        //                kernel.push_back(G_Id[i]->bits);
        //            }
        //        }
        //        //        Log::log << "[getKernelZ] found kernel:\n";
        //        //        printKernel(kernel);
        //        // free / deallocate G_Id and its elements
        //        for (unsigned int i = 0; i < G_Id.size(); i++) {
        //            delete G_Id[i];
        //        }
        //        return kernel;
    }

    // Returns the kernel of the group G modulo phase, as a vector<bitset>
    // we assume the width of G is at most 2*NUM_QUBITS
    template<std::size_t NUM_QUBITS>
    inline std::vector<std::bitset<2 * NUM_QUBITS>> getKernelModuloPhase(const std::vector<LimEntry<NUM_QUBITS>>& G) {
        std::vector<LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>> G_Id = appendIdentityMatrixBitsetBig(G);

        std::sort(G_Id.begin(), G_Id.end(), LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>::greaterValue);
        GaussianEliminationModuloPhaseSortedFast(G_Id);
        std::vector<std::bitset<2 * NUM_QUBITS>> kernel;
        for (std::size_t i = 0; i < G_Id.size(); i++) {
            if (G_Id[i].lim.isIdentityModuloPhase()) {
                kernel.push_back(G_Id[i].bits);
            }
        }
        return kernel;
    }

    // Assume: G_Id has been sorted, and then Gaussian elimination was performed. (Zero columns have NOT been pruned)
    template<std::size_t NUM_QUBITS>
    inline std::vector<std::bitset<2 * NUM_QUBITS>> getKernelModuloPhase2(const std::vector<LimEntry<NUM_QUBITS>>& G_Id) {
        //std::vector<LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>> G_Id = appendIdentityMatrixBitsetBig(G);

        //std::sort(G_Id.begin(), G_Id.end(), LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>::greaterValue);
        //GaussianEliminationModuloPhaseSortedFast(G_Id);
        std::vector<std::bitset<2 * NUM_QUBITS>> kernel;
        for (std::size_t i = 0; i < G_Id.size(); i++) {
            if (G_Id[i].lim.isIdentityModuloPhase()) {
                kernel.push_back(G_Id[i].bits);
            }
        }
        return kernel;
    }

    // Given two groups G, H, computes the intersection, <G> intersect <H>
    // TODO refactor with NUM_QUBITS template parameter
    //    inline StabilizerGroup intersectGroupsZ(const StabilizerGroup& G, const StabilizerGroup& H) {
    //        StabilizerGroup                          intersection;
    //        StabilizerGroup                          GH     = groupConcatenate(G, H);
    //        std::vector<std::bitset<dd::NUM_QUBITS>> kernel = getKernelZ(GH);
    //        LimEntry<>                               g;
    //        for (unsigned int i = 0; i < kernel.size(); i++) {
    //            g = getProductOfElements(G, kernel[i]);
    //            intersection.push_back(new LimEntry<NUM_QUBITS>(g));
    //        }
    //        //        Log::log << "[intersectGroupsZ] found intersection:\n";
    //        //        printStabilizerGroup(intersection);
    //        return intersection;
    //    }

    // Returns a generating set J for the intersection of G and H, so <J>= <G> intersect <H>
    //    J is not necessarily in Column Echelon Form
    //    J may contain elements that are equal up to phase
    inline StabilizerGroupValue intersectGroupsModuloPhase(const StabilizerGroup& G, const StabilizerGroupValue& H) {
        groupIntersectCallCount++;
        clock_t begin = clock();
        StabilizerGroupValue                         intersection;
        StabilizerGroupValue                         concat = groupConcatenate(G, H);
        std::vector<std::bitset<2 * dd::NUM_QUBITS>> kernel = getKernelModuloPhase(concat);
        //        Log::log << "[intersectGroups mod phase] |kernel| = " << kernel.size() << "\n";
        for (std::size_t i = 0; i < kernel.size(); i++) {
            auto g = getProductOfElements(G, kernel[i]);
            intersection.push_back(g);
        }
        clock_t end = clock();
        groupIntersectTime += end - begin;

        return intersection;
    }

    inline StabilizerGroupValue intersectGroupsModuloPhaseValue(const StabilizerGroup& G, const StabilizerGroup& H) {
        groupIntersectCallCount++;
        clock_t begin = clock();
        StabilizerGroupValue                         intersection; // TODO reserve some storage? or use std::array instead of std::vector?
        StabilizerGroupValue                         concat = groupConcatenateValue(G, H);
        std::vector<std::bitset<2 * dd::NUM_QUBITS>> kernel = getKernelModuloPhase(concat);
        for (unsigned int i = 0; i < kernel.size(); i++) {
            auto g = getProductOfElements(G, kernel[i]);
            intersection.push_back(g);
        }
        groupIntersectTime += clock() - begin;

        return intersection;
    }

    // TODO (low priority) prevent the use of the oppositePhaseGenerators vector
    //   instead, use some bookkeeping variables to add the appropriately constructed objects to the intersection vector
    //   the purpose is to have less dynamically allocated memory. In this case the use of the vector oppositePhaseGenerators's DAM is prevented
    inline StabilizerGroupValue intersectGroupsPauli(const StabilizerGroup& G, const StabilizerGroupValue& H) {
        groupIntersectCallCount++;
        clock_t begin = clock();
        StabilizerGroupValue intersection = intersectGroupsModuloPhase(G, H);
        StabilizerGroupValue oppositePhaseGenerators;
        toColumnEchelonForm(intersection);
        //Log::log << "[intersect groups Pauli] intersection mod phase = " << groupToString(intersection, n) << '\n';
        // Remove all elements from intersection where the G-phase is not equal to the H-phase
        std::size_t g = 0;
        std::size_t intersectionSize = intersection.size();
        for (std::size_t i = 0; i < intersectionSize; i++) {
            auto const phaseG = recoverPhase(G, &intersection[g]);
            auto const phaseH = recoverPhase(H, &intersection[g]);
            if (phaseG == phaseH) {
                intersection[g].setPhase(phaseG);
                //Log::log << "[intersect groups Pauli] Adding " << LimEntry<>::to_string(&intersection[g], 3) << " to intersection.\n";
                g++;
            } else {
                // add it to the list of opposite phases
                //Log::log << "[intersect groups Pauli] Element " << LimEntry<>::to_string(&intersection[g], 3) << " has phase(G)=" << phaseToString(phaseG) << " and phaseH=" << phaseToString(phaseH) << ".\n";
                oppositePhaseGenerators.push_back(intersection[g]);
                // remove this from the intersection
                intersection[g] = intersection[intersection.size() - 1];
                intersection.pop_back();
            }
        }
        for (std::size_t i = 1; i < oppositePhaseGenerators.size(); i++) {
            auto a      = LimEntry<>::multiplyValue(oppositePhaseGenerators[0], oppositePhaseGenerators[i]);
            auto const phaseG = recoverPhase(G, &a);
            a.setPhase(phaseG);
            intersection.push_back(a);
        }
        //Log::log << "[intersect groups Pauli] intersection = " << groupToString(intersection, n) << '\n';
        groupIntersectTime += clock() - begin;
        return intersection;
    }

    // Precondition: G and H are in column echelon form
    // TODO refactor so that oppositePhaseGenerators are not allocated dynamically but are integrated in the main for-loop
    //    inline StabilizerGroup intersectGroupsPauli(const StabilizerGroup& G, const StabilizerGroup& H) {
    //        //        Qubit n = 5;
    //        //Log::log << "[intersect groups Pauli] G = " << groupToString(G, n) << " H = " << groupToString(H, n) << '\n';
    //        StabilizerGroup intersection = intersectGroupsModuloPhase(G, H);
    //        StabilizerGroup oppositePhaseGenerators;
    //        toColumnEchelonForm(intersection);
    //        //Log::log << "[intersect groups Pauli] intersection mod phase = " << groupToString(intersection, n) << '\n';
    //        // Remove all elements from intersection where the G-phase is not equal to the H-phase
    //        unsigned int s = intersection.size();
    //        phase_t      phaseG, phaseH;
    //        unsigned int g = 0;
    //        for (unsigned int i = 0; i < s; i++) {
    //            phaseG = recoverPhase(G, intersection[g]);
    //            phaseH = recoverPhase(H, intersection[g]);
    //            if (phaseG == phaseH) {
    //                intersection[g]->setPhase(phaseG);
    //                //Log::log << "[intersect groups Pauli] Adding " << LimEntry<>::to_string(intersection[g], 3) << " to intersection.\n";
    //                g++;
    //            } else {
    //                // add it to the wrong phase stuff
    //                //Log::log << "[intersect groups Pauli] Element " << LimEntry<>::to_string(intersection[g], 3) << " has phase(G)=" << phaseToString(phaseG) << " and phaseH=" << phaseToString(phaseH) << ".\n";
    //                oppositePhaseGenerators.push_back(intersection[g]);
    //                // remove this from the intersection
    //                intersection[g] = intersection[intersection.size() - 1];
    //                intersection.pop_back();
    //            }
    //        }
    //        LimEntry<>* a;
    //        for (unsigned int i = 1; i < oppositePhaseGenerators.size(); i++) {
    //            a      = LimEntry<>::multiply(oppositePhaseGenerators[0], oppositePhaseGenerators[i]);
    //            phaseG = recoverPhase(G, a);
    //            a->setPhase(phaseG);
    //            intersection.push_back(a);
    //        }
    //        //Log::log << "[intersect groups Pauli] intersection = " << groupToString(intersection, n) << '\n';
    //        return intersection;
    //    }

    //    inline StabilizerGroup conjugateGroup(const StabilizerGroup& G, const LimEntry<>* a) {
    //        StabilizerGroup H;
    //        for (unsigned int i = 0; i < G.size(); i++) {
    //            H.push_back(new LimEntry<>(G[i]));
    //            if (!H[i]->commutesWith(a)) {
    //                H[i]->setPhase(multiplyPhases(H[i]->getPhase(), phase_t::phase_minus_one));
    //            }
    //        }
    //        return H;
    //    }

    inline StabilizerGroupValue conjugateGroupValue(const StabilizerGroup& G, const LimEntry<>* a) {
        StabilizerGroupValue H;
        for (unsigned int i = 0; i < G.size(); i++) {
            H.push_back(*G[i]);
            if (!H[i].commutesWith(a)) {
                // TODO implement and use a new function in LimEntry which directly multiplies the phase by -1
                H[i].setPhase(multiplyPhases(H[i].getPhase(), phase_t::phase_minus_one));
            }
        }
        return H;
    }

    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> getCosetIntersectionElementModuloPhase(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::vector<LimEntry<NUM_QUBITS>*>& H, const LimEntry<NUM_QUBITS>& a, bool& foundElement) {
        cosetIntersectCallCount++;
        clock_t begin = clock();
        static unsigned int callCount = 0;
        callCount++;
        std::vector<LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>> GH_Id = concatenateAndAppendIdentityMatrix(G, H);
        toColumnEchelonFormModuloPhase(GH_Id);

        std::bitset<NUM_QUBITS>               decomposition; // decomposition of 'a'
        LimBitset<NUM_QUBITS, 2 * NUM_QUBITS> a_bitset(a);
        a_bitset = GramSchmidtFastSorted(GH_Id, a_bitset);
        std::bitset<NUM_QUBITS> decomposition_G, decomposition_H; // these bitsets are initialized to 00...0, according to the C++ reference
        bitsetCopySegment(decomposition_G, a_bitset.bits, 0, 0, G.size());
        bitsetCopySegment(decomposition_H, a_bitset.bits, 0, G.size(), G.size() + H.size());
        LimEntry<NUM_QUBITS> a_G = getProductOfElements(G, decomposition_G);
        //        Log::log << "[coset intersection P] got first product. Computing second product.\n"; Log::log.flush();
        LimEntry<NUM_QUBITS> a_H     = getProductOfElements(H, decomposition_H);
        LimEntry<NUM_QUBITS> a_prime = LimEntry<NUM_QUBITS>::multiplyValue(a_G, a_H);
        if (!LimEntry<NUM_QUBITS>::EqualModuloPhase(a, a_prime)) {
            foundElement = false;
        } else {
            foundElement = true;
        }
        cosetIntersectModPTime += clock() - begin;
        return a_G;
    }

    // Given Pauli groups G,H, and Pauli strings a,b, and a phase lambda,
    // Finds an element in the set G intersect lambda a H b,
    // or returns LimEntry::noLIM, if this set is empty
    // TODO refactor to allocate less dynamic memory
    template<std::size_t NUM_QUBITS>
    std::pair<LimEntry<NUM_QUBITS>, bool> getCosetIntersectionElementPauli(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::vector<LimEntry<NUM_QUBITS>*>& H, const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b, phase_t lambda, [[maybe_unused]] Qubit nQubits = 5) {
        if (lambda == phase_t::no_phase) {
            return {LimEntry<NUM_QUBITS>(), false};
        }
        cosetIntersectCallCount++;
        clock_t begin = clock();
        // find an element in G intersect abH modulo phase
        LimEntry<NUM_QUBITS> ab = LimEntry<NUM_QUBITS>::multiplyValue(*a, *b);
        bool                 foundCIEMP;
        LimEntry<NUM_QUBITS> c = getCosetIntersectionElementModuloPhase(G, H, ab, foundCIEMP);
        if (!foundCIEMP) {
            //            std::cout << "[get coset intersection] Even modulo phase there is no element.\n";
            //            std::cout << "[coset intersection] a = " << LimEntry<>::to_string(a, nQubits) << " b = " << LimEntry<>::to_string(b, nQubits) << " c = " << LimEntry<>::to_string(c, nQubits) << " ab = " << LimEntry<>::to_string(ab, nQubits) << " lambda = " << phaseToString(lambda) << '\n';
            //            std::cout << "[coset intersection] G = " << groupToString(G, nQubits) << "  H = " << groupToString(H, nQubits) << "\n";
            cosetIntersectPauliTime += clock() - begin;
            return {LimEntry<NUM_QUBITS>(), false};
        }
        c.setPhase(recoverPhase(G, &c));
        LimEntry<NUM_QUBITS> acb = LimEntry<NUM_QUBITS>::multiplyValue(*a, c);
        acb                      = LimEntry<NUM_QUBITS>::multiplyValue(acb, *b);
        phase_t alpha            = multiplyPhases(acb.getPhase(), getPhaseInverse(lambda));
        // Retrieve the phase of acb in H
        phase_t tau = recoverPhase(H, &acb);
        //Log::log << "[coset intersection] a = " << LimEntry<>::to_string(a, nQubits) << " b = " << LimEntry<>::to_string(b, nQubits) << " c = " << LimEntry<>::to_string(c, nQubits) << " ab = " << LimEntry<>::to_string(ab, nQubits) << " abc = " << LimEntry<>::to_string(acb, nQubits) << " lambda = " << phaseToString(lambda) << " alpha = " << phaseToString(alpha) << " tau = " << phaseToString(tau) << '\n';
        //Log::log << "[coset intersection] G = " << groupToString(G, nQubits) << "  H = " << groupToString(H, nQubits) << "\n";
        if (alpha == tau) {
            cosetIntersectPauliTime += clock() - begin;
            return {c, true};
        }
        // TODO we should just be able to say 'else', because ALWAYS alpha == -tau in this case.
        //    Check if this conjecture is true.
        else if (alpha == multiplyPhases(tau, phase_t::phase_minus_one)) {
            // See if some element of J has xy = -1
            std::vector<LimEntry<NUM_QUBITS>> GintersectH = intersectGroupsModuloPhaseValue(G, H);
            for (std::size_t i = 0; i < GintersectH.size(); i++) {
                if ((!GintersectH[i].commutesWith(b)) ^ (recoverPhase(G, &GintersectH[i]) != recoverPhase(H, &GintersectH[i]))) {
                    cosetIntersectPauliTime += clock() - begin;
                    return {LimEntry<NUM_QUBITS>::multiplyValue(c, recoverElement(G, &GintersectH[i])), true};
                }
            }
        }
        cosetIntersectPauliTime += clock() - begin;
        return {c, false}; // dummy element
    }

    // GH_Id is the concatenation of G and H, to which an identity matrix is appended, and on which Gaussian elimination modulo phase has been performed
    // TODO refactor so that we compute the intersection if needed; otherwise, not. If we compute it, then we give it back to the calling function
    template <std::size_t NUM_QUBITS>
    std::pair<LimEntry<NUM_QUBITS>, bool> getCosetIntersectionElementPauli2(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::vector<LimEntry<NUM_QUBITS>*>& H, const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b, phase_t lambda, const std::vector<LimBitset<NUM_QUBITS, 2*NUM_QUBITS> >& GH_Id_CEF, std::vector<LimEntry<NUM_QUBITS>>& GintersectH, bool& memoizedGintersectH, CachingStrategy cachingStrategy, [[maybe_unused]] const  Qubit nQubits = 5) {
        if (lambda == phase_t::no_phase) {
            return {LimEntry<NUM_QUBITS>(), false};
        }
        cosetIntersectCallCount++;
        clock_t begin = clock();
        // find an element in G intersect abH modulo phase
        LimEntry<NUM_QUBITS> ab = LimEntry<NUM_QUBITS>::multiplyValue(*a, *b);
        bool                 foundCIEMP;
        LimEntry<NUM_QUBITS> c = getCosetIntersectionElementModuloPhase2(G, H, ab, foundCIEMP, GH_Id_CEF);
        if (!foundCIEMP) {
            //            std::cout << "[get coset intersection] Even modulo phase there is no element.\n";
            //            std::cout << "[coset intersection] a = " << LimEntry<>::to_string(a, nQubits) << " b = " << LimEntry<>::to_string(b, nQubits) << " c = " << LimEntry<>::to_string(c, nQubits) << " ab = " << LimEntry<>::to_string(ab, nQubits) << " lambda = " << phaseToString(lambda) << '\n';
            //            std::cout << "[coset intersection] G = " << groupToString(G, nQubits) << "  H = " << groupToString(H, nQubits) << "\n";
            cosetIntersectPauliTime += clock() - begin;
            return {LimEntry<NUM_QUBITS>(), false};
        }
        c.setPhase(recoverPhase(G, &c));
        LimEntry<NUM_QUBITS> acb = LimEntry<NUM_QUBITS>::multiplyValue(*a, c);
        acb                      = LimEntry<NUM_QUBITS>::multiplyValue(acb, *b);
        phase_t alpha            = multiplyPhases(acb.getPhase(), getPhaseInverse(lambda));
        // Retrieve the phase of acb in H
        phase_t tau = recoverPhase(H, &acb);
        //Log::log << "[coset intersection] a = " << LimEntry<>::to_string(a, nQubits) << " b = " << LimEntry<>::to_string(b, nQubits) << " c = " << LimEntry<>::to_string(c, nQubits) << " ab = " << LimEntry<>::to_string(ab, nQubits) << " abc = " << LimEntry<>::to_string(acb, nQubits) << " lambda = " << phaseToString(lambda) << " alpha = " << phaseToString(alpha) << " tau = " << phaseToString(tau) << '\n';
        //Log::log << "[coset intersection] G = " << groupToString(G, nQubits) << "  H = " << groupToString(H, nQubits) << "\n";
        if (alpha == tau) {
            cosetIntersectPauliTime += clock() - begin;
            return {c, true};
        }
            // TODO we should just be able to say 'else', because ALWAYS alpha == -tau in this case.
            //    Check if this conjecture is true.
        else if (alpha == multiplyPhases(tau, phase_t::phase_minus_one)) {
            if ((!memoizedGintersectH && usingLazyMemoizationGroupIntersect(cachingStrategy)) || !usingLazyMemoizationGroupIntersect(cachingStrategy)) {
                GintersectH = intersectGroupsModuloPhaseValue(G, H);
                memoizedGintersectH = true;
            } else {
                intersectionMemoizationHits++;
            }
            // See if some element of J has xy = -1
            for (std::size_t i = 0; i < GintersectH.size(); i++) {
                if ((!GintersectH[i].commutesWith(b)) ^ (recoverPhase(G, &GintersectH[i]) != recoverPhase(H, &GintersectH[i]))) {
                    cosetIntersectPauliTime += clock() - begin;
                    return {LimEntry<NUM_QUBITS>::multiplyValue(c, recoverElement(G, &GintersectH[i])), true};
                }
            }
        }
        cosetIntersectPauliTime += clock() - begin;
        return {c, false}; // dummy element
    }

    template<std::size_t NUM_QUBITS>
    inline LimEntry<NUM_QUBITS> getCosetIntersectionElementModuloPhase2(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::vector<LimEntry<NUM_QUBITS>*>& H, const LimEntry<NUM_QUBITS>& a, bool& foundElement, const std::vector<LimBitset<NUM_QUBITS, 2*NUM_QUBITS>>& GH_Id_CEF) {
        cosetIntersectCallCount++;
        clock_t begin = clock();
        //std::vector<LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>> GH_Id = concatenateAndAppendIdentityMatrix(G, H);
        //toColumnEchelonFormModuloPhase(GH_Id);
        //pruneZeroColumnsModuloPhase(GH_Id);
        //std::sort(GH_Id.begin(), GH_Id.end(), LimBitset<NUM_QUBITS, 2*NUM_QUBITS>::greaterValue);

        std::bitset<NUM_QUBITS>               decomposition; // decomposition of 'a'
        LimBitset<NUM_QUBITS, 2 * NUM_QUBITS> a_bitset(a);
        a_bitset = GramSchmidtFastSorted(GH_Id_CEF, a_bitset);
        std::bitset<NUM_QUBITS> decomposition_G, decomposition_H; // these bitsets are initialized to 00...0, according to the C++ reference
        bitsetCopySegment(decomposition_G, a_bitset.bits, 0, 0, G.size());
        bitsetCopySegment(decomposition_H, a_bitset.bits, 0, G.size(), G.size() + H.size());
        LimEntry<NUM_QUBITS> a_G = getProductOfElements(G, decomposition_G);
        //        Log::log << "[coset intersection P] got first product. Computing second product.\n"; Log::log.flush();
        LimEntry<NUM_QUBITS> a_H     = getProductOfElements(H, decomposition_H);
        LimEntry<NUM_QUBITS> a_prime = LimEntry<NUM_QUBITS>::multiplyValue(a_G, a_H);
        if (!LimEntry<NUM_QUBITS>::EqualModuloPhase(a, a_prime)) {
            foundElement = false;
        } else {
            foundElement = true;
        }
        cosetIntersectModPTime += clock() - begin;
        return a_G;
    }


    // We assume that only vNodes are passed
    // NOT FUNCTIONAL --  Z GROUP IS NOT SUPPORTED
    inline StabilizerGroup constructStabilizerGeneratorSetZ([[maybe_unused]] const vNode& node) {
        StabilizerGroup stabgenset;
        return stabgenset;
        //empty
        //        Edge<vNode> low, high;
        //        low            = node.e[0];
        //        high           = node.e[1];
        //        unsigned int n = node.v;

        // Case 0: Check if this node is the terminal node (aka the Leaf)
        //        if (n == (unsigned int)-1) {
        //            // Return the trivial group.
        //            // This group is generated by the empty set; therefore, we just return the empty stabgenset
        //            return stabgenset;
        //        }
        //        // Case 1: right child is zero
        //        else if (high.isZeroTerminal()) {
        //            //            Log::log << "[stab genZ] |0> knife case  n = " << n << ". Low stabilizer group is:\n";
        //            stabgenset = low.p->limVector; // copies the stabilizer group of the left child
        //                                           //            printStabilizerGroup(stabgenset);
        //            LimEntry<>* idZ = LimEntry<>::getIdentityOperator();
        //            idZ->setOperator(n, 'Z');
        //            stabgenset.push_back(idZ);
        //            //            Log::log << "[stab genZ] Added Z. Now stab gen set is:\n";
        //            //            printStabilizerGroup(stabgenset);
        //            // the matrix set is already in column echelon form,
        //            // so we do not need to perform that step here
        //        }
        //        // Case 2: left child is zero
        //        else if (low.isZeroTerminal()) {
        //            //            Log::log << "[stab genZ] |1> knife case. n = " << n << ". High stabilizer group is:\n";
        //            stabgenset = high.p->limVector;
        //            //            printStabilizerGroup(stabgenset);
        //            LimEntry<>* minusIdZ = LimEntry<>::getMinusIdentityOperator();
        //            minusIdZ->setOperator(n, 'Z');
        //            stabgenset.push_back(minusIdZ);
        //            //            Log::log << "[stab genZ] Added -Z. now stab gen set is:\n";
        //            //            printStabilizerGroup(stabgenset);
        //        }
        //        // Case 3: the node is a 'fork': both its children are nonzero
        //        else {
        //            // Gather the stabilizer groups of the two children
        //            //            Log::log << "[constructStabilizerGeneratorSet] Case fork n = " << n << ".\n";
        //            StabilizerGroup* stabLow  = &(low.p->limVector);
        //            StabilizerGroup* stabHigh = &(high.p->limVector);
        //            // Step 1: Compute the intersection
        //            stabgenset = intersectGroupsZ(*stabLow, *stabHigh);
        //
        //            // Step 2: if some element v is in the set <G> intersect (<H> * -I),
        //            //   then add Z tensor v to the stabgenset
        ////            LimEntry<>* minus = LimEntry<>::getMinusIdentityOperator();
        ////            LimEntry<>* m     = getCosetIntersectionElementPauli(*stabLow, *stabHigh, minus);
        ////            if (m != LimEntry<>::noLIM) {
        ////                m->setOperator(n, 'Z');
        ////                stabgenset.push_back(m);
        ////            }
        //            toColumnEchelonForm(stabgenset);
        //            // todo deallocate minus, m
        //        }
        //
        //        return stabgenset;
    }

    // Construct the stabilizer generator set of 'node' in the Pauli group
    // Puts these generators in column echelon form
    inline StabilizerGroupValue constructStabilizerGeneratorSetPauli(vNode& node, ComplexNumbers& cn, CachingStrategy cachingStrategy) {
        auto       low  = node.e[0];
        auto       high = node.e[1];
        auto const n    = node.v;
        auto       zero = std::array{node.e[0].w.approximatelyZero(), node.e[1].w.approximatelyZero()};
        clock_t    begin = clock();

        // Case 0: Check if this node is the terminal node (aka the Leaf)
        if (n == std::numeric_limits<decltype(n)>::max()) { // TODO replace with a direct check whether 'node' is a terminal node
            // Return the trivial group.
            // This group is generated by the empty set; therefore, we just return the empty stabgenset
            return {};
        }

        StabilizerGroupValue stabgenset;

        if (zero[1]) { // Case 1: right child is zero
            //Log::log << "[stab genPauli] |0> knife case  n = " << n + 1 << ". Low stabilizer group is:\n";
            // TODO first do stabgenset.reserve( low.p->limVector.size() + 1 ) items, then copy the low.p->limVector into stabgenset
            //   This way a reallocation is prevented when the Z operator is added one line later
            stabgenset = toStabilizerGroupValue(low.p->limVector); // copies the stabilizer group of the left child
            //printStabilizerGroup(stabgenset);
            LimEntry<> idZ;
            idZ.setOperator(n, 'Z');
            stabgenset.push_back(idZ);
            //Log::log << "[stab genPauli] Added Z. Now stab gen set is:\n";
            //printStabilizerGroup(stabgenset);
            // the matrix set is already in column echelon form,
            // so we do not need to perform that step here
        } else if (zero[0]) { // Case 2: left child is zero
            //Log::log << "[stab genPauli] |1> knife case. n = " << n + 1 << ". High stabilizer group is:\n";
            // TODO first do stabgenset.reserve( high.p->limVector.size() + 1 ) items, then copy the low.p->limVector into stabgenset
            //   This way a reallocation is prevented when the Z operator is added one line later
            stabgenset = toStabilizerGroupValue(high.p->limVector); // copy the stabilizer of the right child
            //printStabilizerGroup(stabgenset);
            LimEntry<> minusIdZ = LimEntry<>::getMinusIdentityOperator();
            minusIdZ.setOperator(n, 'Z');
            stabgenset.push_back(minusIdZ);
            //Log::log << "[stab genPauli] Added -Z. now stab gen set is:\n";
            //printStabilizerGroup(stabgenset);
        } else { // Case 3: the node is a 'fork': both its children are nonzero
            //                vEdge edgeDummy{&node, Complex::one, nullptr};
            // Gather the stabilizer groups of the two children
            //Log::log << "[constructStabilizerGeneratorSet] Case fork; "  << node << "\n";
            // Step 1: Compute the intersection
            StabilizerGroup*     stabLow  = &(low.p->limVector);
            StabilizerGroup*     stabHigh = &(high.p->limVector);
            StabilizerGroupValue PHP      = conjugateGroupValue(*stabHigh, high.l);
            //Log::log << "[constructStabilizerGeneratorSet] G = Stab(low)  = " << groupToString(*stabLow, n-1) << '\n';
            //Log::log << "[constructStabilizerGeneratorSet] H = Stab(high) = " << groupToString(*stabHigh, n-1) << '\n';
            //Log::log << "[constructStabilizerGeneratorSet] PHP: " << groupToString(PHP, node.e[1].p->v) << '\n';
            stabgenset = intersectGroupsPauli(*stabLow, PHP);
            //Log::log << "[constructStabilizerGeneratorSet] intersection: " << groupToString(stabgenset, n) << '\n';
            //sanityCheckStabilizerGroup(edgeDummy, stabgenset);
            // Step 2: find out whether an element P*P' should be added, where P acts on qubit 'n'
            //Log::log << "[constructStabilizerGeneratorSet] Treating case Z...\n";
            bool foundElementX, foundElementY, foundElementZ;
            LimEntry<> CIE_Z, stabX, stabY, stabZ;

            // Next we do some memoization for getCosetIntersectionElementPauli2. This routine uses the matrix [G H; Id] in column echelon form, and uses the group G intersect H.
            //   Since this routine is called up to two times, we aim to do that work only once
            //   We assume that GH_Id_CEF_memoized is already computed in getIsomorphismPauli, which is always called before this function, and is always called on the same data
            //std::vector<LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>> GH_Id_CEF = concatenateAndAppendIdentityMatrix(*stabLow, *stabHigh);
            //GH_Id_CEF_memoized = concatenateAndAppendIdentityMatrix(*stabLow, *stabHigh);
            //toColumnEchelonFormModuloPhase(GH_Id_CEF_memoized);
            //std::vector<LimEntry<NUM_QUBITS>> GintersectH;
            if (!usingLazyMemoizationGroupIntersect(cachingStrategy)) {
                GintersectH_memoized = intersectGroupsModuloPhaseValue(*stabLow, *stabHigh);
            }
            //memoizedGintersectH = false; // TODO remove this line (to enable memoization)

            // Step 2.1: Find out whether a stabilizer of the form Z*P' exists
            std::tie(CIE_Z, foundElementZ) = getCosetIntersectionElementPauli2(*stabLow, *stabHigh, high.l, high.l, phase_t::phase_minus_one, GH_Id_CEF_memoized, GintersectH_memoized, memoizedGintersectH, cachingStrategy, n - 1);
            if (foundElementZ) {
                stabZ = CIE_Z;
                stabZ.setOperator(n, 'Z');
                stabgenset.push_back(stabZ);
                //Log::log << "[constructStabilizerGeneratorSet] found stabilizer: " << LimEntry<>::to_string(&stab, n) << '\n';
                //sanityCheckStabilizerGroup(edgeDummy, stabgenset);
            }
            if (low.p == high.p) {
                // TODO use cn.getTemporaryComplex instead of getCached - that is faster
                Complex rho      = cn.divCached(node.e[1].w, node.e[0].w);
                phase_t rhoPhase = rho.toPhase();
                cn.returnToCache(rho);
                if (rhoPhase != phase_t::no_phase) {
                    phase_t rhoSquared = multiplyPhases(rhoPhase, rhoPhase);
                    // Step 2.2: Find out whether a stabilizer of the form X*P' exists
                    //Log::log << "[constructStabilizerGeneratorSet] Treating case X...\n";
                    // TODO check if rhoSquared == -1; if so, reuse the result from above (i.e., if foundElementZ, then reuse stabZ, otherwise skip this part)
                    if (rhoSquared == phase_t::phase_minus_one) {
                        stabX = CIE_Z;
                        foundElementX = foundElementZ;
                    }
                    else {
                        std::tie(stabX, foundElementX) = getCosetIntersectionElementPauli2(*stabLow, *stabHigh, high.l, high.l, rhoSquared, GH_Id_CEF_memoized, GintersectH_memoized, memoizedGintersectH, cachingStrategy, n - 1);
                    }
                    if (foundElementX) {
                        LimEntry<> X;
                        X.setOperator(n, pauli_op::pauli_x);
                        //Log::log << "[constructStabilizerGeneratorSet] Just set the X in " << LimEntry<>::to_string(&X) << "\n";
                        X.multiplyBy(high.l);
                        X.multiplyBy(stabX);
                        X.multiplyPhaseBy(rhoPhase);
                        //Log::log << "[constructStabilizerGeneratorSet] found stabilizer: " << LimEntry<>::to_string(&X, n) << '\n';
                        //Log::log << "[constructStabilizerGeneratorSet] with high.l = " << LimEntry<>::to_string(high.l, n) << " coset element = " << LimEntry<>::to_string(stab, n) << ".\n";
                        stabgenset.push_back(X);
                        //sanityCheckStabilizerGroup(edgeDummy, stabgenset);
                    }
                    // Step 2.3: Find out whether a stabilizer of the form Y*P' exists
                    //   In this step, we first check whether a Z-element or an X-element has been found. If so, we don't look for a Y-element.
                    //   Namely, if both a Z and an X-element are stabilizers, then certainly there is a Y-stabilizer, and we do not need to look;
                    //   moreover, if only a Z but no X element was found, then we can be sure that there is no Y-element, and we also do not need to look
                    if (!(foundElementZ || foundElementX)) {
                        //Log::log << "[constructStabilizerGeneratorSet] Treating case Y...\n";
                        phase_t minusRhoSquared = multiplyPhases(rhoSquared, phase_t::phase_minus_one);
                        // if minusRhoSquared == -1, then we may reuse the result from above - from the 'Z' case in step 2.1
                        if (minusRhoSquared == phase_t::phase_minus_one) {
                            stabY = CIE_Z;
                            foundElementX = foundElementZ;
                        }
                        else {
                            std::tie(stabY, foundElementY) = getCosetIntersectionElementPauli2(*stabLow, *stabHigh, high.l, high.l, minusRhoSquared, GH_Id_CEF_memoized, GintersectH_memoized, memoizedGintersectH, cachingStrategy, n - 1);
                        }
                        if (foundElementY) {
                            LimEntry<> X;
                            X.setOperator(n, pauli_op::pauli_y);
                            //Log::log << "[constructStabilizerGeneratorSet] Just set the Y in " << LimEntry<>::to_string(&X, n) << "\n";
                            X.multiplyBy(high.l);
                            X.multiplyBy(stabY);
                            X.multiplyPhaseBy(rhoPhase);
                            X.multiplyPhaseBy(phase_t::phase_minus_i);
                            //Log::log << "[constructStabilizerGeneratorSet] found stabilizer: " << LimEntry<>::to_string(&X, n) << '\n';
                            //Log::log << "[constructStabilizerGeneratorSet] with high.l = " << LimEntry<>::to_string(high.l, n) << " coset element = " << LimEntry<>::to_string(stab, n) << ".\n";
                            stabgenset.push_back(X);
                        }
                    }
                }
            }
            toColumnEchelonForm(stabgenset);
        }
        //            CVec amplitudeVec = getVector(&node);
        //            Log::log << "[constructStabilizerGeneratorSet] Finished. for state " << outputCVec(amplitudeVec) << '\n'
        //            		 << "[constructStabilizerGeneratorSet] Stab = "; //printStabilizerGroup(node.limVector, node.v); Log::log << '\n';

        constructStabilizerTime += clock() - begin;
        return stabgenset;
    }

    // Returns an isomorphism between u and v,
    // or LimEntry<>::noLim if u and v are not isomorphic
    // Assumes that the low edges of u and v have an Identity LIM
    // TODO should we add assertions that u and v do not represent zero vectors?
    // TODO this function does not take into account the different phases... but maybe it doesn't need to...
    inline LimEntry<>* getIsomorphismZ([[maybe_unused]] const vNode* u, [[maybe_unused]] const vNode* v) {
        return LimEntry<>::noLIM;
        //        assert(u != nullptr);
        //        assert(v != nullptr);
        //        //        Log::log << "[getIsomorphismZ] Start.\n";
        ////        LimEntry<>* iso;
        //        //         TODO add assertion that the nodes are on the same number of qubits u->v == v->v
        //        //        assert (u->v == v->v);
        //        Edge<vNode> uLow  = u->e[0];
        //        Edge<vNode> uHigh = u->e[1];
        //        Edge<vNode> vLow  = v->e[0];
        //        Edge<vNode> vHigh = v->e[1];
        //        assert(!(uLow.isZeroTerminal() && uHigh.isZeroTerminal()));
        //        assert(!(vLow.isZeroTerminal() && vHigh.isZeroTerminal()));
        //        // TODO this assertion is not necessarily true; in the normalizeLIMDD function, we hve vLow.l != nullptr
        //        assert(uLow.l == nullptr && vLow.l == nullptr);
        //        // Case 0.1: the nodes are equal
        //        if (u == v) {
        //            //            Log::log << "[getIsomorphismZ] case u == v.\n"; Log::log.flush();
        //            // In this case, we return the Identity operator, which is represented by a null pointer
        //            return nullptr;
        //        }
        //        // Case 0.2: The leaf case.
        //        // TODO this case should already be covered by case 0.1, since in this case v is also the terminal node
        //        //   Do we need this extra check?
        //        else if (vNode::isTerminal(u)) {
        //            //            Log::log << "[getIsomorphismZ] Case u is terminal.\n"; Log::log.flush();
        //            // Return the identity operator, which is represented by a null pointer
        //            return nullptr;
        //        }
        //        // Case 1 ("Left knife"): Left child is nonzero, right child is zero
        //        else if (uHigh.isZeroTerminal()) {
        //            //            Log::log << "[getIsomorphismZ] Case uHigh is terminal\n";
        //            if (!vHigh.isZeroTerminal()) return LimEntry<>::noLIM;
        //            if (uHigh.p != vHigh.p) return LimEntry<>::noLIM;
        //            return LimEntry<>::multiply(*uHigh.l, *vHigh.l);
        //        }
        //        // Case 2 ("Right knife"): Left child is zero, right child is nonzero
        //        else if (uLow.isZeroTerminal()) {
        //            //            Log::log << "[getIsomorphismZ] case uLow is terminal.\n";
        //            if (!vLow.isZeroTerminal()) return LimEntry<>::noLIM; // not isomorphic
        //            if (uLow.p != vLow.p) return LimEntry<>::noLIM;
        //            return nullptr; // return the Identity isomorphism
        //        }
        //        // Case 3 ("Fork"): Both children are nonzero
        //        else {
        //            //            Log::log << "[getIsomorphismZ] case Fork.\n"; Log::log.flush();
        //            //            Log::log << "[getIsomorphismZ] ulw " << uLow.w << " uhw " << uHigh.w << " vlw " << vLow.w << " vhw " << vHigh.w << Log::endl;
        //            // Step 1.2: check if the amplitudes satisfy uHigh = -1 * vHigh
        //            bool amplitudeOppositeSign = uHigh.w.approximatelyEqualsMinus(vHigh.w);
        //            // Step 1.1:  check if the amplitudes are equal, up to a sign
        //            if (!uLow.w.approximatelyEquals(vLow.w) || (!uHigh.w.approximatelyEquals(vHigh.w) && !amplitudeOppositeSign)) return LimEntry<>::noLIM;
        //            //            Log::log << "[getIsomorphismZ] edge weights are approximately equal.\n"; Log::log.flush();
        //            // Step 2: Check if nodes u and v have the same children
        //            if (uLow.p != vLow.p || uHigh.p != vHigh.p) return LimEntry<>::noLIM;
        //            //            Log::log << "[getIsomorphismZ] children of u and v are the same nodes.\n"; Log::log.flush();
        //            // Step 3: (optional) check if the automorphism groups are equal
        //            //            if (!stabilizerGroupsEqual(u->limVector, v->limVector)) {
        //            //                return LimEntry<>::noLIM;
        //            //            }
        //            //            Log::log << "[getIsomorphismZ] the stabilizer Groups of u and v are equal.\n"; Log::log.flush();
        //            // Step 4: If G intersect (H+isoHigh) contains an element P, then Id tensor P is an isomorphism
        //            LimEntry<>* isoHigh = LimEntry<>::multiply(uHigh.l, vHigh.l);
        //            //            Log::log << "[getIsomorphismZ] multiplied high isomorphisms:" << LimEntry<>::to_string(isoHigh) << ".\n"; Log::log.flush();
        //            if (amplitudeOppositeSign) {
        //                //                Log::log << "[getIsomorphismZ] multiplying Phase by -1 because high amplitudes had opposite signs\n"; Log::log.flush();
        //                isoHigh->multiplyPhaseBy(phase_t::phase_minus_one); // multiply by -1
        //            }
        ////            iso = getCosetIntersectionElementPauli(uLow.p->limVector, uHigh.p->limVector, isoHigh);
        ////            //            Log::log << "[getIsomorphismZ] completed coset intersection element.\n"; Log::log.flush();
        ////            if (iso != LimEntry<>::noLIM) {
        ////                //                Log::log << "[getIsomorphismZ] The coset was non-empty; returning element.\n"; Log::log.flush();
        ////                return iso;
        ////            }
        ////             Step 5: If G intersect (H-isomorphism) contains an element P, then Z tensor P is an isomorphism
        //            //            Log::log << "[getIsomorphismZ] multiplying phase by -1.\n"; Log::log.flush();
        //            isoHigh->multiplyPhaseBy(phase_t::phase_minus_one);
        ////            iso = getCosetIntersectionElementPauli(uLow.p->limVector, uHigh.p->limVector, isoHigh);
        ////            //            Log::log << "[getIsomorphismZ] found coset intersection element.\n"; Log::log.flush();
        ////            if (iso != LimEntry<>::noLIM) {
        ////                //                Log::log << "[getIsomorphismZ] Coset was not empty; returning result.\n"; Log::log.flush();
        ////                iso->setOperator(u->v, pauli_op::pauli_z); // TODO should we do this? write a test
        ////                return iso;
        ////            } else {
        //                //                Log::log << "[getIsomorphismZ] Coset was empty; returning -1.\n"; Log::log.flush();
        //                return LimEntry<>::noLIM;
        ////            }
        //        }
    }

    // Assumes that u and v are semi-reduced:
    // - low edge label is identity
    // TODO take the edge weights into account:
    //    in case 3.1
    //    in knife cases
    //    check if uhigh.w = 1 / vhigh.w
    inline void getIsomorphismPauli(const vNode* u, const vNode* v, ComplexNumbers& cn, LimWeight<>& iso, bool& foundIsomorphism, CachingStrategy cachingStrategy) {
        assert(u != nullptr);
        assert(v != nullptr);
        //        Log::log << "[getIsomorphismPauli] Start. states have " << (int) u->v+1 << " qubits.\n";
        assert(u->v == v->v); // Assert u and v have the same nubmer of qubits
        foundIsomorphism  = false;
        Edge<vNode> uLow  = u->e[0];
        Edge<vNode> uHigh = u->e[1];
        Edge<vNode> vLow  = v->e[0];
        Edge<vNode> vHigh = v->e[1];
        // Assert that neither u nor v is the Zero vector
        assert(!(uLow.isZeroTerminal() && uHigh.isZeroTerminal()));
        assert(!(vLow.isZeroTerminal() && vHigh.isZeroTerminal()));
        //Log::log << "[getIsomorphismPauli] Start. u = {" << uLow.w << " * " <<  LimEntry<>::to_string(uLow.l, uLow.p->v) << ", " << uHigh.w << " * "
        //        << LimEntry<>::to_string(uHigh.l, uHigh.p->v) << "}   v = {"
        //        << vLow.w << " * " << LimEntry<>::to_string(vLow.l, vLow.p->v) << ", "
        //        << vHigh.w << " * " << LimEntry<>::to_string(vHigh.l, vHigh.p->v) << "}\n"
        //        << "[getIsomorphismPauli] Stab(u) = " << groupToString(u->limVector, u->v) << "  Stab(v) = " << groupToString(v->limVector, v->v) << "\n";
        //        Log::log << "[getIsomorphismPauli] uLow  = " << uLow.w << " * " << LimEntry<>::to_string(uLow.l, uLow.p->v)   << " vLow.l  = " << vLow.w << " * " << LimEntry<>::to_string(vLow.l, vLow.p->v) << Log::endl;
        //        Log::log << "[getIsomorphismPauli] uHigh = " << uHigh.w<< " * " << LimEntry<>::to_string(uHigh.l, uHigh.p->v) << " vHigh.l = " << vHigh.w << " * "<< LimEntry<>::to_string(vHigh.l, vLow.p->v) << Log::endl;
        if (!LimEntry<>::isIdentityOperator(uLow.l))
            throw std::runtime_error("[getIsomorphismPauli] ERROR low edge of u does not have identity label.\n");
        if (!LimEntry<>::isIdentityOperator(vLow.l))
            throw std::runtime_error("[getIsomorphismPauli] ERROR low edge of v does not have identity label\n");
        auto zeroU = std::array{u->e[0].w.approximatelyZero(), u->e[1].w.approximatelyZero()};
        auto zeroV = std::array{v->e[0].w.approximatelyZero(), v->e[1].w.approximatelyZero()};

        iso.lim.setToIdentityOperator();

        // Case 0: the nodes are equal
        if (u == v) {
            //Log::log << "[getIsomorphismPauli] case u == v.\n";
            Log::log.flush();
            // In this case, we return the Identity operator, which is represented by a null pointer
            foundIsomorphism = true;
        }
        // Case 1 ("Left knife"): Left child is nonzero, right child is zero
        else if (zeroU[1]) {
            //Log::log << "[getIsomorphismPauli] Case |u> = |0>|u'>, since uHigh is zero\n";
            if (zeroV[1]) {
                if (uLow.p == vLow.p) {
                    //            		iso = new LimWeight<>((LimEntry<>*)nullptr);
                    iso.lim.setToIdentityOperator();
                    foundIsomorphism = true;
                }
            } else if (zeroV[0]) {
                if (uLow.p == vHigh.p) {
                    // TODO limdd inspect weight on high edge
                    iso.lim = vHigh.l;
                    iso.lim.setOperator(u->v, 'X');
                    foundIsomorphism = true;
                }
            }
            if (!foundIsomorphism) {
                std::cout << "[getIsomorphism] No isomorphism, case 1" << std::endl;
            }
        }
        // Case 2 ("Right knife"): Left child is zero, right child is nonzero
        else if (zeroU[0]) {
            //Log::log << "[getIsomorphismPauli] case uLow is zero, so |u> = |1>|u'>.\n";
            if (zeroV[0]) {
                // TODO limdd inspect weights
                if (uHigh.p == vHigh.p) {
                    iso.lim = uHigh.l;
                    iso.lim.multiplyBy(vHigh.l);
                    foundIsomorphism = true;
                }
            } else if (zeroV[1]) {
                // TODO limdd inspect weights
                if (uHigh.p == vLow.p) {
                    iso.lim = uHigh.l;
                    iso.lim.setOperator(u->v, 'X');
                    foundIsomorphism = true;
                }
            }
            if (!foundIsomorphism) {
                std::cout << "[getIsomorphism] No isomorphism, case 2" << std::endl;
            }
        }
        // Case 3 ("Fork"): Both children are nonzero
        else {
            // Case 3.1: uLow == vHigh, uHigh == vLow but uLow != uHigh, i.e., the isomorphism's first Pauli operator is an X or Y
            // TODO by handling case 3.1 more efficiently, we can prevent unnecessary copying of u->limVector
            if (uLow.p == vHigh.p && uHigh.p == vLow.p && uLow.p != uHigh.p) {
                // TODO inspect the weights; if they're wrong, then no isomorphism
                // Return lambda^-1 * R * (X tensor P), where
                //    P is the uHigh's edge label
                //    lambda is uHigh's weight
                //    R is an isomorphism between uPrime and v
                //Log::log << "[getIsomorphismPauli] case 3.1: children of nodes are opposite pair. Qubits: " << (int)(u->v) << "\n";
                // TODO refactor this piece of code which swaps two edges
                vNode uPrime;
                uPrime.v         = u->v;
                uPrime.limVector = u->limVector;
                uPrime.e[0]      = u->e[1];
                uPrime.e[0].l    = nullptr;
                uPrime.e[0].w    = u->e[1].w;
                uPrime.e[1]      = u->e[0];
                uPrime.e[1].l    = u->e[1].l;
                uPrime.e[1].w    = u->e[0].w;
                getIsomorphismPauli(&uPrime, v, cn, iso, foundIsomorphism, cachingStrategy);
                if (!foundIsomorphism) return;
                LimEntry<> X = *(u->e[1].l);
                X.setOperator(u->v, pauli_op::pauli_x);
                iso.lim.multiplyBy(X); // TODO can we simply set the operator to X, instead of multiplying?
                foundIsomorphism = true;
                return;
            }
            // Case 3.2: uLow == vLow and uHigh == vHigh
            // Step 1.1: Check if uLow == vLow and uHigh == vHigh, i.e., check if nodes u and v have the same children
            if (uLow.p != vLow.p || uHigh.p != vHigh.p) {
                foundIsomorphism = false;
                Log::log << "[getIsomorphism] No isomorphism, case 3\n";
                return;
            }
            //Log::log << "[getIsomorphismPauli] children of u and v are the same nodes.\n";

            // Next we do some memoization for getCosetIntersectionElementPauli2. This routine uses the matrix [G H; Id] in column echelon form, and uses the group G intersect H.
            //   Since this routine is called up to two times, we aim to do that work only once
            //std::vector<LimBitset<NUM_QUBITS, 2 * NUM_QUBITS>> GH_Id_CEF = concatenateAndAppendIdentityMatrix(uLow.p->limVector, uHigh.p->limVector);
            //toColumnEchelonFormModuloPhase(GH_Id_CEF);
            //std::vector<LimEntry<NUM_QUBITS>> GintersectH;
            //if (!usingLazyMemoizationGroupIntersect(cachingStrategy)) {
            //    GintersectH = intersectGroupsModuloPhaseValue(uLow.p->limVector, uHigh.p->limVector);
            //}
            //memoizedGintersectH = false;
            GH_Id_CEF_memoized = concatenateAndAppendIdentityMatrix(uLow.p->limVector, uHigh.p->limVector);
            toColumnEchelonFormModuloPhase(GH_Id_CEF_memoized);
            //std::vector<LimEntry<NUM_QUBITS>> GintersectH;
            if (!usingLazyMemoizationGroupIntersect(cachingStrategy)) {
                GintersectH_memoized = intersectGroupsModuloPhaseValue(uLow.p->limVector, uHigh.p->limVector);
            }
            memoizedGintersectH = false;


            Complex rhoU = cn.getCached(); // Eventually returned to cache
            Complex rhoV = cn.getCached(); // Eventually returned to cache
            if (uLow.p == uHigh.p) {
                //Log::log << "[getIsomorphismPauli] case low == high.\n";
                Complex rhoUrhoV = cn.getCached();
                ComplexNumbers::div(rhoU, u->e[0].w, u->e[1].w);
                ComplexNumbers::div(rhoV, v->e[0].w, v->e[1].w);
                ComplexNumbers::mul(rhoUrhoV, rhoU, rhoV);
                phase_t lambda = rhoUrhoV.toPhase();
                cn.returnToCache(rhoUrhoV);
                if (lambda != phase_t::no_phase) {
                    bool foundElement{};
                    //std::tie(iso.lim, foundElement) = getCosetIntersectionElementPauli2(uLow.p->limVector, uLow.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF, GintersectH, memoizedGintersectH, cachingStrategy, u->v - 1);
                    std::tie(iso.lim, foundElement) = getCosetIntersectionElementPauli2(uLow.p->limVector, uLow.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF_memoized, GintersectH_memoized, memoizedGintersectH, cachingStrategy, u->v - 1);
                    if (foundElement) {
                        iso.lim.leftMultiplyBy(v->e[1].l);
                        //iso.lim = LimEntry<>::multiply(v->e[1].l, &iso.lim);
                        iso.lim.setOperator(u->v, pauli_op::pauli_x);
                        ComplexNumbers::div(iso.weight, v->e[1].w, u->e[0].w);
                        foundIsomorphism = true;
                        //Log::log << "[getIsomorphismPauli] Case X: Coset was not empty; returning isomorphism " << LimEntry<>::to_string(iso.lim, u->v) << ".\n";
                        cn.returnToCache(rhoV);
                        cn.returnToCache(rhoU);

                        return;
                    }

                    lambda  = multiplyPhases(lambda, phase_t::phase_minus_one);
                    //std::tie(iso.lim, foundElement) = getCosetIntersectionElementPauli2(uLow.p->limVector, uLow.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF, GintersectH, memoizedGintersectH, cachingStrategy, u->v - 1);
                    std::tie(iso.lim, foundElement) = getCosetIntersectionElementPauli2(uLow.p->limVector, uLow.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF_memoized, GintersectH_memoized, memoizedGintersectH, cachingStrategy, u->v - 1);
                    if (foundElement) {
                        iso.lim.leftMultiplyBy(v->e[1].l);
                        //iso.lim = LimEntry<>::multiplyValue(v->e[1].l, &iso.lim);
                        iso.lim.setOperator(u->v, pauli_op::pauli_y);
                        ComplexNumbers::div(iso.weight, v->e[1].w, u->e[0].w);
                        iso.weight.multiplyByMinusi();
                        foundIsomorphism = true;
                        //Log::log << "[getIsomorphismPauli] Case Y: Coset was not empty; returning isomorphism " << LimEntry<>::to_string(iso.lim, u->v) << ".\n";
                        cn.returnToCache(rhoV);
                        cn.returnToCache(rhoU);

                        return;
                    }
                }
            }

            Complex rhoVdivRhoU = cn.getCached();
            ComplexNumbers::div(rhoU, u->e[1].w, u->e[0].w);
            ComplexNumbers::div(rhoV, v->e[1].w, v->e[0].w);
            ComplexNumbers::div(rhoVdivRhoU, rhoV, rhoU); // TODO it suffices to allocate only two cached Complex objects
            phase_t lambda = rhoVdivRhoU.toPhase();

            cn.returnToCache(rhoVdivRhoU);
            cn.returnToCache(rhoV);
            cn.returnToCache(rhoU);
#ifndef NDEBUG
            if (lambda == phase_t::no_phase) {
                Log::log << "[getIsomorphismPauli] Edge weights differ by a factor " << rhoVdivRhoU << " != +/- 1,i so returning noLIM.\n";
                foundIsomorphism = false;
                std::cout << "[getIsomorphism] No isomorphism, case 4" << std::endl;
                return;
            }
#endif
            //            Log::log << "[getIsomorphismPauli] edge weights differ by a factor " << phaseToString(lambda) << ".\n";
            //
            //            Log::log << "[getIsomorphismPauli] Looking for isomorphism I tensor P.\n";
            //iso.weight = cn.divCached(v->e[0].w, u->e[0].w);
            ComplexNumbers::div(iso.weight, v->e[0].w, u->e[0].w);

            //            Log::log << "[getIsomorphismPauli] uLow.p->limVector  = "; printStabilizerGroup(uLow.p->limVector, uLow.p->v); Log::log << '\n';
            //            Log::log << "[getIsomorphismPauli] uHigh.p->limVector = "; printStabilizerGroup(uHigh.p->limVector, uHigh.p->v); Log::log << '\n';
            // TODO use iso.lim instead of temp
            //auto [temp, foundElement] = getCosetIntersectionElementPauli2(uLow.p->limVector, uHigh.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF, GintersectH, memoizedGintersectH, cachingStrategy, u->v);
            auto [temp, foundElement] = getCosetIntersectionElementPauli2(uLow.p->limVector, uHigh.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF_memoized, GintersectH_memoized, memoizedGintersectH, cachingStrategy, u->v);
            if (foundElement) {
                //Log::log << "[getIsomorphismPauli] Coset was not empty; current Lim: " << LimEntry<>::to_string(iso.lim, u->v) << "\n";
                iso.lim          = temp;
                foundIsomorphism = true;
                //                Log::log << "[getIsomorphismPauli] Found coset intersection element " << LimEntry<>::to_string(iso->lim, u->v) << '\n';
                return;
            }
            //Log::log << "[getIsomorphismPauli] Coset was empty; so no isomorphism starts with Id.\n";
            // Step 3: If G intersect (H-isomorphism) contains an element P, then Z tensor P is an isomorphism
            //Log::log << "[getIsomorphismPauli] multiplying phase by -1.\n";
            lambda = multiplyPhases(lambda, phase_t::phase_minus_one);
            //std::tie(temp, foundElement) = getCosetIntersectionElementPauli2(uLow.p->limVector, uHigh.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF, GintersectH, memoizedGintersectH, cachingStrategy, u->v);
            std::tie(temp, foundElement) = getCosetIntersectionElementPauli2(uLow.p->limVector, uHigh.p->limVector, v->e[1].l, u->e[1].l, lambda, GH_Id_CEF_memoized, GintersectH_memoized, memoizedGintersectH, cachingStrategy, u->v);
            if (foundElement) {
                //Log::log << "[getIsomorphismPauli] Coset was not empty; current Lim: " << LimEntry<>::to_string(iso.lim, u->v) << "\n";
                iso.lim = temp;
                iso.lim.setOperator(u->v, pauli_op::pauli_z);
                foundIsomorphism = true;
                //Log::log << "[getIsomorphismPauli] Coset was not empty; returning result.\n";
            } else {
                Log::log << "[getIsomorphismPauli] Coset was empty; returning noLIM.\n";
                std::cout << "Stab(u) = " << groupToString(u->e[0].p->limVector, u->v) << "\n"
                          << "Stab(v) = " << groupToString(u->e[1].p->limVector, v->v) << "\n"
                          << "uHighlim= " << LimEntry<>::to_string(uHigh.l, u->v-1) << "\n"
                          << "vHighlim= " << LimEntry<>::to_string(vHigh.l, v->v-1) << "\n"
                          << "u->v    = " << (int) u->v << "   v->v = " << (int) v->v << "\n"
                          << "ulow  = " << uLow << "\n"
                          << "uhigh = " << uHigh << "\n"
                          << "vlow  = " << vLow  << "\n"
                          << "vhigh = " << vHigh << "\n";
                std::cout << "case 5" << std::endl;
            }
        }
    }

    // Choose the label on the High edge, in the Z group
    inline LimEntry<>* highLabelZ([[maybe_unused]] const vNode* u, [[maybe_unused]] const vNode* v, [[maybe_unused]] LimEntry<>* vLabel, [[maybe_unused]] Complex& weight, [[maybe_unused]] bool& s) {
        return LimEntry<>::noLIM;
        // We assert that the LIM has phase +1  (we expect normalizeLIMDD to guarantee this)
        //        assert(LimEntry<>::getPhase(vLabel) == phase_t::phase_one);
        //        //        Log::log << "[highLabelZWeight] Start; |Gu| = " << u->limVector.size() << " |Gv| = " << v->limVector.size() << ".\n"; Log::log.flush();
        //        StabilizerGroup GH = groupConcatenate(u->limVector, v->limVector);
        //        //        Log::log << "[highLabelZWeight] Concatenated; |GH| = " << GH.size() << Log::endl;
        //        toColumnEchelonForm(GH);
        //        //        Log::log << "[highLabelZWeight] to CEF'ed; now |GH| = " << GH.size() << Log::endl;
        //        LimEntry<> newHighLabel = GramSchmidt(GH, vLabel);
        //        // Set the new phase to +1
        //        newHighLabel.setPhase(phase_t::phase_one);
        //        s = false;
        //        if (weight.lexLargerThanxMinusOne()) {
        //            //            Log::log << "[highLabelZWeight] Multiplying weight by -1, since weight = " << weight << ".\n";
        //            weight.multiplyByMinusOne(true);
        //            s = true;
        //        }
        //        //        Log::log << "[highLabelZWeight] end.\n"; Log::log.flush();
        //        return new LimEntry<>(newHighLabel);
    }

    // Returns the lexicographically smallest LIM R such that R * |v> == lim * |v>
    // This is useful when a canonical edge is needed for a cache entry
    // TODO in Pauli LIMDD, we need to right-multiply the LIM here; whereas in other applications we need a left-multiplication
    //    make sure the left and right-handed multiplications go well

    template<class Node>
    inline LimEntry<> getRootLabel([[maybe_unused]]const Node* v, [[maybe_unused]] const LimEntry<>* lim) {
        throw std::runtime_error("ERROR function 'getRootLabel' is not implemented!\n");
    }

    inline LimEntry<> getRootLabel(const vNode* v, const LimEntry<>* lim) {
        return GramSchmidtFastSorted(v->limVector, lim);
    }

    // ********** These functions catch PauliAlgebra functions when they are called on Matrix objects

    //		static LimEntry<>* highLabelZ(const mNode* u, const mNode* v, LimEntry<>* vLabel) {
    //			Log::log << "[highLabelZ] Called with matrix node. Throwing exception.\n" << u << v << vLabel << Log::endl;
    //			throw std::exception();
    //		}
    //
    //		static LimEntry<>* highLabelPauli(const mNode* u, const mNode* v, LimEntry<>* vLabel) {
    //			Log::log << "[highLabelPauli] Called with matrix node. Throwing exception.\n" << u << v << vLabel << Log::endl;
    //			throw std::exception();
    //		}
    //
    //		static LimEntry<>* getIsomorphismZ(const mNode* u, const mNode* v) {
    //			Log::log << "[getIsomorphismZ] called with matrix nodes. Throwing exception.\n" << u << v << Log::endl;
    //			throw std::exception();
    //		}
    //
    //		static LimEntry<>* getIsomorphismPauli(const mNode* u, const mNode* v) {
    //			Log::log << "[getIsomorphismPauli] called with matrix nodes. Throwing exception.\n" << u << v << Log::endl;
    //			throw std::exception();
    //		}

    inline void conjugateWithHadamard(LimEntry<>& lim, Qubit target) {
        pauli_op op = (pauli_op) lim.getQubit(target);
        switch(op) {
            case pauli_x:
                lim.setOperator(target, pauli_z);
                break;
            case pauli_y:
                lim.multiplyPhaseBy(phase_t::phase_minus_one);
                break;
            case pauli_z:
                lim.setOperator(target, pauli_x);
                break;
            default:
                break;
        }
    }

    inline void conjugateWithPhaseGate(LimEntry<>& lim, Qubit target, bool inverse) {
        pauli_op op = (pauli_op) lim.getQubit(target);
        switch(op) {
            case pauli_x:
            case pauli_y:
                if (inverse) {
                    lim.multiplyPhaseBy(phase_t::phase_minus_i);
                } else {
                    lim.multiplyPhaseBy(phase_t::phase_i);
                }
                break;
            case pauli_z:
                break;
            default:
                break;
        }
    }

    // For a Controlled Pauli gate 'gate', sets lim := gate * lim * gate
    // how to conjugate X with negative controlled Y?
    inline void conjugateWithControlledPauliGate(LimEntry<>& lim, const CliffordGate gate) {
        pauli_op pControl = (pauli_op) lim.getQubit(gate.control.qubit);
        pauli_op pTarget  = (pauli_op) lim.getQubit(gate.target);
        if (pControl == pauli_x || pControl == pauli_y) {
            lim.leftMultiplyBy(gate.target, (pauli_op)gate.gateType);
        }
        if (!LimEntry<>::commutesWith(pTarget, (pauli_op) gate.gateType)) {
            // right-multiply pControl by Z
            lim.multiplyByZ(gate.control.qubit);
        }
//        if ((pControl == pauli_id || pControl == pauli_y) && (!LimEntry<>::commutesWith(pTarget, (pauli_op) gate.gateType)) && gate.control.type == Control::Type::neg) {
//            lim.multiplyPhaseByMinusOne();
//        }
    }

} // namespace dd
#endif //DDPACKAGE_PAULIALGEBRA_HPP
