
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

using namespace dd::literals;

std::ostream& operator<<(std::ostream& out, const dd::CVec& vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        out << vec[i] << ' ';
    }
    return out;
}

void simulateCircuitQMDDvsLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
    auto qmdd  = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
    auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, true, false);

    auto              qmddState  = qmdd->makeZeroState(circuit.n);
    auto              limddState = limdd->makeZeroState(circuit.n);
    dd::CVec          resultQMDD, resultLIMDD;
    std::stringstream dotfilenameStream;

    bool circuitIsCliffordSoFar = true; // Flag is set to false as soon as a non-Clifford gate is applied

    for (unsigned int gate = 0; gate < circuit.gates.size(); gate++) {
        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to QMDD.\n";
        qmddState = qmdd->applyGate(circuit.gates[gate], qmddState);
        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to LIMDD.\n";
        limddState = limdd->applyGate(circuit.gates[gate], limddState);

        resultQMDD  = qmdd->getVector(qmddState);
        resultLIMDD = limdd->getVector(limddState);
//        std::cout << "[simulate circuit] Intermediate states after " << gate + 1 << " gates.\n";
//        std::cout << "[simulate circuit] QMDD  result: " << resultQMDD << '\n';
//        std::cout << "[simulate circuit] LIMDD result: " << resultLIMDD << '\n';

        if (!limdd->vectorsApproximatelyEqual(resultQMDD, resultLIMDD)) {
            std::cout << "[simulate circuit] These intermediate vectors differ; aborting simulation.\n";
            dd::export2Dot(qmddState, "qmdd.dot", false, true, true, false, true, false);
            dd::export2Dot(limddState, "limdd.dot", false, true, true, false, true, false);
            EXPECT_TRUE(false);
            break;
        }
        if (!circuit.gates[gate].isCliffordGate()) {
            circuitIsCliffordSoFar = false;
        }
        if (circuitIsCliffordSoFar) {
            if (!limdd->isTower(limddState)) {
                std::cout << "[simulate circuit] ERROR Expected a tower, but the LIMDD is not a tower. Exporting:\n";
                dd::export2Dot(limddState, "limdd.dot", false, true, true, false, true, false);
                EXPECT_TRUE(false);
                break;
            }
            if (limddState.p->limVector.size() != circuit.n) {
                std::cout << "[simulate circuit] ERROR Stabilizer state has " << limddState.p->limVector.size() << " stabilizers; expected n = " << (int)circuit.n << ".\n";
                //				dd::export2Dot(limddState, "limdd-less-than-n-stabilizers.dot", false, true, true, false, true, false);
                EXPECT_TRUE(false);
                break;
            }
        }
        std::cout << "[simulate circuit] QMDD mul statistics: ";
        qmdd->matrixVectorMultiplication.printStatistics();
        std::cout << "[simulate circuit] LIMDD mul statistics: ";
        limdd->matrixVectorMultiplication.printStatistics();

        std::cout << "[simulate circuit] QMDD add statistics: ";
        qmdd->vectorAdd.printStatistics();
        std::cout << "[simulate circuit] LIMDD add statistics: ";
        limdd->vectorAdd.printStatistics();
    }
}

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

TEST(LimTest, simpleCircuit110) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit111) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit112) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 2);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit113) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 3_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 3);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit114) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 3);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit115) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 3_pc, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit116) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Zmat, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit117) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Ymat, 3);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit118) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 3_pc, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 3);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 1);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 0_pc, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Zmat, 1);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit119) {
    dd::QuantumCircuit c(4);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 2);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Ymat, 0);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Xmat, 1_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 0);
    c.addGate(dd::Xmat, 3);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Xmat, 2_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 0);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Ymat, 3);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 3_pc, 3);
    c.addGate(dd::Ymat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Ymat, 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 3);
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

TEST(LimTest, simpleCircuit_vqe_10) {
    dd::QuantumCircuit c(10);
    c.addGate(dd::U3mat(2.68662123819055, 0, 0), 0);
    c.addGate(dd::U3mat(-1.89057357852147, 0, 0), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(0.526156621282547, 0, 0), 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(-2.65877607637322, 0, 0), 3);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(2.28164362790185, 0, 0), 4);
    c.addGate(dd::Xmat, 0_pc, 4);
    c.addGate(dd::Xmat, 1_pc, 4);
    c.addGate(dd::Xmat, 2_pc, 4);
    c.addGate(dd::Xmat, 3_pc, 4);
    c.addGate(dd::U3mat(-0.858823619363636, 0, 0), 5);
    c.addGate(dd::Xmat, 0_pc, 5);
    c.addGate(dd::Xmat, 1_pc, 5);
    c.addGate(dd::Xmat, 2_pc, 5);
    c.addGate(dd::Xmat, 3_pc, 5);
    c.addGate(dd::Xmat, 4_pc, 5);
    c.addGate(dd::U3mat(-1.79374665455828, 0, 0), 6);
    c.addGate(dd::Xmat, 0_pc, 6);
    c.addGate(dd::Xmat, 1_pc, 6);
    c.addGate(dd::Xmat, 2_pc, 6);
    c.addGate(dd::Xmat, 3_pc, 6);
    c.addGate(dd::Xmat, 4_pc, 6);
    c.addGate(dd::Xmat, 5_pc, 6);
    c.addGate(dd::U3mat(-1.044215261399, 0, 0), 7);
    c.addGate(dd::Xmat, 0_pc, 7);
    c.addGate(dd::Xmat, 1_pc, 7);
    c.addGate(dd::Xmat, 2_pc, 7);
    c.addGate(dd::Xmat, 3_pc, 7);
    c.addGate(dd::Xmat, 4_pc, 7);
    c.addGate(dd::Xmat, 5_pc, 7);
    c.addGate(dd::Xmat, 6_pc, 7);
    c.addGate(dd::U3mat(1.57777927085946, 0, 0), 8);
    c.addGate(dd::Xmat, 0_pc, 8);
    c.addGate(dd::Xmat, 1_pc, 8);
    c.addGate(dd::Xmat, 2_pc, 8);
    c.addGate(dd::Xmat, 3_pc, 8);
    c.addGate(dd::Xmat, 4_pc, 8);
    c.addGate(dd::Xmat, 5_pc, 8);
    c.addGate(dd::Xmat, 6_pc, 8);
    c.addGate(dd::Xmat, 7_pc, 8);
    c.addGate(dd::U3mat(0.0584568342741303, 0, 0), 9);
    c.addGate(dd::Xmat, 0_pc, 9);
    c.addGate(dd::U3mat(0.493785215150024, 0, 0), 0);
    c.addGate(dd::Xmat, 1_pc, 9);
    c.addGate(dd::U3mat(2.17528225837145, 0, 0), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 9);
    c.addGate(dd::U3mat(2.38782953761232, 0, 0), 2);
    c.addGate(dd::Xmat, 0_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 3_pc, 9);
    c.addGate(dd::U3mat(-2.74456490781863, 0, 0), 3);
    c.addGate(dd::Xmat, 0_pc, 3);
    c.addGate(dd::Xmat, 1_pc, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 4_pc, 9);
    c.addGate(dd::U3mat(-0.944693531787479, 0, 0), 4);
    c.addGate(dd::Xmat, 0_pc, 4);
    c.addGate(dd::Xmat, 1_pc, 4);
    c.addGate(dd::Xmat, 2_pc, 4);
    c.addGate(dd::Xmat, 3_pc, 4);
    c.addGate(dd::Xmat, 5_pc, 9);
    c.addGate(dd::U3mat(1.58084675679236, 0, 0), 5);
    c.addGate(dd::Xmat, 0_pc, 5);
    c.addGate(dd::Xmat, 1_pc, 5);
    c.addGate(dd::Xmat, 2_pc, 5);
    c.addGate(dd::Xmat, 3_pc, 5);
    c.addGate(dd::Xmat, 4_pc, 5);
    c.addGate(dd::Xmat, 6_pc, 9);
    c.addGate(dd::U3mat(-1.23567451135838, 0, 0), 6);
    c.addGate(dd::Xmat, 0_pc, 6);
    c.addGate(dd::Xmat, 1_pc, 6);
    c.addGate(dd::Xmat, 2_pc, 6);
    c.addGate(dd::Xmat, 3_pc, 6);
    c.addGate(dd::Xmat, 4_pc, 6);
    c.addGate(dd::Xmat, 5_pc, 6);
    c.addGate(dd::Xmat, 7_pc, 9);
    c.addGate(dd::U3mat(-1.05552653486066, 0, 0), 7);
    c.addGate(dd::Xmat, 0_pc, 7);
    c.addGate(dd::Xmat, 1_pc, 7);
    c.addGate(dd::Xmat, 2_pc, 7);
    c.addGate(dd::Xmat, 3_pc, 7);
    c.addGate(dd::Xmat, 4_pc, 7);
    c.addGate(dd::Xmat, 5_pc, 7);
    c.addGate(dd::Xmat, 6_pc, 7);
    c.addGate(dd::Xmat, 8_pc, 9);
    c.addGate(dd::U3mat(2.31217171104892, 0, 0), 8);
    c.addGate(dd::Xmat, 0_pc, 8);
    c.addGate(dd::Xmat, 1_pc, 8);
    c.addGate(dd::Xmat, 2_pc, 8);
    c.addGate(dd::Xmat, 3_pc, 8);
    c.addGate(dd::Xmat, 4_pc, 8);
    c.addGate(dd::Xmat, 5_pc, 8);
    c.addGate(dd::Xmat, 6_pc, 8);
    c.addGate(dd::Xmat, 7_pc, 8);
    c.addGate(dd::U3mat(1.31263458235761, 0, 0), 9);
    c.addGate(dd::Xmat, 0_pc, 9);
    c.addGate(dd::U3mat(-2.40484784824733, 0, 0), 0);
    c.addGate(dd::Xmat, 1_pc, 9);
    c.addGate(dd::U3mat(0.412079032901195, 0, 0), 1);
    c.addGate(dd::Xmat, 2_pc, 9);
    c.addGate(dd::U3mat(-2.34348535750732, 0, 0), 2);
    c.addGate(dd::Xmat, 3_pc, 9);
    c.addGate(dd::U3mat(-3.04224930574056, 0, 0), 3);
    c.addGate(dd::Xmat, 4_pc, 9);
    c.addGate(dd::U3mat(-1.78983602234406, 0, 0), 4);
    c.addGate(dd::Xmat, 5_pc, 9);
    c.addGate(dd::U3mat(-2.03376426365639, 0, 0), 5);
    c.addGate(dd::Xmat, 6_pc, 9);
    c.addGate(dd::U3mat(1.5067179271741, 0, 0), 6);
    c.addGate(dd::Xmat, 7_pc, 9);
    c.addGate(dd::U3mat(0.371692355160145, 0, 0), 7);
    c.addGate(dd::Xmat, 8_pc, 9);
    c.addGate(dd::U3mat(1.41962968316013, 0, 0), 8);
    c.addGate(dd::U3mat(0.515209311568382, 0, 0), 9);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
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

TEST(LimTest, simpleCircuit_graphstate_24) {
    dd::QuantumCircuit c(24);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 4);
    c.addGate(dd::Xmat, 2_pc, 4);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 6);
    c.addGate(dd::Xmat, 5_pc, 6);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 7);
    c.addGate(dd::Xmat, 0_pc, 7);
    c.addGate(dd::Hmat, 7);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 8);
    c.addGate(dd::Xmat, 6_pc, 8);
    c.addGate(dd::Hmat, 8);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 9);
    c.addGate(dd::Xmat, 8_pc, 9);
    c.addGate(dd::Hmat, 9);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 11);
    c.addGate(dd::Xmat, 4_pc, 11);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 11);
    c.addGate(dd::Xmat, 10_pc, 11);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 12);
    c.addGate(dd::Xmat, 3_pc, 12);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 12);
    c.addGate(dd::Xmat, 7_pc, 12);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 14);
    c.addGate(dd::Xmat, 13_pc, 14);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
    c.addGate(dd::Xmat, 13_pc, 16);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 16);
    c.addGate(dd::Xmat, 15_pc, 16);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 18);
    c.addGate(dd::Xmat, 9_pc, 18);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 18);
    c.addGate(dd::Xmat, 17_pc, 18);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 19);
    c.addGate(dd::Xmat, 15_pc, 19);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 19);
    c.addGate(dd::Xmat, 17_pc, 19);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 20);
    c.addGate(dd::Xmat, 5_pc, 20);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 21);
    c.addGate(dd::Xmat, 1_pc, 21);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 22);
    c.addGate(dd::Xmat, 10_pc, 22);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 22);
    c.addGate(dd::Xmat, 21_pc, 22);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 23);
    c.addGate(dd::Xmat, 14_pc, 23);
    c.addGate(dd::U3mat(0, -dd::PI, -dd::PI), 23);
    c.addGate(dd::Xmat, 20_pc, 23);
    c.addGate(dd::Hmat, 2);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}

TEST(LimTest, simpleCircuit_qaoa_12) {
    dd::QuantumCircuit c(12);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Xmat, 3_pc, 4);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 4);
    c.addGate(dd::Xmat, 3_pc, 4);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Xmat, 1_pc, 5);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 5);
    c.addGate(dd::Xmat, 1_pc, 5);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 1);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::Xmat, 4_pc, 6);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 6);
    c.addGate(dd::Xmat, 4_pc, 6);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 4);
    c.addGate(dd::Hmat, 7);
    c.addGate(dd::Xmat, 5_pc, 7);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 7);
    c.addGate(dd::Xmat, 5_pc, 7);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 5);
    c.addGate(dd::Xmat, 6_pc, 7);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 7);
    c.addGate(dd::Xmat, 6_pc, 7);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 6);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 7);
    c.addGate(dd::Hmat, 8);
    c.addGate(dd::Xmat, 2_pc, 8);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 8);
    c.addGate(dd::Xmat, 2_pc, 8);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 5);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 5);
    c.addGate(dd::Xmat, 1_pc, 5);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 1);
    c.addGate(dd::Xmat, 5_pc, 7);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 7);
    c.addGate(dd::Xmat, 5_pc, 7);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 5);
    c.addGate(dd::Hmat, 9);
    c.addGate(dd::Xmat, 0_pc, 9);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 9);
    c.addGate(dd::Xmat, 0_pc, 9);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 10);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 10);
    c.addGate(dd::Xmat, 0_pc, 10);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 0);
    c.addGate(dd::Xmat, 3_pc, 10);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 10);
    c.addGate(dd::Xmat, 3_pc, 10);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 10);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 3);
    c.addGate(dd::Xmat, 3_pc, 4);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 4);
    c.addGate(dd::Xmat, 3_pc, 4);
    c.addGate(dd::Xmat, 4_pc, 6);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 6);
    c.addGate(dd::Xmat, 4_pc, 6);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 4);
    c.addGate(dd::Xmat, 6_pc, 7);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 7);
    c.addGate(dd::Xmat, 6_pc, 7);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 6);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 7);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 8_pc, 11);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 11);
    c.addGate(dd::Xmat, 8_pc, 11);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 8);
    c.addGate(dd::Xmat, 2_pc, 8);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 8);
    c.addGate(dd::Xmat, 2_pc, 8);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 2);
    c.addGate(dd::Xmat, 9_pc, 11);
    c.addGate(dd::U3mat(0, 0, 1.9931892155424), 11);
    c.addGate(dd::Xmat, 9_pc, 11);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 11);
    c.addGate(dd::Xmat, 8_pc, 11);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 11);
    c.addGate(dd::Xmat, 8_pc, 11);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 8);
    c.addGate(dd::U3mat(-3.01414030579569, -dd::PI / 2, dd::PI / 2), 9);
    c.addGate(dd::Xmat, 0_pc, 9);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 9);
    c.addGate(dd::Xmat, 0_pc, 9);
    c.addGate(dd::Xmat, 0_pc, 10);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 10);
    c.addGate(dd::Xmat, 0_pc, 10);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 0);
    c.addGate(dd::Xmat, 3_pc, 10);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 10);
    c.addGate(dd::Xmat, 3_pc, 10);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 10);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 3);
    c.addGate(dd::Xmat, 9_pc, 11);
    c.addGate(dd::U3mat(0, 0, -5.38200707049379), 11);
    c.addGate(dd::Xmat, 9_pc, 11);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 11);
    c.addGate(dd::U3mat(4.14813772565845, -dd::PI / 2, dd::PI / 2), 9);
    simulateCircuitQMDDvsLIMDDGateByGate(c);
}
