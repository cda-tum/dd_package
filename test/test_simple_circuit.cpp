
#include "dd/Export.hpp"
#include "dd/GateMatrixDefinitions.hpp"
#include "dd/Package.hpp"
#include "dd/LimTable.hpp"
#include "dd/Package.hpp"
#include "dd/PauliAlgebra.hpp"
#include "dd/QuantumGate.hpp"
#include "dd/Definitions.hpp"

#include "gmock/gmock.h"

#include "gtest/gtest.h"
#include <iomanip>
#include <memory>
#include <random>
#include <sstream>

using namespace dd::literals;

std::ostream& operator<<(std::ostream& out, const dd::CVec& vec) {
	for (unsigned int i=0; i<vec.size(); i++) {
		out << vec[i] << ' ';
	}
	return out;
}

void simulateCircuitQMDDvsLIMDD(const dd::QuantumCircuit& circuit) {
	auto qmdd  = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
	auto qmddState = qmdd->simulateCircuit(circuit);
	dd::CVec resultQMDD = qmdd->getVector(qmddState);

	auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group);
	auto limddState= limdd->simulateCircuit(circuit);
	dd::CVec resultLimdd = limdd->getVectorLIMDD(limddState);

	std::cout << "[simulate circuit] QMDD  result: " << resultQMDD << '\n';
	std::cout << "[simulate circuit] LIMDD result: " << resultLimdd << '\n';

	EXPECT_TRUE(limdd->vectorsApproximatelyEqual(resultQMDD, resultLimdd));
}

void simulateCircuitQMDDvsLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
	auto qmdd  = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
	auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group);

	auto qmddState = qmdd->makeZeroState(circuit.n);
	auto limddState= limdd->makeZeroState(circuit.n);
	dd::CVec resultQMDD, resultLIMDD;

	for (unsigned int gate=0; gate<circuit.gates.size(); gate++) {
		std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to QMDD.\n";
		qmddState   = qmdd ->applyGate(circuit.gates[gate], qmddState);
		std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to LIMDD.\n";
		limddState  = limdd->applyGate(circuit.gates[gate], limddState);

        dd::export2Dot(qmddState, "pre_qmdd.dot", true, true, false, false, false);
        dd::export2Dot(limddState, "pre_limdd.dot", true, true, false, false, false);

		resultQMDD  = qmdd ->getVector(qmddState);
		resultLIMDD = limdd->getVector(limddState);
//		resultLIMDD = limdd->getVectorLIMDD(limddState);
		std::cout << "[simulate circuit] Intermediate states after " << gate + 1 << " gates.\n";
		std::cout << "[simulate circuit] QMDD  result: " << resultQMDD << '\n';
		std::cout << "[simulate circuit] LIMDD result: " << resultLIMDD << '\n';
		if (!limdd->vectorsApproximatelyEqual(resultQMDD, resultLIMDD)) {
			std::cout << "[simulate circuit] These intermediate vectors differ; aborting simulation.\n";
            dd::export2Dot(qmddState, "qmdd.dot", true, true, false, false, false);
            dd::export2Dot(limddState, "limdd.dot", true, true, false, false, false);
			EXPECT_TRUE(false);
			break;
		}
	}
}

TEST(LimTest, simpleCircuit1) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Xmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit2) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Ymat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit3) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Zmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit4) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Smat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit5) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit6) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit7) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit8) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit9) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit10) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit11) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit12) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Zmat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit13) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit14) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit15) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Xmat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit16) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Ymat, 0);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit17) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit18) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit19) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Ymat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit20) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Ymat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit21) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Smat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit22) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Smat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit23) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit24) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Smat, 1);
	c.addGate(dd::Smat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit25) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Smat, 0);
	c.addGate(dd::Smat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit26) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Smat, 1);
	c.addGate(dd::Smat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit27) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit28) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0);
	c.addGate(dd::Xmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit29) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0);
	c.addGate(dd::Hmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit30) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0);
	c.addGate(dd::Xmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit31) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 1_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit32) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 1);
	c.addGate(dd::Xmat, 1_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit33) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 1);
	c.addGate(dd::Hmat, 1_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit34) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Xmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit35) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 1);
	c.addGate(dd::Xmat, 1_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit36) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit37) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Hmat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit38) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit39) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit40) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 2);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit41) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Xmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit42) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 1);
	c.addGate(dd::Xmat, 1_pc, 2);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit43) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Xmat, 0_pc, 2);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit44) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 1);
	c.addGate(dd::Xmat, 1_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit45) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 2);
	c.addGate(dd::Xmat, 2_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit46) {
	dd::QuantumCircuit c(3);
	c.addGate(dd::Hmat, 2);
	c.addGate(dd::Xmat, 2_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit47) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Tmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit48) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Tmat, 0);
	c.addGate(dd::Tmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit49) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Tmat, 0);
	c.addGate(dd::Tmat, 0);
	c.addGate(dd::Tmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit50) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Tmat, 0);
	c.addGate(dd::Tmat, 0);
	c.addGate(dd::Tmat, 0);
	c.addGate(dd::Tmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit51) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0);
	c.addGate(dd::Tmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit52) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Tmat, 0_pc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit53) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 1);
	c.addGate(dd::Tmat, 1_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit54) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Tmat, 1);
	c.addGate(dd::Hmat, 1);
	c.addGate(dd::Tmat, 1_pc, 0);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit55) {
	dd::QuantumCircuit c(1);
	c.addGate(dd::Hmat, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit56) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Xmat, 0);
	c.addGate(dd::Xmat, 0_nc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit57) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Tmat, 0_nc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit58) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Tmat, 0);
	c.addGate(dd::Tmat, 0_nc, 1);

	simulateCircuitQMDDvsLIMDD(c);
}

TEST(LimTest, simpleCircuit59) {
	dd::QuantumCircuit c(2);
	c.addGate(dd::Hmat, 0);
	c.addGate(dd::Tmat, 0_nc, 1);
	c.addGate(dd::Tmat, 0);

	simulateCircuitQMDDvsLIMDD(c);
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
	c.addGate(dd::Hmat, 0);

	simulateCircuitQMDDvsLIMDDGateByGate(c);
}


