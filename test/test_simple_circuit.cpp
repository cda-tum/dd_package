
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

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit9) {
    dd::QuantumCircuit c(1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
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

TEST(LimTest, simpleCircuit133) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Zmat, 0_nc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, simpleCircuit134) {
    dd::QuantumCircuit circuit(2);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 0);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}


// Randomly generated circuit on 3 qubis, containing 7 gates.
TEST(LimTest, simpleCircuit135) {
    dd::QuantumCircuit circuit(3);

    circuit.addGate(dd::Hmat, 1);
    circuit.addGate(dd::Hmat, 2);
    circuit.addGate(dd::Ymat, 1_pc, 2);
    circuit.addGate(dd::Ymat, 1_pc, 0);

    simulateCircuitQMDDvsLIMDDGateByGate(circuit);
}

TEST(LimTest, simpleCircuit136) {
    dd::QuantumCircuit c(2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 1);
    c.addGate(dd::U3mat(-dd::PI, 0, -dd::PI), 1);
    c.addGate(dd::U3mat(-dd::PI, -dd::PI, 0), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 1);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, zeroEdgesTest) {
    dd::Qubit nqubits = 2;

    auto limdd = std::make_unique<dd::Package<>>(nqubits, dd::LIMDD_group::Pauli_group, false);

    auto limddState= limdd->makeZeroState(nqubits);
    EXPECT_TRUE(limddState.p->e[1] == dd::vEdge::zero);
    EXPECT_TRUE(limddState.p->e[0].p->e[1] == dd::vEdge::zero);
}
