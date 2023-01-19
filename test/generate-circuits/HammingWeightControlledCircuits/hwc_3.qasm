// This circuit is a randomly generated Hamming Weight-controlled circuit. The control and target registers have 3 qubits each

OPENQASM 2.0;
include "qelib1.inc";
qreg q[11];

// Step 1: put the first register in uniform superposition, by applying hadamard to all qubits
h q[10];
h q[9];
h q[8];
// Stage 1 of Hamming control gates
// Stage 1: compute part  (3 qubits)
x q[10];
x q[9];
ccx q[10], q[9], q[7];
x q[10];
x q[9];
x q[10];
ccx q[10], q[9], q[6];
x q[10];
x q[9];
ccx q[10], q[9], q[6];
x q[9];
ccx q[10], q[9], q[5];
// Stage 2 of Hamming control gates
// Stage 2: compute part  (3 qubits)
x q[8];
ccx q[8], q[7], q[3];
x q[8];
ccx q[8], q[7], q[2];
x q[8];
ccx q[8], q[6], q[2];
x q[8];
ccx q[8], q[6], q[1];
x q[8];
ccx q[8], q[5], q[1];
x q[8];
ccx q[8], q[5], q[0];
// Stage 2: uncompute part  (n=3 qubits)
x q[10];
x q[9];
ccx q[10], q[9], q[7];
x q[10];
x q[9];
x q[10];
ccx q[10], q[9], q[6];
x q[10];
x q[9];
ccx q[10], q[9], q[6];
x q[9];
ccx q[10], q[9], q[5];
// Stage 2: swap part  (3 qubits)
//swap q[7],q[3];
cx q[7],q[3];
cx q[3],q[7];
cx q[7],q[3];
//swap q[6],q[2];
cx q[6],q[2];
cx q[2],q[6];
cx q[6],q[2];
//swap q[5],q[1];
cx q[5],q[1];
cx q[1],q[5];
cx q[5],q[1];
//swap q[4],q[0];
cx q[4],q[0];
cx q[0],q[4];
cx q[4],q[0];
// The Hamming-weight register has now been set up.
// Next, we add 3 Hadamard gates and 33 random controlled Clifford gates
h q[3];
h q[2];
h q[1];
// Next we add the 33 random controlled Clifford gates
ccx q[6],q[3],q[1];
cz q[6],q[1];
ch q[4],q[1];
ccy q[4],q[3],q[1];
ccz q[6],q[3],q[2];
cy q[5],q[1];
ccz q[4],q[1],q[3];
cz q[4],q[1];
ccy q[7],q[2],q[1];
cy q[4],q[1];
ch q[4],q[2];
ch q[6],q[2];
ccx q[6],q[3],q[1];
ccz q[5],q[3],q[2];
cz q[7],q[2];
ccy q[5],q[2],q[3];
ccx q[6],q[1],q[2];
cz q[7],q[2];
ccx q[5],q[2],q[1];
ccz q[6],q[3],q[2];
cx q[4],q[1];
ch q[5],q[3];
cx q[7],q[1];
cs q[7],q[2];
ccz q[4],q[1],q[2];
cs q[5],q[1];
cz q[6],q[3];
cx q[6],q[3];
cs q[4],q[3];
cx q[5],q[2];
ccy q[7],q[3],q[1];
ccx q[5],q[2],q[1];
ccy q[7],q[2],q[1];
