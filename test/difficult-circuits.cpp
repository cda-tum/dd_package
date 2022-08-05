
#include "dd/Definitions.hpp"
#include "dd/Export.hpp"
#include "dd/GateMatrixDefinitions.hpp"
#include "dd/LimTable.hpp"
#include "dd/Package.hpp"
#include "dd/PauliAlgebra.hpp"
#include "dd/QuantumGate.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iomanip>
#include <memory>
#include <random>
#include <sstream>


TEST(LimTest, difficultCircuit1) {
    dd::QuantumCircuit c(25);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::Hmat, 7);
    c.addGate(dd::Hmat, 8);
    c.addGate(dd::Hmat, 9);
    c.addGate(dd::Hmat, 10);
    c.addGate(dd::Hmat, 11);
    c.addGate(dd::Hmat, 12);
    c.addGate(dd::Hmat, 13);
    c.addGate(dd::Hmat, 14);
    c.addGate(dd::Hmat, 15);
    c.addGate(dd::Hmat, 16);
    c.addGate(dd::Hmat, 17);
    c.addGate(dd::Hmat, 18);
    c.addGate(dd::Hmat, 19);
    c.addGate(dd::Hmat, 20);
    c.addGate(dd::Hmat, 21);
    c.addGate(dd::Hmat, 22);
    c.addGate(dd::Hmat, 23);
    c.addGate(dd::Hmat, 24);
    c.addGate(dd::Zmat, 4);
    c.addGate(dd::Zmat, 10);
    c.addGate(dd::Zmat, 20);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 24);
    c.addGate(dd::Zmat, 23);
    c.addGate(dd::Zmat, 17);

//    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, difficultCircuit2) {
    dd::QuantumCircuit c(30);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::Hmat, 7);
    c.addGate(dd::Hmat, 8);
    c.addGate(dd::Hmat, 9);
    c.addGate(dd::Hmat, 10);
    c.addGate(dd::Hmat, 11);
    c.addGate(dd::Hmat, 12);
    c.addGate(dd::Hmat, 13);
    c.addGate(dd::Hmat, 14);
    c.addGate(dd::Hmat, 15);
    c.addGate(dd::Hmat, 16);
    c.addGate(dd::Hmat, 17);
    c.addGate(dd::Hmat, 18);
    c.addGate(dd::Hmat, 19);
    c.addGate(dd::Hmat, 20);
    c.addGate(dd::Hmat, 21);
    c.addGate(dd::Hmat, 22);
    c.addGate(dd::Hmat, 23);
    c.addGate(dd::Hmat, 24);
    c.addGate(dd::Hmat, 25);
    c.addGate(dd::Hmat, 26);
    c.addGate(dd::Hmat, 27);
    c.addGate(dd::Hmat, 28);
    c.addGate(dd::Hmat, 29);
    c.addGate(dd::Zmat, 4);
    c.addGate(dd::Zmat, 10);
    c.addGate(dd::Zmat, 20);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 24);
    c.addGate(dd::Zmat, 28);
    c.addGate(dd::Zmat, 23);
    c.addGate(dd::Zmat, 17);
    c.addGate(dd::Zmat, 15);

    //    simulateCircuitQMDDvsLIMDDGateByGate(c);
}