/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#include "DDexport.hpp"
#include "DDpackage.hpp"
#include "GateMatrixDefinitions.hpp"

#include "gtest/gtest.h"
#include <memory>

using namespace dd;

TEST(DDPackageTest, OperationLookupTest) {
    auto dd = std::make_unique<Package>();

    // ATrue is not the operation that is being stored, but for the test it doesn't matter
    auto tmp_op = dd->operations.lookup(0, ATrue, {2});
    EXPECT_TRUE(tmp_op.p == nullptr);

    auto x_gate = dd->makeGateDD(Xmat, 0, {2});
    dd->operations.insert(0, ATrue, {2}, x_gate);
    tmp_op = dd->operations.lookup(0, ATrue, {2});
    EXPECT_TRUE(tmp_op.p == x_gate.p);

    tmp_op = dd->multiply(tmp_op, x_gate);

    // I only check this, so that the above test is evaluated when compiled using release mode
    EXPECT_TRUE(tmp_op.p != nullptr);

    dd->garbageCollect(true);
    tmp_op = dd->operations.lookup(0, ATrue, {2});
    EXPECT_TRUE(tmp_op.p == nullptr);
}

TEST(DDPackageTest, TrivialTest) {
    auto dd = std::make_unique<Package>();

    auto x_gate = dd->makeGateDD(Xmat, 0, {2});
    auto h_gate = dd->makeGateDD(Hmat, 0, {2});

    ASSERT_EQ(dd->getValueByPath(h_gate, "0"), (ComplexValue{SQRT_2, 0}));

    auto zero_state = dd->makeZeroState(0);
    auto h_state    = dd->multiply(h_gate, zero_state);
    auto one_state  = dd->multiply(x_gate, zero_state);

    ASSERT_EQ(dd->fidelity(zero_state, one_state), 0.0);
    ASSERT_NEAR(dd->fidelity(zero_state, h_state), 0.5, ComplexNumbers::TOLERANCE);
    ASSERT_NEAR(dd->fidelity(one_state, h_state), 0.5, ComplexNumbers::TOLERANCE);
}

TEST(DDPackageTest, BellState) {
    auto dd = std::make_unique<Package>();

    auto h_gate     = dd->makeGateDD(Hmat, 1, {-1, 2});
    auto cx_gate    = dd->makeGateDD(Xmat, 1, {2, 1});
    auto zero_state = dd->makeZeroState(1);

    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    ASSERT_EQ(dd->getValueByPath(bell_state, "00"), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "01"), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "10"), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, "11"), (ComplexValue{SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_state, 0), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, 1), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, 2), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_state, 3), (ComplexValue{SQRT_2, 0}));

    auto goal_state = std::vector<std::pair<float, float>>{{SQRT_2, 0.}, {0., 0.}, {0., 0.}, {SQRT_2, 0.}};
    ASSERT_EQ(dd->getVector(bell_state), goal_state);

    ASSERT_DOUBLE_EQ(dd->fidelity(zero_state, bell_state), 0.5);

    export2Dot(bell_state, "bell_state_colored_labels.dot", true, true, false, false);
    export2Dot(bell_state, "bell_state_colored_labels_classic.dot", true, true, true, false);
    export2Dot(bell_state, "bell_state_mono_labels.dot", false, true, false, false);
    export2Dot(bell_state, "bell_state_mono_labels_classic.dot", false, true, true, false);
    export2Dot(bell_state, "bell_state_colored.dot", true, false, false, false);
    export2Dot(bell_state, "bell_state_colored_classic.dot", true, false, true, false);
    export2Dot(bell_state, "bell_state_mono.dot", false, false, false, false);
    export2Dot(bell_state, "bell_state_mono_classic.dot", false, false, true, false);
}

TEST(DDPackageTest, IdentityTrace) {
    auto dd        = std::make_unique<Package>();
    auto fullTrace = dd->trace(dd->makeIdent(3));

    ASSERT_EQ(fullTrace, (ComplexValue{16, 0}));
}

TEST(DDPackageTest, PartialIdentityTrace) {
    auto dd  = std::make_unique<Package>();
    auto tr  = dd->partialTrace(dd->makeIdent(1), std::bitset<MAXN>(1));
    auto mul = dd->multiply(tr, tr);
    EXPECT_EQ(CN::val(mul.w.r), 4.0);
}

TEST(DDPackageTest, StateGeneration) {
    auto dd = std::make_unique<Package>();

    auto b = std::bitset<MAXN>{2};
    auto e = dd->makeBasisState(5, b);
    auto f = dd->makeBasisState(5, {BasisStates::zero,
                                    BasisStates::one,
                                    BasisStates::plus,
                                    BasisStates::minus,
                                    BasisStates::left,
                                    BasisStates::right});
    dd->incRef(e);
    dd->incRef(f);
    dd->vUniqueTable.printActive();
    dd->vUniqueTable.print();
    dd->printInformation();
}

TEST(DDPackageTest, VectorSerializationTest) {
    auto dd = std::make_unique<Package>();

    auto h_gate     = dd->makeGateDD(Hmat, 1, {-1, 2});
    auto cx_gate    = dd->makeGateDD(Xmat, 1, {2, 1});
    auto zero_state = dd->makeZeroState(1);

    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    serialize(bell_state, "bell_state.dd", false);
    auto deserialized_bell_state = deserializeVector(dd, "bell_state.dd", false);
    EXPECT_EQ(bell_state, deserialized_bell_state);

    serialize(bell_state, "bell_state_binary.dd", true);
    deserialized_bell_state = deserializeVector(dd, "bell_state_binary.dd", true);
    EXPECT_EQ(bell_state, deserialized_bell_state);
}

TEST(DDPackageTest, BellMatrix) {
    auto dd = std::make_unique<Package>();

    auto h_gate  = dd->makeGateDD(Hmat, 1, {-1, 2});
    auto cx_gate = dd->makeGateDD(Xmat, 1, {2, 1});

    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    ASSERT_EQ(dd->getValueByPath(bell_matrix, "00"), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, "02"), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, "20"), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, "22"), (ComplexValue{SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 0), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 0), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 0), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 0), (ComplexValue{SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 1), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 1), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 1), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 1), (ComplexValue{0, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 2), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 2), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 2), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 2), (ComplexValue{-SQRT_2, 0}));

    ASSERT_EQ(dd->getValueByPath(bell_matrix, 0, 3), (ComplexValue{0, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 1, 3), (ComplexValue{SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 2, 3), (ComplexValue{-SQRT_2, 0}));
    ASSERT_EQ(dd->getValueByPath(bell_matrix, 3, 3), (ComplexValue{0, 0}));

    auto goal_row_0  = CVec{{SQRT_2, 0.}, {0., 0.}, {SQRT_2, 0.}, {0., 0.}};
    auto goal_row_1  = CVec{{0., 0.}, {SQRT_2, 0.}, {0., 0.}, {SQRT_2, 0.}};
    auto goal_row_2  = CVec{{0., 0.}, {SQRT_2, 0.}, {0., 0.}, {-SQRT_2, 0.}};
    auto goal_row_3  = CVec{{SQRT_2, 0.}, {0., 0.}, {-SQRT_2, 0.}, {0., 0.}};
    auto goal_matrix = CMat{goal_row_0, goal_row_1, goal_row_2, goal_row_3};
    ASSERT_EQ(dd->getMatrix(bell_matrix), goal_matrix);

    export2Dot(bell_matrix, "bell_matrix_colored_labels.dot", true, true, false, false);
    export2Dot(bell_matrix, "bell_matrix_colored_labels_classic.dot", true, true, true, false);
    export2Dot(bell_matrix, "bell_matrix_mono_labels.dot", false, true, false, false);
    export2Dot(bell_matrix, "bell_matrix_mono_labels_classic.dot", false, true, true, false);
    export2Dot(bell_matrix, "bell_matrix_colored.dot", true, false, false, false);
    export2Dot(bell_matrix, "bell_matrix_colored_classic.dot", true, false, true, false);
    export2Dot(bell_matrix, "bell_matrix_mono.dot", false, false, false, false);
    export2Dot(bell_matrix, "bell_matrix_mono_classic.dot", false, false, true, false);
}

TEST(DDPackageTest, MatrixSerializationTest) {
    auto dd = std::make_unique<Package>();

    auto h_gate  = dd->makeGateDD(Hmat, 1, {-1, 2});
    auto cx_gate = dd->makeGateDD(Xmat, 1, {2, 1});

    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    serialize(bell_matrix, "bell_matrix.dd", false);
    auto deserialized_bell_matrix = deserializeMatrix(dd, "bell_matrix.dd", false);
    EXPECT_EQ(bell_matrix, deserialized_bell_matrix);

    serialize(bell_matrix, "bell_matrix_binary.dd", true);
    deserialized_bell_matrix = deserializeMatrix(dd, "bell_matrix_binary.dd", true);
    EXPECT_EQ(bell_matrix, deserialized_bell_matrix);
}

TEST(DDPackageTest, SerializationErrors) {
    auto dd = std::make_unique<Package>();

    auto h_gate     = dd->makeGateDD(Hmat, 1, {-1, 2});
    auto cx_gate    = dd->makeGateDD(Xmat, 1, {2, 1});
    auto zero_state = dd->makeZeroState(1);
    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    // test non-existing file
    serialize(bell_state, "./path/that/does/not/exist/filename.dd");
    auto e = deserializeVector(dd, "./path/that/does/not/exist/filename.dd", true);
    EXPECT_TRUE(Package::isZeroDD(e));

    // test wrong version number
    std::stringstream ss{};
    ss << 2.0 << std::endl;
    EXPECT_THROW(deserializeVector(dd, ss, false), std::runtime_error);
    ss << 2.0 << std::endl;
    EXPECT_THROW(deserializeMatrix(dd, ss, false), std::runtime_error);

    ss.str("");
    fp version = 2.0;
    ss.write(reinterpret_cast<const char*>(&version), sizeof(fp));
    EXPECT_THROW(deserializeVector(dd, ss, true), std::runtime_error);
    ss.write(reinterpret_cast<const char*>(&version), sizeof(fp));
    EXPECT_THROW(deserializeMatrix(dd, ss, true), std::runtime_error);

    // test wrong format
    ss.str("");
    ss << "0.1" << std::endl;
    ss << "not_complex" << std::endl;
    EXPECT_THROW(deserializeVector(dd, ss), std::runtime_error);
    ss << "0.1" << std::endl;
    ss << "not_complex" << std::endl;
    EXPECT_THROW(deserializeMatrix(dd, ss), std::runtime_error);

    ss.str("");
    ss << "0.1" << std::endl;
    ss << "1.0" << std::endl;
    ss << "no_node_here" << std::endl;
    EXPECT_THROW(deserializeVector(dd, ss), std::runtime_error);
    ss << "0.1" << std::endl;
    ss << "1.0" << std::endl;
    ss << "no_node_here" << std::endl;
    EXPECT_THROW(deserializeMatrix(dd, ss), std::runtime_error);
}

TEST(DDPackageTest, TestConsistency) {
    auto dd = std::make_unique<Package>();

    auto h_gate     = dd->makeGateDD(Hmat, 1, {2, -1});
    auto cx_gate    = dd->makeGateDD(Xmat, 1, {1, 2});
    auto zero_state = dd->makeZeroState(1);

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
    auto dd = std::make_unique<Package>();

    // try to search for a toffoli in an empty table
    auto toffoli = dd->toffoliTable.lookup(2, 2, {2});
    EXPECT_EQ(toffoli.p, nullptr);
    if (toffoli.p == nullptr) {
        toffoli = dd->makeGateDD(Xmat, 2, {0, 1, 2});
        dd->toffoliTable.insert(2, 2, {2}, toffoli);
    }

    // try again with same toffoli
    auto toffoliTableEntry = dd->toffoliTable.lookup(2, 2, {2});
    EXPECT_NE(toffoliTableEntry.p, nullptr);
    EXPECT_EQ(toffoli, toffoliTableEntry);

    // try again with different controlled toffoli
    toffoliTableEntry = dd->toffoliTable.lookup(2, 2, {0, 2});
    EXPECT_EQ(toffoliTableEntry.p, nullptr);

    // try again with different qubit toffoli
    toffoliTableEntry = dd->toffoliTable.lookup(3, 3, {0, 2, 4});
    EXPECT_EQ(toffoliTableEntry.p, nullptr);
}

TEST(DDPackageTest, Extend) {
    auto dd = std::make_unique<Package>();

    auto id = dd->makeIdent(2);
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
    auto dd = std::make_unique<Package>();

    EXPECT_TRUE(dd->isOneDD(dd->makeIdent(-1)));
    EXPECT_TRUE(dd->isOneDD(dd->makeIdent(0, -1)));

    auto id3 = dd->makeIdent(2);
    EXPECT_EQ(dd->makeIdent(0, 2), id3);
    auto& table = dd->getIdentityTable();
    EXPECT_NE(table[2].p, nullptr);

    auto id2 = dd->makeIdent(0, 1); // should be found in IdTable
    EXPECT_EQ(dd->makeIdent(1), id2);

    auto id4 = dd->makeIdent(0, 3); // should use id3 and extend it
    EXPECT_EQ(dd->makeIdent(3), id4);
    EXPECT_NE(table[3].p, nullptr);

    auto idCached = dd->makeIdent(0, 3);
    EXPECT_EQ(id4, idCached);
}

TEST(DDPackageTest, TestLocalInconsistency) {
    auto dd = std::make_unique<Package>();

    auto h_gate     = dd->makeGateDD(Hmat, 1, {2, -1});
    auto cx_gate    = dd->makeGateDD(Xmat, 1, {1, 2});
    auto zero_state = dd->makeZeroState(1);

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
    auto dd          = std::make_unique<Package>();
    auto h_gate      = dd->makeGateDD(Hmat, 1, {2, -1});
    auto cx_gate     = dd->makeGateDD(Xmat, 1, {1, 2});
    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    auto reduced_bell_matrix = dd->reduceAncillae(bell_matrix, {0b00});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);
    reduced_bell_matrix = dd->reduceAncillae(bell_matrix, {0b100});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);

    auto extended_bell_matrix = dd->extend(bell_matrix, 2);
    reduced_bell_matrix       = dd->reduceAncillae(extended_bell_matrix, {0b1100});
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[1]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[2]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[3]));

    EXPECT_EQ(reduced_bell_matrix.p->e[0].p->e[0].p, bell_matrix.p);
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[0].p->e[1]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[0].p->e[2]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[0].p->e[3]));

    reduced_bell_matrix = dd->reduceAncillae(extended_bell_matrix, {0b1100}, false);
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[1]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[2]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[3]));

    EXPECT_EQ(reduced_bell_matrix.p->e[0].p->e[0].p, bell_matrix.p);
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[0].p->e[1]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[0].p->e[2]));
    EXPECT_TRUE(dd->isZeroDD(reduced_bell_matrix.p->e[0].p->e[3]));
}

TEST(DDPackageTest, Garbage) {
    auto dd          = std::make_unique<Package>();
    auto h_gate      = dd->makeGateDD(Hmat, 1, {2, -1});
    auto cx_gate     = dd->makeGateDD(Xmat, 1, {1, 2});
    auto bell_matrix = dd->multiply(cx_gate, h_gate);

    auto reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {0b00});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);
    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {0b100});
    EXPECT_EQ(bell_matrix, reduced_bell_matrix);

    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {0b10});
    auto mat            = dd->getMatrix(reduced_bell_matrix);
    auto zero           = dd::CVec{{0., 0.}, {0., 0.}, {0., 0.}, {0., 0.}};
    EXPECT_EQ(mat[2], zero);
    EXPECT_EQ(mat[3], zero);

    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {0b01});
    mat                 = dd->getMatrix(reduced_bell_matrix);
    EXPECT_EQ(mat[1], zero);
    EXPECT_EQ(mat[3], zero);

    reduced_bell_matrix = dd->reduceGarbage(bell_matrix, {0b10}, false);
    EXPECT_TRUE(Package::isZeroDD(reduced_bell_matrix.p->e[1]));
    EXPECT_TRUE(Package::isZeroDD(reduced_bell_matrix.p->e[3]));
}

TEST(DDPackageTest, InvalidMakeBasisState) {
    auto dd         = std::make_unique<Package>();
    auto basisState = std::vector<BasisStates>{BasisStates::zero};
    auto nqubits    = 2;
    EXPECT_THROW(dd->makeBasisState(nqubits - 1, basisState), std::invalid_argument);
}

TEST(DDPackageTest, InvalidDecRef) {
    auto dd = std::make_unique<Package>();
    auto e  = dd->makeIdent(2);
    EXPECT_THROW(dd->decRef(e), std::runtime_error);
}

TEST(DDPackageTest, PackageReset) {
    auto dd = std::make_unique<Package>();

    // one node in unique table of variable 0
    auto        i_gate = dd->makeIdent(0);
    const auto& unique = dd->mUniqueTable.getTables();
    const auto& table  = unique[0];
    auto        ihash  = dd->hash(i_gate.p);
    const auto& bucket = table[ihash];
    std::cout << ihash << ": " << reinterpret_cast<uintptr_t>(i_gate.p) << std::endl;
    // node should be the first in this unique table bucket
    EXPECT_EQ(bucket, i_gate.p);
    dd->reset();
    // after clearing the tables, they should be empty
    EXPECT_EQ(bucket, nullptr);
    i_gate              = dd->makeIdent(0);
    const auto& bucket2 = table[ihash];
    // after recreating the DD, it should receive the same node
    EXPECT_EQ(bucket2, bucket);

    // two nodes in same unique table bucket of variable 0
    auto z_gate = dd->makeGateDD(dd::Zmat, 0, {2});
    auto zhash  = dd->hash(z_gate.p);
    std::cout << zhash << ": " << reinterpret_cast<uintptr_t>(z_gate.p) << std::endl;
    // both nodes should reside in the same bucket
    EXPECT_EQ(table[ihash], z_gate.p);
    EXPECT_EQ(table[ihash]->next, i_gate.p);
    dd->reset();
    // after clearing the tables, they should be empty
    EXPECT_EQ(table[ihash], nullptr);
    auto z_gate2 = dd->makeGateDD(Zmat, 0, {2});
    auto i_gate2 = dd->makeIdent(0);
    // recreating the decision diagrams in reverse order should use the same pointers as before
    EXPECT_EQ(z_gate2.p, i_gate.p);
    EXPECT_EQ(i_gate2.p, z_gate.p);
}
