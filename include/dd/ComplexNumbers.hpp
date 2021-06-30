/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDcomplex_H
#define DDcomplex_H

#include "Complex.hpp"
#include "ComplexCache.hpp"
#include "ComplexTable.hpp"
#include "ComplexValue.hpp"
#include "Definitions.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>

namespace dd {
    struct ComplexNumbers {
        ComplexTable<> complexTable{};
        ComplexCache<> complexCache{};

        ComplexNumbers()  = default;
        ~ComplexNumbers() = default;

        void clear() {
            complexTable.clear();
            complexCache.clear();
        }

        static void setTolerance(fp tol) {
            ComplexTable<>::setTolerance(tol);
        }

        // operations on complex numbers
        // meanings are self-evident from the names
        static void add(Complex& r, const Complex& a, const Complex& b) {
            assert(r != Complex::zero);
            assert(r != Complex::one);
            if (a.approximatelyZero()) {
                r.setVal(b);
            } else if (b.approximatelyZero()) {
                r.setVal(a);
            } else {
                const auto& aMag   = a.mag->value;
                const auto& aPhase = CTEntry::val(a.phase);
                const auto& bMag   = b.mag->value;
                const auto& bPhase = CTEntry::val(b.phase);

                //                std::cout << ComplexValue::toString(aMag, aPhase) << " + " << ComplexValue::toString(bMag, bPhase) << " = ";

                const auto minmax    = std::minmax(aPhase, bPhase);
                const auto diff      = minmax.second - minmax.first;
                const auto nearby    = std::nearbyint(diff);
                const auto closeness = std::abs(diff - nearby);

                if (closeness < decltype(complexTable)::tolerance()) {
                    if ((static_cast<std::uint64_t>(nearby) % 2) == 0) {
                        // same phase
                        r.mag->value   = aMag + bMag;
                        r.phase->value = aPhase;
                    } else {
                        // opposing phase
                        if (std::abs(aMag - bMag) < decltype(complexTable)::tolerance()) {
                            r.mag->value   = 0.;
                            r.phase->value = 0.;
                        } else if (aMag > bMag) {
                            r.mag->value   = aMag - bMag;
                            r.phase->value = aPhase;
                        } else {
                            r.mag->value   = bMag - aMag;
                            r.phase->value = bPhase;
                        }
                    }
                } else {
                    // general case
                    auto c         = std::polar(aMag, aPhase * PI) + std::polar(bMag, bPhase * PI);
                    r.mag->value   = std::abs(c);
                    r.phase->value = std::arg(c) * PIinv;
                }
                //                std::cout << r << std::endl;
            }
        }
        static void sub(Complex& r, const Complex& a, const Complex& b) {
            assert(r != Complex::zero);
            assert(r != Complex::one);
            if (b.approximatelyZero()) {
                r.setVal(a);
            } else if (a.approximatelyZero()) {
                r.setVal(b);
                r.phase->value += 1.0;
            } else {
                const auto& aMag   = a.mag->value;
                const auto& aPhase = CTEntry::val(a.phase);
                const auto& bMag   = b.mag->value;
                const auto& bPhase = CTEntry::val(b.phase);

                if (std::abs(aPhase - bPhase) < decltype(complexTable)::tolerance()) {
                    r.mag->value   = aMag - bMag;
                    r.phase->value = aPhase;
                } else {
                    auto c         = std::polar(aMag, aPhase * PI) - std::polar(bMag, bPhase * PI);
                    r.mag->value   = std::abs(c);
                    r.phase->value = std::arg(c) * PIinv;
                }
            }
        }
        static void mul(Complex& r, const Complex& a, const Complex& b) {
            assert(r != Complex::zero);
            assert(r != Complex::one);
            if (a.approximatelyOne()) {
                r.setVal(b);
            } else if (b.approximatelyOne()) {
                r.setVal(a);
            } else if (a.approximatelyZero() || b.approximatelyZero()) {
                r.mag->value   = 0.;
                r.phase->value = 0.;
            } else {
                r.mag->value   = a.mag->value * b.mag->value;
                r.phase->value = CTEntry::val(a.phase) + CTEntry::val(b.phase);
            }
        }
        static void div(Complex& r, const Complex& a, const Complex& b) {
            assert(r != Complex::zero);
            assert(r != Complex::one);
            if (a.approximatelyEquals(b)) {
                r.mag->value   = 1.;
                r.phase->value = 0.;
            } else if (a.approximatelyZero()) {
                r.mag->value   = 0.;
                r.phase->value = 0.;
            } else if (b.approximatelyOne()) {
                r.setVal(a);
            } else {
                r.mag->value   = a.mag->value / b.mag->value;
                r.phase->value = CTEntry::val(a.phase) - CTEntry::val(b.phase);
            }
        }
        static inline fp mag2(const Complex& a) {
            auto mag = a.mag->value;
            return mag * mag;
        }
        static inline fp mag(const Complex& a) {
            return a.mag->value;
        }
        static inline fp arg(const Complex& a) {
            return CTEntry::val(a.phase) * PI;
        }
        static Complex conj(const Complex& a) {
            auto ret = a;
            if (a.phase != &ComplexTable<>::zero && a.phase != &ComplexTable<>::one) {
                ret.phase = CTEntry::flipPointerSign(a.phase);
            }
            return ret;
        }
        static void neg(Complex& r, const Complex& a) {
            assert(r.phase != &ComplexTable<>::zero);
            assert(r.phase != &ComplexTable<>::one);
            r.mag            = a.mag;
            const auto phase = CTEntry::val(a.phase) + 1.0;
            r.phase          = CTEntry::getAlignedPointer(r.phase);
            r.phase->value   = phase;
        }

        inline Complex addCached(const Complex& a, const Complex& b) {
            auto c = getCached();
            add(c, a, b);
            return c;
        }

        inline Complex subCached(const Complex& a, const Complex& b) {
            auto c = getCached();
            sub(c, a, b);
            return c;
        }

        inline Complex mulCached(const Complex& a, const Complex& b) {
            auto c = getCached();
            mul(c, a, b);
            return c;
        }

        inline Complex divCached(const Complex& a, const Complex& b) {
            auto c = getCached();
            div(c, a, b);
            return c;
        }

        // lookup a complex value in the complex table; if not found add it
        Complex lookup(const Complex& c) {
            if (c == Complex::zero) {
                return Complex::zero;
            }
            if (c == Complex::one) {
                return Complex::one;
            }

            auto mag   = c.mag->value;
            auto phase = CTEntry::val(c.phase);
            return lookup(mag, phase);
        }
        Complex lookup(const fp& mag, const fp& phase) {
            Complex ret{};
            assert(mag >= 0.);
            ret.mag = complexTable.lookup(mag);

            auto normalizedPhase = std::remainder(phase, 2.0);
            auto signPhase       = std::signbit(normalizedPhase);
            if (signPhase) {
                auto absPhase = std::abs(normalizedPhase);
                if (absPhase < decltype(complexTable)::tolerance()) {
                    // if absolute value is close enough to zero, just return the zero entry (avoiding -0.0)
                    ret.phase = &decltype(complexTable)::zero;
                } else if (std::abs(absPhase - 1.0) < decltype(complexTable)::tolerance()) {
                    // if absolute value is close enough to one, just return the one entry (avoiding -1.0)
                    ret.phase = &decltype(complexTable)::one;
                } else {
                    ret.phase = CTEntry::getNegativePointer(complexTable.lookup(absPhase));
                }
            } else {
                ret.phase = complexTable.lookup(normalizedPhase);
            }

            return ret;
        }
        inline Complex lookup(const ComplexValue& c) { return lookup(c.mag, c.phase); }

        // reference counting and garbage collection
        static void incRef(const Complex& c) {
            // `zero` and `one` are static and never altered
            if (c != Complex::zero && c != Complex::one) {
                ComplexTable<>::incRef(c.mag);
                ComplexTable<>::incRef(c.phase);
            }
        }
        static void decRef(const Complex& c) {
            // `zero` and `one` are static and never altered
            if (c != Complex::zero && c != Complex::one) {
                ComplexTable<>::decRef(c.mag);
                ComplexTable<>::decRef(c.phase);
            }
        }
        std::size_t garbageCollect(bool force = false) {
            return complexTable.garbageCollect(force);
        }

        // provide (temporary) cached complex number
        inline Complex getTemporary() {
            return complexCache.getTemporaryComplex();
        }

        inline Complex getTemporary(const fp& mag, const fp& phase) {
            auto c         = complexCache.getTemporaryComplex();
            c.mag->value   = mag;
            c.phase->value = phase;
            return c;
        }

        inline Complex getTemporary(const ComplexValue& c) {
            return getTemporary(c.mag, c.phase);
        }

        inline Complex getCached() {
            return complexCache.getCachedComplex();
        }

        inline Complex getCached(const fp& mag, const fp& phase) {
            auto c         = complexCache.getCachedComplex();
            c.mag->value   = mag;
            c.phase->value = phase;
            return c;
        }

        inline Complex getCached(const ComplexValue& c) {
            return getCached(c.mag, c.phase);
        }

        void returnToCache(Complex& c) {
            complexCache.returnToCache(c);
        }

        [[nodiscard]] std::size_t cacheCount() const {
            return complexCache.getCount();
        }
    };
} // namespace dd
#endif
