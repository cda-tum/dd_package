
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

TEST(LimTest, singleHadamard) {
    dd::QubitCount numQubits = 24;
    dd::QubitCount target    = 23;
    auto           dd        = std::make_unique<dd::Package<>>(numQubits, dd::LIMDD_group::Pauli_group, false);

    dd::vEdge state  = dd->makeZeroState(numQubits);
    auto      h_gate = dd->makeGateDD(dd::Hmat, numQubits, target);

    std::cout << "Executing circuit with n = " << numQubits << " qubits. Hadamard applied to gate " << target << std::endl;
    std::cout << "Exporting state 0 to svg." << std::endl;
    //export2Dot(state, "state0.dot", true, true, true, false, true, false);

    std::cout << "Applying gate 1." << std::endl;
    state = dd->multiply(h_gate, state);
}

TEST(LimTest, twoHadamardGates) {
    dd::QubitCount numQubits = 24;
    dd::QubitCount target    = 23;
    dd::QubitCount target2   = 15;
    auto           dd        = std::make_unique<dd::Package<>>(numQubits, dd::LIMDD_group::Pauli_group, false);

    dd::vEdge state  = dd->makeZeroState(numQubits);
    auto      h_gate = dd->makeGateDD(dd::Hmat, numQubits, target);

    std::cout << "Executing circuit with n = " << (int)numQubits << " qubits. Hadamard applied to gate " << (int)target << std::endl;

    std::cout << "Applying gate 1." << std::endl;
    state = dd->multiply(h_gate, state);

    auto h_gate2 = dd->makeGateDD(dd::Hmat, numQubits, target2);
    std::cout << "Applying gate 2." << std::endl;
    state = dd->multiply(h_gate2, state);
}

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


TEST(LimTest, simpleCircuit_graphstate_18) {
    dd::QuantumCircuit c(18);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 3);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 5);
    c.addGate(dd::Xmat, 4_pc, 5);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 7);
    c.addGate(dd::Xmat, 6_pc, 7);
    c.addGate(dd::Hmat, 7);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 8);
    c.addGate(dd::Xmat, 5_pc, 8);
    c.addGate(dd::Hmat, 8);
    c.addGate(dd::Hmat, 9);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 10);
    c.addGate(dd::Xmat, 7_pc, 10);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 10);
    c.addGate(dd::Xmat, 9_pc, 10);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 12);
    c.addGate(dd::Xmat, 11_pc, 12);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 13);
    c.addGate(dd::Xmat, 12_pc, 13);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 14);
    c.addGate(dd::Xmat, 9_pc, 14);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 14);
    c.addGate(dd::Xmat, 13_pc, 14);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 15);
    c.addGate(dd::Xmat, 1_pc, 15);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 15);
    c.addGate(dd::Xmat, 2_pc, 15);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
    c.addGate(dd::Xmat, 4_pc, 16);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
    c.addGate(dd::Xmat, 8_pc, 16);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 17);
    c.addGate(dd::Xmat, 6_pc, 17);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 17);
    c.addGate(dd::Xmat, 11_pc, 17);
    c.addGate(dd::Hmat, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}



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

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}