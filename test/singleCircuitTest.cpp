#include "dd/GateMatrixDefinitions.hpp"
#include "dd/QuantumCircuitSimulation.hpp"
#include "dd/QuantumGate.hpp"

#include "gtest/gtest.h"
#include <memory>

using namespace dd::literals;

// Randomly generated circuit on 2 qubis, containing 7 gates.
TEST(LimTest, randomTinyCircuit_256_4) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}