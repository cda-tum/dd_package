#!/bin/bash
id=1
for n in {10..31}
do
    gates=$((2*$n))
    ./generate $n $gates $id
    id=$(($id+1))
done
