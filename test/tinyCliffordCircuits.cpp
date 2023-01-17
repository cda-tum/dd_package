#include "dd/GateMatrixDefinitions.hpp"
      #include "dd/QuantumCircuitSimulation.hpp"
      #include "dd/QuantumGate.hpp"

      #include "gtest/gtest.h"
      #include <memory>

      using namespace dd::literals;

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_3) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_4) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_5) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_6) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_7) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_8) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_9) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_10) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_11) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_12) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_13) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_14) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_15) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_16) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_17) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_18) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_19) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_20) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_21) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_22) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_23) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_24) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_25) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_26) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_27) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_28) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_29) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_30) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_31) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_32) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_33) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_34) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_35) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_36) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_37) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_38) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_39) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_40) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_41) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_42) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_43) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_44) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_45) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_46) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_47) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_48) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_49) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_50) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_51) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_52) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_53) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_54) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_55) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_56) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_57) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_58) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_59) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_60) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_61) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_62) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_63) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_64) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_65) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_66) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_67) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_68) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_69) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_70) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_71) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_72) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_73) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_74) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_75) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_76) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_77) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_78) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_79) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_80) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_81) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_82) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_83) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_84) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_85) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_86) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_87) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_88) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_89) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_90) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_91) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_92) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_93) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_94) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_95) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_96) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_97) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_98) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_99) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_100) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_101) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_102) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_103) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_104) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_105) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_106) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_107) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_108) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_109) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_110) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_111) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_112) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_113) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_114) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_115) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_116) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_117) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_118) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_119) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_120) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_121) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_122) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_123) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_124) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_125) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_126) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_127) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_128) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_129) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_130) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_131) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_132) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_133) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_134) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_135) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_136) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_137) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_138) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_139) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_140) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_141) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_142) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_143) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_144) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_145) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_146) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_147) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_148) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_149) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_150) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_151) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_152) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_153) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_154) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_155) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_156) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_157) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_158) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_159) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_160) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_161) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_162) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_163) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_164) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_165) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_166) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_167) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_168) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_169) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_170) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_171) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_172) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_173) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_174) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_175) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_176) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_177) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_178) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_179) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_180) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_181) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_182) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_183) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_184) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_185) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_186) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_187) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_188) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_189) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_190) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_191) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_192) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_193) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_194) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_195) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_196) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_197) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_198) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_199) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_200) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_201) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_202) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_203) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_204) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_205) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_206) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_207) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_208) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_209) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_210) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_211) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_212) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_213) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_214) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_215) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_216) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_217) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_218) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_219) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_220) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_221) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_222) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_223) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_224) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_225) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_226) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_227) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_228) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_229) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_230) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_231) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_232) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_233) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_234) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_235) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_236) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_237) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_238) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_239) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_240) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_241) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_242) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_243) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_244) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_245) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_246) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_247) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_248) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_249) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_250) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_251) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_252) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_253) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_254) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_255) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_256) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_257) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_258) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_259) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_260) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_261) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_262) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_263) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_264) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_265) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_266) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_267) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_268) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_269) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_270) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_271) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_272) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_273) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_274) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_275) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_276) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_277) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_278) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_279) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_280) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_281) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_282) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_283) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_284) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_285) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_286) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_287) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_288) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_289) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_290) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_291) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_292) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_293) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_294) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_295) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_296) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_297) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_298) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_299) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_300) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_301) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_302) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_303) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_304) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_305) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_306) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_307) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_308) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_309) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_310) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_311) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_312) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_313) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_314) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_315) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_316) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_317) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_318) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_319) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_320) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_321) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_322) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_323) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_324) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_325) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_326) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_327) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_328) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_329) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_330) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_331) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_332) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_333) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_334) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_335) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_336) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_337) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_338) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_339) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_340) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_341) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_342) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_343) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_344) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_345) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_346) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_347) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_348) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_349) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_350) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_351) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_352) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_353) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_354) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_355) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_356) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_357) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_358) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_359) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_360) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_361) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_362) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_363) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_364) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_365) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_366) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_367) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_368) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_369) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_370) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_371) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_372) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_373) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_374) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_375) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_376) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_377) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_378) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_379) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_380) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_381) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_382) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_383) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_384) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_385) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_386) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_387) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_388) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_389) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_390) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_391) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_392) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_393) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_394) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_395) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_396) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_397) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_398) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_399) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_400) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_401) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_402) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_403) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_404) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_405) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_406) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_407) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_408) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_409) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_410) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_411) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_412) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_413) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_414) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_415) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_416) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_417) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_418) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_419) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_420) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_421) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_422) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_423) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_424) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_425) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_426) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_427) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_428) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_429) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_430) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_431) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_432) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_433) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_434) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_435) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_436) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_437) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_438) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_439) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_440) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_441) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_442) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_443) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_444) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_445) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_446) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_447) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_448) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_449) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_450) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_451) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_452) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_453) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_454) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_455) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_456) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_457) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_458) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_459) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_460) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_461) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_462) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_463) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_464) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_465) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_466) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_467) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_468) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_469) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_470) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_471) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_472) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_473) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_474) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_475) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_476) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_477) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_478) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_479) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_480) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_481) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_482) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_483) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_484) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_485) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_486) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_487) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_488) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_489) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_490) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_491) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_492) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_493) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_494) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_495) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_496) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_497) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_498) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_499) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_500) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_501) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_502) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_503) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_504) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_505) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_506) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_507) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_508) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_509) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_510) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_511) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_512) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_513) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_514) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_515) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_516) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_517) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_518) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_519) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_520) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_521) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_522) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_523) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_524) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_525) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_526) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_527) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_528) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_529) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_530) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_531) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_532) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_533) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_534) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_535) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_536) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_537) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_538) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_539) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_540) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_541) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_542) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_543) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_544) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_545) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_546) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_547) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_548) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_549) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_550) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_551) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_552) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_553) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_554) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_555) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_556) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_557) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_558) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_559) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_560) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_561) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_562) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_563) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_564) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_565) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_566) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_567) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_568) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_569) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_570) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_571) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_572) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_573) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_574) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_575) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_576) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_577) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_578) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_579) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_580) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_581) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_582) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_583) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_584) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_585) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_586) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_587) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_588) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_589) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_590) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_591) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_592) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_593) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_594) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_595) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_596) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_597) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_598) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_599) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_600) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_601) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_602) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_603) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_604) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_605) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_606) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_607) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_608) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_609) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_610) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_611) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_612) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_613) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_614) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_615) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_616) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_617) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_618) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_619) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_620) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_621) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_622) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_623) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_624) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_625) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_626) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_627) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_628) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_629) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_630) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_631) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_632) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_633) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_634) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_635) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_636) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_637) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_638) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_639) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_640) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_641) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_642) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_643) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_644) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_645) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_646) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_647) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_648) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_649) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_650) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_651) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_652) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_653) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_654) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_655) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_656) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_657) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_658) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_659) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_660) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_661) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_662) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_663) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_664) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_665) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_666) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_667) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_668) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_669) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_670) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_671) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_672) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_673) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_674) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_675) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_676) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_677) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_678) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_679) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_680) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_681) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_682) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_683) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_684) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_685) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_686) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_687) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_688) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_689) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_690) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_691) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_692) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_693) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_694) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_695) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_696) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_697) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_698) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_699) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_700) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_701) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_702) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_703) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_704) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_705) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_706) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_707) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_708) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_709) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_710) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_711) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_712) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_713) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_714) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_715) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_716) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_717) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_718) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_719) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_720) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_721) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_722) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_723) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_724) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_725) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_726) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_727) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_728) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_729) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_730) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_731) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_732) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_733) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_734) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_735) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_736) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_737) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_738) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_739) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_740) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_741) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_742) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_743) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_744) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_745) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_746) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_747) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_748) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_749) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_750) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_751) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_752) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_753) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_754) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_755) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_756) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_757) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_758) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_759) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_760) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_761) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_762) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_763) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_764) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_765) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_766) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_767) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_768) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_769) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_770) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_771) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_772) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_773) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_774) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_775) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_776) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_777) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_778) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_779) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_780) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_781) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_782) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_783) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_784) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_785) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_786) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_787) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_788) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_789) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_790) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_791) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_792) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_793) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_794) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_795) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_796) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_797) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_798) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_799) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_800) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_801) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_802) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_803) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_804) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_805) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_806) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_807) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_808) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_809) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_810) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_811) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_812) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_813) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_814) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_815) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_816) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_817) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_818) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_819) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_820) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_821) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_822) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_823) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_824) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_825) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_826) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_827) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_828) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_829) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_830) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_831) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_832) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_833) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_834) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_835) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_836) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_837) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_838) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_839) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_840) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_841) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_842) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_843) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_844) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_845) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_846) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_847) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_848) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_849) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_850) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_851) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_852) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_853) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_854) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_855) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_856) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_857) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_858) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_859) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_860) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_861) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_862) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_863) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_864) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_865) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_866) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_867) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_868) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_869) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_870) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_871) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_872) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_873) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_874) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_875) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_876) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_877) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_878) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_879) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_880) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_881) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_882) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_883) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_884) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_885) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_886) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_887) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_888) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_889) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_890) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_891) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_892) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_893) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_894) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_895) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_896) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_897) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_898) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_899) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_900) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_901) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_902) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_903) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_904) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_905) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_906) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_907) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_908) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_909) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_910) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_911) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_912) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_913) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_914) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_915) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_916) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_917) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_918) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_919) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_920) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_921) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_922) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_923) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_924) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_925) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_926) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_927) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_928) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_929) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_930) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_931) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_932) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_933) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_934) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_935) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_936) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_937) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_938) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_939) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_940) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_941) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_942) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_943) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_944) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_945) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_946) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_947) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_948) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_949) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_950) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_951) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_952) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_953) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_954) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_955) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_956) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_957) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_958) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_959) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_960) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_961) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_962) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_963) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_964) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_965) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_966) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_967) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_968) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Ymat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_969) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_970) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_971) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Xmat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_972) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 1);
    circuit.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_973) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 2);
    circuit.addGate(dd::Ymat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_974) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_975) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_976) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Smat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_977) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_978) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 1_nc, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_979) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_980) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Ymat, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_981) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_982) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_983) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Ymat, 2);
    circuit.addGate(dd::Zmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_984) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_985) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Zmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_986) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 2_pc, 1);
    circuit.addGate(dd::Xmat, 0_pc, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_987) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_988) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_989) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_990) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Xmat, 0_pc, 1);
    circuit.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_991) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_992) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Smat, 1);
    circuit.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_993) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Smat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_994) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_nc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_995) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Smat, 2);
    circuit.addGate(dd::Zmat, 2_pc, 0);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 0);
    circuit.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_996) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 0_nc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_997) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_998) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 1);
    circuit.addGate(dd::Zmat, 0_nc, 1);
    circuit.addGate(dd::Xmat, 2);
    circuit.addGate(dd::Xmat, 1);
    circuit.addGate(dd::Xmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_999) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Zmat, 0_pc, 2);
    circuit.addGate(dd::Zmat, 2_nc, 0);
    circuit.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_1000) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Zmat, 1_pc, 2);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Zmat, 0_pc, 1);
    circuit.addGate(dd::Xmat, 1_nc, 0);
    circuit.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_1001) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_nc, 2);
    circuit.addGate(dd::Zmat, 1_nc, 0);
    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1);
    circuit.addGate(dd::Zmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, tinyRandomCliffordCircuit_1002) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

