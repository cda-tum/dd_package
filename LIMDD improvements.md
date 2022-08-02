# Improvements to the LIMDD implementation

This document lists some of the many opportunities to improve the LIMDD implementation.
Chiefly we want two things: no more memory leaks; faster performance.
Incidentally, the way to fix the memory leaks will likely also make the code faster,
because dynamically allocating memory is slower than doing computations with objects on the stack.

## Better Runtimes

- In `makeDDNode`, only call `constructStabilizerGeneratorSet` when a node is newly created, and *not* when a new is succesfully looked up from the UniqueTable.
  - To this end, refactor the `nodeTable.lookup()` function so it takes an extra bool parameter by reference, which it sets to `true` iff the node that is returned was newly created, and to false when the node existed in the Table.
- Hard-code certain gates, to allow linear-time processing, using the algorithms presented in the new arxiv version of the LIMDD paper
  - Implement `getMatrixDescription(mNode)` which, given a Matrix LIMDD, figures out which gates is being implemented
  - **Pauli gates** When applying a Pauli gate, simply apply the Pauli gate to the root label
  - **Downward CNOT** propagate "through" edge labels by using Clifford algebra equivalences. When encountering the control qubit, apply an $X$ gate to the node's high edge, and backtrack
  - **Upward CNOT** propagate "through" edge labels by using Clifford algebra equivalences. When target qubit is reached, perform a hard-coded scheme of projection and additions.
  - **Hadamard** propagate "through" edge labels by using $HXH=Z$ etc. When target qubit is reached, perform hard-coded scheme of additions.
  - **S (phase gate)** Propagate through edge labels by using $SZ=ZS$ and $SX=-XS^{-1}$. When target qubit is reached, multiply high weight by $i$.
  - **T-gate** Propagate through edge labels by using $ZT=TZ$ and $TX=-iXT^{-1}$. When target qubit is reached, multiply high weight by $e^{ipi/4}$. (this is not on arxiv)
  - **General phase gates** of the form $A=[1 & 0; 0 & z]$. Similar to T-gates. Applying such a gate increases the number of nodes by at most 2.
    Floating point inaccuracies can be mostly prevented by cleverly propagating these through the edge labels. (this is not on arxiv)
  - **Toffoli gates** can be implemented more efficiently using a similar scheme.
    In case the control qubits have higher indices than the target qubit, then this can be implemented with no floating point inaccuracies. (this is not on arxiv)
  (X,Y,Z,H,S,S^{-1} CNOT, CZ, CY, T^k, Toffoli, multi-controlled Pauli)
  - Gates {Pauli, downward Controlled-Pauli, S}, (i) do not increase change the structure of the DD (in particular, does not change the number of nodes), and (ii) do not change the set of complex numbers in the table.
    In fact, no edge weights need to be touched except to be multiplied by {+1,-1,i,-i}.
    Therefore, no floating point inaccuracies are necessary. If floating point inaccuracies occur, then we know we've implemented something wrong
      - for the same reason, we should be able to apply these gates to DDs of 100+ qubits with **no change** to the structure of the DD; **no change** to the Complex numbers table
- Refactor the `LimEntry` class as below. The purpose is to be able to do the intermediate computations algebra on objects which do not needlessly allocate an unsigned int field.
  Currently, the `LimEntry` object has a `refCount` field, which is copied and allocates in these intermediate computations, taking time and a little bit of memory.
```c++
template<std::size_t Num_qubits>
class LimEntry {
    PauliString paulis;
    unsigned int refCount;
};
template<std::size_t Num_qubits>
class PauliString {
    std::bitset<2*Num_qubits+2> paulis;
};
```
- use `std::vector::emplace_back(constructor parameters)` to add stuff to a vector; this calls one fewer copy constructor than `std::vector::push_back(object)` (if I understand correctly)
- (low priority, requires much research) don't save the stabilizer group of knife and spoons. Only save the stabilizer group of forks.
  Recompute the stabilizer group of a knife and a fork when necessary
  - Knife: a state $|f> = |0>|g>$
  - Fork:  a state $|f> = |0>|g> + |1>|h>$
  - Spoon: a state $|f> = |0>|v> + |1>P|v>$

## Memory leaks

In PauliAlgebra.hpp, the following functions have memory leaks.
These memory leaks can be repaired by using local objects wherever possible,
instead of dynamically allocated ones (which are not subsequently freed).
Concretely, there are many algorithms that manipulate "Stabilizer groups", which are currently of type
`std::vector<LimEntry<>*>` but would not leak when we refactor them to type `std::vector<LimEntry>`.
Incidentally, this will make the runtimes much better

- In functions in `PauliAlgebra.hpp`  that currently return a `LimEntry<>` object by reference, return a `PauliString` object by value (or pass a `PauliString` object by reference as a parameter? I don't know if that's faster)
- Replace all `std::vector<LimEntry<>*>` by `std::vector<PauliString>`
- Return `LimEntry<>` objects by value instead of by reference
- Replace the `LimBitset<Num_qubits>` by a smarter `LimBitset<Num_qubits, Num_bits>`, to be used in `PauliAlgebra.hpp::getKernel()`. This recognizes that the use case only uses a `LimBitset` with a large bitset, but with a small number of Pauli operators.
- I don't think a separate "cache" for `LimEntry` (or `PauliString`) objects is necessary.

The following functions in `PauliAlgebra.hpp` currently possibly have memory leaks:

- `highLabelPauli()`
- `constructStabilizerGeneratorSetPauli()`
- `getCosetIntersectionElementPauli()`
- `getCosetIntersectionModuloPhase()`
- `groupConcatenate()`
- `appendIdentityMatrixBitset()`
- `getKernelModuloPhase()`
- `getProductofElements()`
- `GaussianElimination()`
- `GramSchmidt()`
- in `LimWeight` class, make the LimEntry<> object a data field instead of a pointer

# Success criteria

It is useful to set up success criteria, so that we know a succesful implementation when we see one:
- There are no memory leaks
- Clifford circuits and stabilizer states have very fast runtimes
- All downward Controlled Pauli gates can be applied with no loss in floating point accuracy
- some circuits on 100+ qubits can be simulated
  - even if some gates have a control qubit that is 100+ indices away from the target qubit
