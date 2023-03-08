/*
 * This file is part of the MQT DD Package which is released under the MIT license.
 * See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
 */

#ifndef DDcomplex_H
#define DDcomplex_H

#include "Complex.hpp"
#include "ComplexCache.hpp"
#include "ComplexTable.hpp"
#include "ComplexValue.hpp"
#include "Definitions.hpp"
#include <iostream>

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
            r.r->value = CTEntry::val(a.r) + CTEntry::val(b.r);
            r.i->value = CTEntry::val(a.i) + CTEntry::val(b.i);
        }
        static void sub(Complex& r, const Complex& a, const Complex& b) {
            assert(r != Complex::zero);
            assert(r != Complex::one);
            r.r->value = CTEntry::val(a.r) - CTEntry::val(b.r);
            r.i->value = CTEntry::val(a.i) - CTEntry::val(b.i);
        }
        static void mul(Complex& r, const Complex& a, const Complex& b) {
            assert(r != Complex::zero);
            assert(r != Complex::one);
            if (a.approximatelyOne()) {
                r.setVal(b);
            } else if (b.approximatelyOne()) {
                r.setVal(a);
            } else if (a.approximatelyZero() || b.approximatelyZero()) {
                r.r->value = 0.;
                r.i->value = 0.;
            } else {
                const auto ar = CTEntry::val(a.r);
                const auto ai = CTEntry::val(a.i);
                const auto br = CTEntry::val(b.r);
                const auto bi = CTEntry::val(b.i);

                r.r->value = ar * br - ai * bi;
                r.i->value = ar * bi + ai * br;
            }
        }
        static void div(Complex& r, const Complex& a, const Complex& b) {
            assert(r != Complex::zero);
            assert(r != Complex::one);
            if (a.approximatelyEquals(b)) {
                r.r->value = 1.;
                r.i->value = 0.;
            } else if (b.approximatelyOne()) {
                r.setVal(a);
            } else {
                const auto ar = CTEntry::val(a.r);
                const auto ai = CTEntry::val(a.i);
                const auto br = CTEntry::val(b.r);
                const auto bi = CTEntry::val(b.i);

                const auto cmag = br * br + bi * bi;

                r.r->value = (ar * br + ai * bi) / cmag;
                r.i->value = (ai * br - ar * bi) / cmag;
            }
        }
        static inline fp mag2(const Complex& a) {
            auto ar = CTEntry::val(a.r);
            auto ai = CTEntry::val(a.i);

            return ar * ar + ai * ai;
        }
        static inline fp mag(const Complex& a) { // TODO LV: this introduces numerical inaccuracy in the case when a is a purely real, or purely imaginary number, i.e., is not a complex number. Perhaps better to take this into account, as follows?
//            if (CTEntry::val(a.i) == 0) return CTEntry::val(a.r); // TODO LV: use appropriate code to check "is equal to zero"
//            if (CTEntry::val(a.r) == 0) return CTEntry::val(a.i);
            return std::sqrt(mag2(a));
        }
        static inline fp arg(const Complex& a) {
            auto ar = CTEntry::val(a.r);
            auto ai = CTEntry::val(a.i);
            return std::atan2(ai, ar);
        }
        static Complex conj(const Complex& a) {
            auto ret = a;
            ret.i    = CTEntry::flipPointerSign(a.i);
            return ret;
        }
        static Complex neg(const Complex& a) {
            auto ret = a;
            ret.i    = CTEntry::flipPointerSign(a.i);
            ret.r    = CTEntry::flipPointerSign(a.r);
            return ret;
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

            auto valr = CTEntry::val(c.r);
            auto vali = CTEntry::val(c.i);
            return lookup(valr, vali);
        }
        Complex lookup(const fp& r, const fp& i) {
//        	std::cout << "[lookup 1/3] looking up value real = " << r << " imag = " << i << std::endl;
            Complex ret{};

            auto sign_r = std::signbit(r);
//            std::cout << "[lookup] sign_r = " << sign_r << '\n';
            if (sign_r) {
//				std::cout << "[lookup 1.5/3] sign bit true.\n";
                auto absr = std::abs(r);
                // if absolute value is close enough to zero, just return the zero entry (avoiding -0.0)
                if (absr < decltype(complexTable)::tolerance()) {
                    ret.r = &decltype(complexTable)::zero;
                } else {
                    ret.r = CTEntry::getNegativePointer(complexTable.lookup(absr));
                }
            } else {
//            	std::cout << "[lookup 1.5/3] sign bit false.\n";
                ret.r = complexTable.lookup(r);
            }
//            std::cout << "[lookup 2/3] ret.r = " << ret.r->value << '\n';

            auto sign_i = std::signbit(i);
//            std::cout << "[lookup] sign_i = " << sign_i << std::endl;
            if (sign_i) {
                auto absi = std::abs(i);
                // if absolute value is close enough to zero, just return the zero entry (avoiding -0.0)
                if (absi < decltype(complexTable)::tolerance()) {
                    ret.i = &decltype(complexTable)::zero;
                } else {
                    ret.i = CTEntry::getNegativePointer(complexTable.lookup(absi));
                }
            } else {
                ret.i = complexTable.lookup(i);
            }

//            std::cout << "[lookup 3/3] ret = " << ret << "\n";

            return ret;
        }
        inline Complex lookup(const ComplexValue& c) { return lookup(c.r, c.i); }

        // reference counting and garbage collection
        static void incRef(const Complex& c) {
            // `zero` and `one` are static and never altered
            if (c != Complex::zero && c != Complex::one) {
                ComplexTable<>::incRef(c.r);
                ComplexTable<>::incRef(c.i);
            }
        }
        static void decRef(const Complex& c) {
            // `zero` and `one` are static and never altered
            if (c != Complex::zero && c != Complex::one) {
                ComplexTable<>::decRef(c.r);
                ComplexTable<>::decRef(c.i);
            }
        }
        std::size_t garbageCollect(bool force = false) {
            return complexTable.garbageCollect(force);
        }

        // provide (temporary) cached complex number
        inline Complex getTemporary() {
            return complexCache.getTemporaryComplex();
        }

        inline Complex getTemporary(const fp& r, const fp& i) {
            auto c     = complexCache.getTemporaryComplex();
            c.r->value = r;
            c.i->value = i;
            return c;
        }

        inline Complex getTemporary(const ComplexValue& c) {
            return getTemporary(c.r, c.i);
        }

        inline Complex getCached() {
            return complexCache.getCachedComplex();
        }

        inline Complex getCached(const fp& r, const fp& i) {
            auto c     = complexCache.getCachedComplex();
            c.r->value = r;
            c.i->value = i;
            return c;
        }

        inline Complex getCached(const ComplexValue& c) {
            return getCached(c.r, c.i);
        }

        // TODO limdd LV: I added this function; is that ok? was there a reason it wasn't there before?
        inline Complex getCached(const Complex& c) {
        	return getCached(CTEntry::val(c.r), CTEntry::val(c.i));
        }

        inline Complex getCachedIfNonzero(const Complex& c) {
            if (!c.exactlyZero()) {
                Complex result = getCached(c);
                return result;
                //return getCached(c);
            }
            else return Complex::zero;
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
