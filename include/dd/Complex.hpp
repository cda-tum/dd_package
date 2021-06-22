/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DD_PACKAGE_COMPLEX_HPP
#define DD_PACKAGE_COMPLEX_HPP

#include "ComplexTable.hpp"
#include "ComplexValue.hpp"

#include <cstddef>
#include <iostream>
#include <utility>

namespace dd {
    using CTEntry = ComplexTable<>::Entry;

    struct Complex {
        CTEntry* mag;
        CTEntry* phase;

        static Complex zero;
        static Complex one;

        void setVal(const Complex& c) const {
            mag->value   = CTEntry::val(c.mag);
            phase->value = CTEntry::val(c.phase);
        }

        [[nodiscard]] inline bool approximatelyEquals(const Complex& c) const {
            return CTEntry::approximatelyEquals(mag, c.mag) && CTEntry::approximatelyEquals(phase, c.phase);
        };

        [[nodiscard]] inline bool approximatelyZero() const {
            return CTEntry::approximatelyZero(mag);
        }

        [[nodiscard]] inline bool approximatelyOne() const {
            return CTEntry::approximatelyOne(mag) && CTEntry::approximatelyZero(phase);
        }

        inline bool operator==(const Complex& other) const {
            return mag == other.mag && phase == other.phase;
        }

        inline bool operator!=(const Complex& other) const {
            return !operator==(other);
        }

        [[nodiscard]] std::string toString(bool formatted = true, int precision = -1) const {
            return ComplexValue::toString(CTEntry::val(mag), CTEntry::val(phase), formatted, precision);
        }

        void writeBinary(std::ostream& os) const {
            CTEntry::writeBinary(mag, os);
            CTEntry::writeBinary(phase, os);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.toString();
        return os;
    }

    inline Complex Complex::zero{&ComplexTable<>::zero, &ComplexTable<>::zero};
    inline Complex Complex::one{&ComplexTable<>::one, &ComplexTable<>::zero};
} // namespace dd

namespace std {
    template<>
    struct hash<dd::Complex> {
        std::size_t operator()(dd::Complex const& c) const noexcept {
            auto h1 = dd::murmur64(reinterpret_cast<std::size_t>(c.mag));
            auto h2 = dd::murmur64(reinterpret_cast<std::size_t>(c.phase));
            return dd::combineHash(h1, h2);
        }
    };
} // namespace std

#endif //DD_PACKAGE_COMPLEX_HPP
