/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "DDcomplex.hpp"

#include "gtest/gtest.h"
#include <memory>

using namespace dd;
using CN = ComplexNumbers;

TEST(DDComplexTest, TrivialTest) {
    auto         cn           = std::make_unique<ComplexNumbers>();
    unsigned int before_count = cn->count;

    auto a = cn->getCachedComplex(2, -3);
    auto b = cn->getCachedComplex(3, 2);

    auto r0 = cn->getCachedComplex(12, -5);
    auto r1 = cn->mulCached(a, b);

    ASSERT_PRED2(static_cast<bool (*)(const Complex&, const Complex&)>(ComplexNumbers::equals), r0, r1);

    cn->lookup(a);
    cn->lookup(b);
    unsigned int between_count = cn->count;
    // the lookup increases the count in the complex table
    ASSERT_LT(before_count, between_count);
    cn->releaseCached(a);
    cn->releaseCached(b);
    cn->releaseCached(r0);
    cn->releaseCached(r1);
    cn->garbageCollect(true);
    // since lookup does not increase the ref count, garbage collection removes the new values
    unsigned int end_count = cn->count;
    ASSERT_EQ(before_count, end_count);
}

TEST(DDComplexTest, ComplexNumberCreation) {
    auto cn = ComplexNumbers();
    EXPECT_EQ(cn.lookup(cn.ZERO), cn.ZERO);
    EXPECT_EQ(cn.lookup(cn.ONE), cn.ONE);
    EXPECT_EQ(cn.lookup(1e-14, 0.), cn.ZERO);
    EXPECT_EQ(cn.val(cn.lookup(1e-14, 1.).r), 0.);
    EXPECT_EQ(cn.val(cn.lookup(1e-14, 1.).i), 1.);
    EXPECT_EQ(cn.val(cn.lookup(1e-14, -1.).r), 0.);
    EXPECT_EQ(cn.val(cn.lookup(1e-14, -1.).i), -1.);
    EXPECT_EQ(cn.val(cn.lookup(-1., -1.).r), -1.);
    EXPECT_EQ(cn.val(cn.lookup(-1., -1.).i), -1.);
    auto c = cn.lookup(0., -1.);
    std::cout << c << std::endl;
    EXPECT_EQ(cn.val(cn.lookup(c).r), 0.);
    EXPECT_EQ(cn.val(cn.lookup(c).i), -1.);
    c = cn.lookup(0., 1.);
    EXPECT_EQ(cn.val(cn.lookup(c).r), 0.);
    EXPECT_EQ(cn.val(cn.lookup(c).i), 1.);
    c = cn.lookup(0., -0.5);
    std::cout << c << std::endl;
    EXPECT_EQ(cn.val(cn.lookup(c).r), 0.);
    EXPECT_EQ(cn.val(cn.lookup(c).i), -0.5);
    c = cn.lookup(-1., -1.);
    EXPECT_EQ(cn.val(cn.lookup(c).r), -1.);
    EXPECT_EQ(cn.val(cn.lookup(c).i), -1.);
    std::cout << c << std::endl;

    auto e = cn.lookup(1., -1.);
    std::cout << e << std::endl;
    std::cout << ComplexValue{1., 1.} << std::endl;
    std::cout << ComplexValue{1., -1.} << std::endl;
    std::cout << ComplexValue{1., -0.5} << std::endl;
    cn.printComplexTable();
    cn.statistics();
    std::cout << "Cache size: " << cn.cacheSize() << std::endl;
}

TEST(DDComplexTest, ComplexNumberArithmetic) {
    auto cn = ComplexNumbers();
    auto c  = cn.lookup(0., 1.);
    auto d  = ComplexNumbers::conj(c);
    EXPECT_EQ(cn.val(d.r), 0.);
    EXPECT_EQ(cn.val(d.i), -1.);
    c = cn.lookup(-1., -1.);
    d = ComplexNumbers::neg(c);
    EXPECT_EQ(cn.val(d.r), 1.);
    EXPECT_EQ(cn.val(d.i), 1.);
    c = cn.lookup(0.5, 0.5);
    ComplexNumbers::incRef(c);
    d = cn.lookup(-0.5, 0.5);
    ComplexNumbers::incRef(d);
    auto e = cn.getTempCachedComplex();
    ComplexNumbers::sub(e, c, d);
    ComplexNumbers::decRef(c);
    ComplexNumbers::decRef(d);
    e = cn.lookup(e);
    EXPECT_EQ(e, cn.ONE);
    auto f = cn.getTempCachedComplex();
    ComplexNumbers::div(f, ComplexNumbers::ZERO, ComplexNumbers::ONE);
}

TEST(DDComplexTest, NearZeroLookup) {
    auto cn = ComplexNumbers();
    auto c  = cn.getTempCachedComplex(ComplexNumbers::TOLERANCE / 10., ComplexNumbers::TOLERANCE / 10.);
    auto d  = cn.lookup(c);
    EXPECT_EQ(d.r, cn.ZERO.r);
    EXPECT_EQ(d.i, cn.ZERO.i);
}

TEST(DDComplexTest, GarbageCollectSomeInBucket) {
    auto cn = ComplexNumbers();

    fp num = 0.25;
    cn.lookup(num, 0.0);

    fp num2 = num + 2. * ComplexNumbers::TOLERANCE;
    ComplexNumbers::incRef(cn.lookup(num2, 0.0)); // num2 should be placed in same bucket as num

    auto key = ComplexNumbers::getKey(num);
    EXPECT_NEAR(cn.ComplexTable[key]->val, num2, ComplexNumbers::TOLERANCE);
    EXPECT_NEAR(cn.ComplexTable[key]->next->val, num, ComplexNumbers::TOLERANCE);

    cn.garbageCollect(true); // num should be collected
    EXPECT_NEAR(cn.ComplexTable[key]->val, num2, ComplexNumbers::TOLERANCE);
    EXPECT_EQ(cn.ComplexTable[key]->next, nullptr);
}

TEST(DDComplexTest, LookupInNeighbouringBuckets) {
    auto cn = ComplexNumbers();

    // lower border of a bucket
    fp bucketBorder = 0.25 * ComplexNumbers::NBUCKET / (ComplexNumbers::NBUCKET - 1);

    // insert a number slightly away from the border
    fp num = bucketBorder + 2 * ComplexNumbers::TOLERANCE;
    cn.lookup(num, 0.0);
    auto key = ComplexNumbers::getKey(num);
    EXPECT_EQ(key, ComplexNumbers::NBUCKET / 4);

    // insert a number barely in the bucket below
    fp num2 = bucketBorder - ComplexNumbers::TOLERANCE / 10;
    cn.lookup(num2, 0.0);
    auto key2 = ComplexNumbers::getKey(num2);
    EXPECT_EQ(key2, ComplexNumbers::NBUCKET / 4 - 1);

    // insert another number in the bucket below a bit farther away from the border
    fp num3 = bucketBorder - 2 * ComplexNumbers::TOLERANCE;
    cn.lookup(num3, 0.0);
    auto key3 = ComplexNumbers::getKey(num3);
    EXPECT_EQ(key3, ComplexNumbers::NBUCKET / 4 - 1);

    // insert border number that is too far away from the number in the bucket, but is close enough to a number in the bucket below
    fp   num4 = bucketBorder;
    auto c    = cn.lookup(num4, 0.0);
    auto key4 = ComplexNumbers::getKey(num4 - ComplexNumbers::TOLERANCE);
    EXPECT_EQ(key2, key4);
    EXPECT_NEAR(c.r->val, num2, ComplexNumbers::TOLERANCE);

    // insert a number in the higher bucket
    fp nextBorder = bucketBorder + 1.0 / (ComplexNumbers::NBUCKET - 1);
    fp num5       = nextBorder;
    cn.lookup(num5, 0.0);
    auto key5 = ComplexNumbers::getKey(num5);
    EXPECT_EQ(key5, ComplexNumbers::NBUCKET / 4 + 1);

    // search for a number in the lower bucket that is ultimately close enough to a number in the upper bucket
    fp   num6 = nextBorder - ComplexNumbers::TOLERANCE / 10;
    auto d    = cn.lookup(num6, 0.0);
    auto key6 = ComplexNumbers::getKey(num6 + ComplexNumbers::TOLERANCE);
    EXPECT_EQ(key5, key6);
    EXPECT_NEAR(d.r->val, num5, ComplexNumbers::TOLERANCE);
}

TEST(DDComplexTest, ComplexValueEquals) {
    ComplexValue a{1.0, 0.0};
    ComplexValue a_tol{1.0 + ComplexNumbers::TOLERANCE / 10, 0.0};
    ComplexValue b{0.0, 1.0};
    EXPECT_TRUE(ComplexNumbers::equals(a, a_tol));
    EXPECT_FALSE(ComplexNumbers::equals(a, b));
}

TEST(DDComplexTest, NumberPrinting) {
    auto cn       = ComplexNumbers();
    auto imag     = cn.lookup(0., 1.);
    auto imag_str = ComplexNumbers::toString(imag, false);
    EXPECT_STREQ(imag_str.c_str(), "1i");
    auto imag_str_formatted = ComplexNumbers::toString(imag, true);
    EXPECT_STREQ(imag_str_formatted.c_str(), "+i");

    auto superposition     = cn.lookup(dd::SQRT2_2, dd::SQRT2_2);
    auto superposition_str = ComplexNumbers::toString(superposition, false, 3);
    EXPECT_STREQ(superposition_str.c_str(), "0.707+0.707i");
    auto superposition_str_formatted = ComplexNumbers::toString(superposition, true, 3);
    EXPECT_STREQ(superposition_str_formatted.c_str(), "√½(1+i)");
    auto neg_superposition               = cn.lookup(dd::SQRT2_2, -dd::SQRT2_2);
    auto neg_superposition_str_formatted = ComplexNumbers::toString(neg_superposition, true, 3);
    EXPECT_STREQ(neg_superposition_str_formatted.c_str(), "√½(1-i)");

    std::stringstream ss{};
    ComplexNumbers::printFormattedReal(ss, dd::SQRT2_2, false);
    EXPECT_STREQ(ss.str().c_str(), "√½");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, dd::SQRT2_2, true);
    EXPECT_STREQ(ss.str().c_str(), "+√½i");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, 0.5, false);
    EXPECT_STREQ(ss.str().c_str(), "½");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, 0.5, true);
    EXPECT_STREQ(ss.str().c_str(), "+½i");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, 0.5 * dd::SQRT2_2, false);
    EXPECT_STREQ(ss.str().c_str(), "√½ ½");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, 0.5 * dd::SQRT2_2, true);
    EXPECT_STREQ(ss.str().c_str(), "+√½ ½i");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, 0.25, false);
    EXPECT_STREQ(ss.str().c_str(), "½**2");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, 0.25, true);
    EXPECT_STREQ(ss.str().c_str(), "+½**2i");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, 0.25 * dd::SQRT2_2, false);
    EXPECT_STREQ(ss.str().c_str(), "√½ ½**2");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, 0.25 * dd::SQRT2_2, true);
    EXPECT_STREQ(ss.str().c_str(), "+√½ ½**2i");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, dd::PI, false);
    EXPECT_STREQ(ss.str().c_str(), "π");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, dd::PI, true);
    EXPECT_STREQ(ss.str().c_str(), "+πi");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, 0.5 * dd::PI, false);
    EXPECT_STREQ(ss.str().c_str(), "½ π");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, 0.5 * dd::PI, true);
    EXPECT_STREQ(ss.str().c_str(), "+½ πi");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, 0.25 * dd::PI, false);
    EXPECT_STREQ(ss.str().c_str(), "½**2 π");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, 0.25 * dd::PI, true);
    EXPECT_STREQ(ss.str().c_str(), "+½**2 πi");
    ss.str("");

    ComplexNumbers::printFormattedReal(ss, 0.1234, false);
    EXPECT_STREQ(ss.str().c_str(), "0.1234");
    ss.str("");
    ComplexNumbers::printFormattedReal(ss, 0.1234, true);
    EXPECT_STREQ(ss.str().c_str(), "+0.1234i");
    ss.str("");
}

TEST(DDComplexTest, MaxRefCountReached) {
    auto cn  = ComplexNumbers();
    auto c   = cn.lookup(SQRT2_2, SQRT2_2);
    auto max = std::numeric_limits<decltype(c.r->ref)>::max();
    c.r->ref = max;
    CN::incRef(c);
    EXPECT_EQ(c.r->ref, max);
    EXPECT_EQ(c.i->ref, max);
}
