#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <ctime>
#include <chrono>

string getGateName(unsigned int gate) {
	switch(gate) {
		case 0: return "Xmat";
		case 1: return "Ymat";
		case 2: return "Zmat";
		case 3: return "Smat";
		case 4: return "Hmat";
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
	unsigned int nQubits, nGates, testId, gate, control, target;
	if (nargs < 4) {
		cout << "usage: " << args[0] << " nQubits nGates testId\n"
		     << "This generates a Quantum circuits consisting of 'nQubits' qubits and 'nGates' Clifford gates.\n";
		return -1;
	}
	srand(millisecondsSinceEpoch());
	nQubits = atoi(args[1]);
	nGates  = atoi(args[2]);
	testId  = atoi(args[3]);
	cout << "// Randomly generated circuit on " << nQubits << " qubis, containing " << nGates << " Clifford gates.\n"
		 << "TEST(LimTest, generatedCircuit_" << testId << ") {\n"
		 << "    dd::QuantumCircuit circuit(" << nQubits << ");\n\n";
	for (unsigned int gateId=0; gateId<nGates; gateId++) {
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
	}
	cout << "\n    simulateCircuitQMDDvsLIMDDGateByGate(circuit);\n"
 	 	 << "}\n\n";
}



//TEST(LimTest, simpleCircuit107) {
//	dd::QuantumCircuit c(5);
//	c.addGate(dd::Hmat, 0);
//	c.addGate(dd::Hmat, 1);
//	c.addGate(dd::Hmat, 2);
//	c.addGate(dd::Hmat, 3);
//	c.addGate(dd::Hmat, 4);
//	c.addGate(dd::Zmat, 0_pc, 2);
//	c.addGate(dd::Zmat, 1_pc, 2);
//	c.addGate(dd::Zmat, 3_pc, 2);
//	c.addGate(dd::Zmat, 4_pc, 2);
//
//	simulateCircuitQMDDvsLIMDDGateByGate(c);
//}
