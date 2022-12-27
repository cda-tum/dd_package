#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <ctime>
#include <chrono>

unsigned int gateSetSize = 7;

string getGateName(unsigned int gate) {
	switch(gate) {
		case 0: return "Xmat";
		case 1: return "Ymat";
		case 2: return "Zmat";
		case 3: return "Smat";
		case 4: return "Hmat";
        case 5: return "Tmat";
        case 6: return "Tdagmat";
		default: return "??";
	}
}

long millisecondsSinceEpoch() {
	auto t = std::chrono::system_clock::now();
	auto since_epoch = t.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
	return millis.count();
}

int main(int nargs, char** args) {
//	cout << "Hello, generation!\n";
	unsigned int nQubits, nGates, testId, gate, control, control2, control1polarity, control2polarity, target, nGatesMade;
    bool cliffordOnly;
	if (nargs < 4) {
		cout << "usage: " << args[0] << " nQubits nGates testId [0/1 clifford-only]\n"
		     << "This generates a Quantum circuits consisting of 'nQubits' qubits and 'nGates' Clifford gates, or general gates if clifford-only=0.\n";
		return -1;
	}
	srand(millisecondsSinceEpoch());
    nQubits = atoi(args[1]);
    nGates  = atoi(args[2]);
    testId  = atoi(args[3]);
    cliffordOnly = (nargs >= 5 && atoi(args[4]) == 1);
    cout << "// Randomly generated circuit on " << nQubits << " qubis, containing " << nGates << " gates.\n"
		 << "TEST(LimTest, generatedCircuit_" << testId << ") {\n"
		 << "    dd::QuantumCircuit circuit(" << nQubits << ");\n\n";
    // Step 1: apply a Hadamard gate to each qubit, with 50% probability
    for (unsigned int i=0; i<nQubits && nGatesMade < nGates; i++) {
        if (rand() % 2) {
            // apply a Hadamard to qubit i
            cout << "    circuit.addGate(dd::Hmat, " << i << ");\n";
            nGatesMade++;
        }
    }
    for (unsigned int gateId=nGatesMade; gateId<nGates; gateId++) {
        if (cliffordOnly) {
            if (rand() % 2 == 0) {
                // do a non-controlled gate
                gate = rand() % 5;
                target = rand() % nQubits;
                cout << "    circuit.addGate(dd::" << getGateName(gate) << ", " << target << ");\n";
            }
            else {
                // do a controlled gate
                gate = rand() % 3;
                control = rand() % nQubits;
                do {
                    target = rand() % nQubits;
                } while (target == control);
                cout << "    circuit.addGate(dd::" << getGateName(gate) << ", " << control << "_pc, " << target << ");\n";
            }
        } else {
            gate = rand() % gateSetSize;
            target = rand() % nQubits;
            if (rand() % 2 == 0) {
                // add a non-controlled gate
                cout << "    circuit.addGate(dd::" << getGateName(gate) << ", " << target << ");\n";
            } else if (rand() % 2 == 0) {
                // add a controlled gate
                do {
                    control = rand() % nQubits;
                } while (control == target);
                control1polarity = rand() % 2;
                cout << "    circuit.addGate(dd::" << getGateName(gate) << ", " << control << "_" << (control1polarity ?  'p' : 'n') << "c, " << target << ");\n";
            } else {
                // add a controlled-controlled gate
                do {
                    control = rand() % nQubits;
                } while (control == target);
                do {
                    control2 = rand() % nQubits;
                } while (control2 == target || control2 == control);
                control1polarity = rand() % 2;
                control2polarity = rand() % 2;
                cout << "    circuit.addGate(dd::" << getGateName(gate) << ", "
                     << control << "_" << (control1polarity ?  'p' : 'n') << "c, "
                     << control2 << "_" << (control2polarity ? 'p' : 'n') << "c, " << target << ");\n";
            }
        }
	}
	cout << "\n    simulateCircuitQMDDvsLIMDDGateByGate(circuit);\n"
 	 	 << "}\n\n";
}
