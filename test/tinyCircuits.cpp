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


// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_1) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_2) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_3) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_4) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_5) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_6) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_7) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_8) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_9) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_10) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_11) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_12) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_13) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_14) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_15) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_16) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_17) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_18) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_19) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_20) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_21) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_22) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_23) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_24) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_25) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_26) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_27) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_28) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_29) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_30) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_31) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_32) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_33) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_34) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_35) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_36) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_37) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_38) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_39) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_40) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_41) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_42) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_43) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_44) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_45) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_46) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_47) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_48) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_49) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_50) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_51) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_52) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_53) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_54) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_55) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_56) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_57) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_58) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_59) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_60) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_61) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_62) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_63) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_64) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_65) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_66) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_67) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_68) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_69) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_70) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_71) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_72) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_73) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_74) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_75) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_76) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_77) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_78) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_79) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_80) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_81) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_82) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_83) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_84) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_85) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_86) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_87) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_88) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_89) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_90) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_91) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_92) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_93) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_94) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_95) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_96) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_97) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_98) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_99) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_100) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_101) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_102) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_103) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_104) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_105) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_106) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_107) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_108) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_109) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_110) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_111) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_112) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_113) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_114) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_115) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_116) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_117) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_118) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_119) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_120) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_121) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_122) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_123) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_124) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_125) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_126) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_127) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_128) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_129) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_130) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_131) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_132) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_133) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_134) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_135) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_136) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_137) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_138) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_139) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_140) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_141) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_142) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_143) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_144) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_145) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_146) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_147) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_148) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_149) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_150) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_151) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_152) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_153) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_154) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_155) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_156) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_157) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_158) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_159) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_160) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_161) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_162) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_163) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_164) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_165) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_166) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_167) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_168) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_169) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_170) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_171) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_172) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_173) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_174) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_175) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_176) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_177) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_178) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_179) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_180) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_181) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_182) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_183) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_184) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_185) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_186) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_187) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_188) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_189) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_190) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_191) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_192) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_193) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_194) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_195) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_196) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_197) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_198) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_199) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_200) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_201) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_202) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_203) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_204) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_205) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_206) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_207) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_208) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_209) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_210) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_211) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_212) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_213) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_214) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_215) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_216) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_217) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_218) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_219) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_220) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_221) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_222) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_223) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_224) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_225) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_226) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_227) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_228) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_229) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_230) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_231) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_232) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_233) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_234) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_235) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_236) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_237) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_238) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_239) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_240) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_241) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_242) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_243) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_244) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_245) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_246) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_247) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_248) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_249) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_250) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_251) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_252) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_253) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_254) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_255) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_256) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_257) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_258) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_259) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_260) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_261) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_262) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_263) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_264) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_265) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_266) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_267) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_268) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_269) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_270) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_271) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_272) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_273) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_274) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_275) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_276) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_277) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_278) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_279) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_280) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_281) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_282) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_283) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_284) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_285) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_286) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_287) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_288) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_289) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_290) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_291) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_292) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_293) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_294) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Tdagmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_295) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_296) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_297) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_298) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_299) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_300) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}


// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_301) {
    dd::QuantumCircuit circuit(3);
    
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Hmat, 1_nc, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_302) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_303) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_304) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_305) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_306) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_307) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_308) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_309) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_310) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_311) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_312) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_313) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_314) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_315) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_316) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_317) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_318) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tdagmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_319) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0_pc, 2);
    circuit.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_320) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Hmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Smat, 1_pc, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_321) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0_pc, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_322) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_323) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_324) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_325) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_326) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1_pc, 2);
    circuit.addGate(dd::Tmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_327) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0_nc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_328) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_329) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Hmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_330) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_331) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Smat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Smat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_332) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_333) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 2);
    circuit.addGate(dd::Tmat, 1_pc, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_334) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_335) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_336) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_337) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_338) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_339) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_340) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_341) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_342) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 2);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_343) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_344) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_345) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_346) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_347) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_348) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Tmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_349) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_350) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_351) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_352) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_353) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_354) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_355) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_356) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_357) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_358) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_359) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_360) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_361) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_362) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_363) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_364) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_365) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_366) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_367) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_368) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_369) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_370) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1_nc, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_371) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_372) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_373) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_374) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_375) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_376) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 2_pc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_377) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_378) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_379) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tmat, 2_pc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Smat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_380) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_381) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_382) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_383) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_384) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_385) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_386) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_387) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_388) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_389) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_390) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_391) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_392) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Smat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_393) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_394) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_395) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_396) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_397) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Hmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_398) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_399) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_400) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_401) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_402) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_403) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_404) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_405) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_406) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_407) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2_pc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_408) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_409) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_410) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_411) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_412) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Hmat, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_413) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_pc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_414) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tdagmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_415) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_416) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1_pc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_417) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_418) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Smat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_419) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_420) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_421) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_422) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_423) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 2_nc, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_424) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_425) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1_pc, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_426) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_427) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_428) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_429) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_430) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tdagmat, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_431) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Smat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_432) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_433) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1_nc, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_434) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 2_pc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_435) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_436) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tdagmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_437) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_438) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_439) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_440) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_441) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tdagmat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_442) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1_pc, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_443) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_444) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_445) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Smat, 1_pc, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_446) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_447) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_448) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tdagmat, 2_pc, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_449) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_450) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_451) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_452) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_453) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_454) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Tmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_455) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 2_nc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_456) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_457) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_458) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_459) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_460) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2_pc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_461) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_462) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_463) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_464) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_465) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_466) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_467) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_468) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_469) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_470) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_471) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_472) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_473) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_474) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Smat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_475) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_476) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1_pc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_477) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_478) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_479) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 0_nc, 2);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_480) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_481) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 2);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_482) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_483) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_484) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_485) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_486) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_487) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_488) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_489) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_490) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2_nc, 0);
    circuit.addGate(dd::Tmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_491) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_492) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_493) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_494) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tmat, 2_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_495) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_496) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_497) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_498) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_499) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_500) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_501) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_502) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2_nc, 0);
    circuit.addGate(dd::Tdagmat, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_503) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_504) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_505) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Hmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_506) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_507) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Smat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_508) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_509) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tdagmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_510) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_511) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Hmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_512) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_513) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_514) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_515) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_516) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_517) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Hmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_518) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2_nc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_519) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_520) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_521) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_522) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_523) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Smat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_524) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Smat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_525) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_526) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_527) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Hmat, 1_pc, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_528) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Tmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_529) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Tmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_530) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 1_pc, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_531) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_532) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Hmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_533) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_534) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_535) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_536) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_537) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_538) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 0_nc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_539) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_540) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_541) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_542) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_543) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_544) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Tmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_545) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_546) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tdagmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_547) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1_pc, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_548) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_549) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_550) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_551) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_552) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_553) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_554) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_555) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_556) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_557) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_558) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_559) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Tdagmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_560) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tdagmat, 1_pc, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_561) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_562) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_563) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_564) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 2_pc, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2_pc, 1);
    circuit.addGate(dd::Smat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_565) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_566) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_567) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_568) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_569) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tdagmat, 1_pc, 2);
    circuit.addGate(dd::Tmat, 2_nc, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_570) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 1_nc, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_571) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Tdagmat, 0_pc, 2);
    circuit.addGate(dd::Tdagmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_572) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0_pc, 2);
    circuit.addGate(dd::Tmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Smat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_573) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Smat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_574) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2_pc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_575) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1_nc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_576) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Smat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_577) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_578) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Hmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_579) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tdagmat, 1_nc, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_580) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 2_pc, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_581) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2_pc, 0);
    circuit.addGate(dd::Tdagmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_582) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Tdagmat, 2_nc, 1);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_583) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_584) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Tmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_585) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0_nc, 2_nc, 1);
    circuit.addGate(dd::Tmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Tmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_586) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0_pc, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Tmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_587) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2_pc, 0);
    circuit.addGate(dd::Smat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_588) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_589) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Tmat, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_590) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Tmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_591) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Tmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_592) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_593) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_594) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 1_nc, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Tmat, 2_nc, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_595) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2_nc, 0);
    circuit.addGate(dd::Tdagmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_596) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Tmat, 0_nc, 1_pc, 2);
    circuit.addGate(dd::Smat, 2_pc, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0_pc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_597) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Tmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 2_nc, 1_pc, 0);
    circuit.addGate(dd::Tmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_598) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1_nc, 0);
    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_599) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1_pc, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Tdagmat, 0_nc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_600) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Tmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0_nc, 1);
    circuit.addGate(dd::Tdagmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2_pc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 2);
    circuit.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

