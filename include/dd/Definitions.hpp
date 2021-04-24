/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_DATATYPES_HPP
#define DDpackage_DATATYPES_HPP

#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>

namespace dd {
    // integer type used for indexing qubits
    // needs to be a signed type to encode -1 as the index for the terminal
    // std::int_fast8_t can at least address 128 qubits as [0, ..., 127]
    using Qubit = std::int_fast8_t;
    static_assert(std::is_signed_v<Qubit>, "Type Qubit must be signed.");

    // integer type used for specifying numbers of qubits
    using QubitCount = std::make_unsigned<Qubit>::type;

    // integer type used for reference counting
    // 32bit suffice for a max ref count of around 4 billion
    using RefCount = std::uint_fast32_t;
    static_assert(std::is_unsigned_v<RefCount>, "RefCount should be unsigned.");

    // floating point type to use
    using fp = double;
    static_assert(std::is_floating_point_v<fp>, "fp should be a floating point type (float, *double*, long double)");

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

    static constexpr fp SQRT2_2 = 0.707106781186547524400844362104849039284835937688474036588L;
    static constexpr fp PI      = 3.141592653589793238462643383279502884197169399375105820974L;
    static constexpr fp PI_2    = 1.570796326794896619231321691639751442098584699687552910487L;
    static constexpr fp PI_4    = 0.785398163397448309615660845819875721049292349843776455243L;

    using CVec = std::vector<std::pair<float, float>>;
    using CMat = std::vector<CVec>;

    static constexpr std::uint_least64_t SERIALIZATION_VERSION = 1;

    constexpr std::size_t murmur64(std::size_t k) {
        k ^= k >> 33;
        k *= 0xff51afd7ed558ccdUL;
        k ^= k >> 33;
        k *= 0xc4ceb9fe1a85ec53UL;
        k ^= k >> 33;
        return k;
    }

    constexpr std::size_t combineHash(std::size_t lhs, std::size_t rhs) {
        lhs ^= rhs + 0x9e3779b97f4a7c15 + (lhs << 6) + (lhs >> 2);
        return lhs;
    }

} // namespace dd
#endif //DDpackage_DATATYPES_HPP
