/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_DATATYPES_HPP
#define DDpackage_DATATYPES_HPP

#include <algorithm>
#include <array>
#include <cstdint>
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

    struct Control {
        enum class Type : bool { pos = true,
                                 neg = false };

        Qubit qubit{};
        Type  type = Type::pos;
    };

    inline bool operator<(const Control& lhs, const Control& rhs) {
        return lhs.qubit < rhs.qubit || (lhs.qubit == rhs.qubit && lhs.type == Control::Type::neg);
    }

    inline bool operator==(const Control& lhs, const Control& rhs) {
        return lhs.qubit == rhs.qubit && lhs.type == rhs.type;
    }

    inline bool operator!=(const Control& lhs, const Control& rhs) {
        return !(lhs == rhs);
    }

    inline namespace literals {
        inline Control operator""_pc(unsigned long long int q) { return {static_cast<Qubit>(q)}; }
        inline Control operator""_nc(unsigned long long int q) { return {static_cast<Qubit>(q), Control::Type::neg}; }
    } // namespace literals

    // floating point type to use
    using fp = double;
    struct ComplexValue {
        fp r, i;

        static ComplexValue readBinary(std::istream& is) {
            ComplexValue temp{};
            is.read(reinterpret_cast<char*>(&temp.r), sizeof(fp));
            is.read(reinterpret_cast<char*>(&temp.i), sizeof(fp));
            return temp;
        }

        static ComplexValue from_string(const std::string& real_str, std::string imag_str) {
            fp real = real_str.empty() ? 0. : std::stod(real_str);

            imag_str.erase(remove(imag_str.begin(), imag_str.end(), ' '), imag_str.end());
            imag_str.erase(remove(imag_str.begin(), imag_str.end(), 'i'), imag_str.end());
            if (imag_str == "+" || imag_str == "-") imag_str = imag_str + "1";
            fp imag = imag_str.empty() ? 0. : std::stod(imag_str);
            return ComplexValue{real, imag};
        }

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

    using GateMatrix           = std::array<ComplexValue, NEDGE>;
    static constexpr fp SQRT_2 = 0.707106781186547524400844362104849039284835937688474036588L;

    using CVec = std::vector<std::pair<float, float>>;
    using CMat = std::vector<CVec>;

    static constexpr double SERIALIZATION_VERSION = 0.1;

} // namespace dd
#endif //DDpackage_DATATYPES_HPP
