
#include "dd/Definitions.hpp"
#include "dd/Export.hpp"
#include "dd/GateMatrixDefinitions.hpp"
#include "dd/LimTable.hpp"
#include "dd/Package.hpp"
#include "dd/QuantumCircuitSimulation.hpp"
#include "dd/QuantumGate.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iomanip>
#include <memory>
#include <random>
#include <sstream>

using namespace dd::literals;

TEST(LimTest, cachingTests) {
    auto limdd = std::make_unique<dd::Package<>>(10, dd::LIMDD_group::Pauli_group, false);

    auto firstLim  = limdd->lf.limCache.getCachedLim();
    auto secondLim = limdd->lf.limCache.getCachedLim();
    EXPECT_NE(firstLim, secondLim);

    auto thirdLim = limdd->lf.limCache.getCachedLim();
    auto tempLim  = limdd->lf.limCache.getTemporaryLim();
    EXPECT_EQ(thirdLim, tempLim);
    EXPECT_EQ(3, limdd->lf.limCache.getCount());

    limdd->lf.limCache.returnToCache(firstLim);
    EXPECT_EQ(firstLim, limdd->lf.limCache.getTemporaryLim());
    EXPECT_EQ(2, limdd->lf.limCache.getCount());

    limdd->lf.limCache.returnToCache(secondLim);
    EXPECT_EQ(secondLim, limdd->lf.limCache.getTemporaryLim());
    EXPECT_EQ(1, limdd->lf.limCache.getCount());

    limdd->lf.limCache.returnToCache(thirdLim);
    EXPECT_EQ(thirdLim, limdd->lf.limCache.getTemporaryLim());
    EXPECT_EQ(0, limdd->lf.limCache.getCount());

    std::cout << "Testing lf" << std::endl;
}

TEST(LimTest, generatedCircuit_TwoH) {
    dd::QuantumCircuit circuit(2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, limddCachingTest) {
    std::mt19937_64    mt;
    std::size_t        numberOfQubits = 1;
    dd::QuantumCircuit circuit(numberOfQubits);
    //    auto               dd           = std::make_unique<dd::Package<>>(numberOfQubits);
    //    dd::vEdge          state        = dd->makeZeroState(numberOfQubits);
    //    auto&              computeTable = dd->getMultiplicationComputeTable<dd::mNode, dd::vNode>();
    //    auto               operation    = dd->makeGateDD(dd::Hmat, numberOfQubits, 0);
    //    auto               lim          = dd->makeGateDD(dd::Xmat, numberOfQubits, 0);
    //
    //    state = dd->multiply(operation, state);
    //
    //    state = dd->multiply(operation, state);
    //    state = dd->multiply(lim, state);
    //    state = dd->multiply(operation, state, 0, false, dd::Hmat, 0);
    //    computeTable.printStatistics();

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);

    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, errorCorrectionBitSetError) {
    dd::QuantumCircuit circuit(17);

    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Xmat, 14_pc, 0);
    circuit.addGate(dd::Xmat, 14_pc, 4);
    circuit.addGate(dd::Xmat, 14_pc, 8);
    circuit.addGate(dd::Xmat, 14_pc, 12);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Xmat, 15_pc, 2);
    circuit.addGate(dd::Xmat, 15_pc, 4);
    circuit.addGate(dd::Xmat, 15_pc, 10);
    circuit.addGate(dd::Xmat, 15_pc, 12);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::Xmat, 16_pc, 6);
    circuit.addGate(dd::Xmat, 16_pc, 8);
    circuit.addGate(dd::Xmat, 16_pc, 10);
    circuit.addGate(dd::Xmat, 16_pc, 12);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Xmat, 14_pc, 1);
    circuit.addGate(dd::Xmat, 14_pc, 5);
    circuit.addGate(dd::Xmat, 14_pc, 9);
    circuit.addGate(dd::Xmat, 14_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Xmat, 15_pc, 3);
    circuit.addGate(dd::Xmat, 15_pc, 5);
    circuit.addGate(dd::Xmat, 15_pc, 11);
    circuit.addGate(dd::Xmat, 15_pc, 13);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::Xmat, 16_pc, 7);
    circuit.addGate(dd::Xmat, 16_pc, 9);
    circuit.addGate(dd::Xmat, 16_pc, 11);
    circuit.addGate(dd::Xmat, 16_pc, 13);
    circuit.addGate(dd::Hmat, 16);

    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, errorCorrectionBitSetError_minimized) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

//    simulateCircuitLIMDDGateByGate(circuit);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, errorCorrectionBitSetError_2) {
    dd::QuantumCircuit circuit(17);

    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Xmat, 14_pc, 0);
    circuit.addGate(dd::Xmat, 14_pc, 4);
    circuit.addGate(dd::Xmat, 14_pc, 8);
    circuit.addGate(dd::Xmat, 14_pc, 12);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Xmat, 15_pc, 2);
    circuit.addGate(dd::Xmat, 15_pc, 4);
    circuit.addGate(dd::Xmat, 15_pc, 10);
    circuit.addGate(dd::Xmat, 15_pc, 12);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::Xmat, 16_pc, 6);
    circuit.addGate(dd::Xmat, 16_pc, 10);
    circuit.addGate(dd::Xmat, 16_pc, 12);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Xmat, 14_pc, 1);
    circuit.addGate(dd::Xmat, 14_pc, 5);
    circuit.addGate(dd::Xmat, 14_pc, 9);
    circuit.addGate(dd::Xmat, 14_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Xmat, 15_pc, 3);
    circuit.addGate(dd::Xmat, 15_pc, 5);
    circuit.addGate(dd::Xmat, 15_pc, 11);
    circuit.addGate(dd::Xmat, 15_pc, 13);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::Xmat, 16_pc, 7);
    circuit.addGate(dd::Xmat, 16_pc, 9);
    circuit.addGate(dd::Xmat, 16_pc, 11);
    circuit.addGate(dd::Xmat, 16_pc, 13);
    circuit.addGate(dd::Hmat, 16);

    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, MeasureOneCollapseTest) {
    std::mt19937_64 mt;

    auto      dd    = std::make_unique<dd::Package<>>(2);
    dd::vEdge state = dd->makeZeroState(2);
    std::cout << "Zero state\n";
    dd->printVector(state);

    auto h0 = dd->makeGateDD(dd::Hmat, 2, 0);
    state   = dd->multiply(h0, state);
    std::cout << "After Hadamard on q0\n";
    dd->printVector(state);

    auto h1 = dd->makeGateDD(dd::Hmat, 2, 1);
    state   = dd->multiply(h1, state);
    std::cout << "After Hadamart on q1\n";
    dd->printVector(state);

    dd->incRef(state);
    auto result = dd->measureOneCollapsing(state, 1, true, mt);
    std::cout << "Measurement result: " << result << "\n";
    dd->printVector(state);
}

// Randomly generated circuit on 10 qubis, containing 30 Clifford gates.
TEST(LimTest, bb84Circuit) {
    std::mt19937_64 mt;

    auto      dd    = std::make_unique<dd::Package<>>(8);
    dd::vEdge state = dd->makeZeroState(8);

    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 2), state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 3), state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 4), state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 5), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 7), state);
    dd->incRef(state);
    dd->measureOneCollapsing(state, 6, true, mt);
    dd->decRef(state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 5), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 2), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 4), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 7), state);
    dd->incRef(state);
    dd->measureOneCollapsing(state, 0, true, mt);
    dd->measureOneCollapsing(state, 3, true, mt);
    dd->measureOneCollapsing(state, 1, true, mt);
    dd->measureOneCollapsing(state, 2, true, mt);
    dd->measureOneCollapsing(state, 4, true, mt);
    dd->measureOneCollapsing(state, 5, true, mt);
    dd->measureOneCollapsing(state, 7, true, mt);
    dd->decRef(state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 2), state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 3), state);
    state = dd->multiply(dd->makeGateDD(dd::Xmat, 8, 4), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 7), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 5), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 6), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 2), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 4), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 3), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 7), state);
    dd->incRef(state);
    dd->measureOneCollapsing(state, 0, true, mt);
    dd->measureOneCollapsing(state, 5, true, mt);
    dd->measureOneCollapsing(state, 6, true, mt);
    dd->decRef(state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 2), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 8, 4), state);
}

// Randomly generated circuit on 10 qubis, containing 30 Clifford gates.
TEST(LimTest, generatedCircuit_1) {
    dd::QuantumCircuit circuit(10);

    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 3_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 5);
    circuit.addGate(dd::Xmat, 4_pc, 3);
    circuit.addGate(dd::Xmat, 2_pc, 9);
    circuit.addGate(dd::Xmat, 6);
    circuit.addGate(dd::Zmat, 4);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Zmat, 2_pc, 8);
    circuit.addGate(dd::Ymat, 0_pc, 4);
    circuit.addGate(dd::Zmat, 4_pc, 9);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 5_pc, 6);
    circuit.addGate(dd::Zmat, 6);
    circuit.addGate(dd::Zmat, 4);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Zmat, 7_pc, 6);
    circuit.addGate(dd::Ymat, 4_pc, 6);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 5_pc, 3);
    circuit.addGate(dd::Zmat, 5);
    circuit.addGate(dd::Ymat, 1_pc, 8);
    circuit.addGate(dd::Ymat, 6_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 8_pc, 0);
    circuit.addGate(dd::Zmat, 9);
    circuit.addGate(dd::Hmat, 9);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 11 qubis, containing 33 Clifford gates.
TEST(LimTest, generatedCircuit_2) {
    dd::QuantumCircuit circuit(11);

    circuit.addGate(dd::Xmat, 10_pc, 4);
    circuit.addGate(dd::Zmat, 7_pc, 5);
    circuit.addGate(dd::Xmat, 3_pc, 2);
    circuit.addGate(dd::Zmat, 3_pc, 5);
    circuit.addGate(dd::Ymat, 8);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 3_pc, 8);
    circuit.addGate(dd::Zmat, 8_pc, 9);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 6_pc, 4);
    circuit.addGate(dd::Xmat, 10_pc, 6);
    circuit.addGate(dd::Zmat, 7_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 7_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 6_pc, 1);
    circuit.addGate(dd::Xmat, 9);
    circuit.addGate(dd::Xmat, 2_pc, 4);
    circuit.addGate(dd::Zmat, 5_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Xmat, 3_pc, 5);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Xmat, 3);
    circuit.addGate(dd::Xmat, 10_pc, 8);
    circuit.addGate(dd::Xmat, 4_pc, 2);
    circuit.addGate(dd::Zmat, 6_pc, 7);
    circuit.addGate(dd::Zmat, 7_pc, 9);
    circuit.addGate(dd::Ymat, 6);
    circuit.addGate(dd::Zmat, 8_pc, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 12 qubis, containing 36 Clifford gates.
TEST(LimTest, generatedCircuit_3) {
    dd::QuantumCircuit circuit(12);

    circuit.addGate(dd::Hmat, 9);
    circuit.addGate(dd::Ymat, 9_pc, 4);
    circuit.addGate(dd::Xmat, 6_pc, 11);
    circuit.addGate(dd::Zmat, 9);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 11);
    circuit.addGate(dd::Xmat, 10_pc, 6);
    circuit.addGate(dd::Ymat, 3);
    circuit.addGate(dd::Ymat, 4_pc, 11);
    circuit.addGate(dd::Hmat, 6);
    circuit.addGate(dd::Ymat, 4_pc, 7);
    circuit.addGate(dd::Xmat, 0_pc, 7);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Ymat, 7);
    circuit.addGate(dd::Ymat, 7_pc, 4);
    circuit.addGate(dd::Zmat, 2_pc, 3);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Xmat, 6);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 8_pc, 9);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 8);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 8_pc, 7);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Smat, 8);
    circuit.addGate(dd::Zmat, 4_pc, 0);
    circuit.addGate(dd::Ymat, 6);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Ymat, 11_pc, 7);
    circuit.addGate(dd::Zmat, 0_pc, 6);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 13 qubis, containing 39 Clifford gates.
TEST(LimTest, generatedCircuit_4) {
    dd::QuantumCircuit circuit(13);

    circuit.addGate(dd::Zmat, 4);
    circuit.addGate(dd::Xmat, 4_pc, 7);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Zmat, 8_pc, 3);
    circuit.addGate(dd::Ymat, 4_pc, 1);
    circuit.addGate(dd::Zmat, 9_pc, 4);
    circuit.addGate(dd::Ymat, 4);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Xmat, 4_pc, 9);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 10_pc, 9);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 6);
    circuit.addGate(dd::Ymat, 10_pc, 12);
    circuit.addGate(dd::Zmat, 10);
    circuit.addGate(dd::Xmat, 11);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 5);
    circuit.addGate(dd::Ymat, 12);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Zmat, 11);
    circuit.addGate(dd::Xmat, 6);
    circuit.addGate(dd::Ymat, 3_pc, 6);
    circuit.addGate(dd::Ymat, 5_pc, 11);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 8_pc, 6);
    circuit.addGate(dd::Zmat, 9_pc, 1);
    circuit.addGate(dd::Zmat, 11_pc, 5);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Xmat, 3_pc, 7);
    circuit.addGate(dd::Ymat, 5);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Ymat, 10_pc, 4);
    circuit.addGate(dd::Xmat, 4_pc, 12);
    circuit.addGate(dd::Ymat, 10_pc, 3);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 14 qubis, containing 42 Clifford gates.
TEST(LimTest, generatedCircuit_5) {
    dd::QuantumCircuit circuit(14);

    circuit.addGate(dd::Xmat, 7_pc, 6);
    circuit.addGate(dd::Xmat, 11);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 10);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 9_pc, 3);
    circuit.addGate(dd::Xmat, 10_pc, 1);
    circuit.addGate(dd::Xmat, 3_pc, 1);
    circuit.addGate(dd::Smat, 6);
    circuit.addGate(dd::Zmat, 11);
    circuit.addGate(dd::Xmat, 6);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Xmat, 5);
    circuit.addGate(dd::Smat, 13);
    circuit.addGate(dd::Xmat, 3_pc, 2);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Ymat, 4_pc, 10);
    circuit.addGate(dd::Ymat, 4_pc, 2);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Smat, 3);
    circuit.addGate(dd::Ymat, 6);
    circuit.addGate(dd::Ymat, 0_pc, 5);
    circuit.addGate(dd::Ymat, 4_pc, 8);
    circuit.addGate(dd::Xmat, 8);
    circuit.addGate(dd::Zmat, 11_pc, 10);
    circuit.addGate(dd::Xmat, 4_pc, 7);
    circuit.addGate(dd::Ymat, 9);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Xmat, 8_pc, 2);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Xmat, 2_pc, 5);
    circuit.addGate(dd::Ymat, 6_pc, 1);
    circuit.addGate(dd::Zmat, 9);
    circuit.addGate(dd::Ymat, 2_pc, 13);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 12);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 11);
    circuit.addGate(dd::Zmat, 6_pc, 3);
    circuit.addGate(dd::Ymat, 10);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 15 qubis, containing 45 Clifford gates.
TEST(LimTest, generatedCircuit_6) {
    dd::QuantumCircuit circuit(15);

    circuit.addGate(dd::Zmat, 9_pc, 10);
    circuit.addGate(dd::Ymat, 11);
    circuit.addGate(dd::Hmat, 8);
    circuit.addGate(dd::Zmat, 13);
    circuit.addGate(dd::Zmat, 11_pc, 10);
    circuit.addGate(dd::Zmat, 4_pc, 3);
    circuit.addGate(dd::Ymat, 4_pc, 13);
    circuit.addGate(dd::Ymat, 3_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 4);
    circuit.addGate(dd::Xmat, 9_pc, 2);
    circuit.addGate(dd::Ymat, 8_pc, 0);
    circuit.addGate(dd::Xmat, 5_pc, 7);
    circuit.addGate(dd::Zmat, 3_pc, 5);
    circuit.addGate(dd::Zmat, 1_pc, 5);
    circuit.addGate(dd::Xmat, 3);
    circuit.addGate(dd::Zmat, 13_pc, 14);
    circuit.addGate(dd::Smat, 7);
    circuit.addGate(dd::Ymat, 10);
    circuit.addGate(dd::Smat, 9);
    circuit.addGate(dd::Ymat, 9_pc, 14);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Ymat, 2_pc, 8);
    circuit.addGate(dd::Zmat, 9_pc, 3);
    circuit.addGate(dd::Xmat, 7_pc, 6);
    circuit.addGate(dd::Xmat, 11_pc, 5);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 10);
    circuit.addGate(dd::Zmat, 11_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 9);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 12);
    circuit.addGate(dd::Ymat, 11);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 7_pc, 4);
    circuit.addGate(dd::Xmat, 11);
    circuit.addGate(dd::Ymat, 5_pc, 3);
    circuit.addGate(dd::Xmat, 12_pc, 9);
    circuit.addGate(dd::Xmat, 12_pc, 7);
    circuit.addGate(dd::Smat, 9);
    circuit.addGate(dd::Xmat, 14);
    circuit.addGate(dd::Hmat, 10);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Zmat, 4_pc, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 16 qubis, containing 48 Clifford gates.
TEST(LimTest, generatedCircuit_7) {
    dd::QuantumCircuit circuit(16);

    circuit.addGate(dd::Zmat, 12_pc, 1);
    circuit.addGate(dd::Ymat, 4);
    circuit.addGate(dd::Zmat, 4_pc, 3);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 6_pc, 8);
    circuit.addGate(dd::Xmat, 3_pc, 6);
    circuit.addGate(dd::Ymat, 9);
    circuit.addGate(dd::Xmat, 15_pc, 10);
    circuit.addGate(dd::Hmat, 6);
    circuit.addGate(dd::Xmat, 11);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 6_pc, 10);
    circuit.addGate(dd::Ymat, 11_pc, 8);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 4_pc, 15);
    circuit.addGate(dd::Zmat, 9);
    circuit.addGate(dd::Hmat, 8);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 14);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Ymat, 5);
    circuit.addGate(dd::Xmat, 7_pc, 6);
    circuit.addGate(dd::Zmat, 15_pc, 6);
    circuit.addGate(dd::Zmat, 14);
    circuit.addGate(dd::Xmat, 15);
    circuit.addGate(dd::Ymat, 1_pc, 4);
    circuit.addGate(dd::Ymat, 6_pc, 9);
    circuit.addGate(dd::Zmat, 1_pc, 7);
    circuit.addGate(dd::Xmat, 8_pc, 1);
    circuit.addGate(dd::Smat, 15);
    circuit.addGate(dd::Xmat, 12_pc, 13);
    circuit.addGate(dd::Ymat, 13);
    circuit.addGate(dd::Zmat, 12_pc, 7);
    circuit.addGate(dd::Xmat, 11_pc, 0);
    circuit.addGate(dd::Xmat, 11_pc, 10);
    circuit.addGate(dd::Xmat, 9_pc, 0);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Smat, 15);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 14_pc, 2);
    circuit.addGate(dd::Zmat, 9_pc, 5);
    circuit.addGate(dd::Zmat, 4);
    circuit.addGate(dd::Zmat, 5_pc, 11);
    circuit.addGate(dd::Ymat, 5_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 14);
    circuit.addGate(dd::Ymat, 8_pc, 14);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 17 qubis, containing 51 Clifford gates.
TEST(LimTest, generatedCircuit_8) {
    dd::QuantumCircuit circuit(17);

    circuit.addGate(dd::Ymat, 12);
    circuit.addGate(dd::Xmat, 1_pc, 15);
    circuit.addGate(dd::Xmat, 9);
    circuit.addGate(dd::Ymat, 8);
    circuit.addGate(dd::Xmat, 14);
    circuit.addGate(dd::Zmat, 1_pc, 7);
    circuit.addGate(dd::Xmat, 8_pc, 6);
    circuit.addGate(dd::Ymat, 15);
    circuit.addGate(dd::Ymat, 4);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 8);
    circuit.addGate(dd::Ymat, 0_pc, 5);
    circuit.addGate(dd::Hmat, 9);
    circuit.addGate(dd::Ymat, 8);
    circuit.addGate(dd::Ymat, 6_pc, 13);
    circuit.addGate(dd::Xmat, 10_pc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 7);
    circuit.addGate(dd::Xmat, 1_pc, 4);
    circuit.addGate(dd::Xmat, 15);
    circuit.addGate(dd::Xmat, 8_pc, 16);
    circuit.addGate(dd::Ymat, 11_pc, 10);
    circuit.addGate(dd::Xmat, 16);
    circuit.addGate(dd::Zmat, 13_pc, 2);
    circuit.addGate(dd::Xmat, 7);
    circuit.addGate(dd::Zmat, 9_pc, 2);
    circuit.addGate(dd::Xmat, 6_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 5);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Zmat, 14);
    circuit.addGate(dd::Zmat, 10_pc, 15);
    circuit.addGate(dd::Smat, 6);
    circuit.addGate(dd::Xmat, 6_pc, 12);
    circuit.addGate(dd::Zmat, 4_pc, 12);
    circuit.addGate(dd::Ymat, 5);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 13);
    circuit.addGate(dd::Zmat, 3_pc, 14);
    circuit.addGate(dd::Zmat, 11_pc, 7);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Xmat, 8);
    circuit.addGate(dd::Ymat, 12_pc, 2);
    circuit.addGate(dd::Zmat, 7_pc, 2);
    circuit.addGate(dd::Ymat, 3_pc, 1);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Ymat, 9);
    circuit.addGate(dd::Xmat, 8);
    circuit.addGate(dd::Ymat, 8_pc, 2);
    circuit.addGate(dd::Ymat, 15_pc, 10);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 18 qubis, containing 54 Clifford gates.
TEST(LimTest, generatedCircuit_9) {
    dd::QuantumCircuit circuit(18);

    circuit.addGate(dd::Xmat, 11_pc, 2);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Ymat, 6_pc, 11);
    circuit.addGate(dd::Xmat, 16_pc, 6);
    circuit.addGate(dd::Ymat, 11_pc, 15);
    circuit.addGate(dd::Xmat, 4_pc, 8);
    circuit.addGate(dd::Hmat, 10);
    circuit.addGate(dd::Zmat, 9);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 15);
    circuit.addGate(dd::Zmat, 6_pc, 4);
    circuit.addGate(dd::Zmat, 11);
    circuit.addGate(dd::Zmat, 0_pc, 10);
    circuit.addGate(dd::Xmat, 7_pc, 10);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 10);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 10);
    circuit.addGate(dd::Hmat, 17);
    circuit.addGate(dd::Smat, 15);
    circuit.addGate(dd::Ymat, 11_pc, 8);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::Hmat, 6);
    circuit.addGate(dd::Ymat, 5_pc, 11);
    circuit.addGate(dd::Hmat, 11);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Zmat, 13_pc, 6);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 9_pc, 7);
    circuit.addGate(dd::Xmat, 7);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 14);
    circuit.addGate(dd::Smat, 9);
    circuit.addGate(dd::Hmat, 7);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Zmat, 8);
    circuit.addGate(dd::Xmat, 6);
    circuit.addGate(dd::Zmat, 15_pc, 0);
    circuit.addGate(dd::Smat, 8);
    circuit.addGate(dd::Xmat, 8);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 11);
    circuit.addGate(dd::Zmat, 13_pc, 0);
    circuit.addGate(dd::Zmat, 10);
    circuit.addGate(dd::Zmat, 9_pc, 13);
    circuit.addGate(dd::Zmat, 17_pc, 7);
    circuit.addGate(dd::Xmat, 7);
    circuit.addGate(dd::Ymat, 15);
    circuit.addGate(dd::Xmat, 3_pc, 8);
    circuit.addGate(dd::Xmat, 9_pc, 0);
    circuit.addGate(dd::Xmat, 17_pc, 14);

    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}
//
//// Randomly generated circuit on 19 qubis, containing 57 Clifford gates.
//TEST(LimTest, generatedCircuit_10) {
//    dd::QuantumCircuit circuit(19);
//
//    circuit.addGate(dd::Zmat, 18_pc, 0);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Xmat, 3_pc, 1);
//    circuit.addGate(dd::Zmat, 8_pc, 7);
//    circuit.addGate(dd::Ymat, 11_pc, 12);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Zmat, 2_pc, 16);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Ymat, 10_pc, 11);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Zmat, 1_pc, 9);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Xmat, 5_pc, 10);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Ymat, 16_pc, 2);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Xmat, 6_pc, 17);
//    circuit.addGate(dd::Ymat, 7_pc, 0);
//    circuit.addGate(dd::Zmat, 6_pc, 8);
//    circuit.addGate(dd::Zmat, 1_pc, 15);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Zmat, 13_pc, 17);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Ymat, 13_pc, 12);
//    circuit.addGate(dd::Xmat, 0_pc, 2);
//    circuit.addGate(dd::Hmat, 18);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Ymat, 14_pc, 3);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Ymat, 11_pc, 2);
//    circuit.addGate(dd::Xmat, 8_pc, 15);
//    circuit.addGate(dd::Xmat, 9_pc, 2);
//    circuit.addGate(dd::Xmat, 1_pc, 16);
//    circuit.addGate(dd::Xmat, 17_pc, 3);
//    circuit.addGate(dd::Ymat, 6_pc, 15);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Xmat, 1_pc, 17);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Zmat, 3_pc, 13);
//    circuit.addGate(dd::Zmat, 14_pc, 3);
//    circuit.addGate(dd::Zmat, 0_pc, 3);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Xmat, 6_pc, 0);
//    circuit.addGate(dd::Xmat, 0_pc, 6);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Xmat, 6_pc, 3);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Zmat, 8_pc, 3);
//    circuit.addGate(dd::Ymat, 3_pc, 17);
//    circuit.addGate(dd::Xmat, 4_pc, 9);
//    circuit.addGate(dd::Hmat, 12);
//
//    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 20 qubis, containing 60 Clifford gates.
//TEST(LimTest, generatedCircuit_11) {
//    dd::QuantumCircuit circuit(20);
//
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Zmat, 10_pc, 2);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Xmat, 11_pc, 5);
//    circuit.addGate(dd::Ymat, 1_pc, 12);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Xmat, 6_pc, 2);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Xmat, 19_pc, 5);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Xmat, 14_pc, 13);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Xmat, 8_pc, 10);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Ymat, 7_pc, 5);
//    circuit.addGate(dd::Ymat, 9_pc, 8);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Hmat, 3);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Xmat, 13_pc, 7);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Zmat, 19_pc, 8);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Xmat, 3_pc, 10);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Zmat, 9_pc, 2);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Xmat, 6_pc, 12);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Zmat, 1_pc, 17);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Xmat, 19_pc, 6);
//    circuit.addGate(dd::Xmat, 6_pc, 17);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Zmat, 4_pc, 14);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Zmat, 11_pc, 4);
//    circuit.addGate(dd::Ymat, 19_pc, 13);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Smat, 4);
//
//    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 21 qubis, containing 63 Clifford gates.
//TEST(LimTest, generatedCircuit_12) {
//    dd::QuantumCircuit circuit(21);
//
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Zmat, 20_pc, 17);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Zmat, 14_pc, 13);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Zmat, 6_pc, 8);
//    circuit.addGate(dd::Xmat, 18_pc, 4);
//    circuit.addGate(dd::Xmat, 5_pc, 3);
//    circuit.addGate(dd::Zmat, 20_pc, 16);
//    circuit.addGate(dd::Ymat, 0_pc, 15);
//    circuit.addGate(dd::Zmat, 5_pc, 19);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Ymat, 2_pc, 1);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Ymat, 7_pc, 6);
//    circuit.addGate(dd::Xmat, 20_pc, 16);
//    circuit.addGate(dd::Zmat, 10_pc, 0);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 4_pc, 8);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Zmat, 1_pc, 15);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Xmat, 16_pc, 6);
//    circuit.addGate(dd::Ymat, 0_pc, 8);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Xmat, 15_pc, 3);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Xmat, 10_pc, 6);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Zmat, 10_pc, 8);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Zmat, 17_pc, 19);
//    circuit.addGate(dd::Zmat, 6_pc, 0);
//    circuit.addGate(dd::Ymat, 10);
//    circuit.addGate(dd::Zmat, 18_pc, 15);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Zmat, 1_pc, 17);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Zmat, 13_pc, 17);
//    circuit.addGate(dd::Xmat, 15_pc, 11);
//    circuit.addGate(dd::Ymat, 0_pc, 15);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Xmat, 8_pc, 12);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 22 qubis, containing 66 Clifford gates.
//TEST(LimTest, generatedCircuit_13) {
//    dd::QuantumCircuit circuit(22);
//
//    circuit.addGate(dd::Ymat, 10_pc, 16);
//    circuit.addGate(dd::Xmat, 4_pc, 13);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Ymat, 13_pc, 11);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Zmat, 2_pc, 19);
//    circuit.addGate(dd::Ymat, 9_pc, 4);
//    circuit.addGate(dd::Ymat, 0_pc, 4);
//    circuit.addGate(dd::Ymat, 10);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Ymat, 7_pc, 15);
//    circuit.addGate(dd::Ymat, 9_pc, 8);
//    circuit.addGate(dd::Ymat, 11_pc, 5);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Xmat, 7_pc, 21);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Ymat, 9_pc, 15);
//    circuit.addGate(dd::Ymat, 0_pc, 20);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Ymat, 20_pc, 12);
//    circuit.addGate(dd::Ymat, 18_pc, 5);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Ymat, 13_pc, 2);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Zmat, 13_pc, 8);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Ymat, 18_pc, 20);
//    circuit.addGate(dd::Xmat, 16_pc, 10);
//    circuit.addGate(dd::Xmat, 21_pc, 0);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Xmat, 18_pc, 9);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Zmat, 18_pc, 7);
//    circuit.addGate(dd::Xmat, 10_pc, 18);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Zmat, 5_pc, 4);
//    circuit.addGate(dd::Ymat, 1_pc, 2);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Zmat, 5_pc, 4);
//    circuit.addGate(dd::Xmat, 11_pc, 6);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Zmat, 3_pc, 5);
//    circuit.addGate(dd::Zmat, 5);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 16_pc, 17);
//    circuit.addGate(dd::Zmat, 0_pc, 6);
//    circuit.addGate(dd::Ymat, 14_pc, 18);
//    circuit.addGate(dd::Zmat, 11_pc, 12);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Ymat, 5_pc, 7);
//    circuit.addGate(dd::Xmat, 15_pc, 7);
//    circuit.addGate(dd::Ymat, 11_pc, 7);
//
//    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 23 qubis, containing 69 Clifford gates.
//TEST(LimTest, generatedCircuit_14) {
//    dd::QuantumCircuit circuit(23);
//
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Xmat, 9_pc, 6);
//    circuit.addGate(dd::Ymat, 12_pc, 11);
//    circuit.addGate(dd::Zmat, 10_pc, 16);
//    circuit.addGate(dd::Xmat, 20_pc, 11);
//    circuit.addGate(dd::Zmat, 17);
//    circuit.addGate(dd::Xmat, 9_pc, 4);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Ymat, 0_pc, 7);
//    circuit.addGate(dd::Ymat, 11);
//    circuit.addGate(dd::Xmat, 9_pc, 16);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Zmat, 6_pc, 18);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Ymat, 20_pc, 2);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Xmat, 7_pc, 21);
//    circuit.addGate(dd::Xmat, 1_pc, 11);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Ymat, 12_pc, 20);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Zmat, 5_pc, 9);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Zmat, 17_pc, 22);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Xmat, 4_pc, 18);
//    circuit.addGate(dd::Zmat, 0_pc, 18);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Zmat, 10_pc, 5);
//    circuit.addGate(dd::Xmat, 12_pc, 9);
//    circuit.addGate(dd::Xmat, 20_pc, 18);
//    circuit.addGate(dd::Zmat, 11_pc, 14);
//    circuit.addGate(dd::Ymat, 7_pc, 1);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Xmat, 8_pc, 22);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Zmat, 1_pc, 4);
//    circuit.addGate(dd::Zmat, 22_pc, 15);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Zmat, 7_pc, 10);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Zmat, 12_pc, 3);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Ymat, 21_pc, 6);
//    circuit.addGate(dd::Xmat, 10_pc, 17);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Xmat, 3_pc, 22);
//    circuit.addGate(dd::Zmat, 13_pc, 8);
//    circuit.addGate(dd::Ymat, 17_pc, 16);
//    circuit.addGate(dd::Xmat, 11_pc, 5);
//    circuit.addGate(dd::Smat, 10);
//
//    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 24 qubis, containing 72 Clifford gates.
//TEST(LimTest, generatedCircuit_15) {
//    dd::QuantumCircuit circuit(24);
//
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Xmat, 10_pc, 17);
//    circuit.addGate(dd::Zmat, 2_pc, 23);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Ymat, 9_pc, 15);
//    circuit.addGate(dd::Zmat, 7_pc, 20);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Zmat, 17_pc, 6);
//    circuit.addGate(dd::Ymat, 0_pc, 20);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Zmat, 13_pc, 6);
//    circuit.addGate(dd::Xmat, 5_pc, 9);
//    circuit.addGate(dd::Xmat, 14_pc, 7);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Ymat, 12_pc, 9);
//    circuit.addGate(dd::Xmat, 18_pc, 9);
//    circuit.addGate(dd::Xmat, 5_pc, 20);
//    circuit.addGate(dd::Xmat, 10_pc, 20);
//    circuit.addGate(dd::Xmat, 3_pc, 1);
//    circuit.addGate(dd::Ymat, 10_pc, 15);
//    circuit.addGate(dd::Ymat, 4_pc, 14);
//    circuit.addGate(dd::Ymat, 19_pc, 10);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Xmat, 18_pc, 23);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Xmat, 19_pc, 15);
//    circuit.addGate(dd::Ymat, 6_pc, 3);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Zmat, 11_pc, 22);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Ymat, 23_pc, 15);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 14_pc, 6);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 18_pc, 15);
//    circuit.addGate(dd::Ymat, 7_pc, 13);
//    circuit.addGate(dd::Xmat, 1_pc, 17);
//    circuit.addGate(dd::Ymat, 11);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Ymat, 20_pc, 7);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Xmat, 14_pc, 23);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Ymat, 4_pc, 2);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Ymat, 7_pc, 16);
//    circuit.addGate(dd::Ymat, 12_pc, 9);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 20_pc, 15);
//    circuit.addGate(dd::Xmat, 18_pc, 19);
//    circuit.addGate(dd::Ymat, 5_pc, 23);
//
//    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//TEST(LimTest, singleHadamard) {
//    dd::QubitCount numQubits = 24;
//    dd::QubitCount target    = 23;
//    auto           dd        = std::make_unique<dd::Package<>>(numQubits, dd::LIMDD_group::Pauli_group, false);
//
//    dd::vEdge state  = dd->makeZeroState(numQubits);
//    auto      h_gate = dd->makeGateDD(dd::Hmat, numQubits, target);
//
//    std::cout << "Executing circuit with n = " << numQubits << " qubits. Hadamard applied to gate " << target << std::endl;
//    std::cout << "Exporting state 0 to svg." << std::endl;
//    export2Dot(state, "state0.dot", true, true, true, false, true, false);
//
//    std::cout << "Applying gate 1." << std::endl;
//    state = dd->multiply(h_gate, state);
//}
//
//TEST(LimTest, twoHadamardGates) {
//    dd::QubitCount numQubits = 24;
//    dd::QubitCount target    = 23;
//    dd::QubitCount target2   = 15;
//    auto           dd        = std::make_unique<dd::Package<>>(numQubits, dd::LIMDD_group::Pauli_group, false);
//
//    dd::vEdge state  = dd->makeZeroState(numQubits);
//    auto      h_gate = dd->makeGateDD(dd::Hmat, numQubits, target);
//
//    std::cout << "Executing circuit with n = " << (int)numQubits << " qubits. Hadamard applied to gate " << (int)target << std::endl;
//
//    std::cout << "Applying gate 1." << std::endl;
//    state = dd->multiply(h_gate, state);
//
//    auto h_gate2 = dd->makeGateDD(dd::Hmat, numQubits, target2);
//    std::cout << "Applying gate 2." << std::endl;
//    state = dd->multiply(h_gate2, state);
//}
//
//// Randomly generated circuit on 25 qubis, containing 75 Clifford gates.
//TEST(LimTest, generatedCircuit_16) {
//    dd::QuantumCircuit circuit(25);
//
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Xmat, 18_pc, 19);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Ymat, 0_pc, 24);
//    circuit.addGate(dd::Zmat, 20_pc, 11);
//    circuit.addGate(dd::Ymat, 22_pc, 6);
//    circuit.addGate(dd::Xmat, 5_pc, 18);
//    circuit.addGate(dd::Ymat, 22_pc, 19);
//    circuit.addGate(dd::Xmat, 0_pc, 8);
//    circuit.addGate(dd::Ymat, 22_pc, 1);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Ymat, 20_pc, 22);
//    circuit.addGate(dd::Ymat, 21_pc, 18);
//    circuit.addGate(dd::Ymat, 24_pc, 5);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Ymat, 14_pc, 23);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Xmat, 5_pc, 4);
//    circuit.addGate(dd::Xmat, 0_pc, 21);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Xmat, 20_pc, 9);
//    circuit.addGate(dd::Xmat, 1_pc, 24);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Zmat, 12_pc, 9);
//    circuit.addGate(dd::Zmat, 15_pc, 18);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Xmat, 23_pc, 7);
//    circuit.addGate(dd::Zmat, 22_pc, 13);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Xmat, 2_pc, 19);
//    circuit.addGate(dd::Xmat, 9_pc, 18);
//    circuit.addGate(dd::Xmat, 18_pc, 6);
//    circuit.addGate(dd::Ymat, 3_pc, 14);
//    circuit.addGate(dd::Ymat, 11_pc, 9);
//    circuit.addGate(dd::Xmat, 15_pc, 5);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Xmat, 12_pc, 13);
//    circuit.addGate(dd::Ymat, 16_pc, 20);
//    circuit.addGate(dd::Xmat, 5_pc, 9);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Zmat, 12_pc, 0);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Zmat, 17_pc, 6);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Ymat, 11_pc, 21);
//    circuit.addGate(dd::Hmat, 3);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Ymat, 15_pc, 9);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Zmat, 11_pc, 7);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Zmat, 4_pc, 19);
//    circuit.addGate(dd::Zmat, 9_pc, 8);
//    circuit.addGate(dd::Xmat, 3_pc, 2);
//    circuit.addGate(dd::Xmat, 13_pc, 2);
//
//    //     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 26 qubis, containing 78 Clifford gates.
//TEST(LimTest, generatedCircuit_17) {
//    dd::QuantumCircuit circuit(26);
//
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Ymat, 25_pc, 15);
//    circuit.addGate(dd::Zmat, 21_pc, 24);
//    circuit.addGate(dd::Xmat, 25_pc, 3);
//    circuit.addGate(dd::Zmat, 24_pc, 18);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Ymat, 19_pc, 16);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Xmat, 21_pc, 18);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Ymat, 6_pc, 16);
//    circuit.addGate(dd::Xmat, 21_pc, 22);
//    circuit.addGate(dd::Xmat, 17_pc, 22);
//    circuit.addGate(dd::Ymat, 14_pc, 25);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Zmat, 3_pc, 15);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 22_pc, 0);
//    circuit.addGate(dd::Ymat, 6_pc, 13);
//    circuit.addGate(dd::Xmat, 9_pc, 16);
//    circuit.addGate(dd::Xmat, 7_pc, 3);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Ymat, 6_pc, 22);
//    circuit.addGate(dd::Zmat, 25_pc, 20);
//    circuit.addGate(dd::Xmat, 24_pc, 16);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Xmat, 18_pc, 3);
//    circuit.addGate(dd::Zmat, 17_pc, 0);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Ymat, 11_pc, 24);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Xmat, 3_pc, 9);
//    circuit.addGate(dd::Zmat, 11_pc, 25);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Ymat, 0_pc, 16);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Ymat, 19_pc, 25);
//    circuit.addGate(dd::Xmat, 3_pc, 13);
//    circuit.addGate(dd::Ymat, 16_pc, 0);
//    circuit.addGate(dd::Ymat, 10_pc, 2);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Zmat, 21_pc, 7);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Ymat, 19_pc, 25);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Xmat, 12_pc, 16);
//    circuit.addGate(dd::Zmat, 18_pc, 12);
//    circuit.addGate(dd::Xmat, 17_pc, 11);
//    circuit.addGate(dd::Xmat, 20_pc, 8);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Xmat, 23_pc, 2);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Zmat, 18_pc, 15);
//    circuit.addGate(dd::Zmat, 8_pc, 12);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Zmat, 9_pc, 3);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Xmat, 2_pc, 7);
//    circuit.addGate(dd::Ymat, 0_pc, 23);
//    circuit.addGate(dd::Zmat, 7_pc, 3);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Xmat, 20_pc, 24);
//    circuit.addGate(dd::Ymat, 1_pc, 14);
//    circuit.addGate(dd::Zmat, 8);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 27 qubis, containing 81 Clifford gates.
//TEST(LimTest, generatedCircuit_18) {
//    dd::QuantumCircuit circuit(27);
//
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Zmat, 5_pc, 22);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Xmat, 0_pc, 23);
//    circuit.addGate(dd::Ymat, 23_pc, 14);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Ymat, 26_pc, 10);
//    circuit.addGate(dd::Zmat, 8_pc, 26);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Zmat, 24_pc, 7);
//    circuit.addGate(dd::Xmat, 18_pc, 17);
//    circuit.addGate(dd::Xmat, 20_pc, 0);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Ymat, 2_pc, 1);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Xmat, 4_pc, 22);
//    circuit.addGate(dd::Xmat, 25_pc, 15);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Zmat, 15_pc, 26);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Ymat, 5_pc, 6);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Zmat, 6_pc, 19);
//    circuit.addGate(dd::Ymat, 7_pc, 24);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Ymat, 18_pc, 9);
//    circuit.addGate(dd::Xmat, 11_pc, 13);
//    circuit.addGate(dd::Zmat, 0_pc, 10);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Xmat, 18_pc, 22);
//    circuit.addGate(dd::Zmat, 4_pc, 5);
//    circuit.addGate(dd::Zmat, 4_pc, 12);
//    circuit.addGate(dd::Ymat, 26_pc, 18);
//    circuit.addGate(dd::Ymat, 9_pc, 22);
//    circuit.addGate(dd::Ymat, 23_pc, 20);
//    circuit.addGate(dd::Zmat, 20_pc, 23);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Zmat, 23_pc, 3);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Xmat, 13_pc, 10);
//    circuit.addGate(dd::Xmat, 0_pc, 3);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Ymat, 12_pc, 10);
//    circuit.addGate(dd::Ymat, 21_pc, 11);
//    circuit.addGate(dd::Xmat, 25_pc, 3);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Zmat, 23_pc, 22);
//    circuit.addGate(dd::Ymat, 16_pc, 10);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 3_pc, 23);
//    circuit.addGate(dd::Zmat, 11_pc, 0);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Xmat, 18_pc, 23);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Xmat, 16_pc, 24);
//    circuit.addGate(dd::Ymat, 2_pc, 4);
//    circuit.addGate(dd::Ymat, 0_pc, 15);
//    circuit.addGate(dd::Ymat, 5_pc, 10);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Xmat, 12_pc, 0);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Zmat, 24_pc, 20);
//    circuit.addGate(dd::Ymat, 20_pc, 26);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Xmat, 17_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 28 qubis, containing 84 Clifford gates.
//TEST(LimTest, generatedCircuit_19) {
//    dd::QuantumCircuit circuit(28);
//
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Zmat, 14_pc, 8);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Ymat, 9_pc, 2);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 10);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 7_pc, 0);
//    circuit.addGate(dd::Xmat, 7_pc, 11);
//    circuit.addGate(dd::Zmat, 9_pc, 25);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Ymat, 21_pc, 25);
//    circuit.addGate(dd::Ymat, 19_pc, 23);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Ymat, 21_pc, 19);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Xmat, 13_pc, 8);
//    circuit.addGate(dd::Ymat, 4_pc, 6);
//    circuit.addGate(dd::Zmat, 16_pc, 14);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Xmat, 9_pc, 26);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Xmat, 24_pc, 19);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Ymat, 16_pc, 10);
//    circuit.addGate(dd::Ymat, 0_pc, 13);
//    circuit.addGate(dd::Ymat, 27_pc, 22);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Zmat, 5_pc, 24);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Xmat, 15_pc, 4);
//    circuit.addGate(dd::Zmat, 14);
//    circuit.addGate(dd::Xmat, 14_pc, 2);
//    circuit.addGate(dd::Zmat, 14_pc, 27);
//    circuit.addGate(dd::Zmat, 6_pc, 0);
//    circuit.addGate(dd::Xmat, 8_pc, 21);
//    circuit.addGate(dd::Xmat, 7_pc, 2);
//    circuit.addGate(dd::Xmat, 7_pc, 24);
//    circuit.addGate(dd::Zmat, 11_pc, 27);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Ymat, 11);
//    circuit.addGate(dd::Ymat, 26);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Ymat, 22_pc, 10);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Xmat, 11_pc, 24);
//    circuit.addGate(dd::Xmat, 3_pc, 0);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Xmat, 22_pc, 20);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Zmat, 8_pc, 6);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Xmat, 5_pc, 0);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Xmat, 3_pc, 24);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Ymat, 13_pc, 9);
//    circuit.addGate(dd::Ymat, 7_pc, 8);
//    circuit.addGate(dd::Zmat, 25_pc, 1);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Zmat, 19_pc, 3);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Xmat, 20_pc, 26);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Xmat, 26_pc, 11);
//    circuit.addGate(dd::Zmat, 8_pc, 2);
//    circuit.addGate(dd::Zmat, 24_pc, 27);
//    circuit.addGate(dd::Zmat, 21_pc, 27);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//    //    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 29 qubis, containing 87 Clifford gates.
//TEST(LimTest, generatedCircuit_20) {
//    dd::QuantumCircuit circuit(29);
//
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Zmat, 27_pc, 9);
//    circuit.addGate(dd::Xmat, 1_pc, 12);
//    circuit.addGate(dd::Ymat, 9_pc, 18);
//    circuit.addGate(dd::Ymat, 8_pc, 3);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Ymat, 22_pc, 2);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Ymat, 5_pc, 12);
//    circuit.addGate(dd::Zmat, 14_pc, 8);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Zmat, 26_pc, 3);
//    circuit.addGate(dd::Xmat, 26_pc, 18);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Ymat, 4_pc, 14);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Xmat, 20_pc, 1);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Ymat, 8_pc, 5);
//    circuit.addGate(dd::Ymat, 12_pc, 14);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Xmat, 19_pc, 4);
//    circuit.addGate(dd::Xmat, 1_pc, 18);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Ymat, 5_pc, 2);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Xmat, 15_pc, 8);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Zmat, 21_pc, 20);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Ymat, 22_pc, 18);
//    circuit.addGate(dd::Xmat, 26_pc, 7);
//    circuit.addGate(dd::Zmat, 26_pc, 5);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Ymat, 8_pc, 27);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Ymat, 7_pc, 23);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Ymat, 24);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Zmat, 20_pc, 16);
//    circuit.addGate(dd::Xmat, 17_pc, 24);
//    circuit.addGate(dd::Ymat, 6_pc, 25);
//    circuit.addGate(dd::Xmat, 26);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Xmat, 26_pc, 14);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Ymat, 20_pc, 28);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Ymat, 28_pc, 14);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Ymat, 3_pc, 9);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Ymat, 17_pc, 14);
//    circuit.addGate(dd::Zmat, 15_pc, 9);
//    circuit.addGate(dd::Ymat, 12_pc, 23);
//    circuit.addGate(dd::Ymat, 26_pc, 4);
//    circuit.addGate(dd::Ymat, 26_pc, 0);
//    circuit.addGate(dd::Zmat, 19_pc, 23);
//    circuit.addGate(dd::Zmat, 15_pc, 2);
//    circuit.addGate(dd::Xmat, 14_pc, 16);
//    circuit.addGate(dd::Ymat, 22_pc, 9);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}

//// Randomly generated circuit on 30 qubis, containing 90 Clifford gates.
//TEST(LimTest, generatedCircuit_21) {
//    dd::QuantumCircuit circuit(30);
//
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Zmat, 13_pc, 22);
//    circuit.addGate(dd::Zmat, 10_pc, 11);
//    circuit.addGate(dd::Zmat, 12_pc, 26);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Xmat, 27_pc, 9);
//    circuit.addGate(dd::Xmat, 22_pc, 17);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Zmat, 22_pc, 1);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Zmat, 1_pc, 20);
//    circuit.addGate(dd::Xmat, 14_pc, 6);
//    circuit.addGate(dd::Xmat, 23_pc, 13);
//    circuit.addGate(dd::Xmat, 22_pc, 9);
//    circuit.addGate(dd::Ymat, 15_pc, 1);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Ymat, 20_pc, 11);
//    circuit.addGate(dd::Ymat, 25_pc, 11);
//    circuit.addGate(dd::Zmat, 26_pc, 20);
//    circuit.addGate(dd::Xmat, 12_pc, 27);
//    circuit.addGate(dd::Xmat, 10_pc, 7);
//    circuit.addGate(dd::Xmat, 23_pc, 16);
//    circuit.addGate(dd::Xmat, 18_pc, 6);
//    circuit.addGate(dd::Zmat, 26_pc, 20);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Ymat, 19_pc, 2);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Zmat, 24_pc, 28);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Zmat, 6_pc, 27);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Ymat, 11_pc, 19);
//    circuit.addGate(dd::Xmat, 16_pc, 12);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Zmat, 28_pc, 11);
//    circuit.addGate(dd::Xmat, 26_pc, 20);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 28_pc, 21);
//    circuit.addGate(dd::Xmat, 8_pc, 28);
//    circuit.addGate(dd::Ymat, 17_pc, 9);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Ymat, 10_pc, 2);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Ymat, 21_pc, 20);
//    circuit.addGate(dd::Xmat, 28_pc, 6);
//    circuit.addGate(dd::Xmat, 15_pc, 7);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Xmat, 7_pc, 16);
//    circuit.addGate(dd::Xmat, 12_pc, 3);
//    circuit.addGate(dd::Ymat, 6_pc, 15);
//    circuit.addGate(dd::Zmat, 29_pc, 20);
//    circuit.addGate(dd::Zmat, 11_pc, 27);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Ymat, 11_pc, 16);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Xmat, 26_pc, 20);
//    circuit.addGate(dd::Ymat, 19_pc, 1);
//    circuit.addGate(dd::Ymat, 4_pc, 10);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Zmat, 27_pc, 20);
//    circuit.addGate(dd::Xmat, 7_pc, 13);
//    circuit.addGate(dd::Xmat, 26_pc, 13);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Xmat, 22_pc, 23);
//
//     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 31 qubis, containing 93 Clifford gates.
//TEST(LimTest, generatedCircuit_22) {
//    dd::QuantumCircuit circuit(31);
//
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Zmat, 22_pc, 16);
//    circuit.addGate(dd::Xmat, 25_pc, 1);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Zmat, 27_pc, 28);
//    circuit.addGate(dd::Ymat, 1_pc, 11);
//    circuit.addGate(dd::Zmat, 10_pc, 11);
//    circuit.addGate(dd::Zmat, 4_pc, 25);
//    circuit.addGate(dd::Zmat, 16);
//    circuit.addGate(dd::Zmat, 1_pc, 25);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Xmat, 28_pc, 12);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Ymat, 7_pc, 8);
//    circuit.addGate(dd::Xmat, 19_pc, 23);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Ymat, 1_pc, 0);
//    circuit.addGate(dd::Ymat, 17_pc, 12);
//    circuit.addGate(dd::Xmat, 22_pc, 8);
//    circuit.addGate(dd::Zmat, 14_pc, 6);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Xmat, 30_pc, 19);
//    circuit.addGate(dd::Ymat, 8_pc, 2);
//    circuit.addGate(dd::Xmat, 21_pc, 5);
//    circuit.addGate(dd::Ymat, 6_pc, 13);
//    circuit.addGate(dd::Ymat, 28_pc, 1);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Zmat, 22_pc, 0);
//    circuit.addGate(dd::Zmat, 15_pc, 29);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Xmat, 17_pc, 13);
//    circuit.addGate(dd::Zmat, 22_pc, 11);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Ymat, 8_pc, 12);
//    circuit.addGate(dd::Xmat, 23_pc, 30);
//    circuit.addGate(dd::Zmat, 19_pc, 9);
//    circuit.addGate(dd::Ymat, 24);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Xmat, 16_pc, 14);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Ymat, 1_pc, 23);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Ymat, 25_pc, 27);
//    circuit.addGate(dd::Zmat, 23_pc, 25);
//    circuit.addGate(dd::Ymat, 29_pc, 5);
//    circuit.addGate(dd::Zmat, 3_pc, 5);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Zmat, 2_pc, 18);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Zmat, 18_pc, 19);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Xmat, 10_pc, 16);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Zmat, 2_pc, 10);
//    circuit.addGate(dd::Ymat, 12_pc, 29);
//    circuit.addGate(dd::Zmat, 20_pc, 2);
//    circuit.addGate(dd::Xmat, 20_pc, 0);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 24_pc, 1);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Ymat, 18_pc, 24);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Xmat, 29_pc, 26);
//    circuit.addGate(dd::Ymat, 26);
//    circuit.addGate(dd::Xmat, 13_pc, 29);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Xmat, 29_pc, 20);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Zmat, 12_pc, 16);
//    circuit.addGate(dd::Zmat, 1_pc, 29);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Zmat, 11_pc, 24);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Ymat, 10_pc, 9);
//    circuit.addGate(dd::Xmat, 15_pc, 16);
//    circuit.addGate(dd::Zmat, 28_pc, 27);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Ymat, 2);
//
//     simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 32 qubis, containing 96 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_1) {
//    dd::QuantumCircuit circuit(32);
//
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Xmat, 11_pc, 21);
//    circuit.addGate(dd::Zmat, 18_pc, 29);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Zmat, 2_pc, 18);
//    circuit.addGate(dd::Zmat, 2_pc, 20);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Zmat, 5_pc, 31);
//    circuit.addGate(dd::Zmat, 25_pc, 11);
//    circuit.addGate(dd::Zmat, 31_pc, 9);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Ymat, 3_pc, 27);
//    circuit.addGate(dd::Xmat, 30_pc, 13);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Xmat, 2_pc, 1);
//    circuit.addGate(dd::Xmat, 18_pc, 26);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Zmat, 18_pc, 29);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Zmat, 31_pc, 6);
//    circuit.addGate(dd::Xmat, 19_pc, 10);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Ymat, 6_pc, 14);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Ymat, 27_pc, 2);
//    circuit.addGate(dd::Xmat, 31_pc, 13);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Zmat, 4_pc, 17);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Xmat, 0_pc, 28);
//    circuit.addGate(dd::Ymat, 10);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Ymat, 22_pc, 8);
//    circuit.addGate(dd::Zmat, 10_pc, 4);
//    circuit.addGate(dd::Xmat, 17_pc, 7);
//    circuit.addGate(dd::Ymat, 5_pc, 0);
//    circuit.addGate(dd::Zmat, 9_pc, 10);
//    circuit.addGate(dd::Zmat, 14_pc, 17);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Xmat, 11_pc, 17);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Zmat, 2_pc, 3);
//    circuit.addGate(dd::Ymat, 24_pc, 20);
//    circuit.addGate(dd::Zmat, 7_pc, 5);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Zmat, 19_pc, 26);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Zmat, 7_pc, 26);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Xmat, 21_pc, 24);
//    circuit.addGate(dd::Zmat, 24_pc, 27);
//    circuit.addGate(dd::Xmat, 5_pc, 10);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Xmat, 6_pc, 29);
//    circuit.addGate(dd::Zmat, 26_pc, 6);
//    circuit.addGate(dd::Xmat, 0_pc, 25);
//    circuit.addGate(dd::Zmat, 0_pc, 18);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Ymat, 28_pc, 11);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 22_pc, 24);
//    circuit.addGate(dd::Smat, 31);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Zmat, 0_pc, 20);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Ymat, 23_pc, 3);
//    circuit.addGate(dd::Zmat, 4_pc, 11);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Xmat, 21_pc, 26);
//    circuit.addGate(dd::Ymat, 15_pc, 11);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Ymat, 2_pc, 1);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Zmat, 2_pc, 22);
//    circuit.addGate(dd::Zmat, 6_pc, 7);
//    circuit.addGate(dd::Hmat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 33 qubis, containing 99 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_2) {
//    dd::QuantumCircuit circuit(33);
//
//    circuit.addGate(dd::Ymat, 1_pc, 3);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Hmat, 3);
//    circuit.addGate(dd::Zmat, 31_pc, 2);
//    circuit.addGate(dd::Ymat, 32_pc, 24);
//    circuit.addGate(dd::Zmat, 13_pc, 24);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Zmat, 5_pc, 2);
//    circuit.addGate(dd::Xmat, 31_pc, 30);
//    circuit.addGate(dd::Xmat, 14_pc, 5);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Zmat, 29_pc, 5);
//    circuit.addGate(dd::Xmat, 5_pc, 20);
//    circuit.addGate(dd::Xmat, 23_pc, 13);
//    circuit.addGate(dd::Zmat, 14_pc, 1);
//    circuit.addGate(dd::Ymat, 32_pc, 16);
//    circuit.addGate(dd::Ymat, 19_pc, 10);
//    circuit.addGate(dd::Xmat, 8_pc, 20);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Ymat, 31_pc, 32);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Ymat, 14_pc, 2);
//    circuit.addGate(dd::Ymat, 18_pc, 25);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Zmat, 8_pc, 25);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Xmat, 16_pc, 19);
//    circuit.addGate(dd::Xmat, 32_pc, 29);
//    circuit.addGate(dd::Zmat, 32_pc, 29);
//    circuit.addGate(dd::Xmat, 21_pc, 15);
//    circuit.addGate(dd::Ymat, 20_pc, 10);
//    circuit.addGate(dd::Zmat, 22_pc, 21);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Zmat, 2_pc, 0);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Ymat, 25_pc, 14);
//    circuit.addGate(dd::Ymat, 25_pc, 13);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Ymat, 24_pc, 2);
//    circuit.addGate(dd::Zmat, 21_pc, 11);
//    circuit.addGate(dd::Xmat, 8_pc, 9);
//    circuit.addGate(dd::Zmat, 7_pc, 11);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Zmat, 15_pc, 16);
//    circuit.addGate(dd::Ymat, 16_pc, 7);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Ymat, 12_pc, 30);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Ymat, 16_pc, 30);
//    circuit.addGate(dd::Zmat, 9_pc, 16);
//    circuit.addGate(dd::Ymat, 28_pc, 12);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Ymat, 10_pc, 7);
//    circuit.addGate(dd::Xmat, 13_pc, 30);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Zmat, 3_pc, 12);
//    circuit.addGate(dd::Xmat, 26_pc, 5);
//    circuit.addGate(dd::Xmat, 18_pc, 7);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Zmat, 17);
//    circuit.addGate(dd::Zmat, 32_pc, 9);
//    circuit.addGate(dd::Xmat, 15_pc, 32);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Xmat, 3_pc, 22);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Xmat, 26_pc, 6);
//    circuit.addGate(dd::Xmat, 2_pc, 28);
//    circuit.addGate(dd::Xmat, 6_pc, 24);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Xmat, 16_pc, 2);
//    circuit.addGate(dd::Ymat, 19_pc, 16);
//    circuit.addGate(dd::Zmat, 26_pc, 18);
//    circuit.addGate(dd::Xmat, 7_pc, 15);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Xmat, 5_pc, 28);
//    circuit.addGate(dd::Zmat, 32_pc, 24);
//    circuit.addGate(dd::Xmat, 16_pc, 0);
//    circuit.addGate(dd::Ymat, 6_pc, 27);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Zmat, 16_pc, 18);
//    circuit.addGate(dd::Ymat, 30_pc, 19);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Zmat, 28_pc, 9);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 34 qubis, containing 102 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_3) {
//    dd::QuantumCircuit circuit(34);
//
//    circuit.addGate(dd::Ymat, 9_pc, 13);
//    circuit.addGate(dd::Zmat, 25_pc, 10);
//    circuit.addGate(dd::Zmat, 23_pc, 0);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Xmat, 33);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Smat, 31);
//    circuit.addGate(dd::Xmat, 20_pc, 24);
//    circuit.addGate(dd::Ymat, 13_pc, 31);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Xmat, 14_pc, 13);
//    circuit.addGate(dd::Zmat, 14_pc, 10);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Zmat, 15_pc, 33);
//    circuit.addGate(dd::Zmat, 27_pc, 32);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Xmat, 13_pc, 5);
//    circuit.addGate(dd::Zmat, 2_pc, 15);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Xmat, 23_pc, 7);
//    circuit.addGate(dd::Ymat, 24_pc, 22);
//    circuit.addGate(dd::Ymat, 11_pc, 7);
//    circuit.addGate(dd::Ymat, 7_pc, 0);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Zmat, 20_pc, 16);
//    circuit.addGate(dd::Ymat, 24_pc, 3);
//    circuit.addGate(dd::Ymat, 7_pc, 20);
//    circuit.addGate(dd::Zmat, 2_pc, 17);
//    circuit.addGate(dd::Xmat, 15_pc, 22);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Zmat, 18_pc, 21);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Ymat, 1_pc, 10);
//    circuit.addGate(dd::Zmat, 20_pc, 29);
//    circuit.addGate(dd::Ymat, 18_pc, 31);
//    circuit.addGate(dd::Zmat, 3_pc, 28);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Xmat, 11_pc, 33);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Zmat, 11_pc, 9);
//    circuit.addGate(dd::Ymat, 10_pc, 14);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Ymat, 29_pc, 6);
//    circuit.addGate(dd::Zmat, 7_pc, 33);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Xmat, 7_pc, 14);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Ymat, 32);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Ymat, 1_pc, 28);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Xmat, 8_pc, 29);
//    circuit.addGate(dd::Zmat, 22_pc, 11);
//    circuit.addGate(dd::Zmat, 26_pc, 13);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 16_pc, 29);
//    circuit.addGate(dd::Zmat, 11_pc, 20);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Zmat, 21_pc, 1);
//    circuit.addGate(dd::Ymat, 24_pc, 13);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Xmat, 33_pc, 27);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 26);
//    circuit.addGate(dd::Zmat, 3_pc, 21);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Ymat, 11_pc, 14);
//    circuit.addGate(dd::Ymat, 13_pc, 2);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Ymat, 21_pc, 10);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Ymat, 7_pc, 30);
//    circuit.addGate(dd::Xmat, 26_pc, 25);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Xmat, 16_pc, 29);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Xmat, 20_pc, 1);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Zmat, 25_pc, 6);
//    circuit.addGate(dd::Xmat, 6_pc, 16);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Zmat, 1_pc, 3);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 35 qubis, containing 105 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_4) {
//    dd::QuantumCircuit circuit(35);
//
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Hmat, 29);
//    circuit.addGate(dd::Ymat, 20_pc, 28);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Ymat, 15_pc, 0);
//    circuit.addGate(dd::Ymat, 33_pc, 29);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Ymat, 30_pc, 6);
//    circuit.addGate(dd::Zmat, 3_pc, 33);
//    circuit.addGate(dd::Ymat, 18_pc, 24);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Zmat, 17_pc, 2);
//    circuit.addGate(dd::Ymat, 8_pc, 23);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Ymat, 16_pc, 11);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Zmat, 24_pc, 34);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Zmat, 17);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Zmat, 4_pc, 19);
//    circuit.addGate(dd::Ymat, 4_pc, 6);
//    circuit.addGate(dd::Xmat, 22_pc, 0);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Ymat, 23_pc, 17);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Ymat, 12_pc, 6);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Xmat, 25_pc, 3);
//    circuit.addGate(dd::Zmat, 9_pc, 20);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Ymat, 5_pc, 33);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Xmat, 5_pc, 33);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Ymat, 33);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Ymat, 16_pc, 17);
//    circuit.addGate(dd::Ymat, 3_pc, 17);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Xmat, 28_pc, 30);
//    circuit.addGate(dd::Xmat, 12_pc, 27);
//    circuit.addGate(dd::Zmat, 21_pc, 31);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Xmat, 15_pc, 33);
//    circuit.addGate(dd::Xmat, 5_pc, 30);
//    circuit.addGate(dd::Zmat, 5);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Xmat, 10_pc, 3);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Ymat, 16_pc, 18);
//    circuit.addGate(dd::Zmat, 20_pc, 26);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Zmat, 25_pc, 17);
//    circuit.addGate(dd::Xmat, 7_pc, 12);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Zmat, 30_pc, 27);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Ymat, 9_pc, 14);
//    circuit.addGate(dd::Ymat, 5_pc, 14);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Xmat, 14_pc, 8);
//    circuit.addGate(dd::Zmat, 32_pc, 14);
//    circuit.addGate(dd::Ymat, 32_pc, 19);
//    circuit.addGate(dd::Zmat, 5_pc, 0);
//    circuit.addGate(dd::Zmat, 19_pc, 2);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Ymat, 4_pc, 6);
//    circuit.addGate(dd::Xmat, 33_pc, 26);
//    circuit.addGate(dd::Zmat, 17);
//    circuit.addGate(dd::Ymat, 27_pc, 21);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Zmat, 32_pc, 13);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Xmat, 8_pc, 23);
//    circuit.addGate(dd::Ymat, 10_pc, 0);
//    circuit.addGate(dd::Xmat, 30_pc, 3);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Xmat, 16_pc, 34);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Ymat, 14_pc, 2);
//    circuit.addGate(dd::Xmat, 21_pc, 6);
//    circuit.addGate(dd::Xmat, 31_pc, 33);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Xmat, 11_pc, 7);
//    circuit.addGate(dd::Zmat, 4_pc, 28);
//    circuit.addGate(dd::Xmat, 25_pc, 7);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Zmat, 27_pc, 15);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Ymat, 17_pc, 10);
//    circuit.addGate(dd::Ymat, 30_pc, 15);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 36 qubis, containing 108 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_5) {
//    dd::QuantumCircuit circuit(36);
//
//    circuit.addGate(dd::Xmat, 27_pc, 33);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Zmat, 0_pc, 35);
//    circuit.addGate(dd::Ymat, 12_pc, 31);
//    circuit.addGate(dd::Zmat, 27_pc, 24);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Smat, 32);
//    circuit.addGate(dd::Xmat, 20_pc, 35);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Xmat, 34_pc, 29);
//    circuit.addGate(dd::Ymat, 21_pc, 9);
//    circuit.addGate(dd::Xmat, 0_pc, 35);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Xmat, 8_pc, 20);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Zmat, 6_pc, 14);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Zmat, 17_pc, 15);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Xmat, 3_pc, 6);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Ymat, 21_pc, 11);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Ymat, 15_pc, 16);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Xmat, 22_pc, 11);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Xmat, 16_pc, 21);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Xmat, 1_pc, 5);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Zmat, 32_pc, 1);
//    circuit.addGate(dd::Zmat, 13_pc, 25);
//    circuit.addGate(dd::Xmat, 0_pc, 21);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Ymat, 30_pc, 27);
//    circuit.addGate(dd::Hmat, 3);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Zmat, 0_pc, 17);
//    circuit.addGate(dd::Xmat, 34_pc, 3);
//    circuit.addGate(dd::Xmat, 29_pc, 6);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Xmat, 20_pc, 27);
//    circuit.addGate(dd::Xmat, 30_pc, 19);
//    circuit.addGate(dd::Ymat, 0_pc, 20);
//    circuit.addGate(dd::Ymat, 9_pc, 2);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Ymat, 14_pc, 30);
//    circuit.addGate(dd::Ymat, 21_pc, 12);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Xmat, 11_pc, 5);
//    circuit.addGate(dd::Xmat, 30_pc, 33);
//    circuit.addGate(dd::Ymat, 1_pc, 31);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Zmat, 5_pc, 3);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Zmat, 4_pc, 20);
//    circuit.addGate(dd::Xmat, 22_pc, 4);
//    circuit.addGate(dd::Ymat, 31_pc, 13);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Xmat, 28_pc, 35);
//    circuit.addGate(dd::Smat, 35);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Ymat, 31_pc, 5);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Xmat, 10_pc, 16);
//    circuit.addGate(dd::Xmat, 0_pc, 2);
//    circuit.addGate(dd::Zmat, 31_pc, 20);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Zmat, 14);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Xmat, 33_pc, 20);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Ymat, 5_pc, 18);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Ymat, 18_pc, 17);
//    circuit.addGate(dd::Ymat, 15);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 37 qubis, containing 111 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_6) {
//    dd::QuantumCircuit circuit(37);
//
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Zmat, 17_pc, 22);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Ymat, 10_pc, 7);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Xmat, 28_pc, 17);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Xmat, 24_pc, 16);
//    circuit.addGate(dd::Ymat, 5_pc, 33);
//    circuit.addGate(dd::Ymat, 10_pc, 15);
//    circuit.addGate(dd::Zmat, 33_pc, 21);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Zmat, 13_pc, 32);
//    circuit.addGate(dd::Xmat, 32_pc, 0);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Ymat, 10_pc, 20);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Xmat, 35);
//    circuit.addGate(dd::Ymat, 10_pc, 28);
//    circuit.addGate(dd::Xmat, 29_pc, 15);
//    circuit.addGate(dd::Zmat, 10_pc, 31);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Xmat, 32_pc, 20);
//    circuit.addGate(dd::Hmat, 18);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Xmat, 5_pc, 30);
//    circuit.addGate(dd::Zmat, 13_pc, 23);
//    circuit.addGate(dd::Ymat, 22_pc, 35);
//    circuit.addGate(dd::Ymat, 8_pc, 26);
//    circuit.addGate(dd::Zmat, 23_pc, 2);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Zmat, 33_pc, 35);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Zmat, 8_pc, 9);
//    circuit.addGate(dd::Zmat, 22_pc, 9);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Ymat, 36_pc, 28);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Xmat, 22_pc, 32);
//    circuit.addGate(dd::Xmat, 22_pc, 15);
//    circuit.addGate(dd::Zmat, 15_pc, 22);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Ymat, 33);
//    circuit.addGate(dd::Xmat, 30_pc, 26);
//    circuit.addGate(dd::Ymat, 32_pc, 16);
//    circuit.addGate(dd::Xmat, 19_pc, 24);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Zmat, 4_pc, 17);
//    circuit.addGate(dd::Zmat, 25_pc, 4);
//    circuit.addGate(dd::Zmat, 28_pc, 2);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Zmat, 11_pc, 19);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Zmat, 23_pc, 5);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Zmat, 7_pc, 32);
//    circuit.addGate(dd::Ymat, 18_pc, 29);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Xmat, 1_pc, 0);
//    circuit.addGate(dd::Ymat, 24_pc, 0);
//    circuit.addGate(dd::Hmat, 34);
//    circuit.addGate(dd::Ymat, 35_pc, 15);
//    circuit.addGate(dd::Xmat, 33_pc, 7);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Xmat, 36_pc, 19);
//    circuit.addGate(dd::Ymat, 35_pc, 16);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Xmat, 12_pc, 22);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Ymat, 15_pc, 19);
//    circuit.addGate(dd::Ymat, 26_pc, 5);
//    circuit.addGate(dd::Xmat, 2_pc, 10);
//    circuit.addGate(dd::Zmat, 4_pc, 15);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Zmat, 32_pc, 9);
//    circuit.addGate(dd::Xmat, 14_pc, 9);
//    circuit.addGate(dd::Xmat, 33);
//    circuit.addGate(dd::Zmat, 16_pc, 19);
//    circuit.addGate(dd::Zmat, 27_pc, 21);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 12_pc, 35);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Ymat, 1_pc, 11);
//    circuit.addGate(dd::Xmat, 6_pc, 32);
//    circuit.addGate(dd::Zmat, 22_pc, 29);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Xmat, 0_pc, 35);
//    circuit.addGate(dd::Ymat, 11);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 38 qubis, containing 114 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_7) {
//    dd::QuantumCircuit circuit(38);
//
//    circuit.addGate(dd::Xmat, 30_pc, 18);
//    circuit.addGate(dd::Xmat, 33);
//    circuit.addGate(dd::Zmat, 20_pc, 23);
//    circuit.addGate(dd::Ymat, 2_pc, 28);
//    circuit.addGate(dd::Ymat, 11_pc, 8);
//    circuit.addGate(dd::Ymat, 12_pc, 34);
//    circuit.addGate(dd::Zmat, 15_pc, 26);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Xmat, 20_pc, 26);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Xmat, 29_pc, 36);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Ymat, 7_pc, 11);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Xmat, 29_pc, 28);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Xmat, 19_pc, 17);
//    circuit.addGate(dd::Zmat, 24_pc, 4);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Ymat, 35_pc, 7);
//    circuit.addGate(dd::Ymat, 27_pc, 29);
//    circuit.addGate(dd::Xmat, 32);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Xmat, 1_pc, 7);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Ymat, 33_pc, 35);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Xmat, 37_pc, 5);
//    circuit.addGate(dd::Zmat, 13_pc, 3);
//    circuit.addGate(dd::Ymat, 26_pc, 12);
//    circuit.addGate(dd::Xmat, 30_pc, 15);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Ymat, 29_pc, 31);
//    circuit.addGate(dd::Ymat, 6_pc, 12);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Zmat, 31_pc, 28);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Ymat, 33_pc, 4);
//    circuit.addGate(dd::Xmat, 6_pc, 1);
//    circuit.addGate(dd::Xmat, 9_pc, 20);
//    circuit.addGate(dd::Ymat, 28_pc, 19);
//    circuit.addGate(dd::Zmat, 3_pc, 27);
//    circuit.addGate(dd::Ymat, 37);
//    circuit.addGate(dd::Xmat, 30_pc, 16);
//    circuit.addGate(dd::Zmat, 22_pc, 30);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Hmat, 29);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Zmat, 31_pc, 36);
//    circuit.addGate(dd::Xmat, 17_pc, 18);
//    circuit.addGate(dd::Zmat, 24_pc, 35);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Zmat, 15_pc, 10);
//    circuit.addGate(dd::Zmat, 18_pc, 33);
//    circuit.addGate(dd::Zmat, 35_pc, 5);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Ymat, 26_pc, 10);
//    circuit.addGate(dd::Xmat, 9_pc, 27);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Xmat, 31_pc, 0);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Ymat, 6_pc, 20);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Ymat, 16_pc, 33);
//    circuit.addGate(dd::Xmat, 20_pc, 6);
//    circuit.addGate(dd::Smat, 31);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Xmat, 13_pc, 3);
//    circuit.addGate(dd::Ymat, 16_pc, 19);
//    circuit.addGate(dd::Zmat, 35_pc, 11);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Ymat, 13_pc, 25);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Xmat, 13_pc, 22);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Xmat, 4_pc, 16);
//    circuit.addGate(dd::Ymat, 12_pc, 21);
//    circuit.addGate(dd::Ymat, 2_pc, 11);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Zmat, 17_pc, 3);
//    circuit.addGate(dd::Xmat, 4_pc, 12);
//    circuit.addGate(dd::Xmat, 11_pc, 26);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Zmat, 26_pc, 29);
//    circuit.addGate(dd::Zmat, 22_pc, 5);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Ymat, 26_pc, 20);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Smat, 21);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 39 qubis, containing 117 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_8) {
//    dd::QuantumCircuit circuit(39);
//
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Xmat, 1_pc, 33);
//    circuit.addGate(dd::Zmat, 28_pc, 16);
//    circuit.addGate(dd::Ymat, 2_pc, 18);
//    circuit.addGate(dd::Ymat, 29_pc, 15);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Zmat, 5);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Xmat, 32_pc, 1);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Ymat, 14_pc, 33);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Zmat, 2_pc, 5);
//    circuit.addGate(dd::Ymat, 35_pc, 8);
//    circuit.addGate(dd::Xmat, 6_pc, 30);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Xmat, 1_pc, 32);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Xmat, 32_pc, 18);
//    circuit.addGate(dd::Zmat, 37_pc, 8);
//    circuit.addGate(dd::Zmat, 5_pc, 12);
//    circuit.addGate(dd::Ymat, 9_pc, 2);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Xmat, 2_pc, 25);
//    circuit.addGate(dd::Zmat, 37_pc, 19);
//    circuit.addGate(dd::Zmat, 4_pc, 30);
//    circuit.addGate(dd::Xmat, 10_pc, 22);
//    circuit.addGate(dd::Zmat, 30_pc, 15);
//    circuit.addGate(dd::Xmat, 16_pc, 0);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Ymat, 35_pc, 37);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Ymat, 6_pc, 23);
//    circuit.addGate(dd::Ymat, 7_pc, 33);
//    circuit.addGate(dd::Zmat, 9_pc, 13);
//    circuit.addGate(dd::Ymat, 2_pc, 31);
//    circuit.addGate(dd::Zmat, 29_pc, 20);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Zmat, 21_pc, 22);
//    circuit.addGate(dd::Xmat, 20_pc, 24);
//    circuit.addGate(dd::Ymat, 29_pc, 10);
//    circuit.addGate(dd::Ymat, 26);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Zmat, 19_pc, 24);
//    circuit.addGate(dd::Ymat, 5_pc, 32);
//    circuit.addGate(dd::Zmat, 25_pc, 6);
//    circuit.addGate(dd::Zmat, 9_pc, 5);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Xmat, 22_pc, 15);
//    circuit.addGate(dd::Xmat, 9_pc, 26);
//    circuit.addGate(dd::Xmat, 12_pc, 7);
//    circuit.addGate(dd::Xmat, 5_pc, 17);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Ymat, 31_pc, 34);
//    circuit.addGate(dd::Xmat, 0_pc, 7);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Ymat, 34_pc, 10);
//    circuit.addGate(dd::Zmat, 16_pc, 17);
//    circuit.addGate(dd::Zmat, 37_pc, 38);
//    circuit.addGate(dd::Ymat, 36_pc, 27);
//    circuit.addGate(dd::Ymat, 18_pc, 22);
//    circuit.addGate(dd::Zmat, 4_pc, 19);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Ymat, 6_pc, 34);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Xmat, 26_pc, 4);
//    circuit.addGate(dd::Zmat, 0_pc, 32);
//    circuit.addGate(dd::Ymat, 26_pc, 8);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Ymat, 10_pc, 15);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Ymat, 12_pc, 24);
//    circuit.addGate(dd::Xmat, 31_pc, 19);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Zmat, 28_pc, 0);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Xmat, 29_pc, 11);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Xmat, 16_pc, 10);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Xmat, 22_pc, 25);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Ymat, 32_pc, 20);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Xmat, 27_pc, 32);
//    circuit.addGate(dd::Ymat, 20_pc, 3);
//    circuit.addGate(dd::Xmat, 38_pc, 25);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Ymat, 2_pc, 11);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 40 qubis, containing 120 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_9) {
//    dd::QuantumCircuit circuit(40);
//
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Xmat, 9_pc, 15);
//    circuit.addGate(dd::Xmat, 8_pc, 5);
//    circuit.addGate(dd::Ymat, 13_pc, 27);
//    circuit.addGate(dd::Xmat, 23_pc, 32);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Ymat, 7_pc, 11);
//    circuit.addGate(dd::Xmat, 35_pc, 9);
//    circuit.addGate(dd::Xmat, 2_pc, 6);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Ymat, 12_pc, 8);
//    circuit.addGate(dd::Ymat, 33);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Ymat, 33_pc, 20);
//    circuit.addGate(dd::Xmat, 34_pc, 1);
//    circuit.addGate(dd::Zmat, 7_pc, 2);
//    circuit.addGate(dd::Ymat, 30);
//    circuit.addGate(dd::Ymat, 24);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Xmat, 15_pc, 27);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Zmat, 14);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Zmat, 3_pc, 39);
//    circuit.addGate(dd::Xmat, 36_pc, 12);
//    circuit.addGate(dd::Zmat, 0_pc, 30);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Ymat, 3_pc, 28);
//    circuit.addGate(dd::Ymat, 37_pc, 29);
//    circuit.addGate(dd::Zmat, 14_pc, 22);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Zmat, 0_pc, 25);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Ymat, 15_pc, 1);
//    circuit.addGate(dd::Zmat, 38_pc, 32);
//    circuit.addGate(dd::Xmat, 23_pc, 38);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Xmat, 13_pc, 16);
//    circuit.addGate(dd::Zmat, 15_pc, 16);
//    circuit.addGate(dd::Xmat, 26_pc, 12);
//    circuit.addGate(dd::Ymat, 16_pc, 27);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Ymat, 15_pc, 3);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Ymat, 29_pc, 13);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Ymat, 17_pc, 0);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 12_pc, 4);
//    circuit.addGate(dd::Xmat, 23_pc, 5);
//    circuit.addGate(dd::Xmat, 10_pc, 5);
//    circuit.addGate(dd::Xmat, 39_pc, 23);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Zmat, 25_pc, 2);
//    circuit.addGate(dd::Zmat, 34_pc, 25);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Zmat, 34_pc, 19);
//    circuit.addGate(dd::Zmat, 19_pc, 29);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Ymat, 39_pc, 15);
//    circuit.addGate(dd::Xmat, 2_pc, 0);
//    circuit.addGate(dd::Ymat, 29_pc, 9);
//    circuit.addGate(dd::Ymat, 27_pc, 4);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Xmat, 23_pc, 37);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Xmat, 14_pc, 13);
//    circuit.addGate(dd::Ymat, 28_pc, 2);
//    circuit.addGate(dd::Ymat, 27_pc, 37);
//    circuit.addGate(dd::Zmat, 18_pc, 16);
//    circuit.addGate(dd::Xmat, 19_pc, 33);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Zmat, 25_pc, 33);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Ymat, 14_pc, 4);
//    circuit.addGate(dd::Ymat, 23_pc, 12);
//    circuit.addGate(dd::Zmat, 23_pc, 6);
//    circuit.addGate(dd::Zmat, 17_pc, 8);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Ymat, 5_pc, 25);
//    circuit.addGate(dd::Ymat, 29_pc, 37);
//    circuit.addGate(dd::Ymat, 35_pc, 16);
//    circuit.addGate(dd::Xmat, 25_pc, 29);
//    circuit.addGate(dd::Zmat, 23_pc, 39);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Ymat, 25_pc, 16);
//    circuit.addGate(dd::Zmat, 22_pc, 18);
//    circuit.addGate(dd::Zmat, 31_pc, 33);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Xmat, 16_pc, 18);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Zmat, 4_pc, 5);
//    circuit.addGate(dd::Zmat, 10_pc, 8);
//    circuit.addGate(dd::Ymat, 11_pc, 24);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Ymat, 8_pc, 10);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Zmat, 38_pc, 3);
//    circuit.addGate(dd::Ymat, 37_pc, 9);
//    circuit.addGate(dd::Xmat, 31);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 41 qubis, containing 123 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_10) {
//    dd::QuantumCircuit circuit(41);
//
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Xmat, 28_pc, 19);
//    circuit.addGate(dd::Xmat, 37_pc, 14);
//    circuit.addGate(dd::Ymat, 35_pc, 2);
//    circuit.addGate(dd::Xmat, 9_pc, 14);
//    circuit.addGate(dd::Xmat, 26);
//    circuit.addGate(dd::Ymat, 17_pc, 11);
//    circuit.addGate(dd::Xmat, 22_pc, 0);
//    circuit.addGate(dd::Xmat, 8_pc, 34);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Ymat, 14_pc, 10);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Ymat, 26_pc, 22);
//    circuit.addGate(dd::Xmat, 7_pc, 8);
//    circuit.addGate(dd::Zmat, 15_pc, 13);
//    circuit.addGate(dd::Ymat, 11);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Xmat, 8_pc, 30);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Zmat, 8_pc, 36);
//    circuit.addGate(dd::Xmat, 20_pc, 4);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Xmat, 33);
//    circuit.addGate(dd::Ymat, 11_pc, 23);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Zmat, 18_pc, 29);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Zmat, 36_pc, 12);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Ymat, 5_pc, 0);
//    circuit.addGate(dd::Zmat, 32_pc, 5);
//    circuit.addGate(dd::Xmat, 28_pc, 1);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Xmat, 35_pc, 2);
//    circuit.addGate(dd::Zmat, 0_pc, 22);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Ymat, 11_pc, 35);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Ymat, 3_pc, 24);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Ymat, 15_pc, 23);
//    circuit.addGate(dd::Ymat, 19_pc, 21);
//    circuit.addGate(dd::Zmat, 5_pc, 26);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Xmat, 18_pc, 20);
//    circuit.addGate(dd::Xmat, 21_pc, 39);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Zmat, 20_pc, 15);
//    circuit.addGate(dd::Zmat, 22_pc, 13);
//    circuit.addGate(dd::Zmat, 1_pc, 8);
//    circuit.addGate(dd::Ymat, 26);
//    circuit.addGate(dd::Ymat, 6_pc, 27);
//    circuit.addGate(dd::Zmat, 30_pc, 32);
//    circuit.addGate(dd::Zmat, 4_pc, 6);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Ymat, 30_pc, 35);
//    circuit.addGate(dd::Xmat, 19_pc, 22);
//    circuit.addGate(dd::Ymat, 8_pc, 33);
//    circuit.addGate(dd::Ymat, 37_pc, 2);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Xmat, 38_pc, 18);
//    circuit.addGate(dd::Xmat, 38);
//    circuit.addGate(dd::Xmat, 24_pc, 26);
//    circuit.addGate(dd::Ymat, 30_pc, 32);
//    circuit.addGate(dd::Ymat, 6_pc, 19);
//    circuit.addGate(dd::Zmat, 25_pc, 23);
//    circuit.addGate(dd::Xmat, 14_pc, 29);
//    circuit.addGate(dd::Zmat, 13_pc, 11);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 38_pc, 24);
//    circuit.addGate(dd::Xmat, 9_pc, 35);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Ymat, 35_pc, 33);
//    circuit.addGate(dd::Zmat, 20_pc, 33);
//    circuit.addGate(dd::Zmat, 8_pc, 16);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Ymat, 31_pc, 28);
//    circuit.addGate(dd::Zmat, 25_pc, 38);
//    circuit.addGate(dd::Xmat, 19_pc, 29);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Zmat, 25_pc, 14);
//    circuit.addGate(dd::Ymat, 13_pc, 7);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Ymat, 25_pc, 5);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Zmat, 10_pc, 27);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Zmat, 14_pc, 10);
//    circuit.addGate(dd::Ymat, 26_pc, 23);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Hmat, 35);
//    circuit.addGate(dd::Zmat, 21_pc, 6);
//    circuit.addGate(dd::Ymat, 18_pc, 10);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Ymat, 14_pc, 39);
//    circuit.addGate(dd::Ymat, 10);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Zmat, 36_pc, 22);
//    circuit.addGate(dd::Ymat, 34_pc, 10);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Xmat, 17_pc, 36);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Ymat, 6_pc, 13);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 42 qubis, containing 126 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_11) {
//    dd::QuantumCircuit circuit(42);
//
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Xmat, 37);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Ymat, 18_pc, 35);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Xmat, 37_pc, 5);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Xmat, 37_pc, 29);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Ymat, 37_pc, 12);
//    circuit.addGate(dd::Xmat, 41_pc, 20);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Xmat, 0_pc, 33);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Zmat, 7_pc, 41);
//    circuit.addGate(dd::Ymat, 38_pc, 28);
//    circuit.addGate(dd::Zmat, 30_pc, 40);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Ymat, 31_pc, 19);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Zmat, 41_pc, 23);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Ymat, 25_pc, 9);
//    circuit.addGate(dd::Xmat, 35_pc, 6);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Xmat, 0_pc, 32);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Zmat, 13_pc, 25);
//    circuit.addGate(dd::Xmat, 10_pc, 3);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Zmat, 40_pc, 16);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Zmat, 24_pc, 8);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Ymat, 32);
//    circuit.addGate(dd::Zmat, 1_pc, 30);
//    circuit.addGate(dd::Ymat, 39_pc, 37);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Ymat, 4_pc, 20);
//    circuit.addGate(dd::Zmat, 26_pc, 15);
//    circuit.addGate(dd::Xmat, 23_pc, 41);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Zmat, 3_pc, 34);
//    circuit.addGate(dd::Hmat, 29);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Xmat, 13_pc, 19);
//    circuit.addGate(dd::Zmat, 22_pc, 3);
//    circuit.addGate(dd::Zmat, 22_pc, 21);
//    circuit.addGate(dd::Zmat, 15_pc, 24);
//    circuit.addGate(dd::Zmat, 12_pc, 4);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Zmat, 37);
//    circuit.addGate(dd::Xmat, 8_pc, 15);
//    circuit.addGate(dd::Ymat, 35_pc, 34);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Ymat, 7_pc, 28);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Zmat, 24_pc, 36);
//    circuit.addGate(dd::Xmat, 0_pc, 4);
//    circuit.addGate(dd::Ymat, 39_pc, 1);
//    circuit.addGate(dd::Ymat, 31_pc, 30);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Zmat, 19_pc, 39);
//    circuit.addGate(dd::Zmat, 38_pc, 9);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Zmat, 0_pc, 31);
//    circuit.addGate(dd::Xmat, 18_pc, 28);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Xmat, 23_pc, 36);
//    circuit.addGate(dd::Ymat, 31_pc, 7);
//    circuit.addGate(dd::Zmat, 16_pc, 31);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Zmat, 33_pc, 17);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Ymat, 20_pc, 10);
//    circuit.addGate(dd::Ymat, 2_pc, 14);
//    circuit.addGate(dd::Ymat, 19_pc, 22);
//    circuit.addGate(dd::Xmat, 10_pc, 30);
//    circuit.addGate(dd::Zmat, 33_pc, 29);
//    circuit.addGate(dd::Zmat, 5_pc, 26);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 27_pc, 16);
//    circuit.addGate(dd::Xmat, 36_pc, 23);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Xmat, 26);
//    circuit.addGate(dd::Zmat, 14);
//    circuit.addGate(dd::Xmat, 5_pc, 32);
//    circuit.addGate(dd::Zmat, 37_pc, 21);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Zmat, 27_pc, 21);
//    circuit.addGate(dd::Xmat, 16_pc, 15);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Zmat, 7_pc, 41);
//    circuit.addGate(dd::Hmat, 35);
//    circuit.addGate(dd::Xmat, 38_pc, 15);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Xmat, 31_pc, 7);
//    circuit.addGate(dd::Ymat, 14_pc, 7);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Zmat, 11_pc, 35);
//    circuit.addGate(dd::Xmat, 32_pc, 10);
//    circuit.addGate(dd::Zmat, 16_pc, 5);
//    circuit.addGate(dd::Xmat, 10);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 43 qubis, containing 129 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_12) {
//    dd::QuantumCircuit circuit(43);
//
//    circuit.addGate(dd::Xmat, 14_pc, 19);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Xmat, 10_pc, 2);
//    circuit.addGate(dd::Xmat, 6_pc, 31);
//    circuit.addGate(dd::Ymat, 37_pc, 29);
//    circuit.addGate(dd::Ymat, 34_pc, 28);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Zmat, 12_pc, 14);
//    circuit.addGate(dd::Ymat, 36_pc, 10);
//    circuit.addGate(dd::Ymat, 25_pc, 4);
//    circuit.addGate(dd::Xmat, 14_pc, 6);
//    circuit.addGate(dd::Xmat, 13_pc, 33);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Zmat, 0_pc, 16);
//    circuit.addGate(dd::Xmat, 23_pc, 24);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Zmat, 17_pc, 16);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Ymat, 5_pc, 29);
//    circuit.addGate(dd::Xmat, 6_pc, 16);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 21_pc, 3);
//    circuit.addGate(dd::Zmat, 12_pc, 19);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Zmat, 28_pc, 7);
//    circuit.addGate(dd::Ymat, 13_pc, 6);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Zmat, 22_pc, 0);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Zmat, 26_pc, 11);
//    circuit.addGate(dd::Xmat, 30_pc, 33);
//    circuit.addGate(dd::Xmat, 15_pc, 7);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Ymat, 28_pc, 17);
//    circuit.addGate(dd::Ymat, 6_pc, 23);
//    circuit.addGate(dd::Hmat, 9);
//    circuit.addGate(dd::Zmat, 5_pc, 13);
//    circuit.addGate(dd::Ymat, 8_pc, 40);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 40_pc, 32);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Zmat, 32_pc, 30);
//    circuit.addGate(dd::Xmat, 28_pc, 10);
//    circuit.addGate(dd::Xmat, 20_pc, 4);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Zmat, 10_pc, 13);
//    circuit.addGate(dd::Ymat, 31_pc, 18);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Xmat, 3_pc, 12);
//    circuit.addGate(dd::Xmat, 3_pc, 38);
//    circuit.addGate(dd::Zmat, 28_pc, 40);
//    circuit.addGate(dd::Xmat, 41);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Xmat, 8_pc, 38);
//    circuit.addGate(dd::Xmat, 3_pc, 20);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Ymat, 13_pc, 30);
//    circuit.addGate(dd::Xmat, 36_pc, 9);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Zmat, 17);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 8_pc, 22);
//    circuit.addGate(dd::Xmat, 17_pc, 37);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Ymat, 39_pc, 24);
//    circuit.addGate(dd::Ymat, 9_pc, 7);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Zmat, 37);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Xmat, 2_pc, 17);
//    circuit.addGate(dd::Xmat, 31_pc, 6);
//    circuit.addGate(dd::Xmat, 35_pc, 30);
//    circuit.addGate(dd::Zmat, 16_pc, 22);
//    circuit.addGate(dd::Zmat, 29_pc, 21);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Xmat, 19_pc, 11);
//    circuit.addGate(dd::Ymat, 27_pc, 2);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Ymat, 6_pc, 14);
//    circuit.addGate(dd::Xmat, 20_pc, 0);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Zmat, 24_pc, 6);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Xmat, 18_pc, 31);
//    circuit.addGate(dd::Smat, 31);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Zmat, 19_pc, 16);
//    circuit.addGate(dd::Ymat, 28_pc, 1);
//    circuit.addGate(dd::Ymat, 19_pc, 15);
//    circuit.addGate(dd::Xmat, 13_pc, 40);
//    circuit.addGate(dd::Ymat, 15_pc, 30);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Ymat, 1_pc, 11);
//    circuit.addGate(dd::Xmat, 37_pc, 21);
//    circuit.addGate(dd::Zmat, 40_pc, 37);
//    circuit.addGate(dd::Ymat, 14_pc, 24);
//    circuit.addGate(dd::Ymat, 0_pc, 35);
//    circuit.addGate(dd::Xmat, 6_pc, 20);
//    circuit.addGate(dd::Ymat, 35_pc, 2);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Xmat, 37_pc, 9);
//    circuit.addGate(dd::Ymat, 39_pc, 34);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Xmat, 3_pc, 14);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Ymat, 7_pc, 2);
//    circuit.addGate(dd::Zmat, 39_pc, 42);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Zmat, 41_pc, 39);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Xmat, 21_pc, 40);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Ymat, 20_pc, 1);
//    circuit.addGate(dd::Ymat, 32);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Zmat, 30_pc, 24);
//    circuit.addGate(dd::Ymat, 31_pc, 32);
//    circuit.addGate(dd::Smat, 20);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 44 qubis, containing 132 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_13) {
//    dd::QuantumCircuit circuit(44);
//
//    circuit.addGate(dd::Zmat, 31_pc, 25);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Ymat, 7_pc, 16);
//    circuit.addGate(dd::Ymat, 26_pc, 33);
//    circuit.addGate(dd::Xmat, 35_pc, 4);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Ymat, 31_pc, 14);
//    circuit.addGate(dd::Ymat, 11_pc, 20);
//    circuit.addGate(dd::Zmat, 7_pc, 20);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Xmat, 39_pc, 10);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Ymat, 6_pc, 27);
//    circuit.addGate(dd::Xmat, 4_pc, 24);
//    circuit.addGate(dd::Ymat, 41_pc, 34);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Zmat, 10_pc, 12);
//    circuit.addGate(dd::Xmat, 16_pc, 24);
//    circuit.addGate(dd::Ymat, 4_pc, 16);
//    circuit.addGate(dd::Xmat, 6_pc, 37);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 4_pc, 15);
//    circuit.addGate(dd::Zmat, 15_pc, 28);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Ymat, 31_pc, 2);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Ymat, 34_pc, 16);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Xmat, 20_pc, 38);
//    circuit.addGate(dd::Ymat, 3_pc, 41);
//    circuit.addGate(dd::Ymat, 21_pc, 1);
//    circuit.addGate(dd::Ymat, 6_pc, 26);
//    circuit.addGate(dd::Xmat, 33_pc, 1);
//    circuit.addGate(dd::Zmat, 5_pc, 24);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Ymat, 37);
//    circuit.addGate(dd::Xmat, 13_pc, 16);
//    circuit.addGate(dd::Xmat, 1_pc, 16);
//    circuit.addGate(dd::Xmat, 13_pc, 34);
//    circuit.addGate(dd::Xmat, 4_pc, 37);
//    circuit.addGate(dd::Zmat, 0_pc, 24);
//    circuit.addGate(dd::Xmat, 41);
//    circuit.addGate(dd::Ymat, 14_pc, 25);
//    circuit.addGate(dd::Hmat, 34);
//    circuit.addGate(dd::Xmat, 8_pc, 42);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Zmat, 4_pc, 23);
//    circuit.addGate(dd::Ymat, 10_pc, 36);
//    circuit.addGate(dd::Zmat, 27_pc, 2);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Xmat, 37_pc, 11);
//    circuit.addGate(dd::Xmat, 40_pc, 15);
//    circuit.addGate(dd::Xmat, 27_pc, 33);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Zmat, 17_pc, 0);
//    circuit.addGate(dd::Zmat, 2_pc, 6);
//    circuit.addGate(dd::Xmat, 26_pc, 8);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Zmat, 21_pc, 36);
//    circuit.addGate(dd::Xmat, 3_pc, 0);
//    circuit.addGate(dd::Ymat, 6_pc, 31);
//    circuit.addGate(dd::Xmat, 2_pc, 36);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Zmat, 6_pc, 21);
//    circuit.addGate(dd::Ymat, 26_pc, 37);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Ymat, 24);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Ymat, 5_pc, 36);
//    circuit.addGate(dd::Hmat, 40);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Xmat, 33_pc, 21);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Ymat, 33_pc, 6);
//    circuit.addGate(dd::Xmat, 29_pc, 9);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Ymat, 3_pc, 7);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Xmat, 1_pc, 32);
//    circuit.addGate(dd::Hmat, 9);
//    circuit.addGate(dd::Xmat, 4_pc, 9);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Xmat, 43_pc, 2);
//    circuit.addGate(dd::Xmat, 11_pc, 7);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Xmat, 5_pc, 24);
//    circuit.addGate(dd::Zmat, 12_pc, 7);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Ymat, 2_pc, 31);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Xmat, 9_pc, 10);
//    circuit.addGate(dd::Xmat, 37_pc, 3);
//    circuit.addGate(dd::Ymat, 30_pc, 13);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Zmat, 29_pc, 6);
//    circuit.addGate(dd::Xmat, 42_pc, 18);
//    circuit.addGate(dd::Xmat, 39_pc, 7);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Zmat, 17_pc, 2);
//    circuit.addGate(dd::Zmat, 18_pc, 41);
//    circuit.addGate(dd::Zmat, 33_pc, 5);
//    circuit.addGate(dd::Zmat, 34_pc, 18);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Ymat, 22_pc, 34);
//    circuit.addGate(dd::Xmat, 21_pc, 1);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Xmat, 21_pc, 17);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 28_pc, 10);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Zmat, 33_pc, 16);
//    circuit.addGate(dd::Xmat, 6_pc, 3);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Ymat, 19_pc, 24);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 45 qubis, containing 135 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_14) {
//    dd::QuantumCircuit circuit(45);
//
//    circuit.addGate(dd::Zmat, 17_pc, 4);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Ymat, 4_pc, 30);
//    circuit.addGate(dd::Ymat, 17_pc, 44);
//    circuit.addGate(dd::Xmat, 43_pc, 36);
//    circuit.addGate(dd::Ymat, 11);
//    circuit.addGate(dd::Ymat, 8_pc, 36);
//    circuit.addGate(dd::Ymat, 19_pc, 10);
//    circuit.addGate(dd::Zmat, 22_pc, 14);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 36_pc, 23);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 1_pc, 27);
//    circuit.addGate(dd::Xmat, 15_pc, 32);
//    circuit.addGate(dd::Ymat, 9_pc, 8);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Xmat, 35);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Zmat, 19_pc, 8);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Xmat, 12_pc, 11);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Ymat, 43_pc, 12);
//    circuit.addGate(dd::Zmat, 9_pc, 2);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Ymat, 14_pc, 23);
//    circuit.addGate(dd::Hmat, 42);
//    circuit.addGate(dd::Ymat, 22_pc, 26);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Xmat, 21_pc, 1);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Ymat, 4_pc, 16);
//    circuit.addGate(dd::Xmat, 5_pc, 34);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 38_pc, 18);
//    circuit.addGate(dd::Xmat, 26_pc, 33);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Xmat, 38);
//    circuit.addGate(dd::Xmat, 34_pc, 31);
//    circuit.addGate(dd::Xmat, 9_pc, 24);
//    circuit.addGate(dd::Xmat, 21_pc, 11);
//    circuit.addGate(dd::Zmat, 32_pc, 25);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Ymat, 8_pc, 1);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Zmat, 29_pc, 40);
//    circuit.addGate(dd::Ymat, 11_pc, 20);
//    circuit.addGate(dd::Zmat, 14_pc, 21);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Xmat, 9_pc, 24);
//    circuit.addGate(dd::Xmat, 26_pc, 4);
//    circuit.addGate(dd::Xmat, 10_pc, 36);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Zmat, 42_pc, 41);
//    circuit.addGate(dd::Zmat, 17_pc, 35);
//    circuit.addGate(dd::Xmat, 20_pc, 26);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Zmat, 38_pc, 37);
//    circuit.addGate(dd::Xmat, 39_pc, 10);
//    circuit.addGate(dd::Ymat, 14_pc, 33);
//    circuit.addGate(dd::Xmat, 2_pc, 1);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Zmat, 24_pc, 28);
//    circuit.addGate(dd::Ymat, 20_pc, 24);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Ymat, 16_pc, 0);
//    circuit.addGate(dd::Hmat, 35);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Xmat, 16_pc, 2);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Ymat, 37_pc, 30);
//    circuit.addGate(dd::Xmat, 37_pc, 7);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Ymat, 37_pc, 17);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Xmat, 26_pc, 20);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Xmat, 4_pc, 44);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Xmat, 17_pc, 11);
//    circuit.addGate(dd::Xmat, 18_pc, 20);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Xmat, 38_pc, 11);
//    circuit.addGate(dd::Zmat, 31_pc, 8);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Ymat, 2_pc, 38);
//    circuit.addGate(dd::Hmat, 34);
//    circuit.addGate(dd::Xmat, 8_pc, 38);
//    circuit.addGate(dd::Xmat, 20_pc, 23);
//    circuit.addGate(dd::Ymat, 38_pc, 27);
//    circuit.addGate(dd::Hmat, 43);
//    circuit.addGate(dd::Zmat, 20_pc, 19);
//    circuit.addGate(dd::Xmat, 4_pc, 13);
//    circuit.addGate(dd::Xmat, 39_pc, 40);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Zmat, 43_pc, 8);
//    circuit.addGate(dd::Zmat, 3_pc, 17);
//    circuit.addGate(dd::Zmat, 37_pc, 27);
//    circuit.addGate(dd::Zmat, 26_pc, 21);
//    circuit.addGate(dd::Ymat, 40_pc, 3);
//    circuit.addGate(dd::Zmat, 16);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Xmat, 6_pc, 25);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Smat, 44);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Ymat, 0_pc, 11);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Zmat, 44_pc, 37);
//    circuit.addGate(dd::Xmat, 20_pc, 11);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 32_pc, 14);
//    circuit.addGate(dd::Zmat, 19_pc, 5);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 46 qubis, containing 138 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_15) {
//    dd::QuantumCircuit circuit(46);
//
//    circuit.addGate(dd::Zmat, 29_pc, 33);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Xmat, 0_pc, 8);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Ymat, 13_pc, 35);
//    circuit.addGate(dd::Xmat, 11_pc, 45);
//    circuit.addGate(dd::Xmat, 27_pc, 39);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Zmat, 40_pc, 11);
//    circuit.addGate(dd::Xmat, 34_pc, 29);
//    circuit.addGate(dd::Ymat, 8_pc, 42);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Ymat, 12_pc, 0);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Ymat, 2_pc, 12);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Zmat, 14_pc, 22);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Zmat, 8_pc, 12);
//    circuit.addGate(dd::Hmat, 45);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Xmat, 4_pc, 41);
//    circuit.addGate(dd::Ymat, 37_pc, 14);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Xmat, 34_pc, 7);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Smat, 38);
//    circuit.addGate(dd::Xmat, 0_pc, 19);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Ymat, 36_pc, 26);
//    circuit.addGate(dd::Ymat, 3_pc, 39);
//    circuit.addGate(dd::Ymat, 13_pc, 16);
//    circuit.addGate(dd::Zmat, 17_pc, 29);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Ymat, 23_pc, 19);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Ymat, 43_pc, 21);
//    circuit.addGate(dd::Hmat, 43);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Xmat, 44_pc, 6);
//    circuit.addGate(dd::Xmat, 23_pc, 41);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Zmat, 31_pc, 17);
//    circuit.addGate(dd::Xmat, 44_pc, 13);
//    circuit.addGate(dd::Xmat, 28_pc, 35);
//    circuit.addGate(dd::Zmat, 38_pc, 16);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Zmat, 45);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 35_pc, 30);
//    circuit.addGate(dd::Xmat, 41);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Xmat, 23_pc, 39);
//    circuit.addGate(dd::Xmat, 19_pc, 5);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Ymat, 14_pc, 31);
//    circuit.addGate(dd::Ymat, 30_pc, 31);
//    circuit.addGate(dd::Xmat, 18_pc, 5);
//    circuit.addGate(dd::Zmat, 33_pc, 10);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Hmat, 29);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Ymat, 28_pc, 26);
//    circuit.addGate(dd::Xmat, 11_pc, 26);
//    circuit.addGate(dd::Ymat, 11_pc, 44);
//    circuit.addGate(dd::Xmat, 3_pc, 30);
//    circuit.addGate(dd::Zmat, 34_pc, 7);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Ymat, 20_pc, 31);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Xmat, 32_pc, 17);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 0_pc, 45);
//    circuit.addGate(dd::Zmat, 28_pc, 3);
//    circuit.addGate(dd::Ymat, 17_pc, 42);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Xmat, 17_pc, 9);
//    circuit.addGate(dd::Xmat, 24_pc, 14);
//    circuit.addGate(dd::Xmat, 7_pc, 22);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Smat, 31);
//    circuit.addGate(dd::Ymat, 10_pc, 17);
//    circuit.addGate(dd::Xmat, 27_pc, 33);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Xmat, 0_pc, 39);
//    circuit.addGate(dd::Xmat, 1_pc, 15);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Zmat, 9_pc, 4);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Ymat, 42_pc, 7);
//    circuit.addGate(dd::Xmat, 26_pc, 17);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Xmat, 25_pc, 2);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Ymat, 8_pc, 26);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Xmat, 32_pc, 19);
//    circuit.addGate(dd::Ymat, 21_pc, 12);
//    circuit.addGate(dd::Zmat, 43_pc, 38);
//    circuit.addGate(dd::Zmat, 41_pc, 27);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Xmat, 32);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Ymat, 44_pc, 45);
//    circuit.addGate(dd::Zmat, 38_pc, 27);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Zmat, 6_pc, 16);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 47 qubis, containing 141 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_16) {
//    dd::QuantumCircuit circuit(47);
//
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Xmat, 23_pc, 39);
//    circuit.addGate(dd::Xmat, 4_pc, 10);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Zmat, 16_pc, 3);
//    circuit.addGate(dd::Ymat, 30_pc, 6);
//    circuit.addGate(dd::Zmat, 46_pc, 27);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Smat, 46);
//    circuit.addGate(dd::Zmat, 16_pc, 28);
//    circuit.addGate(dd::Zmat, 44_pc, 38);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Ymat, 30_pc, 13);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Ymat, 27_pc, 25);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Xmat, 27_pc, 36);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Xmat, 2_pc, 20);
//    circuit.addGate(dd::Zmat, 37);
//    circuit.addGate(dd::Zmat, 37);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Zmat, 46_pc, 6);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Ymat, 30);
//    circuit.addGate(dd::Xmat, 28_pc, 21);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Ymat, 28_pc, 20);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Ymat, 45_pc, 8);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 15_pc, 7);
//    circuit.addGate(dd::Zmat, 29_pc, 26);
//    circuit.addGate(dd::Ymat, 23_pc, 9);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Zmat, 17_pc, 10);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Xmat, 42_pc, 46);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Zmat, 8_pc, 33);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Xmat, 39_pc, 20);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Ymat, 29_pc, 10);
//    circuit.addGate(dd::Ymat, 20_pc, 14);
//    circuit.addGate(dd::Xmat, 14_pc, 38);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Xmat, 37);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Zmat, 29_pc, 40);
//    circuit.addGate(dd::Xmat, 33_pc, 34);
//    circuit.addGate(dd::Xmat, 44_pc, 12);
//    circuit.addGate(dd::Xmat, 26_pc, 23);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Zmat, 13_pc, 21);
//    circuit.addGate(dd::Ymat, 18_pc, 32);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Xmat, 4_pc, 22);
//    circuit.addGate(dd::Ymat, 34_pc, 16);
//    circuit.addGate(dd::Zmat, 39_pc, 15);
//    circuit.addGate(dd::Zmat, 20_pc, 30);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Zmat, 16_pc, 24);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Xmat, 38);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Ymat, 37_pc, 19);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Ymat, 42_pc, 3);
//    circuit.addGate(dd::Zmat, 40_pc, 21);
//    circuit.addGate(dd::Ymat, 25_pc, 0);
//    circuit.addGate(dd::Ymat, 43_pc, 7);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Zmat, 15_pc, 7);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Zmat, 0_pc, 41);
//    circuit.addGate(dd::Zmat, 25_pc, 30);
//    circuit.addGate(dd::Xmat, 0_pc, 9);
//    circuit.addGate(dd::Zmat, 9_pc, 40);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Zmat, 25_pc, 31);
//    circuit.addGate(dd::Ymat, 42);
//    circuit.addGate(dd::Ymat, 37_pc, 27);
//    circuit.addGate(dd::Zmat, 30_pc, 36);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Ymat, 19_pc, 20);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Xmat, 18_pc, 2);
//    circuit.addGate(dd::Xmat, 41_pc, 14);
//    circuit.addGate(dd::Ymat, 9_pc, 23);
//    circuit.addGate(dd::Xmat, 40_pc, 18);
//    circuit.addGate(dd::Zmat, 27_pc, 4);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Ymat, 38_pc, 6);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Zmat, 25_pc, 16);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Ymat, 19_pc, 35);
//    circuit.addGate(dd::Ymat, 32_pc, 26);
//    circuit.addGate(dd::Xmat, 9_pc, 8);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Xmat, 1_pc, 46);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Zmat, 14_pc, 27);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Zmat, 21_pc, 40);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Ymat, 42);
//    circuit.addGate(dd::Ymat, 43_pc, 19);
//    circuit.addGate(dd::Smat, 32);
//    circuit.addGate(dd::Xmat, 15_pc, 34);
//    circuit.addGate(dd::Zmat, 4_pc, 23);
//    circuit.addGate(dd::Ymat, 3_pc, 14);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Xmat, 33);
//    circuit.addGate(dd::Zmat, 29_pc, 45);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Zmat, 4_pc, 31);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Xmat, 34_pc, 15);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 48 qubis, containing 144 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_17) {
//    dd::QuantumCircuit circuit(48);
//
//    circuit.addGate(dd::Xmat, 31_pc, 25);
//    circuit.addGate(dd::Ymat, 2_pc, 18);
//    circuit.addGate(dd::Xmat, 11_pc, 34);
//    circuit.addGate(dd::Zmat, 19_pc, 13);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Zmat, 31_pc, 12);
//    circuit.addGate(dd::Zmat, 14_pc, 43);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Zmat, 27_pc, 29);
//    circuit.addGate(dd::Xmat, 47_pc, 15);
//    circuit.addGate(dd::Ymat, 46_pc, 41);
//    circuit.addGate(dd::Zmat, 17_pc, 47);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Ymat, 14_pc, 36);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Ymat, 39);
//    circuit.addGate(dd::Ymat, 4_pc, 43);
//    circuit.addGate(dd::Ymat, 0_pc, 34);
//    circuit.addGate(dd::Ymat, 23_pc, 39);
//    circuit.addGate(dd::Ymat, 24_pc, 18);
//    circuit.addGate(dd::Zmat, 6_pc, 5);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Ymat, 12_pc, 18);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Ymat, 34_pc, 9);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Zmat, 44_pc, 3);
//    circuit.addGate(dd::Xmat, 33_pc, 32);
//    circuit.addGate(dd::Ymat, 44_pc, 27);
//    circuit.addGate(dd::Hmat, 3);
//    circuit.addGate(dd::Xmat, 28_pc, 29);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Zmat, 8_pc, 30);
//    circuit.addGate(dd::Xmat, 0_pc, 46);
//    circuit.addGate(dd::Ymat, 22_pc, 29);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Xmat, 10_pc, 14);
//    circuit.addGate(dd::Xmat, 43_pc, 5);
//    circuit.addGate(dd::Zmat, 19_pc, 22);
//    circuit.addGate(dd::Zmat, 17_pc, 45);
//    circuit.addGate(dd::Xmat, 46_pc, 11);
//    circuit.addGate(dd::Zmat, 7_pc, 40);
//    circuit.addGate(dd::Ymat, 12_pc, 32);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Xmat, 34_pc, 16);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Zmat, 33_pc, 31);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Xmat, 15_pc, 5);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Xmat, 14_pc, 5);
//    circuit.addGate(dd::Ymat, 17_pc, 10);
//    circuit.addGate(dd::Zmat, 2_pc, 30);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Zmat, 1_pc, 19);
//    circuit.addGate(dd::Xmat, 29_pc, 4);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Xmat, 33_pc, 24);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Xmat, 29_pc, 25);
//    circuit.addGate(dd::Ymat, 27_pc, 41);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Xmat, 26);
//    circuit.addGate(dd::Xmat, 23_pc, 25);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Ymat, 36_pc, 29);
//    circuit.addGate(dd::Zmat, 46_pc, 45);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Ymat, 18_pc, 39);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Zmat, 7_pc, 3);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Ymat, 10_pc, 20);
//    circuit.addGate(dd::Xmat, 18_pc, 29);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Ymat, 21_pc, 17);
//    circuit.addGate(dd::Zmat, 25_pc, 26);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Xmat, 4_pc, 7);
//    circuit.addGate(dd::Zmat, 41_pc, 14);
//    circuit.addGate(dd::Ymat, 3_pc, 41);
//    circuit.addGate(dd::Xmat, 10_pc, 11);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Ymat, 28_pc, 7);
//    circuit.addGate(dd::Zmat, 1_pc, 18);
//    circuit.addGate(dd::Xmat, 29_pc, 13);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Ymat, 42_pc, 0);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Xmat, 26_pc, 44);
//    circuit.addGate(dd::Smat, 44);
//    circuit.addGate(dd::Ymat, 44_pc, 20);
//    circuit.addGate(dd::Ymat, 19_pc, 21);
//    circuit.addGate(dd::Ymat, 18_pc, 10);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Xmat, 9_pc, 11);
//    circuit.addGate(dd::Zmat, 7_pc, 47);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Zmat, 15_pc, 22);
//    circuit.addGate(dd::Zmat, 9);
//    circuit.addGate(dd::Zmat, 28_pc, 38);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Xmat, 0_pc, 20);
//    circuit.addGate(dd::Smat, 43);
//    circuit.addGate(dd::Xmat, 42_pc, 0);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Ymat, 11_pc, 30);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Ymat, 35_pc, 32);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Hmat, 12);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 49 qubis, containing 147 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_18) {
//    dd::QuantumCircuit circuit(49);
//
//    circuit.addGate(dd::Xmat, 28_pc, 32);
//    circuit.addGate(dd::Ymat, 36_pc, 22);
//    circuit.addGate(dd::Hmat, 40);
//    circuit.addGate(dd::Xmat, 37_pc, 0);
//    circuit.addGate(dd::Ymat, 48_pc, 30);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Ymat, 33_pc, 48);
//    circuit.addGate(dd::Zmat, 25_pc, 6);
//    circuit.addGate(dd::Zmat, 14_pc, 35);
//    circuit.addGate(dd::Xmat, 5_pc, 19);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Xmat, 32_pc, 9);
//    circuit.addGate(dd::Zmat, 33_pc, 15);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Zmat, 9_pc, 41);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Zmat, 11_pc, 1);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 4_pc, 44);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Xmat, 45_pc, 3);
//    circuit.addGate(dd::Ymat, 37_pc, 5);
//    circuit.addGate(dd::Ymat, 3_pc, 46);
//    circuit.addGate(dd::Xmat, 47_pc, 43);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Ymat, 26_pc, 23);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Zmat, 18_pc, 25);
//    circuit.addGate(dd::Zmat, 23_pc, 38);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Ymat, 3_pc, 44);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Zmat, 8_pc, 28);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Ymat, 23_pc, 33);
//    circuit.addGate(dd::Xmat, 36_pc, 27);
//    circuit.addGate(dd::Zmat, 20_pc, 9);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Zmat, 16);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Xmat, 37_pc, 32);
//    circuit.addGate(dd::Xmat, 37_pc, 15);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Xmat, 36_pc, 33);
//    circuit.addGate(dd::Zmat, 4_pc, 8);
//    circuit.addGate(dd::Zmat, 31_pc, 36);
//    circuit.addGate(dd::Xmat, 12_pc, 38);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Ymat, 26);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Ymat, 30);
//    circuit.addGate(dd::Xmat, 33_pc, 6);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Ymat, 11);
//    circuit.addGate(dd::Zmat, 18_pc, 7);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Xmat, 42_pc, 33);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Xmat, 24_pc, 25);
//    circuit.addGate(dd::Ymat, 7_pc, 11);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Zmat, 30_pc, 8);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Ymat, 4_pc, 34);
//    circuit.addGate(dd::Smat, 48);
//    circuit.addGate(dd::Xmat, 1_pc, 28);
//    circuit.addGate(dd::Zmat, 15_pc, 1);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Ymat, 5_pc, 28);
//    circuit.addGate(dd::Ymat, 41_pc, 36);
//    circuit.addGate(dd::Zmat, 46);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Ymat, 36_pc, 38);
//    circuit.addGate(dd::Zmat, 22_pc, 44);
//    circuit.addGate(dd::Xmat, 46_pc, 28);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Ymat, 6_pc, 33);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Zmat, 18_pc, 30);
//    circuit.addGate(dd::Xmat, 41_pc, 10);
//    circuit.addGate(dd::Xmat, 28_pc, 42);
//    circuit.addGate(dd::Zmat, 47_pc, 26);
//    circuit.addGate(dd::Ymat, 16_pc, 2);
//    circuit.addGate(dd::Ymat, 29_pc, 3);
//    circuit.addGate(dd::Ymat, 36_pc, 41);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Ymat, 11_pc, 1);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Xmat, 5_pc, 38);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Zmat, 22_pc, 16);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Zmat, 12_pc, 6);
//    circuit.addGate(dd::Ymat, 44_pc, 2);
//    circuit.addGate(dd::Xmat, 37);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Xmat, 11_pc, 8);
//    circuit.addGate(dd::Ymat, 30_pc, 23);
//    circuit.addGate(dd::Ymat, 48_pc, 35);
//    circuit.addGate(dd::Smat, 42);
//    circuit.addGate(dd::Zmat, 42_pc, 2);
//    circuit.addGate(dd::Ymat, 44_pc, 9);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Ymat, 13_pc, 20);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Zmat, 31_pc, 44);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Zmat, 28_pc, 21);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Ymat, 33_pc, 1);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Xmat, 23_pc, 48);
//    circuit.addGate(dd::Ymat, 48_pc, 13);
//    circuit.addGate(dd::Ymat, 47);
//    circuit.addGate(dd::Zmat, 35);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Smat, 40);
//    circuit.addGate(dd::Ymat, 32_pc, 17);
//    circuit.addGate(dd::Zmat, 47);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Zmat, 31_pc, 25);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 20_pc, 21);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Xmat, 31_pc, 37);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 50 qubis, containing 150 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_19) {
//    dd::QuantumCircuit circuit(50);
//
//    circuit.addGate(dd::Xmat, 25_pc, 16);
//    circuit.addGate(dd::Ymat, 15_pc, 26);
//    circuit.addGate(dd::Hmat, 29);
//    circuit.addGate(dd::Xmat, 29_pc, 12);
//    circuit.addGate(dd::Ymat, 4_pc, 5);
//    circuit.addGate(dd::Xmat, 48);
//    circuit.addGate(dd::Zmat, 35);
//    circuit.addGate(dd::Ymat, 49_pc, 14);
//    circuit.addGate(dd::Zmat, 40_pc, 35);
//    circuit.addGate(dd::Zmat, 43_pc, 38);
//    circuit.addGate(dd::Xmat, 26_pc, 29);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Xmat, 17_pc, 12);
//    circuit.addGate(dd::Zmat, 24_pc, 17);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Ymat, 43);
//    circuit.addGate(dd::Zmat, 38_pc, 27);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Zmat, 11_pc, 46);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Xmat, 26_pc, 33);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Xmat, 24_pc, 19);
//    circuit.addGate(dd::Ymat, 15_pc, 46);
//    circuit.addGate(dd::Ymat, 26_pc, 19);
//    circuit.addGate(dd::Xmat, 42_pc, 44);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Ymat, 22_pc, 41);
//    circuit.addGate(dd::Smat, 40);
//    circuit.addGate(dd::Zmat, 4_pc, 3);
//    circuit.addGate(dd::Zmat, 28_pc, 11);
//    circuit.addGate(dd::Xmat, 44);
//    circuit.addGate(dd::Ymat, 49_pc, 27);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Zmat, 1_pc, 3);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Ymat, 47_pc, 1);
//    circuit.addGate(dd::Xmat, 28_pc, 43);
//    circuit.addGate(dd::Xmat, 32);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Xmat, 47);
//    circuit.addGate(dd::Xmat, 0_pc, 46);
//    circuit.addGate(dd::Xmat, 4_pc, 30);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Xmat, 28_pc, 33);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Zmat, 7_pc, 23);
//    circuit.addGate(dd::Xmat, 37_pc, 17);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Xmat, 23_pc, 44);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Zmat, 9_pc, 17);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Xmat, 16_pc, 18);
//    circuit.addGate(dd::Hmat, 34);
//    circuit.addGate(dd::Xmat, 17_pc, 0);
//    circuit.addGate(dd::Ymat, 1_pc, 3);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Hmat, 29);
//    circuit.addGate(dd::Zmat, 13_pc, 12);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Hmat, 47);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Ymat, 27_pc, 42);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Xmat, 26_pc, 42);
//    circuit.addGate(dd::Zmat, 11_pc, 34);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Ymat, 21_pc, 25);
//    circuit.addGate(dd::Ymat, 40_pc, 37);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Ymat, 9_pc, 2);
//    circuit.addGate(dd::Zmat, 46_pc, 18);
//    circuit.addGate(dd::Xmat, 3_pc, 49);
//    circuit.addGate(dd::Xmat, 45);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Ymat, 45_pc, 24);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Zmat, 24_pc, 17);
//    circuit.addGate(dd::Xmat, 16_pc, 42);
//    circuit.addGate(dd::Xmat, 7_pc, 31);
//    circuit.addGate(dd::Zmat, 0_pc, 25);
//    circuit.addGate(dd::Xmat, 35_pc, 36);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Zmat, 47);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Ymat, 4_pc, 13);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Xmat, 47_pc, 35);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Zmat, 32_pc, 40);
//    circuit.addGate(dd::Hmat, 3);
//    circuit.addGate(dd::Zmat, 43_pc, 6);
//    circuit.addGate(dd::Ymat, 27_pc, 17);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Xmat, 47_pc, 44);
//    circuit.addGate(dd::Ymat, 26_pc, 9);
//    circuit.addGate(dd::Ymat, 15_pc, 6);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Zmat, 42_pc, 32);
//    circuit.addGate(dd::Ymat, 20_pc, 7);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Ymat, 15_pc, 21);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Zmat, 2_pc, 29);
//    circuit.addGate(dd::Xmat, 28_pc, 23);
//    circuit.addGate(dd::Zmat, 17_pc, 37);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Ymat, 27_pc, 35);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Xmat, 38_pc, 45);
//    circuit.addGate(dd::Ymat, 32_pc, 24);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Ymat, 31_pc, 11);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Zmat, 41_pc, 17);
//    circuit.addGate(dd::Smat, 35);
//    circuit.addGate(dd::Ymat, 41_pc, 21);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Xmat, 43_pc, 26);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Ymat, 33_pc, 44);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 51 qubis, containing 153 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_20) {
//    dd::QuantumCircuit circuit(51);
//
//    circuit.addGate(dd::Xmat, 12_pc, 16);
//    circuit.addGate(dd::Xmat, 47_pc, 17);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Xmat, 38_pc, 3);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Zmat, 13_pc, 38);
//    circuit.addGate(dd::Ymat, 27_pc, 46);
//    circuit.addGate(dd::Ymat, 41_pc, 3);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Zmat, 16);
//    circuit.addGate(dd::Ymat, 3_pc, 39);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Xmat, 4_pc, 2);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Xmat, 16_pc, 29);
//    circuit.addGate(dd::Xmat, 45_pc, 4);
//    circuit.addGate(dd::Ymat, 4_pc, 29);
//    circuit.addGate(dd::Zmat, 14_pc, 38);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Zmat, 3_pc, 19);
//    circuit.addGate(dd::Ymat, 17_pc, 3);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Xmat, 8_pc, 23);
//    circuit.addGate(dd::Xmat, 17_pc, 43);
//    circuit.addGate(dd::Zmat, 47_pc, 15);
//    circuit.addGate(dd::Ymat, 3_pc, 44);
//    circuit.addGate(dd::Xmat, 18_pc, 7);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Ymat, 37_pc, 39);
//    circuit.addGate(dd::Smat, 35);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Smat, 38);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Xmat, 38_pc, 14);
//    circuit.addGate(dd::Xmat, 48_pc, 4);
//    circuit.addGate(dd::Xmat, 45_pc, 39);
//    circuit.addGate(dd::Xmat, 17_pc, 16);
//    circuit.addGate(dd::Xmat, 16_pc, 35);
//    circuit.addGate(dd::Xmat, 9_pc, 0);
//    circuit.addGate(dd::Zmat, 42);
//    circuit.addGate(dd::Zmat, 29_pc, 25);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Ymat, 46_pc, 47);
//    circuit.addGate(dd::Xmat, 14_pc, 18);
//    circuit.addGate(dd::Ymat, 15_pc, 28);
//    circuit.addGate(dd::Ymat, 30);
//    circuit.addGate(dd::Zmat, 8_pc, 5);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Xmat, 41_pc, 32);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Ymat, 43_pc, 37);
//    circuit.addGate(dd::Xmat, 35_pc, 18);
//    circuit.addGate(dd::Xmat, 3_pc, 23);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Zmat, 15_pc, 2);
//    circuit.addGate(dd::Zmat, 14_pc, 25);
//    circuit.addGate(dd::Ymat, 27_pc, 20);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Xmat, 42_pc, 43);
//    circuit.addGate(dd::Ymat, 20_pc, 17);
//    circuit.addGate(dd::Zmat, 33_pc, 18);
//    circuit.addGate(dd::Hmat, 3);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Smat, 48);
//    circuit.addGate(dd::Hmat, 48);
//    circuit.addGate(dd::Xmat, 24_pc, 15);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Zmat, 39_pc, 14);
//    circuit.addGate(dd::Ymat, 50_pc, 21);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Smat, 45);
//    circuit.addGate(dd::Ymat, 18_pc, 15);
//    circuit.addGate(dd::Smat, 27);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Xmat, 35);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Zmat, 19_pc, 21);
//    circuit.addGate(dd::Ymat, 0_pc, 14);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Ymat, 32);
//    circuit.addGate(dd::Xmat, 25_pc, 49);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Xmat, 25_pc, 8);
//    circuit.addGate(dd::Xmat, 17_pc, 16);
//    circuit.addGate(dd::Ymat, 31_pc, 19);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Smat, 50);
//    circuit.addGate(dd::Xmat, 22_pc, 23);
//    circuit.addGate(dd::Ymat, 29_pc, 46);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Xmat, 6_pc, 8);
//    circuit.addGate(dd::Zmat, 17_pc, 50);
//    circuit.addGate(dd::Ymat, 37_pc, 13);
//    circuit.addGate(dd::Ymat, 38);
//    circuit.addGate(dd::Xmat, 3_pc, 15);
//    circuit.addGate(dd::Ymat, 13_pc, 10);
//    circuit.addGate(dd::Zmat, 13_pc, 16);
//    circuit.addGate(dd::Ymat, 18_pc, 14);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Zmat, 15_pc, 39);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Ymat, 3_pc, 49);
//    circuit.addGate(dd::Xmat, 34_pc, 20);
//    circuit.addGate(dd::Zmat, 36_pc, 48);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Ymat, 30_pc, 0);
//    circuit.addGate(dd::Zmat, 1_pc, 43);
//    circuit.addGate(dd::Xmat, 2_pc, 13);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Zmat, 26_pc, 28);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Ymat, 44);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Ymat, 2_pc, 10);
//    circuit.addGate(dd::Ymat, 19_pc, 42);
//    circuit.addGate(dd::Ymat, 21_pc, 12);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Xmat, 3_pc, 15);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Zmat, 21_pc, 10);
//    circuit.addGate(dd::Xmat, 2_pc, 27);
//    circuit.addGate(dd::Ymat, 10_pc, 34);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Ymat, 32_pc, 28);
//    circuit.addGate(dd::Ymat, 41_pc, 25);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Xmat, 38_pc, 14);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 52 qubis, containing 156 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_21) {
//    dd::QuantumCircuit circuit(52);
//
//    circuit.addGate(dd::Ymat, 33);
//    circuit.addGate(dd::Xmat, 42_pc, 14);
//    circuit.addGate(dd::Zmat, 26_pc, 19);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Ymat, 37_pc, 19);
//    circuit.addGate(dd::Xmat, 43_pc, 11);
//    circuit.addGate(dd::Zmat, 29_pc, 47);
//    circuit.addGate(dd::Xmat, 29_pc, 37);
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Zmat, 30_pc, 7);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Ymat, 42);
//    circuit.addGate(dd::Zmat, 33_pc, 38);
//    circuit.addGate(dd::Xmat, 43_pc, 13);
//    circuit.addGate(dd::Ymat, 18_pc, 20);
//    circuit.addGate(dd::Xmat, 36_pc, 42);
//    circuit.addGate(dd::Ymat, 25_pc, 17);
//    circuit.addGate(dd::Zmat, 49_pc, 44);
//    circuit.addGate(dd::Zmat, 42_pc, 49);
//    circuit.addGate(dd::Zmat, 39_pc, 44);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Xmat, 50_pc, 26);
//    circuit.addGate(dd::Ymat, 44);
//    circuit.addGate(dd::Xmat, 43_pc, 27);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Zmat, 50_pc, 47);
//    circuit.addGate(dd::Smat, 46);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Xmat, 7_pc, 28);
//    circuit.addGate(dd::Ymat, 34_pc, 48);
//    circuit.addGate(dd::Zmat, 51_pc, 37);
//    circuit.addGate(dd::Ymat, 4_pc, 15);
//    circuit.addGate(dd::Zmat, 49_pc, 45);
//    circuit.addGate(dd::Zmat, 45);
//    circuit.addGate(dd::Ymat, 17_pc, 42);
//    circuit.addGate(dd::Xmat, 27_pc, 41);
//    circuit.addGate(dd::Ymat, 48_pc, 19);
//    circuit.addGate(dd::Ymat, 29_pc, 22);
//    circuit.addGate(dd::Zmat, 21_pc, 8);
//    circuit.addGate(dd::Ymat, 13_pc, 29);
//    circuit.addGate(dd::Xmat, 26_pc, 21);
//    circuit.addGate(dd::Ymat, 42_pc, 44);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Xmat, 0_pc, 21);
//    circuit.addGate(dd::Zmat, 25_pc, 34);
//    circuit.addGate(dd::Zmat, 20_pc, 44);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Zmat, 36_pc, 38);
//    circuit.addGate(dd::Ymat, 7_pc, 48);
//    circuit.addGate(dd::Xmat, 7_pc, 31);
//    circuit.addGate(dd::Ymat, 50_pc, 46);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Zmat, 48_pc, 10);
//    circuit.addGate(dd::Ymat, 30_pc, 44);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Ymat, 13_pc, 5);
//    circuit.addGate(dd::Smat, 15);
//    circuit.addGate(dd::Zmat, 38_pc, 44);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Xmat, 51_pc, 33);
//    circuit.addGate(dd::Zmat, 18_pc, 40);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Xmat, 32_pc, 1);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Zmat, 5_pc, 15);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Xmat, 20_pc, 28);
//    circuit.addGate(dd::Hmat, 46);
//    circuit.addGate(dd::Smat, 50);
//    circuit.addGate(dd::Smat, 32);
//    circuit.addGate(dd::Smat, 49);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Ymat, 44_pc, 33);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Ymat, 0);
//    circuit.addGate(dd::Ymat, 19_pc, 27);
//    circuit.addGate(dd::Zmat, 49_pc, 13);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Zmat, 3_pc, 49);
//    circuit.addGate(dd::Ymat, 22_pc, 29);
//    circuit.addGate(dd::Xmat, 41_pc, 17);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Zmat, 51_pc, 26);
//    circuit.addGate(dd::Ymat, 26_pc, 19);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Xmat, 33_pc, 45);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Xmat, 45_pc, 1);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Ymat, 30);
//    circuit.addGate(dd::Hmat, 47);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Zmat, 47);
//    circuit.addGate(dd::Zmat, 5);
//    circuit.addGate(dd::Ymat, 26_pc, 39);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Ymat, 21_pc, 15);
//    circuit.addGate(dd::Ymat, 34_pc, 27);
//    circuit.addGate(dd::Xmat, 40_pc, 22);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Ymat, 1_pc, 11);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Zmat, 32_pc, 43);
//    circuit.addGate(dd::Xmat, 48);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Ymat, 46);
//    circuit.addGate(dd::Xmat, 42_pc, 17);
//    circuit.addGate(dd::Zmat, 41_pc, 12);
//    circuit.addGate(dd::Zmat, 13_pc, 8);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Ymat, 28_pc, 3);
//    circuit.addGate(dd::Ymat, 51_pc, 46);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Zmat, 42_pc, 50);
//    circuit.addGate(dd::Xmat, 47_pc, 29);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Zmat, 23_pc, 43);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Ymat, 20_pc, 16);
//    circuit.addGate(dd::Xmat, 0_pc, 1);
//    circuit.addGate(dd::Smat, 38);
//    circuit.addGate(dd::Ymat, 38_pc, 25);
//    circuit.addGate(dd::Xmat, 32_pc, 50);
//    circuit.addGate(dd::Xmat, 42_pc, 39);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Ymat, 31_pc, 7);
//    circuit.addGate(dd::Xmat, 48_pc, 17);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Zmat, 38_pc, 4);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Ymat, 44_pc, 37);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Zmat, 43_pc, 2);
//    circuit.addGate(dd::Xmat, 50_pc, 27);
//    circuit.addGate(dd::Zmat, 30_pc, 42);
//    circuit.addGate(dd::Zmat, 47);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Zmat, 17_pc, 10);
//    circuit.addGate(dd::Zmat, 37);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Ymat, 16_pc, 25);
//    circuit.addGate(dd::Xmat, 23);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 53 qubis, containing 159 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_22) {
//    dd::QuantumCircuit circuit(53);
//
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Zmat, 36_pc, 33);
//    circuit.addGate(dd::Xmat, 15_pc, 45);
//    circuit.addGate(dd::Ymat, 28_pc, 27);
//    circuit.addGate(dd::Hmat, 42);
//    circuit.addGate(dd::Ymat, 3_pc, 37);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Ymat, 36_pc, 13);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Xmat, 41);
//    circuit.addGate(dd::Ymat, 3_pc, 45);
//    circuit.addGate(dd::Xmat, 0_pc, 32);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Xmat, 49_pc, 9);
//    circuit.addGate(dd::Ymat, 37_pc, 30);
//    circuit.addGate(dd::Ymat, 18_pc, 11);
//    circuit.addGate(dd::Zmat, 35_pc, 0);
//    circuit.addGate(dd::Zmat, 11_pc, 22);
//    circuit.addGate(dd::Xmat, 12_pc, 18);
//    circuit.addGate(dd::Zmat, 17);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Ymat, 5_pc, 27);
//    circuit.addGate(dd::Xmat, 51_pc, 39);
//    circuit.addGate(dd::Zmat, 45);
//    circuit.addGate(dd::Zmat, 41_pc, 34);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 38_pc, 34);
//    circuit.addGate(dd::Ymat, 31_pc, 7);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Ymat, 37_pc, 11);
//    circuit.addGate(dd::Zmat, 29_pc, 39);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Ymat, 45);
//    circuit.addGate(dd::Ymat, 21_pc, 36);
//    circuit.addGate(dd::Ymat, 32);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Xmat, 48_pc, 3);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Xmat, 0_pc, 1);
//    circuit.addGate(dd::Xmat, 23_pc, 48);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Ymat, 48);
//    circuit.addGate(dd::Ymat, 16_pc, 31);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Xmat, 6_pc, 38);
//    circuit.addGate(dd::Zmat, 35);
//    circuit.addGate(dd::Zmat, 35_pc, 10);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Xmat, 45);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Zmat, 43_pc, 33);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Xmat, 41_pc, 28);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Ymat, 1_pc, 43);
//    circuit.addGate(dd::Ymat, 36_pc, 51);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Ymat, 15_pc, 27);
//    circuit.addGate(dd::Smat, 50);
//    circuit.addGate(dd::Ymat, 13_pc, 51);
//    circuit.addGate(dd::Zmat, 5_pc, 12);
//    circuit.addGate(dd::Hmat, 46);
//    circuit.addGate(dd::Ymat, 19_pc, 39);
//    circuit.addGate(dd::Xmat, 45);
//    circuit.addGate(dd::Ymat, 43);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 10_pc, 38);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Ymat, 27_pc, 29);
//    circuit.addGate(dd::Xmat, 35_pc, 38);
//    circuit.addGate(dd::Ymat, 10_pc, 30);
//    circuit.addGate(dd::Hmat, 48);
//    circuit.addGate(dd::Zmat, 40_pc, 6);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Zmat, 0_pc, 26);
//    circuit.addGate(dd::Xmat, 16_pc, 26);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Zmat, 38_pc, 31);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Xmat, 35_pc, 30);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Zmat, 37_pc, 52);
//    circuit.addGate(dd::Zmat, 47_pc, 35);
//    circuit.addGate(dd::Ymat, 31_pc, 30);
//    circuit.addGate(dd::Xmat, 3_pc, 19);
//    circuit.addGate(dd::Ymat, 34_pc, 11);
//    circuit.addGate(dd::Smat, 46);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Ymat, 31_pc, 11);
//    circuit.addGate(dd::Zmat, 21_pc, 17);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Ymat, 21_pc, 45);
//    circuit.addGate(dd::Zmat, 6_pc, 18);
//    circuit.addGate(dd::Ymat, 12_pc, 40);
//    circuit.addGate(dd::Xmat, 25_pc, 31);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Xmat, 18_pc, 26);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Ymat, 42_pc, 12);
//    circuit.addGate(dd::Ymat, 22_pc, 17);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Ymat, 51);
//    circuit.addGate(dd::Zmat, 39_pc, 50);
//    circuit.addGate(dd::Ymat, 48);
//    circuit.addGate(dd::Smat, 50);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Ymat, 12_pc, 32);
//    circuit.addGate(dd::Xmat, 0_pc, 48);
//    circuit.addGate(dd::Zmat, 17_pc, 20);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Ymat, 30_pc, 47);
//    circuit.addGate(dd::Zmat, 23_pc, 50);
//    circuit.addGate(dd::Ymat, 30_pc, 6);
//    circuit.addGate(dd::Zmat, 18_pc, 12);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Zmat, 12_pc, 25);
//    circuit.addGate(dd::Ymat, 19_pc, 31);
//    circuit.addGate(dd::Xmat, 8_pc, 5);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Xmat, 40_pc, 45);
//    circuit.addGate(dd::Zmat, 49);
//    circuit.addGate(dd::Ymat, 39);
//    circuit.addGate(dd::Xmat, 0_pc, 42);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Xmat, 37_pc, 19);
//    circuit.addGate(dd::Zmat, 50_pc, 31);
//    circuit.addGate(dd::Xmat, 15_pc, 42);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Xmat, 47_pc, 49);
//    circuit.addGate(dd::Zmat, 16_pc, 14);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Ymat, 38_pc, 19);
//    circuit.addGate(dd::Zmat, 29);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 54 qubis, containing 162 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_23) {
//    dd::QuantumCircuit circuit(54);
//
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Zmat, 10_pc, 14);
//    circuit.addGate(dd::Xmat, 15_pc, 50);
//    circuit.addGate(dd::Ymat, 38_pc, 47);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Ymat, 25_pc, 2);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Ymat, 9_pc, 52);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Xmat, 51);
//    circuit.addGate(dd::Ymat, 12_pc, 35);
//    circuit.addGate(dd::Xmat, 36_pc, 41);
//    circuit.addGate(dd::Smat, 53);
//    circuit.addGate(dd::Xmat, 41);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Xmat, 41_pc, 10);
//    circuit.addGate(dd::Ymat, 27_pc, 52);
//    circuit.addGate(dd::Ymat, 49_pc, 38);
//    circuit.addGate(dd::Zmat, 35_pc, 48);
//    circuit.addGate(dd::Zmat, 51_pc, 12);
//    circuit.addGate(dd::Xmat, 18_pc, 37);
//    circuit.addGate(dd::Zmat, 46);
//    circuit.addGate(dd::Ymat, 42);
//    circuit.addGate(dd::Ymat, 52_pc, 44);
//    circuit.addGate(dd::Xmat, 9_pc, 43);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Zmat, 22_pc, 8);
//    circuit.addGate(dd::Smat, 48);
//    circuit.addGate(dd::Xmat, 6_pc, 43);
//    circuit.addGate(dd::Ymat, 42_pc, 43);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Ymat, 4_pc, 32);
//    circuit.addGate(dd::Zmat, 37_pc, 41);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Zmat, 50);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Ymat, 14_pc, 47);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Xmat, 11_pc, 53);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Xmat, 45_pc, 10);
//    circuit.addGate(dd::Xmat, 16_pc, 12);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Ymat, 23_pc, 28);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Xmat, 42_pc, 13);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Zmat, 49_pc, 50);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Zmat, 32_pc, 21);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Zmat, 49);
//    circuit.addGate(dd::Xmat, 23_pc, 4);
//    circuit.addGate(dd::Xmat, 33);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Ymat, 15_pc, 2);
//    circuit.addGate(dd::Ymat, 4_pc, 3);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Ymat, 9_pc, 52);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Ymat, 21_pc, 16);
//    circuit.addGate(dd::Zmat, 36_pc, 5);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Ymat, 15_pc, 0);
//    circuit.addGate(dd::Xmat, 45);
//    circuit.addGate(dd::Ymat, 48);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Xmat, 51_pc, 40);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 32_pc, 17);
//    circuit.addGate(dd::Xmat, 0_pc, 1);
//    circuit.addGate(dd::Ymat, 41_pc, 48);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Zmat, 1_pc, 11);
//    circuit.addGate(dd::Zmat, 5);
//    circuit.addGate(dd::Zmat, 46_pc, 30);
//    circuit.addGate(dd::Xmat, 52_pc, 12);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Zmat, 7_pc, 50);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Xmat, 16_pc, 14);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Smat, 46);
//    circuit.addGate(dd::Zmat, 0_pc, 48);
//    circuit.addGate(dd::Zmat, 8_pc, 15);
//    circuit.addGate(dd::Ymat, 10_pc, 33);
//    circuit.addGate(dd::Xmat, 35_pc, 42);
//    circuit.addGate(dd::Ymat, 52_pc, 17);
//    circuit.addGate(dd::Smat, 45);
//    circuit.addGate(dd::Hmat, 40);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Ymat, 34_pc, 31);
//    circuit.addGate(dd::Zmat, 35_pc, 14);
//    circuit.addGate(dd::Smat, 47);
//    circuit.addGate(dd::Ymat, 42);
//    circuit.addGate(dd::Ymat, 23_pc, 3);
//    circuit.addGate(dd::Zmat, 18_pc, 24);
//    circuit.addGate(dd::Ymat, 16_pc, 17);
//    circuit.addGate(dd::Xmat, 13_pc, 35);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Ymat, 41);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Xmat, 10_pc, 25);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Ymat, 20_pc, 1);
//    circuit.addGate(dd::Ymat, 38_pc, 40);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Ymat, 6);
//    circuit.addGate(dd::Zmat, 38_pc, 17);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Smat, 52);
//    circuit.addGate(dd::Xmat, 49);
//    circuit.addGate(dd::Ymat, 6_pc, 38);
//    circuit.addGate(dd::Xmat, 20_pc, 46);
//    circuit.addGate(dd::Zmat, 30_pc, 10);
//    circuit.addGate(dd::Zmat, 38);
//    circuit.addGate(dd::Ymat, 6_pc, 49);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 46_pc, 2);
//    circuit.addGate(dd::Zmat, 31_pc, 28);
//    circuit.addGate(dd::Ymat, 51);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Hmat, 10);
//    circuit.addGate(dd::Zmat, 10_pc, 2);
//    circuit.addGate(dd::Ymat, 8_pc, 36);
//    circuit.addGate(dd::Xmat, 26_pc, 22);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Xmat, 33_pc, 35);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Xmat, 26_pc, 9);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Xmat, 2_pc, 16);
//    circuit.addGate(dd::Zmat, 52_pc, 10);
//    circuit.addGate(dd::Xmat, 48_pc, 9);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Xmat, 14_pc, 39);
//    circuit.addGate(dd::Zmat, 4_pc, 26);
//    circuit.addGate(dd::Ymat, 43);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Ymat, 40_pc, 17);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Zmat, 38_pc, 39);
//    circuit.addGate(dd::Ymat, 17_pc, 32);
//    circuit.addGate(dd::Xmat, 18);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 55 qubis, containing 165 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_24) {
//    dd::QuantumCircuit circuit(55);
//
//    circuit.addGate(dd::Ymat, 38_pc, 39);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Ymat, 19_pc, 39);
//    circuit.addGate(dd::Ymat, 38_pc, 0);
//    circuit.addGate(dd::Ymat, 22_pc, 0);
//    circuit.addGate(dd::Ymat, 33_pc, 8);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Ymat, 1_pc, 41);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Smat, 42);
//    circuit.addGate(dd::Ymat, 17_pc, 16);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Ymat, 51_pc, 9);
//    circuit.addGate(dd::Xmat, 29_pc, 8);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Ymat, 8_pc, 40);
//    circuit.addGate(dd::Xmat, 37);
//    circuit.addGate(dd::Ymat, 24);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Ymat, 16_pc, 11);
//    circuit.addGate(dd::Ymat, 40_pc, 53);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Ymat, 37_pc, 35);
//    circuit.addGate(dd::Ymat, 43_pc, 38);
//    circuit.addGate(dd::Xmat, 10_pc, 14);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Xmat, 54_pc, 45);
//    circuit.addGate(dd::Zmat, 7_pc, 48);
//    circuit.addGate(dd::Xmat, 23_pc, 19);
//    circuit.addGate(dd::Zmat, 30_pc, 3);
//    circuit.addGate(dd::Zmat, 41_pc, 3);
//    circuit.addGate(dd::Ymat, 46);
//    circuit.addGate(dd::Ymat, 30_pc, 15);
//    circuit.addGate(dd::Xmat, 50_pc, 54);
//    circuit.addGate(dd::Smat, 40);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Zmat, 30_pc, 41);
//    circuit.addGate(dd::Ymat, 37_pc, 28);
//    circuit.addGate(dd::Xmat, 51);
//    circuit.addGate(dd::Ymat, 42_pc, 41);
//    circuit.addGate(dd::Xmat, 46);
//    circuit.addGate(dd::Zmat, 48);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Ymat, 42_pc, 51);
//    circuit.addGate(dd::Zmat, 47_pc, 37);
//    circuit.addGate(dd::Xmat, 23_pc, 21);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Xmat, 33);
//    circuit.addGate(dd::Xmat, 7_pc, 51);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Ymat, 23_pc, 22);
//    circuit.addGate(dd::Zmat, 46_pc, 13);
//    circuit.addGate(dd::Ymat, 47_pc, 31);
//    circuit.addGate(dd::Ymat, 19);
//    circuit.addGate(dd::Zmat, 40_pc, 11);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Zmat, 9_pc, 52);
//    circuit.addGate(dd::Xmat, 49_pc, 5);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Xmat, 8_pc, 6);
//    circuit.addGate(dd::Xmat, 25_pc, 7);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Xmat, 37_pc, 26);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Smat, 44);
//    circuit.addGate(dd::Xmat, 50_pc, 11);
//    circuit.addGate(dd::Smat, 32);
//    circuit.addGate(dd::Ymat, 39);
//    circuit.addGate(dd::Ymat, 51_pc, 25);
//    circuit.addGate(dd::Xmat, 51);
//    circuit.addGate(dd::Xmat, 33_pc, 45);
//    circuit.addGate(dd::Hmat, 54);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Smat, 40);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Ymat, 46_pc, 39);
//    circuit.addGate(dd::Ymat, 50_pc, 13);
//    circuit.addGate(dd::Ymat, 9_pc, 41);
//    circuit.addGate(dd::Ymat, 24);
//    circuit.addGate(dd::Zmat, 44_pc, 35);
//    circuit.addGate(dd::Xmat, 21_pc, 44);
//    circuit.addGate(dd::Smat, 40);
//    circuit.addGate(dd::Ymat, 26);
//    circuit.addGate(dd::Zmat, 49_pc, 21);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Zmat, 22_pc, 51);
//    circuit.addGate(dd::Ymat, 21_pc, 13);
//    circuit.addGate(dd::Ymat, 39);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Zmat, 44_pc, 37);
//    circuit.addGate(dd::Ymat, 10);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Ymat, 31_pc, 42);
//    circuit.addGate(dd::Ymat, 35_pc, 5);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Ymat, 22_pc, 12);
//    circuit.addGate(dd::Ymat, 39_pc, 0);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Xmat, 9_pc, 0);
//    circuit.addGate(dd::Smat, 45);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Zmat, 23_pc, 29);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Zmat, 36_pc, 2);
//    circuit.addGate(dd::Zmat, 22_pc, 41);
//    circuit.addGate(dd::Ymat, 52_pc, 5);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Zmat, 51);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Xmat, 24_pc, 27);
//    circuit.addGate(dd::Ymat, 2_pc, 19);
//    circuit.addGate(dd::Ymat, 32_pc, 4);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Zmat, 27_pc, 47);
//    circuit.addGate(dd::Ymat, 52);
//    circuit.addGate(dd::Hmat, 45);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Xmat, 42_pc, 7);
//    circuit.addGate(dd::Ymat, 21);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Zmat, 0_pc, 46);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Zmat, 31_pc, 28);
//    circuit.addGate(dd::Xmat, 26_pc, 53);
//    circuit.addGate(dd::Zmat, 30_pc, 46);
//    circuit.addGate(dd::Zmat, 42_pc, 28);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 34_pc, 45);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Xmat, 21_pc, 52);
//    circuit.addGate(dd::Zmat, 53_pc, 48);
//    circuit.addGate(dd::Ymat, 46_pc, 26);
//    circuit.addGate(dd::Ymat, 34_pc, 18);
//    circuit.addGate(dd::Xmat, 50_pc, 36);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Ymat, 27_pc, 22);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Ymat, 16_pc, 28);
//    circuit.addGate(dd::Xmat, 41_pc, 40);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Zmat, 53_pc, 13);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Ymat, 11);
//    circuit.addGate(dd::Ymat, 25_pc, 34);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Xmat, 37);
//    circuit.addGate(dd::Ymat, 40_pc, 8);
//    circuit.addGate(dd::Xmat, 36_pc, 40);
//    circuit.addGate(dd::Zmat, 30_pc, 20);
//    circuit.addGate(dd::Xmat, 20_pc, 30);
//    circuit.addGate(dd::Zmat, 4_pc, 1);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Xmat, 17_pc, 44);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 56 qubis, containing 168 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_25) {
//    dd::QuantumCircuit circuit(56);
//
//    circuit.addGate(dd::Xmat, 4_pc, 33);
//    circuit.addGate(dd::Xmat, 21_pc, 24);
//    circuit.addGate(dd::Zmat, 17);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Xmat, 10_pc, 9);
//    circuit.addGate(dd::Zmat, 46_pc, 9);
//    circuit.addGate(dd::Ymat, 21_pc, 3);
//    circuit.addGate(dd::Xmat, 49_pc, 26);
//    circuit.addGate(dd::Xmat, 37_pc, 29);
//    circuit.addGate(dd::Zmat, 43_pc, 40);
//    circuit.addGate(dd::Ymat, 18_pc, 50);
//    circuit.addGate(dd::Zmat, 13_pc, 10);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Hmat, 50);
//    circuit.addGate(dd::Xmat, 47_pc, 50);
//    circuit.addGate(dd::Xmat, 50_pc, 20);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Ymat, 41_pc, 6);
//    circuit.addGate(dd::Ymat, 39);
//    circuit.addGate(dd::Xmat, 17_pc, 22);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Xmat, 53);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Zmat, 14_pc, 11);
//    circuit.addGate(dd::Xmat, 17_pc, 21);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Zmat, 51);
//    circuit.addGate(dd::Xmat, 10_pc, 44);
//    circuit.addGate(dd::Xmat, 4_pc, 36);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Xmat, 10);
//    circuit.addGate(dd::Zmat, 8_pc, 42);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Xmat, 45_pc, 12);
//    circuit.addGate(dd::Zmat, 46);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Ymat, 20_pc, 16);
//    circuit.addGate(dd::Ymat, 4_pc, 9);
//    circuit.addGate(dd::Zmat, 55);
//    circuit.addGate(dd::Zmat, 9_pc, 24);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Zmat, 54_pc, 18);
//    circuit.addGate(dd::Ymat, 31_pc, 9);
//    circuit.addGate(dd::Ymat, 4_pc, 29);
//    circuit.addGate(dd::Ymat, 20_pc, 51);
//    circuit.addGate(dd::Ymat, 31_pc, 19);
//    circuit.addGate(dd::Xmat, 21_pc, 42);
//    circuit.addGate(dd::Ymat, 36_pc, 25);
//    circuit.addGate(dd::Zmat, 20_pc, 2);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Xmat, 19_pc, 17);
//    circuit.addGate(dd::Smat, 5);
//    circuit.addGate(dd::Zmat, 20_pc, 13);
//    circuit.addGate(dd::Smat, 47);
//    circuit.addGate(dd::Zmat, 34_pc, 3);
//    circuit.addGate(dd::Ymat, 44);
//    circuit.addGate(dd::Xmat, 54_pc, 34);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Ymat, 53_pc, 44);
//    circuit.addGate(dd::Hmat, 48);
//    circuit.addGate(dd::Zmat, 12_pc, 30);
//    circuit.addGate(dd::Xmat, 48_pc, 0);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Zmat, 27_pc, 51);
//    circuit.addGate(dd::Xmat, 55_pc, 42);
//    circuit.addGate(dd::Ymat, 8_pc, 7);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Xmat, 26_pc, 30);
//    circuit.addGate(dd::Ymat, 32_pc, 8);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Ymat, 46_pc, 19);
//    circuit.addGate(dd::Zmat, 46_pc, 43);
//    circuit.addGate(dd::Zmat, 22_pc, 33);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Xmat, 6_pc, 26);
//    circuit.addGate(dd::Zmat, 22_pc, 33);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Xmat, 41_pc, 23);
//    circuit.addGate(dd::Hmat, 9);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Ymat, 34);
//    circuit.addGate(dd::Xmat, 0_pc, 16);
//    circuit.addGate(dd::Xmat, 29_pc, 49);
//    circuit.addGate(dd::Xmat, 19_pc, 10);
//    circuit.addGate(dd::Ymat, 43_pc, 36);
//    circuit.addGate(dd::Ymat, 45_pc, 41);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Xmat, 20_pc, 47);
//    circuit.addGate(dd::Zmat, 47_pc, 33);
//    circuit.addGate(dd::Ymat, 33);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Xmat, 25_pc, 54);
//    circuit.addGate(dd::Smat, 24);
//    circuit.addGate(dd::Ymat, 7_pc, 42);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Zmat, 5_pc, 53);
//    circuit.addGate(dd::Xmat, 26_pc, 32);
//    circuit.addGate(dd::Zmat, 49_pc, 4);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Hmat, 41);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Zmat, 47);
//    circuit.addGate(dd::Zmat, 39_pc, 29);
//    circuit.addGate(dd::Zmat, 13_pc, 42);
//    circuit.addGate(dd::Zmat, 39_pc, 46);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Ymat, 16);
//    circuit.addGate(dd::Smat, 43);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Zmat, 47_pc, 20);
//    circuit.addGate(dd::Xmat, 52_pc, 4);
//    circuit.addGate(dd::Xmat, 0_pc, 35);
//    circuit.addGate(dd::Xmat, 28_pc, 10);
//    circuit.addGate(dd::Zmat, 16);
//    circuit.addGate(dd::Zmat, 50_pc, 6);
//    circuit.addGate(dd::Xmat, 32_pc, 52);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Zmat, 32_pc, 54);
//    circuit.addGate(dd::Zmat, 50_pc, 40);
//    circuit.addGate(dd::Xmat, 50);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Smat, 51);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Zmat, 46);
//    circuit.addGate(dd::Xmat, 47);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Ymat, 6_pc, 27);
//    circuit.addGate(dd::Xmat, 23_pc, 7);
//    circuit.addGate(dd::Xmat, 53);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Xmat, 50_pc, 54);
//    circuit.addGate(dd::Ymat, 3_pc, 32);
//    circuit.addGate(dd::Smat, 45);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Xmat, 19_pc, 34);
//    circuit.addGate(dd::Xmat, 47);
//    circuit.addGate(dd::Xmat, 52);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Xmat, 46_pc, 5);
//    circuit.addGate(dd::Ymat, 46_pc, 34);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Ymat, 16_pc, 8);
//    circuit.addGate(dd::Xmat, 24_pc, 10);
//    circuit.addGate(dd::Xmat, 46_pc, 43);
//    circuit.addGate(dd::Xmat, 45_pc, 44);
//    circuit.addGate(dd::Zmat, 42_pc, 28);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Hmat, 42);
//    circuit.addGate(dd::Xmat, 35_pc, 18);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Ymat, 3_pc, 18);
//    circuit.addGate(dd::Smat, 47);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 57 qubis, containing 171 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_26) {
//    dd::QuantumCircuit circuit(57);
//
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Ymat, 15_pc, 23);
//    circuit.addGate(dd::Xmat, 53);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Zmat, 52);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 32_pc, 4);
//    circuit.addGate(dd::Ymat, 44_pc, 12);
//    circuit.addGate(dd::Zmat, 34_pc, 21);
//    circuit.addGate(dd::Hmat, 43);
//    circuit.addGate(dd::Ymat, 18_pc, 51);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Zmat, 42);
//    circuit.addGate(dd::Zmat, 54_pc, 28);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Smat, 56);
//    circuit.addGate(dd::Zmat, 44_pc, 13);
//    circuit.addGate(dd::Hmat, 6);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Ymat, 24_pc, 25);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Smat, 54);
//    circuit.addGate(dd::Zmat, 26_pc, 4);
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Xmat, 38_pc, 37);
//    circuit.addGate(dd::Xmat, 37_pc, 41);
//    circuit.addGate(dd::Ymat, 4_pc, 50);
//    circuit.addGate(dd::Zmat, 34_pc, 44);
//    circuit.addGate(dd::Zmat, 50_pc, 13);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Ymat, 8_pc, 52);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Xmat, 39_pc, 48);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Ymat, 14_pc, 53);
//    circuit.addGate(dd::Zmat, 41);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Ymat, 37_pc, 39);
//    circuit.addGate(dd::Ymat, 48_pc, 18);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Smat, 35);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Ymat, 25_pc, 19);
//    circuit.addGate(dd::Zmat, 48_pc, 34);
//    circuit.addGate(dd::Zmat, 6_pc, 42);
//    circuit.addGate(dd::Smat, 42);
//    circuit.addGate(dd::Zmat, 55);
//    circuit.addGate(dd::Ymat, 24_pc, 48);
//    circuit.addGate(dd::Xmat, 1_pc, 47);
//    circuit.addGate(dd::Ymat, 34_pc, 24);
//    circuit.addGate(dd::Zmat, 55_pc, 38);
//    circuit.addGate(dd::Xmat, 38);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Zmat, 26_pc, 16);
//    circuit.addGate(dd::Xmat, 9_pc, 1);
//    circuit.addGate(dd::Xmat, 27_pc, 8);
//    circuit.addGate(dd::Xmat, 1);
//    circuit.addGate(dd::Xmat, 31);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Ymat, 12_pc, 48);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Smat, 13);
//    circuit.addGate(dd::Hmat, 55);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Smat, 26);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Zmat, 35_pc, 40);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Hmat, 29);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Xmat, 38_pc, 3);
//    circuit.addGate(dd::Smat, 44);
//    circuit.addGate(dd::Xmat, 53);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Zmat, 53_pc, 15);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Ymat, 25_pc, 20);
//    circuit.addGate(dd::Zmat, 48_pc, 40);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Xmat, 46_pc, 18);
//    circuit.addGate(dd::Xmat, 21_pc, 17);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Zmat, 32);
//    circuit.addGate(dd::Xmat, 11_pc, 3);
//    circuit.addGate(dd::Zmat, 23_pc, 31);
//    circuit.addGate(dd::Xmat, 14_pc, 11);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 45_pc, 52);
//    circuit.addGate(dd::Ymat, 28_pc, 11);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Xmat, 45_pc, 20);
//    circuit.addGate(dd::Xmat, 17_pc, 24);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Zmat, 26_pc, 45);
//    circuit.addGate(dd::Zmat, 13_pc, 47);
//    circuit.addGate(dd::Xmat, 18_pc, 12);
//    circuit.addGate(dd::Hmat, 22);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Xmat, 43_pc, 27);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Ymat, 7_pc, 10);
//    circuit.addGate(dd::Zmat, 25_pc, 37);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Smat, 53);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Ymat, 37_pc, 0);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Zmat, 27);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Zmat, 24_pc, 18);
//    circuit.addGate(dd::Zmat, 21_pc, 26);
//    circuit.addGate(dd::Zmat, 12);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Hmat, 7);
//    circuit.addGate(dd::Xmat, 0_pc, 23);
//    circuit.addGate(dd::Smat, 56);
//    circuit.addGate(dd::Xmat, 56);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Xmat, 6_pc, 30);
//    circuit.addGate(dd::Ymat, 50_pc, 30);
//    circuit.addGate(dd::Zmat, 1);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Ymat, 27_pc, 11);
//    circuit.addGate(dd::Smat, 50);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Zmat, 48_pc, 49);
//    circuit.addGate(dd::Ymat, 2_pc, 30);
//    circuit.addGate(dd::Zmat, 29_pc, 43);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Xmat, 32_pc, 2);
//    circuit.addGate(dd::Zmat, 52);
//    circuit.addGate(dd::Zmat, 3_pc, 38);
//    circuit.addGate(dd::Smat, 52);
//    circuit.addGate(dd::Ymat, 14_pc, 35);
//    circuit.addGate(dd::Ymat, 15_pc, 54);
//    circuit.addGate(dd::Zmat, 55_pc, 21);
//    circuit.addGate(dd::Zmat, 50);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Zmat, 38_pc, 28);
//    circuit.addGate(dd::Ymat, 9_pc, 1);
//    circuit.addGate(dd::Zmat, 12_pc, 23);
//    circuit.addGate(dd::Xmat, 26_pc, 1);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Ymat, 47_pc, 52);
//    circuit.addGate(dd::Zmat, 3_pc, 43);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Ymat, 39_pc, 50);
//    circuit.addGate(dd::Xmat, 10_pc, 16);
//    circuit.addGate(dd::Zmat, 36_pc, 15);
//    circuit.addGate(dd::Xmat, 22_pc, 47);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Xmat, 6_pc, 7);
//    circuit.addGate(dd::Ymat, 32_pc, 5);
//    circuit.addGate(dd::Xmat, 24_pc, 31);
//    circuit.addGate(dd::Ymat, 32_pc, 23);
//    circuit.addGate(dd::Zmat, 5);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 58 qubis, containing 174 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_27) {
//    dd::QuantumCircuit circuit(58);
//
//    circuit.addGate(dd::Zmat, 46);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Ymat, 57_pc, 24);
//    circuit.addGate(dd::Xmat, 53);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Zmat, 15);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Xmat, 0_pc, 31);
//    circuit.addGate(dd::Ymat, 9_pc, 4);
//    circuit.addGate(dd::Zmat, 24_pc, 25);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Ymat, 19_pc, 21);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Zmat, 44_pc, 27);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Zmat, 51_pc, 15);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Zmat, 52);
//    circuit.addGate(dd::Ymat, 3_pc, 56);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Zmat, 37_pc, 23);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Ymat, 43);
//    circuit.addGate(dd::Xmat, 49_pc, 42);
//    circuit.addGate(dd::Xmat, 53_pc, 12);
//    circuit.addGate(dd::Ymat, 7_pc, 31);
//    circuit.addGate(dd::Zmat, 21_pc, 31);
//    circuit.addGate(dd::Zmat, 40_pc, 3);
//    circuit.addGate(dd::Xmat, 48);
//    circuit.addGate(dd::Ymat, 46_pc, 17);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 55_pc, 6);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Ymat, 33_pc, 19);
//    circuit.addGate(dd::Zmat, 50);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Ymat, 55_pc, 19);
//    circuit.addGate(dd::Ymat, 9_pc, 55);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Hmat, 17);
//    circuit.addGate(dd::Xmat, 46);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Smat, 53);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Xmat, 55);
//    circuit.addGate(dd::Ymat, 57_pc, 2);
//    circuit.addGate(dd::Zmat, 8_pc, 44);
//    circuit.addGate(dd::Zmat, 24_pc, 54);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Ymat, 47_pc, 57);
//    circuit.addGate(dd::Hmat, 56);
//    circuit.addGate(dd::Zmat, 13_pc, 34);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Ymat, 22_pc, 40);
//    circuit.addGate(dd::Hmat, 48);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Xmat, 8);
//    circuit.addGate(dd::Xmat, 42_pc, 52);
//    circuit.addGate(dd::Xmat, 33_pc, 30);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Smat, 44);
//    circuit.addGate(dd::Ymat, 25_pc, 4);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Smat, 44);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Smat, 53);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Zmat, 46_pc, 37);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Hmat, 42);
//    circuit.addGate(dd::Xmat, 46);
//    circuit.addGate(dd::Xmat, 46);
//    circuit.addGate(dd::Xmat, 24_pc, 37);
//    circuit.addGate(dd::Smat, 25);
//    circuit.addGate(dd::Xmat, 47);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Zmat, 17_pc, 51);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Ymat, 23_pc, 21);
//    circuit.addGate(dd::Zmat, 32_pc, 6);
//    circuit.addGate(dd::Smat, 44);
//    circuit.addGate(dd::Xmat, 10_pc, 45);
//    circuit.addGate(dd::Hmat, 15);
//    circuit.addGate(dd::Xmat, 52);
//    circuit.addGate(dd::Smat, 55);
//    circuit.addGate(dd::Zmat, 48);
//    circuit.addGate(dd::Xmat, 15_pc, 48);
//    circuit.addGate(dd::Zmat, 11_pc, 42);
//    circuit.addGate(dd::Xmat, 48_pc, 23);
//    circuit.addGate(dd::Ymat, 55);
//    circuit.addGate(dd::Ymat, 7_pc, 42);
//    circuit.addGate(dd::Ymat, 49_pc, 57);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Xmat, 42_pc, 19);
//    circuit.addGate(dd::Xmat, 53_pc, 31);
//    circuit.addGate(dd::Ymat, 54);
//    circuit.addGate(dd::Zmat, 37_pc, 35);
//    circuit.addGate(dd::Zmat, 51_pc, 55);
//    circuit.addGate(dd::Xmat, 34_pc, 57);
//    circuit.addGate(dd::Hmat, 34);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Xmat, 43_pc, 10);
//    circuit.addGate(dd::Xmat, 26);
//    circuit.addGate(dd::Ymat, 57_pc, 25);
//    circuit.addGate(dd::Zmat, 25_pc, 33);
//    circuit.addGate(dd::Xmat, 54);
//    circuit.addGate(dd::Smat, 52);
//    circuit.addGate(dd::Smat, 20);
//    circuit.addGate(dd::Ymat, 26_pc, 27);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Zmat, 16);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Zmat, 37);
//    circuit.addGate(dd::Zmat, 24_pc, 52);
//    circuit.addGate(dd::Zmat, 2_pc, 45);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Smat, 3);
//    circuit.addGate(dd::Hmat, 47);
//    circuit.addGate(dd::Xmat, 42_pc, 37);
//    circuit.addGate(dd::Smat, 42);
//    circuit.addGate(dd::Xmat, 6);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Xmat, 25_pc, 15);
//    circuit.addGate(dd::Ymat, 6_pc, 1);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Zmat, 29_pc, 34);
//    circuit.addGate(dd::Ymat, 16_pc, 10);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Ymat, 15);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Zmat, 46_pc, 32);
//    circuit.addGate(dd::Ymat, 31_pc, 36);
//    circuit.addGate(dd::Zmat, 51_pc, 37);
//    circuit.addGate(dd::Hmat, 5);
//    circuit.addGate(dd::Xmat, 21_pc, 19);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Zmat, 15_pc, 47);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Ymat, 33_pc, 23);
//    circuit.addGate(dd::Ymat, 0_pc, 44);
//    circuit.addGate(dd::Zmat, 42_pc, 40);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Zmat, 30_pc, 16);
//    circuit.addGate(dd::Ymat, 5_pc, 45);
//    circuit.addGate(dd::Zmat, 40_pc, 8);
//    circuit.addGate(dd::Xmat, 46_pc, 47);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Ymat, 2_pc, 25);
//    circuit.addGate(dd::Zmat, 46_pc, 40);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Ymat, 9_pc, 19);
//    circuit.addGate(dd::Xmat, 49_pc, 33);
//    circuit.addGate(dd::Zmat, 46_pc, 44);
//    circuit.addGate(dd::Xmat, 42_pc, 47);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Zmat, 14);
//    circuit.addGate(dd::Xmat, 35_pc, 28);
//    circuit.addGate(dd::Ymat, 44_pc, 36);
//    circuit.addGate(dd::Xmat, 55_pc, 33);
//    circuit.addGate(dd::Ymat, 49_pc, 28);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Xmat, 16);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 59 qubis, containing 177 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_28) {
//    dd::QuantumCircuit circuit(59);
//
//    circuit.addGate(dd::Xmat, 40_pc, 31);
//    circuit.addGate(dd::Zmat, 26_pc, 17);
//    circuit.addGate(dd::Xmat, 32_pc, 11);
//    circuit.addGate(dd::Xmat, 53_pc, 44);
//    circuit.addGate(dd::Ymat, 20_pc, 24);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Xmat, 28_pc, 37);
//    circuit.addGate(dd::Hmat, 9);
//    circuit.addGate(dd::Xmat, 2_pc, 50);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Zmat, 11_pc, 22);
//    circuit.addGate(dd::Xmat, 11_pc, 30);
//    circuit.addGate(dd::Ymat, 44_pc, 52);
//    circuit.addGate(dd::Zmat, 31_pc, 3);
//    circuit.addGate(dd::Zmat, 24_pc, 7);
//    circuit.addGate(dd::Xmat, 50_pc, 7);
//    circuit.addGate(dd::Hmat, 4);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Smat, 58);
//    circuit.addGate(dd::Ymat, 4_pc, 15);
//    circuit.addGate(dd::Ymat, 40_pc, 55);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Xmat, 33_pc, 35);
//    circuit.addGate(dd::Xmat, 43_pc, 42);
//    circuit.addGate(dd::Ymat, 54);
//    circuit.addGate(dd::Zmat, 58);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Xmat, 29_pc, 8);
//    circuit.addGate(dd::Ymat, 24_pc, 55);
//    circuit.addGate(dd::Hmat, 51);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Xmat, 55_pc, 4);
//    circuit.addGate(dd::Xmat, 47_pc, 44);
//    circuit.addGate(dd::Hmat, 43);
//    circuit.addGate(dd::Ymat, 46);
//    circuit.addGate(dd::Zmat, 13_pc, 15);
//    circuit.addGate(dd::Xmat, 27_pc, 30);
//    circuit.addGate(dd::Ymat, 30_pc, 40);
//    circuit.addGate(dd::Ymat, 23);
//    circuit.addGate(dd::Hmat, 51);
//    circuit.addGate(dd::Ymat, 55);
//    circuit.addGate(dd::Zmat, 48_pc, 43);
//    circuit.addGate(dd::Zmat, 28_pc, 2);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Ymat, 58_pc, 41);
//    circuit.addGate(dd::Xmat, 16_pc, 24);
//    circuit.addGate(dd::Ymat, 51_pc, 47);
//    circuit.addGate(dd::Xmat, 44);
//    circuit.addGate(dd::Xmat, 39_pc, 14);
//    circuit.addGate(dd::Ymat, 22_pc, 48);
//    circuit.addGate(dd::Zmat, 56_pc, 12);
//    circuit.addGate(dd::Smat, 45);
//    circuit.addGate(dd::Zmat, 3_pc, 16);
//    circuit.addGate(dd::Smat, 12);
//    circuit.addGate(dd::Xmat, 14_pc, 1);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Ymat, 5_pc, 35);
//    circuit.addGate(dd::Ymat, 8);
//    circuit.addGate(dd::Zmat, 57_pc, 1);
//    circuit.addGate(dd::Hmat, 14);
//    circuit.addGate(dd::Hmat, 0);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Xmat, 54_pc, 49);
//    circuit.addGate(dd::Ymat, 4_pc, 26);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Zmat, 14);
//    circuit.addGate(dd::Xmat, 41);
//    circuit.addGate(dd::Ymat, 32_pc, 55);
//    circuit.addGate(dd::Xmat, 54_pc, 7);
//    circuit.addGate(dd::Zmat, 7_pc, 13);
//    circuit.addGate(dd::Smat, 50);
//    circuit.addGate(dd::Hmat, 44);
//    circuit.addGate(dd::Zmat, 52_pc, 17);
//    circuit.addGate(dd::Ymat, 27_pc, 58);
//    circuit.addGate(dd::Zmat, 48);
//    circuit.addGate(dd::Xmat, 51_pc, 48);
//    circuit.addGate(dd::Zmat, 41_pc, 56);
//    circuit.addGate(dd::Ymat, 52_pc, 46);
//    circuit.addGate(dd::Xmat, 55_pc, 16);
//    circuit.addGate(dd::Xmat, 35_pc, 51);
//    circuit.addGate(dd::Ymat, 44_pc, 26);
//    circuit.addGate(dd::Ymat, 53_pc, 54);
//    circuit.addGate(dd::Ymat, 47_pc, 13);
//    circuit.addGate(dd::Zmat, 6);
//    circuit.addGate(dd::Xmat, 51_pc, 10);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Xmat, 15);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Ymat, 13_pc, 49);
//    circuit.addGate(dd::Ymat, 20);
//    circuit.addGate(dd::Ymat, 14_pc, 41);
//    circuit.addGate(dd::Xmat, 34);
//    circuit.addGate(dd::Zmat, 18_pc, 44);
//    circuit.addGate(dd::Xmat, 37_pc, 35);
//    circuit.addGate(dd::Zmat, 43_pc, 42);
//    circuit.addGate(dd::Zmat, 3_pc, 18);
//    circuit.addGate(dd::Zmat, 0_pc, 42);
//    circuit.addGate(dd::Zmat, 49_pc, 55);
//    circuit.addGate(dd::Ymat, 14);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Ymat, 29_pc, 15);
//    circuit.addGate(dd::Xmat, 10_pc, 21);
//    circuit.addGate(dd::Xmat, 47_pc, 19);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Ymat, 47);
//    circuit.addGate(dd::Zmat, 31_pc, 52);
//    circuit.addGate(dd::Xmat, 52_pc, 55);
//    circuit.addGate(dd::Ymat, 18_pc, 36);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Ymat, 39_pc, 28);
//    circuit.addGate(dd::Hmat, 47);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Xmat, 3_pc, 35);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Xmat, 25);
//    circuit.addGate(dd::Xmat, 37_pc, 9);
//    circuit.addGate(dd::Zmat, 24_pc, 41);
//    circuit.addGate(dd::Xmat, 55_pc, 8);
//    circuit.addGate(dd::Ymat, 36_pc, 2);
//    circuit.addGate(dd::Xmat, 51_pc, 46);
//    circuit.addGate(dd::Xmat, 47);
//    circuit.addGate(dd::Zmat, 18_pc, 27);
//    circuit.addGate(dd::Xmat, 36_pc, 44);
//    circuit.addGate(dd::Xmat, 26_pc, 14);
//    circuit.addGate(dd::Ymat, 42_pc, 58);
//    circuit.addGate(dd::Ymat, 58_pc, 0);
//    circuit.addGate(dd::Hmat, 37);
//    circuit.addGate(dd::Ymat, 11_pc, 22);
//    circuit.addGate(dd::Smat, 40);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Zmat, 54);
//    circuit.addGate(dd::Zmat, 39);
//    circuit.addGate(dd::Ymat, 11_pc, 26);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Xmat, 50);
//    circuit.addGate(dd::Ymat, 15_pc, 3);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Hmat, 12);
//    circuit.addGate(dd::Zmat, 24_pc, 39);
//    circuit.addGate(dd::Zmat, 46_pc, 20);
//    circuit.addGate(dd::Xmat, 13);
//    circuit.addGate(dd::Xmat, 54);
//    circuit.addGate(dd::Xmat, 45_pc, 31);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Xmat, 35);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Xmat, 20);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Ymat, 49_pc, 36);
//    circuit.addGate(dd::Zmat, 58_pc, 54);
//    circuit.addGate(dd::Ymat, 51);
//    circuit.addGate(dd::Xmat, 56_pc, 3);
//    circuit.addGate(dd::Xmat, 0_pc, 45);
//    circuit.addGate(dd::Xmat, 15_pc, 3);
//    circuit.addGate(dd::Smat, 30);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 54_pc, 53);
//    circuit.addGate(dd::Smat, 18);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 16_pc, 9);
//    circuit.addGate(dd::Ymat, 44);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Zmat, 42_pc, 3);
//    circuit.addGate(dd::Hmat, 18);
//    circuit.addGate(dd::Zmat, 19_pc, 52);
//    circuit.addGate(dd::Xmat, 32_pc, 56);
//    circuit.addGate(dd::Ymat, 11);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 60 qubis, containing 180 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_29) {
//    dd::QuantumCircuit circuit(60);
//
//    circuit.addGate(dd::Ymat, 33_pc, 10);
//    circuit.addGate(dd::Ymat, 22_pc, 1);
//    circuit.addGate(dd::Smat, 59);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Xmat, 59_pc, 20);
//    circuit.addGate(dd::Zmat, 1_pc, 47);
//    circuit.addGate(dd::Hmat, 54);
//    circuit.addGate(dd::Hmat, 42);
//    circuit.addGate(dd::Zmat, 38_pc, 4);
//    circuit.addGate(dd::Xmat, 7_pc, 24);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Hmat, 9);
//    circuit.addGate(dd::Zmat, 26);
//    circuit.addGate(dd::Zmat, 17_pc, 24);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Xmat, 47_pc, 59);
//    circuit.addGate(dd::Smat, 33);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Hmat, 16);
//    circuit.addGate(dd::Ymat, 24_pc, 53);
//    circuit.addGate(dd::Xmat, 14_pc, 52);
//    circuit.addGate(dd::Ymat, 11_pc, 19);
//    circuit.addGate(dd::Zmat, 43_pc, 42);
//    circuit.addGate(dd::Smat, 16);
//    circuit.addGate(dd::Xmat, 13_pc, 40);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Xmat, 36);
//    circuit.addGate(dd::Zmat, 2);
//    circuit.addGate(dd::Ymat, 37_pc, 18);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Ymat, 52_pc, 54);
//    circuit.addGate(dd::Xmat, 29_pc, 20);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Xmat, 41_pc, 23);
//    circuit.addGate(dd::Hmat, 51);
//    circuit.addGate(dd::Zmat, 27_pc, 9);
//    circuit.addGate(dd::Xmat, 42_pc, 19);
//    circuit.addGate(dd::Xmat, 47_pc, 5);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Zmat, 19);
//    circuit.addGate(dd::Ymat, 48);
//    circuit.addGate(dd::Zmat, 21_pc, 49);
//    circuit.addGate(dd::Xmat, 40_pc, 14);
//    circuit.addGate(dd::Hmat, 23);
//    circuit.addGate(dd::Ymat, 58_pc, 56);
//    circuit.addGate(dd::Smat, 43);
//    circuit.addGate(dd::Xmat, 16_pc, 31);
//    circuit.addGate(dd::Ymat, 30_pc, 13);
//    circuit.addGate(dd::Xmat, 55);
//    circuit.addGate(dd::Xmat, 28);
//    circuit.addGate(dd::Xmat, 17_pc, 8);
//    circuit.addGate(dd::Ymat, 22_pc, 15);
//    circuit.addGate(dd::Ymat, 0_pc, 2);
//    circuit.addGate(dd::Zmat, 58_pc, 26);
//    circuit.addGate(dd::Hmat, 42);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Xmat, 9);
//    circuit.addGate(dd::Zmat, 38_pc, 18);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Ymat, 40_pc, 47);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Ymat, 48_pc, 31);
//    circuit.addGate(dd::Zmat, 23_pc, 1);
//    circuit.addGate(dd::Xmat, 11_pc, 54);
//    circuit.addGate(dd::Ymat, 4);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Zmat, 54);
//    circuit.addGate(dd::Ymat, 3_pc, 4);
//    circuit.addGate(dd::Ymat, 32_pc, 13);
//    circuit.addGate(dd::Ymat, 14_pc, 13);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Zmat, 53_pc, 38);
//    circuit.addGate(dd::Ymat, 24_pc, 17);
//    circuit.addGate(dd::Ymat, 40_pc, 6);
//    circuit.addGate(dd::Ymat, 55);
//    circuit.addGate(dd::Ymat, 55);
//    circuit.addGate(dd::Zmat, 6_pc, 4);
//    circuit.addGate(dd::Xmat, 39);
//    circuit.addGate(dd::Ymat, 44);
//    circuit.addGate(dd::Zmat, 36_pc, 49);
//    circuit.addGate(dd::Hmat, 48);
//    circuit.addGate(dd::Xmat, 57);
//    circuit.addGate(dd::Smat, 29);
//    circuit.addGate(dd::Zmat, 55);
//    circuit.addGate(dd::Xmat, 38_pc, 52);
//    circuit.addGate(dd::Xmat, 59_pc, 19);
//    circuit.addGate(dd::Ymat, 51);
//    circuit.addGate(dd::Hmat, 35);
//    circuit.addGate(dd::Ymat, 4_pc, 19);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Zmat, 55);
//    circuit.addGate(dd::Ymat, 45);
//    circuit.addGate(dd::Zmat, 9_pc, 1);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Xmat, 49);
//    circuit.addGate(dd::Xmat, 19_pc, 26);
//    circuit.addGate(dd::Zmat, 56_pc, 55);
//    circuit.addGate(dd::Ymat, 59_pc, 37);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Zmat, 50);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 37);
//    circuit.addGate(dd::Xmat, 30_pc, 4);
//    circuit.addGate(dd::Zmat, 46_pc, 24);
//    circuit.addGate(dd::Xmat, 43);
//    circuit.addGate(dd::Zmat, 39_pc, 46);
//    circuit.addGate(dd::Ymat, 37_pc, 42);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Xmat, 26_pc, 29);
//    circuit.addGate(dd::Ymat, 17);
//    circuit.addGate(dd::Xmat, 50);
//    circuit.addGate(dd::Xmat, 47_pc, 36);
//    circuit.addGate(dd::Xmat, 52_pc, 57);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Hmat, 19);
//    circuit.addGate(dd::Zmat, 56_pc, 5);
//    circuit.addGate(dd::Xmat, 41_pc, 50);
//    circuit.addGate(dd::Xmat, 12_pc, 13);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Xmat, 46_pc, 59);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Ymat, 2_pc, 42);
//    circuit.addGate(dd::Xmat, 49_pc, 8);
//    circuit.addGate(dd::Ymat, 4_pc, 40);
//    circuit.addGate(dd::Ymat, 22_pc, 18);
//    circuit.addGate(dd::Zmat, 30);
//    circuit.addGate(dd::Xmat, 51_pc, 15);
//    circuit.addGate(dd::Ymat, 53_pc, 47);
//    circuit.addGate(dd::Smat, 59);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Xmat, 56_pc, 17);
//    circuit.addGate(dd::Hmat, 53);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Hmat, 53);
//    circuit.addGate(dd::Zmat, 54_pc, 57);
//    circuit.addGate(dd::Ymat, 43_pc, 25);
//    circuit.addGate(dd::Xmat, 32);
//    circuit.addGate(dd::Xmat, 21_pc, 8);
//    circuit.addGate(dd::Zmat, 53);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Zmat, 58);
//    circuit.addGate(dd::Ymat, 52);
//    circuit.addGate(dd::Zmat, 45);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Zmat, 6_pc, 2);
//    circuit.addGate(dd::Smat, 56);
//    circuit.addGate(dd::Xmat, 47);
//    circuit.addGate(dd::Zmat, 48_pc, 43);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Xmat, 18);
//    circuit.addGate(dd::Xmat, 21_pc, 43);
//    circuit.addGate(dd::Ymat, 28_pc, 19);
//    circuit.addGate(dd::Zmat, 38);
//    circuit.addGate(dd::Zmat, 41_pc, 53);
//    circuit.addGate(dd::Zmat, 39_pc, 1);
//    circuit.addGate(dd::Ymat, 9_pc, 57);
//    circuit.addGate(dd::Xmat, 38);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Xmat, 22);
//    circuit.addGate(dd::Xmat, 57_pc, 5);
//    circuit.addGate(dd::Zmat, 16_pc, 3);
//    circuit.addGate(dd::Xmat, 52);
//    circuit.addGate(dd::Smat, 45);
//    circuit.addGate(dd::Zmat, 16);
//    circuit.addGate(dd::Xmat, 20_pc, 16);
//    circuit.addGate(dd::Ymat, 44_pc, 26);
//    circuit.addGate(dd::Smat, 57);
//    circuit.addGate(dd::Zmat, 11_pc, 38);
//    circuit.addGate(dd::Xmat, 35);
//    circuit.addGate(dd::Zmat, 52_pc, 30);
//    circuit.addGate(dd::Xmat, 14_pc, 20);
//    circuit.addGate(dd::Zmat, 18_pc, 56);
//    circuit.addGate(dd::Ymat, 55_pc, 28);
//    circuit.addGate(dd::Zmat, 12_pc, 17);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 61 qubis, containing 183 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_30) {
//    dd::QuantumCircuit circuit(61);
//
//    circuit.addGate(dd::Smat, 57);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Zmat, 11);
//    circuit.addGate(dd::Xmat, 51_pc, 20);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Ymat, 53_pc, 25);
//    circuit.addGate(dd::Xmat, 35_pc, 13);
//    circuit.addGate(dd::Ymat, 4_pc, 6);
//    circuit.addGate(dd::Zmat, 2_pc, 39);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Smat, 47);
//    circuit.addGate(dd::Zmat, 20_pc, 33);
//    circuit.addGate(dd::Xmat, 5);
//    circuit.addGate(dd::Ymat, 14_pc, 32);
//    circuit.addGate(dd::Ymat, 60_pc, 33);
//    circuit.addGate(dd::Xmat, 30);
//    circuit.addGate(dd::Zmat, 36_pc, 56);
//    circuit.addGate(dd::Xmat, 34_pc, 57);
//    circuit.addGate(dd::Zmat, 54);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Zmat, 43_pc, 60);
//    circuit.addGate(dd::Hmat, 24);
//    circuit.addGate(dd::Hmat, 58);
//    circuit.addGate(dd::Zmat, 58_pc, 12);
//    circuit.addGate(dd::Xmat, 45);
//    circuit.addGate(dd::Zmat, 22_pc, 46);
//    circuit.addGate(dd::Xmat, 21_pc, 39);
//    circuit.addGate(dd::Xmat, 32_pc, 15);
//    circuit.addGate(dd::Ymat, 32_pc, 17);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Zmat, 27_pc, 22);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Zmat, 17_pc, 7);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Smat, 22);
//    circuit.addGate(dd::Zmat, 0_pc, 23);
//    circuit.addGate(dd::Zmat, 38_pc, 49);
//    circuit.addGate(dd::Xmat, 5_pc, 43);
//    circuit.addGate(dd::Hmat, 59);
//    circuit.addGate(dd::Zmat, 23_pc, 33);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Xmat, 35_pc, 0);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Xmat, 27_pc, 31);
//    circuit.addGate(dd::Smat, 21);
//    circuit.addGate(dd::Xmat, 27_pc, 15);
//    circuit.addGate(dd::Ymat, 16_pc, 39);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Xmat, 42);
//    circuit.addGate(dd::Ymat, 19_pc, 16);
//    circuit.addGate(dd::Xmat, 47);
//    circuit.addGate(dd::Hmat, 54);
//    circuit.addGate(dd::Ymat, 20_pc, 46);
//    circuit.addGate(dd::Smat, 7);
//    circuit.addGate(dd::Zmat, 36_pc, 3);
//    circuit.addGate(dd::Smat, 19);
//    circuit.addGate(dd::Xmat, 58);
//    circuit.addGate(dd::Hmat, 11);
//    circuit.addGate(dd::Ymat, 17_pc, 44);
//    circuit.addGate(dd::Zmat, 21_pc, 31);
//    circuit.addGate(dd::Xmat, 24_pc, 37);
//    circuit.addGate(dd::Ymat, 25);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Xmat, 7_pc, 38);
//    circuit.addGate(dd::Hmat, 59);
//    circuit.addGate(dd::Ymat, 56_pc, 55);
//    circuit.addGate(dd::Ymat, 19_pc, 33);
//    circuit.addGate(dd::Xmat, 14_pc, 47);
//    circuit.addGate(dd::Xmat, 12_pc, 2);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Zmat, 4_pc, 11);
//    circuit.addGate(dd::Zmat, 58_pc, 2);
//    circuit.addGate(dd::Xmat, 59_pc, 41);
//    circuit.addGate(dd::Zmat, 47_pc, 27);
//    circuit.addGate(dd::Xmat, 32_pc, 54);
//    circuit.addGate(dd::Ymat, 40);
//    circuit.addGate(dd::Zmat, 53_pc, 4);
//    circuit.addGate(dd::Ymat, 22_pc, 10);
//    circuit.addGate(dd::Ymat, 15_pc, 4);
//    circuit.addGate(dd::Smat, 8);
//    circuit.addGate(dd::Xmat, 6_pc, 26);
//    circuit.addGate(dd::Hmat, 13);
//    circuit.addGate(dd::Hmat, 27);
//    circuit.addGate(dd::Ymat, 29);
//    circuit.addGate(dd::Zmat, 43_pc, 38);
//    circuit.addGate(dd::Xmat, 20_pc, 12);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Zmat, 47_pc, 33);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Xmat, 55_pc, 15);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Ymat, 57);
//    circuit.addGate(dd::Xmat, 47_pc, 6);
//    circuit.addGate(dd::Xmat, 39_pc, 60);
//    circuit.addGate(dd::Xmat, 31_pc, 47);
//    circuit.addGate(dd::Ymat, 21_pc, 51);
//    circuit.addGate(dd::Zmat, 51_pc, 27);
//    circuit.addGate(dd::Zmat, 23);
//    circuit.addGate(dd::Ymat, 55_pc, 23);
//    circuit.addGate(dd::Ymat, 27);
//    circuit.addGate(dd::Ymat, 56);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Zmat, 39_pc, 7);
//    circuit.addGate(dd::Zmat, 54_pc, 17);
//    circuit.addGate(dd::Xmat, 7_pc, 9);
//    circuit.addGate(dd::Hmat, 39);
//    circuit.addGate(dd::Zmat, 1_pc, 2);
//    circuit.addGate(dd::Hmat, 25);
//    circuit.addGate(dd::Smat, 55);
//    circuit.addGate(dd::Hmat, 52);
//    circuit.addGate(dd::Ymat, 29_pc, 39);
//    circuit.addGate(dd::Zmat, 47);
//    circuit.addGate(dd::Xmat, 40_pc, 46);
//    circuit.addGate(dd::Xmat, 54);
//    circuit.addGate(dd::Hmat, 55);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Zmat, 60);
//    circuit.addGate(dd::Xmat, 0_pc, 45);
//    circuit.addGate(dd::Zmat, 35);
//    circuit.addGate(dd::Ymat, 24);
//    circuit.addGate(dd::Ymat, 48);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Smat, 57);
//    circuit.addGate(dd::Zmat, 52_pc, 20);
//    circuit.addGate(dd::Ymat, 4_pc, 8);
//    circuit.addGate(dd::Zmat, 3);
//    circuit.addGate(dd::Zmat, 55_pc, 0);
//    circuit.addGate(dd::Xmat, 58_pc, 32);
//    circuit.addGate(dd::Zmat, 21);
//    circuit.addGate(dd::Zmat, 37);
//    circuit.addGate(dd::Hmat, 41);
//    circuit.addGate(dd::Xmat, 39_pc, 3);
//    circuit.addGate(dd::Ymat, 23_pc, 48);
//    circuit.addGate(dd::Xmat, 58_pc, 22);
//    circuit.addGate(dd::Xmat, 19);
//    circuit.addGate(dd::Ymat, 19_pc, 0);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Hmat, 56);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Smat, 14);
//    circuit.addGate(dd::Zmat, 56_pc, 50);
//    circuit.addGate(dd::Zmat, 13);
//    circuit.addGate(dd::Ymat, 44_pc, 48);
//    circuit.addGate(dd::Xmat, 50);
//    circuit.addGate(dd::Ymat, 48_pc, 58);
//    circuit.addGate(dd::Xmat, 18_pc, 30);
//    circuit.addGate(dd::Xmat, 27_pc, 14);
//    circuit.addGate(dd::Zmat, 35_pc, 54);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Xmat, 45_pc, 41);
//    circuit.addGate(dd::Ymat, 36_pc, 12);
//    circuit.addGate(dd::Ymat, 14_pc, 13);
//    circuit.addGate(dd::Zmat, 0_pc, 30);
//    circuit.addGate(dd::Xmat, 48_pc, 39);
//    circuit.addGate(dd::Zmat, 7_pc, 21);
//    circuit.addGate(dd::Zmat, 56_pc, 57);
//    circuit.addGate(dd::Zmat, 42_pc, 38);
//    circuit.addGate(dd::Zmat, 19_pc, 0);
//    circuit.addGate(dd::Zmat, 12_pc, 26);
//    circuit.addGate(dd::Zmat, 39_pc, 24);
//    circuit.addGate(dd::Ymat, 56_pc, 49);
//    circuit.addGate(dd::Zmat, 29_pc, 11);
//    circuit.addGate(dd::Xmat, 32_pc, 47);
//    circuit.addGate(dd::Ymat, 46_pc, 11);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Xmat, 9_pc, 26);
//    circuit.addGate(dd::Ymat, 38_pc, 24);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Ymat, 48);
//    circuit.addGate(dd::Xmat, 52_pc, 2);
//    circuit.addGate(dd::Hmat, 48);
//    circuit.addGate(dd::Zmat, 35);
//    circuit.addGate(dd::Xmat, 22_pc, 41);
//    circuit.addGate(dd::Xmat, 32_pc, 24);
//    circuit.addGate(dd::Xmat, 50_pc, 44);
//    circuit.addGate(dd::Smat, 9);
//    circuit.addGate(dd::Ymat, 15);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
//// Randomly generated circuit on 62 qubis, containing 186 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_31) {
//    dd::QuantumCircuit circuit(62);
//
//    circuit.addGate(dd::Smat, 37);
//    circuit.addGate(dd::Smat, 4);
//    circuit.addGate(dd::Hmat, 1);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Xmat, 35_pc, 6);
//    circuit.addGate(dd::Zmat, 51);
//    circuit.addGate(dd::Ymat, 25_pc, 47);
//    circuit.addGate(dd::Xmat, 12_pc, 23);
//    circuit.addGate(dd::Ymat, 12_pc, 41);
//    circuit.addGate(dd::Zmat, 16_pc, 57);
//    circuit.addGate(dd::Zmat, 51);
//    circuit.addGate(dd::Smat, 53);
//    circuit.addGate(dd::Zmat, 16_pc, 50);
//    circuit.addGate(dd::Xmat, 54);
//    circuit.addGate(dd::Ymat, 9_pc, 51);
//    circuit.addGate(dd::Ymat, 44_pc, 1);
//    circuit.addGate(dd::Xmat, 16);
//    circuit.addGate(dd::Zmat, 57_pc, 18);
//    circuit.addGate(dd::Xmat, 13_pc, 28);
//    circuit.addGate(dd::Zmat, 60);
//    circuit.addGate(dd::Zmat, 49);
//    circuit.addGate(dd::Zmat, 35_pc, 54);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Zmat, 53_pc, 6);
//    circuit.addGate(dd::Xmat, 21);
//    circuit.addGate(dd::Zmat, 14_pc, 30);
//    circuit.addGate(dd::Xmat, 41_pc, 49);
//    circuit.addGate(dd::Xmat, 47_pc, 33);
//    circuit.addGate(dd::Ymat, 2_pc, 37);
//    circuit.addGate(dd::Ymat, 61);
//    circuit.addGate(dd::Zmat, 33_pc, 0);
//    circuit.addGate(dd::Xmat, 24);
//    circuit.addGate(dd::Zmat, 50_pc, 4);
//    circuit.addGate(dd::Ymat, 13);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Zmat, 21_pc, 26);
//    circuit.addGate(dd::Zmat, 59_pc, 14);
//    circuit.addGate(dd::Xmat, 51_pc, 41);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Zmat, 7_pc, 27);
//    circuit.addGate(dd::Zmat, 36);
//    circuit.addGate(dd::Xmat, 40_pc, 35);
//    circuit.addGate(dd::Hmat, 47);
//    circuit.addGate(dd::Zmat, 22);
//    circuit.addGate(dd::Xmat, 48_pc, 30);
//    circuit.addGate(dd::Smat, 42);
//    circuit.addGate(dd::Xmat, 32_pc, 0);
//    circuit.addGate(dd::Ymat, 7_pc, 38);
//    circuit.addGate(dd::Smat, 2);
//    circuit.addGate(dd::Xmat, 38);
//    circuit.addGate(dd::Ymat, 15_pc, 32);
//    circuit.addGate(dd::Xmat, 17);
//    circuit.addGate(dd::Hmat, 38);
//    circuit.addGate(dd::Ymat, 24_pc, 3);
//    circuit.addGate(dd::Smat, 46);
//    circuit.addGate(dd::Zmat, 14_pc, 16);
//    circuit.addGate(dd::Smat, 23);
//    circuit.addGate(dd::Xmat, 37);
//    circuit.addGate(dd::Hmat, 18);
//    circuit.addGate(dd::Ymat, 16_pc, 44);
//    circuit.addGate(dd::Zmat, 47_pc, 9);
//    circuit.addGate(dd::Xmat, 47_pc, 58);
//    circuit.addGate(dd::Ymat, 60);
//    circuit.addGate(dd::Hmat, 44);
//    circuit.addGate(dd::Xmat, 58_pc, 49);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Ymat, 45_pc, 55);
//    circuit.addGate(dd::Ymat, 22_pc, 15);
//    circuit.addGate(dd::Xmat, 8_pc, 46);
//    circuit.addGate(dd::Xmat, 3_pc, 0);
//    circuit.addGate(dd::Hmat, 20);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Zmat, 5_pc, 14);
//    circuit.addGate(dd::Zmat, 24_pc, 60);
//    circuit.addGate(dd::Xmat, 25_pc, 43);
//    circuit.addGate(dd::Zmat, 44_pc, 39);
//    circuit.addGate(dd::Xmat, 42_pc, 38);
//    circuit.addGate(dd::Ymat, 53);
//    circuit.addGate(dd::Zmat, 52_pc, 40);
//    circuit.addGate(dd::Ymat, 34_pc, 17);
//    circuit.addGate(dd::Ymat, 23_pc, 25);
//    circuit.addGate(dd::Ymat, 48_pc, 41);
//    circuit.addGate(dd::Xmat, 4_pc, 52);
//    circuit.addGate(dd::Hmat, 35);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Ymat, 9);
//    circuit.addGate(dd::Zmat, 52_pc, 35);
//    circuit.addGate(dd::Xmat, 16_pc, 57);
//    circuit.addGate(dd::Xmat, 7);
//    circuit.addGate(dd::Hmat, 32);
//    circuit.addGate(dd::Zmat, 18_pc, 34);
//    circuit.addGate(dd::Smat, 36);
//    circuit.addGate(dd::Xmat, 52_pc, 38);
//    circuit.addGate(dd::Zmat, 5);
//    circuit.addGate(dd::Xmat, 14);
//    circuit.addGate(dd::Ymat, 2);
//    circuit.addGate(dd::Xmat, 28_pc, 35);
//    circuit.addGate(dd::Xmat, 5_pc, 4);
//    circuit.addGate(dd::Xmat, 36_pc, 28);
//    circuit.addGate(dd::Ymat, 60_pc, 16);
//    circuit.addGate(dd::Zmat, 21_pc, 9);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Ymat, 42_pc, 51);
//    circuit.addGate(dd::Ymat, 57);
//    circuit.addGate(dd::Ymat, 61);
//    circuit.addGate(dd::Hmat, 58);
//    circuit.addGate(dd::Zmat, 60_pc, 42);
//    circuit.addGate(dd::Zmat, 8_pc, 24);
//    circuit.addGate(dd::Xmat, 40_pc, 38);
//    circuit.addGate(dd::Hmat, 46);
//    circuit.addGate(dd::Zmat, 50_pc, 56);
//    circuit.addGate(dd::Hmat, 45);
//    circuit.addGate(dd::Smat, 39);
//    circuit.addGate(dd::Hmat, 36);
//    circuit.addGate(dd::Ymat, 32_pc, 0);
//    circuit.addGate(dd::Zmat, 43);
//    circuit.addGate(dd::Xmat, 51_pc, 61);
//    circuit.addGate(dd::Xmat, 40);
//    circuit.addGate(dd::Hmat, 35);
//    circuit.addGate(dd::Ymat, 28);
//    circuit.addGate(dd::Zmat, 18);
//    circuit.addGate(dd::Xmat, 23_pc, 48);
//    circuit.addGate(dd::Zmat, 24);
//    circuit.addGate(dd::Ymat, 18);
//    circuit.addGate(dd::Ymat, 36);
//    circuit.addGate(dd::Xmat, 11);
//    circuit.addGate(dd::Ymat, 10);
//    circuit.addGate(dd::Smat, 48);
//    circuit.addGate(dd::Zmat, 22_pc, 9);
//    circuit.addGate(dd::Ymat, 38_pc, 25);
//    circuit.addGate(dd::Zmat, 34);
//    circuit.addGate(dd::Zmat, 18_pc, 1);
//    circuit.addGate(dd::Xmat, 31_pc, 57);
//    circuit.addGate(dd::Zmat, 29);
//    circuit.addGate(dd::Zmat, 40);
//    circuit.addGate(dd::Hmat, 49);
//    circuit.addGate(dd::Xmat, 33_pc, 0);
//    circuit.addGate(dd::Ymat, 9_pc, 37);
//    circuit.addGate(dd::Xmat, 60_pc, 42);
//    circuit.addGate(dd::Xmat, 3);
//    circuit.addGate(dd::Ymat, 4_pc, 5);
//    circuit.addGate(dd::Zmat, 60);
//    circuit.addGate(dd::Hmat, 28);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Smat, 53);
//    circuit.addGate(dd::Zmat, 23_pc, 59);
//    circuit.addGate(dd::Zmat, 7);
//    circuit.addGate(dd::Ymat, 50_pc, 11);
//    circuit.addGate(dd::Xmat, 41);
//    circuit.addGate(dd::Ymat, 25_pc, 38);
//    circuit.addGate(dd::Xmat, 8_pc, 30);
//    circuit.addGate(dd::Xmat, 56_pc, 5);
//    circuit.addGate(dd::Zmat, 33_pc, 20);
//    circuit.addGate(dd::Zmat, 25);
//    circuit.addGate(dd::Xmat, 3_pc, 23);
//    circuit.addGate(dd::Ymat, 13_pc, 20);
//    circuit.addGate(dd::Ymat, 21_pc, 4);
//    circuit.addGate(dd::Zmat, 29_pc, 53);
//    circuit.addGate(dd::Xmat, 61_pc, 43);
//    circuit.addGate(dd::Zmat, 35_pc, 52);
//    circuit.addGate(dd::Zmat, 23_pc, 21);
//    circuit.addGate(dd::Zmat, 44_pc, 30);
//    circuit.addGate(dd::Zmat, 54_pc, 48);
//    circuit.addGate(dd::Zmat, 6_pc, 24);
//    circuit.addGate(dd::Zmat, 28_pc, 0);
//    circuit.addGate(dd::Ymat, 51_pc, 22);
//    circuit.addGate(dd::Zmat, 1_pc, 52);
//    circuit.addGate(dd::Xmat, 42_pc, 26);
//    circuit.addGate(dd::Ymat, 46_pc, 25);
//    circuit.addGate(dd::Ymat, 55);
//    circuit.addGate(dd::Xmat, 45_pc, 54);
//    circuit.addGate(dd::Ymat, 60_pc, 36);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Ymat, 54);
//    circuit.addGate(dd::Xmat, 59_pc, 7);
//    circuit.addGate(dd::Hmat, 30);
//    circuit.addGate(dd::Zmat, 57);
//    circuit.addGate(dd::Xmat, 39_pc, 52);
//    circuit.addGate(dd::Xmat, 44_pc, 24);
//    circuit.addGate(dd::Xmat, 16_pc, 27);
//    circuit.addGate(dd::Smat, 61);
//    circuit.addGate(dd::Ymat, 59);
//    circuit.addGate(dd::Hmat, 51);
//    circuit.addGate(dd::Xmat, 47_pc, 38);
//    circuit.addGate(dd::Ymat, 7_pc, 57);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}
//
// Randomly generated circuit on 63 qubis, containing 189 Clifford gates.
//TEST(LimTest, generatedCircuitLarge_32) {
//    dd::QuantumCircuit circuit(63);
//
//    circuit.addGate(dd::Zmat, 56);
//    circuit.addGate(dd::Ymat, 46_pc, 23);
//    circuit.addGate(dd::Hmat, 45);
//    circuit.addGate(dd::Xmat, 25_pc, 61);
//    circuit.addGate(dd::Smat, 57);
//    circuit.addGate(dd::Zmat, 42_pc, 1);
//    circuit.addGate(dd::Ymat, 40_pc, 25);
//    circuit.addGate(dd::Ymat, 37);
//    circuit.addGate(dd::Ymat, 41);
//    circuit.addGate(dd::Smat, 34);
//    circuit.addGate(dd::Ymat, 15_pc, 55);
//    circuit.addGate(dd::Ymat, 37_pc, 47);
//    circuit.addGate(dd::Xmat, 44_pc, 47);
//    circuit.addGate(dd::Zmat, 15_pc, 48);
//    circuit.addGate(dd::Zmat, 18_pc, 44);
//    circuit.addGate(dd::Zmat, 5);
//    circuit.addGate(dd::Ymat, 47_pc, 12);
//    circuit.addGate(dd::Xmat, 50_pc, 27);
//    circuit.addGate(dd::Zmat, 42_pc, 32);
//    circuit.addGate(dd::Zmat, 7_pc, 47);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Smat, 1);
//    circuit.addGate(dd::Smat, 17);
//    circuit.addGate(dd::Xmat, 61_pc, 34);
//    circuit.addGate(dd::Xmat, 9_pc, 11);
//    circuit.addGate(dd::Zmat, 4);
//    circuit.addGate(dd::Ymat, 31);
//    circuit.addGate(dd::Zmat, 8);
//    circuit.addGate(dd::Xmat, 27);
//    circuit.addGate(dd::Xmat, 51_pc, 16);
//    circuit.addGate(dd::Zmat, 30_pc, 37);
//    circuit.addGate(dd::Hmat, 54);
//    circuit.addGate(dd::Zmat, 52_pc, 30);
//    circuit.addGate(dd::Zmat, 38);
//    circuit.addGate(dd::Ymat, 58);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Xmat, 23_pc, 25);
//    circuit.addGate(dd::Hmat, 50);
//    circuit.addGate(dd::Xmat, 38);
//    circuit.addGate(dd::Zmat, 38);
//    circuit.addGate(dd::Zmat, 60_pc, 25);
//    circuit.addGate(dd::Ymat, 6_pc, 38);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Ymat, 1_pc, 57);
//    circuit.addGate(dd::Zmat, 57);
//    circuit.addGate(dd::Xmat, 17_pc, 59);
//    circuit.addGate(dd::Zmat, 44);
//    circuit.addGate(dd::Zmat, 20);
//    circuit.addGate(dd::Hmat, 56);
//    circuit.addGate(dd::Xmat, 51_pc, 40);
//    circuit.addGate(dd::Ymat, 44_pc, 33);
//    circuit.addGate(dd::Smat, 61);
//    circuit.addGate(dd::Zmat, 0_pc, 6);
//    circuit.addGate(dd::Zmat, 40_pc, 1);
//    circuit.addGate(dd::Smat, 38);
//    circuit.addGate(dd::Zmat, 27_pc, 57);
//    circuit.addGate(dd::Zmat, 4_pc, 27);
//    circuit.addGate(dd::Xmat, 15_pc, 40);
//    circuit.addGate(dd::Ymat, 22);
//    circuit.addGate(dd::Zmat, 46_pc, 35);
//    circuit.addGate(dd::Ymat, 33_pc, 7);
//    circuit.addGate(dd::Xmat, 0);
//    circuit.addGate(dd::Xmat, 9_pc, 49);
//    circuit.addGate(dd::Ymat, 0_pc, 7);
//    circuit.addGate(dd::Xmat, 10_pc, 60);
//    circuit.addGate(dd::Smat, 11);
//    circuit.addGate(dd::Xmat, 6_pc, 45);
//    circuit.addGate(dd::Hmat, 26);
//    circuit.addGate(dd::Ymat, 61);
//    circuit.addGate(dd::Xmat, 36_pc, 6);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Xmat, 42_pc, 40);
//    circuit.addGate(dd::Ymat, 45_pc, 7);
//    circuit.addGate(dd::Ymat, 2_pc, 5);
//    circuit.addGate(dd::Smat, 28);
//    circuit.addGate(dd::Hmat, 8);
//    circuit.addGate(dd::Ymat, 35);
//    circuit.addGate(dd::Zmat, 31);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Zmat, 55);
//    circuit.addGate(dd::Ymat, 28_pc, 9);
//    circuit.addGate(dd::Hmat, 50);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Ymat, 13_pc, 4);
//    circuit.addGate(dd::Hmat, 42);
//    circuit.addGate(dd::Xmat, 16_pc, 2);
//    circuit.addGate(dd::Smat, 41);
//    circuit.addGate(dd::Zmat, 39_pc, 52);
//    circuit.addGate(dd::Zmat, 44_pc, 41);
//    circuit.addGate(dd::Zmat, 49);
//    circuit.addGate(dd::Ymat, 36_pc, 52);
//    circuit.addGate(dd::Zmat, 43_pc, 25);
//    circuit.addGate(dd::Zmat, 47);
//    circuit.addGate(dd::Ymat, 23_pc, 18);
//    circuit.addGate(dd::Ymat, 34_pc, 4);
//    circuit.addGate(dd::Hmat, 51);
//    circuit.addGate(dd::Zmat, 58_pc, 33);
//    circuit.addGate(dd::Ymat, 3);
//    circuit.addGate(dd::Hmat, 54);
//    circuit.addGate(dd::Ymat, 41);
//    circuit.addGate(dd::Hmat, 21);
//    circuit.addGate(dd::Xmat, 2);
//    circuit.addGate(dd::Zmat, 24_pc, 48);
//    circuit.addGate(dd::Smat, 10);
//    circuit.addGate(dd::Zmat, 12_pc, 2);
//    circuit.addGate(dd::Xmat, 10_pc, 47);
//    circuit.addGate(dd::Ymat, 19_pc, 24);
//    circuit.addGate(dd::Zmat, 15_pc, 55);
//    circuit.addGate(dd::Zmat, 10);
//    circuit.addGate(dd::Xmat, 54_pc, 25);
//    circuit.addGate(dd::Ymat, 19_pc, 37);
//    circuit.addGate(dd::Ymat, 35_pc, 10);
//    circuit.addGate(dd::Zmat, 22_pc, 17);
//    circuit.addGate(dd::Xmat, 26_pc, 8);
//    circuit.addGate(dd::Ymat, 25_pc, 59);
//    circuit.addGate(dd::Ymat, 9_pc, 0);
//    circuit.addGate(dd::Xmat, 10_pc, 25);
//    circuit.addGate(dd::Ymat, 49);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Ymat, 37_pc, 34);
//    circuit.addGate(dd::Zmat, 7_pc, 47);
//    circuit.addGate(dd::Zmat, 59);
//    circuit.addGate(dd::Smat, 31);
//    circuit.addGate(dd::Zmat, 25_pc, 53);
//    circuit.addGate(dd::Zmat, 53_pc, 24);
//    circuit.addGate(dd::Zmat, 47_pc, 44);
//    circuit.addGate(dd::Xmat, 4);
//    circuit.addGate(dd::Ymat, 1);
//    circuit.addGate(dd::Zmat, 36_pc, 53);
//    circuit.addGate(dd::Xmat, 37);
//    circuit.addGate(dd::Zmat, 33);
//    circuit.addGate(dd::Zmat, 62_pc, 6);
//    circuit.addGate(dd::Ymat, 59_pc, 41);
//    circuit.addGate(dd::Smat, 0);
//    circuit.addGate(dd::Zmat, 48_pc, 2);
//    circuit.addGate(dd::Ymat, 5);
//    circuit.addGate(dd::Zmat, 6_pc, 19);
//    circuit.addGate(dd::Ymat, 7_pc, 60);
//    circuit.addGate(dd::Xmat, 57_pc, 27);
//    circuit.addGate(dd::Ymat, 11_pc, 9);
//    circuit.addGate(dd::Ymat, 29_pc, 19);
//    circuit.addGate(dd::Zmat, 4_pc, 32);
//    circuit.addGate(dd::Xmat, 17_pc, 42);
//    circuit.addGate(dd::Hmat, 47);
//    circuit.addGate(dd::Ymat, 53_pc, 40);
//    circuit.addGate(dd::Ymat, 48_pc, 17);
//    circuit.addGate(dd::Xmat, 11_pc, 12);
//    circuit.addGate(dd::Ymat, 22_pc, 45);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Ymat, 30);
//    circuit.addGate(dd::Zmat, 7_pc, 60);
//    circuit.addGate(dd::Xmat, 29);
//    circuit.addGate(dd::Ymat, 50_pc, 21);
//    circuit.addGate(dd::Xmat, 43_pc, 50);
//    circuit.addGate(dd::Hmat, 33);
//    circuit.addGate(dd::Hmat, 46);
//    circuit.addGate(dd::Zmat, 5_pc, 56);
//    circuit.addGate(dd::Zmat, 5_pc, 32);
//    circuit.addGate(dd::Ymat, 42_pc, 13);
//    circuit.addGate(dd::Xmat, 42_pc, 25);
//    circuit.addGate(dd::Ymat, 56);
//    circuit.addGate(dd::Ymat, 12);
//    circuit.addGate(dd::Xmat, 61);
//    circuit.addGate(dd::Hmat, 31);
//    circuit.addGate(dd::Xmat, 12);
//    circuit.addGate(dd::Zmat, 17_pc, 4);
//    circuit.addGate(dd::Ymat, 7);
//    circuit.addGate(dd::Zmat, 39_pc, 48);
//    circuit.addGate(dd::Zmat, 23_pc, 24);
//    circuit.addGate(dd::Hmat, 2);
//    circuit.addGate(dd::Ymat, 62_pc, 42);
//    circuit.addGate(dd::Smat, 40);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Zmat, 19_pc, 59);
//    circuit.addGate(dd::Zmat, 0);
//    circuit.addGate(dd::Smat, 6);
//    circuit.addGate(dd::Ymat, 45_pc, 39);
//    circuit.addGate(dd::Smat, 62);
//    circuit.addGate(dd::Xmat, 23);
//    circuit.addGate(dd::Zmat, 36_pc, 41);
//    circuit.addGate(dd::Ymat, 15_pc, 24);
//    circuit.addGate(dd::Zmat, 28);
//    circuit.addGate(dd::Xmat, 45_pc, 32);
//    circuit.addGate(dd::Ymat, 33);
//    circuit.addGate(dd::Ymat, 37_pc, 4);
//    circuit.addGate(dd::Ymat, 43_pc, 5);
//    circuit.addGate(dd::Xmat, 44_pc, 52);
//    circuit.addGate(dd::Xmat, 57_pc, 35);
//    circuit.addGate(dd::Zmat, 34_pc, 12);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
//}

//
//
//TEST(LimTest, simpleCircuit1) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit2) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Ymat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit3) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Zmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit4) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Smat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit5) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit6) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit7) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit8) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit9) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit10) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit11) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit12) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit13) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit14) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit15) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit16) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit17) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit18) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit19) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Ymat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit20) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Ymat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit21) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Smat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit22) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Smat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit23) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit24) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Smat, 1);
//    c.addGate(dd::Smat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit25) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Smat, 0);
//    c.addGate(dd::Smat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit26) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Smat, 1);
//    c.addGate(dd::Smat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit27) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit28) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit29) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit30) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit31) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit32) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit33) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit34) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit35) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit36) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit37) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit38) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit39) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit40) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit41) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit42) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit43) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit44) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit45) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit46) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit47) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Tmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit48) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit49) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit50) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit51) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Tmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit52) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit53) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Tmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit54) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Tmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit55) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Tmat, 1_pc, 0);
//    c.addGate(dd::Tmat, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit56) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Tmat, 0_nc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit57) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0_nc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit58) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 0_nc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit59) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0_nc, 1);
//    c.addGate(dd::Tmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit60) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0_nc, 1);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Tmat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit61) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Tmat, 1_nc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit62) {
//    dd::QuantumCircuit c(2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Tmat, 1_nc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit63) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Tmat, 1_nc, 0);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit64) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Tmat, 2);
//    c.addGate(dd::Tmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_nc, 0);
//    c.addGate(dd::Zmat, 2_nc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit65) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit66) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit67) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 0_nc, 1_nc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit68) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit69) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 2_nc, 1_nc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit70) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 2_nc, 1_nc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit71) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 2_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit72) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 2_nc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit73) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 2_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit74) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit75) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit76) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Tmat, 0_pc, 1_nc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit77) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Tmat, 1_nc, 2_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit78) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Tmat, 0_pc, 1_nc, 2);
//    c.addGate(dd::Tmat, 1_nc, 2_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit79) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Tmat, 0_pc, 1_nc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit80) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Smat, 0_pc, 1);
//    c.addGate(dd::Smat, 1_pc, 2);
//    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Zmat, 1_nc, 2_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit81) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Tmat, 2_pc, 0);
//    c.addGate(dd::Tmat, 2_pc, 1_pc, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Tmat, 2_pc, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit82) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 2_pc, 0);
//    c.addGate(dd::Hmat, 0_pc, 2_pc, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Smat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1_pc, 2);
//    c.addGate(dd::Tmat, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit83) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 0_pc, 2_pc, 1);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit84) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Hmat, 1_pc, 2);
//    c.addGate(dd::Tmat, 2_pc, 1_pc, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit85) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2_pc, 1_pc, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0_pc, 2_pc, 1);
//    c.addGate(dd::Hmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 0_pc, 2_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit86) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit87) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 2_pc, 3);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit88) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit89) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Tmat, 3_pc, 0);
//    c.addGate(dd::Tmat, 3_pc, 2_pc, 1_pc, 0);
//    c.addGate(dd::Tmat, 0_pc, 1_nc, 2_nc, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Tmat, 1_pc, 2);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 2_nc, 1);
//    c.addGate(dd::Hmat, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit90) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 0_pc, 3);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Zmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 0_pc, 3);
//    c.addGate(dd::Hmat, 3_pc, 0);
//    c.addGate(dd::Hmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2_pc, 3);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit91) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 3_pc, 0);
//    c.addGate(dd::Zmat, 3_pc, 1);
//    c.addGate(dd::Zmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Tmat, 3);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit92) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Tmat, 2);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 2_pc, 3);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_1) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_2) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    //	c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_3) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    //	c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_4) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    //	c.addGate(dd::Xmat, 1_pc, 2);
//    //	c.addGate(dd::Xmat, 0_pc, 2);
//    //	c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_5) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    //	c.addGate(dd::Zmat, 0_pc, 1);
//    //	c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_6) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    //	c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_7) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    //	c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_8) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    //	c.addGate(dd::Xmat, 1_pc, 2);
//    //	c.addGate(dd::Xmat, 0_pc, 2);
//    //	c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    //	c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_9) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    //	c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit93_10) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    //	c.addGate(dd::Zmat, 0_pc, 1);
//    //	c.addGate(dd::Zmat, 1_pc, 3);
//    //	c.addGate(dd::Xmat, 1_pc, 2);
//    //	c.addGate(dd::Xmat, 0_pc, 2);
//    //	c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
//    c.addGate(dd::Hmat, 1_pc, 3);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit94) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Tmat, 2);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Tmat, 4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit95) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Tmat, 2);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Tmat, 4);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 4);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 4);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit96) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 3_pc, 4);
//    c.addGate(dd::Tmat, 4);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Tmat, 2);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 4);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit97) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 2_nc, 1);
//    c.addGate(dd::Tmat, 1);
//    c.addGate(dd::Hmat, 2_nc, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Tmat, 4);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Tmat, 4_pc, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Tmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Tmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit98) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 2_pc, 3);
//    c.addGate(dd::Zmat, 3_pc, 4);
//    c.addGate(dd::Zmat, 0_pc, 4);
//    c.addGate(dd::Xmat, 4_pc, 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Ymat, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit99) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 3_pc, 4);
//    c.addGate(dd::Zmat, 2_pc, 3);
//    c.addGate(dd::Zmat, 2_pc, 0);
//    c.addGate(dd::Zmat, 2_pc, 3);
//    c.addGate(dd::Zmat, 2_pc, 4);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Smat, 4);
//    c.addGate(dd::Tmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 3_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit100) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit101) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit102) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit103) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit104) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit105) {
//    dd::QuantumCircuit c(1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Tmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit107) {
//    dd::QuantumCircuit c(8);
//    c.addGate(dd::U3mat(1, 2, 3), 0);
//    c.addGate(dd::U3mat(1, 2, 3), 0_pc, 1);
//    c.addGate(dd::U3mat(1, 2, 3), 1_pc, 2);
//    c.addGate(dd::U3mat(1, 2, 3), 2_pc, 3);
//    c.addGate(dd::U3mat(1, 2, 3), 3_pc, 4);
//    c.addGate(dd::U3mat(1, 2, 3), 4_pc, 5);
//    c.addGate(dd::U3mat(1, 2, 3), 5_pc, 6);
//    c.addGate(dd::U3mat(1, 2, 3), 6_pc, 7);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit108) {
//    dd::QuantumCircuit c(8);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Hmat, 7);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit109) {
//    dd::QuantumCircuit c(8);
//    c.addGate(dd::U3mat(1, 2, 3), 0);
//    c.addGate(dd::U3mat(1, 2, 3), 1);
//    c.addGate(dd::U3mat(1, 2, 3), 2);
//    c.addGate(dd::U3mat(1, 2, 3), 3);
//    c.addGate(dd::U3mat(1, 2, 3), 4);
//    c.addGate(dd::U3mat(1, 2, 3), 5);
//    c.addGate(dd::U3mat(1, 2, 3), 6);
//    c.addGate(dd::U3mat(1, 2, 3), 7);
//    c.addGate(dd::U3mat(1, 2, 3), 0);
//    c.addGate(dd::U3mat(1, 2, 3), 1);
//    c.addGate(dd::U3mat(1, 2, 3), 2);
//    c.addGate(dd::U3mat(1, 2, 3), 3);
//    c.addGate(dd::U3mat(1, 2, 3), 4);
//    c.addGate(dd::U3mat(1, 2, 3), 5);
//    c.addGate(dd::U3mat(1, 2, 3), 6);
//    c.addGate(dd::U3mat(1, 2, 3), 7);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit110) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 1);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit111) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit112) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit113) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 3);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit114) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 3);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit115) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 3_pc, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit116) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Zmat, 1);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit117) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Ymat, 3);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit118) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 3_pc, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 3);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 1);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 0_pc, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Zmat, 1);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit119) {
//    dd::QuantumCircuit c(4);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 2);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Ymat, 0);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Xmat, 3);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Xmat, 2_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 0);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Ymat, 3);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 3);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Ymat, 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 3);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit120) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 0_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit121) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 0_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit122) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit123) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit124) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 0_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit125) {
//    dd::QuantumCircuit c(3);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 0_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit126) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Zmat, 0_pc, 1);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 3_pc, 4);
//    c.addGate(dd::Zmat, 2_pc, 3);
//    c.addGate(dd::Zmat, 2_pc, 0);
//    c.addGate(dd::Zmat, 2_pc, 3);
//    c.addGate(dd::Zmat, 2_pc, 4);
//    c.addGate(dd::Xmat, 0);
//    c.addGate(dd::Ymat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Smat, 4);
//    c.addGate(dd::Hmat, 3);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit127) {
//    dd::QuantumCircuit c(5);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Zmat, 0_pc, 2);
//    c.addGate(dd::Zmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 3_pc, 2);
//    c.addGate(dd::Zmat, 4_pc, 2);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit_vqe_10) {
//    dd::QuantumCircuit c(10);
//    c.addGate(dd::U3mat(2.68662123819055, 0, 0), 0);
//    c.addGate(dd::U3mat(-1.89057357852147, 0, 0), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(0.526156621282547, 0, 0), 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(-2.65877607637322, 0, 0), 3);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(2.28164362790185, 0, 0), 4);
//    c.addGate(dd::Xmat, 0_pc, 4);
//    c.addGate(dd::Xmat, 1_pc, 4);
//    c.addGate(dd::Xmat, 2_pc, 4);
//    c.addGate(dd::Xmat, 3_pc, 4);
//    c.addGate(dd::U3mat(-0.858823619363636, 0, 0), 5);
//    c.addGate(dd::Xmat, 0_pc, 5);
//    c.addGate(dd::Xmat, 1_pc, 5);
//    c.addGate(dd::Xmat, 2_pc, 5);
//    c.addGate(dd::Xmat, 3_pc, 5);
//    c.addGate(dd::Xmat, 4_pc, 5);
//    c.addGate(dd::U3mat(-1.79374665455828, 0, 0), 6);
//    c.addGate(dd::Xmat, 0_pc, 6);
//    c.addGate(dd::Xmat, 1_pc, 6);
//    c.addGate(dd::Xmat, 2_pc, 6);
//    c.addGate(dd::Xmat, 3_pc, 6);
//    c.addGate(dd::Xmat, 4_pc, 6);
//    c.addGate(dd::Xmat, 5_pc, 6);
//    c.addGate(dd::U3mat(-1.044215261399, 0, 0), 7);
//    c.addGate(dd::Xmat, 0_pc, 7);
//    c.addGate(dd::Xmat, 1_pc, 7);
//    c.addGate(dd::Xmat, 2_pc, 7);
//    c.addGate(dd::Xmat, 3_pc, 7);
//    c.addGate(dd::Xmat, 4_pc, 7);
//    c.addGate(dd::Xmat, 5_pc, 7);
//    c.addGate(dd::Xmat, 6_pc, 7);
//    c.addGate(dd::U3mat(1.57777927085946, 0, 0), 8);
//    c.addGate(dd::Xmat, 0_pc, 8);
//    c.addGate(dd::Xmat, 1_pc, 8);
//    c.addGate(dd::Xmat, 2_pc, 8);
//    c.addGate(dd::Xmat, 3_pc, 8);
//    c.addGate(dd::Xmat, 4_pc, 8);
//    c.addGate(dd::Xmat, 5_pc, 8);
//    c.addGate(dd::Xmat, 6_pc, 8);
//    c.addGate(dd::Xmat, 7_pc, 8);
//    c.addGate(dd::U3mat(0.0584568342741303, 0, 0), 9);
//    c.addGate(dd::Xmat, 0_pc, 9);
//    c.addGate(dd::U3mat(0.493785215150024, 0, 0), 0);
//    c.addGate(dd::Xmat, 1_pc, 9);
//    c.addGate(dd::U3mat(2.17528225837145, 0, 0), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 9);
//    c.addGate(dd::U3mat(2.38782953761232, 0, 0), 2);
//    c.addGate(dd::Xmat, 0_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 3_pc, 9);
//    c.addGate(dd::U3mat(-2.74456490781863, 0, 0), 3);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::Xmat, 1_pc, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 4_pc, 9);
//    c.addGate(dd::U3mat(-0.944693531787479, 0, 0), 4);
//    c.addGate(dd::Xmat, 0_pc, 4);
//    c.addGate(dd::Xmat, 1_pc, 4);
//    c.addGate(dd::Xmat, 2_pc, 4);
//    c.addGate(dd::Xmat, 3_pc, 4);
//    c.addGate(dd::Xmat, 5_pc, 9);
//    c.addGate(dd::U3mat(1.58084675679236, 0, 0), 5);
//    c.addGate(dd::Xmat, 0_pc, 5);
//    c.addGate(dd::Xmat, 1_pc, 5);
//    c.addGate(dd::Xmat, 2_pc, 5);
//    c.addGate(dd::Xmat, 3_pc, 5);
//    c.addGate(dd::Xmat, 4_pc, 5);
//    c.addGate(dd::Xmat, 6_pc, 9);
//    c.addGate(dd::U3mat(-1.23567451135838, 0, 0), 6);
//    c.addGate(dd::Xmat, 0_pc, 6);
//    c.addGate(dd::Xmat, 1_pc, 6);
//    c.addGate(dd::Xmat, 2_pc, 6);
//    c.addGate(dd::Xmat, 3_pc, 6);
//    c.addGate(dd::Xmat, 4_pc, 6);
//    c.addGate(dd::Xmat, 5_pc, 6);
//    c.addGate(dd::Xmat, 7_pc, 9);
//    c.addGate(dd::U3mat(-1.05552653486066, 0, 0), 7);
//    c.addGate(dd::Xmat, 0_pc, 7);
//    c.addGate(dd::Xmat, 1_pc, 7);
//    c.addGate(dd::Xmat, 2_pc, 7);
//    c.addGate(dd::Xmat, 3_pc, 7);
//    c.addGate(dd::Xmat, 4_pc, 7);
//    c.addGate(dd::Xmat, 5_pc, 7);
//    c.addGate(dd::Xmat, 6_pc, 7);
//    c.addGate(dd::Xmat, 8_pc, 9);
//    c.addGate(dd::U3mat(2.31217171104892, 0, 0), 8);
//    c.addGate(dd::Xmat, 0_pc, 8);
//    c.addGate(dd::Xmat, 1_pc, 8);
//    c.addGate(dd::Xmat, 2_pc, 8);
//    c.addGate(dd::Xmat, 3_pc, 8);
//    c.addGate(dd::Xmat, 4_pc, 8);
//    c.addGate(dd::Xmat, 5_pc, 8);
//    c.addGate(dd::Xmat, 6_pc, 8);
//    c.addGate(dd::Xmat, 7_pc, 8);
//    c.addGate(dd::U3mat(1.31263458235761, 0, 0), 9);
//    c.addGate(dd::Xmat, 0_pc, 9);
//    c.addGate(dd::U3mat(-2.40484784824733, 0, 0), 0);
//    c.addGate(dd::Xmat, 1_pc, 9);
//    c.addGate(dd::U3mat(0.412079032901195, 0, 0), 1);
//    c.addGate(dd::Xmat, 2_pc, 9);
//    c.addGate(dd::U3mat(-2.34348535750732, 0, 0), 2);
//    c.addGate(dd::Xmat, 3_pc, 9);
//    c.addGate(dd::U3mat(-3.04224930574056, 0, 0), 3);
//    c.addGate(dd::Xmat, 4_pc, 9);
//    c.addGate(dd::U3mat(-1.78983602234406, 0, 0), 4);
//    c.addGate(dd::Xmat, 5_pc, 9);
//    c.addGate(dd::U3mat(-2.03376426365639, 0, 0), 5);
//    c.addGate(dd::Xmat, 6_pc, 9);
//    c.addGate(dd::U3mat(1.5067179271741, 0, 0), 6);
//    c.addGate(dd::Xmat, 7_pc, 9);
//    c.addGate(dd::U3mat(0.371692355160145, 0, 0), 7);
//    c.addGate(dd::Xmat, 8_pc, 9);
//    c.addGate(dd::U3mat(1.41962968316013, 0, 0), 8);
//    c.addGate(dd::U3mat(0.515209311568382, 0, 0), 9);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit_graphstate_18) {
//    dd::QuantumCircuit c(18);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 3);
//    c.addGate(dd::Xmat, 0_pc, 3);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 5);
//    c.addGate(dd::Xmat, 4_pc, 5);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 7);
//    c.addGate(dd::Xmat, 6_pc, 7);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 8);
//    c.addGate(dd::Xmat, 5_pc, 8);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::Hmat, 9);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 10);
//    c.addGate(dd::Xmat, 7_pc, 10);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 10);
//    c.addGate(dd::Xmat, 9_pc, 10);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 12);
//    c.addGate(dd::Xmat, 11_pc, 12);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 13);
//    c.addGate(dd::Xmat, 12_pc, 13);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 14);
//    c.addGate(dd::Xmat, 9_pc, 14);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 14);
//    c.addGate(dd::Xmat, 13_pc, 14);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 15);
//    c.addGate(dd::Xmat, 1_pc, 15);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 15);
//    c.addGate(dd::Xmat, 2_pc, 15);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
//    c.addGate(dd::Xmat, 4_pc, 16);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
//    c.addGate(dd::Xmat, 8_pc, 16);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 17);
//    c.addGate(dd::Xmat, 6_pc, 17);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 17);
//    c.addGate(dd::Xmat, 11_pc, 17);
//    c.addGate(dd::Hmat, 1);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit_graphstate_24) {
//    dd::QuantumCircuit c(24);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 4);
//    c.addGate(dd::Xmat, 2_pc, 4);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 6);
//    c.addGate(dd::Xmat, 5_pc, 6);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 7);
//    c.addGate(dd::Xmat, 0_pc, 7);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 8);
//    c.addGate(dd::Xmat, 6_pc, 8);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 9);
//    c.addGate(dd::Xmat, 8_pc, 9);
//    c.addGate(dd::Hmat, 9);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 11);
//    c.addGate(dd::Xmat, 4_pc, 11);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 11);
//    c.addGate(dd::Xmat, 10_pc, 11);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 12);
//    c.addGate(dd::Xmat, 3_pc, 12);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 12);
//    c.addGate(dd::Xmat, 7_pc, 12);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 14);
//    c.addGate(dd::Xmat, 13_pc, 14);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
//    c.addGate(dd::Xmat, 13_pc, 16);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
//    c.addGate(dd::Xmat, 15_pc, 16);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 18);
//    c.addGate(dd::Xmat, 9_pc, 18);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 18);
//    c.addGate(dd::Xmat, 17_pc, 18);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 19);
//    c.addGate(dd::Xmat, 15_pc, 19);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 19);
//    c.addGate(dd::Xmat, 17_pc, 19);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 20);
//    c.addGate(dd::Xmat, 5_pc, 20);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 21);
//    c.addGate(dd::Xmat, 1_pc, 21);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 22);
//    c.addGate(dd::Xmat, 10_pc, 22);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 22);
//    c.addGate(dd::Xmat, 21_pc, 22);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 23);
//    c.addGate(dd::Xmat, 14_pc, 23);
//    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 23);
//    c.addGate(dd::Xmat, 20_pc, 23);
//    c.addGate(dd::Hmat, 2);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleCircuit_qaoa_12) {
//    dd::QuantumCircuit c(12);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Xmat, 3_pc, 4);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 4);
//    c.addGate(dd::Xmat, 3_pc, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Xmat, 1_pc, 5);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 5);
//    c.addGate(dd::Xmat, 1_pc, 5);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 1);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Xmat, 4_pc, 6);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 6);
//    c.addGate(dd::Xmat, 4_pc, 6);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 4);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::Xmat, 5_pc, 7);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 7);
//    c.addGate(dd::Xmat, 5_pc, 7);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 5);
//    c.addGate(dd::Xmat, 6_pc, 7);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 7);
//    c.addGate(dd::Xmat, 6_pc, 7);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 6);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 7);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::Xmat, 2_pc, 8);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 8);
//    c.addGate(dd::Xmat, 2_pc, 8);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 5);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 5);
//    c.addGate(dd::Xmat, 1_pc, 5);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 1);
//    c.addGate(dd::Xmat, 5_pc, 7);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 7);
//    c.addGate(dd::Xmat, 5_pc, 7);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 5);
//    c.addGate(dd::Hmat, 9);
//    c.addGate(dd::Xmat, 0_pc, 9);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 9);
//    c.addGate(dd::Xmat, 0_pc, 9);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 10);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 10);
//    c.addGate(dd::Xmat, 0_pc, 10);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 0);
//    c.addGate(dd::Xmat, 3_pc, 10);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 10);
//    c.addGate(dd::Xmat, 3_pc, 10);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 10);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 3);
//    c.addGate(dd::Xmat, 3_pc, 4);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 4);
//    c.addGate(dd::Xmat, 3_pc, 4);
//    c.addGate(dd::Xmat, 4_pc, 6);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 6);
//    c.addGate(dd::Xmat, 4_pc, 6);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 4);
//    c.addGate(dd::Xmat, 6_pc, 7);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 7);
//    c.addGate(dd::Xmat, 6_pc, 7);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 6);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 7);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 8_pc, 11);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 11);
//    c.addGate(dd::Xmat, 8_pc, 11);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 8);
//    c.addGate(dd::Xmat, 2_pc, 8);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 8);
//    c.addGate(dd::Xmat, 2_pc, 8);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 2);
//    c.addGate(dd::Xmat, 9_pc, 11);
//    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 11);
//    c.addGate(dd::Xmat, 9_pc, 11);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 11);
//    c.addGate(dd::Xmat, 8_pc, 11);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 11);
//    c.addGate(dd::Xmat, 8_pc, 11);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 8);
//    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 9);
//    c.addGate(dd::Xmat, 0_pc, 9);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 9);
//    c.addGate(dd::Xmat, 0_pc, 9);
//    c.addGate(dd::Xmat, 0_pc, 10);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 10);
//    c.addGate(dd::Xmat, 0_pc, 10);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 0);
//    c.addGate(dd::Xmat, 3_pc, 10);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 10);
//    c.addGate(dd::Xmat, 3_pc, 10);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 10);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 3);
//    c.addGate(dd::Xmat, 9_pc, 11);
//    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 11);
//    c.addGate(dd::Xmat, 9_pc, 11);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 11);
//    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 9);
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleClifford128) {
//    dd::QuantumCircuit c(18);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::Hmat, 9);
//    c.addGate(dd::Hmat, 10);
//    c.addGate(dd::Hmat, 11);
//    c.addGate(dd::Hmat, 12);
//    c.addGate(dd::Hmat, 13);
//    c.addGate(dd::Hmat, 14);
//    c.addGate(dd::Hmat, 15);
//    c.addGate(dd::Hmat, 16);
//    c.addGate(dd::Hmat, 17);
//    c.addGate(dd::Zmat, 0_pc,  2);
//    c.addGate(dd::Zmat, 1_pc,  14);
//    c.addGate(dd::Zmat, 3_pc,  10);
//    c.addGate(dd::Zmat, 4_pc,  13);
//    c.addGate(dd::Zmat, 10_pc, 11);
//    c.addGate(dd::Zmat, 11_pc, 14);
//    c.addGate(dd::Zmat, 17_pc, 16);
//    c.addGate(dd::Zmat, 6_pc,  1);
//    c.addGate(dd::Zmat, 7_pc,  15);
//    c.addGate(dd::Zmat, 8_pc,  10);
//    c.addGate(dd::Zmat, 11_pc, 1);
//    c.addGate(dd::Zmat, 15_pc, 3);
//    c.addGate(dd::Zmat, 14_pc, 5);
//    c.addGate(dd::Zmat, 16_pc, 2);
//    c.addGate(dd::Zmat, 13_pc, 6);
//    c.addGate(dd::Zmat, 2_pc,  17);
//    c.addGate(dd::Zmat, 3_pc,  16);
//    c.addGate(dd::Zmat, 4_pc,  7);
//    c.addGate(dd::Zmat, 1_pc,  2);
//    c.addGate(dd::Zmat, 6_pc,  3);
//    c.addGate(dd::Zmat, 3_pc,  6);
//    c.addGate(dd::Zmat, 16_pc, 14 );
//    c.addGate(dd::Zmat, 17_pc, 17);
//    c.addGate(dd::Zmat, 2_pc,  13);
//    c.addGate(dd::Zmat, 13_pc, 10);
//    c.addGate(dd::Zmat, 11_pc, 12);
//    c.addGate(dd::Zmat, 5_pc,  6);
//    c.addGate(dd::Zmat, 7_pc,  6);
//    c.addGate(dd::Zmat, 3_pc,  6);
//    c.addGate(dd::Zmat, 2_pc,  6);
//
//    simulateCircuitLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleClifford129) {
//    dd::QuantumCircuit c(19);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::Hmat, 9);
//    c.addGate(dd::Hmat, 10);
//    c.addGate(dd::Hmat, 11);
//    c.addGate(dd::Hmat, 12);
//    c.addGate(dd::Hmat, 13);
//    c.addGate(dd::Hmat, 14);
//    c.addGate(dd::Hmat, 15);
//    c.addGate(dd::Hmat, 16);
//    c.addGate(dd::Hmat, 17);
//    c.addGate(dd::Hmat, 18);
//    c.addGate(dd::Zmat, 0_pc,  2);
//    c.addGate(dd::Zmat, 1_pc,  14);
//    c.addGate(dd::Zmat, 3_pc,  10);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 4_pc,  13);
//    c.addGate(dd::Zmat, 10_pc, 11);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Zmat, 11_pc, 14);
//    c.addGate(dd::Zmat, 17_pc, 16);
//    c.addGate(dd::Hmat, 11);
//    c.addGate(dd::Zmat, 6_pc,  1);
//    c.addGate(dd::Zmat, 7_pc,  15);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Zmat, 8_pc,  10);
//    c.addGate(dd::Zmat, 11_pc, 1);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::Zmat, 15_pc, 3);
//    c.addGate(dd::Zmat, 14_pc, 5);
//    c.addGate(dd::Hmat, 14);
//    c.addGate(dd::Zmat, 16_pc, 2);
//    c.addGate(dd::Zmat, 13_pc, 6);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Zmat, 2_pc,  17);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Zmat, 3_pc,  16);
//    c.addGate(dd::Zmat, 4_pc,  7);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Zmat, 1_pc,  2);
//    c.addGate(dd::Zmat, 6_pc,  3);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Zmat, 3_pc,  6);
//    c.addGate(dd::Zmat, 16_pc, 14 );
//    c.addGate(dd::Zmat, 17_pc, 16);
//    c.addGate(dd::Hmat, 17);
//    c.addGate(dd::Zmat, 2_pc,  13);
//    c.addGate(dd::Zmat, 13_pc, 10);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Zmat, 11_pc, 12);
//    c.addGate(dd::Zmat, 5_pc,  6);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Zmat, 7_pc,  6);
//    c.addGate(dd::Zmat, 3_pc,  6);
//    c.addGate(dd::Zmat, 2_pc,  6);
//    c.addGate(dd::Hmat, 4);
//
//    simulateCircuitLIMDDGateByGate(c);
//}
//
//TEST(LimTest, simpleClifford130) {
//    dd::QuantumCircuit c(63);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::Hmat, 9);
//    c.addGate(dd::Hmat, 10);
//    c.addGate(dd::Hmat, 11);
//    c.addGate(dd::Hmat, 12);
//    c.addGate(dd::Hmat, 13);
//    c.addGate(dd::Hmat, 14);
//    c.addGate(dd::Hmat, 15);
//    c.addGate(dd::Hmat, 16);
//    c.addGate(dd::Hmat, 17);
//    c.addGate(dd::Hmat, 18);
//    c.addGate(dd::Hmat, 19);
//    c.addGate(dd::Hmat, 20);
//    c.addGate(dd::Hmat, 21);
//    c.addGate(dd::Hmat, 22);
//    c.addGate(dd::Hmat, 23);
//    c.addGate(dd::Hmat, 24);
//    c.addGate(dd::Hmat, 25);
//    c.addGate(dd::Hmat, 26);
//    c.addGate(dd::Hmat, 27);
//    c.addGate(dd::Hmat, 28);
//    c.addGate(dd::Hmat, 29);
//    c.addGate(dd::Hmat, 30);
//    c.addGate(dd::Hmat, 31);
//    c.addGate(dd::Hmat, 32);
//    c.addGate(dd::Hmat, 33);
//    c.addGate(dd::Hmat, 34);
//    c.addGate(dd::Hmat, 35);
//    c.addGate(dd::Hmat, 36);
//    c.addGate(dd::Hmat, 37);
//    c.addGate(dd::Hmat, 38);
//    c.addGate(dd::Hmat, 39);
//    c.addGate(dd::Hmat, 40);
//    c.addGate(dd::Hmat, 41);
//    c.addGate(dd::Hmat, 42);
//    c.addGate(dd::Hmat, 43);
//    c.addGate(dd::Hmat, 44);
//    c.addGate(dd::Hmat, 45);
//    c.addGate(dd::Hmat, 46);
//    c.addGate(dd::Hmat, 47);
//    c.addGate(dd::Hmat, 48);
//    c.addGate(dd::Hmat, 49);
//    c.addGate(dd::Hmat, 50);
//    c.addGate(dd::Hmat, 51);
//    c.addGate(dd::Hmat, 52);
//    c.addGate(dd::Hmat, 53);
//    c.addGate(dd::Hmat, 54);
//    c.addGate(dd::Hmat, 55);
//    c.addGate(dd::Hmat, 56);
//    c.addGate(dd::Hmat, 57);
//    c.addGate(dd::Hmat, 58);
//    c.addGate(dd::Hmat, 59);
//    c.addGate(dd::Hmat, 60);
//    c.addGate(dd::Hmat, 61);
//    c.addGate(dd::Hmat, 62);
//
//    simulateCircuitLIMDDGateByGate(c);
//}
//
//
//TEST(LimTest, basis_trotter_n4) {
//    dd::QuantumCircuit c(4);
//
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.08130614625631793
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.08130614625631793
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 2);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**-0.05102950815299322
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**0.05102950815299322
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: CZ**-0.048279591094340914
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 0.5), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4758602045), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.4758602045, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9758602045, 0), 1);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    // Gate: CZ**-0.022156912718971442
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.75), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.25), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4889215436), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.2389215436, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.7389215436, 0), 3);
//
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);
//
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 3);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 0);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 1);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.9500630905158097
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.9500630905158097
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: CZ**-0.013654184706660842
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4931729076), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4931729076, dd::PI * 1.0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9931729076, 0), 2);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    // Gate: CZ**-0.006328040119021747
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4961253835), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.9961253835), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4968359799), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5007105964, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0007105964, 0), 0);
//
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);
//
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 0);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 2);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**-0.5017530508495694
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**0.5017530508495694
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: CZ**-0.00046375097365492423
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5001274262), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0001274262), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4997681245), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4996406983, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9996406983, 0), 1);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    // Gate: CZ**-0.0004129506013584246
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.4998373235), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9998373235), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4997935247), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4999562012, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9999562012, dd::PI * 1.0), 3);
//
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);
//
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 3);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 0);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 1);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.4158482042253096
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.4158482042253096
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//
//    c.addGate(dd::Zmat, 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 1);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**0.08130614625631793
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**-0.08130614625631793
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//
//    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 1);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.05102950815299322
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.05102950815299322
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: CZ**-0.048279591094340914
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 0.5), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4758602045), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.4758602045, dd::PI * 1.0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9758602045, 0), 2);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    // Gate: CZ**-0.022156912718971442
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.75), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.25), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4889215436), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.2389215436, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.7389215436, 0), 0);
//
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);
//
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 0);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 2);
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 2);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**-0.9500630905158097
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**0.9500630905158097
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: CZ**-0.013654184706660842
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4931729076), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4931729076, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9931729076, 0), 1);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    // Gate: CZ**-0.006328040119021747
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4961253835), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.9961253835), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4968359799), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5007105964, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0007105964, 0), 3);
//
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);
//
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 3);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 0);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 1);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.5017530508495694
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.5017530508495694
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: CZ**-0.00046375097365492423
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5001274262), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0001274262), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4997681245), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4996406983, dd::PI * 1.0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9996406983, 0), 2);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    // Gate: CZ**-0.0004129506013584246
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.4998373235), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9998373235), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4997935247), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4999562012, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9999562012, dd::PI * 1.0), 0);
//
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);
//
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 0);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 2);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**-0.4158482042253096
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**0.4158482042253096
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    c.addGate(dd::Zmat, 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    c.addGate(dd::Zmat, 1);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 2);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.08130614625631793
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.08130614625631793
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 2);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**-0.05102950815299322
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**0.05102950815299322
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: CZ**-0.048279591094340914
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 0.5), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4758602045), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.4758602045, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9758602045, 0), 1);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    // Gate: CZ**-0.022156912718971442
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.75), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.25), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4889215436), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.2389215436, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.7389215436, 0), 3);
//
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);
//
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 3);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**-0.03270667647415345
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 0);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 1);
//    c.addGate(dd::Zmat, 2);
//    c.addGate(dd::Zmat, 1);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.9500630905158097
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.9500630905158097
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: CZ**-0.013654184706660842
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4931729076), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4931729076, dd::PI * 1.0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9931729076, 0), 2);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//
//    // Gate: CZ**-0.006328040119021747
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4961253835), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.9961253835), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4968359799), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5007105964, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0007105964, 0), 0);
//
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);
//
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 3);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 0);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 0);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//
//    // Gate: CZ**0.009295387491454189
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 3);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 2);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**-0.5017530508495694
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 0);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**0.5017530508495694
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: CZ**-0.00046375097365492423
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5001274262), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0001274262), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4997681245), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4996406983, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9996406983, 0), 1);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//
//    // Gate: CZ**-0.0004129506013584246
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.4998373235), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9998373235), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4997935247), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4999562012, 0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9999562012, dd::PI * 1.0), 3);
//
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);
//
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 0);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 0);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 3);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 3);
//
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//
//    // Gate: CZ**0.00043761426330885954
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
//    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
//    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
//    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);
//
//    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 0);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Zmat, 3);
//    c.addGate(dd::Zmat, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 1);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    // Gate: PhasedISWAP**-0.4158482042253096
//    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 3);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 3);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//
//    // Gate: PhasedISWAP**0.4158482042253096
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 1);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 1);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
//
//    // Gate: PhasedISWAP**-1.0
//    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
//    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
//
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 3);
//    c.addGate(dd::Xmat, 3_pc, 2);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 0_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 0);
//    c.addGate(dd::Xmat, 2_pc, 1);
//    c.addGate(dd::Xmat, 1_pc, 2);
//    c.addGate(dd::Xmat, 2_pc, 1);
//
//    simulateCircuitQMDDvsLIMDDGateByGate(c);
//}

TEST(LimTest, shorTest) {
    dd::QuantumCircuit circuit(18);

    circuit.addGate(dd::Xmat, 11);
    circuit.addGate(dd::Hmat, 7);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 32), 17_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 16), 17_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 14 / 8), 17_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 6 / 4), 17_pc, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 2 / 2), 17_pc, 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 32), 12);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 16), 13);
    circuit.addGate(dd::U1mat(dd::PI * 14 / 8), 14);
    circuit.addGate(dd::U1mat(dd::PI * 6 / 4), 15);
    circuit.addGate(dd::U1mat(dd::PI * 2 / 2), 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 32), 17_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 16), 17_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 14 / 8), 17_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 6 / 4), 17_pc, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 2 / 2), 17_pc, 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 32), 12);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 16), 13);
    circuit.addGate(dd::U1mat(dd::PI * 14 / 8), 14);
    circuit.addGate(dd::U1mat(dd::PI * 6 / 4), 15);
    circuit.addGate(dd::U1mat(dd::PI * 2 / 2), 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 32), 17_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 16), 17_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 14 / 8), 17_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 6 / 4), 17_pc, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 2 / 2), 17_pc, 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 32), 12);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 16), 13);
    circuit.addGate(dd::U1mat(dd::PI * 14 / 8), 14);
    circuit.addGate(dd::U1mat(dd::PI * 6 / 4), 15);
    circuit.addGate(dd::U1mat(dd::PI * 2 / 2), 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Hmat, 7);
    circuit.addGate(dd::Hmat, 6);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 32), 12);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 16), 13);
    circuit.addGate(dd::U1mat(-dd::PI * 14 / 8), 14);
    circuit.addGate(dd::U1mat(-dd::PI * 6 / 4), 15);
    circuit.addGate(dd::U1mat(-dd::PI * 2 / 2), 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 32), 17_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 16), 17_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 14 / 8), 17_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 6 / 4), 17_pc, 15);
    circuit.addGate(dd::U1mat(dd::PI * 2 / 2), 17_pc, 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Xmat, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 32), 12);
    circuit.addGate(dd::U1mat(-dd::PI * 30 / 16), 13);
    circuit.addGate(dd::U1mat(-dd::PI * 14 / 8), 14);
    circuit.addGate(dd::U1mat(-dd::PI * 6 / 4), 15);
    circuit.addGate(dd::U1mat(-dd::PI * 2 / 2), 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::Xmat, 12_pc, 17);
    circuit.addGate(dd::Hmat, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 13_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 14_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 15_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 16), 16_pc, 12);
    circuit.addGate(dd::Hmat, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 32), 17_pc, 12);
    circuit.addGate(dd::U1mat(dd::PI * 30 / 16), 17_pc, 13);
    circuit.addGate(dd::U1mat(dd::PI * 14 / 8), 17_pc, 14);
    circuit.addGate(dd::U1mat(dd::PI * 6 / 4), 17_pc, 15);
    circuit.addGate(dd::U1mat(dd::PI * 2 / 2), 17_pc, 16);
    circuit.addGate(dd::Hmat, 16);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 16_pc, 15);
    circuit.addGate(dd::Hmat, 15);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 15_pc, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 16_pc, 14);
    circuit.addGate(dd::Hmat, 14);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 2), 14_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 4), 15_pc, 13);
    circuit.addGate(dd::U1mat(-dd::PI * 1 / 8), 16_pc, 13);
    circuit.addGate(dd::Hmat, 13);

//    simulateCircuitLIMDDGateByGate(circuit);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}



TEST(LimTest, zeroEdgesTest) {
    dd::Qubit nqubits = 2;

    auto limdd = std::make_unique<dd::Package<>>(nqubits, dd::LIMDD_group::Pauli_group, false);

    auto limddState= limdd->makeZeroState(nqubits);
    EXPECT_TRUE(limddState.p->e[1] == dd::vEdge::zero);
    EXPECT_TRUE(limddState.p->e[0].p->e[1] == dd::vEdge::zero);
}