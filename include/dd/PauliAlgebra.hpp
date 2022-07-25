//
// Created by lieuwe on 13/12/2021.
//

#ifndef DDPACKAGE_PAULIALGEBRA_HPP
#define DDPACKAGE_PAULIALGEBRA_HPP

#include "ComplexNumbers.hpp"
#include "Edge.hpp"
#include "LimTable.hpp"
#include "Log.hpp"
#include "PauliUtilities.hpp"
#include <iostream>
#include "Node.hpp"

#include <array>
#include <iostream>

// note: my package won't compile unless I put my functions in a class
// for now, I've called this class Pauli
// - Lieuwe

namespace dd {

        template<std::size_t NUM_QUBITS>
        [[nodiscard]] LimEntry<NUM_QUBITS> createCanonicalLabel(const LimEntry<NUM_QUBITS>& x, const LimEntry<NUM_QUBITS>& y, const vEdge w) {
            auto c = x;
            c.setPhase(getPhaseInverse(c.getPhase()));
            c.multiplyBy(y);
            const auto d = *getRootLabel(w.p, &c);
//            if (d==c){
//                std::cout << "RootLabelEqual" << std::endl;
//            } else {
//                std::cout << "RootLabelNotEqual" << std::endl;
//            }
            return d;
        }

        template<std::size_t NUM_QUBITS>
        [[nodiscard]] LimEntry<NUM_QUBITS> createCanonicalLabel([[maybe_unused]] const LimEntry<NUM_QUBITS>& x, [[maybe_unused]] const LimEntry<NUM_QUBITS>& y, [[maybe_unused]] const mEdge w) {
        	throw std::exception();
        }

        static void movePhaseIntoWeight(LimEntry<>& lim, Complex& weight) {
            if (lim.getPhase() != phase_one) {
                weight.multiplyByPhase(lim.getPhase());
                lim.setPhase(phase_one);
            }
        }

		// TODO write a test
		// TODO refactor to use recoverElement
		template<std::size_t NUM_QUBITS>
		phase_t recoverPhase(const std::vector<LimEntry<NUM_QUBITS>* >&G, const LimEntry<NUM_QUBITS>* a) {
			if (a == LimEntry<NUM_QUBITS>::noLIM) {
				throw std::runtime_error("[recoverPhase] a is noLIM.\n");
			}
			LimEntry<NUM_QUBITS> A(a);
			LimEntry<NUM_QUBITS> B;
			for (unsigned int g=0; g<G.size(); g++) {
				for (unsigned int i=0; i<2*NUM_QUBITS; i++) {
					if (A.paulis.test(i) && G[g]->paulis.test(i)) {
						A.multiplyBy(G[g]);
						B.multiplyBy(G[g]);
						break;
					}
				}
			}
			return B.getPhase();
		}

		// TODO write a test
		template <std::size_t NUM_QUBITS>
		LimEntry<NUM_QUBITS> recoverElement(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* a) {
			if (a == LimEntry<NUM_QUBITS>::noLIM) {
				throw std::runtime_error("[recoverPhase] a is noLIM.\n");
			}
			LimEntry<NUM_QUBITS> A(a);
			LimEntry<NUM_QUBITS> B;
			for (unsigned int g=0; g<G.size(); g++) {
				for (unsigned int i=0; i<2*NUM_QUBITS; i++) {
					if (A.paulis.test(i) && G[g]->paulis.test(i)) {
						A.multiplyBy(G[g]);
						B.multiplyBy(G[g]);
						break;
					}
				}
			}
			return B;
		}


		// Performs Gaussian elimination on G
		// We assume that G is not stored in the LimTable.
		// In more detail: the elements of G are modified in place
		// Therefore, the LimEntry objects should NOT be stored in the LimTable;
		// todo this algorithm allocates many new LIMs; by modifying in place, less memory can be allocated, and we solve a memory leak
		template <std::size_t NUM_QUBITS>
		void GaussianElimination(std::vector<LimEntry<NUM_QUBITS>*>& G) {
			if (G.size() <= 1) return;
	//        Log::log << "[Gaussian Elimination] start. |G| = " << G.size() << ".\n"; Log::log.flush();
			unsigned int pauli_height = 2*NUM_QUBITS; // length of the columns as far as they contain Pauli operators
			unsigned int reducingColId;
			for (unsigned int h=0; h<pauli_height; h++) {
				// Step 1: Find a column with a '1' at position h
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
	//                    Log::log << "[Gaussian Elimination] Multiplying col " << reduceColId << " with col " << reducingColId << ".\n"; Log::log.flush();
						G[reduceColId] = LimEntry<NUM_QUBITS>::multiply(G[reduceColId], G[reducingColId]);
					}
				}
			}
		}

		template <std::size_t NUM_QUBITS>
		bool isAbelian(const std::vector<LimBitset<NUM_QUBITS>*>& G) {
			for (unsigned int i=0; i<G.size(); i++) {
				for (unsigned int j=i+1; j<G.size(); j++) {
					if (!G[i]->lim.commutesWith(&(G[j]->lim))) {
						return false;
					}
				}
			}
			return true;
		}

		// does not initialize 'decomposition' to an identity matrix
		// TODO don't reallocate so much memory
		// TODO there is a faster version if the group is sorted
		//    (calls to GaussianElimination from getKernel do not sort their group before calling)
		template <std::size_t NUM_QUBITS>
		void GaussianElimination(std::vector<LimBitset<NUM_QUBITS>*>& G) {
			if (G.size() <= 1) return;
	//        Log::log << "[Gaussian Elimination Bitset] start. |G| = " << G.size() << ".\n"; Log::log.flush();
			unsigned int pauli_height = 2*NUM_QUBITS; // length of the columns as far as they contain Pauli operators
			unsigned int reducingColId;
			if (!isAbelian(G)) {
				// Add -I
				G.push_back(new LimBitset<NUM_QUBITS>(LimEntry<NUM_QUBITS>::getMinusIdentityOperator()));
			}
			for (unsigned int h=0; h<pauli_height; h++) {
				// Step 1: Find a column whose first '1' is at position h
				reducingColId = -1;
				for (unsigned int i=0; i<G.size(); i++) {
					if (G[i]->lim.pivotPosition() == h) {
						reducingColId = i;
						break;
					}
				}
				if (reducingColId == (unsigned int)-1) continue;
				// Step 2: Reduce all other columns via G[reducingColId]
				for (unsigned int reduceColId =0; reduceColId < G.size(); reduceColId++) {
					if (reduceColId == reducingColId) continue;
					if (G[reduceColId]->lim.paulis.test(h)) {
	//                    Log::log << "[Gaussian Elimination Bitset] Multiplying col " << reduceColId << " with col " << reducingColId << ".\n"; Log::log.flush();
						G[reduceColId] = LimBitset<NUM_QUBITS>::multiply(G[reduceColId], G[reducingColId]);
					}
				}
			}
			// the pauli's are done; handle the phase
			reducingColId = -1;
			for (unsigned int i=0; i<G.size(); i++) {
				if (G[i]->lim.isIdentityModuloPhase() && G[i]->lim.getPhase() == phase_t::phase_minus_one) {
					reducingColId = i;
					break;
				}
			}
			if (reducingColId == (unsigned int) -1) return;
			for (unsigned int reduceColId = 0; reduceColId < G.size(); reduceColId++) {
				if (reduceColId == reducingColId) continue;
				if (G[reduceColId]->lim.getPhase() == phase_t::phase_minus_one || G[reduceColId]->lim.getPhase() == phase_t::phase_minus_i) {
					G[reduceColId] = LimBitset<NUM_QUBITS>::multiply(G[reduceColId], G[reducingColId]);
				}
			}
		}

		// Performs Gaussian Elimination on the group G, ignoring the phase of the LIMs involved
		// todo it is possible to write a faster procedure, if we are allowed to assume that G is sorted
		template <std::size_t NUM_QUBITS>
		void GaussianEliminationModuloPhase(std::vector<LimBitset<NUM_QUBITS>*>& G) {
			if (G.size() <= 1) return;
	//        Log::log << "[Gaussian Elimination Bitset] start. |G| = " << G.size() << ".\n"; Log::log.flush();
			unsigned int pauli_height = 2*NUM_QUBITS; // length of the columns as far as they contain Pauli operators
			unsigned int reducingColId;
			for (unsigned int row=0; row<pauli_height; row++) {
				// Step 1: Find a column with a '1' at position row
				reducingColId = -1;
				for (unsigned int i=0; i<G.size(); i++) {
					if (G[i]->lim.pivotPosition() == row) {
						reducingColId = i;
						break;
					}
				}
				if (reducingColId == (unsigned int)-1) continue;
				// Step 2: Reduce all other columns via G[reducingColId]
				for (unsigned int reduceColId =0; reduceColId < G.size(); reduceColId++) {
					if (reduceColId == reducingColId) continue;
					if (G[reduceColId]->lim.paulis.test(row)) {
	//                    Log::log << "[Gaussian Elimination Bitset] Multiplying col " << reduceColId << " with col " << reducingColId << ".\n"; Log::log.flush();
						G[reduceColId] = LimBitset<NUM_QUBITS>::multiply(G[reduceColId], G[reducingColId]);
					}
				}
			}
		}

		// Puts the stabilizer group in column echelon form; specifically:
		//   1. performs Gaussian elimination on G
		//   2. prunes the all-zero columns
		//   3. sorts the columns lexicographically, i.e., so that 'pivots' appear in the matrix
		void toColumnEchelonForm(StabilizerGroup& G) {
	//        Log::log << "[toColumnEchelonForm] Before CEF, group is:\n"; Log::log.flush();
	//        printStabilizerGroup(G);
			GaussianElimination(G);
	//        Log::log << "[toColumnEchelonForm] After Gaussian Elimination, before pruning zero col's, group is:\n";Log::log.flush();
	//        printStabilizerGroup(G);
			pruneZeroColumns(G);
			// To obtain a lower triangular form, we now sort the vectors descending lexicographically, descending
			std::sort(G.begin(), G.end(), LimEntry<>::geq);
	//        Log::log << "[toColumnEchelonForm] After CEF, group is:\n"; Log::log.flush();
	//        printStabilizerGroup(G);
		}

		template <std::size_t NUM_QUBITS>
		void toColumnEchelonForm(std::vector<LimBitset<NUM_QUBITS>*>& G) {
	//        Log::log << "[toColumnEchelonForm] start, |G| = " << G.size() << "\n";
			GaussianElimination(G);
			pruneZeroColumns(G);
			std::sort(G.begin(), G.end(), LimBitset<NUM_QUBITS>::geq);
		}

		template <std::size_t NUM_QUBITS>
		void toColumnEchelonFormModuloPhase(std::vector<LimBitset<NUM_QUBITS>* >& G) {
			GaussianEliminationModuloPhase(G);
			pruneZeroColumnsModuloPhase(G);
			std::sort(G.begin(), G.end(), LimBitset<NUM_QUBITS>::geq);
		}

		// Reduces a vector 'x' via a group 'G' via the Gram-Schmidt procedure
		// Returns the reduced vector
		template<std::size_t NUM_QUBITS>
		LimEntry<NUM_QUBITS>* GramSchmidt(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* x) {
	//        Log::log << "[GramSchmidt] |G|=" << G.size() << "  x = " << LimEntry<>::to_string(x) << "\n"; Log::log.flush();
			LimEntry<NUM_QUBITS> y(x); // = new LimEntry<NUM_QUBITS>(x);
			if (G.size() == 0) return new LimEntry<NUM_QUBITS>(y);
			std::size_t height = 2*NUM_QUBITS;
			for (unsigned int h=0; h<height; h++) {
				if (y.paulis[h]) {
	//                Log::log << "[GramSchmidt] h=" << h << ".\n";
					// Look for a vector whose first '1' entry is at position h
					for (unsigned int v=0; v<G.size(); v++) {
						if (G[v]->pivotPosition() == h) {
	//                        Log::log << "[GramSchmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << LimEntry<>::to_string(G[v]) << "\n";
	//                        y = LimEntry<NUM_QUBITS>::multiply(*y, *G[v]);
							y.multiplyBy(*G[v]);
						}
					}
				}
			}
			return new LimEntry<NUM_QUBITS>(y);
		}

		// todo this algorithm can be sped up if we are allowed to assume that the group G is sorted
		// todo this version uses right multiplication; refactor to left multiplication
		template <std::size_t NUM_QUBITS>
		LimBitset<NUM_QUBITS> GramSchmidt(const std::vector<LimBitset<NUM_QUBITS>*>& G, const LimBitset<NUM_QUBITS>* x) {
	//        LimBitset<NUM_QUBITS>* y = new LimBitset<NUM_QUBITS>(x);
			LimBitset<NUM_QUBITS> y(x);
			if (G.size() == 0) return y;
			std::size_t height = 2*NUM_QUBITS;
	//        Log::log << "[Gram Schmidt] start y = " << y << "\n";
			for (unsigned int h=0; h<height; h++) {
				if (y.lim.paulis[h]) {
	//                Log::log << "[GramSchmidt] h=" << h << ".\n";
					// Look for a vector whose first '1' entry is at position h
					for (unsigned int v=0; v<G.size(); v++) {
						if (G[v]->lim.pivotPosition() == h) {
	//                        Log::log << "[Gram Schmidt] found '1' in G[" << v << "][" << h << "]; multiplying by " << *G[v] << "\n";
							y.multiplyBy(*G[v]);
	//                        Log::log << "[Gram Schmidt] after multiplication, y = " << y << "\n";
						}
					}
				}
			}
			return y;
		}

		// Performs the GramSchmidt algorithm,, i.e.,
		//   given a group G and a vector x,
		//   reduces the vector x via G, and returns this reduced vector
		//   The decomposition that is found, is recorded in the bitset 'indicator'
		// todo this algorithm can be sped up if the group G is sorted
		template <std::size_t NUM_QUBITS>
		void GramSchmidt(const std::vector<LimEntry<NUM_QUBITS>*>& G, const LimEntry<NUM_QUBITS>* x, std::bitset<NUM_QUBITS>& indicator) {
	//        Log::log << "[GramSchmidt] |G|=" << G.size() << "  x = " << LimEntry<>::to_string(x) << "\n";
	//        LimEntry<NUM_QUBITS>* y = new LimEntry<NUM_QUBITS>(x);
			LimEntry<NUM_QUBITS> y(x);
			std::size_t height = 2*NUM_QUBITS;
			for (unsigned int i=0; i<height && i<NUM_QUBITS; i++) {
				indicator.set(i, 0);
			}
			if (G.size() == 0) return;
			for (unsigned int h=0; h<height; h++) {
				if (y.paulis[h]) {
	//                Log::log << "[GramSchmidt] h=" << h << ".\n";
					// Look for a vector whose first '1' entry is at position h
					for (unsigned int v=0; v<G.size(); v++) {
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
		}


		// Given a group G and a 0/1 indicator vector,
		//   returns the product of the indicated elements of G
		//   e.g., with G={ZIZ, IZZ, IXY} and indicator = '110', we return ZZI
		template<std::size_t NUM_QUBITS>
		LimEntry<NUM_QUBITS>* getProductOfElements(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::bitset<NUM_QUBITS>& indicator) {
			LimEntry<NUM_QUBITS>* g = LimEntry<NUM_QUBITS>::getIdentityOperator();
			assert(G.size() <= NUM_QUBITS);
			for (unsigned int i=0; i<G.size(); i++) {
				if (indicator.test(i)) {
					g->multiplyBy(G[i]);
				}
			}
			return g;
		}

		// TODO free / deallocate G_Id and its elements
		template <std::size_t NUM_QUBITS>
		std::vector<std::bitset<NUM_QUBITS> > getKernelZ(const std::vector<LimEntry<NUM_QUBITS>* >& G) {
			std::vector<LimBitset<NUM_QUBITS>* > G_Id = appendIdentityMatrixBitset(G);
			GaussianElimination(G_Id);
	//        Log::log << "[getKernelZ] after Gaussian elimination, G_Id:\n";
	//        printStabilizerGroup(G_Id);
			std::vector<std::bitset<NUM_QUBITS> > kernel;
			for (unsigned int i=0; i<G_Id.size(); i++) {
				if (G_Id[i]->lim.isIdentityOperator()) {
					kernel.push_back(G_Id[i]->bits);
				}
			}
			// TODO free / deallocate G_Id and its elements
	//        Log::log << "[getKernelZ] found kernel:\n";
	//        printKernel(kernel);
			return kernel;
		}

		// Returns the kernel of the group G modulo phase, as a vector<bitset>
		// TODO free / deallocate G_Id and its elements
		template <std::size_t NUM_QUBITS>
		std::vector<std::bitset<NUM_QUBITS> > getKernelModuloPhase(const std::vector<LimEntry<NUM_QUBITS>* >& G) {
			std::vector<LimBitset<NUM_QUBITS>* > G_Id = appendIdentityMatrixBitset(G);
			GaussianEliminationModuloPhase(G_Id);
			std::vector<std::bitset<NUM_QUBITS> > kernel;
			for (unsigned i=0; i<G_Id.size(); i++) {
				if (G_Id[i]->lim.isIdentityModuloPhase()) {
					kernel.push_back(G_Id[i]->bits);
				}
			}
			// TODO free / deallocate G_Id and its elements
			return kernel;
		}

		// Given two groups G, H, computes the intersection, <G> intersect <H>
		// TODO refactor with NUM_QUBITS template parameter
		StabilizerGroup intersectGroupsZ(const StabilizerGroup& G, const StabilizerGroup& H) {
			StabilizerGroup intersection;
			StabilizerGroup GH = groupConcatenate(G, H);
			std::vector<std::bitset<dd::NUM_QUBITS> > kernel = getKernelZ(GH);
			LimEntry<>* g;
			for (unsigned int i=0; i<kernel.size(); i++) {
				g = getProductOfElements(G, kernel[i]);
				intersection.push_back(g);
			}
	//        Log::log << "[intersectGroupsZ] found intersection:\n";
	//        printStabilizerGroup(intersection);
			return intersection;
		}

		// Returns a generating set J for the intersection of G and H, so <J>= <G> intersect <H>
		//    J is not necessarily in Column Echelon Form
		//    J may contain elements that are equal up to phase
		// todo verify: does this method work for Pauli groups? it certainly works for Z groups
		// TODO refactor with template parameter NUM_QUBITS
		StabilizerGroup intersectGroupsModuloPhase(const StabilizerGroup& G, const StabilizerGroup& H) {
	//        Log::log << "[intersectGroups mod phase] start  |G|=" << G.size() << "  |H| = " << H.size() << Log::endl;
	//        Log::log << "[intersectGroups mod phase] Group G:\n";
	//        printStabilizerGroup(G);
	//        Log::log << "[intersectGroups mod phase] Group H:\n";
	//        printStabilizerGroup(H);
			StabilizerGroup intersection;
			StabilizerGroup concat = groupConcatenate(G, H);
			std::vector<std::bitset<dd::NUM_QUBITS> > kernel = getKernelModuloPhase(concat);
	//        Log::log << "[intersectGroups mod phase] |kernel| = " << kernel.size() << "\n";
			LimEntry<>* g;
			for (unsigned int i=0; i<kernel.size(); i++) {
				g = getProductOfElements(G, kernel[i]);
				intersection.push_back(g);
			}
	//        Log::log << "[intersectGroups mod phase] Found intersection: \n";
	//        printStabilizerGroup(intersection);

			return intersection;
		}

		StabilizerGroup intersectGroupsPauli(const StabilizerGroup& G, const StabilizerGroup& H) {
			StabilizerGroup intersection = intersectGroupsModuloPhase(G, H);
			// Remove all elements from intersection where the G-phase is not equal to the H-phase
			unsigned int s = intersection.size();
			phase_t phaseG, phaseH;
			unsigned int g = 0;
			for (unsigned int i=0; i<s; i++) {
				phaseG = recoverPhase(G, intersection[g]);
				phaseH = recoverPhase(H, intersection[g]);
				if (phaseG == phaseH) {
					intersection[g]->setPhase(phaseG);
					g++;
				} else {
					// remove this from the intersection
					intersection.pop_back();
				}
			}
			return intersection;
		}

		StabilizerGroup conjugateGroup(const StabilizerGroup& G, const LimEntry<>* a) {
			StabilizerGroup H;
			for (unsigned int i=0; i<G.size(); i++) {
				H.push_back(new LimEntry<>(G[i]));
				if (!H[i]->commutesWith(a)) {
					H[i]->setPhase(multiplyPhases(H[i]->getPhase(), phase_t::phase_minus_one));
				}
			}
			return H;
		}

		template <std::size_t NUM_QUBITS>
		LimEntry<NUM_QUBITS>* getCosetIntersectionElementModuloPhase(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::vector<LimEntry<NUM_QUBITS>*>& H, const LimEntry<NUM_QUBITS>* a) {
			// How do I do this?
			// it's just modulo F2
			std::vector<LimEntry<NUM_QUBITS>*> GH = groupConcatenate(G, H); // TODO memory leak
			std::vector<LimBitset<NUM_QUBITS>*> GH_Id = appendIdentityMatrixBitset(GH); // TODO memory leak
			toColumnEchelonFormModuloPhase(GH_Id);

			std::bitset<NUM_QUBITS> decomposition;   // decomposition of 'a'
			LimBitset<NUM_QUBITS> a_bitset(a);
			// todo refactor this to the GramSchmidt(Group, LimEntry, std::bitset) version instead of the GramSchmidt(Group, LimBitset) version
			a_bitset = GramSchmidt(GH_Id, &a_bitset);
			std::bitset<NUM_QUBITS> decomposition_G, decomposition_H;  // these bitsets are initialized to 00...0, according to the C++ reference
			bitsetCopySegment(decomposition_G, a_bitset.bits, 0, 0, G.size());
			bitsetCopySegment(decomposition_H, a_bitset.bits, 0, G.size(), G.size()+H.size());
			LimEntry<NUM_QUBITS>* a_G = getProductOfElements(G, decomposition_G);
	//        Log::log << "[coset intersection P] got first product. Computing second product.\n"; Log::log.flush();
			LimEntry<NUM_QUBITS>* a_H = getProductOfElements(H, decomposition_H);
			LimEntry<NUM_QUBITS>* a_prime = LimEntry<NUM_QUBITS>::multiply(a_G, a_H);  // TODO memory leak
			if (!LimEntry<NUM_QUBITS>::EqualModuloPhase(a, a_prime)) {
				return LimEntry<NUM_QUBITS>::noLIM;
			}
			return a_G;
		}

		// Given sets G, H which generate Pauli groups <G> and <H>, respectively, and a Pauli string a,
		// Searches for an element in the set '<G> intersect (<H>+a)'
		// Note that '<G>' is a group, and '<H>+a' is a coset
		// If the intersection of these two sets is empty, 'LimEntry<..>::noLIM' is returned
		template <std::size_t NUM_QUBITS>
		LimEntry<NUM_QUBITS>* getCosetIntersectionElementPauli(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::vector<LimEntry<NUM_QUBITS>*>& H, const LimEntry<NUM_QUBITS>* a) {
	//        Log::log << "[coset intersection P] a = " << *a << "\n"; Log::log.flush();
			std::vector<LimEntry<NUM_QUBITS>*> GH = groupConcatenate(G, H);
			assert(GH.size() <= NUM_QUBITS); // todo fix me; Concatenating two StabilizerGroups of size NUM_QUBITS can result in a StabilizerGroups > NUM_QUBITS. This causes an error in line appendIdentityMatrixBitset
			std::vector<LimBitset<NUM_QUBITS>*> GH_Id = appendIdentityMatrixBitset(GH);
			toColumnEchelonFormModuloPhase(GH_Id);
	//        Log::log << "[coset intersection P] Found GH +Id to column echelon mod phase:\n";
	//        printStabilizerGroup(GH_Id);
			std::bitset<NUM_QUBITS> decomposition;   // decomposition of 'a'
	//        Log::log << "[coset intersection P] Doing Gram-Schmidt with GH, a.\n"; Log::log.flush();
			LimBitset<NUM_QUBITS> a_bitset(a);
			// todo refactor this to the GramSchmidt(Group, LimEntry, std::bitset) version instead of the GramSchmidt(Group, LimBitset) version
			a_bitset = GramSchmidt(GH_Id, &a_bitset);
	//        Log::log << "[coset intersection P] after Gram-Schmidt, a_bitset = " << a_bitset << "\n";
	//        Log::log << "[coset intersection P] a.bits[0] = " << a_bitset.bits.test(0) << ", a.bits[1] = " << a_bitset.bits.test(1) << "\n";
	//        Log::log << "[coset intersection P] computing product of elements (GH, decomposition).\n"; Log::log.flush();
	//        LimEntry<NUM_QUBITS>* c = getProductOfElements(GH, decomposition);
	//        Log::log << "[coset intersection P] Computed product of elements.\n"; Log::log.flush();
			std::bitset<NUM_QUBITS> decomposition_G, decomposition_H;  // these bitsets are initialized to 00...0, according to the C++ reference
	//        Log::log << "[coset intersection P] copying bit segment 1...\n"; Log::log.flush();
			bitsetCopySegment(decomposition_G, a_bitset.bits, 0, 0, G.size());
			bitsetCopySegment(decomposition_H, a_bitset.bits, 0, G.size(), G.size()+H.size());
	//        bitsetCopySegment<NUM_QUBITS, 2*NUM_QUBITS+2>(decomposition_G, c->paulis, 0, 2*nqubits, 2*nqubits+G.size());
	//        Log::log << "[coset intersection P] copying bit segment 2...\n"; Log::log.flush();
	//        bitsetCopySegment(decomposition_H, c->paulis, 0, 2*nqubits + G.size(), 2*nqubits+G.size() + H.size());
	//        Log::log << "[coset intersection P] copy successful! Getting product of elements.\n"; Log::log.flush();
			LimEntry<NUM_QUBITS>* a_G = getProductOfElements(G, decomposition_G);
	//        Log::log << "[coset intersection P] got first product. Computing second product.\n"; Log::log.flush();
			LimEntry<NUM_QUBITS>* a_H = getProductOfElements(H, decomposition_H);
			LimEntry<NUM_QUBITS>* a_prime = LimEntry<NUM_QUBITS>::multiply(a_G, a_H);
			phase_t phase_diff = (phase_t) ((a->getPhase() + a_prime->getPhase()) & 0x3);
	//        Log::log << "[coset intersection P] a_G = " << *a_G << "\n";
	//        Log::log << "[coset intersection P] a_H = " << *a_H << "\n";
	//        Log::log << "[coset intersection P] decomposition G = " << decomposition_G << "\n";
	//        Log::log << "[coset intersection P] decomposition H = " << decomposition_H << "\n";
	//        Log::log << "[coset intersection P] aprime = " << *a_prime << "\n"; Log::log.flush();
			// todo replace this check with the more 'elegant' checking whether the vector returned by GramSchmidt, above, is identity modulo phase
			//   that has the advantage that the check can be done earlier
			if (!LimEntry<NUM_QUBITS>::EqualModuloPhase(a, a_prime)) {
				return LimEntry<NUM_QUBITS>::noLIM;
			}
			if (phase_diff == phase_t::phase_one) {
				return a_G;
			}
			else if (phase_diff == phase_t::phase_i || phase_diff == phase_t::phase_minus_i) {
				return LimEntry<NUM_QUBITS>::noLIM;
			}
			// phase_diff must be -1  (i.e., must be phase_t::phase_minus_one)
	//        Log::log << "[coset intersection P] Phase difference is -1. Computing intersection...\n"; Log::log.flush();
			const std::vector<LimEntry<NUM_QUBITS>*> intersection = intersectGroupsModuloPhase(G, H);
			LimEntry<NUM_QUBITS>* k_G;
			LimEntry<NUM_QUBITS>* k_H;
			for (unsigned int i=0; i<intersection.size(); i++) {
				GramSchmidt(G, intersection[i], decomposition_G);
				GramSchmidt(H, intersection[i], decomposition_H);
				k_G = getProductOfElements(G, decomposition_G);
				k_H = getProductOfElements(H, decomposition_H);
				if (((k_G->getPhase() + k_H->getPhase()) & 0x3) == phase_t::phase_minus_one) {
					a_G->multiplyBy(k_G);
					return a_G;
				}
			}
	//        Log::log << "[coset intersection P] no element in coset; returning noLIM.\n"; Log::log.flush();
			return LimEntry<NUM_QUBITS>::noLIM;
		}

		// Given Pauli groups G,H, and Pauli strings a,b, and a phase lambda,
		// Finds an element in the set G intersect lambda a H b,
		// or returns LimEntry::noLIM, if this set is empty
		// TODO refactor to allocate less dynamic memory
		template <std::size_t NUM_QUBITS>
		LimEntry<NUM_QUBITS>* getCosetIntersectionElementPauli(const std::vector<LimEntry<NUM_QUBITS>*>& G, const std::vector<LimEntry<NUM_QUBITS>*>& H, const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b, phase_t lambda, Qubit nQubits = 5) {
			if (lambda == phase_t::no_phase) return LimEntry<NUM_QUBITS>::noLIM;
			// find an element in G intersect abH modulo phase
			LimEntry<NUM_QUBITS>* ab = LimEntry<NUM_QUBITS>::multiply(a, b);
			LimEntry<NUM_QUBITS>* c = getCosetIntersectionElementModuloPhase(G, H, ab);
			if (c == LimEntry<NUM_QUBITS>::noLIM)
				return LimEntry<NUM_QUBITS>::noLIM;
			c->setPhase(recoverPhase(G, c));
			LimEntry<NUM_QUBITS>* acb = LimEntry<NUM_QUBITS>::multiply(a,c);
			acb = LimEntry<NUM_QUBITS>::multiply(acb, b);
			phase_t alpha = multiplyPhases(acb->getPhase(), getPhaseInverse(lambda));
			// Retrieve the phase of acb in H
			phase_t tau = recoverPhase(H, acb);
			Log::log << "[coset intersection] a = " << LimEntry<>::to_string(a, nQubits) << " b = " << LimEntry<>::to_string(b, nQubits) << " c = " << LimEntry<>::to_string(c, nQubits) << " ab = " << LimEntry<>::to_string(ab, nQubits) << " abc = " << LimEntry<>::to_string(acb, nQubits) << " lambda = " << phaseToString(lambda) << " alpha = " << phaseToString(alpha) << " tau = " << phaseToString(tau) << '\n';
			Log::log << "[coset intersection] G = " << groupToString(G, nQubits) << "  H = " << groupToString(H, nQubits) << "\n";
			if (alpha == tau) {
				return c;
			}
			// TODO we should just be able to say 'else', because ALWAYS alpha == -tau in this case.
			//    Check if this conjecture is true.
			else if (alpha == multiplyPhases(tau, phase_t::phase_minus_one)) {
				// See if some element of J has xy = -1
				std::vector<LimEntry<NUM_QUBITS>*> GintersectH = intersectGroupsModuloPhase(G, H);
				for (unsigned int i=0; i<GintersectH.size(); i++) {
					if ((!GintersectH[i]->commutesWith(b)) ^ (recoverPhase(G, GintersectH[i]) != recoverPhase(H, GintersectH[i]))) {
						return LimEntry<NUM_QUBITS>::multiply(c, new LimEntry<NUM_QUBITS>(recoverElement(G, GintersectH[i])));
					}
				}
			}
			return LimEntry<NUM_QUBITS>::noLIM;
		}

		// We assume that only vNodes are passed
		// todo deallocate minus, m
		StabilizerGroup constructStabilizerGeneratorSetZ(const vNode node) {
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
	//            Log::log << "[stab genZ] |0> knife case  n = " << n << ". Low stabilizer group is:\n";
				stabgenset = low.p->limVector; // copies the stabilizer group of the left child
	//            printStabilizerGroup(stabgenset);
				LimEntry<>* idZ = LimEntry<>::getIdentityOperator();
				idZ->setOperator(n, 'Z');
				stabgenset.push_back(idZ);
	//            Log::log << "[stab genZ] Added Z. Now stab gen set is:\n";
	//            printStabilizerGroup(stabgenset);
				// the matrix set is already in column echelon form,
				// so we do not need to perform that step here
			}
			// Case 2: left child is zero
			else if (low.isZeroTerminal()) {
	//            Log::log << "[stab genZ] |1> knife case. n = " << n << ". High stabilizer group is:\n";
				stabgenset = high.p->limVector;
	//            printStabilizerGroup(stabgenset);
				LimEntry<>* minusIdZ = LimEntry<>::getMinusIdentityOperator();
				minusIdZ->setOperator(n, 'Z');
				stabgenset.push_back(minusIdZ);
	//            Log::log << "[stab genZ] Added -Z. now stab gen set is:\n";
	//            printStabilizerGroup(stabgenset);
			}
			// Case 3: the node is a 'fork': both its children are nonzero
			else {
				// Gather the stabilizer groups of the two children
	//            Log::log << "[constructStabilizerGeneratorSet] Case fork n = " << n << ".\n";
				StabilizerGroup* stabLow  = &(low. p->limVector);
				StabilizerGroup* stabHigh = &(high.p->limVector);
				// Step 1: Compute the intersection
				stabgenset = intersectGroupsZ(*stabLow, *stabHigh);

				// Step 2: if some element v is in the set <G> intersect (<H> * -I),
				//   then add Z tensor v to the stabgenset
				LimEntry<>* minus = LimEntry<>::getMinusIdentityOperator();
				LimEntry<>* m = getCosetIntersectionElementPauli(*stabLow, *stabHigh, minus);
				if (m != LimEntry<>::noLIM) {
					m->setOperator(n, 'Z');
					stabgenset.push_back(m);
				}
				toColumnEchelonForm(stabgenset);
				// todo deallocate minus, m
			}

			return stabgenset;
		}

		// Returns an isomorphism between u and v,
		// or LimEntry<>::noLim if u and v are not isomorphic
		// Assumes that the low edges of u and v have an Identity LIM
		// TODO should we add assertions that u and v do not represent zero vectors?
		// TODO this function does not take into account the different phases... but maybe it doesn't need to...
		LimEntry<>* getIsomorphismZ(const vNode* u, const vNode* v) {
			assert( u != nullptr );
			assert( v != nullptr );
	//        Log::log << "[getIsomorphismZ] Start.\n";
			LimEntry<>* iso;
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
	//            Log::log << "[getIsomorphismZ] case u == v.\n"; Log::log.flush();
				// In this case, we return the Identity operator, which is represented by a null pointer
				return nullptr;
			}
			// Case 0.2: The leaf case.
			// TODO this case should already be covered by case 0.1, since in this case v is also the terminal node
			//   Do we need this extra check?
			else if (vNode::isTerminal(u)) {
	//            Log::log << "[getIsomorphismZ] Case u is terminal.\n"; Log::log.flush();
				// Return the identity operator, which is represented by a null pointer
				return nullptr;
			}
			// Case 1 ("Left knife"): Left child is nonzero, right child is zero
			else if (uHigh.isZeroTerminal()) {
	//            Log::log << "[getIsomorphismZ] Case uHigh is terminal\n";
				if (!vHigh.isZeroTerminal()) return LimEntry<>::noLIM;
				if (uHigh.p != vHigh.p) return LimEntry<>::noLIM;
				return LimEntry<>::multiply(*uHigh.l, *vHigh.l);
			}
			// Case 2 ("Right knife"): Left child is zero, right child is nonzero
			else if (uLow.isZeroTerminal()) {
	//            Log::log << "[getIsomorphismZ] case uLow is terminal.\n";
				if (!vLow.isZeroTerminal()) return LimEntry<>::noLIM; // not isomorphic
				if (uLow.p != vLow.p) return LimEntry<>::noLIM;
				return nullptr;  // return the Identity isomorphism
			}
			// Case 3 ("Fork"): Both children are nonzero
			else {
	//            Log::log << "[getIsomorphismZ] case Fork.\n"; Log::log.flush();
	//            Log::log << "[getIsomorphismZ] ulw " << uLow.w << " uhw " << uHigh.w << " vlw " << vLow.w << " vhw " << vHigh.w << Log::endl;
				// Step 1.2: check if the amplitudes satisfy uHigh = -1 * vHigh
				bool amplitudeOppositeSign = uHigh.w.approximatelyEqualsMinus(vHigh.w);
				// Step 1.1:  check if the amplitudes are equal, up to a sign
				if (!uLow.w.approximatelyEquals(vLow.w) || (!uHigh.w.approximatelyEquals(vHigh.w) && !amplitudeOppositeSign)) return LimEntry<>::noLIM;
	//            Log::log << "[getIsomorphismZ] edge weights are approximately equal.\n"; Log::log.flush();
				// Step 2: Check if nodes u and v have the same children
				if (uLow.p != vLow.p || uHigh.p != vHigh.p) return LimEntry<>::noLIM;
	//            Log::log << "[getIsomorphismZ] children of u and v are the same nodes.\n"; Log::log.flush();
				// Step 3: (optional) check if the automorphism groups are equal
	//            if (!stabilizerGroupsEqual(u->limVector, v->limVector)) {
	//                return LimEntry<>::noLIM;
	//            }
	//            Log::log << "[getIsomorphismZ] the stabilizer Groups of u and v are equal.\n"; Log::log.flush();
				// Step 4: If G intersect (H+isoHigh) contains an element P, then Id tensor P is an isomorphism
				LimEntry<>* isoHigh = LimEntry<>::multiply(uHigh.l, vHigh.l);
	//            Log::log << "[getIsomorphismZ] multiplied high isomorphisms:" << LimEntry<>::to_string(isoHigh) << ".\n"; Log::log.flush();
				if (amplitudeOppositeSign) {
	//                Log::log << "[getIsomorphismZ] multiplying Phase by -1 because high amplitudes had opposite signs\n"; Log::log.flush();
					isoHigh->multiplyPhaseBy(phase_t::phase_minus_one); // multiply by -1
				}
				iso = getCosetIntersectionElementPauli(uLow.p->limVector, uHigh.p->limVector, isoHigh);
	//            Log::log << "[getIsomorphismZ] completed coset intersection element.\n"; Log::log.flush();
				if (iso != LimEntry<>::noLIM) {
	//                Log::log << "[getIsomorphismZ] The coset was non-empty; returning element.\n"; Log::log.flush();
					return iso;
				}
				// Step 5: If G intersect (H-isomorphism) contains an element P, then Z tensor P is an isomorphism
	//            Log::log << "[getIsomorphismZ] multiplying phase by -1.\n"; Log::log.flush();
				isoHigh->multiplyPhaseBy(phase_t::phase_minus_one);
				iso = getCosetIntersectionElementPauli(uLow.p->limVector, uHigh.p->limVector, isoHigh);
	//            Log::log << "[getIsomorphismZ] found coset intersection element.\n"; Log::log.flush();
				if (iso != LimEntry<>::noLIM) {
	//                Log::log << "[getIsomorphismZ] Coset was not empty; returning result.\n"; Log::log.flush();
					iso->setOperator(u->v, pauli_op::pauli_z); // TODO should we do this? write a test
					return iso;
				}
				else {
	//                Log::log << "[getIsomorphismZ] Coset was empty; returning -1.\n"; Log::log.flush();
					return LimEntry<>::noLIM;
				}
			}
		}

		// Assumes that u and v are semi-reduced:
		// - low edge label is identity
		// TODO take the edge weights into account:
		//    in case 3.1
		//    in knife cases
		//    check if uhigh.w = 1 / vhigh.w
		void getIsomorphismPauli(const vNode* u, const vNode* v, ComplexNumbers& cn, LimWeight<>& iso, bool& foundIsomorphism) {
			assert( u != nullptr );
			assert( v != nullptr );
	//        Log::log << "[getIsomorphismPauli] Start. states have " << (int) u->v+1 << " qubits.\n";
			assert (u->v == v->v);  // Assert u and v have the same nubmer of qubits
			foundIsomorphism = false;
			Edge<vNode> uLow  = u->e[0];
			Edge<vNode> uHigh = u->e[1];
			Edge<vNode> vLow  = v->e[0];
			Edge<vNode> vHigh = v->e[1];
			// Assert that neither u nor v is the Zero vector
			assert (!(uLow.isZeroTerminal() && uHigh.isZeroTerminal()));
			assert (!(vLow.isZeroTerminal() && vHigh.isZeroTerminal()));
			Log::log << "[getIsomorphismPauli] Start. u = {" << uLow.w << " * " <<  LimEntry<>::to_string(uLow.l, uLow.p->v) << ", " << uHigh.w << " * "
					 << LimEntry<>::to_string(uHigh.l, uHigh.p->v) << "}   v = {"
					 << vLow.w << " * " << LimEntry<>::to_string(vLow.l, vLow.p->v) << ", "
					 << vHigh.w << " * " << LimEntry<>::to_string(vHigh.l, vHigh.p->v) << "}\n";
	//        Log::log << "[getIsomorphismPauli] u = " << u << "   v = " << v << '\n';
	//        Log::log << "[getIsomorphismPauli] uLow = " << uLow.p << "   uHigh = " << uHigh.p << '\n';
			if (!LimEntry<>::isIdentityOperator(uLow.l))
				throw std::runtime_error("[getIsomorphismPauli] ERROR low edge of u does not have identity label.\n");
			if (!LimEntry<>::isIdentityOperator(vLow.l))
				throw std::runtime_error("[getIsomorphismPauli] ERROR low edge of v does not have identity label\n");
			auto zeroU = std::array{u->e[0].w.approximatelyZero(), u->e[1].w.approximatelyZero()};
			auto zeroV = std::array{v->e[0].w.approximatelyZero(), v->e[1].w.approximatelyZero()};

			iso.lim = new LimEntry<>();

			// Case 0: the nodes are equal
			if (u == v) {
				Log::log << "[getIsomorphismPauli] case u == v.\n"; Log::log.flush();
				// In this case, we return the Identity operator, which is represented by a null pointer
				iso.lim->setToIdentityOperator();
				foundIsomorphism = true;
			}
			// Case 1 ("Left knife"): Left child is nonzero, right child is zero
			else if (zeroU[1]) {
				Log::log << "[getIsomorphismPauli] Case |u> = |0>|u'>, since uHigh is zero\n";
				if (zeroV[1]) {
					if (uLow.p == vLow.p) {
	//            		iso = new LimWeight<>((LimEntry<>*)nullptr);
						iso.lim->setToIdentityOperator();
						foundIsomorphism = true;
					}
				}
				else if (zeroV[0]) {
					if (uLow.p == vHigh.p) {
						// TODO limdd inspect weight on high edge
						*iso.lim = vHigh.l;
						iso.lim->setOperator(u->v, 'X');
						foundIsomorphism = true;
					}
				}
			}
			// Case 2 ("Right knife"): Left child is zero, right child is nonzero
			else if (zeroU[0]) {
				Log::log << "[getIsomorphismPauli] case uLow is zero, so |u> = |1>|u'>.\n";
				if (zeroV[0]) {
					// TODO limdd inspect weights
					if (uHigh.p == vHigh.p) {
						*iso.lim = uHigh.l;
						iso.lim->multiplyBy(vHigh.l);
						foundIsomorphism = true;
					}
				}
				else if (zeroV[1]) {
					// TODO limdd inspect weights
					if (uHigh.p == vLow.p) {
						*iso.lim = uHigh.l;
						iso.lim->setOperator(u->v, 'X');
						foundIsomorphism = true;
					}
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
					Log::log << "[getIsomorphismPauli] case 3.1: children of nodes are opposite pair. Qubits: " << (int)(u->v) << "\n";
					// TODO refactor this piece of code which swaps two edges
					vNode uPrime;
					uPrime.v = u->v;
					uPrime.limVector = u->limVector;
					uPrime.e[0]   = u->e[1];
					uPrime.e[0].l = nullptr;
					uPrime.e[0].w = u->e[1].w;
					uPrime.e[1]   = u->e[0];
					uPrime.e[1].l = u->e[1].l;
					uPrime.e[1].w = u->e[0].w;
					getIsomorphismPauli(&uPrime, v, cn, iso, foundIsomorphism);
					if (!foundIsomorphism) return;
					LimEntry<> X = *(u->e[1].l);
					X.setOperator(u->v, pauli_op::pauli_x);
					iso.lim->multiplyBy(X);
					foundIsomorphism = true;
					return;
				}
				// Case 3.2: uLow == vLow and uHigh == vHigh
				// Step 1.1: Check if uLow == vLow and uHigh == vHigh, i.e., check if nodes u and v have the same children
				if (uLow.p != vLow.p || uHigh.p != vHigh.p) {
					foundIsomorphism = false;
					return;
				}
				// TODO should we refactor this last part and just call getIsomorphismZ?
				//      we could refactor ONLY this last part, and thereby make both this and the getIsomorphismZ functions more readable
				if (uLow.p == uHigh.p) {
					// TODO cover this case
				}

				// Step 1.2: check if the weights satisfy uHigh = -1 * vHigh
				Complex rhoU        = cn.getCached();  // Eventually returned to cache
				Complex rhoV        = cn.getCached();  // Eventually returned to cache
				Complex rhoVdivRhoU = cn.getCached();
				ComplexNumbers::div(rhoU, u->e[1].w, u->e[0].w);
				ComplexNumbers::div(rhoV, v->e[1].w, v->e[0].w);
				ComplexNumbers::div(rhoVdivRhoU, rhoV, rhoU); // TODO it suffices to allocate only two cached Complex objects
				phase_t lambda = rhoVdivRhoU.toPhase();

				cn.returnToCache(rhoVdivRhoU);
				cn.returnToCache(rhoV);
				cn.returnToCache(rhoU);
				if (lambda == phase_t::no_phase) {
					Log::log << "[getIsomorphismPauli] Edge weights differ by a factor " << rhoVdivRhoU << " != +/- 1,i so returning noLIM.\n";
					foundIsomorphism = false;
					return;
				}
				Log::log << "[getIsomorphismPauli] edge weights differ by a factor " << phaseToString(lambda) << ".\n";

				iso.weight = cn.divCached(v->e[0].w, u->e[0].w);
	//            ComplexNumbers::div(iso.weight, v->e[0].w, u->e[0].w);

	//            Log::log << "[getIsomorphismPauli] uLow.p->limVector  = "; printStabilizerGroup(uLow.p->limVector, uLow.p->v); Log::log << '\n';
	//            Log::log << "[getIsomorphismPauli] uHigh.p->limVector = "; printStabilizerGroup(uHigh.p->limVector, uHigh.p->v); Log::log << '\n';
				LimEntry<>* temp = getCosetIntersectionElementPauli(uLow.p->limVector, uHigh.p->limVector, v->e[1].l, u->e[1].l, lambda, u->v);
				if (temp != LimEntry<>::noLIM) {
					*iso.lim = *temp;
					foundIsomorphism = true;
	//                Log::log << "[getIsomorphismPauli] Found coset intersection element " << LimEntry<>::to_string(iso->lim, u->v) << '\n';
					return;
				}
				Log::log << "[getIsomorphismPauli] Coset was empty; so no isomorphism starts with Id.\n";
				// Step 3: If G intersect (H-isomorphism) contains an element P, then Z tensor P is an isomorphism
				Log::log << "[getIsomorphismPauli] multiplying phase by -1.\n"; Log::log.flush();
				lambda = multiplyPhases(lambda, phase_t::phase_minus_one);
				temp = getCosetIntersectionElementPauli(uLow.p->limVector, uHigh.p->limVector, v->e[1].l, u->e[1].l, lambda, u->v);
				if (temp != LimEntry<>::noLIM) {
					*iso.lim = *temp;
					iso.lim->setOperator(u->v, pauli_op::pauli_z);
					foundIsomorphism = true;
					Log::log << "[getIsomorphismPauli] Coset was not empty; returning result.\n"; Log::log.flush();
				}
				else {
					Log::log << "[getIsomorphismPauli] Coset was empty; returning noLIM.\n"; Log::log.flush();
				}
			}
		}

	//    static LimWeight<>* getIsomorphismPauliBruteForce(const vNode* u, const vNode* v, ComplexNumbers& cn) {
	//    	Edge<vNode> eu{u, Complex::one, nullptr};
	//    	Edge<vNode> ev{v, Complex::one, nullptr};
	//    	unsigned int nqubits = u->v;
	//    	LimEntry<> iso;
	//    	unsigned int isoNum;
	//    	CVec uVec(1ULL << (2*nqubits), 0);
	//    	CVec vVec(1ULL << (2*nqubits), 0);
	//    	for (isoNum = 0; isoNum < 1ULL << (2*nqubits); isoNum++) {
	//    		for (unsigned i=0; i<2nqubits; i++) {
	//    			iso.paulis.set(i, (isoNum & (0x1 << i)) >> i);
	//    		}
	//    		// TODO call getVector
	//    	}
	//    	return nullptr;
	//    }

		// Choose the label on the High edge, in the Z group
		LimEntry<>* highLabelZ(const vNode* u, const vNode* v, LimEntry<>* vLabel, Complex& weight, bool& s) {
			// We assert that the LIM has phase +1  (we expect normalizeLIMDD to guarantee this)
			assert(LimEntry<>::getPhase(vLabel) == phase_t::phase_one);
	//        Log::log << "[highLabelZWeight] Start; |Gu| = " << u->limVector.size() << " |Gv| = " << v->limVector.size() << ".\n"; Log::log.flush();
			StabilizerGroup GH = groupConcatenate(u->limVector, v->limVector);
	//        Log::log << "[highLabelZWeight] Concatenated; |GH| = " << GH.size() << Log::endl;
			toColumnEchelonForm(GH);
	//        Log::log << "[highLabelZWeight] to CEF'ed; now |GH| = " << GH.size() << Log::endl;
			LimEntry<>* newHighLabel = GramSchmidt(GH, vLabel);
			// Set the new phase to +1
			newHighLabel->setPhase(phase_t::phase_one);
			s = false;
			if (weight.lexLargerThanxMinusOne()) {
	//            Log::log << "[highLabelZWeight] Multiplying weight by -1, since weight = " << weight << ".\n";
				weight.multiplyByMinusOne(true);
				s = true;
			}
	//        Log::log << "[highLabelZWeight] end.\n"; Log::log.flush();
			return newHighLabel;
		}

		// Finds a high label for a node with low child u and high child v, with current high edge label vLabel, and current high LIM vLabel
		// Sets the object 'highLabel' to the new label
		// Here we demand that 'weight' and 'weightInv' are retrieved with ComplexTable.getTemporary(..),
		// since they will be assigned values but will not be looked up in the ComplexTable
		// TODO limdd:
		//   1. make NUM_QUBITS a template parameter
		void highLabelPauli(const vNode* u, const vNode* v, LimEntry<>* vLabel, Complex& weight, LimEntry<>& highLabel) {
			Log::log << "[highLabelPauli] weight * lim = " << weight << " * " << *vLabel << '\n';
			if (u == v) {
				Log::log << "[highLabelPauli] stabgenset is: " << groupToString(u->limVector, u->v) << '\n';
				highLabel = *GramSchmidt(u->limVector, vLabel);
				weight.multiplyByPhase(highLabel.getPhase());
				Log::log << "[highLabelPauli] case u = v; canonical lim is " << LimEntry<>::to_string(&highLabel, u->v) << " so multiplying weight by " << phaseToString(highLabel.getPhase()) << ", result: weight = " << weight << '\n';
				highLabel.setPhase(phase_t::phase_one);
				if (CTEntry::val(weight.r) < 0 || (CTEntry::approximatelyEquals(weight.r, &ComplexTable<>::zero) && CTEntry::val(weight.i) < 0)) {
					weight.multiplyByMinusOne(true);
					Log::log << "[highLabelPauli] the high edge weight is flipped. New weight is " << weight << ".\n";
				}
			}
			else {
				Log::log << "[highLabelPauli] stabgenset is: " << groupToString(u->limVector, u->v) << '\n';
				StabilizerGroup GH = groupConcatenate(u->limVector, v->limVector);
				toColumnEchelonForm(GH);
				highLabel = *GramSchmidt(GH, vLabel);
				weight.multiplyByPhase(highLabel.getPhase());
				Log::log << "[highLabelPauli] Found canonical label: " << LimEntry<>::to_string(&highLabel, u->v) << ", so multiplying weight by " << phaseToString(highLabel.getPhase()) << ", result: weight = " << weight << '\n';
				highLabel.setPhase(phase_t::phase_one);
				if (weight.lexSmallerThanxMinusOne()) {
					Log::log << "[highLabelPauli] before multiplication by -1 for canonicity, weight = " << weight << "\n";
					weight.multiplyByMinusOne(true);
					Log::log << "[highLabelPauli] Multiplied high edge weight by -1; New weight is " << weight << ".\n";
				}
			}
		}

		// Returns the lexicographically smallest LIM R such that R * |v> == lim * |v>
		// This is useful when a canonical edge is needed for a cache entry
		// TODO do we need to left-multiply in GramSchmidt, or right-multiply?
		//   I think right-multiply, but we should check this
		LimEntry<>* getRootLabel(const vNode* v, const LimEntry<>* lim) {
			return GramSchmidt(v->limVector, lim);
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

} // namespace dd
#endif //DDPACKAGE_PAULIALGEBRA_HPP
