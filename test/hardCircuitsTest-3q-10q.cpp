// This file contains many quantum circuits that are expected to be hard to simulate using DDs.

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

// Randomly generated circuit on 3 qubis, containing 30 gates.
TEST(LimTest, hardCircuit_3) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 4 qubis, containing 40 gates.
TEST(LimTest, hardCircuit_4) {
    dd::QuantumCircuit circuit(4);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Tdagmat, 3);
    circuit.addGate(dd::Smat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2_pc, 3);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1_nc, 3);
    circuit.addGate(dd::Smat, 3);
    circuit.addGate(dd::Hmat, 3_pc, 2);
    circuit.addGate(dd::Tmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 3_pc, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 3);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 0_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 3_nc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 3);
    circuit.addGate(dd::Ymat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 3);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2_nc, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 5 qubis, containing 50 gates.
TEST(LimTest, hardCircuit_5) {
    dd::QuantumCircuit circuit(5);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 4_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 4_pc, 1);
    circuit.addGate(dd::Hmat, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 4);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 3_nc, 1_pc, 2);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tmat, 4);
    circuit.addGate(dd::Smat, 4_pc, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 3);
    circuit.addGate(dd::Smat, 2_pc, 4);
    circuit.addGate(dd::Hmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1_pc, 3_pc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 2_nc, 3);
    circuit.addGate(dd::Smat, 3);
    circuit.addGate(dd::Tdagmat, 0_pc, 3);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 3_pc, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 4);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2_pc, 1_pc, 4);
    circuit.addGate(dd::Xmat, 3_nc, 0_nc, 4);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 4_pc, 3);
    circuit.addGate(dd::Hmat, 2_nc, 1_nc, 3);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 3);
    circuit.addGate(dd::Smat, 4_nc, 2);
    circuit.addGate(dd::Tmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2); // triggers an error
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 6 qubis, containing 60 gates.
TEST(LimTest, hardCircuit_6) {
    dd::QuantumCircuit circuit(6);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tdagmat, 5);
    circuit.addGate(dd::Xmat, 5_pc, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 3);
    circuit.addGate(dd::Smat, 0_nc, 4);
    circuit.addGate(dd::Tdagmat, 5);
    circuit.addGate(dd::Tdagmat, 3_pc, 4);
    circuit.addGate(dd::Smat, 3);
    circuit.addGate(dd::Ymat, 4);
    circuit.addGate(dd::Tdagmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 5_pc, 4_pc, 3);
    circuit.addGate(dd::Tdagmat, 3_nc, 5_pc, 0);
    circuit.addGate(dd::Xmat, 4_nc, 1);
    circuit.addGate(dd::Tdagmat, 3);
    circuit.addGate(dd::Tmat, 5);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 4_nc, 3_nc, 1);
    circuit.addGate(dd::Xmat, 4);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 4_pc, 0);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 5);
    circuit.addGate(dd::Hmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 3_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 3_pc, 5_pc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 3_nc, 4_pc, 2);
    circuit.addGate(dd::Tmat, 4_nc, 5);
    circuit.addGate(dd::Xmat, 4);
    circuit.addGate(dd::Tmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 4_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 4);
    circuit.addGate(dd::Hmat, 2_pc, 4_nc, 3);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Ymat, 0_pc, 2_nc, 5);
    circuit.addGate(dd::Zmat, 4);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 7 qubis, containing 70 gates.
TEST(LimTest, hardCircuit_7) {
    dd::QuantumCircuit circuit(7);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Hmat, 6);
    circuit.addGate(dd::Tmat, 3_nc, 5_pc, 4);
    circuit.addGate(dd::Smat, 1_pc, 6);
    circuit.addGate(dd::Ymat, 6_pc, 5);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2_pc, 5);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tmat, 5_nc, 1_pc, 4);
    circuit.addGate(dd::Xmat, 1_nc, 3);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 5_nc, 6);
    circuit.addGate(dd::Smat, 5_nc, 3);
    circuit.addGate(dd::Tmat, 1_nc, 6_nc, 0);
    circuit.addGate(dd::Ymat, 6);
    circuit.addGate(dd::Xmat, 3_nc, 6);
    circuit.addGate(dd::Tdagmat, 3);
    circuit.addGate(dd::Tmat, 1_nc, 6);
    circuit.addGate(dd::Xmat, 3_pc, 4);
    circuit.addGate(dd::Tdagmat, 5);
    circuit.addGate(dd::Tmat, 3);
    circuit.addGate(dd::Hmat, 2_nc, 6_pc, 4);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 4_pc, 1);
    circuit.addGate(dd::Xmat, 6_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 5_nc, 0_pc, 6);
    circuit.addGate(dd::Hmat, 3_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 3);
    circuit.addGate(dd::Hmat, 6_nc, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tmat, 5);
    circuit.addGate(dd::Tdagmat, 6);
    circuit.addGate(dd::Ymat, 1_pc, 6);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 5);
    circuit.addGate(dd::Tmat, 6);
    circuit.addGate(dd::Smat, 3_pc, 5_pc, 6);
    circuit.addGate(dd::Hmat, 0_nc, 3_pc, 5);
    circuit.addGate(dd::Smat, 4_nc, 5_nc, 6);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Zmat, 5_nc, 4_nc, 1);
    circuit.addGate(dd::Xmat, 4_pc, 3_nc, 6);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 3);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 5_pc, 3_nc, 6);
    circuit.addGate(dd::Ymat, 4_nc, 1);
    circuit.addGate(dd::Tmat, 5);
    circuit.addGate(dd::Ymat, 3_pc, 1_nc, 6);
    circuit.addGate(dd::Tmat, 5);
    circuit.addGate(dd::Zmat, 5);
    circuit.addGate(dd::Xmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Tdagmat, 3_pc, 0);
    circuit.addGate(dd::Xmat, 5_nc, 1);
    circuit.addGate(dd::Tdagmat, 4_pc, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 8 qubis, containing 80 gates.
TEST(LimTest, hardCircuit_8) {
    dd::QuantumCircuit circuit(8);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Ymat, 3);
    circuit.addGate(dd::Tdagmat, 2_nc, 5);
    circuit.addGate(dd::Tmat, 4);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Smat, 2_pc, 4_pc, 7);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 6_nc, 2);
    circuit.addGate(dd::Smat, 5_pc, 7_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 7);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2_nc, 5);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 4_nc, 5);
    circuit.addGate(dd::Smat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Tdagmat, 2_pc, 6);
    circuit.addGate(dd::Ymat, 2_nc, 0_nc, 4);
    circuit.addGate(dd::Zmat, 1_pc, 0_nc, 6);
    circuit.addGate(dd::Tmat, 3);
    circuit.addGate(dd::Xmat, 7_nc, 5_nc, 6);
    circuit.addGate(dd::Ymat, 7_pc, 4_pc, 0);
    circuit.addGate(dd::Tmat, 2_pc, 4_pc, 7);
    circuit.addGate(dd::Ymat, 5);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 3);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 7_pc, 0);
    circuit.addGate(dd::Tmat, 7);
    circuit.addGate(dd::Xmat, 3_nc, 6);
    circuit.addGate(dd::Hmat, 5_nc, 1);
    circuit.addGate(dd::Zmat, 5);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 7_pc, 1);
    circuit.addGate(dd::Tmat, 2_nc, 0_pc, 4);
    circuit.addGate(dd::Ymat, 3);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 2_pc, 7_pc, 0);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Tdagmat, 1_nc, 6_pc, 3);
    circuit.addGate(dd::Tmat, 7_pc, 3_pc, 4);
    circuit.addGate(dd::Tdagmat, 7_nc, 6);
    circuit.addGate(dd::Zmat, 5_nc, 4_nc, 6);
    circuit.addGate(dd::Ymat, 1_nc, 6_pc, 3);
    circuit.addGate(dd::Tmat, 7);
    circuit.addGate(dd::Tdagmat, 3_nc, 4);
    circuit.addGate(dd::Tdagmat, 3_pc, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 5_pc, 4_pc, 3);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 4);
    circuit.addGate(dd::Zmat, 5_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 7);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Xmat, 7_pc, 3);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Smat, 6_pc, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2_pc, 0_nc, 3);
    circuit.addGate(dd::Zmat, 2_nc, 4_pc, 6);
    circuit.addGate(dd::Xmat, 5);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Hmat, 5_nc, 4);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 9 qubis, containing 90 gates.
TEST(LimTest, hardCircuit_9) {
    dd::QuantumCircuit circuit(9);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Hmat, 8);
    circuit.addGate(dd::Tmat, 4_pc, 7_pc, 8);
    circuit.addGate(dd::Ymat, 8_pc, 1_nc, 7);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Xmat, 5);
    circuit.addGate(dd::Hmat, 2_pc, 8);
    circuit.addGate(dd::Ymat, 8);
    circuit.addGate(dd::Tmat, 3);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Hmat, 5_pc, 4_nc, 6);
    circuit.addGate(dd::Xmat, 2_pc, 3);
    circuit.addGate(dd::Smat, 8_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 8_pc, 6_pc, 4);
    circuit.addGate(dd::Zmat, 7_pc, 2_nc, 3);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tdagmat, 8_pc, 1_nc, 0);
    circuit.addGate(dd::Ymat, 4_nc, 1);
    circuit.addGate(dd::Tdagmat, 8_pc, 7_pc, 3);
    circuit.addGate(dd::Tdagmat, 3);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Tmat, 3_nc, 5_pc, 6);
    circuit.addGate(dd::Ymat, 4_nc, 2);
    circuit.addGate(dd::Hmat, 0_pc, 3_nc, 4);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Xmat, 1_pc, 0_pc, 3);
    circuit.addGate(dd::Hmat, 1_nc, 4_pc, 7);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 3);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 8_nc, 4_nc, 5);
    circuit.addGate(dd::Tdagmat, 2_nc, 3_pc, 1);
    circuit.addGate(dd::Hmat, 7_nc, 4);
    circuit.addGate(dd::Tmat, 4_pc, 8);
    circuit.addGate(dd::Smat, 8_nc, 5_pc, 3);
    circuit.addGate(dd::Hmat, 7_pc, 1_pc, 3);
    circuit.addGate(dd::Tmat, 7_pc, 5);
    circuit.addGate(dd::Tdagmat, 5);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 4);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Tmat, 6_nc, 8_nc, 7);
    circuit.addGate(dd::Tdagmat, 8);
    circuit.addGate(dd::Smat, 4);
    circuit.addGate(dd::Xmat, 1_pc, 8_pc, 5);
    circuit.addGate(dd::Tmat, 5);
    circuit.addGate(dd::Tdagmat, 8);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 3_pc, 6);
    circuit.addGate(dd::Tdagmat, 6);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 8);
    circuit.addGate(dd::Hmat, 2_pc, 8);
    circuit.addGate(dd::Tmat, 1_pc, 0_nc, 4);
    circuit.addGate(dd::Ymat, 3);
    circuit.addGate(dd::Xmat, 3);
    circuit.addGate(dd::Tmat, 4_nc, 8);
    circuit.addGate(dd::Tmat, 1_pc, 8);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 3);
    circuit.addGate(dd::Hmat, 3);
    circuit.addGate(dd::Hmat, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 7);
    circuit.addGate(dd::Smat, 4_nc, 5);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 3_pc, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 2_nc, 8_nc, 7);
    circuit.addGate(dd::Smat, 6_nc, 3);
    circuit.addGate(dd::Xmat, 6);
    circuit.addGate(dd::Hmat, 8);
    circuit.addGate(dd::Tdagmat, 8_nc, 2);
    circuit.addGate(dd::Hmat, 8);
    circuit.addGate(dd::Hmat, 7_pc, 6);
    circuit.addGate(dd::Tmat, 1_nc, 6_nc, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 5);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 10 qubis, containing 100 gates.
TEST(LimTest, hardCircuit_10) {
    dd::QuantumCircuit circuit(10);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Hmat, 8);
    circuit.addGate(dd::Hmat, 9);
    circuit.addGate(dd::Tdagmat, 5_pc, 2_pc, 7);
    circuit.addGate(dd::Ymat, 8_pc, 7_nc, 0);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Xmat, 4);
    circuit.addGate(dd::Hmat, 7_pc, 9);
    circuit.addGate(dd::Ymat, 5);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Hmat, 4);
    circuit.addGate(dd::Hmat, 1_nc, 5_pc, 4);
    circuit.addGate(dd::Smat, 7);
    circuit.addGate(dd::Zmat, 3_nc, 7);
    circuit.addGate(dd::Hmat, 8_pc, 3_pc, 4);
    circuit.addGate(dd::Tmat, 8);
    circuit.addGate(dd::Hmat, 3_pc, 5_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 7);
    circuit.addGate(dd::Xmat, 4);
    circuit.addGate(dd::Tdagmat, 3_pc, 7_nc, 2);
    circuit.addGate(dd::Ymat, 7_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 3_pc, 2_nc, 5);
    circuit.addGate(dd::Hmat, 7);
    circuit.addGate(dd::Tmat, 9_nc, 6_nc, 4);
    circuit.addGate(dd::Smat, 2_nc, 7_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 7_pc, 3);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 3);
    circuit.addGate(dd::Ymat, 3_nc, 5_nc, 9);
    circuit.addGate(dd::Tdagmat, 9);
    circuit.addGate(dd::Xmat, 7_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 7);
    circuit.addGate(dd::Smat, 1_pc, 8);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 7_pc, 3_nc, 0);
    circuit.addGate(dd::Ymat, 5);
    circuit.addGate(dd::Smat, 4);
    circuit.addGate(dd::Xmat, 4_pc, 7_nc, 5);
    circuit.addGate(dd::Zmat, 4_pc, 3);
    circuit.addGate(dd::Smat, 7_pc, 5);
    circuit.addGate(dd::Hmat, 5);
    circuit.addGate(dd::Tdagmat, 9_pc, 2_pc, 3);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Ymat, 5);
    circuit.addGate(dd::Xmat, 4);
    circuit.addGate(dd::Zmat, 3);
    circuit.addGate(dd::Tmat, 2_nc, 6_nc, 7);
    circuit.addGate(dd::Xmat, 8_pc, 6);
    circuit.addGate(dd::Tmat, 8_pc, 6_pc, 7);
    circuit.addGate(dd::Tmat, 5);
    circuit.addGate(dd::Tdagmat, 5);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 3);
    circuit.addGate(dd::Tdagmat, 4);
    circuit.addGate(dd::Hmat, 8);
    circuit.addGate(dd::Tdagmat, 6_nc, 7);
    circuit.addGate(dd::Smat, 5);
    circuit.addGate(dd::Hmat, 4_pc, 6);
    circuit.addGate(dd::Tmat, 2_pc, 0_nc, 6);
    circuit.addGate(dd::Ymat, 6);
    circuit.addGate(dd::Xmat, 9);
    circuit.addGate(dd::Tmat, 3_nc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 4);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tdagmat, 5);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 9_pc, 4);
    circuit.addGate(dd::Tdagmat, 6);
    circuit.addGate(dd::Smat, 9_nc, 3);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 4);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 5);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Tdagmat, 9_nc, 4_nc, 5);
    circuit.addGate(dd::Smat, 4_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0_nc, 6);
    circuit.addGate(dd::Hmat, 6_nc, 0);
    circuit.addGate(dd::Zmat, 7);
    circuit.addGate(dd::Zmat, 0_pc, 1_pc, 4);
    circuit.addGate(dd::Smat, 4);
    circuit.addGate(dd::Smat, 9);
    circuit.addGate(dd::Ymat, 3);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0_pc, 7);
    circuit.addGate(dd::Ymat, 2_pc, 0_nc, 8);
    circuit.addGate(dd::Tmat, 8);
    circuit.addGate(dd::Hmat, 8_nc, 5_nc, 4);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

