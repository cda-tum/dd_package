/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "DDexport.hpp"
#include "DDpackage.hpp"
#include "GateMatrixDefinitions.hpp"

#include "gtest/gtest.h"
#include <memory>

using namespace dd::literals;

TEST(DDPackageTest, OperationLookupTest) {
    auto dd = std::make_unique<dd::Package>(1);

    // ATrue is not the operation that is being stored, but for the test it doesn't matter
    auto tmp_op = dd->operations.lookup(1, dd::ATrue, 0);
    EXPECT_TRUE(tmp_op.p == nullptr);

    auto x_gate = dd->makeGateDD(dd::Xmat, 1, 0);
    dd->operations.insert(1, dd::ATrue, 0, x_gate);
    tmp_op = dd->operations.lookup(1, dd::ATrue, 0);
    EXPECT_TRUE(tmp_op.p == x_gate.p);

    tmp_op = dd->multiply(tmp_op, x_gate);

    // I only check this, so that the above test is evaluated when compiled using release mode
    EXPECT_TRUE(tmp_op.p != nullptr);

    dd->garbageCollect(true);
    tmp_op = dd->operations.lookup(1, dd::ATrue, 0);
    EXPECT_TRUE(tmp_op.p == nullptr);
}

TEST(DDPackageTest, TrivialTest) {
    auto dd = std::make_unique<dd::Package>(2);
    EXPECT_EQ(dd->qubits(), 2);

    auto x_gate = dd->makeGateDD(dd::Xmat, 1, 0);
    auto h_gate = dd->makeGateDD(dd::Hmat, 1, 0);

    ASSERT_EQ(dd->getValueByPath(h_gate, "0"), (dd::ComplexValue{dd::SQRT_2, 0}));

    auto zero_state = dd->makeZeroState(1);
    auto h_state    = dd->multiply(h_gate, zero_state);
    auto one_state  = dd->multiply(x_gate, zero_state);

    ASSERT_EQ(dd->fidelity(zero_state, one_state), 0.0);
    ASSERT_NEAR(dd->fidelity(zero_state, h_state), 0.5, dd::ComplexNumbers::TOLERANCE);
    ASSERT_NEAR(dd->fidelity(one_state, h_state), 0.5, dd::ComplexNumbers::TOLERANCE);
}

TEST(DDPackageTest, BellState) {
    auto dd = std::make_unique<dd::Package>(2);

    auto h_gate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cx_gate    = dd->makeGateDD(dd::Xmat, 2, 1, 0);
    auto zero_state = dd->makeZeroState(2);

    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    ASSERT_EQ(dd->getValueByPath(bell_state, "00"), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "01"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "10"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "11"), (dd::ComplexValue{dd::SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_state, 0), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, 1), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, 2), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, 3), (dd::ComplexValue{dd::SQRT_2, 0}));

    auto goal_state = std::vector<std::pair<float, float>>{{dd::SQRT_2, 0.}, {0., 0.}, {0., 0.}, {dd::SQRT_2, 0.}};
    ASSERT_EQ(dd->getVector(bell_state), goal_state);

    ASSERT_DOUBLE_EQ(dd->fidelity(zero_state, bell_state), 0.5);

    export2Dot(bell_state, "bell_state_colored_labels.dot", true, true, false);
    export2Dot(bell_state, "bell_state_colored_labels_classic.dot", true, true, true);
    export2Dot(bell_state, "bell_state_mono_labels.dot", false, true, false);
    export2Dot(bell_state, "bell_state_mono_labels_classic.dot", false, true, true);
    export2Dot(bell_state, "bell_state_colored.dot", true, false, false);
    export2Dot(bell_state, "bell_state_colored_classic.dot", true, false, true);
    export2Dot(bell_state, "bell_state_mono.dot", false, false, false);
    export2Dot(bell_state, "bell_state_mono_classic.dot", false, false, true);

    dd->statistics();
}

TEST(DDPackageTest, NegativeControl) {
    auto dd = std::make_unique<dd::Package>(2);

    auto x_gate     = dd->makeGateDD(dd::Xmat, 2, 1_nc, 0);
    auto zero_state = dd->makeZeroState(2);
    auto state01    = dd->multiply(x_gate, zero_state);
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
    EXPECT_EQ(CN::val(mul.w.r), 4.0);
}

TEST(DDPackageTest, StateGenerationManipulation) {
    unsigned short nqubits = 6;
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
}

TEST(DDPackageTest, VectorSerializationTest) {
    auto dd = std::make_unique<dd::Package>(2);

    auto h_gate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cx_gate    = dd->makeGateDD(dd::Xmat, 2, 1, 0);
    auto zero_state = dd->makeZeroState(2);

    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    serialize(bell_state, "bell_state.dd", false);
    auto deserialized_bell_state = dd->deserialize<dd::Package::vNode>("bell_state.dd", false);
    EXPECT_EQ(bell_state, deserialized_bell_state);

    serialize(bell_state, "bell_state_binary.dd", true);
    deserialized_bell_state = dd->deserialize<dd::Package::vNode>("bell_state_binary.dd", true);
    EXPECT_EQ(bell_state, deserialized_bell_state);
}

TEST(DDPackageTest, BellMatrix) {
    auto dd = std::make_unique<dd::Package>(2);

    auto h_gate  = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cx_gate = dd->makeGateDD(dd::Xmat, 2, 1, 0);

    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    ASSERT_EQ(dd->getValueByPath(bell_matrix, "00"), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, "02"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, "20"), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, "22"), (dd::ComplexValue{dd::SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 0), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 0), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 0), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 0), (dd::ComplexValue{dd::SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 1), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 1), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 1), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 1), (dd::ComplexValue{0, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 2), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 2), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 2), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 2), (dd::ComplexValue{-dd::SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 3), (dd::ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 3), (dd::ComplexValue{dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 3), (dd::ComplexValue{-dd::SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 3), (dd::ComplexValue{0, 0}));

    auto goal_row_0  = dd::CVec{{dd::SQRT_2, 0.}, {0., 0.}, {dd::SQRT_2, 0.}, {0., 0.}};
    auto goal_row_1  = dd::CVec{{0., 0.}, {dd::SQRT_2, 0.}, {0., 0.}, {dd::SQRT_2, 0.}};
    auto goal_row_2  = dd::CVec{{0., 0.}, {dd::SQRT_2, 0.}, {0., 0.}, {-dd::SQRT_2, 0.}};
    auto goal_row_3  = dd::CVec{{dd::SQRT_2, 0.}, {0., 0.}, {-dd::SQRT_2, 0.}, {0., 0.}};
    auto goal_matrix = dd::CMat{goal_row_0, goal_row_1, goal_row_2, goal_row_3};
    ASSERT_EQ(dd->getMatrix(bell_matrix), goal_matrix);

    export2Dot(bell_matrix, "bell_matrix_colored_labels.dot", true, true, false);
    export2Dot(bell_matrix, "bell_matrix_colored_labels_classic.dot", true, true, true);
    export2Dot(bell_matrix, "bell_matrix_mono_labels.dot", false, true, false);
    export2Dot(bell_matrix, "bell_matrix_mono_labels_classic.dot", false, true, true);
    export2Dot(bell_matrix, "bell_matrix_colored.dot", true, false, false);
    export2Dot(bell_matrix, "bell_matrix_colored_classic.dot", true, false, true);
    export2Dot(bell_matrix, "bell_matrix_mono.dot", false, false, false);
    export2Dot(bell_matrix, "bell_matrix_mono_classic.dot", false, false, true);

    dd->statistics();
}

TEST(DDPackageTest, MatrixSerializationTest) {
    auto dd = std::make_unique<dd::Package>(2);

    auto h_gate  = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cx_gate = dd->makeGateDD(dd::Xmat, 2, 1, 0);

    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    serialize(bell_matrix, "bell_matrix.dd", false);
    auto deserialized_bell_matrix = dd->deserialize<dd::Package::mNode>("bell_matrix.dd", false);
    EXPECT_EQ(bell_matrix, deserialized_bell_matrix);

    serialize(bell_matrix, "bell_matrix_binary.dd", true);
    deserialized_bell_matrix = dd->deserialize<dd::Package::mNode>("bell_matrix_binary.dd", true);
    EXPECT_EQ(bell_matrix, deserialized_bell_matrix);
}

TEST(DDPackageTest, SerializationErrors) {
    auto dd = std::make_unique<dd::Package>(2);

    auto h_gate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cx_gate    = dd->makeGateDD(dd::Xmat, 2, 1, 0);
    auto zero_state = dd->makeZeroState(2);
    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    // test non-existing file
    serialize(bell_state, "./path/that/does/not/exist/filename.dd");
    auto e = dd->deserialize<dd::Package::vNode>("./path/that/does/not/exist/filename.dd", true);
    EXPECT_TRUE(e.isZeroTerminal());

    // test wrong version number
    std::stringstream ss{};
    ss << 2.0 << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss, false), std::runtime_error);
    ss << 2.0 << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss, false), std::runtime_error);

    ss.str("");
    dd::fp version = 2.0;
    ss.write(reinterpret_cast<const char*>(&version), sizeof(dd::fp));
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss, true), std::runtime_error);
    ss.write(reinterpret_cast<const char*>(&version), sizeof(dd::fp));
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss, true), std::runtime_error);

    // test wrong format
    ss.str("");
    ss << "0.1" << std::endl;
    ss << "not_complex" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss), std::runtime_error);
    ss << "0.1" << std::endl;
    ss << "not_complex" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss), std::runtime_error);

    ss.str("");
    ss << "0.1" << std::endl;
    ss << "1.0" << std::endl;
    ss << "no_node_here" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::vNode>(ss), std::runtime_error);
    ss << "0.1" << std::endl;
    ss << "1.0" << std::endl;
    ss << "no_node_here" << std::endl;
    EXPECT_THROW(dd->deserialize<dd::Package::mNode>(ss), std::runtime_error);
}

TEST(DDPackageTest, TestConsistency) {
    auto dd = std::make_unique<dd::Package>(2);

    auto h_gate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cx_gate    = dd->makeGateDD(dd::Xmat, 2, 1, 0);
    auto zero_state = dd->makeZeroState(2);

    auto bell_matrix = dd->multiply(cx_gate, h_gate);
    dd->incRef(bell_matrix);
    auto local = dd->isLocallyConsistent(bell_matrix);
    EXPECT_TRUE(local);
    auto global = dd->isGloballyConsistent(bell_matrix);
    EXPECT_TRUE(global);
    dd->debugnode(bell_matrix.p);

    auto bell_state = dd->multiply(bell_matrix, zero_state);
    dd->incRef(bell_state);
    local = dd->isLocallyConsistent(bell_state);
    EXPECT_TRUE(local);
    global = dd->isGloballyConsistent(bell_state);
    EXPECT_TRUE(global);
    dd->debugnode(bell_state.p);
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
    auto& table = dd->getIdentityTable();
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

    auto h_gate     = dd->makeGateDD(dd::Hmat, 2, 0);
    auto cx_gate    = dd->makeGateDD(dd::Xmat, 2, 0, 1);
    auto zero_state = dd->makeZeroState(2);

    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);
    auto local      = dd->isLocallyConsistent(bell_state);
    EXPECT_FALSE(local);
    bell_state.p->ref = 1;
    local             = dd->isLocallyConsistent(bell_state);
    EXPECT_FALSE(local);
    bell_state.p->ref = 0;
    dd->incRef(bell_state);

    bell_state.p->v = 2;
    local           = dd->isLocallyConsistent(bell_state);
    EXPECT_FALSE(local);
    bell_state.p->v = 1;

    bell_state.p->e[0].w.r->ref = 0;
    local                       = dd->isLocallyConsistent(bell_state);
    EXPECT_FALSE(local);
    bell_state.p->e[0].w.r->ref = 1;
}

TEST(DDPackageTest, Ancillaries) {
    auto dd          = std::make_unique<dd::Package>(4);
    auto h_gate      = dd->makeGateDD(dd::Hmat, 2, 0);
    auto cx_gate     = dd->makeGateDD(dd::Xmat, 2, 0, 1);
    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    auto reduced_bell_matrix = dd->reduceAncillae(bell_matrix, {false, false, false, false});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);
    reduced_bell_matrix = dd->reduceAncillae(bell_matrix, {false, false, true, true});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);

    auto extended_bell_matrix = dd->extend(bell_matrix, 2);
    reduced_bell_matrix       = dd->reduceAncillae(extended_bell_matrix, {false, false, true, true});
    EXPECT_TRUE(reduced_bell_matrix.p->e[1].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[2].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[3].isZeroTerminal());

    EXPECT_EQ(reduced_bell_matrix.p->e[0].p->e[0].p, bell_matrix.p);
    EXPECT_TRUE(reduced_bell_matrix.p->e[0].p->e[1].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[0].p->e[2].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[0].p->e[3].isZeroTerminal());

    reduced_bell_matrix = dd->reduceAncillae(extended_bell_matrix, {false, false, true, true}, false);
    EXPECT_TRUE(reduced_bell_matrix.p->e[1].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[2].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[3].isZeroTerminal());

    EXPECT_EQ(reduced_bell_matrix.p->e[0].p->e[0].p, bell_matrix.p);
    EXPECT_TRUE(reduced_bell_matrix.p->e[0].p->e[1].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[0].p->e[2].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[0].p->e[3].isZeroTerminal());
}

TEST(DDPackageTest, Garbage) {
    auto dd          = std::make_unique<dd::Package>(4);
    auto h_gate      = dd->makeGateDD(dd::Hmat, 2, 0);
    auto cx_gate     = dd->makeGateDD(dd::Xmat, 2, 0, 1);
    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    auto reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {false, false, false, false});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);
    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {false, false, true, false});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);

    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {false, true, false, false});
    auto mat            = dd->getMatrix(reduced_bell_matrix);
    auto zero           = dd::CVec{{0., 0.}, {0., 0.}, {0., 0.}, {0., 0.}};
    EXPECT_EQ(mat[2], zero);
    EXPECT_EQ(mat[3], zero);

    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {true, false, false, false});
    mat                 = dd->getMatrix(reduced_bell_matrix);
    EXPECT_EQ(mat[1], zero);
    EXPECT_EQ(mat[3], zero);

    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {false, true, false, false}, false);
    EXPECT_TRUE(reduced_bell_matrix.p->e[1].isZeroTerminal());
    EXPECT_TRUE(reduced_bell_matrix.p->e[3].isZeroTerminal());
}

TEST(DDPackageTest, InvalidMakeBasisState) {
    auto nqubits    = 2;
    auto dd         = std::make_unique<dd::Package>(nqubits);
    auto basisState = std::vector<dd::BasisStates>{dd::BasisStates::zero};
    EXPECT_THROW(dd->makeBasisState(nqubits, basisState), std::invalid_argument);
}

TEST(DDPackageTest, InvalidDecRef) {
    auto dd = std::make_unique<dd::Package>(2);
    auto e  = dd->makeIdent(2);
    EXPECT_THROW(dd->decRef(e), std::runtime_error);
}

TEST(DDPackageTest, PackageReset) {
    auto dd = std::make_unique<dd::Package>(1);

    // one node in unique table of variable 0
    auto        i_gate = dd->makeIdent(1);
    const auto& unique = dd->mUniqueTable.getTables();
    const auto& table  = unique[0];
    auto        ihash  = dd->mUniqueTable.hash(i_gate.p);
    const auto& node   = table[ihash].front();
    std::cout << ihash << ": " << reinterpret_cast<uintptr_t>(i_gate.p) << std::endl;
    // node should be the first in this unique table bucket
    EXPECT_EQ(node, i_gate.p);
    dd->reset();
    // after clearing the tables, they should be empty
    EXPECT_TRUE(table[ihash].empty());
    i_gate            = dd->makeIdent(1);
    const auto& node2 = table[ihash].front();
    // after recreating the DD, it should receive the same node
    EXPECT_EQ(node2, node);

    // two nodes in same unique table bucket of variable 0
    auto z_gate = dd->makeGateDD(dd::Zmat, 1, 0);
    auto zhash  = dd->mUniqueTable.hash(z_gate.p);
    std::cout << zhash << ": " << reinterpret_cast<uintptr_t>(z_gate.p) << std::endl;
    // both nodes should reside in the same bucket
    EXPECT_EQ(table[ihash].front(), z_gate.p);
    auto it = table[ihash].begin();
    std::advance(it, 1);
    EXPECT_EQ(*it, i_gate.p);
    dd->reset();
    // after clearing the tables, they should be empty
    EXPECT_TRUE(table[ihash].empty());
    auto z_gate2 = dd->makeGateDD(dd::Zmat, 1, 0);
    auto i_gate2 = dd->makeIdent(1);
    // recreating the decision diagrams in reverse order should use the same pointers as before
    EXPECT_EQ(z_gate2.p, i_gate.p);
    EXPECT_EQ(i_gate2.p, z_gate.p);
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
    dd->garbageCollect(true);
}
