import prependRandomCliffordCircuit
import os

directoryOut = '/DIRECTORY OUT/'
directory = '/DIRECTORY IN'

for filename in os.listdir(directory):
    f = os.path.join(directory, filename)
    if os.path.isfile(f):
        filenameBare = filename[0:len(filename)-5]
        filenameOut = directoryOut + filenameBare + "_randStab_01.qasm"
        print("NEW FILENAME : " + filenameOut)
        prependRandomCliffordCircuit.prependRandomStabilizerCircuit(str(f), filenameOut)
