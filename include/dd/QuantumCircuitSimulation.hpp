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

    auto limddState = limdd->makeZeroState(circuit.n);
    limdd->incRef(limddState);

    bool circuitIsCliffordSoFar = true; // Flag is set to false as soon as a non-Clifford gate is applied

    for (unsigned int gate = 0; gate < circuit.gates.size(); gate++) {
        //        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to QMDD.\n";
        //        qmddState   = qmdd ->applyGate(circuit.gates[gate], qmddState);
        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to LIMDD." << std::endl;
        auto tmp = limdd->applyGate(circuit.gates[gate], limddState);
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
                std::cout << "[simulate circuit] ERROR Stabilizer state has " << limddState.p->limVector.size() << " stabilizers; expected n = " << (int)circuit.n << ".\n";
                //              dd::export2Dot(limddState, "limdd-less-than-n-stabilizers.dot", false, true, true, false, true, false);
                EXPECT_TRUE(false);
                break;
            }
        }
    }
}


void raceCircuitQMDDvsLIMDD(const dd::QuantumCircuit& circuit) {
    auto qmdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
    auto limddOld = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false,
                                                    dd::CachingStrategy::QMDDCachingStrategy);
    auto limddClifford = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false,
                                                 dd::CachingStrategy::cliffordSpecialCaching);
    auto limddLocality = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false,
                                                 dd::CachingStrategy::localityAwareCachingDirtyTrick);

    std::cout << "[race circuit] Simulating old LIMDD\n";
    // simulate old LIMDD
    clock_t limdd_old_begin = clock();
    //limddOld->simulateCircuit(circuit);
    clock_t limdd_old_end = clock();

    // simulate clifford LIMDD
    std::cout << "[race circuit] Simulating LIMDD with Clifford-specialized caching\n";
    clock_t limdd_clifford_begin = clock();
    //limddClifford->simulateCircuit(circuit);
    clock_t limdd_clifford_end = clock();

    // simulate locality-aware LIMDD
    std::cout << "[race circuit] Simulating LIMDD with locality-aware caching, but without Clifford-specialized caching\n";
    clock_t limdd_locality_begin = clock();
    limddLocality->simulateCircuit(circuit);
    clock_t limdd_locality_end = clock();

    std::cout << "[race circuit] Simulating QMDD.\n";
    // simulate QMDD
    clock_t qmdd_begin = clock();
    //qmdd->simulateCircuit(circuit);
    clock_t qmdd_end = clock();

    std::cout   <<   "QMDD time:                        " << (qmdd_end - qmdd_begin)
                << "\nLIMDD old time:                   " << (limdd_old_end - limdd_old_begin)
                << "\nLIMDD clifford-specialized time:  " << (limdd_clifford_end - limdd_clifford_begin)
                << "\nLIMDD locality-aware time:        " << (limdd_locality_end - limdd_locality_begin) << "\n";
    float ratio = ((float)(qmdd_end - qmdd_begin)) / ((float)(limdd_clifford_end - limdd_clifford_begin));
    if (ratio < 1.0f) {
        std::cout << "Worse by:                         " << 100.0*(1/ratio - 1.0f) << "%\n";
    } else {
        std::cout << "Better by:                        " << 100.0*(ratio - 1.0) << "%\n";
    }
    std::cout << "getVector: " << limddOld->getVectorCallCounter << " (should be zero)\n";
    if (limddOld->getVectorCallCounter != 0) {
        std::cout << "    ERROR getVector was called. Double-check: did you compile in debug mode?\n";
    }

    std::cout << "QMDD  --  call counter statistics:\n";
    qmdd->printCallCounterStatistics();
    std::cout << "nodes       " << qmdd->vUniqueTable.getNodeCount() << "\n";
    std::cout << "LIMDD old                     -- call counter statistics:\n";
    limddOld->printCallCounterStatistics();
    std::cout << "nodes       " << limddOld->vUniqueTable.getNodeCount() << "\n";
    std::cout << "LIMDD Clifford-specialized    --  call counter statistics:\n";
    limddClifford->printCallCounterStatistics();
    std::cout << "nodes:      " << limddClifford->vUniqueTable.getNodeCount() << "\n";
    std::cout << "LIMDD locality-aware caching  --  call counter statistics:\n";
    limddLocality->printCallCounterStatistics();
    std::cout << "nodes:      " << limddLocality->vUniqueTable.getNodeCount() << "\n";

    std::ofstream statsfile;
    statsfile.open("DDstatsfile.csv", std::ios_base::app);
    //format: version name, time taken,nodecount
    statsfile << "limdd-locality-1.0," << (limdd_locality_end - limdd_locality_begin) << "\n";
    //statsfile << "qmdd," << (limdd_locality_begin - limdd_locality_end) << "\n";
    statsfile.close();
}

void simulateCircuitQMDDvsLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
    raceCircuitQMDDvsLIMDD(circuit);
    return;
    //        simulateCircuitLIMDDGateByGate(circuit);
    //        return;
    auto qmdd  = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
    auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false, dd::CachingStrategy::cliffordSpecialCaching);

    auto              qmddState  = qmdd->makeZeroState(circuit.n);
    auto              limddState = limdd->makeZeroState(circuit.n);
    dd::CVec          resultQMDD, resultLIMDD;
    std::stringstream dotfilenameStream;

    bool circuitIsCliffordSoFar = true; // Flag is set to false as soon as a non-Clifford gate is applied

    for (unsigned int gate = 0; gate < circuit.gates.size(); gate++) {
        //        dd::export2Dot(qmddState, "qmdd.dot", false, true, true, false, true, false);
        //        dd::export2Dot(limddState, "limdd.dot", false, true, true, false, true, false);

        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to QMDD.\n";
        qmddState = qmdd->applyGate(circuit.gates[gate], qmddState);
        std::cout << "[simulate circuit] Applying gate " << gate + 1 << " to LIMDD.\n";
        limddState = limdd->applyGate(circuit.gates[gate], limddState);

        resultQMDD  = qmdd->getVector(qmddState);
        resultLIMDD = limdd->getVector(limddState);

        //std::cout << "[simulate circuit] Intermediate states after " << gate + 1 << " gates.\n";
        //std::cout << "[simulate circuit] QMDD  result: " << dd::outputCVec(resultQMDD) << '\n';
        //std::cout << "[simulate circuit] LIMDD result: " << dd::outputCVec(resultLIMDD) << '\n';

        std::cout << "[simulate circuit] QMDD mul statistics: ";
        qmdd->matrixVectorMultiplication.printStatistics();
        std::cout << "[simulate circuit] LIMDD mul statistics: ";
        limdd->matrixVectorMultiplication.printStatistics();

        std::cout << "[simulate circuit] QMDD add statistics: ";
        qmdd->vectorAdd.printStatistics();
        std::cout << "[simulate circuit] LIMDD add statistics: ";
        limdd->vectorAdd.printStatistics();

        //        ASSERT_TRUE(limdd->mulCallCounter <= qmdd->mulCallCounter);
        //        EXPECT_TRUE(limdd->matrixVectorMultiplication.getHits() <= qmdd->matrixVectorMultiplication.getHits());

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
                std::cout << "[simulate circuit]   Failed after applying " << (gate + 1) << " gates.\n";
                //				dd::export2Dot(limddState, "limdd-less-than-n-stabilizers.dot", false, true, true, false, true, false);
                EXPECT_TRUE(false);
                break;
            }
        }
        if (circuitIsCliffordSoFar) {
            //ASSERT_TRUE(limdd->multiply2CallCounter == 0); // This check is disabled in order to test the locality-aware caching strategy
        }
        std::cout << "[simulate circuit] QMDD  mul statistics: ";
        qmdd->matrixVectorMultiplication.printStatistics();
        std::cout << "[simulate circuit] LIMDD mul statistics: ";
        limdd->matrixVectorMultiplication.printStatistics();

        std::cout << "[simulate circuit] QMDD  add statistics: ";
        qmdd->vectorAdd.printStatistics();
        std::cout << "[simulate circuit] LIMDD add statistics: ";
        limdd->vectorAdd.printStatistics();

        // assert that limdd hit rate is at least as good as qmdd hit rate
        //        EXPECT_TRUE(std::isnan(limdd->matrixVectorMultiplication.hitRatio()) || std::isnan(qmdd->matrixVectorMultiplication.hitRatio()) || limdd->matrixVectorMultiplication.hitRatio() >= qmdd->matrixVectorMultiplication.hitRatio());
    }

    //    qmdd->measureAll(qmddState, false, mt);

    dd::export2Dot(qmddState, "qmdd.dot", false, true, true, false, true, false);
    dd::export2Dot(limddState, "limdd.dot", false, true, true, false, true, false);

    std::mt19937_64 mt;
    auto            qmddResult  = qmdd->measureAll(qmddState, false, mt);
    auto            limddResult = qmdd->measureAll(limddState, false, mt);

    for (dd::Qubit i = 0; i < (dd::Qubit)qmdd->qubits(); i++) {
        std::cout << "Testing for " << int(i) << std::endl;
        auto qmddResult  = qmdd->determineMeasurementProbabilities(qmddState, i, true);
        auto limddResult = limdd->determineMeasurementProbabilities(limddState, i, true);

        EXPECT_NEAR(qmddResult.first, limddResult.first, 0.0000001);
        EXPECT_NEAR(qmddResult.second, limddResult.second, 0.0000001);
    }

    std::cout << "LIMDD call counter statistics:\n";
    limdd->printCallCounterStatistics();
    std::cout << "QMDD  call counter statistics:\n";
    qmdd->printCallCounterStatistics();

    std::cout << "[simulate circuit] Number of Unique lims: " << qmdd->limCount(qmddState) << std::endl;
    std::cout << "[simulate circuit] Number of Unique numbers: " << qmdd->numberCount(qmddState) << std::endl;

    std::cout << "[simulate circuit] Number of Unique lims: " << limdd->limCount(limddState) << std::endl;
    std::cout << "[simulate circuit] Number of Unique numbers: " << limdd->numberCount(limddState) << std::endl;

    std::cout << "[simulate circuit] qmdd  multiply calls: " << qmdd->mulCallCounter << std::endl;
    std::cout << "[simulate circuit] limdd multiply calls: " << limdd->mulCallCounter << std::endl;


    //    limdd->printVector(limddState);
    //    qmdd->printVector(qmddState);
}
#endif //DDPACKAGE_SIMULATION_HPP
