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

        static void printFormatted(std::ostream& os, fp num, bool imaginary = false) {
            if (std::abs(num) < ComplexTable<>::tolerance()) {
                os << (std::signbit(num) ? "-" : "+") << "0" << (imaginary ? "i" : "");
                return;
            }

            if (std::log2(std::abs(num)) == 0) { // +-1
                if (imaginary) {
                    os << (std::signbit(num) ? "-" : "+") << "i";
                } else
                    os << (std::signbit(num) ? "-" : "") << 1;
                return;
            }

            const auto absnum   = std::abs(num);
            auto       fraction = getLowestFraction(absnum);
            auto       approx   = static_cast<fp>(fraction.first) / static_cast<fp>(fraction.second);
            auto       error    = std::abs(absnum - approx);

            if (error < ComplexTable<>::tolerance()) { // suitable fraction a/b found
                if (imaginary) {
                    if (fraction.second == 1U) {
                        if (fraction.first == 1U) {
                            os << (std::signbit(num) ? "-" : "+") << "i";
                        } else {
                            os << (std::signbit(num) ? "-" : "+") << fraction.first << "i";
                        }
                    } else {
                        if (fraction.first == 1U) {
                            os << (std::signbit(num) ? "-" : "+") << "i/" << fraction.second;
                        } else {
                            os << (std::signbit(num) ? "-" : "+") << fraction.first << "i/" << fraction.second;
                        }
                    }
                } else {
                    if (fraction.second == 1U) {
                        os << fraction.first;
                    } else {
                        os << fraction.first << "/" << fraction.second;
                    }
                }
                return;
            }

            const auto abssqrt = absnum / SQRT2_2;
            if (std::abs(abssqrt - 1) < ComplexTable<>::tolerance()) { // +- 1/sqrt(2)
                if (imaginary) {
                    os << (std::signbit(num) ? "-" : "+") << "i/√2";
                } else {
                    os << (std::signbit(num) ? "-" : "") << "1/√2";
                }
                return;
            }

            fraction = getLowestFraction(abssqrt);
            approx   = static_cast<fp>(fraction.first) / static_cast<fp>(fraction.second);
            error    = std::abs(abssqrt - approx);

            if (error < ComplexTable<>::tolerance()) { // suitable fraction a/(b * sqrt(2)) found
                if (imaginary) {
                    if (fraction.second == 1U) {
                        if (fraction.first == 1U) {
                            os << (std::signbit(num) ? "-" : "+") << "i/√2";
                        } else {
                            os << (std::signbit(num) ? "-" : "+") << fraction.first << "i/√2";
                        }
                    } else {
                        if (fraction.first == 1U) {
                            os << (std::signbit(num) ? "-" : "+") << "i/(" << fraction.second << "√2)";
                        } else {
                            os << (std::signbit(num) ? "-" : "+") << fraction.first << "i/(" << fraction.second << "√2)";
                        }
                    }
                } else {
                    if (fraction.second == 1U) {
                        os << fraction.first << "/√2)";
                    } else {
                        os << fraction.first << "/(" << fraction.second << "√2)";
                    }
                }
                return;
            }

            const auto abspi = absnum / PI;
            if (std::abs(abspi - 1) < ComplexTable<>::tolerance()) { // +- π
                if (imaginary) {
                    os << (std::signbit(num) ? "-" : "+") << "πi";
                } else {
                    os << (std::signbit(num) ? "-" : "") << "π";
                }
                return;
            }

            fraction = getLowestFraction(abspi);
            approx   = static_cast<fp>(fraction.first) / static_cast<fp>(fraction.second);
            error    = std::abs(abspi - approx);

            if (error < ComplexTable<>::tolerance()) { // suitable fraction a/b π found
                if (fraction.second == 1U) {
                    os << (imaginary && !std::signbit(num) ? "+" : "") << fraction.first << "π" << (imaginary ? "i" : "");
                } else if (fraction.first == 1U) {
                    os << (imaginary && !std::signbit(num) ? "+" : "") << "π" << (imaginary ? "i" : "") << "/" << fraction.second;
                } else {
                    os << (imaginary && !std::signbit(num) ? "+" : "") << fraction.first << "π" << (imaginary ? "i" : "") << "/" << fraction.second;
                }
                return;
            }

            if (imaginary) { // default
                os << (std::signbit(num) ? "" : "+") << num << "i";
            } else {
                os << num;
            }
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
