/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_DATATYPES_HPP
#define DDpackage_DATATYPES_HPP

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace dd {
    // integer type used for indexing qubits
    // needs to be a signed type to encode -1 as the index for the terminal
    // std::int_fast8_t can at least address 128 qubits as [0, ..., 127]
    using Qubit = std::int_fast8_t;

    // integer type used for specifying numbers of qubits
    using QubitCount = std::make_unsigned<Qubit>::type;

    // integer type used for reference counting
    // 32bit suffice for a max ref count of around 4 billion
    using RefCount = std::uint_fast32_t;

    // forward declarations of important structs
    template<class Node>
    struct Edge;
    template<typename Node>
    struct CachedEdge;

    struct ComplexValue;
    class ComplexNumbers;

    // floating point type to use
    using fp = double;

    // logic radix
    static constexpr std::uint_fast8_t RADIX = 2;
    // max no. of edges = RADIX^2
    static constexpr std::uint_fast8_t NEDGE = RADIX * RADIX;

    enum class BasisStates {
        zero,
        one,
        plus,
        minus,
        right,
        left
    };

    using GateMatrix           = std::array<ComplexValue, NEDGE>;
    static constexpr fp SQRT_2 = 0.707106781186547524400844362104849039284835937688474036588L;

    using CVec = std::vector<std::pair<float, float>>;
    using CMat = std::vector<CVec>;

    static constexpr double SERIALIZATION_VERSION = 0.1;

} // namespace dd
using CN = dd::ComplexNumbers;
#endif //DDpackage_DATATYPES_HPP
