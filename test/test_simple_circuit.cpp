
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

void simulateCircuitLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
    auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false, false);

    auto limddState= limdd->makeZeroState(circuit.n);

    bool circuitIsCliffordSoFar = true;  // Flag is set to false as soon as a non-Clifford gate is applied

    for (unsigned int gate=0; gate<circuit.gates.size(); gate++) {
//        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to QMDD.\n";
//        qmddState   = qmdd ->applyGate(circuit.gates[gate], qmddState);
        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to LIMDD.\n";
        limddState  = limdd->applyGate(circuit.gates[gate], limddState);

//        resultQMDD  = qmdd ->getVector(qmddState);
//        resultLIMDD = limdd->getVector(limddState);
//        std::cout << "[simulate circuit] Intermediate states after " << gate + 1 << " gates.\n";
//        std::cout << "[simulate circuit] QMDD  result: " << resultQMDD << '\n';
//        std::cout << "[simulate circuit] LIMDD result: " << resultLIMDD << '\n';
//
//        std::cout << "[simulate circuit] QMDD mul statistics: ";
//        qmdd->matrixVectorMultiplication.printStatistics();
//        std::cout << "[simulate circuit] LIMDD mul statistics: ";
//        limdd->matrixVectorMultiplication.printStatistics();
//
//        std::cout << "[simulate circuit] QMDD add statistics: ";
//        qmdd->vectorAdd.printStatistics();
//        std::cout << "[simulate circuit] LIMDD add statistics: ";
//        limdd->vectorAdd.printStatistics();

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
                std::cout << "[simulate circuit] ERROR Stabilizer state has " << limddState.p->limVector.size() << " stabilizers; expected n = " << (int) circuit.n << ".\n";
//              dd::export2Dot(limddState, "limdd-less-than-n-stabilizers.dot", false, true, true, false, true, false);
                EXPECT_TRUE(false);
                break;
            }
        }
    }
}

void simulateCircuitQMDDvsLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
    simulateCircuitLIMDDGateByGate(circuit);
    return;
	auto qmdd  = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
	auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false, false);

	auto qmddState = qmdd->makeZeroState(circuit.n);
	auto limddState= limdd->makeZeroState(circuit.n);
	dd::CVec resultQMDD, resultLIMDD;
	std::stringstream dotfilenameStream;

	bool circuitIsCliffordSoFar = true;  // Flag is set to false as soon as a non-Clifford gate is applied

	for (unsigned int gate=0; gate<circuit.gates.size(); gate++) {
		std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to QMDD.\n";
		qmddState   = qmdd ->applyGate(circuit.gates[gate], qmddState);
		std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to LIMDD.\n";
		limddState  = limdd->applyGate(circuit.gates[gate], limddState);

		resultQMDD  = qmdd ->getVector(qmddState);
		resultLIMDD = limdd->getVector(limddState);
		std::cout << "[simulate circuit] Intermediate states after " << gate + 1 << " gates.\n";
		std::cout << "[simulate circuit] QMDD  result: " << resultQMDD << '\n';
		std::cout << "[simulate circuit] LIMDD result: " << resultLIMDD << '\n';

        std::cout << "[simulate circuit] QMDD mul statistics: ";
        qmdd->matrixVectorMultiplication.printStatistics();
        std::cout << "[simulate circuit] LIMDD mul statistics: ";
        limdd->matrixVectorMultiplication.printStatistics();

        std::cout << "[simulate circuit] QMDD add statistics: ";
        qmdd->vectorAdd.printStatistics();
        std::cout << "[simulate circuit] LIMDD add statistics: ";
        limdd->vectorAdd.printStatistics();

		if (!limdd->vectorsApproximatelyEqual(resultQMDD, resultLIMDD)) {
			std::cout << "[simulate circuit] These intermediate vectors differ; aborting simulation.\n";
            dd::export2Dot(qmddState,  "qmdd.dot",  false, true, true, false, true, false);
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
				std::cout << "[simulate circuit] ERROR Stabilizer state has " << limddState.p->limVector.size() << " stabilizers; expected n = " << (int) circuit.n << ".\n";
//				dd::export2Dot(limddState, "limdd-less-than-n-stabilizers.dot", false, true, true, false, true, false);
				EXPECT_TRUE(false);
				break;
			}
		}
//		dotfilenameStream = std::stringstream();
//		dotfilenameStream << "limdd-gate" << gate << ".dot";
//		dd::export2Dot(limddState, dotfilenameStream.str(), false, true, true, false, true, false);
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

TEST(LimTest, simpleClifford128) {
    dd::QuantumCircuit c(18);
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
    c.addGate(dd::Zmat, 0_pc,  2);
    c.addGate(dd::Zmat, 1_pc,  14);
    c.addGate(dd::Zmat, 3_pc,  10);
    c.addGate(dd::Zmat, 4_pc,  13);
    c.addGate(dd::Zmat, 10_pc, 11);
    c.addGate(dd::Zmat, 11_pc, 14);
    c.addGate(dd::Zmat, 17_pc, 16);
    c.addGate(dd::Zmat, 6_pc,  1);
    c.addGate(dd::Zmat, 7_pc,  15);
    c.addGate(dd::Zmat, 8_pc,  10);
    c.addGate(dd::Zmat, 11_pc, 1);
    c.addGate(dd::Zmat, 15_pc, 3);
    c.addGate(dd::Zmat, 14_pc, 5);
    c.addGate(dd::Zmat, 16_pc, 2);
    c.addGate(dd::Zmat, 13_pc, 6);
    c.addGate(dd::Zmat, 2_pc,  17);
    c.addGate(dd::Zmat, 3_pc,  16);
    c.addGate(dd::Zmat, 4_pc,  7);
    c.addGate(dd::Zmat, 1_pc,  2);
    c.addGate(dd::Zmat, 6_pc,  3);
    c.addGate(dd::Zmat, 3_pc,  6);
    c.addGate(dd::Zmat, 16_pc, 14 );
    c.addGate(dd::Zmat, 17_pc, 17);
    c.addGate(dd::Zmat, 2_pc,  13);
    c.addGate(dd::Zmat, 13_pc, 10);
    c.addGate(dd::Zmat, 11_pc, 12);
    c.addGate(dd::Zmat, 5_pc,  6);
    c.addGate(dd::Zmat, 7_pc,  6);
    c.addGate(dd::Zmat, 3_pc,  6);
    c.addGate(dd::Zmat, 2_pc,  6);

    simulateCircuitLIMDDGateByGate(c);
}

TEST(LimTest, simpleClifford129) {
    dd::QuantumCircuit c(19);
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
    c.addGate(dd::Zmat, 0_pc,  2);
    c.addGate(dd::Zmat, 1_pc,  14);
    c.addGate(dd::Zmat, 3_pc,  10);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 4_pc,  13);
    c.addGate(dd::Zmat, 10_pc, 11);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Zmat, 11_pc, 14);
    c.addGate(dd::Zmat, 17_pc, 16);
    c.addGate(dd::Hmat, 11);
    c.addGate(dd::Zmat, 6_pc,  1);
    c.addGate(dd::Zmat, 7_pc,  15);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Zmat, 8_pc,  10);
    c.addGate(dd::Zmat, 11_pc, 1);
    c.addGate(dd::Hmat, 8);
    c.addGate(dd::Zmat, 15_pc, 3);
    c.addGate(dd::Zmat, 14_pc, 5);
    c.addGate(dd::Hmat, 14);
    c.addGate(dd::Zmat, 16_pc, 2);
    c.addGate(dd::Zmat, 13_pc, 6);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Zmat, 2_pc,  17);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Zmat, 3_pc,  16);
    c.addGate(dd::Zmat, 4_pc,  7);
    c.addGate(dd::Hmat, 4);
    c.addGate(dd::Zmat, 1_pc,  2);
    c.addGate(dd::Zmat, 6_pc,  3);
    c.addGate(dd::Hmat, 6);
    c.addGate(dd::Zmat, 3_pc,  6);
    c.addGate(dd::Zmat, 16_pc, 14 );
    c.addGate(dd::Zmat, 17_pc, 16);
    c.addGate(dd::Hmat, 17);
    c.addGate(dd::Zmat, 2_pc,  13);
    c.addGate(dd::Zmat, 13_pc, 10);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Zmat, 11_pc, 12);
    c.addGate(dd::Zmat, 5_pc,  6);
    c.addGate(dd::Hmat, 5);
    c.addGate(dd::Zmat, 7_pc,  6);
    c.addGate(dd::Zmat, 3_pc,  6);
    c.addGate(dd::Zmat, 2_pc,  6);
    c.addGate(dd::Hmat, 4);

    simulateCircuitLIMDDGateByGate(c);
}

//TEST(LimTest, simpleClifford130) {
//    dd::QuantumCircuit c(63);
//    c.addGate(dd::Hmat, 0);
//    c.addGate(dd::Hmat, 1);
//    c.addGate(dd::Hmat, 2);
//    c.addGate(dd::Hmat, 3);
//    c.addGate(dd::Hmat, 4);
//    c.addGate(dd::Hmat, 5);
//    c.addGate(dd::Hmat, 6);
//    c.addGate(dd::Hmat, 7);
//    c.addGate(dd::Hmat, 8);
//    c.addGate(dd::Hmat, 9);
//    c.addGate(dd::Hmat, 10);
//    c.addGate(dd::Hmat, 11);
//    c.addGate(dd::Hmat, 12);
//    c.addGate(dd::Hmat, 13);
//    c.addGate(dd::Hmat, 14);
//    c.addGate(dd::Hmat, 15);
//    c.addGate(dd::Hmat, 16);
//    c.addGate(dd::Hmat, 17);
//    c.addGate(dd::Hmat, 18);
//    c.addGate(dd::Hmat, 19);
//    c.addGate(dd::Hmat, 20);
//    c.addGate(dd::Hmat, 21);
//    c.addGate(dd::Hmat, 22);
//    c.addGate(dd::Hmat, 23);
//    c.addGate(dd::Hmat, 24);
//    c.addGate(dd::Hmat, 25);
//    c.addGate(dd::Hmat, 26);
//    c.addGate(dd::Hmat, 27);
//    c.addGate(dd::Hmat, 28);
//    c.addGate(dd::Hmat, 29);
//    c.addGate(dd::Hmat, 30);
//    c.addGate(dd::Hmat, 31);
//    c.addGate(dd::Hmat, 32);
//    c.addGate(dd::Hmat, 33);
//    c.addGate(dd::Hmat, 34);
//    c.addGate(dd::Hmat, 35);
//    c.addGate(dd::Hmat, 36);
//    c.addGate(dd::Hmat, 37);
//    c.addGate(dd::Hmat, 38);
//    c.addGate(dd::Hmat, 39);
//    c.addGate(dd::Hmat, 40);
//    c.addGate(dd::Hmat, 41);
//    c.addGate(dd::Hmat, 42);
//    c.addGate(dd::Hmat, 43);
//    c.addGate(dd::Hmat, 44);
//    c.addGate(dd::Hmat, 45);
//    c.addGate(dd::Hmat, 46);
//    c.addGate(dd::Hmat, 47);
//    c.addGate(dd::Hmat, 48);
//    c.addGate(dd::Hmat, 49);
//    c.addGate(dd::Hmat, 50);
//    c.addGate(dd::Hmat, 51);
//    c.addGate(dd::Hmat, 52);
//    c.addGate(dd::Hmat, 53);
//    c.addGate(dd::Hmat, 54);
//    c.addGate(dd::Hmat, 55);
//    c.addGate(dd::Hmat, 56);
//    c.addGate(dd::Hmat, 57);
//    c.addGate(dd::Hmat, 58);
//    c.addGate(dd::Hmat, 59);
//    c.addGate(dd::Hmat, 60);
//    c.addGate(dd::Hmat, 61);
//    c.addGate(dd::Hmat, 62);
//
//    simulateCircuitLIMDDGateByGate(c);
//}


TEST(LimTest, basis_trotter_n4) {
    dd::QuantumCircuit c(4);

    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.08130614625631793
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.08130614625631793
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 1);
    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 3);
    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 2);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**-0.05102950815299322
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**0.05102950815299322
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: CZ**-0.048279591094340914
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 0.5), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4758602045), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.4758602045, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9758602045, 0), 1);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    // Gate: CZ**-0.022156912718971442
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.75), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.25), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4889215436), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.2389215436, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.7389215436, 0), 3);

    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);

    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 3);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);

    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 3);
    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 0);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 2);
    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 1);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.9500630905158097
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.9500630905158097
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: CZ**-0.013654184706660842
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4931729076), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4931729076, dd::PI * 1.0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9931729076, 0), 2);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    // Gate: CZ**-0.006328040119021747
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4961253835), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.9961253835), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4968359799), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5007105964, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0007105964, 0), 0);

    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);

    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 0);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);

    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 0);
    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 1);
    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 2);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**-0.5017530508495694
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**0.5017530508495694
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: CZ**-0.00046375097365492423
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5001274262), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0001274262), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4997681245), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4996406983, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9996406983, 0), 1);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    // Gate: CZ**-0.0004129506013584246
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.4998373235), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9998373235), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4997935247), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4999562012, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9999562012, dd::PI * 1.0), 3);

    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);

    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 3);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);

    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 3);
    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 0);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 2);
    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 1);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.4158482042253096
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.4158482042253096
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);

    c.addGate(dd::Zmat, 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 1);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**0.08130614625631793
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**-0.08130614625631793
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);

    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 2);
    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 0);
    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 1);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.05102950815299322
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.05102950815299322
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: CZ**-0.048279591094340914
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 0.5), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4758602045), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.4758602045, dd::PI * 1.0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9758602045, 0), 2);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    // Gate: CZ**-0.022156912718971442
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.75), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.25), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4889215436), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.2389215436, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.7389215436, 0), 0);

    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);

    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 0);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);

    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 0);
    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 1);
    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 2);
    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 2);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**-0.9500630905158097
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**0.9500630905158097
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: CZ**-0.013654184706660842
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4931729076), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4931729076, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9931729076, 0), 1);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    // Gate: CZ**-0.006328040119021747
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4961253835), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.9961253835), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4968359799), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5007105964, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0007105964, 0), 3);

    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);

    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 3);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);

    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 3);
    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 0);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 2);
    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 1);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.5017530508495694
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.5017530508495694
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: CZ**-0.00046375097365492423
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5001274262), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0001274262), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4997681245), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4996406983, dd::PI * 1.0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9996406983, 0), 2);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    // Gate: CZ**-0.0004129506013584246
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.4998373235), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9998373235), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4997935247), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4999562012, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9999562012, dd::PI * 1.0), 0);

    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);

    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 0);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);

    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 0);
    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 1);
    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 2);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**-0.4158482042253096
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**0.4158482042253096
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    c.addGate(dd::Zmat, 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    c.addGate(dd::Zmat, 1);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 2);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.08130614625631793
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.08130614625631793
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.0406530731), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.0406530731), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    c.addGate(dd::RZmat(dd::PI * 0.1123177385), 1);
    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 3);
    c.addGate(dd::RZmat(dd::PI * 0.0564909955), 2);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**-0.05102950815299322
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**0.05102950815299322
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.0255147541), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.0255147541), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: CZ**-0.048279591094340914
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 0.5), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4758602045), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.4758602045, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9758602045, 0), 1);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    // Gate: CZ**-0.022156912718971442
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.75), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.25), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4889215436), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.2389215436, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.7389215436, 0), 3);

    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);

    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 1);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 3);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**-0.03270667647415345
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4836466618), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9836466618, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4836466618, 0), 2);

    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 3);
    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 0);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.0241397955), 2);
    c.addGate(dd::RZmat(dd::PI * -0.0110784564), 1);
    c.addGate(dd::Zmat, 2);
    c.addGate(dd::Zmat, 1);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.9500630905158097
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.9500630905158097
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.4750315453), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.4750315453), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: CZ**-0.013654184706660842
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4931729076), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4931729076, dd::PI * 1.0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9931729076, 0), 2);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);

    // Gate: CZ**-0.006328040119021747
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4961253835), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.9961253835), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4968359799), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5007105964, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0007105964, 0), 0);

    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);

    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 3);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 2);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 0);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 0);
    c.addGate(dd::RZmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 0);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);

    // Gate: CZ**0.009295387491454189
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0820521548), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.5820521548), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4953523063), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9225955389, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4225955389, 0), 1);

    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 0);
    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 3);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::RZmat(dd::PI * -0.0068270924), 1);
    c.addGate(dd::RZmat(dd::PI * -0.0031640201), 2);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**-0.5017530508495694
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 0);
    c.addGate(dd::Hmat, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**0.5017530508495694
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.2508765254), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.2508765254), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.5), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: CZ**-0.00046375097365492423
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.5001274262), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.0001274262), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4997681245), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4996406983, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.9996406983, 0), 1);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);

    // Gate: CZ**-0.0004129506013584246
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0, dd::PI * 1.4998373235), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9998373235), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4997935247), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.4999562012, 0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 0.9999562012, dd::PI * 1.0), 3);

    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);

    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 1);
    c.addGate(dd::RXmat(dd::PI * 0.5), 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 0);
    c.addGate(dd::RYmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RXmat(dd::PI * -0.5), 1);
    c.addGate(dd::RZmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 0);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 1);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 3);
    c.addGate(dd::RXmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 2);
    c.addGate(dd::RYmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RXmat(dd::PI * -0.5), 3);
    c.addGate(dd::RZmat(dd::PI * 0.5), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 3);

    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);

    // Gate: CZ**0.00043761426330885954
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.9993457511), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, 0, dd::PI * 1.4993457511), 2);
    c.addGate(dd::RXmat(dd::PI * 0.5), 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RXmat(dd::PI * 0.4997811929), 1);
    c.addGate(dd::RYmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RXmat(dd::PI * -0.5), 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.0008730561, dd::PI * 1.0), 1);
    c.addGate(dd::U3mat(dd::PI * 0.5, dd::PI * 1.5008730561, dd::PI * 1.0), 2);

    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 3);
    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 0);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Zmat, 3);
    c.addGate(dd::Zmat, 0);
    c.addGate(dd::RZmat(dd::PI * -0.0002318755), 2);
    c.addGate(dd::RZmat(dd::PI * -0.0002064753), 1);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    // Gate: PhasedISWAP**-0.4158482042253096
    c.addGate(dd::RZmat(dd::PI * 0.25), 3);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 3);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 3);
    c.addGate(dd::Hmat, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 3);
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);

    // Gate: PhasedISWAP**0.4158482042253096
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 0);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * 0.2079241021), 1);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.2079241021), 1);
    c.addGate(dd::Hmat, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::RZmat(dd::PI * 0.25), 0);

    // Gate: PhasedISWAP**-1.0
    c.addGate(dd::RZmat(dd::PI * 0.25), 2);
    c.addGate(dd::RZmat(dd::PI * -0.25), 1);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * -0.5), 2);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::RZmat(dd::PI * 0.5), 2);
    c.addGate(dd::Hmat, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::RZmat(dd::PI * -0.25), 2);
    c.addGate(dd::RZmat(dd::PI * 0.25), 1);

    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 3);
    c.addGate(dd::Xmat, 3_pc, 2);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 0_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 0);
    c.addGate(dd::Xmat, 2_pc, 1);
    c.addGate(dd::Xmat, 1_pc, 2);
    c.addGate(dd::Xmat, 2_pc, 1);

    simulateCircuitQMDDvsLIMDDGateByGate(c);
}
