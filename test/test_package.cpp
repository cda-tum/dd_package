/*
 * This file is part of the MQT DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "dd/Export.hpp"
#include "dd/GateMatrixDefinitions.hpp"
#include "dd/Package.hpp"

#include "gtest/gtest.h"
#include <iomanip>
#include <memory>
#include <random>
#include <sstream>

using namespace dd::literals;

TEST(DDPackageTest, RequestInvalidPackageSize) {
    EXPECT_THROW(auto dd = std::make_unique<dd::Package>(std::numeric_limits<dd::Qubit>::max() + 2), std::invalid_argument);
}

TEST(DDPackageTest, OperationLookupTest) {
    auto dd = std::make_unique<dd::Package>(1);

    // ATrue is not the operation that is being stored, but for the test it doesn't matter
    auto tmpOp = dd->noiseOperationTable.lookup(1, dd::NoiseOperationKind::ATrue, 0);
    EXPECT_TRUE(tmpOp.p == nullptr);

    auto xGate = dd->makeGateDD(dd::Xmat, 1, 0);
    dd->noiseOperationTable.insert(dd::NoiseOperationKind::ATrue, 0, xGate);
    tmpOp = dd->noiseOperationTable.lookup(1, dd::NoiseOperationKind::ATrue, 0);
    EXPECT_TRUE(tmpOp.p == xGate.p);

    tmpOp = dd->multiply(tmpOp, xGate);

    // I only check this, so that the above test is evaluated when compiled using release mode
    EXPECT_TRUE(tmpOp.p != nullptr);

    dd->garbageCollect(true);
    tmpOp = dd->noiseOperationTable.lookup(1, dd::NoiseOperationKind::ATrue, 0);
    EXPECT_TRUE(tmpOp.p == nullptr);
}

TEST(DDPackageTest, TrivialTest) {
    auto dd = std::make_unique<dd::Package>(2);
    EXPECT_EQ(dd->qubits(), 2);

    auto xGate = dd->makeGateDD(dd::Xmat, 1, 0);
    auto hGate = dd->makeGateDD(dd::Hmat, 1, 0);

    ASSERT_EQ(dd->getValueByPath(hGate, "0"), (dd::ComplexValue{dd::SQRT2_2, 0}));

    auto zeroState = dd->makeZeroState(1);
    auto hState    = dd->multiply(hGate, zeroState);
    auto oneState  = dd->multiply(xGate, zeroState);

    ASSERT_EQ(dd->fidelity(zeroState, oneState), 0.0);
    // repeat the same calculation - triggering compute table hit
    ASSERT_EQ(dd->fidelity(zeroState, oneState), 0.0);
    ASSERT_NEAR(dd->fidelity(zeroState, hState), 0.5, dd::ComplexTable<>::tolerance());
    ASSERT_NEAR(dd->fidelity(oneState, hState), 0.5, dd::ComplexTable<>::tolerance());
}

TEST(DDPackageTest, BellState) {
    auto dd = std::make_unique<dd::Package>(2);

    auto hGate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cxGate    = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);
    auto zeroState = dd->makeZeroState(2);

    auto bellState = dd->multiply(dd->multiply(cxGate, hGate), zeroState);
    dd->printVector(bellState);

    // repeated calculation is practically for free
    auto bellState2 = dd->multiply(dd->multiply(cxGate, hGate), zeroState);
    EXPECT_EQ(bellState, bellState2);

    ASSERT_EQ(dd->getValueByPath(bellState, "00"), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellState, "01"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellState, "10"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellState, "11"), (dd::ComplexValue{dd::SQRT2_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bellState, 0), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellState, 1), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellState, 2), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellState, 3), (dd::ComplexValue{dd::SQRT2_2, 0}));

    auto goalState = dd::CVec{{dd::SQRT2_2, 0.}, {0., 0.}, {0., 0.}, {dd::SQRT2_2, 0.}};
    ASSERT_EQ(dd->getVector(bellState), goalState);

    ASSERT_DOUBLE_EQ(dd->fidelity(zeroState, bellState), 0.5);

    export2Dot(bellState, "bell_state_colored_labels.dot", true, true, false, false, false);
    export2Dot(bellState, "bell_state_colored_labels_classic.dot", true, true, true, false, false);
    export2Dot(bellState, "bell_state_mono_labels.dot", false, true, false, false, false);
    export2Dot(bellState, "bell_state_mono_labels_classic.dot", false, true, true, false, false);
    export2Dot(bellState, "bell_state_colored.dot", true, false, false, false, false);
    export2Dot(bellState, "bell_state_colored_classic.dot", true, false, true, false, false);
    export2Dot(bellState, "bell_state_mono.dot", false, false, false, false, false);
    export2Dot(bellState, "bell_state_mono_classic.dot", false, false, true, false, false);
    export2Dot(bellState, "bell_state_memory.dot", false, true, true, true, false);
    dd::exportEdgeWeights(bellState, std::cout);

    dd->statistics();
}

TEST(DDPackageTest, QFTState) {
    auto dd = std::make_unique<dd::Package>(3);

    auto h0Gate    = dd->makeGateDD(dd::Hmat, 3, 0);
    auto s0Gate    = dd->makeGateDD(dd::Smat, 3, 1_pc, 0);
    auto t0Gate    = dd->makeGateDD(dd::Tmat, 3, 2_pc, 0);
    auto h1Gate    = dd->makeGateDD(dd::Hmat, 3, 1);
    auto s1Gate    = dd->makeGateDD(dd::Smat, 3, 2_pc, 1);
    auto h2Gate   = dd->makeGateDD(dd::Hmat, 3, 2);
    auto swapGate = dd->makeSWAPDD(3, {}, 0, 2);

    auto qftOp = dd->multiply(s0Gate, h0Gate);
    qftOp      = dd->multiply(t0Gate, qftOp);
    qftOp      = dd->multiply(h1Gate, qftOp);
    qftOp      = dd->multiply(s1Gate, qftOp);
    qftOp      = dd->multiply(h2Gate, qftOp);

    qftOp         = dd->multiply(swapGate, qftOp);
    auto qftState = dd->multiply(qftOp, dd->makeZeroState(3));

    dd->printVector(qftState);

    for (dd::Qubit qubit = 0; qubit < 7; ++qubit) {
        ASSERT_NEAR(dd->getValueByPath(qftState, qubit).r, static_cast<dd::fp>(0.5) * dd::SQRT2_2, dd->cn.complexTable.tolerance());
        ASSERT_EQ(dd->getValueByPath(qftState, qubit).i, 0);
    }

    export2Dot(qftState, "qft_state_colored_labels.dot", true, true, false, false, false);
    export2Dot(qftState, "qft_state_colored_labels_classic.dot", true, true, true, false, false);
    export2Dot(qftState, "qft_state_mono_labels.dot", false, true, false, false, false);
    export2Dot(qftState, "qft_state_mono_labels_classic.dot", false, true, true, false, false);
    export2Dot(qftState, "qft_state_colored.dot", true, false, false, false, false);
    export2Dot(qftState, "qft_state_colored_classic.dot", true, false, true, false, false);
    export2Dot(qftState, "qft_state_mono.dot", false, false, false, false, false);
    export2Dot(qftState, "qft_state_mono_classic.dot", false, false, true, false, false);
    export2Dot(qftState, "qft_state_memory.dot", false, true, true, true, false);
    dd::exportEdgeWeights(qftState, std::cout);

    export2Dot(qftOp, "qft_op_polar_colored_labels.dot", true, true, false, false, false, true);
    export2Dot(qftOp, "qft_op_polar_colored_labels_classic.dot", true, true, true, false, false, true);
    export2Dot(qftOp, "qft_op_polar_mono_labels.dot", false, true, false, false, false, true);
    export2Dot(qftOp, "qft_op_polar_mono_labels_classic.dot", false, true, true, false, false, true);
    export2Dot(qftOp, "qft_op_polar_colored.dot", true, false, false, false, false, true);
    export2Dot(qftOp, "qft_op_polar_colored_classic.dot", true, false, true, false, false, true);
    export2Dot(qftOp, "qft_op_polar_mono.dot", false, false, false, false, false, true);
    export2Dot(qftOp, "qft_op_polar_mono_classic.dot", false, false, true, false, false, true);
    export2Dot(qftOp, "qft_op_polar_memory.dot", false, true, true, true, false, true);

    export2Dot(qftOp, "qft_op_rectangular_colored_labels.dot", true, true, false, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_colored_labels_classic.dot", true, true, true, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_mono_labels.dot", false, true, false, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_mono_labels_classic.dot", false, true, true, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_colored.dot", true, false, false, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_colored_classic.dot", true, false, true, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_mono.dot", false, false, false, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_mono_classic.dot", false, false, true, false, false, false);
    export2Dot(qftOp, "qft_op_rectangular_memory.dot", false, true, true, true, false, false);

    dd->statistics();
}

TEST(DDPackageTest, CorruptedBellState) {
    auto dd = std::make_unique<dd::Package>(2);

    auto hGate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cxGate    = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);
    auto zeroState = dd->makeZeroState(2);

    auto bellState = dd->multiply(dd->multiply(cxGate, hGate), zeroState);

    bellState.w = dd->cn.getTemporary(0.5, 0);
    // prints a warning
    std::mt19937_64 mt; // NOLINT
    std::cout << dd->measureAll(bellState, false, mt) << "\n";

    bellState.w = dd::Complex::zero;

    ASSERT_THROW(dd->measureAll(bellState, false, mt), std::runtime_error);

    ASSERT_THROW(dd->measureOneCollapsing(bellState, 0, true, mt), std::runtime_error);
}

TEST(DDPackageTest, NegativeControl) {
    auto dd = std::make_unique<dd::Package>(2);

    auto xGate     = dd->makeGateDD(dd::Xmat, 2, 1_nc, 0);
    auto zeroState = dd->makeZeroState(2);
    auto state01    = dd->multiply(xGate, zeroState);
    EXPECT_EQ(dd->getValueByPath(state01, 0b01).r, 1.);
}

TEST(DDPackageTest, IdentityTrace) {
    auto dd        = std::make_unique<dd::Package>(4);
    auto fullTrace = dd->trace(dd->makeIdent(4));

    ASSERT_EQ(fullTrace, (dd::ComplexValue{16, 0}));
}

TEST(DDPackageTest, PartialIdentityTrace) {
    auto dd  = std::make_unique<dd::Package>(2);
    auto tr  = dd->partialTrace(dd->makeIdent(2), {false, true});
    auto mul = dd->multiply(tr, tr);
    EXPECT_EQ(dd::CTEntry::val(mul.w.r), 4.0);
}

TEST(DDPackageTest, StateGenerationManipulation) {
    std::size_t nqubits = 6;
    auto           dd      = std::make_unique<dd::Package>(nqubits);
    auto           b       = std::vector<bool>(nqubits, false);
    b[0] = b[1] = true;
    auto e      = dd->makeBasisState(nqubits, b);
    auto f      = dd->makeBasisState(nqubits, {dd::BasisStates::zero,
                                               dd::BasisStates::one,
                                               dd::BasisStates::plus,
                                               dd::BasisStates::minus,
                                               dd::BasisStates::left,
                                               dd::BasisStates::right});
    dd->incRef(e);
    dd->incRef(f);
    dd->vUniqueTable.printActive();
    dd->vUniqueTable.print();
    dd->printInformation();
    dd->decRef(e);
    dd->decRef(f);
}

TEST(DDPackageTest, VectorSerializationTest) {
    auto dd = std::make_unique<dd::Package>(2);

    auto hGate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cxGate    = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);
    auto zeroState = dd->makeZeroState(2);

    auto bellState = dd->multiply(dd->multiply(cxGate, hGate), zeroState);

    serialize(bellState, "bell_state.dd", false);
    auto deserializedBellState = dd->deserialize<dd::Package::vNode>("bell_state.dd", false);
    EXPECT_EQ(bellState, deserializedBellState);

    serialize(bellState, "bell_state_binary.dd", true);
    deserializedBellState = dd->deserialize<dd::Package::vNode>("bell_state_binary.dd", true);
    EXPECT_EQ(bellState, deserializedBellState);
}

TEST(DDPackageTest, BellMatrix) {
    auto dd = std::make_unique<dd::Package>(2);

    auto hGate  = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cxGate = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);

    auto bellMatrix = dd->multiply(cxGate, hGate);

    ASSERT_EQ(dd->getValueByPath(bellMatrix, "00"), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, "02"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, "20"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, "22"), (dd::ComplexValue{dd::SQRT2_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bellMatrix, 0, 0), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 1, 0), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 2, 0), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 3, 0), (dd::ComplexValue{dd::SQRT2_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bellMatrix, 0, 1), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 1, 1), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 2, 1), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 3, 1), (dd::ComplexValue{0, 0}));

    ASSERT_EQ(dd->getValueByPath(bellMatrix, 0, 2), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 1, 2), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 2, 2), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 3, 2), (dd::ComplexValue{-dd::SQRT2_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bellMatrix, 0, 3), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 1, 3), (dd::ComplexValue{dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 2, 3), (dd::ComplexValue{-dd::SQRT2_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bellMatrix, 3, 3), (dd::ComplexValue{0, 0}));

    auto goalRow0  = dd::CVec{{dd::SQRT2_2, 0.}, {0., 0.}, {dd::SQRT2_2, 0.}, {0., 0.}};
    auto goalRow1  = dd::CVec{{0., 0.}, {dd::SQRT2_2, 0.}, {0., 0.}, {dd::SQRT2_2, 0.}};
    auto goalRow2  = dd::CVec{{0., 0.}, {dd::SQRT2_2, 0.}, {0., 0.}, {-dd::SQRT2_2, 0.}};
    auto goalRow3  = dd::CVec{{dd::SQRT2_2, 0.}, {0., 0.}, {-dd::SQRT2_2, 0.}, {0., 0.}};
    auto goalMatrix = dd::CMat{goalRow0, goalRow1, goalRow2, goalRow3};
    ASSERT_EQ(dd->getMatrix(bellMatrix), goalMatrix);

    export2Dot(bellMatrix, "bell_matrix_colored_labels.dot", true, true, false, false, false);
    export2Dot(bellMatrix, "bell_matrix_colored_labels_classic.dot", true, true, true, false, false);
    export2Dot(bellMatrix, "bell_matrix_mono_labels.dot", false, true, false, false, false);
    export2Dot(bellMatrix, "bell_matrix_mono_labels_classic.dot", false, true, true, false, false);
    export2Dot(bellMatrix, "bell_matrix_colored.dot", true, false, false, false, false);
    export2Dot(bellMatrix, "bell_matrix_colored_classic.dot", true, false, true, false, false);
    export2Dot(bellMatrix, "bell_matrix_mono.dot", false, false, false, false, false);
    export2Dot(bellMatrix, "bell_matrix_mono_classic.dot", false, false, true, false, false);
    export2Dot(bellMatrix, "bell_matrix_memory.dot", false, true, true, true, false);

    dd->statistics();
}

TEST(DDPackageTest, MatrixSerializationTest) {
    auto dd = std::make_unique<dd::Package>(2);

    auto hGate  = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cxGate = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);

    auto bellMatrix = dd->multiply(cxGate, hGate);

    serialize(bellMatrix, "bell_matrix.dd", false);
    auto deserializedBellMatrix = dd->deserialize<dd::Package::mNode>("bell_matrix.dd", false);
    EXPECT_EQ(bellMatrix, deserializedBellMatrix);

    serialize(bellMatrix, "bell_matrix_binary.dd", true);
    deserializedBellMatrix = dd->deserialize<dd::Package::mNode>("bell_matrix_binary.dd", true);
    EXPECT_EQ(bellMatrix, deserializedBellMatrix);
}

TEST(DDPackageTest, SerializationErrors) {
    auto dd = std::make_unique<dd::Package>(2);

    auto hGate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cxGate    = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);
    auto zeroState = dd->makeZeroState(2);
    auto bellState = dd->multiply(dd->multiply(cxGate, hGate), zeroState);

    // test non-existing file
    EXPECT_THROW(serialize(bellState, "./path/that/does/not/exist/filename.dd"), std::invalid_argument);
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>("./path/that/does/not/exist/filename.dd", true), std::invalid_argument);

    // test wrong version number
    std::stringstream ss{};
    ss << 2 << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss, false), std::runtime_error);
    ss << 2 << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss, false), std::runtime_error);

    ss.str("");
    std::remove_const_t<decltype(dd::SERIALIZATION_VERSION)> version = 2;
    ss.write(reinterpret_cast<const char*>(&version), sizeof(decltype(dd::SERIALIZATION_VERSION))); // NOLINT
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss, true), std::runtime_error);
    ss.write(reinterpret_cast<const char*>(&version), sizeof(decltype(dd::SERIALIZATION_VERSION))); // NOLINT
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss, true), std::runtime_error);

    // test wrong format
    ss.str("");
    ss << "1" << std::endl;
    ss << "not_complex" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss), std::runtime_error);
    ss << "1" << std::endl;
    ss << "not_complex" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss), std::runtime_error);

    ss.str("");
    ss << "1" << std::endl;
    ss << "1.0" << std::endl;
    ss << "no_node_here" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss), std::runtime_error);
    ss << "1" << std::endl;
    ss << "1.0" << std::endl;
    ss << "no_node_here" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss), std::runtime_error);
}

TEST(DDPackageTest, TestConsistency) {
    auto dd = std::make_unique<dd::Package>(2);

    auto hGate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cxGate    = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);
    auto zeroState = dd->makeZeroState(2);

    auto bellMatrix = dd->multiply(cxGate, hGate);
    dd->incRef(bellMatrix);
    auto local = dd->isLocallyConsistent(bellMatrix);
    EXPECT_TRUE(local);
    auto global = dd->isGloballyConsistent(bellMatrix);
    EXPECT_TRUE(global);
    dd->debugnode(bellMatrix.p);

    auto bellState = dd->multiply(bellMatrix, zeroState);
    dd->incRef(bellState);
    local = dd->isLocallyConsistent(bellState);
    EXPECT_TRUE(local);
    global = dd->isGloballyConsistent(bellState);
    EXPECT_TRUE(global);
    dd->debugnode(bellState.p);
}

TEST(DDPackageTest, ToffoliTable) {
    auto dd = std::make_unique<dd::Package>(4);

    // try to search for a toffoli in an empty table
    auto toffoli = dd->toffoliTable.lookup(3, {0_nc, 1_pc}, 2);
    EXPECT_EQ(toffoli.p, nullptr);
    if (toffoli.p == nullptr) {
        toffoli = dd->makeGateDD(dd::Xmat, 3, {0_nc, 1_pc}, 2);
        dd->toffoliTable.insert(3, {0_nc, 1_pc}, 2, toffoli);
    }

    // try again with same toffoli
    auto toffoliTableEntry = dd->toffoliTable.lookup(3, {0_nc, 1_pc}, 2);
    EXPECT_NE(toffoliTableEntry.p, nullptr);
    EXPECT_EQ(toffoli, toffoliTableEntry);

    // try again with different controlled toffoli
    toffoliTableEntry = dd->toffoliTable.lookup(3, {0_pc, 1_pc}, 2);
    EXPECT_EQ(toffoliTableEntry.p, nullptr);

    // try again with different qubit toffoli
    toffoliTableEntry = dd->toffoliTable.lookup(4, {0_pc, 1_pc, 2_pc}, 3);
    EXPECT_EQ(toffoliTableEntry.p, nullptr);

    // clear the table
    dd->toffoliTable.clear();
    toffoliTableEntry = dd->toffoliTable.lookup(3, {0_nc, 1_pc}, 2);
    EXPECT_EQ(toffoliTableEntry.p, nullptr);
}

TEST(DDPackageTest, Extend) {
    auto dd = std::make_unique<dd::Package>(4);

    auto id = dd->makeIdent(3);
    EXPECT_EQ(id.p->v, 2);
    EXPECT_EQ(id.p->e[0], id.p->e[3]);
    EXPECT_EQ(id.p->e[1], id.p->e[2]);
    EXPECT_TRUE(id.p->ident);

    auto ext = dd->extend(id, 0, 1);
    EXPECT_EQ(ext.p->v, 3);
    EXPECT_EQ(ext.p->e[0], ext.p->e[3]);
    EXPECT_EQ(ext.p->e[1], ext.p->e[2]);
    EXPECT_TRUE(ext.p->ident);
}

TEST(DDPackageTest, Identity) {
    auto dd = std::make_unique<dd::Package>(4);

    EXPECT_TRUE(dd->makeIdent(0).isOneTerminal());
    EXPECT_TRUE(dd->makeIdent(0, -1).isOneTerminal());

    auto id3 = dd->makeIdent(3);
    EXPECT_EQ(dd->makeIdent(0, 2), id3);
    const auto& table = dd->getIdentityTable();
    EXPECT_NE(table[2].p, nullptr);

    auto id2 = dd->makeIdent(0, 1); // should be found in IdTable
    EXPECT_EQ(dd->makeIdent(2), id2);

    auto id4 = dd->makeIdent(0, 3); // should use id3 and extend it
    EXPECT_EQ(dd->makeIdent(0, 3), id4);
    EXPECT_NE(table[3].p, nullptr);

    auto idCached = dd->makeIdent(4);
    EXPECT_EQ(id4, idCached);
}

TEST(DDPackageTest, TestLocalInconsistency) {
    auto dd = std::make_unique<dd::Package>(3);

    auto hGate     = dd->makeGateDD(dd::Hmat, 2, 0);
    auto cxGate    = dd->makeGateDD(dd::Xmat, 2, 0_pc, 1);
    auto zeroState = dd->makeZeroState(2);

    auto bellState = dd->multiply(dd->multiply(cxGate, hGate), zeroState);
    auto local      = dd->isLocallyConsistent(bellState);
    EXPECT_FALSE(local);
    bellState.p->ref = 1;
    local             = dd->isLocallyConsistent(bellState);
    EXPECT_FALSE(local);
    bellState.p->ref = 0;
    dd->incRef(bellState);

    bellState.p->v = 2;
    local           = dd->isLocallyConsistent(bellState);
    EXPECT_FALSE(local);
    bellState.p->v = 1;

    bellState.p->e[0].w.r->refCount = 0;
    local                            = dd->isLocallyConsistent(bellState);
    EXPECT_FALSE(local);
    bellState.p->e[0].w.r->refCount = 1;
}

TEST(DDPackageTest, Ancillaries) {
    auto dd          = std::make_unique<dd::Package>(4);
    auto hGate      = dd->makeGateDD(dd::Hmat, 2, 0);
    auto cxGate     = dd->makeGateDD(dd::Xmat, 2, 0_pc, 1);
    auto bellMatrix = dd->multiply(cxGate, hGate);

    dd->incRef(bellMatrix);
    auto reducedBellMatrix = dd->reduceAncillae(bellMatrix, {false, false, false, false});
    EXPECT_EQ(bellMatrix, reducedBellMatrix);
    dd->incRef(bellMatrix);
    reducedBellMatrix = dd->reduceAncillae(bellMatrix, {false, false, true, true});
    EXPECT_EQ(bellMatrix, reducedBellMatrix);

    auto extendedBellMatrix = dd->extend(bellMatrix, 2);
    dd->incRef(extendedBellMatrix);
    reducedBellMatrix = dd->reduceAncillae(extendedBellMatrix, {false, false, true, true});
    EXPECT_TRUE(reducedBellMatrix.p->e[1].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[2].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[3].isZeroTerminal());

    EXPECT_EQ(reducedBellMatrix.p->e[0].p->e[0].p, bellMatrix.p);
    EXPECT_TRUE(reducedBellMatrix.p->e[0].p->e[1].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[0].p->e[2].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[0].p->e[3].isZeroTerminal());

    dd->incRef(extendedBellMatrix);
    reducedBellMatrix = dd->reduceAncillae(extendedBellMatrix, {false, false, true, true}, false);
    EXPECT_TRUE(reducedBellMatrix.p->e[1].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[2].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[3].isZeroTerminal());

    EXPECT_EQ(reducedBellMatrix.p->e[0].p->e[0].p, bellMatrix.p);
    EXPECT_TRUE(reducedBellMatrix.p->e[0].p->e[1].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[0].p->e[2].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[0].p->e[3].isZeroTerminal());
}

TEST(DDPackageTest, GarbageVector) {
    auto dd         = std::make_unique<dd::Package>(4);
    auto hGate     = dd->makeGateDD(dd::Hmat, 2, 0);
    auto cxGate    = dd->makeGateDD(dd::Xmat, 2, 0_pc, 1);
    auto zeroState = dd->makeZeroState(2);
    auto bellState = dd->multiply(dd->multiply(cxGate, hGate), zeroState);
    dd->printVector(bellState);

    dd->incRef(bellState);
    auto reducedBellState = dd->reduceGarbage(bellState, {false, false, false, false});
    EXPECT_EQ(bellState, reducedBellState);
    dd->incRef(bellState);
    reducedBellState = dd->reduceGarbage(bellState, {false, false, true, false});
    EXPECT_EQ(bellState, reducedBellState);

    dd->incRef(bellState);
    reducedBellState = dd->reduceGarbage(bellState, {false, true, false, false});
    auto vec           = dd->getVector(reducedBellState);
    dd->printVector(reducedBellState);
    EXPECT_EQ(vec[2], static_cast<std::complex<dd::fp>>(dd::complex_zero));
    EXPECT_EQ(vec[3], static_cast<std::complex<dd::fp>>(dd::complex_zero));

    dd->incRef(bellState);
    reducedBellState = dd->reduceGarbage(bellState, {true, false, false, false});
    dd->printVector(reducedBellState);
    vec = dd->getVector(reducedBellState);
    EXPECT_EQ(vec[1], static_cast<std::complex<dd::fp>>(dd::complex_zero));
    EXPECT_EQ(vec[3], static_cast<std::complex<dd::fp>>(dd::complex_zero));
}

TEST(DDPackageTest, GarbageMatrix) {
    auto dd          = std::make_unique<dd::Package>(4);
    auto hGate      = dd->makeGateDD(dd::Hmat, 2, 0);
    auto cxGate     = dd->makeGateDD(dd::Xmat, 2, 0_pc, 1);
    auto bellMatrix = dd->multiply(cxGate, hGate);

    dd->incRef(bellMatrix);
    auto reducedBellMatrix = dd->reduceGarbage(bellMatrix, {false, false, false, false});
    EXPECT_EQ(bellMatrix, reducedBellMatrix);
    dd->incRef(bellMatrix);
    reducedBellMatrix = dd->reduceGarbage(bellMatrix, {false, false, true, false});
    EXPECT_EQ(bellMatrix, reducedBellMatrix);

    dd->incRef(bellMatrix);
    reducedBellMatrix = dd->reduceGarbage(bellMatrix, {false, true, false, false});
    auto mat            = dd->getMatrix(reducedBellMatrix);
    auto zero           = dd::CVec{{0., 0.}, {0., 0.}, {0., 0.}, {0., 0.}};
    EXPECT_EQ(mat[2], zero);
    EXPECT_EQ(mat[3], zero);

    dd->incRef(bellMatrix);
    reducedBellMatrix = dd->reduceGarbage(bellMatrix, {true, false, false, false});
    mat                 = dd->getMatrix(reducedBellMatrix);
    EXPECT_EQ(mat[1], zero);
    EXPECT_EQ(mat[3], zero);

    dd->incRef(bellMatrix);
    reducedBellMatrix = dd->reduceGarbage(bellMatrix, {false, true, false, false}, false);
    EXPECT_TRUE(reducedBellMatrix.p->e[1].isZeroTerminal());
    EXPECT_TRUE(reducedBellMatrix.p->e[3].isZeroTerminal());
}

TEST(DDPackageTest, InvalidMakeBasisStateAndGate) {
    auto nqubits    = 2;
    auto dd         = std::make_unique<dd::Package>(nqubits);
    auto basisState = std::vector<dd::BasisStates>{dd::BasisStates::zero};
    EXPECT_THROW(dd->makeBasisState(nqubits, basisState), std::runtime_error);
    EXPECT_THROW(dd->makeZeroState(3), std::runtime_error);
    EXPECT_THROW(dd->makeBasisState(3, {true, true, true}), std::runtime_error);
    EXPECT_THROW(dd->makeBasisState(3, {dd::BasisStates::one, dd::BasisStates::one, dd::BasisStates::one}), std::runtime_error);
    EXPECT_THROW(dd->makeGateDD(dd::Xmat, 3, 0), std::runtime_error);
}

TEST(DDPackageTest, InvalidDecRef) {
    auto dd = std::make_unique<dd::Package>(2);
    auto e  = dd->makeIdent(2);
    EXPECT_THROW(dd->decRef(e), std::runtime_error);
}

TEST(DDPackageTest, PackageReset) {
    auto dd = std::make_unique<dd::Package>(1);

    // one node in unique table of variable 0
    auto        iGate = dd->makeIdent(1);
    const auto& unique = dd->mUniqueTable.getTables();
    const auto& table  = unique[0];
    auto        ihash  = dd->mUniqueTable.hash(iGate.p); // NOLINT
    const auto* node   = table[ihash];
    std::cout << ihash << ": " << reinterpret_cast<std::uintptr_t>(iGate.p) << std::endl; // NOLINT
    // node should be the first in this unique table bucket
    EXPECT_EQ(node, iGate.p);
    dd->reset();
    // after clearing the tables, they should be empty
    EXPECT_EQ(table[ihash], nullptr);
    iGate            = dd->makeIdent(1);
    const auto* node2 = table[ihash];
    // after recreating the DD, it should receive the same node
    EXPECT_EQ(node2, node);
}

TEST(DDPackageTest, MaxRefCount) {
    auto dd = std::make_unique<dd::Package>(1);
    auto e  = dd->makeIdent(1);
    // ref count saturates at this value
    e.p->ref = std::numeric_limits<decltype(e.p->ref)>::max();
    dd->incRef(e);
    EXPECT_EQ(e.p->ref, std::numeric_limits<decltype(e.p->ref)>::max());
}

TEST(DDPackageTest, Inverse) {
    auto dd   = std::make_unique<dd::Package>(1);
    auto x    = dd->makeGateDD(dd::Xmat, 1, 0);
    auto xdag = dd->conjugateTranspose(x);
    EXPECT_EQ(x, xdag);
    dd->garbageCollect();
    // nothing should have been collected since the threshold is not reached
    EXPECT_EQ(dd->mUniqueTable.getNodeCount(), 1);
    dd->incRef(x);
    dd->garbageCollect(true);
    // nothing should have been collected since the lone node has a non-zero ref count
    EXPECT_EQ(dd->mUniqueTable.getNodeCount(), 1);
    dd->decRef(x);
    dd->garbageCollect(true);
    // now the node should have been collected
    EXPECT_EQ(dd->mUniqueTable.getNodeCount(), 0);
}

TEST(DDPackageTest, UniqueTableAllocation) {
    auto dd = std::make_unique<dd::Package>(1);

    auto allocs = dd->vUniqueTable.getAllocations();
    std::cout << allocs << std::endl;
    std::vector<dd::Package::vNode*> nodes{allocs};
    // get all the nodes that are pre-allocated
    for (auto i = 0U; i < allocs; ++i) {
        nodes[i] = dd->vUniqueTable.getNode();
    }

    // trigger new allocation
    [[maybe_unused]] auto *node = dd->vUniqueTable.getNode();
    EXPECT_EQ(dd->vUniqueTable.getAllocations(), (1. + dd->vUniqueTable.getGrowthFactor()) * allocs);

    // clearing the unique table should reduce the allocated size to the original size
    dd->vUniqueTable.clear();
    EXPECT_EQ(dd->vUniqueTable.getAllocations(), allocs);
}

TEST(DDPackageTest, MatrixTranspose) {
    auto dd = std::make_unique<dd::Package>(2);
    auto cx = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);

    // transposing a symmetric matrix shall yield a symmetric matrix
    auto cxTransposed = dd->transpose(cx);
    EXPECT_EQ(cxTransposed, cx);

    // the Y gate is not symmetric
    auto y           = dd->makeGateDD(dd::Ymat, 2, 0);
    auto yTransposed = dd->transpose(y);
    EXPECT_NE(yTransposed, y);

    // transposing twice should yield the original matrix
    auto yTT = dd->transpose(yTransposed);
    EXPECT_EQ(yTT, y);

    // perform the same computation again -> trigger a compute table hit
    auto yAgain = dd->transpose(yTransposed);
    EXPECT_EQ(yAgain, y);
}

TEST(DDPackageTest, SpecialCaseTerminal) {
    auto dd  = std::make_unique<dd::Package>(2);
    auto one = dd::Package::vEdge::one;
    dd::export2Dot(one, "oneColored.dot", true);
    dd::export2Dot(one, "oneClassic.dot", false);
    dd::export2Dot(one, "oneMemory.dot", true, true, false, true);

    EXPECT_EQ(dd->vUniqueTable.lookup(one), one);

    auto zero = dd::Package::vEdge::zero;
    EXPECT_EQ(dd->kronecker(zero, one), zero);
    EXPECT_EQ(dd->kronecker(one, one), one);

    dd->debugnode(one.p);
    dd::ComplexValue cOne{1.0, 0.0};
    EXPECT_EQ(dd->getValueByPath(one, ""), cOne);
    EXPECT_EQ(dd->getValueByPath(one, 0), cOne);
    EXPECT_EQ(dd->getValueByPath(dd::Package::mEdge::one, 0, 0), cOne);

    dd::ComplexValue cZero{0.0, 0.0};
    EXPECT_EQ(dd->innerProduct(zero, zero), cZero);
}

//TEST(DDPackageTest, GarbageCollectSomeButNotAll) {
//    auto dd = std::make_unique<dd::Package>(1);
//
//    // one node in unique table of variable 0
//    const auto& unique = dd->mUniqueTable.getTables();
//    const auto& table  = unique[0];
//
//    auto I     = dd->makeIdent(1);
//    auto Ihash = dd->mUniqueTable.hash(I.p);
//
//    // two nodes in same unique table bucket of variable 0
//    auto Z     = dd->makeGateDD(dd::Zmat, 1, 0);
//    auto Zhash = dd->mUniqueTable.hash(Z.p);
//
//    // I and Z should be placed in the same bucket
//    EXPECT_EQ(Ihash, Zhash);
//
//    // increase the reference count of the Z gate, but not the I gate
//    dd->incRef(Z);
//
//    // garbage collection should only collect the I gate and leave the Z gate at the front of the bucket
//    dd->garbageCollect(true);
//
//    EXPECT_EQ(table[Zhash], Z.p);
//    EXPECT_EQ(table[Zhash]->next, nullptr);
//}

TEST(DDPackageTest, KroneckerProduct) {
    auto dd        = std::make_unique<dd::Package>(2);
    auto x         = dd->makeGateDD(dd::Xmat, 1, 0);
    auto kronecker = dd->kronecker(x, x);
    EXPECT_EQ(kronecker.p->v, 1);
    EXPECT_EQ(kronecker.p->e[0], dd::Package::mEdge::zero);
    EXPECT_EQ(kronecker.p->e[0], kronecker.p->e[3]);
    EXPECT_EQ(kronecker.p->e[1], kronecker.p->e[2]);
    EXPECT_EQ(kronecker.p->e[1].p->v, 0);
    EXPECT_EQ(kronecker.p->e[1].p->e[0], dd::Package::mEdge::zero);
    EXPECT_EQ(kronecker.p->e[1].p->e[0], kronecker.p->e[1].p->e[3]);
    EXPECT_EQ(kronecker.p->e[1].p->e[1], dd::Package::mEdge::one);
    EXPECT_EQ(kronecker.p->e[1].p->e[1], kronecker.p->e[1].p->e[2]);

    auto kronecker2 = dd->kronecker(x, x);
    EXPECT_EQ(kronecker, kronecker2);
}

TEST(DDPackageTest, NearZeroNormalize) {
    auto               dd       = std::make_unique<dd::Package>(2);
    dd::fp             nearZero = dd::ComplexTable<>::tolerance() / 10;
    dd::Package::vEdge ve{};
    ve.p    = dd->vUniqueTable.getNode();
    ve.p->v = 1;
    ve.w    = dd::Complex::one;
    for (auto& edge: ve.p->e) {
        edge.p    = dd->vUniqueTable.getNode();
        edge.p->v = 0;
        edge.w    = dd->cn.getCached(nearZero, 0.);
        edge.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    }
    auto veNormalizedCached = dd->normalize(ve, true);
    EXPECT_EQ(veNormalizedCached, dd::Package::vEdge::zero);

    for (auto& edge: ve.p->e) {
        edge.p    = dd->vUniqueTable.getNode();
        edge.p->v = 0;
        edge.w    = dd->cn.lookup(nearZero, 0.);
        edge.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    }
    auto veNormalized = dd->normalize(ve, false);
    EXPECT_EQ(veNormalized, dd::Package::vEdge::zero);

    dd::Package::mEdge me{};
    me.p    = dd->mUniqueTable.getNode();
    me.p->v = 1;
    me.w    = dd::Complex::one;
    for (auto& edge: me.p->e) {
        edge.p    = dd->mUniqueTable.getNode();
        edge.p->v = 0;
        edge.w    = dd->cn.getCached(nearZero, 0.);
        edge.p->e = {dd::Package::mEdge::one, dd::Package::mEdge::one, dd::Package::mEdge::one, dd::Package::mEdge::one};
    }
    auto meNormalizedCached = dd->normalize(me, true);
    EXPECT_EQ(meNormalizedCached, dd::Package::mEdge::zero);

    for (auto& edge: me.p->e) {
        edge.p    = dd->mUniqueTable.getNode();
        edge.p->v = 0;
        edge.w    = dd->cn.lookup(nearZero, 0.);
        edge.p->e = {dd::Package::mEdge::one, dd::Package::mEdge::one, dd::Package::mEdge::one, dd::Package::mEdge::one};
    }
    auto meNormalized = dd->normalize(me, false);
    EXPECT_EQ(meNormalized, dd::Package::mEdge::zero);
}

TEST(DDPackageTest, Controls) {
    dd::Control cpos{0};
    dd::Control cneg{0, dd::Control::Type::neg};

    EXPECT_NE(cpos, cneg);

    dd::Controls controls{};
    controls.insert(cpos);
    controls.insert(cneg);
    EXPECT_EQ(controls.begin()->type, dd::Control::Type::neg);
    EXPECT_EQ(controls.count(0), 2);
}

TEST(DDPackageTest, DestructiveMeasurementAll) {
    auto dd         = std::make_unique<dd::Package>(4);
    auto hGate0     = dd->makeGateDD(dd::Hmat, 2, 0);
    auto hGate1     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto plusMatrix = dd->multiply(hGate0, hGate1);
    auto zeroState  = dd->makeZeroState(2);
    auto plusState  = dd->multiply(plusMatrix, zeroState);
    dd->incRef(plusState);

    std::mt19937_64 mt{0}; // NOLINT

    const dd::CVec vBefore = dd->getVector(plusState);

    ASSERT_EQ(vBefore[0], vBefore[1]);
    ASSERT_EQ(vBefore[0], vBefore[2]);
    ASSERT_EQ(vBefore[0], vBefore[3]);

    const std::string m = dd->measureAll(plusState, true, mt);

    const dd::CVec vAfter = dd->getVector(plusState);
    const int      i      = std::stoi(m, nullptr, 2);

    ASSERT_EQ(vAfter[i], static_cast<std::complex<dd::fp>>(dd::complex_one));
}

TEST(DDPackageTest, DestructiveMeasurementOne) {
    auto dd         = std::make_unique<dd::Package>(4);
    auto hGate0     = dd->makeGateDD(dd::Hmat, 2, 0);
    auto hGate1     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto plusMatrix = dd->multiply(hGate0, hGate1);
    auto zeroState  = dd->makeZeroState(2);
    auto plusState  = dd->multiply(plusMatrix, zeroState);
    dd->incRef(plusState);

    std::mt19937_64 mt{0}; // NOLINT

    const char     m      = dd->measureOneCollapsing(plusState, 0, true, mt);
    const dd::CVec vAfter = dd->getVector(plusState);

    ASSERT_EQ(m, '0');
    ASSERT_EQ(vAfter[0], static_cast<std::complex<dd::fp>>(dd::complex_SQRT2_2));
    ASSERT_EQ(vAfter[2], static_cast<std::complex<dd::fp>>(dd::complex_SQRT2_2));
    ASSERT_EQ(vAfter[1], static_cast<std::complex<dd::fp>>(dd::complex_zero));
    ASSERT_EQ(vAfter[3], static_cast<std::complex<dd::fp>>(dd::complex_zero));
}

TEST(DDPackageTest, DestructiveMeasurementOneArbitraryNormalization) {
    auto dd         = std::make_unique<dd::Package>(4);
    auto hGate0     = dd->makeGateDD(dd::Hmat, 2, 0);
    auto hGate1     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto plusMatrix = dd->multiply(hGate0, hGate1);
    auto zeroState  = dd->makeZeroState(2);
    auto plusState  = dd->multiply(plusMatrix, zeroState);
    dd->incRef(plusState);

    std::mt19937_64 mt{0}; // NOLINT

    const char     m      = dd->measureOneCollapsing(plusState, 0, false, mt);
    const dd::CVec vAfter = dd->getVector(plusState);

    ASSERT_EQ(m, '0');
    ASSERT_EQ(vAfter[0], static_cast<std::complex<dd::fp>>(dd::complex_SQRT2_2));
    ASSERT_EQ(vAfter[2], static_cast<std::complex<dd::fp>>(dd::complex_SQRT2_2));
    ASSERT_EQ(vAfter[1], static_cast<std::complex<dd::fp>>(dd::complex_zero));
    ASSERT_EQ(vAfter[3], static_cast<std::complex<dd::fp>>(dd::complex_zero));
}

TEST(DDPackageTest, ExportPolarPhaseFormatted) {
    std::ostringstream phaseString;

    // zero case
    dd::printPhaseFormatted(phaseString, 0);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ 0)");
    phaseString.str("");

    // one cases
    dd::printPhaseFormatted(phaseString, 0.5 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ/2)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, -0.5 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(-iπ/2)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, -dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(-iπ)");
    phaseString.str("");

    // 1/sqrt(2) cases
    dd::printPhaseFormatted(phaseString, dd::SQRT2_2 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ/√2)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, 2 * dd::SQRT2_2 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ 2/√2)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, 0.5 * dd::SQRT2_2 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ/(2√2))");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, 0.75 * dd::SQRT2_2 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ 3/(4√2))");
    phaseString.str("");

    // pi cases mhhh pie
    dd::printPhaseFormatted(phaseString, dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, 2 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ 2)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, 0.5 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ/2)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, 0.75 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ 3/4)");
    phaseString.str("");

    dd::printPhaseFormatted(phaseString, 0.25 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ/4)");
    phaseString.str("");

    // general case
    dd::printPhaseFormatted(phaseString, 0.12345 * dd::PI);
    EXPECT_STREQ(phaseString.str().c_str(), "ℯ(iπ 0.12345)");
    phaseString.str("");
}

TEST(DDPackageTest, ExportConditionalFormat) {
    auto cn = std::make_unique<dd::ComplexNumbers>();

    EXPECT_STREQ(dd::conditionalFormat(cn->getCached(1, 0)).c_str(), "1");
    EXPECT_STREQ(dd::conditionalFormat(cn->getCached(0, 1)).c_str(), "i");
    EXPECT_STREQ(dd::conditionalFormat(cn->getCached(-1, 0)).c_str(), "-1");
    EXPECT_STREQ(dd::conditionalFormat(cn->getCached(0, -1)).c_str(), "-i");

    const auto num = cn->getCached(-dd::SQRT2_2, -dd::SQRT2_2);
    EXPECT_STREQ(dd::conditionalFormat(num).c_str(), "ℯ(-iπ 3/4)");
    EXPECT_STREQ(dd::conditionalFormat(num, false).c_str(), "-1/√2(1+i)");

    EXPECT_STREQ(dd::conditionalFormat(cn->getCached(-1, -1)).c_str(), "2/√2 ℯ(-iπ 3/4)");
    EXPECT_STREQ(dd::conditionalFormat(cn->getCached(-dd::SQRT2_2, 0)).c_str(), "-1/√2");
}

TEST(DDPackageTest, BasicNumericInstabilityTest) {
    const dd::fp zero = 0.0;
    const dd::fp half = 0.5;
    const dd::fp one = 1.0;
    const dd::fp two = 2.0;

    std::cout << std::setprecision(std::numeric_limits<dd::fp>::max_digits10);

    std::cout << "The 1/sqrt(2) constant used in this package is " << dd::SQRT2_2 << ", which is the closest floating point value to the actual value of 1/sqrt(2).\n";
    std::cout << "Computing std::sqrt(0.5) actually computes this value, i.e. " << std::sqrt(half) << "\n";
    EXPECT_EQ(dd::SQRT2_2, std::sqrt(half));

    std::cout << "However, computing 1/std::sqrt(2.) leads to " << one / std::sqrt(two) << ", which differs by 1 ULP from std::sqrt(0.5)\n";
    EXPECT_EQ(one / std::sqrt(two), std::nextafter(std::sqrt(half), zero));

    std::cout << "In the same fashion, computing std::sqrt(2.) leads to " << std::sqrt(two) << ", while computing 1/std::sqrt(0.5) leads to " << one / std::sqrt(half) << ", which differ by exactly 1 ULP\n";
    EXPECT_EQ(std::sqrt(two), std::nextafter(one / std::sqrt(half), two));

    std::cout << "Another inaccuracy occurs when computing 1/sqrt(2) * 1/sqrt(2), which should equal to 0.5 but is off by 1 ULP: " << std::sqrt(half) * std::sqrt(half) << "\n";
    EXPECT_EQ(std::sqrt(half) * std::sqrt(half), std::nextafter(half, one));

    std::cout << "This inaccuracy even persists when computing std::sqrt(0.5) * std::sqrt(0.5): " << std::sqrt(half) * std::sqrt(half) << "\n";
    EXPECT_EQ(std::sqrt(half) * std::sqrt(half), std::nextafter(half, one));

    //    std::cout << "Interestingly, calculating powers of dd::SQRT2_2 can be conducted very precisely, i.e., with an error of only 1 ULP.\n";
    //    dd::fp      accumulator = dd::SQRT2_2 * dd::SQRT2_2;
    //    std::size_t nq          = 64;
    //    for (std::size_t i = 1; i < nq; i += 2) {
    //        std::size_t power  = (i + 1) / 2;
    //        std::size_t denom  = 1UL << power;
    //        dd::fp      target = 1. / static_cast<double>(denom);
    //        dd::fp      diff   = std::abs(target - accumulator);
    //        const auto  ulps   = dd::ulpDistance(accumulator, target);
    //        std::cout << accumulator << ", numerical error: " << diff << ", ulps: " << ulps << "\n"";
    //        EXPECT_EQ(ulps, 1);
    //        accumulator *= dd::SQRT2_2;
    //        accumulator *= dd::SQRT2_2;
    //    }
}

TEST(DDPackageTest, BasicNumericStabilityTest) {
    using limits = std::numeric_limits<dd::fp>;

    auto dd  = std::make_unique<dd::Package>(1);
    auto tol = dd::ComplexTable<>::tolerance();
    dd::ComplexNumbers::setTolerance(limits::epsilon());
    auto state  = dd->makeZeroState(1);
    auto h      = dd->makeGateDD(dd::Hmat, 1, 0);
    auto state1 = dd->multiply(h, state);
    auto z      = dd->makeGateDD(dd::Zmat, 1, 0);
    auto result = dd->multiply(z, state1);

    const auto topWeight   = result.w.toString(false, limits::max_digits10);
    const auto leftWeight  = result.p->e[0].w.toString(false, limits::max_digits10);
    const auto rightWeight = result.p->e[1].w.toString(false, limits::max_digits10);
    std::cout << topWeight << " | " << leftWeight << " | " << rightWeight << std::endl;
    EXPECT_EQ(topWeight, "1");
    std::ostringstream oss{};
    oss << std::setprecision(limits::max_digits10) << dd::SQRT2_2;
    EXPECT_EQ(leftWeight, oss.str());
    oss.str("");
    oss << -dd::SQRT2_2;
    EXPECT_EQ(rightWeight, oss.str());
    // restore tolerance
    dd::ComplexNumbers::setTolerance(tol);
}

TEST(DDPackageTest, NormalizationNumericStabilityTest) {
    auto dd = std::make_unique<dd::Package>(1);
    for (std::size_t x = 23; x <= 50; ++x) {
        const auto lambda = dd::PI / static_cast<dd::fp>(1ULL << x);
        std::cout << std::setprecision(17) << "x: " << x << " | lambda: " << lambda << " | cos(lambda): " << std::cos(lambda) << " | sin(lambda): " << std::sin(lambda) << std::endl;
        auto p      = dd->makeGateDD(dd::Phasemat(lambda), 1, 0);
        auto pdag   = dd->makeGateDD(dd::Phasemat(-lambda), 1, 0);
        auto result = dd->multiply(p, pdag);
        EXPECT_TRUE(result.p->ident);
        dd->cn.complexTable.clear();
    }
}

TEST(DDPackageTest, FidelityOfMeasurementOutcomes) {
    auto dd = std::make_unique<dd::Package>(3);

    auto hGate     = dd->makeGateDD(dd::Hmat, 3, 2);
    auto cxGate1   = dd->makeGateDD(dd::Xmat, 3, 2_pc, 1);
    auto cxGate2   = dd->makeGateDD(dd::Xmat, 3, 1_pc, 0);
    auto zeroState = dd->makeZeroState(3);

    auto ghzState = dd->multiply(cxGate2, dd->multiply(cxGate1, dd->multiply(hGate, zeroState)));

    dd::ProbabilityVector probs{};
    probs[0]      = 0.5;
    probs[7]      = 0.5;
    auto fidelity = dd->fidelityOfMeasurementOutcomes(ghzState, probs);
    EXPECT_NEAR(fidelity, 1.0, dd::ComplexTable<>::tolerance());
}

TEST(DDPackageTest, CloseToIdentity) {
    auto dd = std::make_unique<dd::Package>(3);
    auto id = dd->makeIdent(1);
    EXPECT_TRUE(dd->isCloseToIdentity(id));
    dd::Package::mEdge close{};
    close.p  = id.p;
    close.w  = dd->cn.lookup(1e-11, 0);
    auto id2 = dd->makeDDNode(1, std::array{id, dd::Package::mEdge::zero, dd::Package::mEdge::zero, close});
    EXPECT_TRUE(dd->isCloseToIdentity(id2));

    auto noId = dd->makeDDNode(1, std::array{dd::Package::mEdge::zero, id, dd::Package::mEdge::zero, close});
    EXPECT_FALSE(dd->isCloseToIdentity(noId));

    dd::Package::mEdge notClose{};
    notClose.p = id.p;
    notClose.w = dd->cn.lookup(1e-9, 0);
    auto noId2 = dd->makeDDNode(1, std::array{notClose, dd::Package::mEdge::zero, dd::Package::mEdge::zero, close});
    EXPECT_FALSE(dd->isCloseToIdentity(noId2));

    auto noId3 = dd->makeDDNode(1, std::array{close, dd::Package::mEdge::zero, dd::Package::mEdge::zero, notClose});
    EXPECT_FALSE(dd->isCloseToIdentity(noId3));

    auto notClose2 = dd->makeDDNode(0, std::array{dd::Package::mEdge::zero, dd::Package::mEdge::one, dd::Package::mEdge::one, dd::Package::mEdge::zero});
    auto notClose3 = dd->makeDDNode(1, std::array{notClose2, dd::Package::mEdge::zero, dd::Package::mEdge::zero, notClose2});
    EXPECT_FALSE(dd->isCloseToIdentity(notClose3));
}
