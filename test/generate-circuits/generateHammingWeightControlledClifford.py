import sys
import random

# TODO swap the qubit indices, so that the largest registers are the control qubits, and the lower-index qubits are the targets
# TODO add option to generate graph state rather than Clifford circuit
# TODO allow multiple HWC circuits to be written in a directory
#   to this end, name the files hwc_n_j.qasm, e.g., hwc_11_5.qasm for the 5-th HWC circuit on 11 qubits
#   simply check whether hwc_n_j.qasm already exists, and if so, j++ and try again

def totalNumberQubits(n):
    return 3*n+2

def getIndex(n, id):
    return str(totalNumberQubits(n) - 1 - id)

def getAncillaRegisterIndex(n, id):
    return getIndex(n, n+id)

def getTargetRegisterIndex(n, id):
    return getIndex(n, n+n+1+id)

def writePrologue(file_out, n):
    file_out.write("// This circuit is a randomly generated Hamming Weight-controlled circuit. The control and target registers have " + str(n) + " qubits each\n\n")
    file_out.write("OPENQASM 2.0;\n")
    file_out.write("include \"qelib1.inc\";\n")
    file_out.write("qreg q[" + str(totalNumberQubits(n)) + "];\n\n")
    file_out.write("// Step 1: put the first register in uniform superposition, by applying hadamard to all qubits\n")
    for k in range(0, n):
        file_out.write("h q["+getIndex(n, k)+"];\n")

def writeHammingControlComputePart(file_out, n, k):
    file_out.write("// Stage "+str(k)+": compute part  ("+str(n)+" qubits)\n")
    for w in range(0, k+1):
        file_out.write("x q["  +getIndex(n, k)+"];\n")
        file_out.write("ccx q["+getIndex(n, k)+"], q["+getAncillaRegisterIndex(n, w)+"], q["+getTargetRegisterIndex(n, w)+"];\n")
        file_out.write("x q["  +getIndex(n, k)+"];\n")
        file_out.write("ccx q["+getIndex(n, k)+"], q["+getAncillaRegisterIndex(n, w)+"], q["+getTargetRegisterIndex(n, w+1)+"];\n")
        # for j in range(0, 2):
        #     file_out.write("ccx q[k]=j q[n+w], q[n+n+1+w+j]\n")

def writeHammingControlUncomputePart(file_out, n, k):
    file_out.write("// Stage "+str(k)+": uncompute part  ("+str(n)+" qubits)\n")
    file_out.write("Cx q["+getTargetRegisterIndex(n, 0)+"], q["+getAncillaRegisterIndex(n, 0)+"];\n")
    for w in range(1, k+1):
        file_out.write("x q["  +getIndex(n, k)+"];\n")
        file_out.write("ccx q["+getIndex(n, k)+"], q["+getTargetRegisterIndex(n, w)+"], q["  +getAncillaRegisterIndex(n, w)+"];\n")
        file_out.write("x q["  +getIndex(n, k)+"];\n")
        file_out.write("ccx q["+getIndex(n, k)+"], q["+getTargetRegisterIndex(n, w)+"], q["  +getAncillaRegisterIndex(n, w+1)+"];\n")
    file_out.write("ccx q["    +getIndex(n, k)+"], q["+getTargetRegisterIndex(n, w+1)+"], q["+getAncillaRegisterIndex(n, w)+"];\n")

def writeHammingControlSwapPart(file_out, n, k):
    file_out.write("// Stage "+str(k)+": swap part  ("+str(n)+" qubits)\n")
    for w in range(0, k+2):
        file_out.write("//swap q["+getAncillaRegisterIndex(n, w)+"],q["+getTargetRegisterIndex(n, w)+"];\n")
        file_out.write("cx q["+getAncillaRegisterIndex(n, w)+"],q["+getTargetRegisterIndex(n, w)+"];\n")
        file_out.write("cx q["+getTargetRegisterIndex(n, w)+"],q["+getAncillaRegisterIndex(n, w)+"];\n")
        file_out.write("cx q["+getAncillaRegisterIndex(n, w)+"],q["+getTargetRegisterIndex(n, w)+"];\n")

def writeComputePartStage1(file_out, n):
    # stage 1 is special, so we just hard-code the gates
    # not 0, not 1, then 0
    # TODO propagate ids
    file_out.write("x q["+getIndex(n, 0)+"];\n")
    file_out.write("x q["+getIndex(n, 1)+"];\n")
    file_out.write("ccx q["+getIndex(n, 0)+"], q["+getIndex(n, 1)+"], q["+getAncillaRegisterIndex(n, 0)+ "];\n")
    file_out.write("x q["+getIndex(n, 0)+"];\n")
    file_out.write("x q["+getIndex(n, 1)+"];\n")
    # not 0, 1, then 1
    file_out.write("x q["+getIndex(n, 0)+"];\n")
    file_out.write("ccx q["+getIndex(n, 0)+"], q["+getIndex(n, 1)+"], q[" +getAncillaRegisterIndex(n, 1)+"];\n")
    file_out.write("x q["+getIndex(n, 0)+"];\n")
    # 0, not 1, then 1
    file_out.write("x q["+getIndex(n, 1)+"];\n")
    file_out.write("ccx q["+getIndex(n, 0)+"], q["+getIndex(n, 1)+"], q[" +getAncillaRegisterIndex(n, 1)+"];\n")
    file_out.write("x q["+getIndex(n, 1)+"];\n")
    # 0 and 1 then 2
    file_out.write("ccx q["+getIndex(n, 0)+"], q["+getIndex(n, 1)+"], q[" +getAncillaRegisterIndex(n, 2)+"];\n")


def writeHammingControlStage(file_out, n, k):
    # assume regsiter {q[n]...q[n+1]} contains the indicator bits of weight k;
    # and then overwrite this register so that it contains the indicator bits of weigth k
    file_out.write("// Stage " + str(k) + " of Hamming control gates\n")
    if k == 1:
        # stage 1 only has a compute part; it does not have an compute part, nor a swap part
        file_out.write("// Stage "+str(k)+": compute part  ("+str(n)+" qubits)\n")
        writeComputePartStage1(file_out, n)
    elif k == 2:
        # 6 gates for compute stage
        writeHammingControlComputePart(file_out, n, k)
        # 4 gates for uncompute stage
        # The uncompute part of stage 2 is the same as the compute part of stage 1
        file_out.write("// Stage "+str(k)+": uncompute part  (n="+str(n)+" qubits)\n")
        writeComputePartStage1(file_out, n)
        # 4 swap gates
        writeHammingControlSwapPart(file_out, n, k)
    else:
        # compute part
        writeHammingControlComputePart(file_out, n, k)
        # uncompute part
        writeHammingControlUncomputePart(file_out, n, k)
        # swap part
        writeHammingControlSwapPart(file_out, n, k)

def writeHammingControls(file_out, n):
    for k in range(1, n):
        writeHammingControlStage(file_out, n, k)

def getGateName(gateId):
    if gateId == 0:
        return "x"
    elif gateId == 1:
        return "y"
    elif gateId == 2:
        return "z"
    elif gateId == 3:
        return "s"
    elif gateId == 4:
        return "h"
    return "??"

# TODO propagate ids
def writeRandomCliffordCircuit(file_out, n, nGates):
    file_out.write("// The Hamming-weight register has now been set up.\n// Next, we add "+str(n)+" Hadamard gates and "+str(nGates-n) + " random controlled Clifford gates\n")
    # Apply Hadamards to the target register
    for k in range(0, n):
        file_out.write("h q["+getTargetRegisterIndex(n, k)+"];\n")
    file_out.write("// Next we add the "+str(nGates - n)+" random controlled Clifford gates\n")
    for g in range(0, nGates-n):
        w = random.randint(0, n) # choose a Hamming weight which controls the gate
        target = random.randint(0, n-1) # choose a target qubit in the target register
        # randomly choose whether to apply either a single-qubit Clifford gate or a controlled Pauli gate
        if random.randint(0,1) == 0:
            gate = random.randint(0,4)
            # write a single-qubit Clifford gate, controlled by a weight
            file_out.write("c" + getGateName(gate) + " q[" + getAncillaRegisterIndex(n, w) + "],q[" + getTargetRegisterIndex(n, target) + "];\n")
        else:
            # write a double-controlled Pauli gate, controlled by a weight and by a qubit in the target register
            gate = random.randint(0,2)
            control = random.randint(0, n-1)
            while target == control:
                control = random.randint(0, n-1)
            file_out.write("cc"+ getGateName(gate) + " q[" + getAncillaRegisterIndex(n, w) + "],q[" + getTargetRegisterIndex(n, control)+"],q[" + getTargetRegisterIndex(n, target) +"];\n")

def getRandomHammingWeightControlledCliffordCircuit(n, nGates):
    file_out = open("HammingWeightControlledCircuits/hwc_"+ str(n) + ".qasm", "w")
    writePrologue(file_out, n)
    writeHammingControls(file_out, n)
    writeRandomCliffordCircuit(file_out, n, nGates)
    file_out.close()

if (len(sys.argv) < 2):
    print("Usage: "+ sys.argv[0] + " nQubits [nGates], where nQubits is the number of qubits, nGates is the number of controlled Clifford gates.\nBy default nGates = 4* nQubits ^ 2")
else:
    nQubits = int(sys.argv[1])
    nGates = 4 * nQubits * nQubits
    if (len(sys.argv) >= 3):
        nGates = int(sys.argv[2])
    getRandomHammingWeightControlledCliffordCircuit(nQubits, nGates)