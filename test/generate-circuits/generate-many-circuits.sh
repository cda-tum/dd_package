#!/bin/bash

echo "\
#include \"dd/Definitions.hpp\"
#include \"dd/Export.hpp\"
#include \"dd/GateMatrixDefinitions.hpp\"
#include \"dd/LimTable.hpp\"
#include \"dd/Package.hpp\"
#include \"dd/QuantumCircuitSimulation.hpp\"
#include \"dd/QuantumGate.hpp\"
#include \"gmock/gmock.h\"
#include \"gtest/gtest.h\"
#include <iomanip>
#include <memory>
#include <random>
#include <sstream>

using namespace dd::literals;

"

id=301
for n in {1..300}
do
    gates=7
    ./generateCliffordCircuit 3 $gates $id 0
    id=$(($id+1))
done
