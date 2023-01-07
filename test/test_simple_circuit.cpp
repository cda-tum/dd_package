
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

TEST(LimTest, simpleCircuit1) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit2) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit3) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Zmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit4) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit5) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit6) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit7) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit8) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);

    simulateCircuitLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit9) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit10) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit11) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit12) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit13) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit14) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit15) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit16) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit17) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit18) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit19) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Ymat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit20) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Ymat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit21) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit22) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit23) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit24) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Smat, 1);
    c.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit25) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Smat, 0);
    c.addGate(dd::Smat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit26) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Smat, 1);
    c.addGate(dd::Smat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit27) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit28) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit29) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit30) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit31) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit32) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit33) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit34) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit35) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit36) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit37) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit38) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit39) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit40) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit41) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit42) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit43) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit44) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit45) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit46) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit47) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit48) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit49) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit50) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit51) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit52) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit53) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit54) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit55) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Tmat, 1_pc, 0);
    c.addGate(dd::Tmat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit56) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit57) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit58) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit59) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0_nc, 1);
    c.addGate(dd::Tmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit60) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0_nc, 1);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Tmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit61) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Tmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit62) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Tmat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit63) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Tmat, 1_nc, 0);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Zmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit64) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Tmat, 2);
    c.addGate(dd::Tmat, 1_pc, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_nc, 0);
    c.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit64_2) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Tmat, 2);
    c.addGate(dd::Tmat, 1_pc, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_nc, 0);
    //c.addGate(dd::Zmat, 2_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit65) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit66) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit67) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 0_nc, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit68) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit69) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 2_nc, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit70) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 2_nc, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit71) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0_pc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit72) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 2_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit73) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 0_pc, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit74) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit75) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit76) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Tmat, 0_pc, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit77) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Tmat, 1_nc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit78) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Tmat, 0_pc, 1_nc, 2);
    c.addGate(dd::Tmat, 1_nc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit79) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Tmat, 0_pc, 1_nc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit80) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Smat, 0_pc, 1);
    c.addGate(dd::Smat, 1_pc, 2);
    c.addGate(dd::Tmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Zmat, 1_nc, 2_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit81) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Tmat, 2_pc, 0);
    c.addGate(dd::Tmat, 2_pc, 1_pc, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Tmat, 2_pc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit82) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 2_pc, 0);
    c.addGate(dd::Hmat, 0_pc, 2_pc, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Smat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1_pc, 2);
    c.addGate(dd::Tmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit83) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 0_pc, 2_pc, 1);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit84) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 0_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Hmat, 1_pc, 2);
    c.addGate(dd::Tmat, 2_pc, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit85) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2_pc, 1_pc, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0_pc, 2_pc, 1);
    c.addGate(dd::Hmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 0_pc, 2_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit86) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 0_pc, 2);
    c.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit87) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 2_pc, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit88) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit89) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Tmat, 3_pc, 0);
    c.addGate(dd::Tmat, 3_pc, 2_pc, 1_pc, 0);
    c.addGate(dd::Tmat, 0_pc, 1_nc, 2_nc, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Tmat, 1_pc, 2);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 2_nc, 1);
    c.addGate(dd::Hmat, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit90) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 0_pc, 2);
    c.addGate(dd::Zmat, 0_pc, 3);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Zmat, 2_pc, 3);
    c.addGate(dd::Hmat, 0_pc, 3);
    c.addGate(dd::Hmat, 3_pc, 0);
    c.addGate(dd::Hmat, 1_pc, 2);
    c.addGate(dd::Hmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2_pc, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit91) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 3_pc, 0);
    c.addGate(dd::Zmat, 3_pc, 1);
    c.addGate(dd::Zmat, 3_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Tmat, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit92) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Tmat, 2);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 2_pc, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_1) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_2) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    //	c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_3) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    //	c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_4) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    //	c.addGate(dd::Xmat, 1_pc, 2);
    //	c.addGate(dd::Xmat, 0_pc, 2);
    //	c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_5) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    //	c.addGate(dd::Zmat, 0_pc, 1);
    //	c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_6) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    //	c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_7) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    //	c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_8) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    //	c.addGate(dd::Xmat, 1_pc, 2);
    //	c.addGate(dd::Xmat, 0_pc, 2);
    //	c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    //	c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_9) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    //	c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit93_10) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    //	c.addGate(dd::Zmat, 0_pc, 1);
    //	c.addGate(dd::Zmat, 1_pc, 3);
    //	c.addGate(dd::Xmat, 1_pc, 2);
    //	c.addGate(dd::Xmat, 0_pc, 2);
    //	c.addGate(dd::Xmat, 0_pc, 1_pc, 2);
    c.addGate(dd::Hmat, 1_pc, 3);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit94) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Tmat, 2);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Tmat, 4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit95) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Tmat, 2);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Tmat, 4);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 4);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 4);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit96) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0_pc, 1);
    c.addGate(dd::Hmat, 1_pc, 2);
    c.addGate(dd::Hmat, 2_pc, 3);
    c.addGate(dd::Hmat, 3_pc, 4);
    c.addGate(dd::Tmat, 4);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Tmat, 2);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 4);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit97) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0_pc, 1);
    c.addGate(dd::Hmat, 2_nc, 1);
    c.addGate(dd::Tmat, 1);
    c.addGate(dd::Hmat, 2_nc, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Tmat, 4);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Tmat, 4_pc, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Tmat, 3_pc, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Tmat, 2_pc, 1);
    c.addGate(dd::Hmat, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit98) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 2_pc, 3);
    c.addGate(dd::Zmat, 3_pc, 4);
    c.addGate(dd::Zmat, 0_pc, 4);
    c.addGate(dd::Xmat, 4_pc, 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Ymat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit98_2) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit98_3) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit98_4) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit99) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 3_pc, 4);
    c.addGate(dd::Zmat, 2_pc, 3);
    c.addGate(dd::Zmat, 2_pc, 0);
    c.addGate(dd::Zmat, 2_pc, 3);
    c.addGate(dd::Zmat, 2_pc, 4);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Smat, 4);
    c.addGate(dd::Tmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 3_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit100) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit101) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit102) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit103) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit104) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit105) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Tmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit107) {
    dd::QuantumCircuit c(8);
    c.addGate(dd::U3mat(1, 2, 3), 0);
    c.addGate(dd::U3mat(1, 2, 3), 0_pc, 1);
    c.addGate(dd::U3mat(1, 2, 3), 1_pc, 2);
    c.addGate(dd::U3mat(1, 2, 3), 2_pc, 3);
    c.addGate(dd::U3mat(1, 2, 3), 3_pc, 4);
    c.addGate(dd::U3mat(1, 2, 3), 4_pc, 5);
    c.addGate(dd::U3mat(1, 2, 3), 5_pc, 6);
    c.addGate(dd::U3mat(1, 2, 3), 6_pc, 7);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit108) {
    dd::QuantumCircuit c(8);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::Hmat, 7);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::Hmat, 7);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit109) {
    dd::QuantumCircuit c(8);
    c.addGate(dd::U3mat(1, 2, 3), 0);
    c.addGate(dd::U3mat(1, 2, 3), 1);
    c.addGate(dd::U3mat(1, 2, 3), 2);
    c.addGate(dd::U3mat(1, 2, 3), 3);
    c.addGate(dd::U3mat(1, 2, 3), 4);
    c.addGate(dd::U3mat(1, 2, 3), 5);
    c.addGate(dd::U3mat(1, 2, 3), 6);
    c.addGate(dd::U3mat(1, 2, 3), 7);
    c.addGate(dd::U3mat(1, 2, 3), 0);
    c.addGate(dd::U3mat(1, 2, 3), 1);
    c.addGate(dd::U3mat(1, 2, 3), 2);
    c.addGate(dd::U3mat(1, 2, 3), 3);
    c.addGate(dd::U3mat(1, 2, 3), 4);
    c.addGate(dd::U3mat(1, 2, 3), 5);
    c.addGate(dd::U3mat(1, 2, 3), 6);
    c.addGate(dd::U3mat(1, 2, 3), 7);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit120) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit121) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit122) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 0_pc, 2);
    c.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit123) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0_pc, 2);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit124) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0_pc, 2);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 0_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit125) {
    dd::QuantumCircuit c(3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 0_pc, 2);
    c.addGate(dd::Zmat, 0_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit126) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Zmat, 0_pc, 1);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 3_pc, 4);
    c.addGate(dd::Zmat, 2_pc, 3);
    c.addGate(dd::Zmat, 2_pc, 0);
    c.addGate(dd::Zmat, 2_pc, 3);
    c.addGate(dd::Zmat, 2_pc, 4);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Smat, 4);
    c.addGate(dd::Hmat, 3);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit127) {
    dd::QuantumCircuit c(5);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Zmat, 0_pc, 2);
    c.addGate(dd::Zmat, 1_pc, 2);
    c.addGate(dd::Zmat, 3_pc, 2);
    c.addGate(dd::Zmat, 4_pc, 2);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit128) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, simpleCircuit129) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 1_nc, 0);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, simpleCircuit130) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, simpleCircuit131) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Xmat, 2_nc, 0);
    circuit.addGate(dd::Ymat, 0_nc, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, simpleCircuit132) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 1_pc, 0);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_nc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
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

TEST(LimTest, singleHadamard) {
    dd::QubitCount numQubits = 24;
    dd::QubitCount target    = 23;
    auto           dd        = std::make_unique<dd::Package<>>(numQubits, dd::LIMDD_group::Pauli_group, false);

    dd::vEdge state  = dd->makeZeroState(numQubits);
    auto      h_gate = dd->makeGateDD(dd::Hmat, numQubits, target);

    std::cout << "Executing circuit with n = " << numQubits << " qubits. Hadamard applied to gate " << target << std::endl;
    std::cout << "Exporting state 0 to svg." << std::endl;
    export2Dot(state, "state0.dot", true, true, true, false, true, false);

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



TEST(LimTest, zeroEdgesTest) {
    dd::Qubit nqubits = 2;

    auto limdd = std::make_unique<dd::Package<>>(nqubits, dd::LIMDD_group::Pauli_group, false);

    auto limddState= limdd->makeZeroState(nqubits);
    EXPECT_TRUE(limddState.p->e[1] == dd::vEdge::zero);
    EXPECT_TRUE(limddState.p->e[0].p->e[1] == dd::vEdge::zero);
}

// Randomly generated circuit on 3 qubis, containing 30 gates.
TEST(LimTest, hardCircuitTest_3) {
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

    raceCircuitQMDDvsLIMDD(circuit);
}

// Randomly generated circuit on 4 qubis, containing 40 gates.
TEST(LimTest, hardCircuitTest_4) {
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
TEST(LimTest, hardCircuitTest_5) {
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
TEST(LimTest, hardCircuitTest_6) {
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
