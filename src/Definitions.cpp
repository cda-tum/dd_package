/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "Definitions.hpp"

namespace dd {
    inline namespace literals {
        Control operator""_pc(unsigned long long int q) { return {static_cast<Qubit>(q)}; }
        Control operator""_nc(unsigned long long int q) { return {static_cast<Qubit>(q), Control::Type::neg}; }
    } // namespace literals
} // namespace dd
