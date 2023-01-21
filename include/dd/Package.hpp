/*
* This file is part of the MQT DD Package which is released under the MIT license.
* See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
*/

#ifndef DDpackage_H
#define DDpackage_H

#include "CVecUtilities.hpp"
#include "Complex.hpp"
#include "ComplexCache.hpp"
#include "ComplexNumbers.hpp"
#include "ComplexTable.hpp"
#include "ComplexValue.hpp"
#include "ComputeTable.hpp"
#include "Control.hpp"
#include "Definitions.hpp"
#include "DensityNoiseTable.hpp"
#include "Edge.hpp"
#include "Export.hpp"
#include "GateMatrixDefinitions.hpp"
#include "LimCache.hpp"
#include "LimFunctionality.hpp"
#include "LimTable.hpp"
#include "Log.hpp"
#include "Node.hpp"
#include "PauliAlgebra.hpp"
#include "PauliUtilities.hpp"
#include "QuantumGate.hpp"
#include "StochasticNoiseOperationTable.hpp"
#include "ToffoliTable.hpp"
#include "UnaryComputeTable.hpp"
#include "UniqueTable.hpp"

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace dd {

    struct DDPackageConfig {
        //Note the order of parameters here must be the *same* as in the template definition.
        static constexpr std::size_t UT_VEC_NBUCKET                 = 32768U;
        static constexpr std::size_t UT_VEC_INITIAL_ALLOCATION_SIZE = 2048U;
        static constexpr std::size_t UT_MAT_NBUCKET                 = 32768U;
        static constexpr std::size_t UT_MAT_INITIAL_ALLOCATION_SIZE = 2048U;
        static constexpr std::size_t CT_VEC_ADD_NBUCKET             = 16384U;
        static constexpr std::size_t CT_MAT_ADD_NBUCKET             = 16384U;
        static constexpr std::size_t CT_MAT_TRANS_NBUCKET           = 4096U;
        static constexpr std::size_t CT_MAT_CONJ_TRANS_NBUCKET      = 4096U;
        static constexpr std::size_t CT_MAT_VEC_MULT_NBUCKET        = 16384U;
        static constexpr std::size_t CT_MAT_MAT_MULT_NBUCKET        = 16384U;
        static constexpr std::size_t CT_VEC_KRON_NBUCKET            = 4096U;
        static constexpr std::size_t CT_MAT_KRON_NBUCKET            = 4096U;
        static constexpr std::size_t CT_VEC_INNER_PROD_NBUCKET      = 4096U;
        static constexpr std::size_t CT_DM_NOISE_NBUCKET            = 1U;
        static constexpr std::size_t UT_DM_NBUCKET                  = 1U;
        static constexpr std::size_t UT_DM_INITIAL_ALLOCATION_SIZE  = 1U;
        static constexpr std::size_t CT_DM_DM_MULT_NBUCKET          = 1U;
        static constexpr std::size_t CT_DM_ADD_NBUCKET              = 1U;

        // The number of different quantum operations. I.e., the number of operations defined in the QFR OpType.hpp
        // This parameter is required to initialize the StochasticNoiseOperationTable.hpp
        static constexpr std::size_t STOCHASTIC_CACHE_OPS = 1;
    };

    template<std::size_t UT_VEC_NBUCKET                 = DDPackageConfig::UT_VEC_NBUCKET,
             std::size_t UT_VEC_INITIAL_ALLOCATION_SIZE = DDPackageConfig::UT_VEC_INITIAL_ALLOCATION_SIZE,
             std::size_t UT_MAT_NBUCKET                 = DDPackageConfig::UT_MAT_NBUCKET,
             std::size_t UT_MAT_INITIAL_ALLOCATION_SIZE = DDPackageConfig::UT_MAT_INITIAL_ALLOCATION_SIZE,
             std::size_t CT_VEC_ADD_NBUCKET             = DDPackageConfig::CT_VEC_ADD_NBUCKET,
             std::size_t CT_MAT_ADD_NBUCKET             = DDPackageConfig::CT_MAT_ADD_NBUCKET,
             std::size_t CT_MAT_TRANS_NBUCKET           = DDPackageConfig::CT_MAT_TRANS_NBUCKET,
             std::size_t CT_MAT_CONJ_TRANS_NBUCKET      = DDPackageConfig::CT_MAT_CONJ_TRANS_NBUCKET,
             std::size_t CT_MAT_VEC_MULT_NBUCKET        = DDPackageConfig::CT_MAT_VEC_MULT_NBUCKET,
             std::size_t CT_MAT_MAT_MULT_NBUCKET        = DDPackageConfig::CT_MAT_MAT_MULT_NBUCKET,
             std::size_t CT_VEC_KRON_NBUCKET            = DDPackageConfig::CT_VEC_KRON_NBUCKET,
             std::size_t CT_MAT_KRON_NBUCKET            = DDPackageConfig::CT_MAT_KRON_NBUCKET,
             std::size_t CT_VEC_INNER_PROD_NBUCKET      = DDPackageConfig::CT_VEC_INNER_PROD_NBUCKET,
             std::size_t CT_DM_NOISE_NBUCKET            = DDPackageConfig::CT_DM_NOISE_NBUCKET,
             std::size_t UT_DM_NBUCKET                  = DDPackageConfig::UT_DM_NBUCKET,
             std::size_t UT_DM_INITIAL_ALLOCATION_SIZE  = DDPackageConfig::UT_DM_INITIAL_ALLOCATION_SIZE,
             std::size_t CT_DM_DM_MULT_NBUCKET          = DDPackageConfig::CT_DM_DM_MULT_NBUCKET,
             std::size_t CT_DM_ADD_NBUCKET              = DDPackageConfig::CT_DM_ADD_NBUCKET,
             std::size_t STOCHASTIC_CACHE_OPS           = DDPackageConfig::STOCHASTIC_CACHE_OPS>
    class Package {
        ///
        /// Complex number handling
        ///
    public:
        ComplexNumbers   cn{};
        LimFunctionality lf{};

        ///
        /// Construction, destruction, information and reset
        ///
    public:
        static constexpr std::size_t maxPossibleQubits = static_cast<std::make_unsigned_t<Qubit>>(std::numeric_limits<Qubit>::max()) + 1U;
        static constexpr std::size_t defaultQubits     = 128;
        // Choose which group is used for LIMDD's isomorphism merging subroutines
        static constexpr LIMDD_group defaultGroup = LIMDD_group::Pauli_group;
        //        static constexpr LIMDD_group defaultGroup = LIMDD_group::QMDD_group;

        explicit Package(std::size_t nq = defaultQubits, LIMDD_group _group = defaultGroup, bool outputToLog = false, CachingStrategy _cachingStrategy = (CachingStrategy)(CachingStrategy::cliffordSpecialCaching | CachingStrategy::lazyMemoizationGroupIntersect | CachingStrategy::smartStabilizerGeneration | CachingStrategy::skipIdentityGateMultiplication)):
            cn(ComplexNumbers()), nqubits(nq), group(_group), cachingStrategy(_cachingStrategy) {
            resize(nq);
            Log::log.verbose = outputToLog;
            if (group == QMDD_group) cachingStrategy = QMDDCachingStrategy;
        };
        ~Package()                      = default;
        Package(const Package& package) = delete;

        Package& operator=(const Package& package) = delete;

        // resize the package instance
        void resize(std::size_t nq) {
            if (nq > maxPossibleQubits) {
                throw std::invalid_argument("Requested too many qubits from package. Qubit datatype only allows up to " +
                                            std::to_string(maxPossibleQubits) + " qubits, while " +
                                            std::to_string(nq) + " were requested. Please recompile the package with a wider Qubit type!");
            }
            nqubits = nq;
            vUniqueTable.resize(nqubits);
            mUniqueTable.resize(nqubits);
            dUniqueTable.resize(nqubits);
            stochasticNoiseOperationCache.resize(nqubits);
            IdTable.resize(nqubits);
        }

        // reset package state
        void reset() {
            clearUniqueTables();
            clearComputeTables();
            cn.clear();
        }

        // getter for qubits
        [[nodiscard]] auto qubits() const { return nqubits; }

    private:
        std::size_t nqubits;
        LIMDD_group group;
        CachingStrategy cachingStrategy;

        ///
        /// Vector nodes, edges and quantum states
        ///

        // Done limdd: Add LIMs for Stabilizer Groups to nodes
    public:
        vEdge normalize(const vEdge& e, bool cached) {
            //        	std::cout << "[normalize] start. Edge is currently " << e;
            auto zero = std::array{e.p->e[0].w.approximatelyZero(), e.p->e[1].w.approximatelyZero()};

            // make sure to release cached numbers approximately zero, but not exactly zero
            if (cached) {
                for (auto i = 0U; i < RADIX; i++) {
                    if (zero[i] && e.p->e[i].w != Complex::zero) {
                        cn.returnToCache(e.p->e[i].w);
                        e.p->e[i] = vEdge::zero;
                    }
                }
            }

            if (zero[0]) {
                // all equal to zero
                if (zero[1]) {
                    if (!cached && !e.isTerminal()) {
                        // If it is not a cached computation, the node has to be put back into the chain
                        vUniqueTable.returnNode(e.p);
                    }
                    return vEdge::zero;
                }

                auto  r = e;
                auto& w = r.p->e[1].w;
                if (cached && !w.exactlyOne()) {
                    r.w = w;
                } else {
                    r.w = cn.lookup(w);
                }
                w = Complex::one;
                return r;
            }

            if (zero[1]) {
                auto  r = e;
                auto& w = r.p->e[0].w;
                if (cached && !w.exactlyOne()) {
                    r.w = w;
                } else {
                    r.w = cn.lookup(w);
                }
                w = Complex::one;
                return r;
            }

            //            std::cout << "[normalize] step 1/5: Case fork. Currently edge is " << e;

            const auto mag0         = ComplexNumbers::mag2(e.p->e[0].w);
            const auto mag1         = ComplexNumbers::mag2(e.p->e[1].w);
            const auto norm2        = mag0 + mag1;
            const auto mag2Max      = (mag0 + ComplexTable<>::tolerance() >= mag1) ? mag0 : mag1;
            const auto argMax       = (mag0 + ComplexTable<>::tolerance() >= mag1) ? 0 : 1;
            const auto norm         = std::sqrt(norm2);
            const auto magMax       = std::sqrt(mag2Max); // TODO this looks like it introduces numerical errors in the case when the edge weights are real, or purely imaginary, but not complex, which happens often; perhaps better take this into account, e.g. replace this with "magMAg = abs(e.p->e[argMax].w);"  ?
            const auto commonFactor = norm / magMax;

            //            std::cout << "[normalize] step 2/5: norm " << norm << " magMag " << magMax << " commonFactor " << commonFactor << "\n";

            auto  r   = e;
            auto& max = r.p->e[argMax];
            if (cached && !max.w.exactlyOne()) { // TODO LV: I don't understand; if max.w is exactly one, then r.w will be looked up in the Complex Numbers Table, even when `cached=true`. Why? The user expects that, if cached=true, then r.w is a cached value, no?
                //Log::log << "[normalizeQMDD] NOT looking up r.w in Complex Numbers Table. cached = " << cached << ", max.w.exactlyOne() = " << max.w.exactlyOne() << "\n";
                r.w = max.w;
                r.w.r->value *= commonFactor;
                r.w.i->value *= commonFactor;
            } else {
                //Log::log << "[normalizeQMDD] looking up r.w in Complex Numbers Table. cached = " << cached << ", max.w.exactlyOne() = " << max.w.exactlyOne() << "\n";
                r.w = cn.lookup(CTEntry::val(max.w.r) * commonFactor, CTEntry::val(max.w.i) * commonFactor);
                if (r.w.approximatelyZero()) {
                    return vEdge::zero;
                }
            }

            //            std::cout << "[normalize] step 3/5 edge is " << r;
            //            std::cout << "[normalize] looking up " << (magMax / norm) << " in ComplexNumbers cache.\n";

            max.w = cn.lookup(magMax / norm, 0.);
            if (max.w == Complex::zero)
                max = vEdge::zero;

            //            std::cout << "[normalize] step 4/5 edge is " << r;

            const auto argMin = (argMax + 1) % 2;
            auto&      min    = r.p->e[argMin];
            if (cached) {
                cn.returnToCache(min.w);
                ComplexNumbers::div(min.w, min.w, r.w);
                min.w = cn.lookup(min.w);
            } else {
                //            	std::cout << "[normalize] now cached, so getting temp numer. edge is " << r << "\n";
                auto c = cn.getTemporary();
                ComplexNumbers::div(c, min.w, r.w);
                min.w = cn.lookup(c);
            }
            if (min.w == Complex::zero) {
                min = vEdge::zero;
            }
            //            std::cout << "[normalize step 5/5 edge is " << r;

            return r;
        }

        // DEPRECATED  --  Z GROUP IS NOT SUPPORTED
        // Returns an edge to a node isomorphic to e.p
        // The edge is labeled with a LIM
        // the node e.p is canonical, according to <Z>-LIMDD reduction rules
        vEdge normalizeLIMDDZ(const vEdge& e, [[maybe_unused]] bool cached) {
            return e;
            // Step 1: Make sure the weight on the LIMs is +1
            //            if (!(LimEntry<>::getPhase(e.p->e[0].l) == phase_t::phase_one &&
            //                  LimEntry<>::getPhase(e.p->e[1].l) == phase_t::phase_one)) {
            //                throw std::runtime_error("[normalizeLIMDD] ERROR phase in LIM is not +1.");
            //            }
            //
            //            auto r = normalize(e, cached);
            //
            //            auto zero = std::array{e.p->e[0].w.approximatelyZero(), e.p->e[1].w.approximatelyZero()};
            //
            //            // Case 1 ("Low Knife"):  high edge = 0, low edge is nonzero
            //            if (zero[1]) {
            //                // Step 1: Set the root edge label to 'Identity tensor R'
            //                r.l = r.p->e[0].l;
            //                // Step 2: Set the low edge label to 'Identity'
            //                r.p->e[0].l = nullptr;
            //                return r;
            //            }
            //            // Case 2 ("High Knife"):  low edge = 0, high edge is nonzero
            //            if (zero[0]) {
            //                // Step 1: Set the root edge pointer to 'Identity tensor (low edge label)'
            //                r.l = r.p->e[1].l;
            //                // Step 2: Set the high edge label to 'Identity'
            //                r.p->e[1].l = nullptr;
            //                return r;
            //            }
            //
            //            // Case 3 ("Fork"):  both edges of e are non-zero
            //            //            std::cout << "[normalizeLIMDD] case Fork. Setting data.\n";
            //            //            std::cout.flush();
            //            LimEntry<>* lowLim = r.p->e[0].l;
            //            LimEntry<>* higLim = r.p->e[1].l;
            //            // Step 1: Make a new LIM, which is the left LIM multiplied by the right LIM
            //            //            std::cout << "[normalizeLIMDD] Step 1: multiply.\n";
            //            //            std::cout.flush();
            //            //            LimEntry<>* higLimTemp = LimEntry<>::multiply(lowLim, higLim);
            //            r.p->e[1].l = LimEntry<>::multiply(lowLim, higLim); // TODO memory leak
            //            // Step 2: Make the left LIM Identity
            //            //            std::cout << "[normalizeLIMDD] Step 2: Set low edge to nullptr.\n";
            //            //            std::cout.flush();
            //            r.p->e[0].l   = nullptr;
            //            vNode oldNode = *(r.p); // make a copy of the old node
            //            // Step 3: Choose a canonical right LIM
            //            //            std::cout << "[normalizeLIMDD] Step 3: pick High Label.\n";
            //            //            std::cout.flush();
            //            bool        s           = false;
            //            LimEntry<>* higLimTemp2 = highLabelZ(r.p->e[0].p, r.p->e[1].p, r.p->e[1].l, r.p->e[1].w, s);
            //            r.p->e[1].l             = limTable.lookup(*higLimTemp2);
            //            limTable.incRef(r.p->e[1].l);
            //            //            std::cout << "[normalizeLIMDD] Found high label: " << LimEntry<>::to_string(r.p->e[1].l) << "\n";
            //            //            std::cout.flush();
            //            // Step 4: Find an isomorphism 'iso' which maps the new node to the old node
            //            //            std::cout << "[normalizeLIMDD] Step 4: find an isomorphism.\n";
            //            //            std::cout.flush();
            //            LimEntry<>* iso = getIsomorphismZ(r.p, &oldNode); // TODO memory leak: this Lim is not freed
            //            assert(iso != LimEntry<>::noLIM);
            //            // Root label := root label * (Id tensor (A)) * K
            //            // Step 5: Use R as the LIM for the incoming edge e
            //            //            std::cout << "[normalizeLIMDD] Step 5: Repair the root edge.\n";
            //            //            std::cout.flush();
            //            r.l = LimEntry<>::multiply(r.l, lowLim); // TODO memory leak
            //                                                     //            std::cout << "[normalizeLIMDD] Step 5.1: Second multiplication.\n";
            //                                                     //            std::cout.flush();
            //            r.l = LimEntry<>::multiply(r.l, iso);    // TODO memory leak
            //            // Step 6: Lastly, to make the edge canonical, we make sure the phase of the LIM is +1; to this end, we multiply the weight r.w by the phase of the Lim r.l
            //            //            std::cout << "[normalizeLIMDD] Step 6: Set the LIM phase to 1.\n";
            //            //            std::cout.flush();
            //            if (r.l->getPhase() == phase_t::phase_minus_one) {
            //                // Step 6.1: multiply the weight 'r.w' by -1
            //                r.w.multiplyByMinusOne();
            //                // Step 6.2: Make the phase of r.l '+1'
            //                r.l->setPhase(phase_t::phase_one);
            //            }
            //            // Step 7: lastly, we should multiply by II...IZ if the highLabel method multiplied the high edge weight by -1
            //            if (s) {
            //                //                LimEntry<> Z;
            //                //                Z.setOperator(r.p->v, 'Z');
            //                //                r.l->multiplyBy(Z);
            //            }
            //
            //            // TODO this procedure changes the weights on the low and high edges. Should we call normalize again?
            //            // Should we *not* call normalize at the beginning of the procedure?
            //
            //            return r;
        }

    public:
        // Finds a high label for a node with low child u and high child v, with current high edge label vLabel, and current high LIM vLabel
        // Sets the
        // Here we demand that 'weight' and 'weightInv' are retrieved with ComplexTable.getTemporary(..),
        // since they will be assigned values but will not be looked up in the ComplexTable
        void highLabelPauli(vNode* u, vNode* v, LimEntry<>* vLabel, Complex& lowWeight, Complex& highWeight, LimEntry<>& newHighLabel) {
            //Log::log << "[highLabelPauli] low: " << lowWeight << " * I; high: " << highWeight << " * " << *vLabel << '\n';
            //LimEntry<>* newHighLabel;
            if (u == v) {
                newHighLabel = GramSchmidtFastSorted(u->limVector, vLabel, u->v);
                highWeight.multiplyByPhase(newHighLabel.getPhase());
                //Log::log << "[highLabelPauli] case u = v; canonical lim is " << newHighLabel << " so multiplying weight by " << phaseToString(newHighLabel.getPhase()) << ", result: weight = " << highWeight << '\n';
                newHighLabel.setPhase(phase_t::phase_one);

                fp lomag2 = ComplexNumbers::mag2(lowWeight);
                fp himag2 = ComplexNumbers::mag2(highWeight);
                if (himag2 > lomag2) {
                    //Log::log << "[highLabelPauli] high is larger than low.\n";
                    // Swap low, high
                    Complex hiTemp = cn.getCached(lowWeight);
                    Complex loTemp = cn.getCached(highWeight);
                    vEdge   lo{u, hiTemp, nullptr};
                    vEdge   hi{u, loTemp, nullptr};
                    //Log::log << "[highLabelPauli] before normalize: loTemp = " << loTemp << "; hiTemp = " << hiTemp << '\n';
                    // Normalize low, high
                    vNode tempNode{{lo, hi}, nullptr, {}, 0, (Qubit)(u->v + 1)};
                    vEdge tempEdge{&tempNode, Complex::one, nullptr};
                    tempEdge = normalize(tempEdge, false);
                    //Log::log << "[highlabelPauli] after  normalize: loTemp = " << loTemp << "; hiTemp = " << hiTemp << '\n';
                    //Log::log << "[highlabelPauli] after  normalize: lo edge= " << tempEdge.p->e[0].w << "; hiEdge = " << tempEdge.p->e[1].w << '\n';

                    // Now the weights are normalized
                    //highWeight.setVal(tempEdge.p->e[0].w);
                    //lowWeight.setVal(tempEdge.p->e[1].w);
                    highWeight.r->value = CTEntry::val(tempEdge.p->e[0].w.r);
                    highWeight.i->value = CTEntry::val(tempEdge.p->e[0].w.i);
                    lowWeight.r->value  = CTEntry::val(tempEdge.p->e[1].w.r);
                    lowWeight.i->value  = CTEntry::val(tempEdge.p->e[1].w.i);

                    //                		Log::log << "[highLabelPauli] (case high > low) new low = " << lowWeight << "; new high = " << highWeight << "\n";
                    cn.returnToCache(loTemp);
                    cn.returnToCache(hiTemp);
                }
                if (CTEntry::val(highWeight.r) < 0 || (CTEntry::approximatelyEquals(highWeight.r, &ComplexTable<>::zero) && CTEntry::val(highWeight.i) < 0)) {
                    highWeight.multiplyByMinusOne(true);
                    //Log::log << "[highLabelPauli] the high edge weight is flipped. New weight is " << highWeight << ".\n";
                }
            } else {
                StabilizerGroupValue GH = groupConcatenateValue(u->limVector, v->limVector);
                toColumnEchelonForm(GH);
                //                std::cout << "[highLabel] Concatenated group = " << groupToString(GH, u->v) << "\n";
                newHighLabel = GramSchmidtFastSorted(GH, vLabel);
                //                std::cout << "[highlabel] After Gram-Schmidt, Label " << LimEntry<>::to_string(vLabel, u->v) << " becomes " << LimEntry<>::to_string(&newHighLabel, u->v) << "\n";
                highWeight.multiplyByPhase(newHighLabel.getPhase());
                //Log::log << "[highLabelPauli] canonical lim is " << newHighLabel << " so multiplying weight by " << phaseToString(newHighLabel.getPhase()) << ", result: weight = " << highWeight << '\n';
                newHighLabel.setPhase(phase_t::phase_one);
                if (highWeight.lexSmallerThanxMinusOne()) {
                    //                    std::cout << "[highLabelPauli] before multiplication by -1, highWeight = " << highWeight << "\n";
                    highWeight.multiplyByMinusOne(true);
                    //                    std::cout << "[highLabelPauli] Multiplied high edge weight by -1; New weight is " << highWeight << ".\n";
                }
            }
        }

#if !NDEBUG
        template<class Edge>
        void sanityCheckNormalize(CVec before, CVec after, [[maybe_unused]] const Edge& originalEdge, [[maybe_unused]] const Edge& normalizedEdge) {
            if (!vectorsApproximatelyEqual(before, after)) {
                Log::log << "[normalizeLIMDD] ERROR normalized vector is off :-(\n";
                Log::log << "[normalizeLIMDD] original:   " << outputCVec(before) << "\n";
                Log::log << "[normalizeLIMDD] normalized: " << outputCVec(after) << "\n";
                //export2Dot(originalEdge,   "originalEdge.dot",   false, true, true, false, true);
                //export2Dot(normalizedEdge, "normalizedEdge.dot", false, true, true, false, true);
                throw std::runtime_error("[normalizeLIMDD] ERROR normalized edge has different vector than original edge! See files originalEdge.svg and normalizedEdge.svg\n");
            }
        }
#endif

        void outputDescendantsStabilizerGroups(vEdge edge) {
            if (edge.isTerminal()) return;
            //Log::log << "[print stabs] n = " << (int) edge.p->v << "; Stab(v) = " << groupToString(edge.p->limVector, edge.p->v) << "  edge = " << edge << "\n";
            if (!edge.p->e[0].isTerminal()) {
                outputDescendantsStabilizerGroups(edge.p->e[0]);
            } else if (!edge.p->e[1].isTerminal()) {
                outputDescendantsStabilizerGroups(edge.p->e[1]);
            }
        }
#if !NDEBUG
        template<class Edge>
        void sanityCheckStabilizerGroup(Edge& edge, StabilizerGroup& stabilizerGroup) {
            CVec  nodeVec = getVector(edge.p);
            vEdge edgeId  = edge;
            edgeId.l      = nullptr;
            edgeId.w      = Complex::one;
            CVec stabVec;
            for (unsigned int i = 0; i < stabilizerGroup.size(); i++) {
                stabVec = getVector(edgeId, *stabilizerGroup[i]);
                if (!vectorsApproximatelyPointwiseEqual(nodeVec, stabVec)) {
                    CVec edgeVec = getVector(edge);
                    Log::log << "[sanity check stabilizer group] ERROR stabilizer group contains a non-stabilizer element: " << LimEntry<>::to_string(stabilizerGroup[i], edge.p->v) << "\n";
                    Log::log << "[sanity check stabilizer group] Edge is " << edge << '\n';
                    Log::log << "[sanity check stabilizer group] Node's stabilizer group is :" << groupToString(stabilizerGroup, edge.p->v) << "\n";
                    Log::log << "[sanity check stabilizer group] node's vector: " << outputCVec(nodeVec) << "\n";
                    Log::log << "[sanity check stabilizer group] stabilizer vec:" << outputCVec(stabVec) << "\n";
                    Log::log << "[sanity check stabilizer group] edge vec:      " << outputCVec(edgeVec) << "\n";
                    outputDescendantsStabilizerGroups(edge);
                    //export2Dot(edge, "errorStabilizer.dot", false, true, true, false, true, false);
                    throw std::runtime_error("[sanity check stabilizer group] ERROR stabilizer group contains a non-stabilizer element. See also errorStabilizer.svg\n");
                }
            }
        }

        // Checks whether a == iso * b
        template<class Edge>
        void sanityCheckIsomorphism(vNode& a, vNode& b, LimEntry<> iso, [[maybe_unused]] Edge dummy) {
            Edge edgeA{&a, Complex::one, nullptr};
            Edge edgeB{&b, Complex::one, nullptr};
            CVec avec    = getVector(edgeA);
            CVec isobvec = getVector(edgeB, iso);
            if (!vectorsApproximatelyEqual(avec, isobvec)) {
                CVec bvec = getVector(edgeB);
                Log::log << "[sanity check isomorphism] ERROR isomorphism is not an isomorphism\n"
                         << "[sanity check isomorphism] node A is " << a << "\n"
                         << "[sanity check isomorphism] node B is " << b << "\n"
                         << "[sanity check isomorphism] iso = " << iso.to_string(a.v) << '\n';
                Log::log << "[sanity check isomorphism] node a = ";
                printCVec(avec);
                Log::log << "\n[sanity check isomorphism] node b = ";
                printCVec(bvec);
                Log::log << "\n[sanity check isomorphism] iso * node b = ";
                printCVec(isobvec);
                //export2Dot(edgeA, "errorIsoA.dot", false, true, true, false, true, false);
                //export2Dot(edgeB, "errorIsoB.dot", false, true, true, false, true, false);
                throw std::runtime_error("[sanity check isomorphism] ERROR Purported isomorphism is not actually an isomorphism.\n");
            }
        }

        bool sanityCheckMakeDDNode(const CVec& left, const CVec& right, const CVec& result) {
            if (result.size() == 0) {
                return (isZeroVector(left) && isZeroVector(right));
            }
            unsigned int d = result.size() / 2;
            if ((left.size() != d && left.size() != 0) || (right.size() != d && right.size() != 0)) {
                //Log::log << "[sanity check makeDDNode] left = " << left.size() << "  right = " << right.size() << "  result = " << result.size() << " d = " << d << '\n';
                throw std::runtime_error("[sanity check makeDDNode] received vectors of unexpected sizes.\n");
            }
            if (left.size() == 0) {
                // check if result is zero here
                if (!isZeroVector(result, 0, d)) {
                    return false;
                }
            } else {
                for (unsigned int i = 0; i < left.size(); i++) {
                    if (!Complex::approximatelyEqual(left[i], result[i])) {
                        return false;
                    }
                }
            }
            if (right.size() == 0) {
                if (!isZeroVector(result, d, 2 * d)) return false;
            } else {
                for (unsigned int i = 0; i < d; i++) {
                    if (!Complex::approximatelyEqual(right[i], result[i + d])) {
                        return false;
                    }
                }
            }
            return true;
        }
#endif

        clock_t normalizeLIMDDTime = 0;
        long normalizeLIMDDCallCount = 0;
        // Returns an edge r satisfying |r> = |e>
        // the node e.p is put in canonical form, according to Pauli-LIMDD reduction rules
        vEdge normalizeLIMDDPauli(const vEdge& e, bool cached) {
            if (e.l == nullptr) {
                //std::cout << "[normalizeLIMDDPauli] e.l == nullptr location 1\n";
                throw std::exception();
            }
            startProfile(normalizeLIMDD)
            CVec rpVec;
            CVec oldNodeVec;
#if !NDEBUG
            CVec vec_e0 = getVector(e.p->e[0], e.p->v);
            CVec vec_e1 = getVector(e.p->e[1], e.p->v);
            sanityCheckStabilizerGroup(e.p->e[0], e.p->e[0].p->limVector);
            sanityCheckStabilizerGroup(e.p->e[1], e.p->e[1].p->limVector);
            CVec eVecStart = getVector(e, e.p->v);
            CVec currentVector; // temporary variable for reuse
#endif
            /// Step 1: Make sure the weight on the LIMs is +1
            if (!(LimEntry<>::getPhase(e.p->e[0].l) == phase_t::phase_one &&
                  LimEntry<>::getPhase(e.p->e[1].l) == phase_t::phase_one)) {
                throw std::runtime_error("[normalizeLIMDD] ERROR phase in LIM is not +1.");
            }
            Edge<vNode> result = normalize(e, cached);
            //Log::log << "[normalizeLIMDDPauli] after normalize, result = " << result << '\n';
            //Log::log << "[normalizeLIMDD] result.w = " << (void*) result.w.result << "; one(@" << (void*) Complex::one.result << ") = " << Complex::one << "\n";
            result.l           = e.l;
#if !NDEBUG
            cn.complexTable.checkConstantsIntegrity();
            currentVector = getVector(result, e.p->v);
            sanityCheckNormalize(eVecStart, currentVector, e, result);

            Edge<vNode> rOld = copyEdge(result); // TODO this seems out of date
#endif
            if (result.l == nullptr) {
                throw std::exception();
            }
            auto isZero = std::array{e.p->e[0].w.approximatelyZero(), e.p->e[1].w.approximatelyZero()};

            // The case when both children are isZero is not handled
            /// Case 1 ("Low Knife"):  high edge = 0, so |phi> = |0>|lowChild>
            if (isZero[1]) {
                //Log::log << "[normalizeLIMDD] Case |0>   (\"low knife\") " << (result.p->v + 1) << " qubits.\n";
                /// Step 1: Set the root edge label to 'Identity tensor R'
                result.l->multiplyBy(result.p->e[0].l); // = LimEntry<>::multiply(result.l, result.p->e[0].l);
                /// Step 2: Set the low and high edge labels to 'Identity'
                result.p->e[0].l = nullptr; // TODO possible memory leak
                result.p->e[1].l = nullptr; // TODO posible memory leak
                /// Step 3: multiply the root weight by the LIM phase; set the LIM phase to +1
                result.w.multiplyByPhase(result.l->getPhase());
                result.l->setPhase(phase_t::phase_one);
                /// Step 4: multiply the root edge weight by the low edge weight
                if (result.w.exactlyZero() || result.p->e[0].w.exactlyZero()) {
                    result.w = Complex::zero;
                } else if (cached) {
                    ComplexNumbers::mul(result.w, result.w, result.p->e[0].w);
                } else {
                    result.w = cn.mulCached(result.w, result.p->e[0].w);
                }
                result.p->e[0].w = Complex::one;
                /// Step 5: Set the weight to point to actually isZero
                result.p->e[1] = vEdge::zero;
                endProfile(normalizeLIMDD)
                return result;
            }
            /// Case 2 ("High Knife"):  low edge = 0, so |phi> = |1>|highChild>
            if (isZero[0]) {
                //Log::log << "[normalizeLIMDD] Case |1>   (\"high knife\")" << (result.p->v + 1) << " qubits.\n";
                /// Step 1: Multiply the root label by the high edge label
                result.l->multiplyBy(result.p->e[1].l);
                /// Step 2: Right-multiply the root edge by X
                LimEntry<> X;
                X.setOperator(result.p->v, 'X');
                result.l->multiplyBy(X);
                /// Step 3: Set the low and high edge labels to 'Identity'
                result.p->e[0].l = nullptr; // Set low  edge to Identity
                /// Step 4: Set the weight right
                if (result.w.exactlyZero() || result.p->e[1].w.exactlyZero()) {
                    result.w = Complex::zero;
                } else if (cached) {
                    ComplexNumbers::mul(result.w, result.w, result.p->e[1].w);
                } else {
                    result.w = cn.mulCached(result.w, result.p->e[1].w);
                }
                result.p->e[0].w = Complex::one;
                // Step 5: multiply the root weight by the LIM phase; set the LIM phase to +1
                result.w.multiplyByPhase(result.l->getPhase());
                result.l->setPhase(phase_t::phase_one);
                result.p->e[0].p = result.p->e[1].p;
                result.p->e[1]   = vEdge::zero;
                endProfile(normalizeLIMDD)
                return result;
            }
            //Log::log << "[normalizeLIMDD] Start. case Fork on " << (signed int)(result.p->v) + 1 << " qubits. Edge is currently: " << result << '\n';
            if ((long long unsigned int)(e.p->e[0].p) > (long long unsigned int)(e.p->e[1].p)) {
                std::swap(result.p->e[0], result.p->e[1]);
                //Log::log << "[normalizeLIMDD] Step 0: We swapped the children, so we correct for this by multiplying with X.\n";
                result.l->multiplyByX(result.p->v);
            }
            // TODO if both children's stabilizer groups are empty, probably we can immediately return

            /// Case 3 ("Fork"):  both edges of e are non-isZero
            LimEntry<>* lowLim = result.p->e[0].l;
            /// Step 1: Make a new LIM, which is the left LIM multiplied by the right LIM
            //Log::log << "[normalizeLIMDD] Step 1: Multiply low and high LIMs, result = " << result << "\n";
            LimEntry<> highLimTemp2 = LimEntry<>::multiply(result.p->e[0].l, result.p->e[1].l);
            result.p->e[1].l             = &highLimTemp2;
            result.p->e[1].w             = cn.getCached(CTEntry::val(result.p->e[1].w.r), CTEntry::val(result.p->e[1].w.i));
            //Log::log << "[normalizeLIMDD] after getting result.p->e[1] from cache, result.w = " << (void*) result.w.result << "; one = " << (void*) Complex::one.result << "\n";
            result.p->e[1].w.multiplyByPhase(result.p->e[1].l->getPhase());
            result.p->e[1].l->setPhase(phase_t::phase_one);
            /// Step 2: Make the left LIM Identity
            //Log::log << "[normalizeLIMDD] Step 2: Set low edge to nullptr. Edge is currently " << result << '\n';
            result.p->e[0].l = nullptr;
            /// Step 3: Choose a canonical right LIM
            vNode      oldNode            = *(result.p);                    // make a copy of the old node
            // TODO can we just use in-place result.p->e[0 and 1].w instead of these temporary weights?
            Complex    lowEdgeWeightTemp  = cn.getCached(result.p->e[0].w); // Returned to cache
            Complex    highEdgeWeightTemp = cn.getCached(result.p->e[1].w); // Returned to cache
            LimEntry<> highLimTemp;
            highLabelPauli(result.p->e[0].p, result.p->e[1].p, result.p->e[1].l, lowEdgeWeightTemp, highEdgeWeightTemp, highLimTemp);
            //Log::log << "[normalizeLIMDD] After got high label, result = " << result << "\n";
            result.p->e[0].w = lowEdgeWeightTemp;
            result.p->e[1].w = highEdgeWeightTemp;
            result.p->e[1].l = lf.limTable.lookup(highLimTemp);
            // TODO limdd should we decrement reference count on the weight result.p->e[1].w here?
            /// Step 4: Find an isomorphism 'iso' which maps the new node to the old node
#if !NDEBUG
            rpVec      = getVector(result.p);
            oldNodeVec = getVector(&oldNode);
            Log::log << "[normalizeLIMDD] vector of original node                     = " << outputCVec(oldNodeVec) << '\n'
                     << "[normalizeLIMDD] vector after assigning canonical high label = " << outputCVec(rpVec) << '\n';
#endif
            LimWeight<> iso;
            bool        foundIsomorphism = false;
            iso.weight = cn.getCached();
            //Log::log << "[normalizeLIMDD] getting isomorphism. result = " << result << "\n";
            getIsomorphismPauli(result.p, &oldNode, cn, iso, foundIsomorphism, cachingStrategy);
            //Log::log << "[normalizeLIMDD] after getting isomorphism. result = " << result << "\n";
            if (!foundIsomorphism) {
                Log::log << "[normalizeLIMDD] ERROR in step 4: old node is not isomorphic to canonical node.\n"
                         << "|- Old node is: " << oldNode << '\n'
                         << "|- new node is: " << *result.p << '\n'
                         << "|- old node vector: " << oldNodeVec << '\n'
                         << "|- new node vector: " << rpVec << '\n'
                         << "|- stab(oldLow)  = " << groupToString(oldNode.e[0].p->limVector, result.p->v - 1) << "\n"
                         << "|- stab(oldHigh) = " << groupToString(oldNode.e[1].p->limVector, result.p->v - 1) << "\n"
                         << "|- stab(newLow)  = " << groupToString(result.p->e[0].p->limVector, result.p->v - 1) << "\n"
                         << "|- stab(newHigh) = " << groupToString(result.p->e[1].p->limVector, result.p->v - 1) << "\n"
                         << "|- one = " << Complex::one << '\n';
                throw std::runtime_error("[normalizeLIMDD] ERROR in step 4: old node is not isomorphic to canonical node.\n");
            }
#if !NDEBUG
            sanityCheckIsomorphism(oldNode, *result.p, iso.lim, vEdge{});
#endif
            /// Next step: look up the new low and high weights for 'result' that were found by highLabelPauli()
            ///   (we only do this now instead of immediately when the weights were found, in order to help the subroutine 'getIsomorphism'.
            ///    Namely, looking up a number may change that number, which makes it harder for getIsomorphism() to do arithmetic)
            result.p->e[0].w = cn.lookup(lowEdgeWeightTemp);
            result.p->e[1].w = cn.lookup(highEdgeWeightTemp);
            cn.returnToCache(highEdgeWeightTemp);
            cn.returnToCache(lowEdgeWeightTemp);
            //Log::log << "[normalizeLIMDD] Found isomorphism: " << iso.weight << " * " << LimEntry<>::to_string(&iso.lim, result.p->v) << "\n";
            //Log::log << "[normalizeLIMDD] Step 5.1: Multiply root LIM by old low LIM, from " << result.w << " * " << LimEntry<>::to_string(result.l, result.p->v) << " to " << result.w << " * " << LimEntry<>::to_string(&LimEntry<>::multiply(*result.l, *lowLim), result.p->v) << ".\n";
            result.l->multiplyBy(lowLim);
            //Log::log << "[normalizeLIMDD] Step 5.2: Multiply root LIM by iso, becomes " << LimEntry<>::to_string(LimEntry<>::multiply(result.l, iso.lim), result.p->v) << ".\n";
            result.l->multiplyBy(iso.lim);
            //Log::log << "[normalizeLIMDD] after correcting LIM, result = " << result << "; one = " << Complex::one << "\n";
            //Log::log << "[normalizeLIMDD] result.w = " << (void*) result.w.result << ", " << (void*) result.w.i << "; one = " << (void*) Complex::one.result << "\n";
            cn.mul(result.w, result.w, iso.weight);
            //Log::log << "[normalizeLIMDD] after multiplying iso weight " << iso.weight << ", result = " << result << "; one = " << Complex::one << "\n";
            //Log::log << "[normalizeLIMDD] result.w = " << (void*) result.w.result << ", " << (void*) result.w.i << "; one = " << (void*) Complex::one.result << "\n";
            cn.returnToCache(iso.weight);
            //oldNode.e[1].w contains the cached weight from line "result.p->e[1].w = cn.getCached(CTEntry::val(result.p->e[1].w.result), CTEntry::val(result.p->e[1].w.i));"
            cn.returnToCache(oldNode.e[1].w);
            //Log::log << "[normalizeLIMDD] after returning weights to the cache, result = " << result << "\n";

            /// Step 6: Lastly, to make the edge canonical, we make sure the phase of the LIM is +1; to this end, we multiply the weight result.w by the phase of the Lim result.l
            //Log::log << "[normalizeLIMDD] Step 7: Moving LIM-phase into edge weight; currently result = " << result << '\n';
            movePhaseIntoWeight(*result.l, result.w);
            //Log::log << "[normalizeLIMDD] Final root edge: " << result << '\n';
#if !NDEBUG
            currentVector = getVector(result);
            sanityCheckNormalize(eVecStart, currentVector, rOld, result);
#endif
            endProfile(normalizeLIMDD)
            return result;
        }

        dEdge makeZeroDensityOperator(QubitCount n) {
            auto f = dEdge::one;
            for (size_t p = 0; p < n; p++) {
                f = makeDDNode(p, std::array{f, dEdge::zero, dEdge::zero, dEdge::zero});
            }
            return f;
        }

        // generate |0...0> with n qubits
        // TODO limdd: add identities to zero state?
        vEdge makeZeroState(QubitCount n, std::size_t start = 0) {
            if (n + start > nqubits) {
                throw std::runtime_error("Requested state with " +
                                         std::to_string(n + start) +
                                         " qubits, but current package configuration only supports up to " +
                                         std::to_string(nqubits) +
                                         " qubits. Please allocate a larger package instance.");
            }
            auto f = vEdge::one;
            for (std::size_t p = start; p < n + start; p++) {
                f = makeDDNode(static_cast<Qubit>(p), std::array{f, vEdge::zero});
                if (!f.w.exactlyOne()) {
                    cn.returnToCache(f.w);
                    f.w = Complex::one;
                }
            }
            return f;
        }
        // generate computational basis state |i> with n qubits
        vEdge makeBasisState(QubitCount n, const std::vector<bool>& state, std::size_t start = 0) {
            if (n + start > nqubits) {
                throw std::runtime_error("Requested state with " +
                                         std::to_string(n + start) +
                                         " qubits, but current package configuration only supports up to " +
                                         std::to_string(nqubits) +
                                         " qubits. Please allocate a larger package instance.");
            }
            auto f = vEdge::one;
            for (std::size_t p = start; p < n + start; ++p) {
                if (state[p] == 0) {
                    f = makeDDNode(static_cast<Qubit>(p), std::array{f, vEdge::zero});
                } else {
                    f = makeDDNode(static_cast<Qubit>(p), std::array{vEdge::zero, f});
                }
            }
            return f;
        }
        // generate general basis state with n qubits
        vEdge makeBasisState(QubitCount n, const std::vector<BasisStates>& state, std::size_t start = 0) {
            if (n + start > nqubits) {
                throw std::runtime_error("Requested state with " +
                                         std::to_string(n + start) +
                                         " qubits, but current package configuration only supports up to " +
                                         std::to_string(nqubits) +
                                         " qubits. Please allocate a larger package instance.");
            }
            if (state.size() < n) {
                throw std::runtime_error("Insufficient qubit states provided. Requested " + std::to_string(n) + ", but received " + std::to_string(state.size()));
            }

            auto f = vEdge::one;
            for (std::size_t p = start; p < n + start; ++p) {
                switch (state[p]) {
                    case BasisStates::zero:
                        f = makeDDNode(static_cast<Qubit>(p), std::array{f, vEdge::zero});
                        break;
                    case BasisStates::one:
                        f = makeDDNode(static_cast<Qubit>(p), std::array{vEdge::zero, f});
                        break;
                    case BasisStates::plus:
                        f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0), nullptr}, {f.p, cn.lookup(dd::SQRT2_2, 0), nullptr}}});
                        break;
                    case BasisStates::minus:
                        f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0), nullptr}, {f.p, cn.lookup(-dd::SQRT2_2, 0), nullptr}}});
                        break;
                    case BasisStates::right:
                        f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0), nullptr}, {f.p, cn.lookup(0, dd::SQRT2_2), nullptr}}});
                        break;
                    case BasisStates::left:
                        f = makeDDNode(static_cast<Qubit>(p), std::array<vEdge, RADIX>{{{f.p, cn.lookup(dd::SQRT2_2, 0), nullptr}, {f.p, cn.lookup(0, -dd::SQRT2_2), nullptr}}});
                        break;
                }
            }
            return f;
        }

        ///
        /// Matrix nodes, edges and quantum gates
        ///
    public:
        template<class Node>
        Edge<Node> normalize(const Edge<Node>& e, bool cached) {
            if constexpr (std::is_same_v<Node, mNode> || std::is_same_v<Node, dNode>) {
                auto argmax = -1;

                auto zero = std::array{e.p->e[0].w.approximatelyZero(),
                                       e.p->e[1].w.approximatelyZero(),
                                       e.p->e[2].w.approximatelyZero(),
                                       e.p->e[3].w.approximatelyZero()};

                // make sure to release cached numbers approximately zero, but not exactly zero
                if (cached) {
                    for (auto i = 0U; i < NEDGE; i++) {
                        if (zero[i] && e.p->e[i].w != Complex::zero) {
                            cn.returnToCache(e.p->e[i].w);
                            e.p->e[i] = Edge<Node>::zero;
                        }
                    }
                }

                fp   max  = 0;
                auto maxc = Complex::one;
                // determine max amplitude
                for (auto i = 0U; i < NEDGE; ++i) {
                    if (zero[i]) continue;
                    if (argmax == -1) {
                        argmax = static_cast<decltype(argmax)>(i);
                        max    = ComplexNumbers::mag2(e.p->e[i].w);
                        maxc   = e.p->e[i].w;
                    } else {
                        auto mag = ComplexNumbers::mag2(e.p->e[i].w);
                        if (mag - max > ComplexTable<>::tolerance()) {
                            argmax = static_cast<decltype(argmax)>(i);
                            max    = mag;
                            maxc   = e.p->e[i].w;
                        }
                    }
                }

                // all equal to zero
                if (argmax == -1) {
                    if (!cached && !e.isTerminal()) {
                        // If it is not a cached computation, the node has to be put back into the chain
                        getUniqueTable<Node>().returnNode(e.p);
                    }
                    return Edge<Node>::zero;
                }

                auto r = e;
                // divide each entry by max
                for (auto i = 0U; i < NEDGE; ++i) {
                    if (static_cast<decltype(argmax)>(i) == argmax) {
                        if (cached) {
                            if (r.w.exactlyOne())
                                r.w = maxc;
                            else
                                ComplexNumbers::mul(r.w, r.w, maxc);
                        } else {
                            if (r.w.exactlyOne()) {
                                r.w = maxc;
                            } else {
                                auto c = cn.getTemporary();
                                ComplexNumbers::mul(c, r.w, maxc);
                                r.w = cn.lookup(c);
                            }
                        }
                        r.p->e[i].w = Complex::one;
                    } else {
                        if (zero[i]) {
                            if (cached && r.p->e[i].w != Complex::zero)
                                cn.returnToCache(r.p->e[i].w);
                            r.p->e[i] = Edge<Node>::zero;
                            continue;
                        }
                        if (cached && !zero[i] && !r.p->e[i].w.exactlyOne()) {
                            cn.returnToCache(r.p->e[i].w);
                        }
                        if (r.p->e[i].w.approximatelyOne())
                            r.p->e[i].w = Complex::one;
                        auto c = cn.getTemporary();
                        ComplexNumbers::div(c, r.p->e[i].w, maxc);
                        r.p->e[i].w = cn.lookup(c);
                    }
                }
                return r;
            }
        }

        // build matrix representation for a single gate on an n-qubit circuit
        mEdge makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, Qubit target, std::size_t start = 0) {
            return makeGateDD(mat, n, Controls{}, target, start);
        }
        mEdge makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, const Control& control, Qubit target, std::size_t start = 0) {
            return makeGateDD(mat, n, Controls{control}, target, start);
        }
        mEdge makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, const Controls& controls, Qubit target, std::size_t start = 0) {
            if (n + start > nqubits) {
                throw std::runtime_error("Requested gate with " +
                                         std::to_string(n + start) +
                                         " qubits, but current package configuration only supports up to " +
                                         std::to_string(nqubits) +
                                         " qubits. Please allocate a larger package instance.");
            }
            std::array<mEdge, NEDGE> em{};
            auto                     it = controls.begin();
            for (auto i = 0U; i < NEDGE; ++i) {
                if (mat[i].r == 0 && mat[i].i == 0) {
                    em[i] = mEdge::zero;
                } else {
                    em[i] = mEdge::terminal(cn.lookup(mat[i]));
                }
            }

            //process lines below target
            auto z = static_cast<Qubit>(start);
            for (; z < target; z++) {
                for (auto i1 = 0U; i1 < RADIX; i1++) {
                    for (auto i2 = 0U; i2 < RADIX; i2++) {
                        auto i = i1 * RADIX + i2;
                        if (it != controls.end() && it->qubit == z) {
                            if (it->type == Control::Type::neg) { // neg. control
                                em[i] = makeDDNode(z, std::array{em[i], mEdge::zero, mEdge::zero, (i1 == i2) ? makeIdent(static_cast<Qubit>(start), static_cast<Qubit>(z - 1)) : mEdge::zero});
                            } else { // pos. control
                                em[i] = makeDDNode(z, std::array{(i1 == i2) ? makeIdent(static_cast<Qubit>(start), static_cast<Qubit>(z - 1)) : mEdge::zero, mEdge::zero, mEdge::zero, em[i]});
                            }
                        } else { // not connected
                            em[i] = makeDDNode(z, std::array{em[i], mEdge::zero, mEdge::zero, em[i]});
                        }
                    }
                }
                if (it != controls.end() && it->qubit == z) {
                    ++it;
                }
            }

            // target line
            auto e = makeDDNode(z, em);

            //process lines above target
            for (; z < static_cast<Qubit>(n - 1 + start); z++) {
                auto q = static_cast<Qubit>(z + 1);
                if (it != controls.end() && it->qubit == q) {
                    if (it->type == Control::Type::neg) { // neg. control
                        e = makeDDNode(q, std::array{e, mEdge::zero, mEdge::zero, makeIdent(static_cast<Qubit>(start), static_cast<Qubit>(q - 1))});
                    } else { // pos. control
                        e = makeDDNode(q, std::array{makeIdent(static_cast<Qubit>(start), static_cast<Qubit>(q - 1)), mEdge::zero, mEdge::zero, e});
                    }
                    ++it;
                } else { // not connected
                    e = makeDDNode(q, std::array{e, mEdge::zero, mEdge::zero, e});
                }
            }
            setIdentityFlags(e);
            return e;
        }

        mEdge makeSWAPDD(QubitCount n, const Controls& controls, Qubit target0, Qubit target1, std::size_t start = 0) {
            auto c = controls;
            c.insert(Control{target0});
            mEdge e = makeGateDD(Xmat, n, c, target1, start);
            c.erase(Control{target0});
            c.insert(Control{target1});
            e = multiply(e, multiply(makeGateDD(Xmat, n, c, target0, start), e));
            return e;
        }

        mEdge makePeresDD(QubitCount n, const Controls& controls, Qubit target0, Qubit target1, std::size_t start = 0) {
            auto c = controls;
            c.insert(Control{target1});
            mEdge e = makeGateDD(Xmat, n, c, target0, start);
            e       = multiply(makeGateDD(Xmat, n, controls, target1, start), e);
            return e;
        }

        mEdge makePeresdagDD(QubitCount n, const Controls& controls, Qubit target0, Qubit target1, std::size_t start = 0) {
            mEdge e = makeGateDD(Xmat, n, controls, target1, start);
            auto  c = controls;
            c.insert(Control{target1});
            e = multiply(makeGateDD(Xmat, n, c, target0, start), e);
            return e;
        }

        mEdge makeiSWAPDD(QubitCount n, const Controls& controls, Qubit target0, Qubit target1, std::size_t start = 0) {
            mEdge e = makeGateDD(Smat, n, controls, target1, start);              // S q[1]
            e       = multiply(e, makeGateDD(Smat, n, controls, target0, start)); // S q[0]
            e       = multiply(e, makeGateDD(Hmat, n, controls, target0, start)); // H q[0]
            auto c  = controls;
            c.insert(Control{target0});
            e = multiply(e, makeGateDD(Xmat, n, c, target1, start)); // CX q[0], q[1]
            c.erase(Control{target0});
            c.insert(Control{target1});
            e = multiply(e, makeGateDD(Xmat, n, c, target0, start));        // CX q[1], q[0]
            e = multiply(e, makeGateDD(Hmat, n, controls, target1, start)); // H q[1]
            return e;
        }

        mEdge makeiSWAPinvDD(QubitCount n, const Controls& controls, Qubit target0, Qubit target1, std::size_t start = 0) {
            mEdge e = makeGateDD(Hmat, n, controls, target1, start); // H q[1]
            auto  c = controls;
            c.insert(Control{target1});
            e = multiply(e, makeGateDD(Xmat, n, c, target0, start)); // CX q[1], q[0]
            c.erase(Control{target1});
            c.insert(Control{target0});
            e = multiply(e, makeGateDD(Xmat, n, c, target1, start));           // CX q[0], q[1]
            e = multiply(e, makeGateDD(Hmat, n, controls, target0, start));    // H q[0]
            e = multiply(e, makeGateDD(Sdagmat, n, controls, target0, start)); // Sdag q[0]
            e = multiply(e, makeGateDD(Sdagmat, n, controls, target1, start)); // Sdag q[1]
            return e;
        }

    private:
        // check whether node represents a symmetric matrix or the identity
        void checkSpecialMatrices(mNode* p) {
            // TODO limdd: anything to mark as special in LIMDDs?
            if (p->v == -1)
                return;

            p->setIdentity(false);
            p->setSymmetric(false);

            // check if matrix is symmetric
            if (!p->e[0].p->isSymmetric() || !p->e[3].p->isSymmetric()) return;
            if (transpose(p->e[1]) != p->e[2]) return;
            p->setSymmetric(true);

            // check if matrix resembles identity
            if (!(p->e[0].p->isIdentity()) || (p->e[1].w) != Complex::zero || (p->e[2].w) != Complex::zero || (p->e[0].w) != Complex::one ||
                (p->e[3].w) != Complex::one || !(p->e[3].p->isIdentity()))
                return;
            p->setIdentity(true);
        }

        ///
        /// Unique tables, LIM table, Reference counting and garbage collection
        ///
    public:
        // unique tables
        template<class Node>
        [[nodiscard]] auto& getUniqueTable() {
            if constexpr (std::is_same_v<Node, vNode>) {
                return vUniqueTable;
            } else if constexpr (std::is_same_v<Node, mNode>) {
                return mUniqueTable;
            } else if constexpr (std::is_same_v<Node, dNode>) {
                return dUniqueTable;
            }
        }

        //        [[nodiscard]] inline LimTable<>& getLimTable() {
        //            return limTable;
        //        }

        template<class Node>
        void incRef(const Edge<Node>& e) {
            getUniqueTable<Node>().incRef(e);
        }
        template<class Node>
        void decRef(const Edge<Node>& e) {
            getUniqueTable<Node>().decRef(e);
        }

        std::size_t countNodes(vEdge e) {
            incRef(e);
            std::size_t nodeCount = vUniqueTable.getActiveNodeCount();
            decRef(e);
            return nodeCount;
        }

        UniqueTable<vNode, UT_VEC_NBUCKET, UT_VEC_INITIAL_ALLOCATION_SIZE> vUniqueTable{nqubits};
        UniqueTable<mNode, UT_MAT_NBUCKET, UT_MAT_INITIAL_ALLOCATION_SIZE> mUniqueTable{nqubits};
        UniqueTable<dNode, UT_DM_NBUCKET, UT_DM_INITIAL_ALLOCATION_SIZE>   dUniqueTable{nqubits};

        bool garbageCollect(bool force = false) {
            // TODO Limdd: add GC for limTable, modify GC for edges and nodes so that the lims are removed
            // return immediately if no table needs collection
            if (!force &&
                !vUniqueTable.possiblyNeedsCollection() &&
                !mUniqueTable.possiblyNeedsCollection() &&
                !dUniqueTable.possiblyNeedsCollection() &&
                !cn.complexTable.possiblyNeedsCollection()) {
                return false;
            }

            auto cCollect = cn.garbageCollect(force);
            if (cCollect > 0) {
                // Collecting garbage in the complex numbers table requires collecting the node tables as well
                force = true;
            }
            auto vCollect   = vUniqueTable.garbageCollect(force);
            auto mCollect   = mUniqueTable.garbageCollect(force);
            auto dCollect   = dUniqueTable.garbageCollect(force);
            auto limCollect = lf.limTable.garbageCollect(force);

            // invalidate all compute tables involving vectors if any vector node has been collected
            if (vCollect > 0 || limCollect > 0) {
                vectorAdd.clear();
                vectorInnerProduct.clear();
                vectorKronecker.clear();
                matrixVectorMultiplication.clear();
            }
            // invalidate all compute tables involving matrices if any matrix node has been collected
            if (mCollect > 0 || dCollect > 0) {
                matrixAdd.clear();
                matrixTranspose.clear();
                conjugateMatrixTranspose.clear();
                matrixKronecker.clear();
                matrixVectorMultiplication.clear();
                matrixMatrixMultiplication.clear();
                toffoliTable.clear();
                clearIdentityTable();
                stochasticNoiseOperationCache.clear();
                densityAdd.clear();
                densityDensityMultiplication.clear();
                densityNoise.clear();
            }
            // invalidate all compute tables where any component of the entry contains numbers from the complex table if any complex numbers were collected
            if (cCollect > 0) {
                matrixVectorMultiplication.clear();
                matrixMatrixMultiplication.clear();
                matrixTranspose.clear();
                conjugateMatrixTranspose.clear();
                vectorInnerProduct.clear();
                vectorKronecker.clear();
                matrixKronecker.clear();
                stochasticNoiseOperationCache.clear();
                densityAdd.clear();
                densityDensityMultiplication.clear();
                densityNoise.clear();
            }
            return vCollect > 0 || mCollect > 0 || cCollect > 0;
        }

        void clearUniqueTables() {
            vUniqueTable.clear();
            mUniqueTable.clear();
            dUniqueTable.clear();
            lf.limTable.clear();
        }

        // create a normalized DD node and return an edge pointing to it. The node is not recreated if it already exists.
        template<class Node>
        Edge<Node> makeNode(Qubit var, const std::array<Edge<Node>, std::tuple_size_v<decltype(Node::e)>>& edges, bool cached = false, [[maybe_unused]] const bool generateDensityMatrix = false) {
            // TODO Limdd: add LIMs to makeDDNode
            auto&      uniqueTable = getUniqueTable<Node>();
            Edge<Node> e{uniqueTable.getNode(), Complex::one, nullptr};
            e.p->v = var;
            e.p->e = edges;

            if constexpr (std::is_same_v<Node, mNode> || std::is_same_v<Node, dNode>) {
                e.p->flags = 0;
                if constexpr (std::is_same_v<Node, dNode>) {
                    e.p->setDensityMatrixNodeFlag(generateDensityMatrix);
                }
            }

            assert(e.p->ref == 0);
            for ([[maybe_unused]] const auto& edge: edges)
                // an error here indicates that cached nodes are assigned multiple times. Check if garbage collect correctly resets the cache tables!
                assert(edge.p->v == var - 1 || edge.isTerminal());

            // normalize it
            e = normalize(e, cached);
            assert(e.p->v == var || e.isTerminal());

            // Construct the Stabilizer Generator set
            e.p->limVector = constructStabilizerGeneratorSet(e.p);

            // look it up in the unique tables
            auto l = uniqueTable.lookup(e, false);
            assert(l.p->v == var || l.isTerminal());

            // set specific node properties for matrices
            if constexpr (std::is_same_v<Node, mNode>) {
                if (l.p == e.p)
                    checkSpecialMatrices(l.p);
            }
            return l;
        }

        // create a normalized DD node and return an edge pointing to it. The node is not recreated if it already exists.
        template<class Node>
        Edge<Node> makeDDNode(Qubit var, const std::array<Edge<Node>, std::tuple_size_v<decltype(Node::e)>>& edges, bool cached = false, [[maybe_unused]] const bool generateDensityMatrix = false) {
            auto&      uniqueTable = getUniqueTable<Node>();
            Edge<Node> e{uniqueTable.getNode(), Complex::one, nullptr};
            e.p->v = var;
            e.p->e = edges;

            e.p->flags = 0;

            assert(e.p->ref == 0);
            for ([[maybe_unused]] const auto& edge: edges)
                // an error here indicates that cached nodes are assigned multiple times. Check if garbage collect correctly resets the cache tables!
                assert(edge.p->v == var - 1 || edge.isTerminal());

            // normalize it
            e = normalize(e, cached);
            assert(e.p->v == var || e.isTerminal());

            // look it up in the unique tables
            auto l = uniqueTable.lookup(e, false);
            assert(l.p->v == var || l.isTerminal());

            // set specific node properties for matrices
            if constexpr (std::is_same_v<Node, mNode>) {
                if (l.p == e.p)
                    checkSpecialMatrices(l.p);
            }
            return l;
        }

        void putStabilizersInTable(vEdge& edge, const StabilizerGroupValue& stabilizers) {
            LimEntry<>* limptr;
            edge.p->limVector.clear();
            edge.p->limVector.reserve(stabilizers.size());
            for (unsigned int i = 0; i < stabilizers.size(); i++) {
                limptr = lf.limTable.lookup(stabilizers[i]);
                edge.p->limVector.push_back(limptr);
            }
        }

        // create a normalized DD node and return an edge pointing to it. The node is not recreated if it already exists.
        // Here the parameters 'targetEdge' and 'gate' satisfy the equation |edges> = gate * |targetEdge.p>, i.e.,
        //   the new node was created by applying 'gate' to the node 'targetEdge.p'
        long makeDDNodeCallCount = 0;
        clock_t makeDDNodeTime = 0;
        Edge<vNode> makeDDNode(Qubit var, const std::array<Edge<vNode>, std::tuple_size_v<decltype(vNode::e)>>& edges, bool cached = false, LimEntry<>* lim = nullptr, const vEdge targetEdge = {}, const CliffordGate gate = CliffordGate::cliffordGateNone()) {
            //std::cout << "makeDDNode(" << var << ", ..., " << cached << ", ..)\n";
            startProfile(makeDDNode)
            auto& uniqueTable = getUniqueTable<vNode>();

            Edge<vNode> e{uniqueTable.getNode(), Complex::one, lim};
            e.p->v = var;
            e.p->e = edges;

            assert(e.p->ref == 0);
            for ([[maybe_unused]] const auto& edge: edges)
                assert(edge.p != nullptr || edge.p->v == var - 1 || edge.isTerminal());

            // set specific node properties for matrices
            CVec       vece0, vece1, vece, vecResult;
            LimEntry<> tempRootLabel; //todo use cached lims in the future
            // normalize it
            switch (group) {
                case Z_group:
                    e = normalizeLIMDDZ(e, cached);
                    break;
                case Pauli_group:
#if !NDEBUG

                    vece0 = getVector(edges[0], var - 1);
                    vece1 = getVector(edges[1], var - 1);
#endif
                    e.l = &tempRootLabel;
                    if (e.l == nullptr) {
                        std::cout << "[makeDDNode] e.l is nullptr.\n";
                        throw std::exception();
                    }
                    e   = normalizeLIMDDPauli(e, cached);
                    e.l = lf.limTable.lookup(*e.l);

#if !NDEBUG

                    vecResult = getVector(e, var);
                    if (LimEntry<>::isIdentityOperator(lim) && !sanityCheckMakeDDNode(vece0, vece1, vecResult)) {
                        Log::log << "[makeDDNode] ERROR  sanity check failed.\n"
                                 << "[makeDDNode] edges[0]   : " << outputCVec(vece0) << '\n'
                                 << "[makeDDNode] edges[1]   : " << outputCVec(vece1) << '\n'
                                 << "[makeDDNode] edges[0]   : " << edges[0] << '\n'
                                 << "[makeDDNode] edges[1]   : " << edges[1] << '\n'
                                 << "[makeDDNode] input vec  : " << outputCVec(vece) << '\n'
                                 << "[makeDDNode] result vec : " << outputCVec(vecResult) << '\n'
                                 << "[makeDDNode] result     : " << e << '\n';
                        throw std::runtime_error("[makeDDNode] ERROR sanity check failed.\n");
                    }

#endif
                    break;
                case QMDD_group:
                    e = normalize(e, cached);
                    break;
            }
            assert(e.p->v == var || e.isTerminal());

            bool foundNodeInTable;
            auto l = uniqueTable.lookupAndBookkeep(e, foundNodeInTable, false);
            // If the node was not found in the table, then we must now compute its stabilizer group
            if (!foundNodeInTable) {
                StabilizerGroupValue stabilizers;
                switch (group) {
                    case Z_group:
                        l.p->limVector = constructStabilizerGeneratorSetZ(*(e.p));
                        break;
                    case Pauli_group:
                        if (usingSmartStabilizerGeneration(cachingStrategy) && !gate.isNone()) {
                            //Log::log << "[makeDDNode] Smartly finding stabilizers. Node vector is " << outputCVec(getVector(e.p)) << ". originalEdge = " << targetEdge << "\n";
                            stabilizers = constructStabilizerGeneratorSetPauliAfterClifford(l,  targetEdge, gate);
                        }
                        else {
                            //Log::log << "[makeDDNode] not using smart stabs.\n";
                            stabilizers = constructStabilizerGeneratorSetPauli(*(e.p), cn, cachingStrategy);
                        }
                        putStabilizersInTable(l, stabilizers);
#if !NDEBUG

                        vece = getVector(l.p);
                        Log::log << "[makeDDNode] just built Stab(" << l.p << "). Amplitude vector: " << outputCVec(vece) << '\n'
                                 << "[makeDDNode] Stab = ";
                        printStabilizerGroup(l.p->limVector, l.p->v);
                        Log::log << '\n';
                        sanityCheckStabilizerGroup(l, l.p->limVector);

#endif
                        break;
                    case QMDD_group: break;
                }
            }

            // TODO delete the LIMs on the original low and high edges, as below
            //   currently this gives a segmentation fault
            // delete edges[0].l; // TODO
            // delete edges[1].l; // TODO
            // look it up in the unique tables
            assert(l.p->v == var || l.isTerminal());
            endProfile(makeDDNode)
            return l;
        }

        // Returns a node that is not normalized
        //   *** ONLY for testing purposes ***
        Edge<vNode> makeDDNodeNonNormalized(const std::array<Edge<vNode>, std::tuple_size_v<decltype(vNode::e)>>& edges) {
            auto& uniqueTable = vUniqueTable;

            Edge<vNode> e{uniqueTable.getNode(), Complex::one, nullptr};
            if (!edges[0].isZeroTerminal()) {
                e.p->v = edges[0].p->v + 1;
            } else {
                e.p->v = edges[1].p->v + 1;
            }
            e.p->e = edges;
            return e;
        }

        Edge<vNode> copyEdge(const vEdge edge) {
            auto&       uniqueTable = getUniqueTable<vNode>();
            Edge<vNode> e{uniqueTable.getNode(), Complex::one, lf.limTable.lookup(LimEntry<>(edge.l))};
            e.p->e      = edge.p->e;
            e.p->e[0].l = lf.limTable.lookup(LimEntry<>(edge.p->e[0].l));
            e.p->e[1].l = lf.limTable.lookup(LimEntry<>(edge.p->e[1].l));
            e.p->v      = edge.p->v;
            if (e.p->v != -1) {
                Edge<vNode> l = uniqueTable.lookup(e, false);
                return l;
            } else
                return e;
        }

        template<class Node>
        Edge<Node> deleteEdge(const Edge<Node>& e, dd::Qubit v, std::size_t edgeIdx) {
            std::unordered_map<Node*, Edge<Node>> nodes{};
            return deleteEdge(e, v, edgeIdx, nodes);
        }

    private:
        template<class Node>
        Edge<Node> deleteEdge(const Edge<Node>& e, dd::Qubit v, std::size_t edgeIdx, std::unordered_map<Node*, Edge<Node>>& nodes) {
            if (e.p == nullptr || e.isTerminal()) {
                return e;
            }

            const auto& nodeit = nodes.find(e.p);
            Edge<Node>  newedge{};
            if (nodeit != nodes.end()) {
                newedge = nodeit->second;
            } else {
                constexpr std::size_t     N = std::tuple_size_v<decltype(e.p->e)>;
                std::array<Edge<Node>, N> edges{};
                if (e.p->v == v) {
                    for (std::size_t i = 0; i < N; i++) {
                        edges[i] = i == edgeIdx ? Edge<Node>::zero : e.p->e[i]; // optimization -> node cannot occur below again, since dd is assumed to be free
                    }
                } else {
                    for (std::size_t i = 0; i < N; i++) {
                        edges[i] = deleteEdge(e.p->e[i], v, edgeIdx, nodes);
                    }
                }

                newedge    = makeDDNode(e.p->v, edges);
                nodes[e.p] = newedge;
            }

            if (newedge.w.approximatelyOne()) {
                newedge.w = e.w;
            } else {
                auto w = cn.getTemporary();
                dd::ComplexNumbers::mul(w, newedge.w, e.w);
                newedge.w = cn.lookup(w);
            }

            return newedge;
        }

        ///
        /// Compute table definitions
        ///
    public:
        void clearComputeTables() {
            vectorAdd.clear();
            matrixAdd.clear();
            matrixTranspose.clear();
            conjugateMatrixTranspose.clear();
            matrixMatrixMultiplication.clear();
            matrixVectorMultiplication.clear();
            vectorInnerProduct.clear();
            vectorKronecker.clear();
            matrixKronecker.clear();

            toffoliTable.clear();

            clearIdentityTable();

            stochasticNoiseOperationCache.clear();
            densityAdd.clear();
            densityDensityMultiplication.clear();
            densityNoise.clear();
        }

        ///
        /// Measurements from state decision diagrams
        ///
    public:
        std::string measureAll(vEdge& rootEdge, const bool collapse, std::mt19937_64& mt, fp epsilon = 0.001) {
            if (std::abs(ComplexNumbers::mag2(rootEdge.w) - 1.0L) > epsilon) {
                if (rootEdge.w.approximatelyZero()) {
                    throw std::runtime_error("Numerical instabilities led to a 0-vector! Abort simulation!");
                }
                std::cerr << "WARNING in MAll: numerical instability occurred during simulation: |alpha|^2 + |beta|^2 = "
                          << ComplexNumbers::mag2(rootEdge.w) << ", but should be 1!\n";
            }

            vEdge      cur            = rootEdge;
            LimEntry<> lim            = {};
            const auto numberOfQubits = static_cast<QubitCount>(rootEdge.p->v + 1);

            std::string result(numberOfQubits, '0');

            std::uniform_real_distribution<fp> dist(0.0, 1.0L);

            for (Qubit i = rootEdge.p->v; i >= 0; --i) {
                lim.multiplyBy(cur.l);
                const auto op = lim.getPauliForQubit(cur.p->v);
                lim.setOperator(cur.p->v, 'I');

                // recursive case
                auto const e0 = follow2(cur, 0, op);
                auto const e1 = follow2(cur, 1, op);

                fp p0  = ComplexNumbers::mag2(e0.w);
                fp p1  = ComplexNumbers::mag2(e1.w);
                fp tmp = p0 + p1;

                if (std::abs(tmp - 1.0L) > epsilon) {
                    throw std::runtime_error("Added probabilities differ from 1 by " + std::to_string(std::abs(tmp - 1.0L)));
                }
                p0 /= tmp;

                const fp threshold = dist(mt);
                if (threshold < p0) {
                    cur = e0;
                } else {
                    result[cur.p->v] = '1';
                    cur              = e1;
                }
            }

            if (collapse) {
                decRef(rootEdge);

                vEdge                e = vEdge::one;
                std::array<vEdge, 2> edges{};

                for (Qubit p = 0; p < numberOfQubits; p++) {
                    if (result[p] == '0') {
                        edges[0] = e;
                        edges[1] = vEdge::zero;
                    } else {
                        edges[0] = vEdge::zero;
                        edges[1] = e;
                    }
                    e = makeDDNode(p, edges, false);
                }
                incRef(e);
                rootEdge = e;
                garbageCollect();
            }

            return std::string{result.rbegin(), result.rend()};
        }

    private:
        double assignProbabilities(const vEdge& edge, std::unordered_map<vNode*, fp>& probs) {
            // TODO limdd
            auto it = probs.find(edge.p);
            if (it != probs.end()) {
                return ComplexNumbers::mag2(edge.w) * it->second;
            }
            double sum;
            if (edge.isTerminal()) {
                sum = 1.0;
            } else {
                sum = assignProbabilities(edge.p->e.at(0), probs) + assignProbabilities(edge.p->e.at(1), probs);
            }

            probs.insert({edge.p, sum});

            return ComplexNumbers::mag2(edge.w) * sum;
        }

    public:
        std::pair<dd::fp, dd::fp> determineMeasurementProbabilities(const vEdge& root_edge, const Qubit index, const bool assumeProbabilityNormalization) {
            std::map<std::pair<vNode*, bool>, fp> probsMone;
            std::set<std::pair<vNode*, bool>>     visited;
            std::queue<std::pair<vEdge, bool>>    queue;

            if (root_edge.l->getPauliForQubit(index) == dd::pauli_x ||
                root_edge.l->getPauliForQubit(index) == dd::pauli_y) {
                queue.emplace(root_edge, true);
                visited.insert({root_edge.p, true});
                probsMone[{root_edge.p, true}] = ComplexNumbers::mag2(root_edge.w);
            } else {
                queue.emplace(root_edge, false);
                visited.insert({root_edge.p, false});
                probsMone[{root_edge.p, false}] = ComplexNumbers::mag2(root_edge.w);
            }

            while (queue.front().first.p->v != index) {
                auto ptr        = queue.front().first;
                bool flipProb   = queue.front().second;
                bool flipProbE0 = queue.front().second;
                bool flipProbE1 = queue.front().second;
                queue.pop();

                fp prob = probsMone[{ptr.p, flipProb}];

                auto opFollow   = pauli_id;
                auto opTargetE0 = pauli_id;
                auto opTargetE1 = pauli_id;
                if (ptr.l != nullptr) {
                    opFollow = ptr.l->getPauliForQubit(ptr.p->v);
                }
                auto const e0 = follow2(ptr, 0, opFollow);
                auto const e1 = follow2(ptr, 1, opFollow);

                if (e0.l != nullptr) {
                    opTargetE0 = e0.l->getPauliForQubit(index);
                }
                if (e1.l != nullptr) {
                    opTargetE1 = e1.l->getPauliForQubit(index);
                }

                if (opTargetE0 == dd::pauli_x || opTargetE0 == dd::pauli_y) {
                    flipProbE0 = !flipProbE0;
                }
                if (opTargetE1 == dd::pauli_x || opTargetE1 == dd::pauli_y) {
                    flipProbE1 = !flipProbE1;
                }

                if (!e0.w.approximatelyZero()) {
                    const fp tmp1 = prob * ComplexNumbers::mag2(e0.w);

                    if (visited.find({e0.p, flipProbE0}) != visited.end()) {
                        probsMone[{e0.p, flipProbE0}] = probsMone[{e0.p, flipProbE0}] + tmp1;
                    } else {
                        probsMone[{e0.p, flipProbE0}] = tmp1;
                        visited.insert({e0.p, flipProbE0});
                        queue.push({e0, flipProbE0});
                    }
                }

                if (!e1.w.approximatelyZero()) {
                    const fp tmp1 = prob * ComplexNumbers::mag2(e1.w);

                    if (visited.find({e1.p, flipProbE1}) != visited.end()) {
                        probsMone[{e1.p, flipProbE1}] = probsMone[{e1.p, flipProbE1}] + tmp1;
                    } else {
                        probsMone[{e1.p, flipProbE1}] = tmp1;
                        visited.insert({e1.p, flipProbE1});
                        queue.push({e1, flipProbE1});
                    }
                }
            }

            fp pzero{0}, pone{0};

            if (assumeProbabilityNormalization) {
                while (!queue.empty()) {
                    auto ptr      = queue.front().first;
                    bool flipProb = queue.front().second;
                    queue.pop();

                    auto opFollow = pauli_id;

                    //                    if (ptr.l != nullptr) {
                    //                        opFollow = ptr.l->getPauliForQubit(ptr.p->v);
                    //                    }

                    auto e0 = follow2(ptr, 0, opFollow);
                    auto e1 = follow2(ptr, 1, opFollow);

                    if (flipProb) {
                        std::swap(e0, e1);
                    }

                    if (!e0.w.approximatelyZero()) {
                        pzero += probsMone[{ptr.p, flipProb}] * ComplexNumbers::mag2(e0.w);
                    }

                    if (!e1.w.approximatelyZero()) {
                        pone += probsMone[{ptr.p, flipProb}] * ComplexNumbers::mag2(e1.w);
                    }
                }
            } else {
                throw std::runtime_error("determineMeasurementProbabilities without assumeProbabilityNormalization is not implemented yet.");
                //                std::unordered_map<vNode*, fp> probs;
                //                assignProbabilities(root_edge, probs);
                //
                //                while (!queue.empty()) {
                //                                        auto* ptr = queue.front().first.p;
                //                                        queue.pop();
                //
                //                                        if (!ptr->e.at(0).w.approximatelyZero()) {
                //                                            pzero += probsMone[ptr] * probs[ptr->e.at(0).p] * ComplexNumbers::mag2(ptr->e.at(0).w);
                //                                        }
                //
                //                                        if (!ptr->e.at(1).w.approximatelyZero()) {
                //                                            pone += probsMone[ptr] * probs[ptr->e.at(1).p] * ComplexNumbers::mag2(ptr->e.at(1).w);
                //                                        }
                //                }
            }
            return {pzero, pone};
        }

        char measureOneCollapsing(vEdge& root_edge, const Qubit index, const bool assumeProbabilityNormalization, std::mt19937_64& mt, fp epsilon = 0.001) {
            // TODO limdd
            const auto& [pzero, pone] = determineMeasurementProbabilities(root_edge, index, assumeProbabilityNormalization);

            if (std::abs(pzero - 1) < epsilon) {
                return '0';
            } else if (std::abs(pone - 1) < epsilon) {
                return '1';
            }

            const fp sum = pzero + pone;
            if (std::abs(sum - 1) > epsilon) {
                throw std::runtime_error("Numerical instability occurred during measurement: |alpha|^2 + |beta|^2 = " + std::to_string(pzero) + " + " + std::to_string(pone) + " = " +
                                         std::to_string(pzero + pone) + ", but should be 1!");
            }
            GateMatrix measurementMatrix{
                    complex_zero, complex_zero,
                    complex_zero, complex_zero};

            std::uniform_real_distribution<fp> dist(0.0, 1.0L);

            fp   threshold = dist(mt);
            fp   normalizationFactor;
            char result;

            if (threshold < pzero / sum) {
                measurementMatrix[0] = complex_one;
                normalizationFactor  = pzero;
                result               = '0';
            } else {
                measurementMatrix[3] = complex_one;
                normalizationFactor  = pone;
                result               = '1';
            }

            mEdge measurementGate = makeGateDD(measurementMatrix, root_edge.p->v + 1, index);

            vEdge e = multiply(measurementGate, root_edge);

            Complex c = cn.getTemporary(std::sqrt(1.0 / normalizationFactor), 0);
            ComplexNumbers::mul(c, e.w, c);
            e.w = cn.lookup(c);
            incRef(e);
            decRef(root_edge);
            root_edge = e;

            return result;
        }

        ///
        /// Addition
        ///
    public:
        ComputeTable<vCachedEdge, vCachedEdge, vCachedEdge, CT_VEC_ADD_NBUCKET> vectorAdd{};
        ComputeTable<mCachedEdge, mCachedEdge, mCachedEdge, CT_MAT_ADD_NBUCKET> matrixAdd{};
        ComputeTable<dCachedEdge, dCachedEdge, dCachedEdge, CT_DM_ADD_NBUCKET>  densityAdd{};

        template<class Node>
        [[nodiscard]] auto& getAddComputeTable() {
            if constexpr (std::is_same_v<Node, vNode>) {
                return vectorAdd;
            } else if constexpr (std::is_same_v<Node, mNode>) {
                return matrixAdd;
            } else if constexpr (std::is_same_v<Node, dNode>) {
                return densityAdd;
            }
        }

        template<class Edge>
        Edge add(const Edge& x, const Edge& y) {
            // TODO limdd
            [[maybe_unused]] const auto before = cn.cacheCount();

            auto result = add2(x, y);

            if (result.w != Complex::zero) {
                cn.returnToCache(result.w);
                result.w = cn.lookup(result.w);
            }

            [[maybe_unused]] const auto after = cn.complexCache.getCount();
            assert(after == before);

            return result;
        }

    public:
        long addCallCount = 0;
        clock_t addTime = 0;
        template<class Node>
        Edge<Node> add2(const Edge<Node>& x, const Edge<Node>& y, const LimEntry<>& limX = {}, const LimEntry<>& limY = {}) {
            startProfile(add)
            addCallCount++;
            LimEntry<> trueLimX = limX;
            trueLimX.multiplyBy(x.l);
            // Making a copy from trueLimX as I need it later for inserting the result into the cache
            auto trueLimXCopy = trueLimX;

            LimEntry<> trueLimY = limY;
            trueLimY.multiplyBy(y.l);

            if (x.p == nullptr) return y;
            if (y.p == nullptr) return x;

            if (x.w.exactlyZero()) {
                if (y.w.exactlyZero()) {
                    return Edge<Node>::zero;
                }
                auto r = y;
                r.w    = cn.getCached(CTEntry::val(y.w.r), CTEntry::val(y.w.i));
                r.w.multiplyByPhase(trueLimY.getPhase());
                trueLimY.setPhase(phase_t::phase_one);
                r.l = lf.limTable.lookup(trueLimY);
                return r;
            }
            if (y.w.exactlyZero()) {
                auto r = x;
                r.w    = cn.getCached(CTEntry::val(x.w.r), CTEntry::val(x.w.i));
                r.w.multiplyByPhase(trueLimX.getPhase());
                trueLimX.setPhase(phase_t::phase_one);
                r.l = lf.limTable.lookup(trueLimX);
                return r;
            }

            if (x.p == y.p && LimEntry<>::EqualModuloPhase(&trueLimX, &trueLimY)) {
                auto    r   = y;
                Complex xwp = cn.getCached(x.w);
                xwp.multiplyByPhase(trueLimX.getPhase());
                Complex ywp = cn.getCached(y.w);
                ywp.multiplyByPhase(trueLimY.getPhase());
                r.w = cn.addCached(xwp, ywp);
                cn.returnToCache(xwp);
                cn.returnToCache(ywp);
                if (r.w.approximatelyZero()) {
                    cn.returnToCache(r.w);
                    return Edge<Node>::zero;
                }
                trueLimY.setPhase(phase_t::phase_one);
                r.l = lf.limTable.lookup(trueLimY);
                //                Log::log << "[add2] Case x.p == y.p; x.w = " << LimEntry<>::to_string(&trueLimX, x.p->v) << "*" << x.w << " y.w = " << LimEntry<>::to_string(&trueLimY, y.p->v) << "*" << y.w << "  x.w+y.w = " << r.w << '\n';
                return r;
            }

            auto& computeTable = getAddComputeTable<Node>();

            const auto trueLimC      = createCanonicalLabel(trueLimX, trueLimY, y);
            const auto trueLimCTable = lf.limTable.lookup(trueLimC);

            auto r = computeTable.lookup({x.p, x.w, nullptr}, {y.p, y.w, trueLimCTable}, false);
            //            auto r = computeTable.lookup({x.p, x.w, trueLimCTable}, {y.p, y.w, nullptr});

            //           if (r.p != nullptr && false) { // activate for debugging caching only
            if (r.p != nullptr) {
                if (r.w.approximatelyZero()) {
                    return Edge<Node>::zero;
                } else {
                    auto       weight = cn.getCached(r.w);
                    LimEntry<> lim    = trueLimX;
                    if (r.l != nullptr) {
                        lim.multiplyBy(r.l);
                        movePhaseIntoWeight(lim, weight);
                    }
                    return {r.p, weight, lf.limTable.lookup(lim)};
                }
            }

            Qubit w;
            if (x.isTerminal()) {
                w = y.p->v;
            } else {
                w = x.p->v;
                if (!y.isTerminal() && y.p->v > w) {
                    w = y.p->v;
                }
            }

            const auto opX = trueLimX.getPauliForQubit(x.p->v);
            trueLimX.setOperator(x.p->v, 'I');

            const auto opY = trueLimY.getPauliForQubit(y.p->v);
            trueLimY.setOperator(y.p->v, 'I');

            constexpr std::size_t     N = std::tuple_size_v<decltype(x.p->e)>;
            std::array<Edge<Node>, N> edge{};
            for (auto i = 0U; i < N; i++) {
                Edge<Node> e1{};
                if (!x.isTerminal() && x.p->v == w) {
                    e1 = follow2(x, i, opX);
                    //                    e1 = x.p->e[i];

                    if (e1.w != Complex::zero) {
                        e1.w = cn.mulCached(e1.w, x.w);
                    }
                } else {
                    e1 = x;
                    if (y.p->e[i].p == nullptr) {
                        e1 = {nullptr, Complex::zero, nullptr};
                    }
                }
                Edge<Node> e2{};
                if (!y.isTerminal() && y.p->v == w) {
                    //e2 = y.p->e[i];
                    e2 = follow2(y, i, opY);

                    if (e2.w != Complex::zero) {
                        e2.w = cn.mulCached(e2.w, y.w);
                    }
                } else {
                    e2 = y;
                    if (x.p->e[i].p == nullptr) {
                        e2 = {nullptr, Complex::zero, nullptr};
                    }
                }

                if constexpr (std::is_same_v<Node, dNode>) {
                    dEdge::applyDmChangesToEdges(e1, e2);
                    edge[i] = add2(e1, e2, trueLimX, trueLimY);
                    dEdge::revertDmChangesToEdges(e1, e2);
                } else {
#if !NDEBUG
                    CVec vectorArg0 = getVector(e1, w, trueLimX);
                    CVec vectorArg1 = getVector(e2, w, trueLimY);

                    CVec vectorExpected = addVectors(vectorArg0, vectorArg1);
#endif
                    //                    export2Dot(e1, "e1.dot", true, true, false, false, true);
                    //                    export2Dot(e2, "e2.dot", true, true, false, false, true);
                    edge[i] = add2(e1, e2, trueLimX, trueLimY);
//                    export2Dot(edge[i], "e3.dot", true, true, false, false, true);
#if !NDEBUG

                    CVec vectorResult = getVector(edge[i], w);
                    if (!vectorsApproximatelyEqual(vectorResult, vectorExpected)) {
                        Log::log << "[add2] ERROR addition went wrong.\n";
                        Log::log << "[add2] Left operand: " << LimEntry<>::to_string(&limX, x.p->v) << " * " << x << ";  Right operand: " << LimEntry<>::to_string(&limY, y.p->v) << " * " << y << '\n';
                        Log::log << "arg0:    ";
                        printCVec(vectorArg0);
                        Log::log << '\n';
                        Log::log << "arg1     ";
                        printCVec(vectorArg1);
                        Log::log << '\n';
                        Log::log << "expected ";
                        printCVec(vectorExpected);
                        Log::log << '\n';
                        Log::log << "result   ";
                        printCVec(vectorResult);
                        Log::log << '\n';
                        //export2Dot(e1, "add-error-x.dot", false, true, true, false, true);
                        //export2Dot(e2, "add-error-y.dot", false, true, true, false, true);
                        //export2Dot(edge[i], "add-error-result.dot", false, true, true, false, true);
                        throw std::runtime_error("[add2] ERROR Add did not return expected result. See images 'add-error-x.dot',  'add-error-y.dot',  'add-error-result.dot'");
                    }

#endif
                }

                if (!x.isTerminal() && x.p->v == w && e1.w != Complex::zero) {
                    cn.returnToCache(e1.w);
                }

                if (!y.isTerminal() && y.p->v == w && e2.w != Complex::zero) {
                    cn.returnToCache(e2.w);
                }
            }
            auto e = makeDDNode(w, edge, true);
#if !NDEBUG
            //            Log::log << "[add2] computing vector x.\n";

            CVec vectorArg0 = getVector(x, w, limX);
            //            Log::log << "[add2] computing vector y.\n";
            CVec vectorArg1     = getVector(y, w, limY);
            CVec vectorExpected = addVectors(vectorArg0, vectorArg1);
            CVec vectorResult   = getVector(e, w);
            if (!vectorsApproximatelyEqual(vectorResult, vectorExpected)) {
                Log::log << "[add2] ERROR addition went wrong.\n";
                Log::log << "[add2] Left operand: " << LimEntry<>::to_string(&limX, x.p->v) << " * " << x << ";  Right operand: " << LimEntry<>::to_string(&limY, y.p->v) << " * " << y << '\n';
                Log::log << "arg0:    ";
                printCVec(vectorArg0);
                Log::log << '\n';
                Log::log << "arg1     ";
                printCVec(vectorArg1);
                Log::log << '\n';
                Log::log << "expected ";
                printCVec(vectorExpected);
                Log::log << '\n';
                Log::log << "result   ";
                printCVec(vectorResult);
                Log::log << '\n';
                //export2Dot(x, "add-error-x.dot", false, true, true, false, true, false);
                //export2Dot(y, "add-error-y.dot", false, true, true, false, true, false);
                //export2Dot(e, "add-error-result.dot", false, true, true, false, true, false);
                throw std::runtime_error("[add2] ERROR Add did not return expected result. See images 'add-error-x.dot',  'add-error-y.dot',  'add-error-result.dot'");
            }

#endif

            //           if (r.p != nullptr && e.p != r.p){ // activate for debugging caching only
            //               std::cout << "Caching error detected in add" << std::endl;
            //           }

            trueLimXCopy.setPhase(getPhaseInverse(trueLimXCopy.getPhase()));
            trueLimXCopy.multiplyBy(e.l);
            auto weight = cn.getCached(e.w);
            movePhaseIntoWeight(trueLimXCopy, weight);
            //
            computeTable.insert({x.p, x.w, nullptr}, {y.p, y.w, trueLimCTable}, {e.p, weight, lf.limTable.lookup(trueLimXCopy)});
            cn.returnToCache(weight);
            endProfile(add)
            return e;
        }

        ///
        /// Matrix (conjugate) transpose
        ///
    public:
        UnaryComputeTable<mEdge, mEdge, CT_MAT_TRANS_NBUCKET>      matrixTranspose{};
        UnaryComputeTable<mEdge, mEdge, CT_MAT_CONJ_TRANS_NBUCKET> conjugateMatrixTranspose{};

        mEdge transpose(const mEdge& a) {
            if (a.p == nullptr || a.isTerminal() || a.p->isSymmetric()) {
                return a;
            }

            // check in compute table
            auto r = matrixTranspose.lookup(a);
            if (r.p != nullptr) {
                return r;
            }

            std::array<mEdge, NEDGE> e{};
            // transpose sub-matrices and rearrange as required
            for (auto i = 0U; i < RADIX; ++i) {
                for (auto j = 0U; j < RADIX; ++j) {
                    e[RADIX * i + j] = transpose(a.p->e[RADIX * j + i]);
                }
            }
            // create new top node
            r = makeDDNode(a.p->v, e);
            // adjust top weight
            auto c = cn.getTemporary();
            ComplexNumbers::mul(c, r.w, a.w);
            r.w = cn.lookup(c);

            // put in compute table
            matrixTranspose.insert(a, r);
            return r;
        }
        mEdge conjugateTranspose(const mEdge& a) {
            if (a.p == nullptr)
                return a;
            if (a.isTerminal()) { // terminal case
                auto r = a;
                r.w    = ComplexNumbers::conj(a.w);
                return r;
            }

            // check if in compute table
            auto r = conjugateMatrixTranspose.lookup(a);
            if (r.p != nullptr) {
                return r;
            }

            std::array<mEdge, NEDGE> e{};
            // conjugate transpose submatrices and rearrange as required
            for (auto i = 0U; i < RADIX; ++i) {
                for (auto j = 0U; j < RADIX; ++j) {
                    e[RADIX * i + j] = conjugateTranspose(a.p->e[RADIX * j + i]);
                }
            }
            // create new top node
            r = makeDDNode(a.p->v, e);

            auto c = cn.getTemporary();
            // adjust top weight including conjugate
            ComplexNumbers::mul(c, r.w, ComplexNumbers::conj(a.w));
            r.w = cn.lookup(c);

            // put it in the compute table
            conjugateMatrixTranspose.insert(a, r);
            return r;
        }

        ///
        /// Multiplication
        ///
    public:
        ComputeTable<mEdge, vEdge, vCachedEdge, CT_MAT_VEC_MULT_NBUCKET> matrixVectorMultiplication{};
        ComputeTable<mEdge, mEdge, mCachedEdge, CT_MAT_MAT_MULT_NBUCKET> matrixMatrixMultiplication{};
        ComputeTable<dEdge, dEdge, dCachedEdge, CT_DM_DM_MULT_NBUCKET>   densityDensityMultiplication{};

        template<class LeftOperandNode, class RightOperandNode>
        [[nodiscard]] auto& getMultiplicationComputeTable() {
            if constexpr (std::is_same_v<RightOperandNode, vNode>) {
                return matrixVectorMultiplication;
            } else if constexpr (std::is_same_v<RightOperandNode, mNode>) {
                return matrixMatrixMultiplication;
            } else if constexpr (std::is_same_v<RightOperandNode, dNode>) {
                return densityDensityMultiplication;
            }
        }

        dEdge applyOperationToDensity(dEdge& e, const mEdge& operation, bool generateDensityMatrix = false) {
            [[maybe_unused]] const auto before = cn.cacheCount();
            auto                        tmp0   = conjugateTranspose(operation);
            auto                        tmp1   = multiply(e, densityFromMatrixEdge(tmp0), 0, false);
            auto                        tmp2   = multiply(densityFromMatrixEdge(operation), tmp1, 0, generateDensityMatrix);
            incRef(tmp2);
            dEdge::alignDensityEdge(e);
            decRef(e);
            e = tmp2;

            if (generateDensityMatrix) {
                dEdge::setDensityMatrixTrue(e);
            }

            return e;
        }

        template<class LeftOperand, class RightOperand>
        RightOperand multiply(const LeftOperand& x, const RightOperand& y, dd::Qubit start = 0, [[maybe_unused]] bool generateDensityMatrix = false) {
            [[maybe_unused]] const auto before         = cn.cacheCount();
            [[maybe_unused]] const auto limCountBefore = lf.cacheCount();

            Qubit        var = -1;
            RightOperand e;

            if constexpr (std::is_same_v<LeftOperand, dEdge>) {
                auto xCopy = x;
                auto yCopy = y;
                dEdge::applyDmChangesToEdges(xCopy, yCopy);

                if (!xCopy.isTerminal()) {
                    var = xCopy.p->v;
                }
                if (!y.isTerminal() && yCopy.p->v > var) {
                    var = yCopy.p->v;
                }
                //Log::log << "[multiply] Start multiplying Mat x Vec.\n";
                e = multiply2(xCopy, yCopy, var, start, generateDensityMatrix);
                //Log::log << "[multiply] Multiplication complete. Node: " << e << '\n';

                dEdge::revertDmChangesToEdges(xCopy, yCopy);

            } else {
                if (!x.isTerminal()) {
                    var = x.p->v;
                }
                if (!y.isTerminal() && (y.p->v) > var) {
                    var = y.p->v;
                }
                bool appliedCliffordGate = false;
                if constexpr (std::is_same_v<RightOperand, vEdge>) {
                    if (usingSpecialCliffordCaching(cachingStrategy)) {
                        e = applyCliffordGate(x, y, appliedCliffordGate);
                    }
                }
                if (!appliedCliffordGate) {
                    e = multiply2(x, y, var, start);
                }
            }

            if (!e.w.exactlyZero() && !e.w.exactlyOne()) {
                cn.returnToCache(e.w);
                e.l = lf.limTable.lookup(LimEntry<>(e.l));
                e.w = cn.lookup(e.w);
            }

            [[maybe_unused]] const auto after         = cn.cacheCount();
            [[maybe_unused]] const auto limCountAfter = lf.cacheCount();
            assert(before == after);
            assert(limCountBefore == limCountAfter);

            return e;
        }

        vEdge applyCliffordGate(const Edge<mNode>& x, const vEdge y, bool& appliedCliffordGate) {
            //Log::log << "[applyCliffordGate] start.\n";
            vEdge e = applyHadamardGate(x, y, appliedCliffordGate);
            if (!appliedCliffordGate) {
                e = applyPhaseGate(x, y, appliedCliffordGate);
            }
            if (!appliedCliffordGate) {
                e = applyControlledPauliGate(x, y, appliedCliffordGate);
            }
            if (!appliedCliffordGate) {
                e = applyPauliGate(x, y, appliedCliffordGate);
            }
            if (!appliedCliffordGate) {
                e = applyIdentityGate(x, y, appliedCliffordGate);
            }
            return e;
        }

        template<class Node>
        std::pair<Edge<Node>, LimEntry<>> follow(const Edge<Node>& e, const short path, LimEntry<> lim) {
            assert(e.p != nullptr);
            LimEntry<> lim2(lim);
            lim2.multiplyBy(e.l);

            const auto op = lim2.getPauliForQubit(e.p->v);
            lim2.setOperator(e.p->v, 'I');

            auto e1 = follow2(e, path, op);
            return {e1, lim2};
        }

        template<class Node>
        Edge<Node> follow2(const Edge<Node>& e, const short path, pauli_op op) {
            assert(e.p != nullptr);
            Edge<Node> newE = {};
            switch (op) {
                case pauli_id:
                    //                    Log::log << "[Follow] encountered I \n";
                    return e.p->e[path];
                case pauli_x:
                    //                    Log::log << "[Follow] encountered X \n";
                    return e.p->e[1 - path];
                case pauli_y:
                    //                    Log::log << "[Follow] encountered Y \n";
                    newE = e.p->e[1 - path];
                    if (path == 0) {
                        newE.w.multiplyByMinusi(false);
                    } else {
                        newE.w.multiplyByi(false);
                    }
                    return newE;
                case pauli_z:
                    //                    Log::log << "[Follow] encountered Z \n";
                    if (path == 1) {
                        newE = e.p->e[path];
                        newE.w.multiplyByMinusOne(false);
                        return newE;
                    } else {
                        return e.p->e[path];
                    }
                default:
                    throw std::runtime_error("[Follow] Encountered unknown group element!\n");
            }
        }

    private:
        void makePrintIdent(Qubit var) {
            for (Qubit jk = var; jk < (Qubit)nqubits; jk++) {
                std::cout << "\t\t";
            }
        }

        bool topQubitIsIdentity(const Edge<mNode>& mat) {
            if (mat.p->e[0].p == mat.p->e[3].p &&
                mat.p->e[0].w == Complex::one &&
                mat.p->e[1].w == Complex::zero &&
                mat.p->e[2].w == Complex::zero &&
                mat.p->e[3].w == Complex::one) return true;
            return false;
        }

        void setIdentityFlags(Edge<mNode>& mat) {
            setIdentityFlagsTraverseDD(mat);
            unsetVisitationFlags(mat);
        }

        void setIdentityFlagsTraverseDD(Edge<mNode>& mat) {
            if (mat.isTerminal()) {
                mat.p->setIdentity(true);
                return;
            }
            if (mat.p->flags & 1)
                return;
            for (int i = 0; i < 4; i++) {
                setIdentityFlagsTraverseDD(mat.p->e[i]);
            }
            if (mat.p->e[0].p->isIdentity() && mat.p->e[0].p == mat.p->e[3].p &&
                mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero &&
                mat.p->e[3].w == Complex::one) {
                mat.p->setIdentity(true);
            } else
                mat.p->setIdentity(false);
            mat.p->flags |= 1;
        }

        void unsetVisitationFlags(Edge<mNode>& mat) {
            if (mat.isTerminal()) {
                return;
            }
            if (!(mat.p->flags & 1)) {
                return;
            }
            unsetVisitationFlags(mat.p->e[0]);
            unsetVisitationFlags(mat.p->e[1]);
            unsetVisitationFlags(mat.p->e[2]);
            unsetVisitationFlags(mat.p->e[3]);

            mat.p->flags = (mat.p->flags & (~1));
        }

        // Returns whether the edge represents a single Hadamard gate and several identity gates
        // If so, returns the index of the qubit to which the Hadamard is applied
        // Otherwise, returns -1
        // requires matrix node identity flags to be set
        CliffordGate isHadamardGate(const Edge<mNode>& mat) {
            // either this qubit is the identity, or it's a hadamard and the rest is the identity
            CliffordGate gate = CliffordGate(cliffNoGate, {-1, Control::Type::pos}, -1);
            if (mat.p == mNode::terminal) return gate;
            if (topQubitIsIdentity(mat)) {
                return isHadamardGate(mat.p->e[0]);
            }
            if (mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::one &&
                mat.p->e[2].w == Complex::one && mat.p->e[3].w == Complex::minus_one &&
                mat.p->e[0].p == mat.p->e[1].p && mat.p->e[0].p == mat.p->e[2].p && mat.p->e[0].p == mat.p->e[3].p &&
                mat.p->e[0].p->isIdentity()) {
                return CliffordGate(cliffHadamard, {-1, Control::Type::pos}, mat.p->v);
            }
            return gate;
        }

        Qubit isPhaseGate(const Edge<mNode>& mat) {
            if (mat.p == mNode::terminal) return (Qubit) -1;
            if (topQubitIsIdentity(mat)) return isPhaseGate(mat.p->e[0]);
            if (mat.p->e[0].p == mat.p->e[3].p &&
                mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && mat.p->e[3].w == Complex::complex_i &&
                mat.p->e[0].p->isIdentity()) {
                return mat.p->v;
            }
            return (Qubit)-1;
        }

        CliffordGate isPauliGate(const Edge<mNode>& mat) {
            CliffordGate gate(cliffNoGate, {-1, Control::Type::pos}, -1);
            //Log::log << "[isPauli, n=" << (int)mat.p->v << "]\n";
            if (mNode::isTerminal(mat.p)) return gate;
            if (topQubitIsIdentity(mat)) return isPauliGate(mat.p->e[0]);
            //Log::log << "[isPauli, n=" << (int)mat.p->v << "] weights = [" << mat.p->e[0].w << ", " << mat.p->e[1].w << ", " << mat.p->e[2].w << ", " << mat.p->e[3].w << "] identity = ["
            //         << mat.p->e[0].p->isIdentity() << ", " << mat.p->e[1].p->isIdentity() << ", " << mat.p->e[2].p->isIdentity() << ", " << mat.p->e[3].p->isIdentity() << "]\n";
            // Check if this gate is X
            if (mat.p->e[1].p == mat.p->e[2].p &&
                mat.p->e[0].w == Complex::zero && mat.p->e[1].w == Complex::one && mat.p->e[2].w == Complex::one && mat.p->e[3].w == Complex::zero &&
                mat.p->e[1].p->isIdentity()) {
                return CliffordGate(cliffpauli_x, {-1, Control::Type::pos}, mat.p->v);
            }
            // Check if this gate is Y
            if (mat.p->e[1].p == mat.p->e[2].p &&
                mat.p->e[0].w == Complex::zero && mat.p->e[1].w == Complex::one && mat.p->e[2].w == Complex::minus_one && mat.p->e[3].w == Complex::zero &&
                mat.p->e[1].p->isIdentity()) {
                return CliffordGate(cliffpauli_y, {-1, Control::Type::pos}, mat.p->v);
            }
            // Check if this gate is Z
            if (mat.p->e[0].p == mat.p->e[3].p &&
                mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && mat.p->e[3].w == Complex::minus_one &&
                mat.p->e[0].p->isIdentity()) {
                return CliffordGate(cliffpauli_z, {-1, Control::Type::pos}, mat.p->v);
            }
            return gate;
        }

        // Return whether this matrix projects a qubit t onto value |b>, for some b in {0,1}.
        // If so, returns the pair (t, b)
        // otherwise, returns the pair (-1, 0)
        std::pair<Qubit, bool> isProjectionOperator(const Edge<mNode>& mat) {
            std::pair<Qubit, bool> gate = {-1, false};
            if (mNode::isTerminal(mat.p)) return gate;
            if (topQubitIsIdentity(mat)) return isProjectionOperator(mat.p->e[0]);
            if (mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && mat.p->e[3].w == Complex::zero &&
                mat.p->e[0].p->isIdentity()) {
                gate = {mat.p->v, 0};
            }
            else if (mat.p->e[0].w == Complex::zero && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && mat.p->e[3].w == Complex::one &&
                mat.p->e[1].p->isIdentity()) {
                gate = {mat.p->v, 1};
            }
            return gate;
        }

        CliffordGate isControlledPauliGate(const Edge<mNode>& mat) {
            CliffordGate gate(cliffNoGate, {-1, Control::Type::pos}, -1);
            if (mNode::isTerminal(mat.p)) {
                //Log::log << "[isCP] arrived at terminal.\n";
                return gate;
            }
            //Log::log <<  "[isCP] n=" << (int) mat.p->v << " identity = [ " << mat.p->e[0].p->isIdentity() << ", " << mat.p->e[1].p->isIdentity() << ", " << mat.p->e[2].p->isIdentity() << ", " << mat.p->e[3].p->isIdentity() << "] "
            //         << "terminal = [" << mNode::isTerminal(mat.p->e[0].p) << ", " << mNode::isTerminal(mat.p->e[1].p) << ", " << mNode::isTerminal(mat.p->e[2].p) << ", " << mNode::isTerminal(mat.p->e[3].p) << "]  "
            //         << "weight = [" << (mat.p->e[0].w) << ", " << (mat.p->e[1].w) << ", " << (mat.p->e[2].w) << ", " << (mat.p->e[3].w) << "]\n";
            if (topQubitIsIdentity(mat)) {
                //Log::log << "[isCP] top qubit " << (int) mat.p->v << " is identity; recursing.\n";
                return isControlledPauliGate(mat.p->e[0]);
            }
            // Check for positive downward-controlled Pauli
            // TODO merge code of cases positive controlled Pauli and controlled neg Pauli
            if (mat.p->e[0].p->isIdentity() &&
                mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && (mat.p->e[3].w == Complex::one || mat.p->e[3].w == Complex::minus_i)) {
                gate = isPauliGate(mat.p->e[3]);
                //Log::log << "[isCP] checked e[3], is gate " << (char) gate.gateType << " on qubit " << (int)gate.target << '\n';
                if (gate.gateType != cliffNoGate) {
                    gate.control = {mat.p->v, Control::Type::pos};
                }
            }
            // Check for negative upward-controlled Pauli Z
            else if (mat.p->e[0].p->isIdentity() &&
                     mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && mat.p->e[3].w == Complex::minus_one) {
                gate = isPauliGate(mat.p->e[3]);
                //Log::log << "[isCP] possible negative upward controlled " << (char)gate.gateType << " gate (should be Z).\n";
                if (gate.gateType == cliffpauli_z) {
                    gate = CliffordGate(cliffpauli_z, Control{gate.target, Control::Type::neg}, mat.p->v);
                }
            }
            // Check for negative downward-controlled Pauli
            // TODO merge code of downward-controlled Pauli X,Z with Pauli Y
            else if (mat.p->e[3].p->isIdentity() &&
                    (mat.p->e[0].w == Complex::one || mat.p->e[0].w == Complex::minus_i) && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && mat.p->e[3].w == Complex::one) {
                gate = isPauliGate(mat.p->e[0]);
                //Log::log << "[isCP] possible negative downward controlled Pauli.\n";
                if (gate.gateType != cliffNoGate) {
                    gate.control = {mat.p->v, Control::Type::neg};
                }
            }
            // Check for negative downward-controlled Y
            else if (mat.p->e[3].p->isIdentity() &&
                     mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::zero && mat.p->e[2].w == Complex::zero && mat.p->e[3].w == Complex::complex_i) {
                gate = isPauliGate(mat.p->e[0]);
                //Log::log << "[isCP] possible negative downward controlled Y.\n";
                if (gate.gateType != cliffNoGate) {
                    gate.control = {mat.p->v, Control::Type::neg};
                }
            }
            // TODO merge the upward controlled X and Y cases, to take up less code
            // Check for upwards controlled X
            else if (mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::one && mat.p->e[2].w == Complex::one && mat.p->e[3].w == Complex::one &&
                     mat.p->e[0].p == mat.p->e[3].p && mat.p->e[1].p == mat.p->e[2].p) {
                std::pair<Qubit, bool> projection0 = isProjectionOperator(mat.p->e[0]);
                std::pair<Qubit, bool> projection1 = isProjectionOperator(mat.p->e[1]);
                //Log::log << "[isCP] possible upward controlled X. projection0 = " << (int)projection0.first << ", " << (int)projection0.second << " projection1 << " << projection1.first << ", " << projection1.second << "\n";
                // TODO merge these two cases of positive and negative control
                if (projection0.second == false && projection1.second == true && projection0.first == projection1.first && projection0.first != (Qubit)-1) {
                    gate = CliffordGate(cliffpauli_x, {projection0.first, Control::Type::pos}, mat.p->v);
                } else if (projection0.second == true && projection1.second == false && projection0.first == projection1.first && projection0.first != (Qubit)-1) {
                    gate = CliffordGate(cliffpauli_x, {projection0.first, Control::Type::neg}, mat.p->v);
                }
            }
            // Check for upwards controlled Y
            else if (mat.p->e[0].w == Complex::one && mat.p->e[1].w == Complex::minus_i && mat.p->e[2].w == Complex::complex_i && mat.p->e[3].w == Complex::one &&
                     mat.p->e[0].p == mat.p->e[3].p && mat.p->e[1].p == mat.p->e[2].p) {
                std::pair<Qubit, bool> projection0 = isProjectionOperator(mat.p->e[0]);
                std::pair<Qubit, bool> projection1 = isProjectionOperator(mat.p->e[1]);
                //Log::log << "[isCP] possible upward controlled Y, " << projection0.second << ", " << projection1.second << "\n";
                if (projection0.second == false && projection1.second == true && projection0.first == projection1.first && projection0.first != (Qubit)-1) {
                    gate = CliffordGate(cliffpauli_y, {projection0.first, Control::Type::pos}, mat.p->v);
                } else if (projection0.second == true && projection1.second == false && projection0.first == projection1.first && projection0.first != (Qubit)-1) {
                    gate = CliffordGate(cliffpauli_y, {projection0.first, Control::Type::neg}, mat.p->v);
                }
            }
            //Log::log << "[isCP, n=" << (int)mat.p->v << "] Verdict: gate is " << gate << ".\n";
            return gate;
        }

        // returns a vector containing the indices of all qubits on which 'mat' does not act as the identity
        std::vector<Qubit> getActiveQubits(Edge<mNode> mat) {
            std::set<Qubit> activeQubits;
            getActiveQubitsTraverseDD(mat, activeQubits);
            unsetVisitationFlags(mat);
            std::vector<Qubit> activeQubitsVec;
            // add all qubits to the vector
            //Log::log << "[selectActivePart] found " << activeQubits.size() << " active qubits.\n";
            for (auto it = activeQubits.begin(); it != activeQubits.end(); it ++) {
                activeQubitsVec.push_back(*it);
            }
            std::sort(activeQubitsVec.begin(), activeQubitsVec.end());
            return activeQubitsVec;
        }

        void getActiveQubitsTraverseDD(Edge<mNode> mat, std::set<Qubit>& active) {
            if (mNode::isTerminal(mat.p)) return;
            if (mat.p->flags & 1) return; // node has been previously visited
            if (mat.w.exactlyZero()) return; // matrix acts trivially on all qubits
            if (mat.p->isIdentity()) return; // matrix acts trivially on all qubits
            //Log::log << "[getActQubits, n=" << (int) mat.p->v << "] weights = " << mat.p->e[0].w << ", " << mat.p->e[1].w << ", " << mat.p->e[2].w << ", " << mat.p->e[3].w << "\n";
            if (!topQubitIsIdentity(mat)) {
                //Log::log << "[getActQubits, n=" << (int) mat.p->v << "] found non-identity.\n";
                active.insert(mat.p->v);
            }
            for (int i=0; i<4; i++) {
                getActiveQubitsTraverseDD(mat.p->e[i], active);
            }
            mat.p->flags |= 1; // mark node as visited
        }

    public:
        unsigned int multiply2CallCount = 0;
        clock_t multiply2Time = 0;
    private:
        // Returns x * lim * y
        template<class LeftOperandNode, class RightOperandNode>
        Edge<RightOperandNode> multiply2(const Edge<LeftOperandNode>&       x,
                                         const Edge<RightOperandNode>&      y,
                                         Qubit                              var,
                                         Qubit                              start                 = 0,
                                         [[maybe_unused]] bool              generateDensityMatrix = false,
                                         [[maybe_unused]] const LimEntry<>& lim                   = {}) {
            startProfile(multiply2)
            multiply2CallCount++;
            [[maybe_unused]] const unsigned int callIndex = multiply2CallCount;
            using LEdge             = Edge<LeftOperandNode>;
            using REdge             = Edge<RightOperandNode>;
            using ResultEdge        = Edge<RightOperandNode>;
            using LEdge                              = Edge<LeftOperandNode>;
            using REdge                              = Edge<RightOperandNode>;
            using ResultEdge                         = Edge<RightOperandNode>;
            if (x.p == nullptr) return {nullptr, Complex::zero, nullptr};
            if (y.p == nullptr) return y;

            if (x.w.exactlyZero() || y.w.exactlyZero()) {
                return ResultEdge::zero;
            }
#if !NDEBUG
            CMat mat_x = getMatrix(x);
            CVec vec_y = getVector(y, var, lim);
            CVec vecExpected = multiplyMatrixVector(mat_x, vec_y);
#endif
            auto xCopy = x;
            xCopy.w    = Complex::one;
            auto       yCopy   = y;
            yCopy.w    = Complex::one;

            LimEntry<>  reducedLim;
            phase_t     reducedLimPhase;
            LimEntry<>* reducedLimTable;
            LimEntry<> limActive, limInactive;
            LimEntry<>* limActiveTable;
            phase_t activeLimPhase;
            pauli_op op;

            /// Check if x is the identity gate; if so, then we can fast-forward this calculation a lot
            if (usingSkipIdentityGate(cachingStrategy)) {
                if (x.p->isIdentity()) {
                    auto resultWeight = cn.getCached(CTEntry::val(y.w.r), CTEntry::val(y.w.i));
                    cn.mul(resultWeight, resultWeight, x.w);
                    LimEntry<> resultLim(lim);
                    resultLim.multiplyBy(y.l);
                    movePhaseIntoWeight(resultLim, resultWeight);

                    yCopy.l = lf.limTable.lookup(resultLim);
                    yCopy.w = resultWeight;
                    return yCopy;
                }
            }

            if (var == start - 1) {
                auto resultWeight = cn.getCached(CTEntry::val(y.w.r), CTEntry::val(y.w.i));
                ComplexNumbers::mul(resultWeight, x.w, resultWeight);
                //if (usingLocalityAwareCachingDirtyTrick(cachingStrategy)) {
                //    resultWeight.multiplyByPhase(lim.getPhase());
                //} else {
                LimEntry<> lim2(lim);
                lim2.multiplyBy(y.l);
                resultWeight.multiplyByPhase(lim2.getPhase());
                //}
                return ResultEdge::terminal(resultWeight);
            }

            auto& computeTable = getMultiplicationComputeTable<LeftOperandNode, RightOperandNode>();


            /// Lookup the computation in the cache
            if constexpr (std::is_same_v<RightOperandNode, vNode>) {
                if (usingLocalityAwareCachingDirtyTrick(cachingStrategy)) {
                    //Log::log << "[multiply2, c=" << callIndex << " n=" << (int) y.p->v << "] Start. y = " << y << "; lim = "<< lim.to_string(y.p->v) << "; lim * |y> = " << outputCVec(getVector(y, var, lim)) << ". Currently limActive = limInactive = " << limActive.to_string(y.p->v) << (x.p->isIdentity() ? "; matrix is identity.\n" : "\n");
                    std::vector<Qubit> activeQubits = getActiveQubits(x);
                    //Log::log << "[multiply2, c=" << callIndex << " n=" << (int) y.p->v << "] [pre process] found active qubits: {"; for (int i=0; i<activeQubits.size(); i++) Log::log << (int)activeQubits[i] << " "; Log::log << "}\n";
                    limActive = lim;
                    limActive.multiplyBy(y.l);
                    activeLimPhase = limActive.getPhase();
                    limActive.setPhase(phase_one);
                    limInactive = limActive;
                    limActive.selectActivePart(activeQubits);
                    if (usingLocalityAwarePropagateReducedLim(cachingStrategy)) {
                        limActive = getRootLabel(y.p, &limActive);
                    }
                    limInactive.selectInactivePart(activeQubits);
                    limActiveTable = lf.limTable.lookup(limActive); // TODO this inserts 'limActive' into the LimTable, which may not be desirable
                    //Log::log << "[multiply2, c=" << callIndex << " n=" << (int) y.p->v << "] [pre process] dirty trick. Lookup in cache: " << vEdge{y.p, Complex::one, limActiveTable} << " limActive = " << limActive.to_string(y.p->v) << "  limInactive = " << LimEntry<>::to_string(&limInactive, y.p->v) << "\n";
                    auto cachedEdge = computeTable.lookup({x.p, Complex::one, nullptr}, {y.p, Complex::one, limActiveTable}, false);
                    if (cachedEdge.p != nullptr) {
                        auto result = ResultEdge{cachedEdge.p, cn.getCached(cachedEdge.w), cachedEdge.l};
                        //Log::log << "[multiply, n=" << (int) y.p->v << "] cache hit! Asked for y=" << y << "  got result = " << result << "\n";
                        ComplexNumbers::mul(result.w, result.w, x.w);
                        ComplexNumbers::mul(result.w, result.w, y.w);
                        if (result.w.approximatelyZero()) {
                            cn.returnToCache(result.w);
                            return ResultEdge::zero;
                        }
                        result.w.multiplyByPhase(activeLimPhase);
                        LimEntry<> resultLim(result.l);
                        resultLim.leftMultiplyBy(limInactive);
                        movePhaseIntoWeight(resultLim, result.w);
                        result.l = lf.limTable.lookup(resultLim);
                        return result;
                    }
                    yCopy.l = limActiveTable;
                    op = yCopy.l->getPauliForQubit(yCopy.p->v);
                    //Log::log << "[multiply2, c=" << callIndex << " n=" << (int) y.p->v << "] [pre process] cache miss. Now yCopy = " << yCopy << "  limInactive = " << limInactive.to_string(y.p->v) << " op = " << (char)op << "\n";
                }
                else if (cachingStrategy == CachingStrategy::localityAwareCachingClean) { // TODO
                    std::cout << "[multiply2] ERROR clean caching not yet implemented.\n";
                    throw std::runtime_error("[multiply2] ERROR clean caching not yet implemented.\n");
                }
                else {
                    reducedLim = lim;
                    reducedLim.multiplyBy(y.l);
                    reducedLim      = getRootLabel(y.p, &reducedLim);
                    reducedLimPhase = reducedLim.getPhase();
                    reducedLim.setPhase(phase_t::phase_one);

                    // TODO this puts 'reducedLimTable' in the table, which may not be desirable, since this LIM is not referenced by any node.
                    //   Therefore, its refcount is not decremented at the end of the method, and it henceforth lives on as a 'zombie' in the table
                    //   solution: look up reducedLim in the table, and if this LIM is not in the table, then we can immediately conclude that the compute table does not contain what we are looking for either
                    //   (if I understand correctly) -LV
                    reducedLimTable = lf.limTable.lookup(reducedLim);
                    op = reducedLim.getPauliForQubit(yCopy.p->v);
                    auto r = computeTable.lookup({x.p, Complex::one, nullptr}, {y.p, Complex::one, reducedLimTable}, generateDensityMatrix);
                    //            if (r.p != nullptr && false) { // activate for debugging caching only
                    if (r.p != nullptr) {
                        if (r.w.approximatelyZero()) {
                            return ResultEdge::zero;
                        } else {
                            auto e = ResultEdge{r.p, cn.getCached(r.w), r.l};
                            ComplexNumbers::mul(e.w, e.w, x.w);
                            ComplexNumbers::mul(e.w, e.w, y.w);
                            e.w.multiplyByPhase(reducedLimPhase);
                            if (e.w.approximatelyZero()) {
                                cn.returnToCache(e.w);
                                return ResultEdge::zero;
                            }
                            return e;
                        }
                    }
                }
            }

            constexpr std::size_t N = std::tuple_size_v<decltype(y.p->e)>;

            ResultEdge e{};
            if constexpr (std::is_same_v<RightOperandNode, mCachedEdge>) {
                // This branch is only taken for matrices
                if (x.p->v == var && x.p->v == y.p->v) {
                    if (x.p->isIdentity()) {
                        if constexpr (N == NEDGE) {
                            // additionally check if y is the identity in case of matrix multiplication
                            if (y.p->isIdentity()) {
                                e = makeIdent(start, var);
                            } else {
                                e = yCopy;
                            }
                        } else {
                            e = yCopy;
                        }
                        computeTable.insert(xCopy, yCopy, {e.p, e.w, e.l});
                        e.w = cn.mulCached(x.w, y.w);
                        if (e.w.approximatelyZero()) {
                            cn.returnToCache(e.w);
                            return ResultEdge::zero;
                        }
                        return e;
                    }

                    if constexpr (N == NEDGE) {
                        // additionally check if y is the identity in case of matrix multiplication
                        if (y.p->isIdentity()) {
                            e = xCopy;
                            computeTable.insert(xCopy, yCopy, {e.p, e.w, e.l});
                            e.w = cn.mulCached(x.w, y.w);

                            if (e.w.approximatelyZero()) {
                                cn.returnToCache(e.w);
                                return ResultEdge::zero;
                            }
                            return e;
                        }
                    }
                }
            }

            constexpr std::size_t     ROWS = RADIX;
            constexpr std::size_t     COLS = N == NEDGE ? RADIX : 1U;
            std::array<ResultEdge, N> edge{};

            CVec vectorArg0, vectorArg1, vectorResult, vectorExpected;
            reducedLim.setOperator(y.p->v, pauli_id);

            LimEntry<> limActivePropagate;
            for (auto i = 0U; i < ROWS; i++) {
                for (auto j = 0U; j < COLS; j++) {
                    const auto idx = COLS * i + j;
                    edge[idx]      = ResultEdge::zero;
                    for (auto k = 0U; k < ROWS; k++) {
                        LEdge e1{};
                        if (!x.isTerminal() && x.p->v == var) {
                            e1 = x.p->e[ROWS * i + k];
                        } else {
                            e1 = xCopy;
                        }

                        if constexpr (std::is_same_v<LeftOperandNode, dNode>) {
                            dEdge m;
                            REdge e2{};
                            if (!y.isTerminal() && y.p->v == var) {
                                e2 = y.p->e[j + COLS * k];
                            } else {
                                e2 = yCopy;
                            }
                            dEdge::applyDmChangesToEdges(e1, e2);
                            if (!generateDensityMatrix || idx == 1) {
                                // When generateDensityMatrix is false or I have the first edge I don't optimize anything and set generateDensityMatrix to false for all child edges
                                m = multiply2(e1, e2, static_cast<Qubit>(var - 1), start, false);
                            } else if (idx == 2) {
                                // When I have the second edge and generateDensityMatrix == false, then edge[2] == edge[1]
                                if (k == 0) {
                                    if (edge[1].w.approximatelyZero()) {
                                        edge[2] = ResultEdge::zero;
                                    } else {
                                        edge[2] = ResultEdge{edge[1].p, cn.getCached(edge[1].w.r->value, edge[1].w.i->value), nullptr};
                                    }
                                }
                                continue;
                            } else {
                                m = multiply2(e1, e2, static_cast<Qubit>(var - 1), start, generateDensityMatrix);
                            }

                            if (k == 0 || edge[idx].w.exactlyZero()) {
                                edge[idx] = m;
                            } else if (!m.w.exactlyZero()) {
                                dEdge::applyDmChangesToEdges(edge[idx], m);
                                auto old_e = edge[idx];
                                edge[idx]  = add2(edge[idx], m);
                                dEdge::revertDmChangesToEdges(edge[idx], e2);
                                cn.returnToCache(old_e.w);
                                cn.returnToCache(m.w);
                            }
                            //Undo modifications on density matrices
                            dEdge::revertDmChangesToEdges(e1, e2);
                        } else {
                            REdge      e2{};
                            if (!y.isTerminal() && y.p->v == var) {
                                e2 = follow2(yCopy, j + COLS * k, op);
                            } else {
                                e2 = yCopy;
                            }
                            ResultEdge m;
                            if (usingLocalityAwareCachingDirtyTrick(cachingStrategy)) {
                                limActivePropagate = limActive;
                                limActivePropagate.setOperator(y.p->v, pauli_id);
                                m = multiply2(e1, e2, static_cast<Qubit>(var - 1), start, false, limActivePropagate);
                                //Log::log << "[multiply2, c=" << callIndex << " n=" << (int)x.p->v << "] got result " << outputCVec(getVector(m,x.p->v-1)) << "\n";
                            } else {
                                m = multiply2(e1, e2, static_cast<Qubit>(var - 1), start, false, reducedLim);
                            }

                            if (k == 0 || edge[idx].w.exactlyZero()) {
                                edge[idx] = m;
                            } else if (!m.w.exactlyZero()) {
                                auto old_e = edge[idx];
                                edge[idx] = add2(edge[idx], m);
                                cn.returnToCache(old_e.w);
                                cn.returnToCache(m.w);
                            }
                        }
                    }
                }
            }
            //            export2Dot(edge[0], "edge0.dot", true, true, false, false, true);
            //            export2Dot(edge[1], "edge1.dot", true, true, false, false, true);

            if constexpr (std::is_same_v<RightOperandNode, vNode>) {
#if !NDEBUG
                CVec vece0, vece1, vece;

                vece0 = getVector(edge[0], var - 1);
                vece1 = getVector(edge[1], var - 1);
#endif
                e = makeDDNode(var, edge, true, nullptr);
#if !NDEBUG
                vece = getVector(e, var);
                if (!sanityCheckMakeDDNode(vece0, vece1, vece)) {
                    Log::log << "[multiply2, c=" << callIndex << " n="<< (int) y.p->v << "] ERROR sanity check failed after makeDDNode.\n"
                             << "[multiply2] edge[0]    = " << edge[0] << '\n'
                             << "[multiply2] edge[1]    = " << edge[1] << '\n'
                             << "[multiply2] e (result) = " << e << '\n'
                             << "[multiply2] vece0         = ";
                    printCVec(vece0);
                    Log::log << "[multiply2] vece1         = ";
                    printCVec(vece1);
                    Log::log << "[multiply2] vece (result) = ";
                    printCVec(vece);
                    throw std::runtime_error("[multiply2] ERROR Sanity check failed after makenode.");
                }
#endif
            } else {
                e = makeDDNode(var, edge, true, generateDensityMatrix);
            }

            //            if (r.p != nullptr && e.p != r.p) { // activate for debugging caching
            //                std::cout << "Caching error detected in mul" << std::endl;
            //            } else {
            //                e = ResultEdge{r.p, cn.getCached(r.w), r.l};
            //            }

            /// Next step: Insert the result 'e' into the compute cache
            if (usingLocalityAwareCachingDirtyTrick(cachingStrategy)) {
                //CVec evec = getVector(e);
                //Log::log << "[multiply2, c=" << callIndex << " n=" << (int)x.p->v << "] [postprocess] Result of computation before correcting for limInactive (" << limInactive.to_string(y.p->v) << "): " << e << " with vector " << outputCVec(getVector(e)) << "  op=" << (char) op << "\n";
                computeTable.insert({x.p, Complex::one, nullptr}, {y.p, Complex::one, limActiveTable}, {e.p, e.w, e.l}); // TODO use e instead of {e.p, e.w, e.l}
                //Log::log << "[multiply2, n=" << (int)x.p->v << "] inserted edge into cache: y=" << vEdge{y.p, Complex::one, limActiveTable} << " e=" << vEdge{e.p, e.w, e.l} << "\n";
                //Log::log << "[multiply2, c=" << callIndex << " n=" << (int)x.p->v << "] NOTE: NOT inserting result into cache; not yet enabled.\n";
                LimEntry<> elim(e.l);
                elim.leftMultiplyBy(limInactive);
                movePhaseIntoWeight(elim, e.w);
                e.l = lf.limTable.lookup(elim);
                //Log::log << "[multiply2, c=" << callIndex << " n=" << (int)x.p->v << "] [postprocess] Result of computation after correcting for limInactive, e = " << e << " with vector " << outputCVec(getVector(e)) << "\n";
            } else {
                computeTable.insert({x.p, Complex::one, nullptr}, {y.p, Complex::one, reducedLimTable}, {e.p, e.w, e.l}); // TODO use e instead of {e.p, e.w, e.l}
            }

            //            export2Dot(e, "edgeResult0.dot", true, true, false, false, true);
            if (!e.w.exactlyZero() && (x.w.exactlyOne() || !y.w.exactlyZero())) {
                ComplexNumbers::mul(e.w, e.w, x.w);
                ComplexNumbers::mul(e.w, e.w, y.w);
                if (e.w.approximatelyZero()) {
                    cn.returnToCache(e.w);
                    return ResultEdge::zero;
                }
                if (usingLocalityAwareCachingDirtyTrick(cachingStrategy)) {
                    e.w.multiplyByPhase(activeLimPhase);
                } else {
                    e.w.multiplyByPhase(reducedLimPhase);
                }
            }

#if !NDEBUG
            // Last step: sanity check to see whether the resulting vector is what was expected
            CVec vecResult;
            vecResult = getVector(e);
            if (!vectorsApproximatelyEqual(vecResult, vecExpected)) {
                Log::log << "[multiply2, c=" << callIndex << "] ERROR. Computed DD result vector is different from expected result vector.\n"
                         << "[multiply2] input edge: y=" << y << "\n"
                         << "[multiply2] input amplitude vector: ";
                printCVec(vec_y);
                Log::log << "\n[multiply2] Matrix:\n";
                printMatrix(xCopy);
                Log::log << "\n[multiply2] Expected result: ";
                printCVec(vecExpected);
                Log::log << "\n[multiply2] Actual result:  ";
                printCVec(vecResult);
                //throw std::runtime_error("[multiply2] ERROR  multiply does not return expected result.\n");
            }
            //            export2Dot(e, "edgeResult.dot", true, true, false, false, true);
#endif
            assert(e.p->v > 0 && e.p->e[0].w.approximatelyZero() && !e.p->e[0].isZeroTerminal());
            assert(e.p->v > 0 && e.p->e[1].w.approximatelyZero() && !e.p->e[1].isZeroTerminal());

            //Log::log << "[multiply2, c=" << callIndex << "] returning e=" << outputCVec(getVector(e, y.p->v)) << "\n";
            return e;
        }

    public:
        vEdge applyGate(const QuantumGate& gate, const vEdge state) {
            //            printMatrix(makeGateDD(gate.mat, qubits(), gate.controls, gate.target));
            Edge<mNode> gateDD = makeGateDD(gate.mat, qubits(), gate.controls, gate.target);
            //setIdentityFlags(gateDD);
            return multiply(gateDD, state);
        }

        unsigned int applyPauliCallCount = 0;
        // TODO modernize
        vEdge applyPauliGate(const Edge<mNode>& x, const vEdge& y, bool& success) {
            startProfile(applyPauli)
            success = false;
            if (!usingSpecialCliffordCaching(cachingStrategy)) return y;
            CliffordGate gate = isPauliGate(x);
            //Log::log << "[Apply Pauli] Pauli gate is " << (char) gate.gateType << " on qubit " << (int) gate.target << "\n";
            if (gate.gateType != cliffNoGate) {
                vEdge result = y; // TODO refactor to call applySpecificPauliGate
                LimEntry<> lim(result.l);
                lim.leftMultiplyBy(gate.target, (pauli_op) gate.gateType);
                result.w = cn.getCachedIfNonzero(result.w);
                movePhaseIntoWeight(lim, result.w);
                result.l = lf.limTable.lookup(lim); // TODO should we decrement the refcount of the old LIM?
                success = true;
                return result;
            }
            return y;
        }

        vEdge applySpecificPauliGate(const vEdge& y, const CliffordGate gate) {
            //Log::log << "[applySpecificPauliGate, gate=" << gate << "] Start.\n";
            vEdge result = y;
            LimEntry<> lim(result.l);
            lim.leftMultiplyBy(gate.target, (pauli_op) gate.gateType);
            result.w = cn.getCachedIfNonzero(result.w);
            movePhaseIntoWeight(lim, result.w);
            result.l = lf.limTable.lookup(lim); // TODO should we decrement the refcount of y.l?
            return result;
        }

        vEdge applyHadamardGate(const Edge<mNode>& x, const vEdge& y, bool& success) {
            success = false;
            if (!usingSpecialCliffordCaching(cachingStrategy)) {
                return y;
            }
            CliffordGate gate = isHadamardGate(x);
            //std::cout << "[Hadamard] Hadamard target is " << (int) gate.target << "\n";
            if (gate.gateType != cliffNoGate) {
                success = true;
                return applyHadamardGate2(x, y, gate.target);
            }
            return y;
        }

        vEdge applyPhaseGate(const Edge<mNode>& x, const vEdge& y, bool& success) {
            success = false;
            if (!usingSpecialCliffordCaching(cachingStrategy)) {
                return y;
            }
            Qubit phaseTarget = isPhaseGate(x);
            //Log::log << "[Phase] phase gate is " << (int) phaseTarget << '\n';
            if (phaseTarget != (Qubit) -1) {
                success = true;
                const Edge<mNode> xConjugate = conjugateTranspose(x);
                return applyPhaseGate2(x, xConjugate, y, phaseTarget, false);
            }
            return y;
        }

        vEdge applyControlledPauliGate(const Edge<mNode>& x, const vEdge& y, bool& success) {
            success = false;
            if (!usingSpecialCliffordCaching(cachingStrategy)) {
                //Log::log << "[applyControlledPauliGate] not using Clifford caching. Exit.\n";
                return y;
            }
            CliffordGate gate = isControlledPauliGate(x);
            //Log::log << "[CPauli] controlled Pauli gate is " << (char) gate.gateType << ", control = " << (int) gate.control.qubit << " target = " << (int) gate.target << '\n';
            if (gate.gateType != cliffNoGate) {
                success = true;
                /// Our implementation can apply only positive-controlled gates. Nevertheless, when 'gate' is a negative-controlled gate, then we can still apply this gate, by applying also two X gates.
                ///   specifically, to achieve this we apply X * positive-gate * X
                if (gate.control.type == Control::Type::neg) {
                    /// Prepare the positive-controlled gate
                    CliffordGate positiveControlledGate  = gate;
                    positiveControlledGate.control.type  = Control::Type::pos;
                    /// By convention, we always say that controlled Z gates are downward-controlled (we have this option, since they are symmetric)
                    if (positiveControlledGate.gateType == cliffpauli_z && gate.control.qubit < gate.target) {
                        positiveControlledGate.target        = gate.control.qubit;
                        positiveControlledGate.control.qubit = gate.target;
                    }
                    /// Prepare the X gate
                    CliffordGate xGate = CliffordGate(cliffpauli_x, Control{-1, Control::Type::pos}, gate.control.qubit);
                    /// Prepare the DD of the new, positive-controlled gate
                    GateMatrix  gatematrix               = positiveControlledGate.getGateMatrix();
                    Controls controls = {positiveControlledGate.control};
                    Edge<mNode> positiveControlledGateDD = makeGateDD(gatematrix, qubits(), controls, positiveControlledGate.target);
                    /// Apply the gates
                    vEdge result = applySpecificPauliGate(y, xGate);
                    result = applyControlledPauliGate2(positiveControlledGateDD, result, positiveControlledGate);
                    result = applySpecificPauliGate(result, xGate);
                    return result;
                } else {
                    return applyControlledPauliGate2(x, y, gate);
                }
            }
            return y;
        }

        vEdge applyProjection(const Edge<mNode>& x, const vEdge& y, bool& success) {
            success = false;
            if (!usingSpecialCliffordCaching(cachingStrategy)) {
                return y;
            }
            std::pair<Qubit, bool> projection = isProjectionOperator(x);
            //Log::log << "[apply projection] projection is " << (int) projection.first << " onto |" << (int)projection.second << ">.\n";
            if (projection.first != (Qubit)-1) {
                success = true;
                return applyProjection2(x, y, projection);
            }
            return y;
        }

        vEdge applyIdentityGate(const Edge<mNode>& x, const vEdge& y, bool& success) {
            success = false;
            if (!usingSpecialCliffordCaching(cachingStrategy)) {
                return y;
            }
            bool isIdentity = x.p->isIdentity();
            if (isIdentity) {
                //Log::log << "[apply identity] gate is identity.\n";
                success = true;
                return y;
            } else {
                //Log::log << "[apply identity] gate is not identity.\n";
            }
            return y;
        }

        // returns the vEdge equal to:   x.w * y.w * pushedLim * cachedResult
        // puts the new LIM in the LimTable
        vEdge processCachedEdge(const Edge <mNode> &x, const vEdge &y, const LimEntry<> &pushedLim, vCachedEdge cachedResult) {
            if (cachedResult.w.approximatelyZero()) {
                return vEdge::zero;
            }
            vEdge result = vEdge{cachedResult.p, cn.getCached(cachedResult.w), cachedResult.l};
            ComplexNumbers::mul(result.w, result.w, x.w); // TODO is this necessary? or is x.w always == 1?
            ComplexNumbers::mul(result.w, result.w, y.w);
            if (result.w.approximatelyZero()) {
                cn.returnToCache(result.w);
                return vEdge::zero;
            }
            LimEntry<> eLim = pushedLim;
            eLim.multiplyBy(result.l);
            result.l = lf.limTable.lookup(eLim);
            return result;
        }

        // returns an edge equal to:  x.w * y.w * lim * {e0, e1}
        // puts the tuple (x, y, {e0, e1}) in the computeTable
        // TODO refactor so that x and y are passed as pointers to nodes, not edges
        //    includes: refactor so that multiplying by weights x.w, y.w is not necessary
        vEdge makeNodeAndInsertCache(const Edge <mNode> &x, const vEdge &y, const LimEntry<> &pushedLim, vEdge &e0, vEdge &e1, CliffordGate gate = CliffordGate::cliffordGateNone()) {
            movePhaseIntoWeight(e0.l, e0.w);
            movePhaseIntoWeight(e1.l, e1.w);
            std::array<vEdge, 2> edges = {e0, e1};
            vEdge result = makeDDNode(y.p->v, edges, true, nullptr, y, gate); // TODO where is result.l? in the table? shouldn't we then dereference it?
            /// put the result in the cache
            auto& computeTable = getMultiplicationComputeTable<mNode, vNode>();
            result.l = lf.limTable.lookup(*result.l);
            computeTable.insert({x.p, Complex::one, nullptr}, {y.p, Complex::one, nullptr}, {result.p, result.w, result.l});
            if (result.w.approximatelyZero()) {
                //Log::log << "[makeNodeAndCache] result is zero.\n";
                return vEdge::zero;
            }
            /// multiply by the old LIM
            LimEntry<> resultLim = pushedLim;
            resultLim.multiplyBy(result.l);
            result.w = cn.getCachedIfNonzero(result.w); // TODO is this necessary? or is this Complex value already a cached value?
            movePhaseIntoWeight(resultLim, result.w);
            result.l = lf.limTable.lookup(resultLim);
            //Log::log << "[makeNodeAndCache] corrected LIM; result = " << result << '\n';
            /// Multiply by the weights of x and y
            ComplexNumbers::mul(result.w, result.w, x.w); // TODO is this necessary? or is the weight always 1?
            ComplexNumbers::mul(result.w, result.w, y.w);
            if (result.w.approximatelyZero()) {
                cn.returnToCache(result.w);
                return vEdge::zero;
            }
            //Log::log << "[makeNodeAndCache] corrected weight; result = " << result << " with vector " << outputCVec(getVector(result)) << '\n';
            return result;
        }

        unsigned int applyHadamardCallCount = 0;
        /// note that when we look up the computation in the ComputeTable, we use a nullptr for y's lim, i.e., the identity LIM. That is, we apply the phase gate directly to the node, rather than to the edge
        ///   We can do this because we exploit the algebraic property that the projection operator can be pushed through a Pauli LIM,
        ///   since Proj(x) Z = Z Proj(x), and Proj(b) X = X Proj(1-b)
        vEdge applyHadamardGate2(const Edge<mNode>& x, const vEdge y, Qubit hadamardTarget) {
            startProfile(applyHadamard)
            if (y.isTerminal()) return y;
            //Log::log << "[Hadamard, " << (int)y.p->v << " qubits] Start. target is " << (int) hadamardTarget << ". y = " << y << "\n";
            LimEntry<> pushedLim(y.l);
            conjugateWithHadamard(pushedLim, hadamardTarget);
            /// look up in the cache
            auto cachedResult = matrixVectorMultiplication.lookup({x.p, Complex::one, nullptr}, {y.p, Complex::one, nullptr}, false);
            if (cachedResult.p != nullptr) {
                //Log::log << "[Hadamard] cache hit!\n";
                return processCachedEdge(x, y, pushedLim, cachedResult);
            }
            /// cache miss; now simply compute the result
            //Log::log << "[Hadamard] cache miss.\n";
            vEdge e0, e1;
            if (hadamardTarget == y.p->v) {
                vEdge e00 = y.p->e[0];
                vEdge e01 = y.p->e[1];
                vEdge e10 = y.p->e[0];
                vEdge e11 = y.p->e[1];
                e00.w = cn.getCachedIfNonzero(e00.w);
                e01.w = cn.getCachedIfNonzero(e01.w);
                e10.w = cn.getCachedIfNonzero(e10.w);
                e11.w = cn.getCachedIfNonzero(e11.w);
                e11.w.multiplyByMinusOne(true);
                //Log::log << "[Hadamard] e10 = " << e10 << '\n';
                //Log::log << "[Hadamard] e11 = " << e11 << '\n';
                e0 = add2(e00, e01);
                e1 = add2(e10, e11);
            } else {
                /// Apply identity to this qubit, then apply Hadamard to the remaining qubits
                //Log::log << "[Hadamard, n=" << (int) y.p->v << "] recursing on e0.\n";
                e0 = applyHadamardGate2(x.p->e[0], y.p->e[0], hadamardTarget);
                //Log::log << "[Hadamard, n=" << (int) y.p->v << "] recursing on e1.\n";
                e1 = applyHadamardGate2(x.p->e[0], y.p->e[1], hadamardTarget);
            }
            e0.w = cn.getCachedIfNonzero(e0.w);
            e1.w = cn.getCachedIfNonzero(e1.w);
            CliffordGate hadamardGate(cliffHadamard, Control::noControl(), hadamardTarget);
            return makeNodeAndInsertCache(x, y, pushedLim, e0, e1, hadamardGate); // TODO add 'gate' parameter to enable smart stab construction
        }

        unsigned int applyPhaseCallCount = 0;
        /// note that when we look up the computation in the ComputeTable, we use a nullptr for y's lim, i.e., the identity LIM. That is, we apply the phase gate directly to the node, rather than to the edge
        /// We can do this because we exploit the algebraic property that the Phase gate can be pushed through a Pauli LIM
        vEdge applyPhaseGate2(const Edge<mNode>& phaseGateDD, const Edge<mNode> phaseInverseGateDD, const vEdge y, Qubit phaseTarget, bool inverse) {
            startProfile(applyPhase)
            if (y.isTerminal()) return y;
            //Log::log << "[Phase, n=" << (int)y.p->v << ", t=" << (int) phaseTarget << "] Start. y = " << y << "; inverse = " << inverse << '\n';
            LimEntry<> pushedLim(y.l);
            conjugateWithPhaseGate(pushedLim, phaseTarget, inverse);
            Edge<mNode> xApply = inverse? phaseInverseGateDD : phaseGateDD; // 'xApply' is the gate that we will now apply to y
            auto cachedResult = matrixVectorMultiplication.lookup({xApply.p, Complex::one, nullptr}, {y.p, Complex::one, nullptr}, false);
            if (cachedResult.p != nullptr) {
                //Log::log << "[Phase] cache hit!\n";
                return processCachedEdge(xApply, y, pushedLim, cachedResult);
            }
            /// cache miss; now simply compute the result
            vEdge e0, e1;
            if (phaseTarget == y.p->v) {
                e0   = y.p->e[0];
                e1   = y.p->e[1];
                //Log::log << "[Phase] inverse = " << inverse << ". applying S gate to qubit " << (int) y.p->v << ". e1 = "  << e1 << '\n';
                if (inverse) {
                    e1.w.multiplyByMinusi(false);
                }
                else {
                    e1.w.multiplyByi(false);
                }
                //Log::log << "[Phase] after multiplication, e1 = " << e1 << '\n';
            } else { /// Apply identity to this qubit, then apply Hadamard to the remaining qubits
                //Log::log << "[Phase] apply identity to qubit " << (int) y.p->v << '\n';
                e0 = applyPhaseGate2(phaseGateDD.p->e[0], phaseInverseGateDD.p->e[0], y.p->e[0], phaseTarget, inverse);
                e1 = applyPhaseGate2(phaseGateDD.p->e[0], phaseInverseGateDD.p->e[0], y.p->e[1], phaseTarget, inverse);
            }
            e0.w = cn.getCachedIfNonzero(e0.w);
            e1.w = cn.getCachedIfNonzero(e1.w);
            CliffordGate appliedGate(inverse ? cliffPhaseInv : cliffPhase, Control::noControl(), phaseTarget);
            return makeNodeAndInsertCache(xApply, y, pushedLim, e0, e1, appliedGate);
        }

        unsigned int applyControlledPauliCallCount = 0;
        /// note that when we look up the computation in the ComputeTable, we use a nullptr for y's lim, i.e., the identity LIM. That is, we apply the phase gate directly to the node, rather than to the edge
        /// We can do this because we exploit the algebraic property that the controlled Pauli gate can be pushed through a Pauli LIM
        vEdge applyControlledPauliGate2(const Edge<mNode>& x, const vEdge y, CliffordGate gate) {
            startProfile(applyControlledPauli)
            [[maybe_unused]] unsigned int callIndex = applyControlledPauliCallCount;
            //Log::log << "[CPauli #" << callIndex << ", n=" << (int)y.p->v << ", gate=" << gate << "] Start. mat has " << (int)x.p->v << " qubits. y = " << y << '\n';
            //Log::log << "[CPauli #" << callIndex << ", n=" << (int)y.p->v << "] y   = " << outputCVec(getVector(y)) << "\n";
            //Log::log << "[CPauli #" << callIndex << ", n=" << (int)y.p->v << "] y.p = " << outputCVec(getVector(y.p)) << "\n";
#if !NDEBUG
            CMat mat_x;
            CVec vec_y, vecExpected;

            mat_x       = getMatrix(x);
            vec_y       = getVector(y, y.p->v);
            vecExpected = multiplyMatrixVector(mat_x, vec_y);
#endif
            if (y.isTerminal()) return y;
            LimEntry<> pushedLim(y.l);
            conjugateWithControlledPauliGate(pushedLim, gate);
            auto cachedResult = matrixVectorMultiplication.lookup({x.p, Complex::one, nullptr}, {y.p, Complex::one, nullptr}, false);
            if (cachedResult.p != nullptr) {
                vEdge result = processCachedEdge(x, y, pushedLim, cachedResult);
#if !NDEBUG
                //Log::log << "[CPauli #" << callIndex << "] cache hit!\n";
                // Last step: sanity check to see whether the resulting vector is what was expected
                CVec vecResult;
                vecResult = getVector(result);
                if (!vectorsApproximatelyEqual(vecResult, vecExpected)) {
                    Log::log << "[CPauli #" << callIndex << "] ERROR. Computed DD result vector is different from expected result vector.\n"
                             << "[CPauli] input edge: y=" << y << "\n"
                             << "[CPauli] input amplitude vector: " << outputCVec(vecResult);
                    Log::log << "\n[CPauli] Matrix:\n";
                    printMatrix(x);
                    Log::log << "\n[CPauli #" << callIndex << "] Expected result: ";
                    printCVec(vecExpected);
                    Log::log << "\n[CPauli #" << callIndex << "] Actual result:  ";
                    printCVec(vecResult);
                    //throw std::runtime_error("[CPauli] ERROR  multiply does not return expected result.\n");
                }
#endif
                return result;
            }
            /// cache miss; now simply compute the result
            //Log::log << "[CPauli #" << callIndex << "] cache miss.\n";
            vEdge e[2];
            if (gate.control.qubit == y.p->v) {  ///  this qubit is the control, and the target qubit is below
                //Log::log << "[CPauli #" << callIndex << ", n=" << (int)y.p->v << "] applying Pauli " << (char)gate.gateType << " to qubit " << (int)gate.target << " from control qubit " << (int)gate.control.qubit << " with type " << (int)gate.control.type << ".\n";
                CliffordGate pauliGate(gate.gateType, Control::noControl(), gate.target);
                e[  (int)gate.control.type] = applySpecificPauliGate(y.p->e[(int)gate.control.type], pauliGate);
                e[1^(int)gate.control.type] = y.p->e[1^(int)gate.control.type];
                //Log::log << "[CPauli #" << callIndex << "] e[0] = " << outputCVec(getVector(e[0])) << "\n";
                //Log::log << "[CPauli #" << callIndex << "] e[1] = " << outputCVec(getVector(e[1])) << "\n";
            } else if (gate.target == y.p->v) {  ///  this qubit is the target, and the control qubit is below (has lower index); this case is slightly trickier
                if (gate.gateType == cliffpauli_x || gate.gateType == cliffpauli_y) {
                    vEdge f[2][2];
#if !NDEBUG
                    CVec vec[2][2];
#endif
                    auto project0 = makeGateDD(project0mat, y.p->v, gate.control.qubit);
                    auto project1 = makeGateDD(project1mat, y.p->v, gate.control.qubit);
                    std::pair<Qubit, bool> projectGate[2] = {{gate.control.qubit, gate.control.type == Control::Type::pos ? 0 : 1},
                                                             {gate.control.qubit, gate.control.type == Control::Type::pos ? 1 : 0}};
                    CVec yi;
                    for (int i=0; i<2; i++) for (int j=0; j<2; j++) {
#if !NDEBUG
                        yi = getVector(y.p->e[i]);
                        Log::log << "[CPauli #" << callIndex << "] computing projection onto " << j << " of edge y[" << i << "] = " << outputCVec(yi) << "\n";
#endif
                        f[i][j] = applyProjection2(project0, project1, y.p->e[i], projectGate[j]);
                        f[i][j].w = cn.getCachedIfNonzero(f[i][j].w);
#if !NDEBUG
                        vec[i][j] = getVector(f[i][j]);
                        Log::log << "[CPauli #" << callIndex << ", n=" << (int)y.p->v << ", c=" << (int) gate.control.qubit << ", t=" << (int) gate.target << " op=" <<(char) gate.gateType << "] f[" << i << "][" << j << "] = " << outputCVec(vec[i][j]) << '\n';
#endif
                    }
                    if (gate.gateType == cliffpauli_y) {
                        if (!f[0][1].w.exactlyZero())
                            f[0][1].w.multiplyByi();
                        if (!f[1][1].w.exactlyZero())
                            f[1][1].w.multiplyByMinusi();
                    }
                    e[0] = add2(f[0][0], f[1][1]);
                    e[1] = add2(f[0][1], f[1][0]);
                }
            } else {
                /// Apply identity to this qubit, then apply the controlled Pauli gate to the remaining qubits
                //Log::log << "[CPauli #" << callIndex << "] top qubit is Id; recursing on 0-child.\n";
                e[0] = applyControlledPauliGate2(x.p->e[0], y.p->e[0], gate);
                //Log::log << "[CPauli #" << callIndex << "] Found 0-child: e[0] = " << outputCVec(getVector(e[0])) << ". Recursing on 1-child.\n";
                e[1] = applyControlledPauliGate2(x.p->e[0], y.p->e[1], gate);
                //Log::log << "[CPauli #" << callIndex << "] e[1] = " << outputCVec(getVector(e[1])) << "\n";
            }
            e[0].w = cn.getCachedIfNonzero(e[0].w);
            e[1].w = cn.getCachedIfNonzero(e[1].w);
            vEdge result = makeNodeAndInsertCache(x, y, pushedLim, e[0], e[1], gate);
#if !NDEBUG
            // Last step: sanity check to see whether the resulting vector is what was expected
            CVec vecResult;
            vecResult = getVector(result);
            if (!vectorsApproximatelyEqual(vecResult, vecExpected)) {
                Log::log << "[CPauli #" << callIndex << "] ERROR. Computed DD result vector is different from expected result vector.\n"
                         << "[CPauli] input edge: y=" << y << "\n"
                         << "[CPauli] input amplitude vector: " << outputCVec(vecResult);
                Log::log << "\n[CPauli] Matrix:\n";
                printMatrix(x);
                Log::log << "\n[CPauli #" << callIndex << "] Expected result: ";
                printCVec(vecExpected);
                Log::log << "\n[CPauli #" << callIndex << "] Actual result:  ";
                printCVec(vecResult);
                //throw std::runtime_error("[CPauli] ERROR  multiply does not return expected result.\n");
            }
#endif
            return result;
        }

        // TODO refactor so that multiplying by weight is not necessary
        // TODO refactor so that a pointer to a projectionDD node is passed, not edge
        // TODO refactor so that an array of mNode[2] is passed, instead of 2 parameters
        // Applies a projection, multiplied by the weight on proj[x], where x = gate.second ^ (pushedLim[target] is antidiagonal)
        /// note that when we look it up, we use a nullptr for y's lim, i.e., the identity LIM. That is, we apply the phase gate directly to the node, rather than to the edge
        /// We can do this because we exploit the algebraic property that the projection operator can be pushed through a Pauli LIM, as Proj(b) X = X Proj(1-b), and Proj(b) Z = Z Proj(b)
        unsigned int applyProjectionCallCount = 0;
        vEdge applyProjection2(const Edge<mNode>& proj0, const Edge<mNode>& proj1, const vEdge y, std::pair<Qubit, bool> gate) {
            startProfile(applyProjection)
            //Log::log << "[Apply projection, n=" << (int)y.p->v << "] Start." << '\n';
            if (y.isTerminal()) return y;
            std::pair<Qubit, bool> gateApplied = gate;
            LimEntry<> pushedLim(y.l);
            Qubit targetQubit  = gateApplied.first;
            gateApplied.second ^= pushedLim.getQubit(targetQubit) == pauli_x || pushedLim.getQubit(targetQubit) == pauli_y;
            bool projection = gateApplied.second;
            Edge<mNode> projections[2] = {proj0, proj1};
            auto cachedResult = matrixVectorMultiplication.lookup({projections[projection].p, Complex::one, nullptr}, {y.p, Complex::one, nullptr}, false);
            if (cachedResult.p != nullptr) {
                return processCachedEdge(projections[projection], y, pushedLim, cachedResult);
                //Log::log << "[Apply projection onto " << projection << ", n=" << (int) y.p->v << "] cache hit!\n";
                //vEdge result =  processCachedEdge(projections[projection], y, pushedLim, cachedResult);
                //CVec resultvec = getVector(result);
                //Log::log << "[Apply projection onto " << projection << ", n=" << (int) y.p->v << "] result = " << result << "\n"
                //        << " result = " << outputCVec(resultvec) << "\n";
                //return result;
            }
            /// cache miss; now simply compute the result
            //Log::log << "[Apply projection onto " << projection << ", n=" << (int) y.p->v << "] cache miss.\n";
            vEdge e[2];
            if (targetQubit == y.p->v) {
                e[projection] = y.p->e[projection];
                e[1-projection] = vEdge::zero;
                e[projection].w = cn.getCachedIfNonzero(e[projection].w);
            } else {
                /// Recurse by applying identity to this qubit, then apply projection to the remaining qubits
                //Log::log << "[Apply projection] apply identity to qubit " << (int) y.p->v << '\n';
                for (int i=0; i<2; i++) {
                    e[i] = applyProjection2(proj0.p->e[0], proj1.p->e[0], y.p->e[i], gateApplied);
                    e[i].w = cn.getCachedIfNonzero(e[i].w);
                }
            }
            // TODO add 'gateApplied' parameter to enable smart stab construction
            // TODO or should we add 'gate' parameter??
            return makeNodeAndInsertCache(projections[projection], y, pushedLim, e[0], e[1]);
        }

        vEdge simulateCircuit(const QuantumCircuit& circuit) {
            auto state = makeZeroState(circuit.n);
            for (unsigned int gate = 0; gate < circuit.gates.size(); gate++) {
                state = applyGate(circuit.gates[gate], state);
            }
            return state;
        }

        ///
        /// Inner product and fidelity
        ///
    public:
        ComputeTable<vEdge, vEdge, vCachedEdge, CT_VEC_INNER_PROD_NBUCKET> vectorInnerProduct{};

        ComplexValue innerProduct(const vEdge& x, const vEdge& y) {
            if (x.p == nullptr || y.p == nullptr || x.w.approximatelyZero() || y.w.approximatelyZero()) { // the 0 case
                return {0, 0};
            }

            [[maybe_unused]] const auto before = cn.cacheCount();

            auto w = x.p->v;
            if (y.p->v > w) {
                w = y.p->v;
            }
            const ComplexValue ip = innerProduct(x, y, static_cast<Qubit>(w + 1));

            [[maybe_unused]] const auto after = cn.cacheCount();
            assert(after == before);

            return ip;
        }
        fp fidelity(const vEdge& x, const vEdge& y) {
            // TODO limdd
            const auto fid = innerProduct(x, y);
            return fid.r * fid.r + fid.i * fid.i;
        }

        dd::fp fidelityOfMeasurementOutcomes(const vEdge& e, const ProbabilityVector& probs) {
            if (e.w.approximatelyZero()) {
                return 0.;
            }
            return fidelityOfMeasurementOutcomesRecursive(e, probs, 0);
        }

        dd::fp fidelityOfMeasurementOutcomesRecursive(const vEdge& e, const ProbabilityVector& probs, const std::size_t i) {
            const auto topw = dd::ComplexNumbers::mag(e.w);
            if (e.isTerminal()) {
                if (auto it = probs.find(i); it != probs.end()) {
                    return topw * std::sqrt(it->second);
                } else {
                    return 0.;
                }
            }

            std::size_t leftIdx          = i;
            dd::fp      leftContribution = 0.;
            if (!e.p->e[0].w.approximatelyZero()) {
                leftContribution = fidelityOfMeasurementOutcomesRecursive(e.p->e[0], probs, leftIdx);
            }

            std::size_t rightIdx          = i | (1ULL << e.p->v);
            auto        rightContribution = 0.;
            if (!e.p->e[1].w.approximatelyZero()) {
                rightContribution = fidelityOfMeasurementOutcomesRecursive(e.p->e[1], probs, rightIdx);
            }

            dd::fp fidelity = topw * (leftContribution + rightContribution);
            return fidelity;
        }

    private:
        ComplexValue innerProduct(const vEdge& x, const vEdge& y, Qubit var) {
            if (x.p == nullptr || y.p == nullptr || x.w.approximatelyZero() || y.w.approximatelyZero()) { // the 0 case
                return {0.0, 0.0};
            }

            if (var == 0) {
                auto c = cn.getTemporary();
                ComplexNumbers::mul(c, x.w, y.w);
                return {c.r->value, c.i->value};
            }

            auto xCopy = x;
            xCopy.w    = Complex::one;
            auto yCopy = y;
            yCopy.w    = Complex::one;

            auto r = vectorInnerProduct.lookup(xCopy, yCopy);
            if (r.p != nullptr) {
                auto c = cn.getTemporary(r.w);
                ComplexNumbers::mul(c, c, x.w);
                ComplexNumbers::mul(c, c, y.w);
                return {CTEntry::val(c.r), CTEntry::val(c.i)};
            }

            auto w = static_cast<Qubit>(var - 1);

            ComplexValue sum{0.0, 0.0};
            for (auto i = 0U; i < RADIX; i++) {
                vEdge e1{};
                if (!x.isTerminal() && x.p->v == w) {
                    e1 = x.p->e[i];
                } else {
                    e1 = xCopy;
                }
                vEdge e2{};
                if (!y.isTerminal() && y.p->v == w) {
                    e2   = y.p->e[i];
                    e2.w = ComplexNumbers::conj(e2.w);
                } else {
                    e2 = yCopy;
                }
                auto cv = innerProduct(e1, e2, w);
                sum.r += cv.r;
                sum.i += cv.i;
            }
            r.p = vNode::terminal;
            r.w = sum;

            vectorInnerProduct.insert(xCopy, yCopy, r);
            auto c = cn.getTemporary(sum);
            ComplexNumbers::mul(c, c, x.w);
            ComplexNumbers::mul(c, c, y.w);
            return {CTEntry::val(c.r), CTEntry::val(c.i)};
        }

        ///
        /// Kronecker/tensor product
        ///
    public:
        ComputeTable<vEdge, vEdge, vCachedEdge, CT_VEC_KRON_NBUCKET> vectorKronecker{};
        ComputeTable<mEdge, mEdge, mCachedEdge, CT_MAT_KRON_NBUCKET> matrixKronecker{};

        template<class Node>
        [[nodiscard]] auto& getKroneckerComputeTable() {
            if constexpr (std::is_same_v<Node, vNode>) {
                return vectorKronecker;
            } else {
                return matrixKronecker;
            }
        }

        template<class Edge>
        Edge kronecker(const Edge& x, const Edge& y, bool incIdx = true) {
            if constexpr (std::is_same_v<Edge, dEdge>) {
                throw std::invalid_argument("Kronecker is currently not supported for density matrices");
            }

            auto e = kronecker2(x, y, incIdx);

            if (e.w != Complex::zero && !e.w.exactlyOne()) {
                cn.returnToCache(e.w);
                e.w = cn.lookup(e.w);
            }

            return e;
        }

        // extent the DD pointed to by `e` with `h` identities on top and `l` identities at the bottom
        mEdge extend(const mEdge& e, Qubit h, Qubit l = 0) {
            auto f = (l > 0) ? kronecker(e, makeIdent(l)) : e;
            auto g = (h > 0) ? kronecker(makeIdent(h), f) : f;
            return g;
        }

    private:
        template<class Node>
        Edge<Node> kronecker2(const Edge<Node>& x, const Edge<Node>& y, bool incIdx = true) {
            if (x.w.approximatelyZero() || y.w.approximatelyZero())
                return Edge<Node>::zero;

            if (x.isTerminal()) {
                auto r = y;
                r.w    = cn.mulCached(x.w, y.w);
                return r;
            }

            auto& computeTable = getKroneckerComputeTable<Node>();
            auto  r            = computeTable.lookup(x, y);
            if (r.p != nullptr) {
                if (r.w.approximatelyZero()) {
                    return Edge<Node>::zero;
                } else {
                    return {r.p, cn.getCached(r.w), nullptr};
                }
            }

            constexpr std::size_t N = std::tuple_size_v<decltype(x.p->e)>;
            // special case handling for matrices
            if constexpr (N == NEDGE) {
                if (x.p->isIdentity()) {
                    auto idx = incIdx ? static_cast<Qubit>(y.p->v + 1) : y.p->v;
                    auto e   = makeDDNode(idx, std::array{y, Edge<Node>::zero, Edge<Node>::zero, y});
                    for (auto i = 0; i < x.p->v; ++i) {
                        idx = incIdx ? static_cast<Qubit>(e.p->v + 1) : e.p->v;
                        e   = makeDDNode(idx, std::array{e, Edge<Node>::zero, Edge<Node>::zero, e});
                    }

                    e.w = cn.getCached(CTEntry::val(y.w.r), CTEntry::val(y.w.i));
                    computeTable.insert(x, y, {e.p, e.w, e.l});
                    return e;
                }
            }

            std::array<Edge<Node>, N> edge{};
            for (auto i = 0U; i < N; ++i) {
                edge[i] = kronecker2(x.p->e[i], y, incIdx);
            }

            auto idx = incIdx ? static_cast<Qubit>(y.p->v + x.p->v + 1) : x.p->v;
            auto e   = makeDDNode(idx, edge, true);
            ComplexNumbers::mul(e.w, e.w, x.w);
            computeTable.insert(x, y, {e.p, e.w, e.l});
            return e;
        }

        ///
        /// (Partial) trace
        ///
    public:
        mEdge partialTrace(const mEdge& a, const std::vector<bool>& eliminate) {
            [[maybe_unused]] const auto before = cn.cacheCount();
            const auto                  result = trace(a, eliminate);
            [[maybe_unused]] const auto after  = cn.cacheCount();
            assert(before == after);
            return result;
        }
        ComplexValue trace(const mEdge& a) {
            auto                        eliminate = std::vector<bool>(nqubits, true);
            [[maybe_unused]] const auto before    = cn.cacheCount();
            const auto                  res       = partialTrace(a, eliminate);
            [[maybe_unused]] const auto after     = cn.cacheCount();
            assert(before == after);
            return {CTEntry::val(res.w.r), CTEntry::val(res.w.i)};
        }
        bool isCloseToIdentity(const mEdge& m, dd::fp tol = 1e-10) {
            std::unordered_set<decltype(m.p)> visited{};
            visited.reserve(mUniqueTable.getActiveNodeCount());
            return isCloseToIdentityRecursive(m, visited, tol);
        }

    private:
        /// TODO: introduce a compute table for the trace?
        mEdge trace(const mEdge& a, const std::vector<bool>& eliminate, std::size_t alreadyEliminated = 0) {
            auto v = a.p->v;

            if (a.w.approximatelyZero()) return mEdge::zero;

            if (std::none_of(eliminate.begin(), eliminate.end(), [](bool v) { return v; })) return a;

            // Base case
            if (v == -1) {
                if (a.isTerminal()) return a;
                throw std::runtime_error("Expected terminal node in trace.");
            }

            if (eliminate[v]) {
                auto elims = alreadyEliminated + 1;
                auto r     = mEdge::zero;

                auto t0 = trace(a.p->e[0], eliminate, elims);
                r       = add2(r, t0);
                auto r1 = r;

                auto t1 = trace(a.p->e[3], eliminate, elims);
                r       = add2(r, t1);
                auto r2 = r;

                if (r.w.exactlyOne()) {
                    r.w = a.w;
                } else {
                    auto c = cn.getTemporary();
                    ComplexNumbers::mul(c, r.w, a.w);
                    r.w = cn.lookup(c); // better safe than sorry. this may result in complex values with magnitude > 1 in the complex table
                }

                if (r1.w != Complex::zero) {
                    cn.returnToCache(r1.w);
                }

                if (r2.w != Complex::zero) {
                    cn.returnToCache(r2.w);
                }

                return r;
            } else {
                auto                     adjustedV = static_cast<Qubit>(a.p->v - (std::count(eliminate.begin(), eliminate.end(), true) - alreadyEliminated));
                std::array<mEdge, NEDGE> edge{};
                std::transform(a.p->e.cbegin(),
                               a.p->e.cend(),
                               edge.begin(),
                               [&](const mEdge& e) -> mEdge { return trace(e, eliminate, alreadyEliminated); });
                auto r = makeDDNode(adjustedV, edge);

                if (r.w.exactlyOne()) {
                    r.w = a.w;
                } else {
                    auto c = cn.getTemporary();
                    ComplexNumbers::mul(c, r.w, a.w);
                    r.w = cn.lookup(c);
                }
                return r;
            }
        }

        bool isCloseToIdentityRecursive(const mEdge& m, std::unordered_set<decltype(m.p)>& visited, dd::fp tol) {
            // immediately return if this node has already been visited
            if (visited.find(m.p) != visited.end()) {
                return true;
            }

            // immediately return of this node is identical to the identity
            if (m.p->isIdentity()) {
                return true;
            }

            // check whether any of the middle successors is non-zero, i.e., m = [ x 0 0 y ]
            const auto mag1 = dd::ComplexNumbers::mag2(m.p->e[1U].w);
            const auto mag2 = dd::ComplexNumbers::mag2(m.p->e[2U].w);
            if (mag1 > tol || mag2 > tol) {
                visited.insert(m.p);
                return false;
            }

            // check whether  m = [ ~1 0 0 y ]
            const auto mag0 = dd::ComplexNumbers::mag2(m.p->e[0U].w);
            if (std::abs(mag0 - 1.0) > tol) {
                visited.insert(m.p);
                return false;
            }
            const auto arg0 = dd::ComplexNumbers::arg(m.p->e[0U].w);
            if (std::abs(arg0) > tol) {
                visited.insert(m.p);
                return false;
            }

            // check whether m = [ x 0 0 ~1 ] or m = [ x 0 0 ~0 ] (the last case is true for an ancillary qubit)
            const auto mag3 = dd::ComplexNumbers::mag2(m.p->e[3U].w);
            if (mag3 > tol) {
                if (std::abs(mag3 - 1.0) > tol) {
                    visited.insert(m.p);
                    return false;
                }
                const auto arg3 = dd::ComplexNumbers::arg(m.p->e[3U].w);
                if (std::abs(arg3) > tol) {
                    visited.insert(m.p);
                    return false;
                }
            }

            // m either has the form [ ~1 0 0 ~1 ] or [ ~1 0 0 ~0 ]
            const auto ident0 = isCloseToIdentityRecursive(m.p->e[0U], visited, tol);
            if (!ident0) {
                visited.insert(m.p);
                return false;
            }

            // m either has the form [ I 0 0 ~1 ] or [ I 0 0 ~0 ]
            const auto ident3 = isCloseToIdentityRecursive(m.p->e[3U], visited, tol);
            visited.insert(m.p);
            return ident3;
        }

        ///
        /// Toffoli gates
        ///
    public:
        ToffoliTable<mEdge> toffoliTable{};

        ///
        /// Identity matrices
        ///
    public:
        // create n-qubit identity DD. makeIdent(n) === makeIdent(0, n-1)
        mEdge makeIdent(QubitCount n) {
            return makeIdent(0, static_cast<Qubit>(n - 1));
        }
        mEdge makeIdent(Qubit leastSignificantQubit, Qubit mostSignificantQubit) {
            if (mostSignificantQubit < leastSignificantQubit)
                return mEdge::one;

            if (leastSignificantQubit == 0 && IdTable[mostSignificantQubit].p != nullptr) {
                return IdTable[mostSignificantQubit];
            }
            if (mostSignificantQubit >= 1 && (IdTable[mostSignificantQubit - 1]).p != nullptr) {
                IdTable[mostSignificantQubit] = makeDDNode(mostSignificantQubit,
                                                           std::array{IdTable[mostSignificantQubit - 1],
                                                                      mEdge::zero,
                                                                      mEdge::zero,
                                                                      IdTable[mostSignificantQubit - 1]});
                return IdTable[mostSignificantQubit];
            }

            auto e = makeDDNode(leastSignificantQubit, std::array{mEdge::one, mEdge::zero, mEdge::zero, mEdge::one});
            for (std::size_t k = leastSignificantQubit + 1; k <= std::make_unsigned_t<Qubit>(mostSignificantQubit); k++) {
                e = makeDDNode(static_cast<Qubit>(k), std::array{e, mEdge::zero, mEdge::zero, e});
            }
            if (leastSignificantQubit == 0)
                IdTable[mostSignificantQubit] = e;
            return e;
        }

        // identity table access and reset
        [[nodiscard]] const auto& getIdentityTable() const {
            return IdTable;
        }

        void clearIdentityTable() {
            for (auto& entry: IdTable) entry.p = nullptr;
        }

        mEdge createInitialMatrix(dd::QubitCount n, const std::vector<bool>& ancillary) {
            auto e = makeIdent(n);
            incRef(e);
            return reduceAncillae(e, ancillary);
        }

    private:
        std::vector<mEdge> IdTable{};

        ///
        /// Noise Operations
        ///
    public:
        StochasticNoiseOperationTable<mEdge, STOCHASTIC_CACHE_OPS> stochasticNoiseOperationCache{nqubits};
        DensityNoiseTable<dEdge, dEdge, CT_DM_NOISE_NBUCKET>       densityNoise{};

        ///
        /// Decision diagram size
        ///
    public:
        template<class Edge>
        unsigned int size(const Edge& e) {
            static constexpr unsigned int            NODECOUNT_BUCKETS = 200000;
            static std::unordered_set<decltype(e.p)> visited{NODECOUNT_BUCKETS}; // 2e6
            visited.max_load_factor(10);
            visited.clear();
            return nodeCount(e, visited);
        }

    private:
        template<class Edge>
        unsigned int nodeCount(const Edge& e, std::unordered_set<decltype(e.p)>& v) const {
            auto eCopy = e;
            if constexpr (std::is_same_v<Edge, dEdge>) {
                dEdge::alignDensityEdge(eCopy);
            }
            v.insert(eCopy.p);
            unsigned int sum = 1;
            if (!eCopy.isTerminal()) {
                for (const auto& edge: eCopy.p->e) {
                    if (edge.p != nullptr && !v.count(edge.p)) {
                        sum += nodeCount(edge, v);
                    }
                }
            }
            return sum;
        }

    public:
        template<class Edge>
        size_t limCount(const Edge& e) const {
            std::unordered_set<std::size_t> uniqueLims  = {};
            std::unordered_set<std::size_t> uniqueNodes = {};
            limCount(e, uniqueLims, uniqueNodes);
            return uniqueLims.size();
        }

        template<class Edge>
        size_t numberCount(const Edge& e) const {
            std::unordered_set<std::size_t> uniqueNumbers = {};
            std::unordered_set<std::size_t> uniqueNodes   = {};
            numberCount(e, uniqueNumbers, uniqueNodes);
            return uniqueNumbers.size();
        }

    private:
        template<class Edge>
        void limCount(const Edge& e, std::unordered_set<std::size_t>& v, std::unordered_set<std::size_t>& nodes) const {
            auto eCopy = e;

            if constexpr (std::is_same_v<Edge, dEdge>) {
                dEdge::alignDensityEdge(eCopy);
            }

            v.insert((std::size_t)eCopy.l);
            for (const auto& lim: e.p->limVector) {
                v.insert((std::size_t)lim);
            }

            if (nodes.find((std::size_t)eCopy.p) != nodes.end()) {
                return;
            }
            nodes.insert((std::size_t)eCopy.p);

            if (!eCopy.isTerminal()) {
                for (const auto& edge: eCopy.p->e) {
                    limCount(edge, v, nodes);
                }
            }
        }

        template<class Edge>
        void numberCount(const Edge& e, std::unordered_set<std::size_t>& v, std::unordered_set<std::size_t>& nodes) const {
            auto eCopy = e;

            if constexpr (std::is_same_v<Edge, dEdge>) {
                dEdge::alignDensityEdge(eCopy);
            }

            v.insert((std::size_t)CTEntry::getAlignedPointer(e.w.r));
            v.insert((std::size_t)CTEntry::getAlignedPointer(e.w.i));

            if (nodes.find((std::size_t)eCopy.p) != nodes.end()) {
                return;
            }
            nodes.insert((std::size_t)eCopy.p);

            if (!eCopy.isTerminal()) {
                for (const auto& edge: eCopy.p->e) {
                    numberCount(edge, v, nodes);
                }
            }
        }

        ///
        /// Ancillary and garbage reduction
        ///
    public:
        mEdge reduceAncillae(mEdge& e, const std::vector<bool>& ancillary, bool regular = true) {
            // return if no more garbage left
            if (std::none_of(ancillary.begin(), ancillary.end(), [](bool v) { return v; }) || e.p == nullptr) return e;
            Qubit lowerbound = 0;
            for (auto i = 0U; i < ancillary.size(); ++i) {
                if (ancillary[i]) {
                    lowerbound = static_cast<Qubit>(i);
                    break;
                }
            }
            if (e.p->v < lowerbound) return e;
            auto f = reduceAncillaeRecursion(e, ancillary, lowerbound, regular);
            decRef(e);
            incRef(f);
            return f;
        }

        // Garbage reduction works for reversible circuits --- to be thoroughly tested for quantum circuits
        vEdge reduceGarbage(vEdge& e, const std::vector<bool>& garbage) {
            // return if no more garbage left
            if (std::none_of(garbage.begin(), garbage.end(), [](bool v) { return v; }) || e.p == nullptr) return e;
            Qubit lowerbound = 0;
            for (auto i = 0U; i < garbage.size(); ++i) {
                if (garbage[i]) {
                    lowerbound = static_cast<Qubit>(i);
                    break;
                }
            }
            if (e.p->v < lowerbound) return e;
            auto f = reduceGarbageRecursion(e, garbage, lowerbound);
            decRef(e);
            incRef(f);
            return f;
        }
        mEdge reduceGarbage(mEdge& e, const std::vector<bool>& garbage, bool regular = true) {
            // return if no more garbage left
            if (std::none_of(garbage.begin(), garbage.end(), [](bool v) { return v; }) || e.p == nullptr) return e;
            Qubit lowerbound = 0;
            for (auto i = 0U; i < garbage.size(); ++i) {
                if (garbage[i]) {
                    lowerbound = static_cast<Qubit>(i);
                    break;
                }
            }
            if (e.p->v < lowerbound) return e;
            auto f = reduceGarbageRecursion(e, garbage, lowerbound, regular);
            decRef(e);
            incRef(f);
            return f;
        }

    private:
        mEdge reduceAncillaeRecursion(mEdge& e, const std::vector<bool>& ancillary, Qubit lowerbound, bool regular = true) {
            if (e.p->v < lowerbound) return e;

            auto f = e;

            std::array<mEdge, NEDGE> edges{};
            std::bitset<NEDGE>       handled{};
            for (auto i = 0U; i < NEDGE; ++i) {
                if (!handled.test(i)) {
                    if (e.p->e[i].isTerminal()) {
                        edges[i] = e.p->e[i];
                    } else {
                        edges[i] = reduceAncillaeRecursion(f.p->e[i], ancillary, lowerbound, regular);
                        for (auto j = i + 1; j < NEDGE; ++j) {
                            if (e.p->e[i].p == e.p->e[j].p) {
                                edges[j] = edges[i];
                                handled.set(j);
                            }
                        }
                    }
                    handled.set(i);
                }
            }
            f = makeDDNode(f.p->v, edges);

            // something to reduce for this qubit
            if (f.p->v >= 0 && ancillary[f.p->v]) {
                if (regular) {
                    if (f.p->e[1].w != Complex::zero || f.p->e[3].w != Complex::zero) {
                        f = makeDDNode(f.p->v, std::array{f.p->e[0], mEdge::zero, f.p->e[2], mEdge::zero});
                    }
                } else {
                    if (f.p->e[2].w != Complex::zero || f.p->e[3].w != Complex::zero) {
                        f = makeDDNode(f.p->v, std::array{f.p->e[0], f.p->e[1], mEdge::zero, mEdge::zero});
                    }
                }
            }

            auto c = cn.mulCached(f.w, e.w);
            f.w    = cn.lookup(c);
            cn.returnToCache(c);
            return f;
        }

        vEdge reduceGarbageRecursion(vEdge& e, const std::vector<bool>& garbage, Qubit lowerbound) {
            if (e.p->v < lowerbound) return e;

            auto f = e;

            std::array<vEdge, RADIX> edges{};
            std::bitset<RADIX>       handled{};
            for (auto i = 0U; i < RADIX; ++i) {
                if (!handled.test(i)) {
                    if (e.p->e[i].isTerminal()) {
                        edges[i] = e.p->e[i];
                    } else {
                        edges[i] = reduceGarbageRecursion(f.p->e[i], garbage, lowerbound);
                        for (auto j = i + 1; j < RADIX; ++j) {
                            if (e.p->e[i].p == e.p->e[j].p) {
                                edges[j] = edges[i];
                                handled.set(j);
                            }
                        }
                    }
                    handled.set(i);
                }
            }
            f = makeDDNode(f.p->v, edges);

            // something to reduce for this qubit
            if (f.p->v >= 0 && garbage[f.p->v]) {
                if (f.p->e[1].w != Complex::zero) {
                    vEdge g{};
                    if (f.p->e[0].w == Complex::zero && f.p->e[1].w != Complex::zero) {
                        g = f.p->e[1];
                    } else if (f.p->e[1].w != Complex::zero) {
                        g = add(f.p->e[0], f.p->e[1]);
                    } else {
                        g = f.p->e[0];
                    }
                    f = makeDDNode(e.p->v, std::array{g, vEdge::zero});
                }
            }

            auto c = cn.mulCached(f.w, e.w);
            f.w    = cn.lookup(c);
            cn.returnToCache(c);

            // Quick-fix for normalization bug
            if (ComplexNumbers::mag2(f.w) > 1.0)
                f.w = Complex::one;

            return f;
        }
        mEdge reduceGarbageRecursion(mEdge& e, const std::vector<bool>& garbage, Qubit lowerbound, bool regular = true) {
            if (e.p->v < lowerbound) return e;

            auto f = e;

            std::array<mEdge, NEDGE> edges{};
            std::bitset<NEDGE>       handled{};
            for (auto i = 0U; i < NEDGE; ++i) {
                if (!handled.test(i)) {
                    if (e.p->e[i].isTerminal()) {
                        edges[i] = e.p->e[i];
                    } else {
                        edges[i] = reduceGarbageRecursion(f.p->e[i], garbage, lowerbound, regular);
                        for (auto j = i + 1; j < NEDGE; ++j) {
                            if (e.p->e[i].p == e.p->e[j].p) {
                                edges[j] = edges[i];
                                handled.set(j);
                            }
                        }
                    }
                    handled.set(i);
                }
            }
            f = makeDDNode(f.p->v, edges);

            // something to reduce for this qubit
            if (f.p->v >= 0 && garbage[f.p->v]) {
                if (regular) {
                    if (f.p->e[2].w != Complex::zero || f.p->e[3].w != Complex::zero) {
                        mEdge g{};
                        if (f.p->e[0].w == Complex::zero && f.p->e[2].w != Complex::zero) {
                            g = f.p->e[2];
                        } else if (f.p->e[2].w != Complex::zero) {
                            g = add(f.p->e[0], f.p->e[2]);
                        } else {
                            g = f.p->e[0];
                        }
                        mEdge h{};
                        if (f.p->e[1].w == Complex::zero && f.p->e[3].w != Complex::zero) {
                            h = f.p->e[3];
                        } else if (f.p->e[3].w != Complex::zero) {
                            h = add(f.p->e[1], f.p->e[3]);
                        } else {
                            h = f.p->e[1];
                        }
                        f = makeDDNode(e.p->v, std::array{g, h, mEdge::zero, mEdge::zero});
                    }
                } else {
                    if (f.p->e[1].w != Complex::zero || f.p->e[3].w != Complex::zero) {
                        mEdge g{};
                        if (f.p->e[0].w == Complex::zero && f.p->e[1].w != Complex::zero) {
                            g = f.p->e[1];
                        } else if (f.p->e[1].w != Complex::zero) {
                            g = add(f.p->e[0], f.p->e[1]);
                        } else {
                            g = f.p->e[0];
                        }
                        mEdge h{};
                        if (f.p->e[2].w == Complex::zero && f.p->e[3].w != Complex::zero) {
                            h = f.p->e[3];
                        } else if (f.p->e[3].w != Complex::zero) {
                            h = add(f.p->e[2], f.p->e[3]);
                        } else {
                            h = f.p->e[2];
                        }
                        f = makeDDNode(e.p->v, std::array{g, mEdge::zero, h, mEdge::zero});
                    }
                }
            }

            auto c = cn.mulCached(f.w, e.w);
            f.w    = cn.lookup(c);
            cn.returnToCache(c);

            // Quick-fix for normalization bug
            if (ComplexNumbers::mag2(f.w) > 1.0)
                f.w = Complex::one;

            return f;
        }

        ///
        /// Vector and matrix extraction from DDs
        ///
    public:
        /// Get a single element of the vector or matrix represented by the dd with root edge e
        /// \tparam Edge type of edge to use (vector or matrix)
        /// \param e edge to traverse
        /// \param elements string {0, 1, 2, 3}^n describing which outgoing edge should be followed
        ///        (for vectors entries are limited to 0 and 1)
        ///        If string is longer than required, the additional characters are ignored.
        /// \return the complex amplitude of the specified element
        template<class Edge>
        ComplexValue getValueByPath(const Edge& e, const std::string& elements) {
            // TODO limdd
            if (e.isTerminal()) {
                return {CTEntry::val(e.w.r), CTEntry::val(e.w.i)};
            }

            auto c = cn.getTemporary(1, 0);
            auto r = e;
            do {
                ComplexNumbers::mul(c, c, r.w);
                std::size_t tmp = elements.at(r.p->v) - '0';
                assert(tmp <= r.p->e.size());
                r = r.p->e.at(tmp);
            } while (!r.isTerminal());
            ComplexNumbers::mul(c, c, r.w);

            return {CTEntry::val(c.r), CTEntry::val(c.i)};
        }
        ComplexValue getValueByPath(const vEdge& e, std::size_t i) {
            if (e.isTerminal()) {
                return {CTEntry::val(e.w.r), CTEntry::val(e.w.i)};
            }
            return getValueByPath(e, Complex::one, i);
        }
        ComplexValue getValueByPath(const vEdge& e, const Complex& amp, std::size_t i) {
            auto c = cn.mulCached(e.w, amp);

            if (e.isTerminal()) {
                cn.returnToCache(c);
                return {CTEntry::val(c.r), CTEntry::val(c.i)};
            }

            const bool one = i & (1ULL << e.p->v);

            ComplexValue r{};
            if (!one && !e.p->e[0].w.approximatelyZero()) {
                r = getValueByPath(e.p->e[0], c, i);
            } else if (one && !e.p->e[1].w.approximatelyZero()) {
                r = getValueByPath(e.p->e[1], c, i);
            }
            cn.returnToCache(c);
            return r;
        }
        ComplexValue getValueByPath(const mEdge& e, std::size_t i, std::size_t j) {
            if (e.isTerminal()) {
                return {CTEntry::val(e.w.r), CTEntry::val(e.w.i)};
            }
            return getValueByPath(e, Complex::one, i, j);
        }
        ComplexValue getValueByPath(const mEdge& e, const Complex& amp, std::size_t i, std::size_t j) {
            auto c = cn.mulCached(e.w, amp);

            if (e.isTerminal()) {
                cn.returnToCache(c);
                return {CTEntry::val(c.r), CTEntry::val(c.i)};
            }

            const bool row = i & (1ULL << e.p->v);
            const bool col = j & (1ULL << e.p->v);

            ComplexValue r{};
            if (!row && !col && !e.p->e[0].w.approximatelyZero()) {
                r = getValueByPath(e.p->e[0], c, i, j);
            } else if (!row && col && !e.p->e[1].w.approximatelyZero()) {
                r = getValueByPath(e.p->e[1], c, i, j);
            } else if (row && !col && !e.p->e[2].w.approximatelyZero()) {
                r = getValueByPath(e.p->e[2], c, i, j);
            } else if (row && col && !e.p->e[3].w.approximatelyZero()) {
                r = getValueByPath(e.p->e[3], c, i, j);
            }
            cn.returnToCache(c);
            return r;
        }

        std::map<std::string, dd::fp> getProbVectorFromDensityMatrix(dEdge e, double measurementThreshold) {
            std::map<std::string, dd::fp> measuredResult = {};
            dd::fp                        p0, p1, globalProbability;
            dEdge::alignDensityEdge(e);
            if (std::pow(2, e.p->v + 1) >= static_cast<double>(std::numeric_limits<unsigned long long>::max())) {
                throw std::runtime_error(std::string{"Density matrix is too large to measure!"});
            }

            const unsigned long long statesToMeasure = 2ULL << e.p->v;

            for (unsigned long long m = 0; m < statesToMeasure; m++) {
                unsigned long long currentResult = m;
                globalProbability                = dd::CTEntry::val(e.w.r);
                auto  resultString               = intToString(m, '1', e.p->v + 1);
                dEdge cur                        = e;
                for (dd::Qubit i = 0; i < e.p->v + 1; ++i) {
                    if (cur.p->v != -1 && globalProbability > measurementThreshold) {
                        assert(dd::CTEntry::approximatelyZero(cur.p->e.at(0).w.i) && dd::CTEntry::approximatelyZero(cur.p->e.at(3).w.i));
                        p0 = dd::CTEntry::val(cur.p->e.at(0).w.r);
                        p1 = dd::CTEntry::val(cur.p->e.at(3).w.r);
                    } else {
                        globalProbability = 0;
                        break;
                    }

                    if (currentResult % 2 == 0) {
                        cur = cur.p->e.at(0);
                        globalProbability *= p0;
                    } else {
                        cur = cur.p->e.at(3);
                        globalProbability *= p1;
                    }
                    currentResult = currentResult >> 1;
                }
                if (globalProbability > 0) { // No need to track probabilities of 0
                    measuredResult.insert({resultString, globalProbability});
                }
            }
            return measuredResult;
        }

        [[nodiscard]] std::string intToString(unsigned long long targetNumber, char value, dd::Qubit size) const {
            std::string path(size, '0');
            for (auto i = 1; i <= size; i++) {
                if (targetNumber % 2) {
                    path[size - i] = value;
                }
                targetNumber = targetNumber >> 1u;
            }
            return path;
        }

        CVec getVector([[maybe_unused]] const mEdge& e, [[maybe_unused]] Qubit q = 0, [[maybe_unused]] LimEntry<> lim = {}) {
            CVec vec;
            return vec;
        }

        CVec getVector(const vEdge& e, LimEntry<> lim) {
            // TODO limdd
            std::size_t dim = 0;
            if (e.p->v >= 0)
                dim = 2ULL << e.p->v;
            else
                dim = 1;
            // allocate resulting vector
            auto vec = CVec(dim, {0.0, 0.0});
            //            Log::log << "[getVector] vector has size " << vec.size() << " after 2ULL << " << (int)(e.p->v) << '\n';

            getVector(e, Complex::one, 0, vec, lim);
            return vec;
        }

        CVec getVector(const vEdge& e, Qubit nQubits, LimEntry<> lim = {}) {
            std::size_t dim;
            if (nQubits >= 0) {
                dim = 2ULL << nQubits;
            } else {
                dim = 1;
            }
            auto vec = CVec(dim, {0.0, 0.0});
            getVector(e, Complex::one, 0, vec, lim);
            return vec;
        }

        CVec getVector(const vEdge& e) {
            std::size_t dim = 0;
            if (e.p->v >= 0)
                dim = 2ULL << e.p->v;
            else
                dim = 1;
            // allocate resulting vector
            auto vec = CVec(dim, {0.0, 0.0});

            getVector(e, Complex::one, 0, vec);
            return vec;
        }

        CVec getVector(vNode* v) {
            vEdge edge{v, Complex::one, nullptr};
            return getVector(edge);
        }

        clock_t getVectorTime = 0;
        long getVectorCallCount = 0;
        void getVector(const vEdge& e, const Complex& amp, std::size_t i, CVec& vec, LimEntry<> lim = {}) {
            startProfile(getVector)
            // calculate new accumulated amplitude
            auto c = cn.mulCached(e.w, amp);
            //            Log::log << "[getVector] i=" << i << " qubit=" << (int)(e.p->v) << " e.w=" << e.w << " amp=" << amp << " c=" << c << " lim = " << LimEntry<>::to_string(&lim, e.p->v) << '\n';

            // base case
            if (e.isTerminal()) {
                c.multiplyByPhase(lim.getPhase());
                vec.at(i) = {CTEntry::val(c.r), CTEntry::val(c.i)};
                cn.returnToCache(c);
                return;
            }

            const std::size_t x = i | (1ULL << e.p->v);

            vEdge e2{};

            LimEntry<> trueLim = lim;
            trueLim.multiplyBy(e.l);
            const auto op = trueLim.getPauliForQubit(e.p->v);
            trueLim.setOperator(e.p->v, 'I');

            // recursive case
            e2 = follow2(e, 0, op);
            if (!e2.w.approximatelyZero()) getVector(e2, c, i, vec, trueLim);

            e2 = follow2(e, 1, op);
            //            Log::log << "[getVector] follow(e, 1, " << LimEntry<>::to_string(&lim, e.p->v) << ") = (" << e2 << ",  " << LimEntry<>::to_string(&lim2, e2.p->v) << '\n';
            if (!e2.w.approximatelyZero()) getVector(e2, c, x, vec, trueLim);

            cn.returnToCache(c);
        }

        // Returns whether the diagram is a Tower.
        bool isTower(const vEdge& edge) {
            if (edge.isTerminal()) return true;
            if (edge.p->e[0].w.approximatelyZero()) {
                return isTower(edge.p->e[1]);
            }
            if (edge.p->e[1].w.approximatelyZero()) {
                return isTower(edge.p->e[0]);
            }
            if (edge.p->e[0].p == edge.p->e[1].p) {
                return isTower(edge.p->e[0]);
            }
            return false;
        }

        //        CVec getVector(const vEdge& e, const LimEntry<>& lim) {
        //            const std::size_t dim = 2ULL << e.p->v;
        //            // allocate resulting vector
        //            auto vec = CVec(dim, {0.0, 0.0});
        //            getVector(e, Complex::one, 0, vec, lim);
        //            //std::cout << "[getVector] complete; constructed vector.\n";
        //            return vec;
        //        }
        //
        //        CVec getVector([[maybe_unused]] const mEdge& e) {
        //            CVec vec;
        //            return vec;
        //        }
        //
        //        CVec getVector([[maybe_unused]] const mEdge& e, [[maybe_unused]] const LimEntry<>& lim) {
        //            CVec vec;
        //            return vec;
        //        }
        //
        //        CVec getVector(const vEdge& e) {
        //            //std::cout << "[getVector] getting vector of " << (int)(e.p->v) << "-qubit state with label " << LimEntry<>::to_string(e.l) << ".\n";
        //            const std::size_t dim = 2ULL << e.p->v;
        //            // allocate resulting vector
        //            auto       vec = CVec(dim, {0.0, 0.0});
        //            LimEntry<> id;
        //            getVector(e, Complex::one, 0, vec, id);
        //            //std::cout << "[getVector] complete; constructed vector.\n";
        //            return vec;
        //        }
        //        void getVector(const vEdge& e, const Complex& amp, std::size_t i, CVec& vec, const LimEntry<>& lim) {
        //            Log::log << "[getVector rec n=" << e.p->v + 1 << " i=" << i << "] vector of " << (int)(e.p->v) + 1 << " qubits; i = " << i << "; e.w = " << e.w << " amp = " << amp << " cached count " << cn.complexCache.getCount() << " edge label " << LimEntry<>::to_string(e.l) << ", aux label " << LimEntry<>::to_string(&lim) << ".\n";
        //            auto c = cn.mulCached(e.w, amp);
        //            Log::log << "[getVector rec n=" << e.p->v + 1 << " i=" << i << "] c = " << c << " after multiplying with aux weight.\n";
        //
        //            // base case
        //            if (e.isTerminal()) {
        //                Log::log << "[getVector rec n=" << e.p->v + 1 << " i=" << i << "] base case: vec[" << i << "] = " << c << "\n";
        //                vec.at(i) = {CTEntry::val(c.r), CTEntry::val(c.i)};
        //                cn.returnToCache(c);
        //                return;
        //            }
        //            const std::size_t x = i | (1ULL << e.p->v);
        //
        //            LimEntry<> lim2(e.l);
        //            lim2.multiplyBy(lim);
        //            c.multiplyByPhase(lim2.getPhase());
        //            lim2.setPhase(phase_t::phase_one);
        //
        //            // recursive case
        //            if (!e.p->e[0].w.approximatelyZero()) {
        //                std::size_t id0 = i;
        //                if (lim2.getQubit(e.p->v) == 'X') {
        //                    // new index is x
        //                    id0 = x;
        //                }
        //                if (lim2.getQubit(e.p->v) == 'Y') {
        //                    // new index is x
        //                    id0 = x;
        //                    // multiply c0 by i
        //                    c.multiplyByi();
        //                }
        //                Log::log << "[getVector rec n=" << e.p->v + 1 << " i=" << i << "] walking the low edge with c = " << c << ".\n";
        //                getVector(e.p->e[0], c, id0, vec, lim2);
        //                if (lim2.getQubit(e.p->v) == 'Y') {
        //                    c.multiplyByMinusi();
        //                }
        //                //                cn.returnToCache(d0);
        //            }
        //            if (!e.p->e[1].w.approximatelyZero()) {
        //                // if lim has Pauli Z operator, then multiply by -1
        //                std::size_t id1 = x;
        //                if (lim2.getQubit(e.p->v) == 'Z') {
        //                    Log::log << "[getVector rec n=" << e.p->v + 1 << " i=" << i << "] c := " << c << " after encountering Z on high edge.\n";
        //                    c.multiplyByMinusOne();
        //                } else if (lim2.getQubit(e.p->v) == 'X') {
        //                    // new index is i
        //                    id1 = i;
        //                } else if (lim2.getQubit(e.p->v) == 'Y') {
        //                    // new index is i
        //                    id1 = i;
        //                    c.multiplyByMinusi();
        //                }
        //                std::cout << "[getVector rec n=" << e.p->v + 1 << " i=" << i << "] walking the high edge with c = " << c << ".\n";
        //                getVector(e.p->e[1], c, id1, vec, lim2);
        //            }
        //            cn.returnToCache(c);
        //        }

        // Returns whether v ~ w, i.e., whether each entry v[i] of v is approximately equal to w[i],
        //    without taking into account a multiplicative factor like in 'vectorsApproximatelyEqual'
        bool vectorsApproximatelyPointwiseEqual(const CVec& v, const CVec& w) {
            if (v.size() != w.size()) return false;
            for (unsigned int i=0; i<v.size(); i++) {
                if (!Complex::approximatelyEqual(v[i], w[i])) {
                    return false;
                }
            }
            return true;
        }

        // Returns whether v ~ w, up to a complex multiplicative factor
        bool vectorsApproximatelyEqual(const CVec& v, const CVec& w) {
            //std::cout << "[vectors approximately equal] start.\n";
            //std::cout.flush();
            if (v.size() < w.size()) {
                // We demand that w is approximately zero
                for (unsigned int i = 0; i < w.size(); i++) {
                    if (!Complex::approximatelyZero(w[i])) return false;
                }
                return true;
            } else if (w.size() < v.size()) {
                for (unsigned int i = 0; i < v.size(); i++) {
                    if (!Complex::approximatelyZero(v[i])) return false;
                }
                return true;
            }
            if (v.size() != w.size()) return false;
            // find the factor d with which the vectors differ
            std::complex<fp> d = 0;
            bool             vz, wz;
            unsigned int     i;
            for (i = 0; i < v.size(); i++) {
                vz = Complex::approximatelyZero(v[i]);
                wz = Complex::approximatelyZero(w[i]);
                if (!vz && !wz) {
                    d = v[i] / w[i];
                    i++;
                    break;
                } else if (!(vz && wz))
                    return false;
            }
            //std::cout << "[vectors approximately equal] found factor d = " << d << "\n";
            //std::cout.flush();
            std::complex<fp> vc;
            // check whether the remainder of the two vectors v,w, differ by factor d
            for (; i < v.size(); i++) {
                vz = Complex::approximatelyZero(v[i]);
                wz = Complex::approximatelyZero(w[i]);
                if (!vz && !wz) {
                    vc = v[i] / d;
                    if (!Complex::approximatelyEqual(vc, w[i])) {
                        return false;
                    }
                } else if (!(vz && wz))
                    return false;
            }

            return true;
        }

        //        bool isValidIsomorphism(Edge<vNode> e1, Edge<vNode> e2, const LimEntry<>* iso) {
        //            e1.l      = LimEntry<>::multiply(e1.l, iso);
        //            CVec phi1 = getVector(e1);
        //            CVec phi2 = getVector(e2);
        //            return vectorsApproximatelyEqual(phi1, phi2);
        //        }

        void printMatrix(const dEdge& e) {
            return;
        }

        CMat getMatrix([[maybe_unused]] const dEdge& e) {
            return {};
        }

        CVec getVector([[maybe_unused]] const dEdge& e, [[maybe_unused]] Qubit q = 0, [[maybe_unused]] LimEntry<> lim = {}) {
            CVec vec;
            return vec;
        }

        void printVector(const vEdge& e) {
            const unsigned long long element = 2ULL << e.p->v;
            for (auto i = 0ULL; i < element; i++) {
                const auto amplitude = getValueByPath(e, i);
                for (Qubit j = e.p->v; j >= 0; j--) {
                    std::cout << ((i >> j) & 1ULL);
                }
                constexpr auto precision = 3;
                // set fixed width to maximum of a printed number
                // (-) 0.precision plus/minus 0.precision i
                constexpr auto width = 1 + 2 + precision + 1 + 2 + precision + 1;
                std::cout << ": " << std::setw(width) << ComplexValue::toString(amplitude.r, amplitude.i, false, precision) << "\n";
            }
            std::cout << std::flush;
        }

        void printMatrix(const mEdge& e) {
            const unsigned long long element = 2ULL << e.p->v;
            for (auto i = 0ULL; i < element; i++) {
                for (auto j = 0ULL; j < element; j++) {
                    const auto     amplitude = getValueByPath(e, i, j);
                    constexpr auto precision = 3;
                    // set fixed width to maximum of a printed number
                    // (-) 0.precision plus/minus 0.precision i
                    constexpr auto width = 1 + 2 + precision + 1 + 2 + precision + 1;
                    std::cout << std::setw(width) << ComplexValue::toString(amplitude.r, amplitude.i, false, precision) << " ";
                }
                std::cout << "\n";
            }
            std::cout << std::flush;
        }

        CMat getMatrix(const mEdge& e) {
            if (e.p->v < 0) {
                auto mat = CMat(1, CVec(1, {CTEntry::val(e.w.r), CTEntry::val(e.w.i)}));
                return mat;
            }
            const unsigned long long dim = 2ULL << e.p->v;
            // allocate resulting matrix
            auto mat = CMat(dim, CVec(dim, {0.0, 0.0}));
            getMatrix(e, Complex::one, 0, 0, mat);
            return mat;
        }
        void getMatrix(const mEdge& e, const Complex& amp, std::size_t i, std::size_t j, CMat& mat) {
            // calculate new accumulated amplitude
            auto c = cn.mulCached(e.w, amp);

            // base case
            if (e.isTerminal()) {
                mat.at(i).at(j) = {CTEntry::val(c.r), CTEntry::val(c.i)};
                cn.returnToCache(c);
                return;
            }

            const std::size_t x = i | (1ULL << e.p->v);
            const std::size_t y = j | (1ULL << e.p->v);

            // recursive case
            if (!e.p->e[0].w.approximatelyZero())
                getMatrix(e.p->e[0], c, i, j, mat);
            if (!e.p->e[1].w.approximatelyZero())
                getMatrix(e.p->e[1], c, i, y, mat);
            if (!e.p->e[2].w.approximatelyZero())
                getMatrix(e.p->e[2], c, x, j, mat);
            if (!e.p->e[3].w.approximatelyZero())
                getMatrix(e.p->e[3], c, x, y, mat);
            cn.returnToCache(c);
        }

        CMat getDensityMatrix(dEdge& e) {
            dEdge::applyDmChangesToEdge(e);
            const unsigned long long dim = 2ULL << e.p->v;
            // allocate resulting matrix
            auto mat = CMat(dim, CVec(dim, {0.0, 0.0}));
            getDensityMatrix(e, Complex::one, 0, 0, mat);
            dd::dEdge::revertDmChangesToEdge(e);
            return mat;
        }

        void getDensityMatrix(dEdge& e, Complex& amp, std::size_t i, std::size_t j, CMat& mat) {
            // calculate new accumulated amplitude
            auto c = cn.mulCached(e.w, amp);

            // base case
            if (e.isTerminal()) {
                mat.at(i).at(j) = {CTEntry::val(c.r), CTEntry::val(c.i)};
                cn.returnToCache(c);
                return;
            }

            const std::size_t x = i | (1ULL << e.p->v);
            const std::size_t y = j | (1ULL << e.p->v);

            // recursive case
            if (!e.p->e[0].w.approximatelyZero()) {
                dEdge::applyDmChangesToEdge(e.p->e[0]);
                getDensityMatrix(e.p->e[0], c, i, j, mat);
                dd::dEdge::revertDmChangesToEdge(e.p->e[0]);
            }
            if (!e.p->e[1].w.approximatelyZero()) {
                dEdge::applyDmChangesToEdge(e.p->e[1]);
                getDensityMatrix(e.p->e[1], c, i, y, mat);
                dd::dEdge::revertDmChangesToEdge(e.p->e[1]);
            }
            if (!e.p->e[2].w.approximatelyZero()) {
                dEdge::applyDmChangesToEdge(e.p->e[2]);
                getDensityMatrix(e.p->e[2], c, x, j, mat);
                dd::dEdge::revertDmChangesToEdge(e.p->e[2]);
            }
            if (!e.p->e[3].w.approximatelyZero()) {
                dEdge::applyDmChangesToEdge(e.p->e[3]);
                getDensityMatrix(e.p->e[3], c, x, y, mat);
                dd::dEdge::revertDmChangesToEdge(e.p->e[3]);
            }

            cn.returnToCache(c);
        }

        void exportAmplitudesRec(const vEdge& edge, std::ostream& oss, const std::string& path, Complex& amplitude, dd::QubitCount level, bool binary = false) {
            if (edge.isTerminal()) {
                auto amp = cn.getTemporary();
                dd::ComplexNumbers::mul(amp, amplitude, edge.w);
                for (std::size_t i = 0; i < (1ULL << level); i++) {
                    if (binary) {
                        amp.writeBinary(oss);
                    } else {
                        oss << amp.toString(false, 16) << "\n";
                    }
                }

                return;
            }

            auto a = cn.mulCached(amplitude, edge.w);
            exportAmplitudesRec(edge.p->e[0], oss, path + "0", a, level - 1, binary);
            exportAmplitudesRec(edge.p->e[1], oss, path + "1", a, level - 1, binary);
            cn.returnToCache(a);
        }
        void exportAmplitudes(const vEdge& edge, std::ostream& oss, dd::QubitCount nq, bool binary = false) {
            if (edge.isTerminal()) {
                // TODO special treatment
                return;
            }
            auto weight = cn.getCached(1., 0.);
            exportAmplitudesRec(edge, oss, "", weight, nq, binary);
            cn.returnToCache(weight);
        }
        void exportAmplitudes(const vEdge& edge, const std::string& outputFilename, dd::QubitCount nq, bool binary = false) {
            std::ofstream      init(outputFilename);
            std::ostringstream oss{};

            exportAmplitudes(edge, oss, nq, binary);

            init << oss.str() << std::flush;
            init.close();
        }

        void exportAmplitudesRec(const vEdge& edge, std::vector<std::complex<dd::fp>>& amplitudes, Complex& amplitude, dd::QubitCount level, std::size_t idx) {
            if (edge.isTerminal()) {
                auto amp = cn.getTemporary();
                dd::ComplexNumbers::mul(amp, amplitude, edge.w);
                idx <<= level;
                for (std::size_t i = 0; i < (1ULL << level); i++) {
                    amplitudes[idx++] = std::complex<dd::fp>{dd::ComplexTable<>::Entry::val(amp.r), dd::ComplexTable<>::Entry::val(amp.i)};
                }

                return;
            }

            auto a = cn.mulCached(amplitude, edge.w);
            exportAmplitudesRec(edge.p->e[0], amplitudes, a, level - 1, idx << 1);
            exportAmplitudesRec(edge.p->e[1], amplitudes, a, level - 1, (idx << 1) | 1ULL);
            cn.returnToCache(a);
        }
        void exportAmplitudes(const vEdge& edge, std::vector<std::complex<dd::fp>>& amplitudes, dd::QubitCount nq) {
            if (edge.isTerminal()) {
                // TODO special treatment
                return;
            }
            auto weight = cn.getCached(1., 0.);
            exportAmplitudesRec(edge, amplitudes, weight, nq, 0);
            cn.returnToCache(weight);
        }

        void addAmplitudesRec(const vEdge& edge, std::vector<std::complex<dd::fp>>& amplitudes, ComplexValue& amplitude, dd::QubitCount level, std::size_t idx) {
            auto         ar = dd::ComplexTable<>::Entry::val(edge.w.r);
            auto         ai = dd::ComplexTable<>::Entry::val(edge.w.i);
            ComplexValue amp{ar * amplitude.r - ai * amplitude.i, ar * amplitude.i + ai * amplitude.r};

            if (edge.isTerminal()) {
                idx <<= level;
                for (std::size_t i = 0; i < (1ULL << level); i++) {
                    auto temp         = std::complex<dd::fp>{amp.r + amplitudes[idx].real(), amp.i + amplitudes[idx].imag()};
                    amplitudes[idx++] = temp;
                }

                return;
            }

            addAmplitudesRec(edge.p->e[0], amplitudes, amp, level - 1, idx << 1);
            addAmplitudesRec(edge.p->e[1], amplitudes, amp, level - 1, idx << 1 | 1ULL);
        }
        void addAmplitudes(const vEdge& edge, std::vector<std::complex<dd::fp>>& amplitudes, dd::QubitCount nq) {
            if (edge.isTerminal()) {
                // TODO special treatment
                return;
            }
            ComplexValue a{1., 0.};
            addAmplitudesRec(edge, amplitudes, a, nq, 0);
        }

        // transfers a decision diagram from another package to this package
        template<class Edge>
        Edge transfer(Edge& original) {
            // POST ORDER TRAVERSAL USING ONE STACK   https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
            Edge              root{};
            std::stack<Edge*> stack;

            std::unordered_map<decltype(original.p), decltype(original.p)> mapped_node{};

            Edge* currentEdge = &original;
            if (!currentEdge->isTerminal()) {
                constexpr std::size_t N = std::tuple_size_v<decltype(original.p->e)>;
                do {
                    while (currentEdge != nullptr && !currentEdge->isTerminal()) {
                        for (short i = N - 1; i > 0; --i) {
                            auto& edge = currentEdge->p->e[i];
                            if (edge.isTerminal()) {
                                continue;
                            }
                            if (edge.w.approximatelyZero()) {
                                continue;
                            }
                            if (mapped_node.find(edge.p) != mapped_node.end()) {
                                continue;
                            }

                            // non-zero edge to be included
                            stack.push(&edge);
                        }
                        stack.push(currentEdge);
                        currentEdge = &currentEdge->p->e[0];
                    }
                    currentEdge = stack.top();
                    stack.pop();

                    bool hasChild = false;
                    for (std::size_t i = 1; i < N && !hasChild; ++i) {
                        auto& edge = currentEdge->p->e[i];
                        if (edge.w.approximatelyZero()) {
                            continue;
                        }
                        if (mapped_node.find(edge.p) != mapped_node.end()) {
                            continue;
                        }
                        hasChild = edge.p == stack.top()->p;
                    }

                    if (hasChild) {
                        Edge* temp = stack.top();
                        stack.pop();
                        stack.push(currentEdge);
                        currentEdge = temp;
                    } else {
                        if (mapped_node.find(currentEdge->p) != mapped_node.end()) {
                            currentEdge = nullptr;
                            continue;
                        }
                        std::array<Edge, N> edges{};
                        for (std::size_t i = 0; i < N; i++) {
                            if (currentEdge->p->e[i].isTerminal()) {
                                edges[i].p = currentEdge->p->e[i].p;
                            } else {
                                edges[i].p = mapped_node[currentEdge->p->e[i].p];
                            }
                            edges[i].w = cn.lookup(currentEdge->p->e[i].w);
                        }
                        root                        = makeDDNode(currentEdge->p->v, edges);
                        mapped_node[currentEdge->p] = root.p;
                        currentEdge                 = nullptr;
                    }
                } while (!stack.empty());

                auto w = cn.getCached(dd::ComplexTable<>::Entry::val(original.w.r), dd::ComplexTable<>::Entry::val(original.w.i));
                dd::ComplexNumbers::mul(w, root.w, w);
                root.w = cn.lookup(w);
                cn.returnToCache(w);
            } else {
                root.p = original.p; // terminal -> static
                root.w = cn.lookup(original.w);
            }
            return root;
        }

        ///
        /// Deserialization
        /// Note: do not rely on the binary format being portable across different architectures/platforms
        ///
    public:
        template<class Node, class Edge = Edge<Node>, std::size_t N = std::tuple_size_v<decltype(Node::e)>>
        Edge deserialize(std::istream& is, bool readBinary = false) {
            auto         result = Edge::zero;
            ComplexValue rootweight{};

            std::unordered_map<std::int_least64_t, Node*> nodes{};
            std::int_least64_t                            node_index;
            Qubit                                         v;
            std::array<ComplexValue, N>                   edge_weights{};
            std::array<std::int_least64_t, N>             edge_indices{};
            edge_indices.fill(-2);

            if (readBinary) {
                std::remove_const_t<decltype(SERIALIZATION_VERSION)> version;
                is.read(reinterpret_cast<char*>(&version), sizeof(decltype(SERIALIZATION_VERSION)));
                if (version != SERIALIZATION_VERSION) {
                    throw std::runtime_error("Wrong Version of serialization file version. version of file: " + std::to_string(version) + "; current version: " + std::to_string(SERIALIZATION_VERSION));
                }

                if (!is.eof()) {
                    rootweight.readBinary(is);
                }

                while (is.read(reinterpret_cast<char*>(&node_index), sizeof(decltype(node_index)))) {
                    is.read(reinterpret_cast<char*>(&v), sizeof(decltype(v)));
                    for (auto i = 0U; i < N; i++) {
                        is.read(reinterpret_cast<char*>(&edge_indices[i]), sizeof(decltype(edge_indices[i])));
                        edge_weights[i].readBinary(is);
                    }
                    result = deserializeNode(node_index, v, edge_indices, edge_weights, nodes);
                }
            } else {
                std::string version;
                std::getline(is, version);
                if (std::stoi(version) != SERIALIZATION_VERSION) {
                    throw std::runtime_error("Wrong Version of serialization file version. version of file: " + version + "; current version: " + std::to_string(SERIALIZATION_VERSION));
                }

                std::string line;
                std::string complex_real_regex = R"(([+-]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?(?![ \d\.]*(?:[eE][+-])?\d*[iI]))?)";
                std::string complex_imag_regex = R"(( ?[+-]? ?(?:(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)?[iI])?)";
                std::string edge_regex         = " \\(((-?\\d+) (" + complex_real_regex + complex_imag_regex + "))?\\)";
                std::regex  complex_weight_regex(complex_real_regex + complex_imag_regex);
                std::string line_construct = "(\\d+) (\\d+)";
                for (auto i = 0U; i < N; ++i) {
                    line_construct += "(?:" + edge_regex + ")";
                }
                line_construct += " *(?:#.*)?";
                std::regex  line_regex(line_construct);
                std::smatch m;

                if (std::getline(is, line)) {
                    if (!std::regex_match(line, m, complex_weight_regex)) {
                        throw std::runtime_error("Regex did not match second line: " + line);
                    }
                    rootweight.from_string(m.str(1), m.str(2));
                }

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

                    for (auto edge_idx = 3U, i = 0U; i < N; i++, edge_idx += 5) {
                        if (m.str(edge_idx).empty()) continue;

                        edge_indices[i] = std::stoi(m.str(edge_idx + 1));
                        edge_weights[i].from_string(m.str(edge_idx + 3), m.str(edge_idx + 4));
                    }

                    result = deserializeNode(node_index, v, edge_indices, edge_weights, nodes);
                }
            }

            auto w = cn.getCached(rootweight.r, rootweight.i);
            ComplexNumbers::mul(w, result.w, w);
            result.w = cn.lookup(w);
            cn.returnToCache(w);

            return result;
        }

        template<class Node, class Edge = Edge<Node>>
        Edge deserialize(const std::string& inputFilename, bool readBinary) {
            auto ifs = std::ifstream(inputFilename, std::ios::binary);

            if (!ifs.good()) {
                throw std::invalid_argument("Cannot open serialized file: " + inputFilename);
            }

            return deserialize<Node>(ifs, readBinary);
        }

    private:
        template<class Node, class Edge = Edge<Node>, std::size_t N = std::tuple_size_v<decltype(Node::e)>>
        Edge deserializeNode(std::int_least64_t index, Qubit v, std::array<std::int_least64_t, N>& edge_idx, std::array<ComplexValue, N>& edge_weight, std::unordered_map<std::int_least64_t, Node*>& nodes) {
            if (index == -1) {
                return Edge::zero;
            }

            std::array<Edge, N> edges{};
            for (auto i = 0U; i < N; ++i) {
                if (edge_idx[i] == -2) {
                    edges[i] = Edge::zero;
                } else {
                    if (edge_idx[i] == -1) {
                        edges[i] = Edge::one;
                    } else {
                        edges[i].p = nodes[edge_idx[i]];
                    }
                    edges[i].w = cn.lookup(edge_weight[i]);
                }
            }

            auto newedge = makeDDNode(v, edges);
            nodes[index] = newedge.p;

            // reset
            edge_idx.fill(-2);

            return newedge;
        }

        ///
        /// Debugging
        ///
    public:
        template<class Node>
        void debugnode(const Node* p) const {
            if (Node::isTerminal(p)) {
                std::clog << "terminal\n";
                return;
            }
            std::clog << "Debug node: " << debugnode_line(p) << "\n";
            for (const auto& edge: p->e) {
                std::clog << "  " << std::hexfloat
                          << std::setw(22) << CTEntry::val(edge.w.r) << " "
                          << std::setw(22) << CTEntry::val(edge.w.i) << std::defaultfloat
                          << "i --> " << debugnode_line(edge.p)
                          << "lim=" << LimEntry<>::to_string(edge.l)
                          << "\n";
            }
            std::clog << std::flush;
        }

        template<class Node>
        std::string debugnode_line(const Node* p) const {
            if (Node::isTerminal(p)) {
                return "terminal";
            }
            std::stringstream sst;
            sst << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(p) << std::dec
                << "[v=" << static_cast<std::int_fast64_t>(p->v)
                << " ref=" << p->ref
                << " hash=" << UniqueTable<Node>::hash(p)
                << " lim="
                << "TODO" // TODO limdd
                << "]";
            return sst.str();
        }

        template<class Edge>
        bool isLocallyConsistent(const Edge& e) {
            assert(Complex::one.r->value == 1 && Complex::one.i->value == 0);
            assert(Complex::zero.r->value == 0 && Complex::zero.i->value == 0);

            const bool result = isLocallyConsistent2(e);
            return result;
        }

        template<class Edge>
        bool isGloballyConsistent(const Edge& e) {
            std::map<ComplexTable<>::Entry*, std::size_t> weight_counter{};
            std::map<decltype(e.p), std::size_t>          node_counter{};
            fillConsistencyCounter(e, weight_counter, node_counter);
            checkConsistencyCounter(e, weight_counter, node_counter);
            return true;
        }

    private:
        template<class Edge>
        bool isLocallyConsistent2(const Edge& e) {
            const auto ptr_r = CTEntry::getAlignedPointer(e.w.r);
            const auto ptr_i = CTEntry::getAlignedPointer(e.w.i);

            if ((ptr_r->refCount == 0 || ptr_i->refCount == 0) && e.w != Complex::one && e.w != Complex::zero) {
                std::clog << "\nLOCAL INCONSISTENCY FOUND\nOffending Number: " << e.w << " (" << ptr_r->refCount << ", " << ptr_i->refCount << ")\n\n";
                debugnode(e.p);
                return false;
            }

            if (e.isTerminal()) {
                return true;
            }

            if (!e.isTerminal() && e.p->ref == 0) {
                std::clog << "\nLOCAL INCONSISTENCY FOUND: RC==0\n";
                debugnode(e.p);
                return false;
            }

            for (const auto& child: e.p->e) {
                if (child.p->v + 1 != e.p->v && !child.isTerminal()) {
                    std::clog << "\nLOCAL INCONSISTENCY FOUND: Wrong V\n";
                    debugnode(e.p);
                    return false;
                }
                if (!child.isTerminal() && child.p->ref == 0) {
                    std::clog << "\nLOCAL INCONSISTENCY FOUND: RC==0\n";
                    debugnode(e.p);
                    return false;
                }
                if (!isLocallyConsistent2(child)) {
                    return false;
                }
            }
            return true;
        }

        template<class Edge>
        void fillConsistencyCounter(const Edge& edge, std::map<ComplexTable<>::Entry*, std::size_t>& weight_map, std::map<decltype(edge.p), std::size_t>& node_map) {
            weight_map[CTEntry::getAlignedPointer(edge.w.r)]++;
            weight_map[CTEntry::getAlignedPointer(edge.w.i)]++;

            if (edge.isTerminal()) {
                return;
            }
            node_map[edge.p]++;
            for (auto& child: edge.p->e) {
                if (node_map[child.p] == 0) {
                    fillConsistencyCounter(child, weight_map, node_map);
                } else {
                    node_map[child.p]++;
                    weight_map[CTEntry::getAlignedPointer(child.w.r)]++;
                    weight_map[CTEntry::getAlignedPointer(child.w.i)]++;
                }
            }
        }

        template<class Edge>
        void checkConsistencyCounter(const Edge& edge, const std::map<ComplexTable<>::Entry*, std::size_t>& weight_map, const std::map<decltype(edge.p), std::size_t>& node_map) {
            auto* r_ptr = CTEntry::getAlignedPointer(edge.w.r);
            auto* i_ptr = CTEntry::getAlignedPointer(edge.w.i);

            if (weight_map.at(r_ptr) > r_ptr->refCount && r_ptr != Complex::one.r && r_ptr != Complex::zero.i && r_ptr != &ComplexTable<>::sqrt2_2) {
                std::clog << "\nOffending weight: " << edge.w << "\n";
                std::clog << "Bits: " << std::hexfloat << CTEntry::val(edge.w.r) << "r " << CTEntry::val(edge.w.i) << std::defaultfloat << "i\n";
                debugnode(edge.p);
                throw std::runtime_error("Ref-Count mismatch for " + std::to_string(r_ptr->value) + "(r): " + std::to_string(weight_map.at(r_ptr)) + " occurences in DD but Ref-Count is only " + std::to_string(r_ptr->refCount));
            }

            if (weight_map.at(i_ptr) > i_ptr->refCount && i_ptr != Complex::zero.i && i_ptr != Complex::one.r && i_ptr != &ComplexTable<>::sqrt2_2) {
                std::clog << "\nOffending weight: " << edge.w << "\n";
                std::clog << "Bits: " << std::hexfloat << CTEntry::val(edge.w.r) << "r " << CTEntry::val(edge.w.i) << std::defaultfloat << "i\n";
                debugnode(edge.p);
                throw std::runtime_error("Ref-Count mismatch for " + std::to_string(i_ptr->value) + "(i): " + std::to_string(weight_map.at(i_ptr)) + " occurences in DD but Ref-Count is only " + std::to_string(i_ptr->refCount));
            }

            if (edge.isTerminal()) {
                return;
            }

            if (node_map.at(edge.p) != edge.p->ref) {
                debugnode(edge.p);
                throw std::runtime_error("Ref-Count mismatch for node: " + std::to_string(node_map.at(edge.p)) + " occurences in DD but Ref-Count is " + std::to_string(edge.p->ref));
            }
            for (auto child: edge.p->e) {
                if (!child.isTerminal() && child.p->v != edge.p->v - 1) {
                    std::clog << "child.p->v == " << child.p->v << "\n";
                    std::clog << " edge.p->v == " << edge.p->v << "\n";
                    debugnode(child.p);
                    debugnode(edge.p);
                    throw std::runtime_error("Variable level ordering seems wrong");
                }
                checkConsistencyCounter(child, weight_map, node_map);
            }
        }

        ///
        /// Printing and Statistics
        ///
    public:
        // print information on package and its members
        static void printInformation() {
            // TODO limdd
            std::cout << "\n  compiled: " << __DATE__ << " " << __TIME__
                      << "\n  Complex size: " << sizeof(Complex) << " bytes (aligned " << alignof(Complex) << " bytes)"
                      << "\n  ComplexValue size: " << sizeof(ComplexValue) << " bytes (aligned " << alignof(ComplexValue) << " bytes)"
                      << "\n  ComplexNumbers size: " << sizeof(ComplexNumbers) << " bytes (aligned " << alignof(ComplexNumbers) << " bytes)"
                      << "\n  LimEntry<> size: " << sizeof(LimEntry<>) << " bytes (aligned " << alignof(LimEntry<>) << " bytes)"
                      << "\n  vEdge size: " << sizeof(vEdge) << " bytes (aligned " << alignof(vEdge) << " bytes)"
                      << "\n  vNode size: " << sizeof(vNode) << " bytes (aligned " << alignof(vNode) << " bytes)"
                      << "\n  mEdge size: " << sizeof(mEdge) << " bytes (aligned " << alignof(mEdge) << " bytes)"
                      << "\n  mNode size: " << sizeof(mNode) << " bytes (aligned " << alignof(mNode) << " bytes)"
                      << "\n  CT Vector Add size: " << sizeof(typename decltype(vectorAdd)::Entry) << " bytes (aligned " << alignof(typename decltype(vectorAdd)::Entry) << " bytes)"
                      << "\n  CT Matrix Add size: " << sizeof(typename decltype(matrixAdd)::Entry) << " bytes (aligned " << alignof(typename decltype(matrixAdd)::Entry) << " bytes)"
                      << "\n  CT Matrix Transpose size: " << sizeof(typename decltype(matrixTranspose)::Entry) << " bytes (aligned " << alignof(typename decltype(matrixTranspose)::Entry) << " bytes)"
                      << "\n  CT Conjugate Matrix Transpose size: " << sizeof(typename decltype(conjugateMatrixTranspose)::Entry) << " bytes (aligned " << alignof(typename decltype(conjugateMatrixTranspose)::Entry) << " bytes)"
                      << "\n  CT Matrix Multiplication size: " << sizeof(typename decltype(matrixMatrixMultiplication)::Entry) << " bytes (aligned " << alignof(typename decltype(matrixMatrixMultiplication)::Entry) << " bytes)"
                      << "\n  CT Matrix Vector Multiplication size: " << sizeof(typename decltype(matrixVectorMultiplication)::Entry) << " bytes (aligned " << alignof(typename decltype(matrixVectorMultiplication)::Entry) << " bytes)"
                      << "\n  CT Vector Inner Product size: " << sizeof(typename decltype(vectorInnerProduct)::Entry) << " bytes (aligned " << alignof(typename decltype(vectorInnerProduct)::Entry) << " bytes)"
                      << "\n  CT Vector Kronecker size: " << sizeof(typename decltype(vectorKronecker)::Entry) << " bytes (aligned " << alignof(typename decltype(vectorKronecker)::Entry) << " bytes)"
                      << "\n  CT Matrix Kronecker size: " << sizeof(typename decltype(matrixKronecker)::Entry) << " bytes (aligned " << alignof(typename decltype(matrixKronecker)::Entry) << " bytes)"
                      << "\n  ToffoliTable::Entry size: " << sizeof(ToffoliTable<mEdge>::Entry) << " bytes (aligned " << alignof(ToffoliTable<mEdge>::Entry) << " bytes)"
                      << "\n  Package size: " << sizeof(Package) << " bytes (aligned " << alignof(Package) << " bytes)"
                      << "\n"
                      << std::flush;
        }

        // print unique and compute table statistics
        void statistics() {
            std::cout << "DD statistics:" << std::endl
                      << "[vUniqueTable] ";
            vUniqueTable.printStatistics();
            std::cout << "[mUniqueTable] ";
            mUniqueTable.printStatistics();
            std::cout << "[CT Vector Add] ";
            vectorAdd.printStatistics();
            std::cout << "[CT Matrix Add] ";
            matrixAdd.printStatistics();
            std::cout << "[CT Matrix Transpose] ";
            matrixTranspose.printStatistics();
            std::cout << "[CT Conjugate Matrix Transpose] ";
            conjugateMatrixTranspose.printStatistics();
            std::cout << "[CT Matrix Multiplication] ";
            matrixMatrixMultiplication.printStatistics();
            std::cout << "[CT Matrix Vector Multiplication] ";
            matrixVectorMultiplication.printStatistics();
            std::cout << "[CT Inner Product] ";
            vectorInnerProduct.printStatistics();
            std::cout << "[CT Vector Kronecker] ";
            vectorKronecker.printStatistics();
            std::cout << "[CT Matrix Kronecker] ";
            matrixKronecker.printStatistics();
            std::cout << "[Toffoli Table] ";
            toffoliTable.printStatistics();
            std::cout << "[Stochastic Noise Table] ";
            stochasticNoiseOperationCache.printStatistics();
            std::cout << "[CT Density Add] ";
            densityAdd.printStatistics();
            std::cout << "[CT Density Mul] ";
            densityDensityMultiplication.printStatistics();
            std::cout << "[CT Density Noise] ";
            densityNoise.printStatistics();
            std::cout << "[ComplexTable] ";
            cn.complexTable.printStatistics();
            std::cout << "[LimTable] ";
            lf.limTable.printStatistics();
        }

        void printCallCounterStatistics() {
            std::cout <<   "Function    Calls"
                      << "\nPauli       " << applyPauliCallCount
                      << "\nHadamard    " << applyHadamardCallCount
                      << "\nC Pauli     " << applyControlledPauliCallCount
                      << "\nPhase       " << applyPhaseCallCount
                      << "\nProjection  " << applyProjectionCallCount
                      << "\nmultiply    " << multiply2CallCount
                      << "\nadd         " << addCallCount
                      << "\n";
        }
    };

} // namespace dd

#endif
