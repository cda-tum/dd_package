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


