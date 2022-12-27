#!/bin/bash
id=3
for n in {3..100}
do
    gates=$((10*$n))
    ./generateCliffordCircuit $n $gates $id
    id=$(($id+1))
done
