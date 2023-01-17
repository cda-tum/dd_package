import re
import subprocess
import sys
import random

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

def writeRandomCliffordCircuit(file_out, nQubits, nGates, quantumRegister):
    # Start in an equal superposition
    nGatesMade = 0
    for i in range(nQubits):
        file_out.write("h " + quantumRegister + "[" + str(i) + "];\n")
        nGatesMade += 1
    for g in range(nGatesMade, nGates):
        target = random.randint(0,nQubits-1)
        if random.randint(0,2) == 0 or nQubits <= 1:
            # Make a single-qubit gate
            gate = random.randint(0,4)
            file_out.write(getGateName(gate) + " " + quantumRegister + "[" + str(target) + "];\n")
        else:
            # Make a two-qubit gate
            gate    = random.randint(0,2)
            control = random.randint(0,nQubits-1)
            while target == control:
                control = random.randint(0,nQubits-1)
            file_out.write("c" + getGateName(gate) + " " + quantumRegister + "[" + str(control) + "], " + quantumRegister + "[" + str(target) + "];\n")

def prependRandomStabilizerCircuit(filename_in, filename_out):
    f = open(filename_in, "r")
    try:
        out = open(filename_out, "w")
    except IOError:
        print("Could not open file for writing.")
        exit()

    beginning = re.compile("OPENQASM|include|qreg|creg")
    qreg = re.compile("qreg .*\[")
    qregName = "None"
    num = re.compile("\d+")
    nQubits = 0
    for line in f:
        r = beginning.search(line)
        if r is None:
            lastLine = line
            break
        else:
            # print("Beginning of file : " + line, end="")
            qregs = qreg.findall(line)
            # print(qregs)
            if len(qregs) != 0:
                # print("qregs : "+ str(qregs))
                nums = num.findall(line)
                if int(nums[len(nums)-1]) > nQubits:
                    qregName = (qregs[0])[5:len(qregs[0])-1]
                    nQubits = int(nums[len(nums)-1])
                    print("Number of qubits: " + str(nQubits))
                    print("Name of quantum register: " + str(qregName))
            out.write(line)

    out.write("\n// Start of random Clifford circuit\n")

    # out.close()
    # print("WRITING WITH NQUBITS = " + str(nQubits))
    nGates = 10 * int(nQubits)
    # subprocess.run(["./generateCliffordCircuit", str(nQubits), str(nGates), "0", "1", "qasm", filename_out, qregName])

    writeRandomCliffordCircuit(out, nQubits, nGates, qregName)

    # out = open(filename_out, "a")
    out.write("// End of random CliffordCircuit\n\n")
    # print("Done with calling generateCliffordCircuit")
    out.write(lastLine)
    for line in f:
        out.write(line)
    f.close()
    out.close()