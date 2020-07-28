#include <memory>

#include "DDpackage.h"
#include "util.h"
#include "gtest/gtest.h"

TEST(DDPackageTest, TrivialTest) {
    auto dd = std::make_unique<dd::Package>();

    short line[2] = {2};
    dd::Edge x_gate = dd->makeGateDD(Xmat, 1, line);
    dd::Edge h_gate = dd->makeGateDD(Hmat, 1, line);

    ASSERT_EQ(dd->getValueByPath(h_gate, "0"), (dd::ComplexValue{dd::SQRT_2, 0}));

    dd::Edge zero_state = dd->makeZeroState(1);
    dd::Edge h_state = dd->multiply(h_gate, zero_state);
    dd::Edge one_state = dd->multiply(x_gate, zero_state);

    ASSERT_EQ(dd->fidelity(zero_state, one_state), 0.0);
    ASSERT_NEAR(dd->fidelity(zero_state, h_state), 0.5, dd::ComplexNumbers::TOLERANCE);
    ASSERT_NEAR(dd->fidelity(one_state, h_state), 0.5, dd::ComplexNumbers::TOLERANCE);
}

TEST(DDPackageTest, BellState) {
    auto dd = std::make_unique<dd::Package>();

    short line[2] = {-1,2};
    dd::Edge h_gate = dd->makeGateDD(Hmat, 2, line);
    dd::Edge cx_gate = dd->makeGateDD({Xmat[0][0], Xmat[0][1], Xmat[1][0], Xmat[1][1]}, 2, {2,1});
    dd::Edge zero_state = dd->makeZeroState(2);

    dd::Edge bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    ASSERT_EQ(dd->getValueByPath(bell_state, "00"), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "02"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "20"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "22"), (dd::ComplexValue{dd::SQRT_2, 0}));

    ASSERT_DOUBLE_EQ(dd->fidelity(zero_state, bell_state), 0.5);
}

TEST(DDPackageTest, IdentifyTrace) {
    auto dd = std::make_unique<dd::Package>();
    auto fullTrace = dd->trace(dd->makeIdent(0, 3));

    ASSERT_EQ(fullTrace, (dd::ComplexValue{16,0}));
}

TEST(DDPackageTest, BaseConversion) {
    short line[3] = {2, -1, -1};
    auto dd = std::make_unique<dd::Package>();
    dd::Edge e_comp = dd->multiply(dd->makeGateDD(Hmat, 3, line), dd->makeZeroState(3));
    line[0] = -1;
    line[1] = 2;
    e_comp = dd->multiply(dd->makeGateDD(Hmat, 3, line), e_comp);
    line[1] = -1;
    line[2] = 2;
    e_comp = dd->multiply(dd->makeGateDD(Hmat, 3, line), e_comp);
    line[2] = -1;
    line[0] = 2;
    e_comp = dd->multiply(dd->makeGateDD(Xmat, 3, line), e_comp);
    dd::Edge e_hadamard = dd->multiply(dd->makeGateDD(Zmat, 3, line), dd->makeZeroState(3));

    dd->export2Dot(e_hadamard, "e_hadamard", true);
    dd::Edge e_comp_conv = dd->convert(e_hadamard, dd::Basis::Hadamard, dd::Basis::Computational);
    dd->export2Dot(e_comp, "e_comp", true);
    dd->export2Dot(e_comp_conv, "e_comp_conv", true);
    EXPECT_TRUE(dd->equals(e_comp, e_comp_conv));
}

TEST(DDPackageTest, ConvertAmplitudes) {
    const fp TOL = 1e-10;
    auto dd = std::make_unique<dd::Package>();    
    unsigned short nqubits = 2;
    short line[2] = {-1, 2};

    dd::Edge e = dd->makeZeroState(nqubits);
    e = dd->multiply(dd->makeGateDD(Hmat, nqubits, line), e);
    e = dd->multiply(dd->makeGateDD(Xmat, nqubits, line), e);
    line[0] = 2;
    line[1] = 1;
    e = dd->multiply(dd->makeGateDD(Xmat, nqubits, line), e);

    dd::Complex comp00 = dd->cn.lookup(dd->getValueByPath(e, "00"));
    dd::Complex comp01 = dd->cn.lookup(dd->getValueByPath(e, "02"));
    dd::Complex comp10 = dd->cn.lookup(dd->getValueByPath(e, "20"));
    dd::Complex comp11 = dd->cn.lookup(dd->getValueByPath(e, "22"));

    dd::Complex hada00 = dd->cn.addCached(comp00, comp01);
    dd->cn.add(hada00, hada00, comp10);
    dd->cn.add(hada00, hada00, comp11);
    dd->cn.div(hada00, hada00, dd->cn.getTempCachedComplex(2, 0));

    dd::Complex hada01 = dd->cn.subCached(comp00, comp01);
    dd->cn.add(hada01, hada01, comp10);
    dd->cn.sub(hada01, hada01, comp11);
    dd->cn.div(hada01, hada01, dd->cn.getTempCachedComplex(2, 0));

    dd::Complex hada10 = dd->cn.addCached(comp00, comp01);
    dd->cn.sub(hada10, hada10, comp10);
    dd->cn.sub(hada10, hada10, comp11);
    dd->cn.div(hada10, hada10, dd->cn.getTempCachedComplex(2, 0));
    
    dd::Complex hada11 = dd->cn.subCached(comp00, comp01);
    dd->cn.sub(hada11, hada11, comp10);
    dd->cn.add(hada11, hada11, comp11);
    dd->cn.div(hada11, hada11, dd->cn.getTempCachedComplex(2, 0));

    std::map<std::string, dd::ComplexValue> amplitudes;
    dd->convertAmplitudes(e, nqubits, amplitudes, dd::Basis::Hadamard, dd::Basis::Computational);

    EXPECT_TRUE(fabs(amplitudes["00"].r - hada00.r->val) < TOL && fabs(amplitudes["00"].i - hada00.i->val) < TOL);
    EXPECT_TRUE(fabs(amplitudes["02"].r - hada01.r->val) < TOL && fabs(amplitudes["02"].i - hada01.i->val) < TOL);
    EXPECT_TRUE(fabs(amplitudes["20"].r - hada10.r->val) < TOL && fabs(amplitudes["20"].i - hada10.i->val) < TOL);
    EXPECT_TRUE(fabs(amplitudes["22"].r - hada11.r->val) < TOL && fabs(amplitudes["22"].i - hada11.i->val) < TOL);
}

TEST(DDPackageTest, CompareAmplitudes) {
    auto dd = std::make_unique<dd::Package>();
    std::map<std::string, dd::ComplexValue> ref;
    std::map<std::string, dd::ComplexValue> amp;

    ref["00"] = {1, 0};
    ref["02"] = {0, 0};
    ref["20"] = {0.5, 0};
    ref["22"] = {0, 0.3};

    amp["00"] = {1, 0};
    amp["02"] = {0, 0};
    amp["20"] = {0.5, 0};
    amp["22"] = {0, 0.3};

    EXPECT_TRUE(dd->compareAmplitudes(ref, amp));
    
    amp["22"] = {0, 0};
    EXPECT_FALSE(dd->compareAmplitudes(ref, amp));
}
