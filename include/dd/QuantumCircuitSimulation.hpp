//
// Created by lieuwe on 11-8-22.
//

#ifndef DDPACKAGE_SIMULATION_HPP
#define DDPACKAGE_SIMULATION_HPP

#include "Package.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

void simulateCircuitQMDDvsLIMDDGateByGate(const dd::QuantumCircuit& circuit);

inline void simulateCircuitLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
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

#if ENABLE_PROFILING
inline void raceCircuitQMDDvsLIMDD(const dd::QuantumCircuit& circuit) {
    //simulateCircuitQMDDvsLIMDDGateByGate(circuit);
    //return;
    auto qmdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
    auto limddOld = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false,
                                                    dd::CachingStrategy::QMDDCachingStrategy);
    auto limddClifford = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false,(dd::CachingStrategy)(
        dd::CachingStrategy::cliffordSpecialCaching |
        dd::CachingStrategy::lazyMemoizationGroupIntersect | dd::CachingStrategy::smartStabilizerGeneration | dd::CachingStrategy::localityAwareCachingDirtyTrick |
        dd::CachingStrategy::localityAwarePropagateReducedLim));
    auto limddLocality = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false,
                                                 dd::CachingStrategy::localityAwareCachingDirtyTrick);

    dd::vEdge resultEdge[4];
    clock_t begin[4], end[4];

    // reset times
    dd::Profile::groupIntersectTime           = 0;
    dd::Profile::cosetIntersectModPTime       = 0;
    dd::Profile::cosetIntersectPauliTime      = 0;
    dd::Profile::constructStabilizerTime      = 0;
    dd::Profile::recoverPhaseTime             = 0;
    dd::Profile::gramSchmidtTime              = 0;
    dd::Profile::gaussianEliminationTime      = 0;
    dd::Profile::normalizeLIMDDTime           = 0;
    dd::Profile::makeDDNodeTime               = 0;
    dd::Profile::addTime                      = 0;
    dd::Profile::multiply2Time                = 0;
    // reset call counts
    dd::Profile::groupIntersectCallCount      = 0;
    dd::Profile::recoverPhaseCallCount        = 0;
    dd::Profile::gaussianEliminationCallCount = 0;
    dd::Profile::cosetIntersectModPCallCount  = 0;
    dd::Profile::cosetIntersectPauliCallCount = 0;
    dd::Profile::constructStabilizerCallCount = 0;
    dd::Profile::recoverPhaseCallCount        = 0;
    dd::Profile::gramSchmidtCallCount         = 0;
    dd::Profile::gaussianEliminationCallCount = 0;
    dd::Profile::normalizeLIMDDCallCount      = 0;
    dd::Profile::makeDDNodeCallCount          = 0;
    dd::Profile::addCallCount                 = 0;
    dd::Profile::multiply2CallCount           = 0;

    dd::Profile::intersectionMemoizationHits  = 0;

    std::cout << "[race circuit] Simulating old LIMDD\n";
    // simulate old LIMDD
    begin[0] = clock();
    //resultEdge[0] = limddOld->simulateCircuit(circuit);
    end[0] = clock();

    // simulate clifford LIMDD
    std::cout << "[race circuit] Simulating LIMDD with Clifford-specialized caching\n";
    begin[1] = clock();
    resultEdge[1] = limddClifford->simulateCircuit(circuit);
    end[1] = clock();

    // simulate locality-aware LIMDD
    std::cout << "[race circuit] Simulating LIMDD with locality-aware caching, but without Clifford-specialized caching\n";
    begin[2] = clock();
    //resultEdge[2] = limddLocality->simulateCircuit(circuit);
    end[2] = clock();

    // simulate QMDD
    std::cout << "[race circuit] Simulating QMDD.\n";
    begin[3] = clock();
    //resultEdge[3] = qmdd->simulateCircuit(circuit);
    end[3] = clock();

    if (limddOld->getVectorCallCount != 0) {
        std::cout << "    ERROR getVector was called. Double-check: did you compile in debug mode?\n";
    }

    std::ofstream statsfile;
    statsfile.open("DDstatsfile.csv", std::ios_base::app);
    statsfile << (int) circuit.n << ",";
    //format: nqubits, version name, time taken, multiply calls, add calls, nodecount, gates, time group intersect, time coset mod phase intersect, time coset pauli intersect, time construct stabs, time recover phase, time gram schmidt, gaussian elimination time..
    // .. normalize time, group intersect calls, coset intersect calls, construct stabs calls, recover phase calls, gram schmidt calls, normalizeLIMDD() calls, makeDDNode calls, intersection memoziation hits, gaussian elim calls,
    // multiply cache lookups, multiply cache hits, multiply cache hit ratio, add cache lookups, add cache hits, add cache ratio
    //statsfile << "limddOld," <<           (end[0] - begin[0]) << "," << limddOld->     multiply2CallCounter << "," << limddOld->     addCallCounter << "," << limddOld->     countNodes(resultEdge[0]) << "," << circuit.gates.size() << ",";
    statsfile << "limddClifford-v1.3-hard-circuits," << (end[1] - begin[1]) << "," << limddClifford->multiply2CallCount << "," << limddClifford->addCallCount << "," << limddClifford->countNodes(resultEdge[1]) << "," << circuit.gates.size() << ",";
    //statsfile << "limddLocality-v1-0-clifford-circuits," << (end[2] - begin[2]) << "," << limddLocality->multiply2CallCounter << "," << limddLocality->addCallCounter << "," << limddLocality->countNodes(resultEdge[2]) << "," << circuit.gates.size() << ",";
    //statsfile << "qmdd," <<               (end[3] - begin[3]) << "," << qmdd->         multiply2CallCounter << "," << qmdd->         addCallCounter << "," << qmdd->         countNodes(resultEdge[3]) << "," << circuit.gates.size() << ",";
    statsfile << dd::Profile::groupIntersectTime << "," << dd::Profile::cosetIntersectModPTime << "," << dd::Profile::cosetIntersectPauliTime << "," << dd::Profile::constructStabilizerTime << "," << dd::Profile::recoverPhaseTime << "," << dd::Profile::gramSchmidtTime << "," << dd::Profile::gaussianEliminationTime << "," << limddClifford->normalizeLIMDDTime << ","
              << dd::Profile::groupIntersectCallCount << "," << dd::Profile::cosetIntersectPauliCallCount + dd::Profile::cosetIntersectModPCallCount << "," << dd::Profile::constructStabilizerCallCount << "," << dd::Profile::recoverPhaseCallCount << "," << dd::Profile::gramSchmidtCallCount << "," << dd::Profile::normalizeLIMDDCallCount << "," << dd::Profile::makeDDNodeCallCount << "," << dd::Profile::intersectionMemoizationHits << "," << dd::Profile::gaussianEliminationCallCount << ","
              << limddClifford->matrixVectorMultiplication.getHits() << "," << limddClifford->matrixVectorMultiplication.getLookups() << "," << limddClifford->matrixVectorMultiplication.hitRatio() << ","
              << limddClifford->vectorAdd.getHits() << "," << limddClifford->vectorAdd.getLookups() << "," << limddClifford->vectorAdd.hitRatio() << "\n";
    statsfile.close();
}
#endif

inline void simulateCircuitQMDDvsLIMDDGateByGate(const dd::QuantumCircuit& circuit) {
    //raceCircuitQMDDvsLIMDD(circuit);
    //return;
    auto qmdd  = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::QMDD_group);
    auto limdd = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, true, (dd::CachingStrategy)(
        dd::CachingStrategy::cliffordSpecialCaching |
        dd::CachingStrategy::lazyMemoizationGroupIntersect |
        dd::CachingStrategy::smartStabilizerGeneration |
        dd::CachingStrategy::localityAwareCachingDirtyTrick |
        dd::CachingStrategy::skipIdentityGateMultiplication
    ));
    //auto limdd2 = std::make_unique<dd::Package<>>(circuit.n, dd::LIMDD_group::Pauli_group, false, (dd::CachingStrategy)(dd::CachingStrategy::cliffordSpecialCaching | dd::CachingStrategy::lazyMemoizationGroupIntersect));

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

        std::cout << "[simulate circuit] Intermediate states after " << gate + 1 << " gates.\n";
        std::cout << "[simulate circuit] QMDD  result: " << dd::outputCVec(resultQMDD) << '\n';
        std::cout << "[simulate circuit] LIMDD result: " << dd::outputCVec(resultLIMDD) << '\n';

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
            std::cout << "[simulate circuit] These intermediate vectors differ; aborting simulation. Gates applied: " << gate + 1 << "\n";
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
            // This check verifies that all Clifford gates were correctly recognized as such by the LIMDD implementation, and were handled as special cases
            //ASSERT_TRUE(limdd->multiply2CallCount == 0); // this check doesn't work anymore since we no longer track the multiply2 call count of individual Packages // This check is disabled in order to test the locality-aware caching strategy
        }

        // assert that limdd hit rate is at least as good as qmdd hit rate
        //        EXPECT_TRUE(std::isnan(limdd->matrixVectorMultiplication.hitRatio()) || std::isnan(qmdd->matrixVectorMultiplication.hitRatio()) || limdd->matrixVectorMultiplication.hitRatio() >= qmdd->matrixVectorMultiplication.hitRatio());
    }

    //qmdd->measureAll(qmddState, false, mt);

    //dd::export2Dot(qmddState, "qmdd.dot", false, true, true, false, true, false);
    //dd::export2Dot(limddState, "limdd.dot", false, true, true, false, true, false);

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

    std::cout << "[simulate circuit] qmdd  multiply calls: " << qmdd->multiply2CallCount << std::endl;
    std::cout << "[simulate circuit] limdd multiply calls: " << limdd->multiply2CallCount << std::endl;


    //    limdd->printVector(limddState);
    //    qmdd->printVector(qmddState);
}
#endif //DDPACKAGE_SIMULATION_HPP
