/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DD_PACKAGE_COMPLEXVALUE_HPP
#define DD_PACKAGE_COMPLEXVALUE_HPP

#include "ComplexTable.hpp"
#include "Definitions.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace dd {
    struct ComplexValue {
        fp r, i;

        [[nodiscard]] inline bool approximatelyEquals(const ComplexValue& c) const {
            return std::abs(r - c.r) < ComplexTable<>::tolerance() &&
                   std::abs(i - c.i) < ComplexTable<>::tolerance();
        }

        [[nodiscard]] inline bool approximatelyZero() const {
            return std::abs(r) < ComplexTable<>::tolerance() &&
                   std::abs(i) < ComplexTable<>::tolerance();
        }

        [[nodiscard]] inline bool approximatelyOne() const {
            return std::abs(r - 1.) < ComplexTable<>::tolerance() &&
                   std::abs(i) < ComplexTable<>::tolerance();
        }

        inline bool operator==(const ComplexValue& other) const {
            return r == other.r && i == other.i;
        }

        inline bool operator!=(const ComplexValue& other) const {
            return !operator==(other);
        }

        void readBinary(std::istream& is) {
            is.read(reinterpret_cast<char*>(&r), sizeof(decltype(r)));
            is.read(reinterpret_cast<char*>(&i), sizeof(decltype(i)));
        }

        void writeBinary(std::ostream& os) const {
            os.write(reinterpret_cast<const char*>(&r), sizeof(decltype(r)));
            os.write(reinterpret_cast<const char*>(&i), sizeof(decltype(i)));
        }

        void from_string(const std::string& real_str, std::string imag_str) {
            fp real = real_str.empty() ? 0. : std::stod(real_str);

            imag_str.erase(remove(imag_str.begin(), imag_str.end(), ' '), imag_str.end());
            imag_str.erase(remove(imag_str.begin(), imag_str.end(), 'i'), imag_str.end());
            if (imag_str == "+" || imag_str == "-") imag_str = imag_str + "1";
            fp imag = imag_str.empty() ? 0. : std::stod(imag_str);
            r       = {real};
            i       = {imag};
        }

        static auto getLowestFraction(const double x, const std::uint64_t maxDenominator = std::uint64_t(1) << 10, const fp tol = dd::ComplexTable<>::tolerance()) {
            assert(x >= 0.);

            std::pair<std::uint64_t, std::uint64_t> lowerBound{0U, 1U};
            std::pair<std::uint64_t, std::uint64_t> upperBound{1U, 0U};

            while ((lowerBound.second <= maxDenominator) && (upperBound.second <= maxDenominator)) {
                auto num    = lowerBound.first + upperBound.first;
                auto den    = lowerBound.second + upperBound.second;
                auto median = static_cast<fp>(num) / static_cast<fp>(den);
                if (std::abs(x - median) < tol) {
                    if (den <= maxDenominator) {
                        return std::pair{num, den};
                    } else if (upperBound.second > lowerBound.second) {
                        return upperBound;
                    } else {
                        return lowerBound;
                    }
                } else if (x > median) {
                    lowerBound = {num, den};
                } else {
                    upperBound = {num, den};
                }
            }
            if (lowerBound.second > maxDenominator) {
                return upperBound;
            } else {
                return lowerBound;
            }
        }

        static void printFormatted(std::ostream& os, fp r, bool imaginary = false) {
            if (std::abs(r) < ComplexTable<>::tolerance()) {
                os << (std::signbit(r) ? "-" : "+") << "0" << (imaginary ? "i" : "");
                return;
            }
            auto n = std::log2(std::abs(r));
            auto m = std::log2(std::abs(r) / SQRT2_2);
            auto o = std::log2(std::abs(r) / PI);

            if (n == 0) { // +-1
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << "i";
                } else
                    os << (std::signbit(r) ? "-" : "") << 1;
                return;
            }

            if (m == 0) { // +- 1/sqrt(2)
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u221a\u00bdi";
                } else {
                    os << (std::signbit(r) ? "-" : "") << u8"\u221a\u00bd";
                }
                return;
            }

            if (o == 0) { // +- pi
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u03c0i";
                } else {
                    os << (std::signbit(r) ? "-" : "") << u8"\u03c0";
                }
                return;
            }

            if (std::abs(n + 1) < ComplexTable<>::tolerance()) { // 1/2
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u00bdi";
                } else
                    os << (std::signbit(r) ? "-" : "") << u8"\u00bd";
                return;
            }

            if (std::abs(m + 1) < ComplexTable<>::tolerance()) { // 1/sqrt(2) 1/2
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u221a\u00bd \u00bdi";
                } else
                    os << (std::signbit(r) ? "-" : "") << u8"\u221a\u00bd \u00bd";
                return;
            }

            if (std::abs(o + 1) < ComplexTable<>::tolerance()) { // +-pi/2
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u00bd \u03c0i";
                } else
                    os << (std::signbit(r) ? "-" : "") << u8"\u00bd \u03c0";
                return;
            }

            if (std::abs(std::round(n) - n) < ComplexTable<>::tolerance() && n < 0) { // 1/2^n
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u00bd\u002a\u002a" << (int)std::round(-n) << "i";
                } else
                    os << (std::signbit(r) ? "-" : "") << u8"\u00bd\u002a\u002a" << (int)std::round(-n);
                return;
            }

            if (std::abs(std::round(m) - m) < ComplexTable<>::tolerance() && m < 0) { // 1/sqrt(2) 1/2^m
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u221a\u00bd \u00bd\u002a\u002a" << (int)std::round(-m) << "i";
                } else
                    os << (std::signbit(r) ? "-" : "") << u8"\u221a\u00bd \u00bd\u002a\u002a" << (int)std::round(-m);
                return;
            }

            if (std::abs(std::round(o) - o) < ComplexTable<>::tolerance() && o < 0) { // 1/2^o pi
                if (imaginary) {
                    os << (std::signbit(r) ? "-" : "+") << u8"\u00bd\u002a\u002a" << (int)std::round(-o) << u8" \u03c0i";
                } else
                    os << (std::signbit(r) ? "-" : "") << u8"\u00bd\u002a\u002a" << (int)std::round(-o) << u8" \u03c0";
                return;
            }

            if (imaginary) { // default
                os << (std::signbit(r) ? "" : "+") << r << "i";
            } else
                os << r;
        }

        static std::string toString(const fp& real, const fp& imag, bool formatted = true, int precision = -1) {
            std::ostringstream ss{};

            if (precision >= 0) ss << std::setprecision(precision);
            const auto tol = ComplexTable<>::tolerance();

            if (std::abs(real) < tol && std::abs(imag) < tol) return "0";

            if (std::abs(real) >= tol) {
                if (formatted) {
                    printFormatted(ss, real);
                } else {
                    ss << real;
                }
            }
            if (std::abs(imag) >= tol) {
                if (formatted) {
                    if (std::abs(real - imag) < tol) {
                        ss << "(1+i)";
                        return ss.str();
                    } else if (std::abs(real + imag) < tol) {
                        ss << "(1-i)";
                        return ss.str();
                    }
                    printFormatted(ss, imag, true);
                } else {
                    if (std::abs(real) < tol) {
                        ss << imag;
                    } else {
                        if (imag > 0.) {
                            ss << "+";
                        }
                        ss << imag;
                    }
                    ss << "i";
                }
            }

            return ss.str();
        }

        explicit operator auto() const { return std::complex<dd::fp>{r, i}; }

        ComplexValue& operator+=(const ComplexValue& rhs) {
            r += rhs.r;
            i += rhs.i;
            return *this;
        }

        friend ComplexValue operator+(ComplexValue lhs, const ComplexValue& rhs) {
            lhs += rhs;
            return lhs;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const ComplexValue& c) {
        return os << ComplexValue::toString(c.r, c.i);
    }
} // namespace dd

namespace std {
    template<>
    struct hash<dd::ComplexValue> {
        std::size_t operator()(dd::ComplexValue const& c) const noexcept {
            auto h1 = dd::murmur64(static_cast<std::size_t>(std::round(c.r / dd::ComplexTable<>::tolerance())));
            auto h2 = dd::murmur64(static_cast<std::size_t>(std::round(c.i / dd::ComplexTable<>::tolerance())));
            return dd::combineHash(h1, h2);
        }
    };
} // namespace std
#endif //DD_PACKAGE_COMPLEXVALUE_HPP
