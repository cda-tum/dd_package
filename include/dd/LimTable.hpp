#ifndef DDPACKAGE_LIMTABLE_HPP
#define DDPACKAGE_LIMTABLE_HPP

#include <bitset>
#include <functional>
#include <limits>
#include <sstream>
#include <string>

namespace dd {

    struct LimEntry {
        static constexpr std::size_t numQubits = 32;
        static_assert(numQubits > 0, "Have at least on qubit");
        static_assert(numQubits <= std::numeric_limits<dd::Qubit>::max(), "Too many qubits for LimEntry");
        static constexpr std::size_t pauliBits = 2 * numQubits;
        static_assert(pauliBits % 2 == 0, "pauliBits has to be a multiple of two!");
        // 2 bits per qubit
        // 00 identity
        // 01 Pauli-Z
        // 10 Pauli-X
        // 11 Pauli-Y
        std::bitset<pauliBits> paulis{};
        LimEntry*              next{};
        RefCount               refCount{};

        [[nodiscard]] char getQubit(dd::Qubit qubit) const {
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

        [[nodiscard]] std::string to_string() const {
            std::ostringstream os;

            for (dd::Qubit i = paulis.size() / 2; i > 0; --i) {
                os << getQubit(i);
            }
            return os.str();
        }

        constexpr bool operator==(const LimEntry& other) const {
            return paulis == other.paulis;
        }
        constexpr bool operator!=(const LimEntry& other) const {
            //todo shouldn't it be enough to define the == operator?
            return paulis != other.paulis;
        }
    };
} // namespace dd

namespace std {
    template<>
    struct hash<dd::LimEntry> {
        std::size_t operator()(dd::LimEntry const& e) const noexcept {
            return std::hash<std::bitset<dd::LimEntry::pauliBits>>{}(e.paulis);
        }
    };

} // namespace std

namespace dd {

    template<std::size_t NBUCKET = 32768, std::size_t ALLOCATION_SIZE = 4096>
    class LimTable {
        LimTable():
            chunkID(0), allocationSize(ALLOCATION_SIZE) {
            chunks.emplace_back(allocationSize);
            allocations += allocationSize;
            chunkIt    = chunks[0].begin();
            chunkEndIt = chunks[0].end();

            lookup(0)->incRef(); // save all identity fixed in the table
        };
        ~LimTable() = default;

        static std::size_t hash(const LimEntry& a) {
            return std::hash<LimEntry>{}(a) % NBUCKET - 1;
        }

        static std::size_t hash(const std::bitset<LimEntry::pauliBits>& a) {
            return std::hash<std::bitset<LimEntry::pauliBits>>{}(a) % NBUCKET - 1;
        }

        LimEntry lookup(const LimEntry& pauliOperand) {
            lookups++;
            const auto key = hash(pauliOperand);

            LimEntry* p = table[key];
            while (p != nullptr) {
                if (pauliOperand == *p) {
                    // Match found
                    if (pauliOperand != *p) {
                        // put node pointed to by e.p on available chain
                        returnPauliString(pauliOperand);
                    }
                    hits++;
                    return *p;
                }
                collisions++;
                p = p->next;
            }

            // pauli string was not found -> add it to front of unique table bucket
            pauliOperand.next = table[key];
            table[key]        = pauliOperand;
            uniquePauliStringsCount++;
            peakUniquePauliStringsCount = std::max(peakUniquePauliStringsCount, uniquePauliStringsCount);
            return pauliOperand;
        }

        LimEntry lookup(const std::bitset<LimEntry::pauliBits>& pauliString) {
            //            auto &pauliOperand = reinterpret_cast<LimEntry&>(available->next);
            //            available->next = pauliOperand.next;
            //            pauliOperand.paulis = pauliString;
            //            lookup(pauliOperand);

            lookups++;
            const auto key = hash(pauliString);

            LimEntry* p = table[key];
            while (p != nullptr) {
                if (pauliString == p->paulis) {
                    // Match found
                    if (pauliOperand != *p) {
                        // put node pointed to by e.p on available chain
                        returnPauliString(pauliOperand);
                    }
                    hits++;
                    return *p;
                }
                collisions++;
                p = p->next;
            }

            // pauli string was not found -> add it to front of unique table bucket
            pauliOperand.next = table[key];
            table[key]        = pauliOperand;
            uniquePauliStringsCount++;
            peakUniquePauliStringsCount = std::max(peakUniquePauliStringsCount, uniquePauliStringsCount);
            return pauliOperand;
        }

        void returnPauliString(LimEntry* p) {
            p->next   = available;
            available = p;
        }

        static void incRef(LimEntry& p) {
            p.refCount++;
        }

        static void decRef(LimEntry& p) {
            p.refCount--;
        }

        void clear() {
            if (count > 0) {
                for (auto& entry: table)
                    entry.result.p = nullptr;
                count = 0;
            }
            hits    = 0;
            lookups = 0;
        }

    private:
        std::array<LimEntry, NBUCKET> table{};
        // compute table lookup statistics
        std::size_t hits                        = 0;
        std::size_t lookups                     = 0;
        std::size_t count                       = 0;
        std::size_t collisions                  = 0;
        std::size_t uniquePauliStringsCount     = 0;
        std::size_t peakUniquePauliStringsCount = 0;

        LimEntry*                                available{};
        std::vector<std::vector<LimEntry>>       chunks{};
        std::size_t                              chunkID;
        typename std::vector<LimEntry>::iterator chunkIt;
        typename std::vector<LimEntry>::iterator chunkEndIt;
        std::size_t                              allocationSize;
        std::size_t                              allocations = 0;
    };

} // namespace dd

#endif //DDPACKAGE_LIMTABLE_HPP
