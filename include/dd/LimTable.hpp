#ifndef DDPACKAGE_LIMTABLE_HPP
#define DDPACKAGE_LIMTABLE_HPP

#include "Definitions.hpp"

#include <array>
#include <bitset>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

// todo two of the bits should be reserved for the phase, which is one of +1, +i, -1, -i
namespace dd {

    template<std::size_t NUM_QUBITS = dd::NUM_QUBITS>
    struct LimEntry {
        static_assert(NUM_QUBITS > 0, "Have at least one qubit");
        static_assert(NUM_QUBITS <= std::numeric_limits<dd::Qubit>::max(), "Too many qubits for LimEntry");

        // We use -1 to indicate 'no LIM found', since the nullptr is reserved for the Identity operator
        static LimEntry<NUM_QUBITS>* noLIM; // value is -1

        constexpr static std::size_t NUM_BITSETBITS = 2 * NUM_QUBITS + 2;
        std::bitset<NUM_BITSETBITS>  paulis{};
        LimEntry*                    next{};
        RefCount                     refCount{};

        // explicit definition of constructors
        LimEntry():
            paulis{0} {}
        explicit LimEntry(std::bitset<NUM_BITSETBITS> paulis):
            paulis{paulis} {}
        explicit LimEntry(std::string pauliString):
            paulis{0} {
            paulis = bitsetFromString(pauliString);
        }
        explicit LimEntry(const LimEntry<NUM_QUBITS>* l) {
            if (l != nullptr && l != noLIM)
                paulis = l->paulis;
        }

        static std::bitset<NUM_BITSETBITS> bitsetFromString(std::string pauliString) {
            std::bitset<NUM_BITSETBITS> res{0};
            if (pauliString.size() == 0) return res;
            std::string::size_type i = 0;  // iterates over the checkvector 'res'
            std::size_t cursor = 0;        // iterates over 'pauliString'
            // Step 1: process the phase in front of the string: either "-",  "i",  or "-i"
            if (pauliString[0] == '-') {
                if (pauliString.size() >= 2 && pauliString[1] == 'i') {
                    // Set phase -i
                    res.set(NUM_BITSETBITS-1, (phase_t::phase_minus_i & 0x2) >> 1);
                    res.set(NUM_BITSETBITS-2,  phase_t::phase_minus_i & 0x1);
                    cursor = 2;  // Start at the character at position 2, skipping the characters '-i'
                }
                else {
                    res.set(NUM_BITSETBITS-1, (phase_t::phase_minus_one & 0x2) >> 1);
                    res.set(NUM_BITSETBITS-2,  phase_t::phase_minus_one & 0x1);
                    cursor = 1;  // Start at the character at position 1, skipping the character '-'
                }
            }
            else if (pauliString[0] == 'i') {
                res.set(NUM_BITSETBITS-1, (phase_t::phase_i & 0x2) >> 1);
                res.set(NUM_BITSETBITS-2,  phase_t::phase_i & 0x1);
                cursor = 1; // Start at character 1, skipping the character 'i' that indicated the phase
            }
            // Step 2: Process all the qubits
            for (; cursor < pauliString.size() && i < NUM_QUBITS; cursor++) {
                switch (pauliString[cursor]) {
                    case 'I':
                        res[2 * i    ] = 0;
                        res[2 * i + 1] = 0;
                        break;
                    case 'X':
                        res[2 * i    ] = 0;
                        res[2 * i + 1] = 1;
                        break;
                    case 'Z':
                        res[2 * i    ] = 1;
                        res[2 * i + 1] = 0;
                        break;
                    case 'Y':
                        res[2 * i    ] = 1;
                        res[2 * i + 1] = 1;
                        break;
                    default:
                        throw std::runtime_error("Unrecognized symbol in Pauli string\n");
                }
                i++;
            }
            return res;
        }

        /**
         * 2 bits per qubit
         * 00 identity
         * 01 Pauli-Z
         * 10 Pauli-X
         * 11 Pauli-Y
         *
         * @param qubit
         * @return char of {I, X, Y, Z}
         */
        [[nodiscard]] char getQubit(dd::Qubit qubit) const {
            // todo return a pauli_t
            if(qubit == -1){
                // Reached terminal
                return 'I';
            }
            if (!paulis.test(2 * qubit + 1) && !paulis.test(2 * qubit)) {
                return 'I';
            } else if (!paulis.test(2 * qubit + 1) && paulis.test(2 * qubit)) {
                return 'Z';
            } else if (paulis.test(2 * qubit + 1) && !paulis.test(2 * qubit)) {
                return 'X';
            } else {
                return 'Y';
            }
        }

        static char getQubit(const LimEntry<NUM_QUBITS>* lim, dd::Qubit qubit) {
            if (lim == nullptr) {
                return 'I';
            }
            if (lim == noLIM) return 'I';
            return lim->getQubit(qubit);
        }

        phase_t getPhase() const {
            int phase = ((int) paulis.test(2*NUM_QUBITS)) | ((int) paulis.test(2*NUM_QUBITS+1) << 1);
            return (phase_t) phase;
        }

        // returns the phase of the LIM, in two bits, which have the following meaning:
        // 00: +1    01: i    10: -1    11: -i
        static phase_t getPhase(const LimEntry<NUM_QUBITS>* l) {
            if (l == nullptr) return phase_t::phase_one;
            if (l == noLIM) return phase_t::phase_one;
            return l->getPhase();
//            uint32_t phase = (l->paulis.test(2*NUM_QUBITS)) | (l->paulis.test(2*NUM_QUBITS+1) << 1);
//            return phase;
        }

        void setPhase(char newPhase) {
            paulis.set(2*NUM_QUBITS, (char) 0x1 & newPhase);
            paulis.set(2*NUM_QUBITS+1, (char) 0x2 & newPhase);
        }

        /**
         * @return a string of {I, X, Y, Y}**n with left in the string corresponding to the top of the decision diagram.
         */
        static std::string to_string(const LimEntry<NUM_QUBITS>* lim) {
            if (lim == nullptr) {
                return std::string(NUM_QUBITS, 'I');
            }
            if (lim == noLIM) {
                return "(no LIM)";
            }

            std::ostringstream os;
            // Write the phase
            if (!lim->paulis.test(NUM_BITSETBITS-1) &&  lim->paulis.test(NUM_BITSETBITS-2)) {
                os << 'i';
            }
            if ( lim->paulis.test(NUM_BITSETBITS-1) && !lim->paulis.test(NUM_BITSETBITS-2)) {
                os << '-';
            }
            if ( lim->paulis.test(NUM_BITSETBITS-1) &&  lim->paulis.test(NUM_BITSETBITS-2)) {
                os << "-i";
            }
            // Write the Pauli operators
            for (unsigned int i = 0; i < NUM_QUBITS; i++) {
                os << getQubit(lim, i);
            }
            return os.str();
        }

        // Prints operators [0, ... , nQubits], i.e., including index 'nQubits'
        static std::string to_string(const LimEntry<NUM_QUBITS>* lim, Qubit nQubits) {
//        	Log::log << "[to_string] outputting LIM " << to_string(lim) << " on " << nQubitsInt << " qubits.\n"; Log::log.flush();
        	if (nQubits < 0) {
            	if (lim == nullptr) {
                    return "1";
            	}
	            if (!lim->paulis.test(NUM_BITSETBITS-1) && !lim->paulis.test(NUM_BITSETBITS-2)) {
	                return "1";
	            }
	            if (!lim->paulis.test(NUM_BITSETBITS-1) &&  lim->paulis.test(NUM_BITSETBITS-2)) {
	                return "i";
	            }
	            if ( lim->paulis.test(NUM_BITSETBITS-1) && !lim->paulis.test(NUM_BITSETBITS-2)) {
	                return "-";
	            }
	            if ( lim->paulis.test(NUM_BITSETBITS-1) &&  lim->paulis.test(NUM_BITSETBITS-2)) {
	                return "-i";
	            }
				return "";
        	}
        	if (lim == nullptr) {
                return std::string(nQubits+1, 'I');
        	}
            if (lim == noLIM) {
                return "(no LIM)";
            }

            std::ostringstream os;
            // Write the phase
            if (!lim->paulis.test(NUM_BITSETBITS-1) &&  lim->paulis.test(NUM_BITSETBITS-2)) {
                os << 'i';
            }
            if ( lim->paulis.test(NUM_BITSETBITS-1) && !lim->paulis.test(NUM_BITSETBITS-2)) {
                os << '-';
            }
            if ( lim->paulis.test(NUM_BITSETBITS-1) &&  lim->paulis.test(NUM_BITSETBITS-2)) {
                os << "-i";
            }
            // Write the Pauli operators
			for (int i = 0; i <= (int) nQubits; i++) {
				os << getQubit(lim, i);
			}
            return os.str();
        }

        // TODO: static versions as well to cover nullptr case?
        bool operator==(const LimEntry<NUM_QUBITS>& other) const {
            return paulis == other.paulis;
        }
        bool operator!=(const LimEntry<NUM_QUBITS>& other) const {
            //todo shouldn't it be enough to define the == operator?
            return paulis != other.paulis;
        }

        // Returns whether two LIMs are equal.
        // Handles the nullptr case: a nullptr is interpreted as the Identity operator
        static bool Equal(const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b) {
            if (a == noLIM) return b == noLIM;
            if (b == noLIM) return false;
//            if (a == nullptr && b == nullptr) return true;
//            if (a == nullptr || b == nullptr) return false;
            if (isIdentityOperator(a) && isIdentityOperator(b)) return true;
            if (a == nullptr) return false;
            if (b == nullptr) return false;
            return (*a == *b);
        }

        static bool EqualModuloPhase(const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b) {
            assert(a != noLIM && b != noLIM);
            if (a == nullptr) {
                return isIdentityOperator(b);
            }
            if (b == nullptr) {
                return isIdentityOperator(a);
            }
            // check whether the first 2*NUM_QUBITS bits are equal
            for (unsigned int i=0; i<2*NUM_QUBITS; i++) {
                if (a->paulis.test(i) != b->paulis.test(i)) {
                    return false;
                }
            }
            return true;
        }

        // Returns whether this vector is the identity operator, i.e., has all bits set to zero
        // TODO limdd: there is probably a faster way to check whether a bitvector is all-zero,
        //   using bit tricks supported by the std::array data structure. --Lieuwe
        bool isAllZeroVector() const {
            for (unsigned int i=0; i<NUM_BITSETBITS; i++) {
                if (paulis.test(i)) return false;
            }
            return true;
        }

        bool isIdentityOperator() const {
            return isAllZeroVector();
        }

        static bool isIdentityOperator(const LimEntry<NUM_QUBITS>* l) {
            assert(l != noLIM);
            if (l == nullptr) return true;
            return l->isIdentityOperator();
        }

        bool isIdentityModuloPhase() const {
            for (unsigned int i=0; i<2*NUM_QUBITS; i++) {
                if (paulis.test(i)) return false;
            }
            return true;
        }

        static bool isIdentityModuloPhase(const LimEntry<NUM_QUBITS>* l) {
            if (l == nullptr) return true;
            if (l == noLIM) return false;
            return l->isIdentityModuloPhase();
        }

        // Returns whether the subsequence [start ... range) is all-zero
        bool isZeroInRange(unsigned int start, unsigned int end) const {
//            std::cout << "[isZeroInRange] start=" << start << " end=" << end << "\n"; std::cout.flush();
            for (unsigned int i=start; i<end && i<NUM_BITSETBITS; i++) {
//                std::cout << "[isZeroInRange] checking i=" << i << "\n"; std::cout.flush();
                if (paulis.test(i)) return false;
            }
//            std::cout << "[isZeroInRange] yes, is zero.\n"; std::cout.flush();
            return true;
        }

        // Given a 'phase' in 0,1,2,3,
        // multiply this LIM's phase by that amount
        void multiplyPhaseBy(int phase) {
//            std::cout << "[multiplyPhaseBy] current = " << (int) LimEntry<NUM_QUBITS>::getPhase(this) << " other = " << (int) phase << "\n";
            int current_phase = ((int) paulis.test(2*NUM_QUBITS)) | ((int) paulis.test(2*NUM_QUBITS + 1) << 1);
            int new_phase = current_phase + (phase & 0x3);
            paulis.set(2*NUM_QUBITS  , new_phase & 0x1);
            paulis.set(2*NUM_QUBITS+1, (new_phase & 0x2) >> 1);
//            std::cout << "[multiplyPhaseBy] new phase = " << (int) LimEntry<NUM_QUBITS>::getPhase(this) << "\n";
        }

        // Right-Multiply this Pauli operator with the 'other' Pauli operator, obtaining this * other
        // todo the 'bitset' data structure supports XOR natively,
        //   so use that to speed up this operation. When you implement this optimization,
        //   be careful that the phase is part of the 'bitset'
        void multiplyBy(const LimEntry<NUM_QUBITS>& other) {
            char op1, op2;
            for (unsigned int i=0; i<NUM_QUBITS; i++) {
                // Step 1: handle the phase, if the operators do not commute
                op1 =       getQubit(i) ;
                op2 = other.getQubit(i);
                if      (op1 == 'X' && op2 == 'Y')  // XY =  iZ
                    multiplyPhaseBy(phase_t::phase_i);
                else if (op1 == 'X' && op2 == 'Z')  // XZ = -iY
                    multiplyPhaseBy(phase_t::phase_minus_i);
                else if (op1 == 'Y' && op2 == 'X')  // YX = -iZ
                    multiplyPhaseBy(phase_t::phase_minus_i);
                else if (op1 == 'Y' && op2 == 'Z')  // YZ =  iX
                    multiplyPhaseBy(phase_t::phase_i);
                else if (op1 == 'Z' && op2 == 'X')  // ZX =  iY
                    multiplyPhaseBy(phase_t::phase_i);
                else if (op1 == 'Z' && op2 == 'Y')  // ZY = -iX
                    multiplyPhaseBy(phase_t::phase_minus_i);

                // Step 2: XOR the bits
                paulis.set(2*i,   paulis.test(2*i) ^ other.paulis.test(2*i));
                paulis.set(2*i+1, paulis.test(2*i+1) ^ other.paulis.test(2*i+1));
            }
            multiplyPhaseBy(LimEntry<NUM_QUBITS>::getPhase(&other));
        }

        void leftMultiplyBy(const LimEntry<NUM_QUBITS>& other) {
        	multiplyBy(other);
        	if (!commutesWith(other)) {
        		multiplyPhaseBy(phase_t::phase_minus_one);
        	}
        }

        void leftMultiplyBy(const LimEntry<NUM_QUBITS>* other) {
        	if (other == nullptr) return;
        	leftMultiplyBy(*other);
        }

        void multiplyBy(const LimEntry<NUM_QUBITS>* other) {
            assert(other != noLIM);
            if (other == nullptr) return; // multiply by identity
            multiplyBy(*other);
        }

        void operator*=(const LimEntry<NUM_QUBITS>& other) {
            multiplyBy(other);
        }

        // Returns the LIM a * b
        // TODO make more efficient by starting with "c = copy of a"
        static LimEntry<NUM_QUBITS>* multiply(const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b) {
            assert(a != noLIM && b != noLIM);
            LimEntry<NUM_QUBITS>* c = LimEntry<NUM_QUBITS>::getIdentityOperator();
            c->multiplyBy(a);
            c->multiplyBy(b);
            return c;
        }

        // TOOD I think this function is not called anywhere
        static LimEntry<NUM_QUBITS>* multiply(const LimEntry<NUM_QUBITS>& a, const LimEntry<NUM_QUBITS>& b) {
            LimEntry<NUM_QUBITS>* c = LimEntry<NUM_QUBITS>::getIdentityOperator();
            c->multiplyBy(a);
            c->multiplyBy(b);
            return c;
        }

        void setOperator(Qubit v, pauli_op op) {
            if ((int) v >= (int) NUM_QUBITS) return;
            switch(op) {
                case pauli_op::pauli_id:
                    paulis.set(2*v,   0);
                    paulis.set(2*v+1, 0);
                    break;
                case pauli_op::pauli_x:
                    paulis.set(2*v,   0);
                    paulis.set(2*v+1, 1);
                    break;
                case pauli_op::pauli_y:
                    paulis.set(2*v,   1);
                    paulis.set(2*v+1, 1);
                    break;
                case pauli_op::pauli_z:
                    paulis.set(2*v,   1);
                    paulis.set(2*v+1, 0);
                    break;
//                default:
                    // TODO limdd throw an exception?
            }
        }

        void setOperator(Qubit v, char op) {
        	setOperator(v, (pauli_op) op);
        }

        void setToIdentityOperator() {
        	for (Qubit qubit=0; qubit < (Qubit) NUM_QUBITS; qubit++) {
        		setOperator(qubit, pauli_op::pauli_id);
        	}
        	setPhase(phase_t::phase_one);
        }

        void operator=(const LimEntry<>* other) {
        	if (other == nullptr) setToIdentityOperator();
        	else {
        		*this = *other;
        	}
        }

        bool commutesWith(const LimEntry<NUM_QUBITS>& b) const {
        	unsigned int anticommute_count = 0;
        	char op1, op2;
        	for (Qubit q=0; q<(Qubit) NUM_QUBITS; q++) {
        		op1 = getQubit(q);
        		op2 = b.getQubit(q);
        		if (op1 != op2 && op1 != pauli_id && op2 != pauli_id) {
        			anticommute_count++;
        		}
        	}
        	// the Pauli Lims commute iff they have an even number of anticommuting gates
        	return (anticommute_count % 2) == 0;
        }

        bool commutesWith(const LimEntry<NUM_QUBITS>* b) const {
        	if (b == nullptr) return true;
        	return commutesWith(*b);
        }

        // Returns I, the Identity operator
        // (Some subroutines start with an identity operator, and then apply mutations to it;
        //  however, if you need the identity operator as such, then use a null pointer)
        static LimEntry<NUM_QUBITS>* getIdentityOperator() {
            LimEntry<NUM_QUBITS>* Id = new LimEntry<NUM_QUBITS>();
            return Id;
        }

        // Returns -I
        // i.e., -1 times the Identity operator
        static LimEntry<NUM_QUBITS>* getMinusIdentityOperator() {
            LimEntry<NUM_QUBITS>* Id = getIdentityOperator();
            Id->setPhase(phase_t::phase_minus_one);
            return Id;
        }

        // Returns the index of the first nonzero entry in the checkvector
        unsigned int pivotPosition() const {
            for (unsigned int i=0; i<2*NUM_QUBITS; i++) {
                if (paulis.test(i)) return i;
            }
            return (unsigned int) -1;
        }

        // Returns whether a <= b in the lexicographic order
        static bool leq(const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b) {
            assert(a != noLIM && b != noLIM);
            if (a == nullptr) return true;
            if (b == nullptr) return a->isIdentityOperator();
            // Note the length of the vectors is 2*NUM_QUBITS+2
            for (unsigned int i=0; i<NUM_BITSETBITS; i++) {
                if (!a->paulis.test(i) and b->paulis.test(i)) {
                    return true;
                }
                if (a->paulis.test(i) and !b->paulis.test(i)) {
                    return false;
                }
            }
            return true; // in this case, vectors are equal
        }

        static bool geq(const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b) {
            return leq(b, a);
        }

        // Returns whether a < b in the lexicographic order
        static bool leneq(const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b) {
            assert(a != noLIM && b != noLIM);
            for (unsigned int i=0; i<NUM_BITSETBITS; i++) {
                if (!a->paulis.test(i) and b->paulis.test(i)) {
                    return true;
                }
                if (a->paulis.test(i) and !b->paulis.test(i)) {
                    return false;
                }
            }
            return false; // the vectors are equal, so return false, since a is not less than b
        }

        static bool geneq(const LimEntry<NUM_QUBITS>* a, const LimEntry<NUM_QUBITS>* b) {
            return leneq(b, a);
        }
    };

    // A wrapper containing a LimEntry and a std::bitset
    // used in Gaussian Elimination, when the matrix of checkvectors is split up into two parts:
    //   a LIM-part and a '0/1 matrix' part, which is used for finding linear combinations
    template <std::size_t NUM_QUBITS=dd::NUM_QUBITS>
    class LimBitset {
    public:
        LimEntry<NUM_QUBITS> lim;
        std::bitset<NUM_QUBITS> bits;

        LimBitset<NUM_QUBITS>() {
            //
        }

        LimBitset<NUM_QUBITS>(const LimBitset<NUM_QUBITS>* a)
                : lim(a->lim), bits(a->bits) {
            //
        }

        LimBitset<NUM_QUBITS>(const LimEntry<NUM_QUBITS>* _lim)
        : lim(*_lim) {
            //
        }

        bool isAllZeroLim() const {
            return lim.isAllZeroVector();
        }

        void multiplyBy(const LimBitset<NUM_QUBITS>& other) {
            lim.multiplyBy(other.lim);
            bits ^= other.bits;
        }

        static LimBitset<NUM_QUBITS>* multiply(const LimBitset<NUM_QUBITS>* a, const LimBitset<NUM_QUBITS>* b) {
            LimBitset<NUM_QUBITS>* c = new LimBitset<NUM_QUBITS>();
            c->multiplyBy(a);
            c->multiplyBy(b);
            return c;
        }

        static bool leq(const LimBitset<NUM_QUBITS>* a, const LimBitset<NUM_QUBITS>* b) {
            return LimEntry<NUM_QUBITS>::leq(&(a->lim), &(b->lim));
        }

        static bool geq(const LimBitset<NUM_QUBITS>* a, const LimBitset<NUM_QUBITS>* b) {
            return LimEntry<NUM_QUBITS>::geq(&(a->lim), &(b->lim));
        }
    };

    // LimWeight contains a LIM and a Complex number
    // The complex number is always a temporary element of the complex numbers cache
    template <std::size_t NUM_QUBITS=dd::NUM_QUBITS>
    struct LimWeight {
    public:
    	LimEntry<NUM_QUBITS>* lim;
    	Complex weight;

        static LimWeight<NUM_QUBITS>* noLIM; // value is -1

        // Initializes the identity operator, with weight +1
    	LimWeight<NUM_QUBITS>()
    			: lim(nullptr), weight(Complex::one) {
    		//
    	}

    	LimWeight<NUM_QUBITS>(const LimWeight<NUM_QUBITS>* a)
    			: lim(a->lim), weight(a->weight) {
    		//
    	}

    	LimWeight<NUM_QUBITS>(const LimEntry<NUM_QUBITS>* a)
    			: lim(new LimEntry<NUM_QUBITS>(a)), weight(Complex::one) {
    		//
    	}

    	LimWeight<NUM_QUBITS>(const std::string pauliString)
    			: lim(new LimEntry<NUM_QUBITS>(pauliString)), weight(Complex::one) {
    		//
    	}

    	void setToIdentityOperator() {
    		if (lim == nullptr) {
    			lim = new LimEntry<>();
    		}
    		else {
    			lim->setToIdentityOperator();
    		}
    	}

    	void multiplyBy(const LimWeight<NUM_QUBITS>& other) {
    		lim->multiplyBy(other->lim);
    		// TODO
    		// Question @Thomas, Stefan: how to multiply the weight? as follows:
    		//   weight = weight * other.weight
    	}

    	void multiplyBy(const LimEntry<NUM_QUBITS>& other) {
    		lim->multiplyBy(other);
    	}

    	static std::string to_string(const LimWeight<NUM_QUBITS>* a) {
    		if (a == LimWeight<NUM_QUBITS>::noLIM) {
    			return "(no LIM)";
    		}
    		return LimEntry<NUM_QUBITS>::to_string(a->lim);
    	}

    	static bool Equal(const LimWeight<NUM_QUBITS>* a, const LimWeight<NUM_QUBITS>* b) {
    		assert(a != nullptr);
    		assert(b != nullptr);
    		if (a == noLIM && b == noLIM) return true;
    		if (a == noLIM || b == noLIM) return false;
    		return LimEntry<NUM_QUBITS>::Equal(a->lim, b->lim);
    	}


    };

    template <std::size_t NUM_QUBITS>
    LimEntry<NUM_QUBITS>* LimEntry<NUM_QUBITS>::noLIM = (LimEntry<NUM_QUBITS>*) -1;

    template <std::size_t NUM_QUBITS>
    LimWeight<NUM_QUBITS>* LimWeight<NUM_QUBITS>::noLIM = (LimWeight<NUM_QUBITS>*) -1;

    template <std::size_t NUM_QUBITS>
    std::ostream& operator<<(std::ostream& out, const LimEntry<NUM_QUBITS>& a) {
        return out << LimEntry<NUM_QUBITS>::to_string(&a);
    }

    template <std::size_t NUM_QUBITS>
    std::ostream& operator<<(std::ostream& out, const LimBitset<NUM_QUBITS>& a) {
        return out << a.lim << " -- " << a.bits;
    }

    template <std::size_t NUM_QUBITS>
    std::ostream& operator<<(std::ostream& out, const LimWeight<NUM_QUBITS>& a) {
//    	LimEntry<NUM_QUBITS>* const alim = (LimEntry<NUM_QUBITS>* const) &(a.lim);
    	return out << a.weight << " * " << LimEntry<NUM_QUBITS>::to_string(a.lim);
    }
} // namespace dd

namespace std {
    template<std::size_t NUM_QUBITS>
    struct hash<dd::LimEntry<NUM_QUBITS>> {
        std::size_t operator()(dd::LimEntry<NUM_QUBITS> const& e) const noexcept {
            return std::hash<std::bitset<dd::LimEntry<NUM_QUBITS>::NUM_BITSETBITS> >{}(e.paulis);
        }
    };

} // namespace std

namespace dd {

    template<std::size_t NUM_QUBITS = dd::NUM_QUBITS, std::size_t NBUCKET = 32768, std::size_t ALLOCATION_SIZE = 4096, std::size_t INITIAL_GC_LIMIT = 65536>
    class LimTable {
    public:
        using Entry                = LimEntry<NUM_QUBITS>;
        using PauliBitSet          = std::bitset<Entry::NUM_BITSETBITS>;
        static constexpr auto MASK = NBUCKET - 1;

        LimTable():
            chunkID(0), allocationSize(ALLOCATION_SIZE), gcLimit(INITIAL_GC_LIMIT) {
            chunks.emplace_back(allocationSize);
            allocations += allocationSize;
            chunkIt    = chunks[0].begin();
            chunkEndIt = chunks[0].end();

            auto* allIdentity     = lookup(PauliBitSet(0)); // save all identity fixed in the table
            allIdentity->refCount = 1;
        };
        ~LimTable() = default;

        static std::size_t hash(const Entry& a) {
            return hash(a.paulis);
        }

        static std::size_t hash(const PauliBitSet& a) {
            return std::hash<PauliBitSet>{}(a)&MASK;
        }

        constexpr std::size_t getNumQubits() {
            return NUM_QUBITS;
        }

        [[nodiscard]] bool availableEmpty() const {
            return available == nullptr;
        };

        [[nodiscard]] Entry* getEntry() {
            // an entry is available on the stack
            if (!availableEmpty()) {
                Entry* entry = available;
                available    = entry->next;
                // returned entries could have a ref count != 0
                entry->refCount = 0;
                return entry;
            }

            // new chunk has to be allocated
            if (chunkIt == chunkEndIt) {
                chunks.emplace_back(allocationSize);
                allocations += allocationSize;
                chunkID++;
                chunkIt    = chunks[chunkID].begin();
                chunkEndIt = chunks[chunkID].end();
            }

            auto entry = &(*chunkIt);
            ++chunkIt;
            return entry;
        }

        Entry* lookup_str(const std::string pauliString) {
            // different name from lookup because 0 can apparently be seen as a
            // string (and therefor overloading lookup on input type is an issue)
            // TODO: maybe find a way to overload lookup() cleanly?
            PauliBitSet bitSet = LimEntry<NUM_QUBITS>::bitsetFromString(pauliString);
            return lookup(bitSet);
        }

        Entry* lookup(const Entry& pauliOperand) {
            //todo assert that pauliOperand is not from the LimTable (otherwise I need to free the pauliOperand)
            return lookup(pauliOperand.paulis);
        }

        Entry* lookup(const PauliBitSet& pauliString) {
            lookups++;
            const auto key = hash(pauliString);

            Entry* p = table[key];
            while (p != nullptr) {
                if (pauliString == p->paulis) {
                    // Match found
                    hits++;
                    return p;
                }
                collisions++;
                p = p->next;
            }

            // pauli string was not found -> add it to front of unique table bucket
            auto* pauliOperand   = getEntry();
            pauliOperand->paulis = pauliString;

            pauliOperand->next = table[key];
            table[key]         = pauliOperand;
            count++;
            maxCount = std::max(maxCount, count);
            return pauliOperand;
        }

        void returnPauliString(Entry* p) {
            p->next   = available;
            available = p;
        }

        static void incRef(Entry* p) {
            if (p == nullptr) {
                return;
            }
            if (p->refCount == std::numeric_limits<RefCount>::max()) {
                std::clog << "[WARN] MAXREFCNT reached for " << p->paulis << ". Number will never be collected." << std::endl;
                return;
            }
            p->refCount++;
        }

        static void decRef(Entry* p) {
            if (p == nullptr) {
                return;
            }
            if (p->refCount == std::numeric_limits<RefCount>::max()) {
                return;
            }
            if (p->refCount == 0) {
                throw std::runtime_error("In LimTable: RefCount of entry " + p->paulis.to_string() + " is zero before decrement");
            }
            p->refCount--;
        }

        void print() {
            for (std::size_t key = 0; key < table.size(); ++key) {
                auto* p = table[key];

                while (p != nullptr) {
                    std::cout << "[" << key << "]\t" << Entry::to_string(p) << " "
                              << " " << p->refCount << "\n";
                    p = p->next;
                }
            }
        }

        void clear() {
            // clear table buckets
            for (auto& bucket: table) {
                bucket = nullptr;
            }

            // clear available stack
            available = nullptr;

            // release memory of all but the first chunk TODO: it could be desirable to keep the memory
            while (chunkID > 0) {
                chunks.pop_back();
                chunkID--;
            }
            // restore initial chunk setting
            chunkIt    = chunks[0].begin();
            chunkEndIt = chunks[0].end();

            for (auto& entry: chunks[0]) {
                entry.refCount = 0;
            }

            count      = 0;
            collisions = 0;
            hits       = 0;
            lookups    = 0;

            gcCalls = 0;
            gcRuns  = 0;
            gcLimit = INITIAL_GC_LIMIT;
        };

        [[nodiscard]] bool possiblyNeedsCollection() const { return count >= gcLimit; }

        std::size_t garbageCollect(bool force = false) {
            gcCalls++;
            // nothing to be done if garbage collection is not forced, and the limit has not been reached,
            // or the current count is minimal (the complex table always contains at least 0.5)
            if ((!force && count < gcLimit) || count <= 1)
                return 0;

            gcRuns++;
            std::size_t collected = 0;
            std::size_t remaining = 0;
            for (std::size_t key = 0; key < table.size(); ++key) {
                Entry* p     = table[key];
                Entry* lastp = nullptr;
                while (p != nullptr) {
                    if (p->refCount == 0) {
                        Entry* next = p->next;
                        if (lastp == nullptr) {
                            table[key] = next;
                        } else {
                            lastp->next = next;
                        }
                        returnPauliString(p);
                        p = next;
                        collected++;
                    } else {
                        lastp = p;
                        p     = p->next;
                        remaining++;
                    }
                }
            }
            // The garbage collection limit changes dynamically depending on the number of remaining (active) nodes.
            // If it were not changed, garbage collection would run through the complete table on each successive call
            // once the number of remaining entries reaches the garbage collection limit. It is increased whenever the
            // number of remaining entries is rather close to the garbage collection threshold and decreased if the
            // number of remaining entries is much lower than the current limit.
            if (remaining > gcLimit / 10 * 9) {
                gcLimit = remaining + INITIAL_GC_LIMIT;
            } else if (remaining < gcLimit / 128) {
                gcLimit /= 2;
            }
            count = remaining;
            return collected;
        }

        std::ostream& printStatistics(std::ostream& os = std::cout) {
            // clang-format off
            os << "hits: " << hits
               << ", collisions: " << collisions
               << ", looks: " << lookups
               << ", gc calls: " << gcCalls
               << ", gc runs: " << gcRuns
               << "\n";
            // clang-format on
            return os;
        }

    private:
        std::array<Entry*, NBUCKET> table{};
        // compute table lookup statistics
        std::size_t hits       = 0;
        std::size_t lookups    = 0;
        std::size_t count      = 0;
        std::size_t collisions = 0;
        std::size_t maxCount   = 0;

        Entry*                                available{};
        std::vector<std::vector<Entry>>       chunks{};
        std::size_t                           chunkID;
        typename std::vector<Entry>::iterator chunkIt{};
        typename std::vector<Entry>::iterator chunkEndIt{};
        std::size_t                           allocationSize;
        std::size_t                           allocations = 0;

        // garbage collection
        std::size_t gcCalls = 0;
        std::size_t gcRuns  = 0;
        std::size_t gcLimit = 100000;
    };

} // namespace dd

#endif //DDPACKAGE_LIMTABLE_HPP
