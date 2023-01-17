#include <iostream>
#include <fstream>
#include <string.h>
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

string getQasmGateName(unsigned int gate) {
    switch(gate) {
        case 0: return "x";
        case 1: return "y";
        case 2: return "z";
        case 3: return "s";
        case 4: return "h";
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
	unsigned int nQubits, nGates, testId, gate, control, control2, control1polarity, control2polarity, target, nGatesMade, qasm;
    bool cliffordOnly;
	if (nargs < 4) {
		cout << "usage: " << args[0] << " nQubits nGates testId [0/1 clifford-only] [qasm] [output file] [quantum register name]\n"
		     << "This generates a Quantum circuits consisting of 'nQubits' qubits and 'nGates' Clifford gates, or general gates if clifford-only=0.\n"
             << "If 'qasm' is specified, then the output is given in .qasm format.\n";
		return -1;
	}
	srand(millisecondsSinceEpoch());
    nQubits = atoi(args[1]);
    nGates  = atoi(args[2]);
    testId  = atoi(args[3]);
    cliffordOnly = (nargs >= 5 && atoi(args[4]) == 1);
    qasm = (nargs >= 6 && strcmp(args[5], "qasm") == 0);
    const char* defaultQuantumRegisterName = "q";
    ofstream out;
    bool writeToFile = false;
    if (nargs >= 7) {
        out.open(args[6], ios::app);
        writeToFile = true;
    }
    string quantumRegisterName = "q";
    if (nargs >= 8) {
        quantumRegisterName = args[7];
    }
    //cout << "[Generate random Clifford circuit] #Qubits = " << nQubits << " #Gates = " << nGates << " file? " << writeToFile << " filename = " << (writeToFile ? args[6] : "-") << " qr name = " << quantumRegisterName << "\n";
    if (!qasm) {
        cout << "// Randomly generated circuit on " << nQubits << " qubis, containing " << nGates << " gates.\n"
             << "TEST(LimTest, generatedCircuit_" << testId << ") {\n"
             << "    dd::QuantumCircuit circuit(" << nQubits << ");\n\n";
    }
    // Step 1: apply a Hadamard gate to each qubit, with 50% probability
    nGatesMade = 0;
    for (unsigned int i=0; i<nQubits && nGatesMade < nGates; i++) {
        if (rand() % 2) {
            // apply a Hadamard to qubit i
            if (qasm) {
                if (writeToFile) {
                    out << "h " << quantumRegisterName << "[" << i << "];\n";
                } else {
                    cout << "h q[" << i << "];\n";
                }
            } else {
                if (writeToFile) {
                    out << "    circuit.addGate(dd::Hmat, " << i << ");\n";
                } else {
                    cout << "    circuit.addGate(dd::Hmat, " << i << ");\n";
                }
            }
            nGatesMade++;
        }
    }
    //cout << "Wrote Hadamards; now " << nGatesMade << " / " << nGates << " gates are made. Applying other gates...\n";
    for (unsigned int gateId=nGatesMade; gateId<nGates; gateId++) {
        //cout << "//Applying gate " << gateId << "\n";
        if (cliffordOnly) {
            if (rand() % 2 == 0 || nQubits <= 1) {
                // do a non-controlled gate
                gate = rand() % 5;
                target = rand() % nQubits;
                if (qasm) {
                    if (writeToFile) {
                        out << getQasmGateName(gate) << " " << quantumRegisterName << "[" << target << "];\n";
                    } else {
                        cout << getQasmGateName(gate) << " q[" << target << "];\n";
                    }
                } else {
                    if (writeToFile) {
                        out << "    circuit.addGate(dd::" << getGateName(gate) << ", " << target << ");\n";
                    } else {
                        cout << "    circuit.addGate(dd::" << getGateName(gate) << ", " << target << ");\n";
                    }
                }
            }
            else {
                // do a controlled gate
                gate = rand() % 3;
                control = rand() % nQubits;
                do {
                    target = rand() % nQubits;
                } while (target == control);
                control1polarity = rand() % 2;
                if (qasm) {
                    if (writeToFile) {
                        out << "c" << getQasmGateName(gate) << " " << quantumRegisterName << "[" << control << "], q[" << target << "];\n";
                    } else {
                        cout << "c" << getQasmGateName(gate) << " " << quantumRegisterName << "[" << control << "], q[" << target << "];\n";
                    }
                } else {
                    if (writeToFile) {
                        out << "    circuit.addGate(dd::" << getGateName(gate) << ", " << control << "_" << (control1polarity ?  'p' : 'n') << "c, " << target << ");\n";
                    } else {
                        cout << "    circuit.addGate(dd::" << getGateName(gate) << ", " << control << "_" << (control1polarity ?  'p' : 'n') << "c, " << target << ");\n";
                    }
                }
            }
        } else {
            gate = rand() % gateSetSize;
            target = rand() % nQubits;
            if (rand() % 2 == 0 || nQubits <= 1) {
                // add a non-controlled gate
                cout << "    circuit.addGate(dd::" << getGateName(gate) << ", " << target << ");\n";
            } else if (rand() % 2 == 0 || nQubits <= 2) {
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
    //cout << "Done. Wrote a random Clifford circuit to file " << args[6] << ".\n";
    if (!qasm) {
        cout << "\n    simulateCircuitQMDDvsLIMDDGateByGate(circuit);\n"
             << "}\n\n";
    }
    out.close();
}
