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

TEST(LimTest, hardCircuit_5_minimized) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 2_nc, 0);
    circuit.addGate(dd::Hmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 0_pc, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1); // triggers an error

    raceCircuitQMDDvsLIMDD(circuit);
}