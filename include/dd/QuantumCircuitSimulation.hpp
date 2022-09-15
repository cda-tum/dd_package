//
// Created by lieuwe on 11-8-22.
//

#ifndef DDPACKAGE_SIMULATION_HPP
#define DDPACKAGE_SIMULATION_HPP

#include "Package.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

void simulateCircuitLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
    auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false);
//    auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group, false);

    auto limddState= limdd->makeZeroState(circuit.n);
    limdd->incRef(limddState);

    bool circuitIsCliffordSoFar = true;  // Flag is set to false as soon as a non-Clifford gate is applied

    for (unsigned int gate=0; gate<circuit.gates.size(); gate++) {
        //        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to QMDD.\n";
        //        qmddState   = qmdd ->applyGate(circuit.gates[gate], qmddState);
        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to LIMDD." << std::endl;
        auto tmp  = limdd->applyGate(circuit.gates[gate], limddState);
        limdd->decRef(limddState);
        limddState = tmp;
        limdd->incRef(limddState);
        limdd->garbageCollect();

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
//        simulateCircuitLIMDDGateByGate(circuit);
//        return;
    auto qmdd  = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
    auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false);

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
        //		std::cout << "[simulate circuit] Intermediate states after " << gate + 1 << " gates.\n";
        //		std::cout << "[simulate circuit] QMDD  result: " << resultQMDD << '\n';
        //		std::cout << "[simulate circuit] LIMDD result: " << resultLIMDD << '\n';

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
        std::cout << "[simulate circuit] QMDD mul statistics: ";
        qmdd->matrixVectorMultiplication.printStatistics();
        std::cout << "[simulate circuit] LIMDD mul statistics: ";
        limdd->matrixVectorMultiplication.printStatistics();

        std::cout << "[simulate circuit] QMDD add statistics: ";
        qmdd->vectorAdd.printStatistics();
        std::cout << "[simulate circuit] LIMDD add statistics: ";
        limdd->vectorAdd.printStatistics();
    }

    std::cout << "[simulate circuit] Number of Unique lims: " <<  qmdd->limCount(qmddState) << std::endl;
    std::cout << "[simulate circuit] Number of Unique numbers: " <<  qmdd->numberCount(qmddState) << std::endl;

    std::cout << "[simulate circuit] Number of Unique lims: " <<  limdd->limCount(limddState) << std::endl;
    std::cout << "[simulate circuit] Number of Unique numbers: " <<  limdd->numberCount(limddState) << std::endl;
}

#endif //DDPACKAGE_SIMULATION_HPP
