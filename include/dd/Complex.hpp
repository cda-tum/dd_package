/*
 * This file is part of the MQT DD Package which is released under the MIT license.
 * See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
 */

#ifndef DD_PACKAGE_COMPLEX_HPP
#define DD_PACKAGE_COMPLEX_HPP

#include "ComplexTable.hpp"
#include "ComplexValue.hpp"
#include "Definitions.hpp"
#include "Log.hpp"

#include <cstddef>
#include <iostream>
#include <utility>

namespace dd {
    using CTEntry = ComplexTable<>::Entry;

    struct Complex {
        CTEntry* r;
        CTEntry* i;

        static Complex zero;
        static Complex one;
        static Complex minus_one;
        static Complex complex_i;
        static Complex minus_i;

        void setVal(const Complex& c) const {
            r->value = CTEntry::val(c.r);
            i->value = CTEntry::val(c.i);
        }

        [[nodiscard]] inline bool approximatelyEquals(const Complex& c) const {
            return CTEntry::approximatelyEquals(r, c.r) && CTEntry::approximatelyEquals(i, c.i);
        };

        [[nodiscard]] inline bool exactlyZero() const {
            return CTEntry::exactlyZero(r) && CTEntry::exactlyZero(i);
        };

        [[nodiscard]] inline bool exactlyOne() const {
            return CTEntry::exactlyOne(r) && CTEntry::exactlyZero(i);
        };

        [[nodiscard]] inline bool approximatelyZero() const {
            return CTEntry::approximatelyZero(r) && CTEntry::approximatelyZero(i);
        }

        [[nodiscard]] inline bool approximatelyOne() const {
            return CTEntry::approximatelyOne(r) && CTEntry::approximatelyZero(i);
        }

        static inline bool approximatelyEqual(const std::complex<fp>& x, const std::complex<fp>& y) {
            return CTEntry::approximatelyEquals(x.real(), y.real()) && CTEntry::approximatelyEquals(x.imag(), y.imag());
        }

        static inline bool approximatelyZero(const std::complex<fp> x) {
            return CTEntry::approximatelyZero(x.real()) && CTEntry::approximatelyZero(x.imag());
        }

        // Returns true iff a == -b, approximately
        bool approximatelyEqualsMinus(const Complex& c) const {
            bool rflip = false, iflip = false;
            // check if Real(a) = -Real(c)
            if (ComplexTable<>::Entry::approximatelyEquals(r, ComplexTable<>::Entry::flipPointerSign(c.r))) {
                rflip = true;
            }
            // Check if Im(a) = -Im(c)
            if (ComplexTable<>::Entry::approximatelyEquals(i, ComplexTable<>::Entry::flipPointerSign(c.i))) {
                iflip = true;
            }
//            std::cout << "[isTimesMinusOne] answer: " << ((rflip && iflip) ? "yes" : "no") << " because a=" << a.toString() << ", b=" << b.toString() << ", so realflip=" << rflip << ", imflip=" << iflip << std::endl;
            return rflip && iflip;
        }

        // Returns true iff this Complex number == +/- c
        //   (i.e, if this number is approximately equal to plus or minus c)
        inline bool approximatelyEqualsPlusMinus(const Complex& c) const {
        	if (approximatelyEquals(c)) return true;
        	if (approximatelyEqualsMinus(c)) return true;
        	return false;
        }

        // Returns a phase_t object, if this complex number is +1 or -1
        phase_t toPhasePMOne() const {
        	if (approximatelyEquals(Complex::one)) return phase_t::phase_one;
        	if (approximatelyEquals(Complex::minus_one)) return phase_t::phase_minus_one;
        	return phase_t::no_phase;
        }

        // Returns a phase_t object, if this complex number is +1, +i, -1, or -i.
        //  Otherwise, returns phase_t::no_phase
        phase_t toPhase() const {
        	if (approximatelyEquals(Complex::one))       return phase_t::phase_one;
        	if (approximatelyEquals(Complex::minus_one)) return phase_t::phase_minus_one;
        	if (approximatelyEquals(Complex::complex_i)) return phase_t::phase_i;
        	if (approximatelyEquals(Complex::minus_i))   return phase_t::phase_minus_i;
        	return phase_t::no_phase;
        }

        inline bool operator==(const Complex& other) const {
            return r == other.r && i == other.i;
        }

        inline bool operator!=(const Complex& other) const {
            return !operator==(other);
        }

        // TODO this function is only used in debugging; we could move it to a more suitable place
        static Complex minusOne() {
            Complex min = one;
            min.r       = ComplexTable<>::Entry::flipPointerSign(min.r);
            return min;
        }

        // Sets this complex value z to '-z'
        void multiplyByMinusOne([[maybe_unused]] bool cached = true) {
            if(Complex::zero == *this){
                return;
            }
//            if (cached) {
//                r->value = r->value * -1;
//                i->value = i->value * -1;
//            } else {
                r = CTEntry::flipPointerSign(r);
                i = CTEntry::flipPointerSign(i);
//            }
        }

        void multiplyByi() {
        	std::swap(r, i);
        	r = CTEntry::flipPointerSign(r);
        }

        void multiplyByMinusi() {
        	std::swap(r, i);
        	i = CTEntry::flipPointerSign(i);
        }

        void multiplyByPhase(dd::phase_t phase) {
        	switch(phase) {
        	case dd::phase_t::phase_i:
        		multiplyByi();
        		break;
        	case phase_t::phase_minus_one:
        		multiplyByMinusOne(true);
        		break;
        	case phase_t::phase_minus_i:
        		multiplyByMinusi();
        		break;
        	case phase_t::phase_one:
        	case phase_t::no_phase:
        		break;
        	}
        }

        [[nodiscard]] std::string toString(bool formatted = true, int precision = -1) const {
            return ComplexValue::toString(CTEntry::val(r), CTEntry::val(i), formatted, precision);
        }

        // Returns true if this=a+bi is lexicographically smaller than other=c+di,
        // which is true iff a<c or (a=c and b<d)
        bool lexSmallerThan(const Complex& other) const {
        	if (!ComplexTable<>::Entry::approximatelyEquals(r, other.r)) {
        		return ComplexTable<>::Entry::val(r) < ComplexTable<>::Entry::val(other.r);
        	}
        	if (!ComplexTable<>::Entry::approximatelyEquals(i, other.i)) {
        		return ComplexTable<>::Entry::val(i) < ComplexTable<>::Entry::val(other.i);
        	}
        	return false;
        }

        bool lexLargerThan(const Complex& other) const {
        	if (!ComplexTable<>::Entry::approximatelyEquals(r, other.r)) {
        		return ComplexTable<>::Entry::val(r) > ComplexTable<>::Entry::val(other.r);
        	}
        	if (!ComplexTable<>::Entry::approximatelyEquals(i, other.i)) {
        		return ComplexTable<>::Entry::val(i) > ComplexTable<>::Entry::val(other.i);
        	}
        	return false;
        }

        // Returns whether z=a+bi is lexicographically smaller than -z
        //   which is true iff
        //   a < 0, or a=0 and b<0
        bool lexSmallerThanxMinusOne() const {
            if (!ComplexTable<>::Entry::approximatelyZero(r)) {
                Log::log << "[lexSmallerThanxMinusOne] real part of " << toString() << " is not zero, so testing real part\n";
//                return !ComplexTable<>::Entry::isNegativePointer(i); // TODO limdd this may be faster than current implementation on next line
                return ComplexTable<>::Entry::val(r) < 0;
            }
            if (!ComplexTable<>::Entry::approximatelyZero(i)) {
                Log::log << "[lexSmallerThanxMinusOne] imag part of " << toString() << " is not zero\n";
//                return !ComplexTable<>::Entry::isNegativePointer(r); // TODO limdd this may be faster than current implementation on next line
                return ComplexTable<>::Entry::val(i) < 0;
            }
            return false;
        }

        bool lexLargerThanxMinusOne() const {
            if (!ComplexTable<>::Entry::approximatelyZero(r)) {
//                std::cout << "[lexSmallerThanxMinusOne] real part of " << toString() << " is not zero.\n";
//                return !ComplexTable<>::Entry::isNegativePointer(r); // TODO limdd this may be faster than current implementation on next line
                return ComplexTable<>::Entry::val(r) > 0;
            }
            if (!ComplexTable<>::Entry::approximatelyZero(i)) {
//                std::cout << "[lexSmallerThanxMinusOne] imag is not zero in " << toString() << "\n";
//                return !ComplexTable<>::Entry::isNegativePointer(i); // TODO limdd this may be faster than current implementation on next line
                return ComplexTable<>::Entry::val(i) > 0;
            }
            return false;
        }

        void writeBinary(std::ostream& os) const {
            CTEntry::writeBinary(r, os);
            CTEntry::writeBinary(i, os);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Complex& c) {
        return os << c.toString();
    }

    inline Complex Complex::zero     {                            &ComplexTable<>::zero,                             &ComplexTable<>::zero};
    inline Complex Complex::one      {                            &ComplexTable<>::one,                              &ComplexTable<>::zero};
    inline Complex Complex::minus_one{CTEntry::getNegativePointer(&ComplexTable<>::one),                             &ComplexTable<>::zero};
    inline Complex Complex::complex_i{                            &ComplexTable<>::zero,                             &ComplexTable<>::one};
    inline Complex Complex::minus_i  {                            &ComplexTable<>::zero, CTEntry::getNegativePointer(&ComplexTable<>::one)};
} // namespace dd

namespace std {
    template<>
    struct hash<dd::Complex> {
        std::size_t operator()(dd::Complex const& c) const noexcept {
            auto h1 = dd::murmur64(reinterpret_cast<std::size_t>(c.r));
            auto h2 = dd::murmur64(reinterpret_cast<std::size_t>(c.i));
            return dd::combineHash(h1, h2);
        }
    };
} // namespace std

#endif //DD_PACKAGE_COMPLEX_HPP
