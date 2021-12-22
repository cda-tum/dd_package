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

// todo two of the bits should be reserved for the phase, which is one of +1, +i, -1, -i
namespace dd {
    enum pauli_op {
        pauli_id = 0,
        pauli_z  = 1,
        pauli_x  = 2,
        pauli_y  = 3
    };

    template<std::size_t NUM_QUBITS = 32>
    struct LimEntry {
        static_assert(NUM_QUBITS > 0, "Have at least one qubit");
        static_assert(NUM_QUBITS <= std::numeric_limits<dd::Qubit>::max(), "Too many qubits for LimEntry");

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
        explicit LimEntry(const LimEntry<NUM_QUBITS>* l):
            paulis(l->paulis) {}

        static std::bitset<NUM_BITSETBITS> bitsetFromString(std::string pauliString) {
            std::bitset<NUM_BITSETBITS> res{0};
            for (std::string::size_type i = 0; i < pauliString.size(); i++) {
                switch (pauliString[i]) {
                    case 'I':
                        res[2 * NUM_QUBITS - (2 * i + 2)] = 0;
                        res[2 * NUM_QUBITS - (2 * i + 1)] = 0;
                        break;
                    case 'X':
                        res[2 * NUM_QUBITS - (2 * i + 2)] = 0;
                        res[2 * NUM_QUBITS - (2 * i + 1)] = 1;
                        break;
                    case 'Z':
                        res[2 * NUM_QUBITS - (2 * i + 2)] = 1;
                        res[2 * NUM_QUBITS - (2 * i + 1)] = 0;
                        break;
                    case 'Y':
                        res[2 * NUM_QUBITS - (2 * i + 2)] = 1;
                        res[2 * NUM_QUBITS - (2 * i + 1)] = 1;
                        break;
                    default:
                        throw std::runtime_error("Unrecognized symbol in Pauli string\n");
                }
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
        char getQubit(dd::Qubit qubit) const {
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
            return lim->getQubit(qubit);
        }

        /**
         * @return a string of {I, X, Y, Y}**n with left in the string corresponding to the top of the decision diagram.
         */
        static std::string to_string(const LimEntry<NUM_QUBITS>* lim) {
            if (lim == nullptr) {
                return std::string(NUM_QUBITS, 'I');
            }

            std::ostringstream os;
            for (int i = NUM_QUBITS - 1; i >= 0; --i) {
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

        // Given a 'phase' in 0,1,2,3,
        // multiply this LIM's phase by that amount
        void multiplyPhaseBy(uint8_t phase) {
            uint8_t current_phase = (paulis.test(2*NUM_QUBITS)) | (paulis.test(2*NUM_QUBITS) << 1);
            uint8_t new_phase = current_phase + (phase & 0x3);
            paulis.set(2*NUM_QUBITS  , new_phase & 0x1);
            paulis.set(2*NUM_QUBITS+1, new_phase & 0x2);
        }

        // Right-Multiply two Pauli operators
        // todo this operation should also take into account the phase;
        //   but let's do that after we implement the phase in the data structure
        void multiplyBy(const LimEntry<NUM_QUBITS>& other) {
            // Multiply the Pauli gates
            paulis.operator^=(other.paulis);
            char op1, op2;
            for (unsigned int i=0; i<NUM_QUBITS; i++) {
                // Step 1: handle the phase, if the operators do not commute
                op1 =       getQubit(i) ;
                op2 = other.getQubit(i);
                if      (op1 == pauli_x && op2 == pauli_y)
                    multiplyPhaseBy(1);    // multiply by i
                else if (op1 == pauli_x && op2 == pauli_z)
                    multiplyPhaseBy(3);    // multiply by -i
                else if (op1 == pauli_y && op2 == pauli_x)
                    multiplyPhaseBy(3);    // multiply by -i
                else if (op1 == pauli_y && op2 == pauli_z)
                    multiplyPhaseBy(1);    // multiply by i
                else if (op1 == pauli_z && op2 == pauli_x)
                    multiplyPhaseBy(1);    // multiply by i
                else if (op1 == pauli_z && op2 == pauli_y)
                    multiplyPhaseBy(3);    // multiply by -i

                // Step 2: XOR the bits
                paulis.set(2*i,   paulis.test(2*i) ^ other.paulis.test(2*i));
                paulis.set(2*i+1, paulis.test(2*i+1) ^ other.paulis.test(2*i+1));
            }
        }

        void operator*=(const LimEntry<NUM_QUBITS>& other) {
            multiplyBy(other);
        }

        void setOperator(unsigned int v, char op) {
            if (v >= NUM_QUBITS) return;
            switch(op) {
                case 'I':
                    paulis.set(2*v,   0);
                    paulis.set(2*v+1, 0);
                    break;
                case 'X':
                    paulis.set(2*v,   0);
                    paulis.set(2*v+1, 1);
                    break;
                case 'Y':
                    paulis.set(2*v,   1);
                    paulis.set(2*v+1, 0);
                    break;
                case 'Z':
                    paulis.set(2*v,   1);
                    paulis.set(2*v+1, 1);
                    break;
//                default:
                    // TODO throw an exception?
            }
        }

        // Returns I, the Identity operator
        // (Some subroutines start with an identity operator, and then apply mutations to it;
        //  however, if you need the identity operator as such, then use a null pointer)
        static LimEntry<>* getIdentityOperator() {
            LimEntry<>* Id = new LimEntry<>();
            return Id;
        }

        // Returns -I
        // i.e., -1 times the Identity operator
        static LimEntry<>* getMinusIdentityOperator() {
            throw std::runtime_error("Error; in getMinusIdentityOperator: not implemented.\n");
        }

        // returns the phase of the LIM, in two bits, which have the following meaning:
        // 00: +1    01: i    10: -1    11: -i
        static uint32_t getPhase(LimEntry<>* l) {
            uint32_t phase = (l->paulis.test(2*NUM_QUBITS)) | (l->paulis.test(2*NUM_QUBITS) << 1);
            return phase;
        }

        // Returns whether this vector is the identity operator, i.e., has all bits set to zero
        // TODO there is probably a faster way to check whether a bitvector is all-zero,
        //   using bit tricks. --Lieuwe
        bool isAllZeroVector() const {
            for (unsigned int i=0; i<NUM_BITSETBITS; i++) {
                if (paulis.test(i)) return false;
            }
            return true;
        }

        bool isIdentityOperator() const {
            return isAllZeroVector();
        }

        // Returns whether a < b in the lexicographic order
        static bool leq(LimEntry<>* a, LimEntry<>* b) {
            // Note the length of the vectors is 2*NUM_QUBITS+2
            for (unsigned int i=0; i<2*NUM_QUBITS+2; i++) {
                if (!a->paulis.test(i) and b->paulis.test(i)) {
                    return true;
                }
                if (a->paulis.test(i) and !b->paulis.test(i)) {
                    return false;
                }
            }
            return true; // in this case, vectors are equal
        }
    };
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

    template<std::size_t NUM_QUBITS = 32, std::size_t NBUCKET = 32768, std::size_t ALLOCATION_SIZE = 4096, std::size_t INITIAL_GC_LIMIT = 65536>
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
