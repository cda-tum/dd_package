#ifndef DDPACKAGE_PAULIUTILITIES_HPP
#define DDPACKAGE_PAULIUTILITIES_HPP

#include "Definitions.hpp"
#include "LimTable.hpp"

namespace dd {

    //namespace Pauli {

    //}

    typedef std::vector<LimEntry<>*> StabilizerGroup;

    template<std::size_t N, std::size_t M>
    inline void bitsetCopySegment(std::bitset<N>& x, const std::bitset<M> y, unsigned int begin_x, unsigned int begin_y, unsigned int end_y) {
        assert(end_y <= M);
        for (unsigned int i = begin_y; i < end_y; i++) {
            x.set(i + begin_x - begin_y, y.test(i));
        }
    }

    inline phase_t multiplyPhases(phase_t a, phase_t b) {
        //	short x = (short) a;
        //	short y = (short) b;
        //	short xy = ((x & 0x1) ^ (y & 0x1)) | ((x & 0x2) ^ (y & 0x2) ^ ((x & y & 0x1) << 1));
        //	return (phase_t) xy;
        return (phase_t)(((int)a + (int)b) & 0x3);
    }

    inline phase_t getPhaseInverse(phase_t a) {
        //    	int A = (int) a;
        //    	A = (A & 0x1) | ( ((A&1) << 1) ^ (A&2) );
        //    	return (phase_t) A;
        return (phase_t)((4 - (int)a) & 0x3);
    }

    inline phase_t getPhaseaMinusB(phase_t a, phase_t b) {
        phase_t minb = getPhaseInverse(b);
        return (phase_t)((a + minb) & 0x3);
    }

    inline std::string phaseToString(phase_t a) {
        switch (a) {
            case phase_t::phase_one:
                return "+1";
            case phase_t::phase_i:
                return "i";
            case phase_t::phase_minus_one:
                return "-1";
            case phase_t::phase_minus_i:
                return "-i";
            case phase_t::no_phase:;
        }
        return "(no phase)";
    }

    // Returns whether the two groups have the same vector of generators
    // Note that, mathematically speaking, two generator sets G and H can still generate the same groups,
    // even if they have different orders
    inline bool stabilizerGroupsEqual(const StabilizerGroup& G, const StabilizerGroup& H) {
        //        Log::log << "[stabilizerGroupsEqual] start.\n";  Log::log.flush();
        if (G.size() != H.size()) return false;
        for (unsigned int i = 0; i < G.size(); i++) {
            if (G[i]->operator!=(*H[i])) return false;
        }
        //        Log::log << "[stabilizerGroupsEqual] groups are equal.\n"; Log::log.flush();
        return true;
    }

    // Returns whether the group G is sorted descending,
    // i.e., whether all the zeros are in the top right quadrant
    inline bool stabilizerGroupIsSorted(const StabilizerGroup& G) {
        for (unsigned int i = 0; i + 1 < G.size(); i++) {
            if (LimEntry<>::leneq(G[i], G[i + 1]))
                return false;
        }
        return true;
    }

    inline void printStabilizerGroup(const StabilizerGroup& G) {
        Log::log << "Stabilizer group (" << G.size() << " elements)\n";
        for (unsigned int i = 0; i < G.size(); i++) {
            Log::log << LimEntry<>::to_string(G[i]) << Log::endl;
        }
    }

    inline void printStabilizerGroup(const StabilizerGroup& G, unsigned int nQubits) {
        Log::log << "Stabilizer group (" << G.size() << " elements) = {";
        for (unsigned int i = 0; i < G.size(); i++) {
            Log::log << LimEntry<>::to_string(G[i], nQubits) << ", ";
        }
        Log::log << "}";
    }

    template<std::size_t NUM_QUBITS>
    inline void printStabilizerGroup(const std::vector<LimBitset<NUM_QUBITS>*>& G) {
        if (G.size() == 0) {
            Log::log << "  (empty group)\n";
        }
        for (unsigned int i = 0; i < G.size(); i++) {
            Log::log << *G[i] << Log::endl;
            Log::log.flush();
        }
    }

    template<std::size_t NUM_QUBITS>
    inline void printKernel(const std::vector<std::bitset<NUM_QUBITS>>& kernel) {
        for (unsigned int i = 0; i < kernel.size(); i++) {
            for (unsigned int j = 0; j < NUM_QUBITS; j++) {
                Log::log << kernel[i].test(j);
            }
            Log::log << '\n';
        }
    }

    inline std::string groupToString(const StabilizerGroup& G, Qubit nQubits) {
        std::stringstream ss;
        ss << "Group (" << G.size() << " elements) = {";
        for (unsigned int i = 0; i < G.size(); i++) {
            ss << LimEntry<>::to_string(G[i], nQubits) << ", ";
        }
        ss << "}";
        return ss.str();
    }

    inline StabilizerGroup groupConcatenate(const StabilizerGroup& G, const StabilizerGroup& H) {
        StabilizerGroup concat = G;
        for (unsigned int i = 0; i < H.size(); i++) {
            concat.push_back(H[i]);
        }
        return concat;
    }

    template<std::size_t NUM_QUBITS>
    inline std::vector<LimBitset<NUM_QUBITS>*> appendIdentityMatrixBitset(const std::vector<LimEntry<NUM_QUBITS>*>& G) {
        std::vector<LimBitset<NUM_QUBITS>*> GI;
        LimBitset<NUM_QUBITS>*              col;
        for (unsigned int i = 0; i < G.size(); i++) {
            col      = new LimBitset<NUM_QUBITS>();
            col->lim = *G[i];
            col->bits.set(i, 1);
            GI.push_back(col);
        }
        return GI;
    }

    template<std::size_t NUM_QUBITS>
    inline std::vector<LimBitset<2*NUM_QUBITS>*> appendIdentityMatrixBitsetBig(const std::vector<LimEntry<NUM_QUBITS>*>& G) {
        std::vector<LimBitset<2*NUM_QUBITS>*> GI;
        LimBitset<2*NUM_QUBITS>*              col;
        for (unsigned int i = 0; i < G.size(); i++) {
            col      = new LimBitset<2*NUM_QUBITS>();
            col->lim = *G[i];
            col->bits.set(i, 1);
            GI.push_back(col);
        }
        return GI;
    }

    // TODO this procedure should reduce the refcount of the LimEntry objects it removes from G
    //   or should deallocate these objects in some other way
    template<std::size_t NUM_QUBITS>
    inline void pruneZeroColumns(std::vector<LimEntry<NUM_QUBITS>*>& G) {
        unsigned int i = 0;
        while (i < G.size()) {
            if (G[i]->isAllZeroVector()) {
                // Remove this all-zero vector from the matrix
                // Step 1: replace it with the last vector in the matrix
                G[i] = G[G.size() - 1];
                G.pop_back();
            } else {
                i++;
            }
        }
    }

    template<std::size_t NUM_QUBITS>
    inline void pruneZeroColumns(std::vector<LimBitset<NUM_QUBITS>*>& G) {
        unsigned int i = 0;
        while (i < G.size()) {
            if (G[i]->lim.isAllZeroVector()) {
                // Remove this all-zero vector from the matrix
                // Step 1: replace it with the last vector in the matrix
                G[i] = G[G.size() - 1];
                G.pop_back();
            } else {
                i++;
            }
        }
    }

    template<std::size_t NUM_QUBITS>
    inline void pruneZeroColumnsModuloPhase(std::vector<LimBitset<NUM_QUBITS>*>& G) {
        unsigned int i = 0;
        while (i < G.size()) {
            if (G[i]->lim.isIdentityModuloPhase()) {
                // Remove this all-zero vector from the matrix
                // Step 1: replace it with the last vector in the matrix
                G[i] = G[G.size() - 1];
                G.pop_back();
            } else {
                i++;
            }
        }
    }

} // namespace dd
#endif
