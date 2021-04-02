/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_DATATYPES_HPP
#define DDpackage_DATATYPES_HPP

#include <array>
#include <cstdint>
#include <vector>

namespace dd {
    // integer type used for indexing qubits
    // needs to be a signed type to encode -1 as the index for the terminal
    // std::int_fast8_t can at least address 128 qubits as [0, ..., 127]
    using Qubit = std::int_fast8_t;

    // integer type used for specifying positive/negative controls
    // currently takes the unsigned type corresponding to how qubits are represented
    // controls are encoded so that
    //      `cq % 2 == 0` -> positive control
    // and
    //      `cq % 2 == 1` -> negative control
    // std::uint_fast8_t can encode pos./neg. controls for at least 128 qubits
    using ControlQubit = std::make_unsigned<Qubit>::type;

    // floating point type to use
    using fp = double;
    struct ComplexValue {
        fp r, i;

        bool operator==(const ComplexValue& other) const {
            return r == other.r && i == other.i;
        }

        bool operator!=(const ComplexValue& other) const {
            return !operator==(other);
        }
    };

    // logic radix
    static constexpr std::uint_fast8_t RADIX = 2;
    // max no. of edges = RADIX^2
    static constexpr std::uint_fast8_t NEDGE = RADIX * RADIX;

    static constexpr size_t MAXN = 128; // max no. of inputs TODO: this will be removed in a future update

    using GateMatrix           = std::array<ComplexValue, NEDGE>;
    static constexpr fp SQRT_2 = 0.707106781186547524400844362104849039284835937688474036588L;

    using CVec = std::vector<std::pair<float, float>>;
    using CMat = std::vector<CVec>;

} // namespace dd
#endif //DDpackage_DATATYPES_HPP
