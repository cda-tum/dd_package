#include "dd/LimTable.hpp"
#include "dd/Package.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(LimTest, SinglePauliOps) {
    dd::LimEntry<1> id{(int)0b000};
    dd::LimEntry<1> z{0b001};
    dd::LimEntry<1> x{0b010};
    dd::LimEntry<1> y{0b011};

    EXPECT_EQ(dd::LimEntry<1>::getQubit(&id, 0), 'I');
    EXPECT_EQ(dd::LimEntry<1>::getQubit(&x, 0), 'X');
    EXPECT_EQ(dd::LimEntry<1>::getQubit(&y, 0), 'Y');
    EXPECT_EQ(dd::LimEntry<1>::getQubit(&z, 0), 'Z');
}

TEST(LimTest, PauliToString) {
    dd::LimEntry<5> limEntry{0b011011000u}; // ...IIIYXZI. Bit order!

    auto str = dd::LimEntry<5>::to_string(&limEntry);

    std::cout << str << "\n";

    EXPECT_STREQ(str.c_str(), "IXZYI");

    auto str_default = dd::LimEntry<5>::to_string(nullptr);
    std::cout << str_default << "\n";

    EXPECT_STREQ(str_default.c_str(), "IIIII");
}

TEST(LimTest, BitSetFromString) {
    // bitsetFromString function
    auto bitSet = dd::LimEntry<6>::bitsetFromString("XIIYYZ");
    EXPECT_EQ(bitSet.to_ulong(), 0b011111000010); // XIIYYZ

    // LimEntry constructor
    dd::LimEntry<7>  limEntry{"YXXZIIZ"};
    dd::LimEntry<10> limEntry2{"XX"};

    auto str1 = dd::LimEntry<7>::to_string(&limEntry);
    auto str2 = dd::LimEntry<10>::to_string(&limEntry2);

    EXPECT_STREQ(str1.c_str(), "YXXZIIZ");
    EXPECT_STREQ(str2.c_str(), "XXIIIIIIII"); // NOTE: trailing I's on the right
}

TEST(LimTest, SimpleTableDefault) {
    auto limtable = std::make_unique<dd::LimTable<>>();
    std::cout << "Limtable size " << sizeof(*limtable) << " byte\n";
    std::cout << "LimEntry size " << sizeof(dd::LimEntry<>) << " byte \n";
    std::cout << "LimBitSt size " << sizeof(dd::LimEntry<>::paulis) << " byte \n";

    limtable->lookup(1);
    limtable->lookup(2);
    limtable->lookup(3);

    auto* y = limtable->lookup(3);
    auto* i = limtable->lookup(0);
    limtable->incRef(y);
    limtable->incRef(i);

    limtable->print();

    EXPECT_EQ(y->refCount, 1);
    EXPECT_EQ(i->refCount, 2);

    std::cout << "Garbage Collection\n";

    auto count = limtable->garbageCollect(true);
    EXPECT_EQ(count, 2); // Collect Z and X

    limtable->print();

    std::cout << "Again\n";

    limtable->decRef(y);
    count = limtable->garbageCollect(true);
    EXPECT_EQ(count, 1); // Collect y

    limtable->print();
}

TEST(LimTest, SimpleTable8) {
    /* Note that due to usage of default template parameters, actual code might break if used with a different LimTable setup */
    auto limtable = std::make_unique<dd::LimTable<8, 32>>();
    std::cout << "Limtable size " << sizeof(*limtable) << " byte\n";
    std::cout << "LimEntry size " << sizeof(dd::LimEntry<8>) << " byte \n";
    std::cout << "LimBitSt size " << sizeof(dd::LimEntry<8>::paulis) << " byte \n";

    limtable->lookup(1);
    limtable->lookup(2);
    limtable->lookup(3);

    auto* y = limtable->lookup(3);
    auto* i = limtable->lookup(0);
    limtable->incRef(y);
    limtable->incRef(i);

    limtable->print();

    EXPECT_EQ(y->refCount, 1);
    EXPECT_EQ(i->refCount, 2);

    std::cout << "Garbage Collection\n";

    auto count = limtable->garbageCollect(true);
    EXPECT_EQ(count, 2); // Collect Z and X

    limtable->print();
}

TEST(LimTest, NodeLims) {
    /* Note that due to usage of default template parameters, actual code might break if used with a different LimTable setup */
    auto dd        = std::make_unique<dd::Package>(1);
    auto root_edge = dd->makeZeroState(1);

    auto* y = dd->getLimTable().lookup(3);
    auto* i = dd->getLimTable().lookup(1);

    root_edge.p->limVector.push_back(y);
    root_edge.p->limVector.push_back(y);
    root_edge.p->limVector.push_back(i);

    dd->incRef(root_edge);
    dd->getLimTable().print();

    EXPECT_EQ(y->refCount, 2);
    EXPECT_EQ(i->refCount, 1);

    dd->decRef(root_edge);
    dd->getLimTable().print();

    EXPECT_EQ(y->refCount, 0);
    EXPECT_EQ(i->refCount, 0);

    std::cout << "Garbage Collection\n";

    auto count = dd->getLimTable().garbageCollect(true);
    EXPECT_EQ(count, 2);

    dd->getLimTable().print();
}

TEST(LimTest, LimHashing) {
    auto dd        = std::make_unique<dd::Package>(2);
    auto root_edge = dd->makeZeroState(2);

    auto hash1 = dd->vUniqueTable.hash(root_edge.p);

    auto* y = dd->getLimTable().lookup(3);
    auto* i = dd->getLimTable().lookup(1);

    root_edge.p->e[0].p->limVector.push_back(y);
    root_edge.p->e[0].p->limVector.push_back(y);
    root_edge.p->e[0].p->limVector.push_back(i);

    auto hash2 = dd->vUniqueTable.hash(root_edge.p);

    EXPECT_NE(hash1, hash2);
}

TEST(LimTest, SimpleTable127) {
    /* Note that due to usage of default template parameters, actual code might break if used with a different LimTable setup */
    auto limtable = std::make_unique<dd::LimTable<127>>();
    std::cout << "Limtable size " << sizeof(*limtable) << " byte\n";
    std::cout << "LimEntry size " << sizeof(dd::LimEntry<127>) << " byte \n";
    std::cout << "LimBitSt size " << sizeof(dd::LimEntry<127>::paulis) << " byte \n";

    limtable->lookup(1);
    limtable->lookup(2);
    limtable->lookup(3);

    auto* y = limtable->lookup(3);
    auto* i = limtable->lookup(0);
    limtable->incRef(y);
    limtable->incRef(i);

    limtable->print();

    EXPECT_EQ(y->refCount, 1);
    EXPECT_EQ(i->refCount, 2);

    std::cout << "Garbage Collection\n";

    auto count = limtable->garbageCollect(true);
    EXPECT_EQ(count, 2); // Collect Z and X

    limtable->print();
}

TEST(LimTest, LookupFromStrings) {
    auto limtable = std::make_unique<dd::LimTable<>>();
    std::cout << "Limtable size " << sizeof(*limtable) << " byte\n";
    std::cout << "LimEntry size " << sizeof(dd::LimEntry<>) << " byte \n";
    std::cout << "LimBitSt size " << sizeof(dd::LimEntry<>::paulis) << " byte \n";

    auto* insert1 = limtable->lookup_str("XZXZ");
    auto* insert2 = limtable->lookup_str("IIYY");

    EXPECT_NE(insert1, insert2);

    limtable->print();

    auto* get1 = limtable->lookup_str("XZXZ");
    auto* get2 = limtable->lookup_str("IIYY");

    EXPECT_EQ(insert1, get1);
    EXPECT_EQ(insert2, get2);
}

TEST(LimTest, MultiplyPauliStrings) {
    // TODO: also include phase in test
    dd::LimEntry<1> x{"X"};
    dd::LimEntry<1> y{"Y"};
    dd::LimEntry<1> z{"Z"};

    // XZ = iY
    dd::LimEntry<1> xz{"X"};
    xz.multiplyBy(z);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&xz).c_str(), "Y");

    // ZX = -iY
    dd::LimEntry<1> zx{"Z"};
    zx.multiplyBy(x);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&xz).c_str(), "Y");

    // XY = iZ
    dd::LimEntry<1> xy{"X"};
    xy.multiplyBy(y);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&xy).c_str(), "Z");

    // YX = -iZ
    dd::LimEntry<1> yx{"Y"};
    yx.multiplyBy(x);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&yx).c_str(), "Z");

    // ZY = -iX
    dd::LimEntry<1> zy{"Z"};
    zy.multiplyBy(y);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&zy).c_str(), "X");

    // YZ = iX
    dd::LimEntry<1> yz{"Y"};
    yz.multiplyBy(z);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&yz).c_str(), "X");

    dd::LimEntry<5> lim1{"IIXYZ"};
    dd::LimEntry<5> lim2{"XIZZZ"};
    lim1.multiplyBy(lim2);
    EXPECT_STREQ(dd::LimEntry<5>::to_string(&lim1).c_str(), "XIYXI");
}

TEST(LimTest, createDDNode) {
    auto dd  = std::make_unique<dd::Package>(1);
    auto lim = dd->limTable.lookup('X');

    EXPECT_EQ(dd->vUniqueTable.getActiveNodeCount(), 0);
    EXPECT_EQ(dd->vUniqueTable.getNodeCount(), 0);

    auto l = dd->makeDDNode(1, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, lim);

    EXPECT_EQ(dd->vUniqueTable.getActiveNodeCount(), 0);
    EXPECT_EQ(dd->vUniqueTable.getNodeCount(), 1);

    dd->incRef(l);

    EXPECT_EQ(dd->vUniqueTable.getActiveNodeCount(), 1);
    EXPECT_EQ(dd->vUniqueTable.getNodeCount(), 1);
}

TEST(LimTest, CreateNode0) {
    auto dd  = std::make_unique<dd::Package>(1);
    auto lim = dd->limTable.lookup('X');

    dd::Edge<dd::vNode> e{dd->vUniqueTable.getNode(), dd::Complex::one, lim};
    e.p->v = 0;
    e.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::zero};

    e = dd->normalizeLIMDD(e, false);

    EXPECT_EQ(dd->vUniqueTable.getActiveNodeCount(), 0);
    EXPECT_EQ(dd->vUniqueTable.getNodeCount(), 0);

    auto l = dd->vUniqueTable.lookup(e, false);

    EXPECT_EQ(dd->vUniqueTable.getActiveNodeCount(), 0);
    EXPECT_EQ(dd->vUniqueTable.getNodeCount(), 1);

    dd->incRef(l);

    EXPECT_EQ(dd->vUniqueTable.getActiveNodeCount(), 1);
    EXPECT_EQ(dd->vUniqueTable.getNodeCount(), 1);
}

TEST(LimTest, CreateNode1) {
    // This test:
    //  Create a node for |+> |+>, i.e., the state [1 1 1 1].
    //  Create two nodes for |+>, and then a node both of whose edges point to |+>.
    auto dd  = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode1.\n"; std::cout.flush();

    // Create |+>
    dd::Edge<dd::vNode> e1{dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e1.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};

    // Create another |+>
    dd::Edge<dd::vNode> e2{dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e2.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};

    dd::Edge<dd::vNode> e3{dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e3.p->e = {e1,e2};

    e3 = dd->normalizeLIMDD(e3, false);

    // Assert: identity label on low edge
    EXPECT_EQ(dd::LimEntry<>::isIdentity(e3.p->e[0].l), true);
    // Assert: identity label on high edge
    EXPECT_EQ(dd::LimEntry<>::isIdentity(e3.p->e[1].l), true);
}

TEST(LimTest, CreateNode2) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode2.\n";

    // Create node |+>
    dd::vNode* plus = dd->vUniqueTable.getNode();
    plus->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    plus->v = 0;

    // Create edge I|+>
    dd::Edge<dd::vNode> e0 = {plus, dd::Complex::one, nullptr};

    // Create edge Z|+>
    dd::LimEntry<>* l = new dd::LimEntry<>("Z");
    dd::Edge<dd::vNode> e1 = {plus, dd::Complex::one, l};

    // Create edge |0>|e0> + |1>|e1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e = {e0, e1};
    // normalize the edge / node
    e = dd->normalizeLIMDD(e, false);
    std::cout << "root label: (should be I): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::isIdentity(e.l), true);
    std::cout << "high label: (should be Z):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::Equal(e.p->e[1].l, l), true);
}

TEST(LimTest, CreateNode3) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode3.\n";

    // Create node |+>
    dd::vNode* plus = dd->vUniqueTable.getNode();
    plus->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    plus->v = 0;

    // Create edge Z|+>
    dd::LimEntry<>* l = new dd::LimEntry<>("Z");
    dd::Edge<dd::vNode> e0 = {plus, dd::Complex::one, l};

    // Create edge I|+>
    dd::Edge<dd::vNode> e1 = {plus, dd::Complex::one, nullptr};

    // Create edge |0>|e0> + |1>|e1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e = {e0, e1};
    // normalize the edge / node
    e = dd->normalizeLIMDD(e, false);
    std::cout << "root label: (should be Z): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::Equal(e.l, l), true);
    std::cout << "high label: (should be Z):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::Equal(e.p->e[1].l, l), true);
}

TEST(LimTest, CreateNode4) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode4.\n";

    dd::LimEntry<>* lim = new dd::LimEntry<>("Z");
    // Create node |0>
    dd::vNode* zeroState = dd->vUniqueTable.getNode();
    zeroState->e = {dd::Package::vEdge::one, dd::Package::vEdge::zero};
    // Add Z to the stabilizer group of zeroState
    zeroState->limVector.push_back(lim);


    // Create node |+>
    dd::vNode* plus = dd->vUniqueTable.getNode();
    plus->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    plus->v = 0;

    // Create edge I|0>
    dd::Edge<dd::vNode> e0 = {zeroState, dd::Complex::one, nullptr};

    // Create edge Z|+>
    dd::Edge<dd::vNode> e1 = {plus, dd::Complex::one, lim};


    // Create edge |0>|e0> + |1>|e1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e = {e0, e1};
    // normalize the edge / node
    e = dd->normalizeLIMDD(e, false);
    std::cout << "root label: (should be Z): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::Equal(e.l, lim), true);
    std::cout << "high label: (should be I):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::isIdentity(e.p->e[1].l), true);
}

TEST(LimTest, CreateNode6) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode6.\n";

    // Create node |0>
    dd::vNode* zeroState = dd->vUniqueTable.getNode();
    zeroState->e = {dd::Package::vEdge::one, dd::Package::vEdge::zero};
    // Add stabilizer Z
    dd::LimEntry<>* limZ = new dd::LimEntry<>("Z");
    zeroState->limVector.push_back(limZ);

    // Create node |0>|0>
    dd::vNode* zeroZero = dd->vUniqueTable.getNode();
    dd::Edge<dd::vNode> e0 = {zeroState, dd::Complex::one, nullptr};
    zeroZero->e = {e0, dd::Package::vEdge::zero};
    // Add stabilizers ZI and IZ
    dd::LimEntry<>* limIZ = new dd::LimEntry<>("IZ");
    zeroZero->limVector.push_back(limZ);
    zeroZero->limVector.push_back(limIZ);

    // Create edge I |0>|0>
    dd::Edge<dd::vNode> zeroZeroEdge = {zeroZero, dd::Complex::one, nullptr};

    // Create edge ZZ |0>|0>
    dd::LimEntry<>* lim = new dd::LimEntry<>("ZZ");
    dd::Edge<dd::vNode> zeroZeroZEdge= {zeroZero, dd::Complex::one, lim};

    // Create node |0>|zeroZeroEdge> + |1>|zeroZeroZEdge>
    dd::vNode* v = dd->vUniqueTable.getNode();
    v->e = {zeroZeroEdge, zeroZeroZEdge};

    // Create edge to v
    dd::Edge<dd::vNode> e = {v, dd::Complex::one, nullptr};

    // normalize the edge / node
    e = dd->normalizeLIMDD(e, false);
    std::cout << "root label: (should be I): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::isIdentity(e.l), true);
    std::cout << "high label: (should be I):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ( dd::LimEntry<>::isIdentity(e.p->e[1].l), true);
}

TEST(LimTest, CreateNode7) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode7\n";

    // Create edge I|0>
    dd::Edge<dd::vNode> zero = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zero.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::zero};
    // Construct stabilizer group of |0>
    zero.p->limVector.push_back(new dd::LimEntry<>("Z"));

    // Create edge II |0>|0>
    dd::Edge<dd::vNode> zeroZero0 = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zeroZero0.p->e = {zero, dd::Package::vEdge::zero};
    // Construct stabilizer group
    zeroZero0.p->limVector.push_back(new dd::LimEntry<>("ZI"));
    zeroZero0.p->limVector.push_back(new dd::LimEntry<>("IZ"));
    // Create a second edge II |0>|0>
    dd::Edge<dd::vNode> zeroZero1 = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zeroZero1.p->e = {zero, dd::Package::vEdge::zero};
    zeroZero1.p->limVector.push_back(new dd::LimEntry<>("ZI"));
    zeroZero1.p->limVector.push_back(new dd::LimEntry<>("IZ"));


    // Create edge I|0>|zeroZero0> + |0>|zeroZero1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e = {zeroZero0, zeroZero1};
    e = dd->normalizeLIMDD(e, false);

    std::cout << "root label: (should be I): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::isIdentity(e.l), true);
    std::cout << "high label: (should be I): " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::isIdentity(e.p->e[1].l), true);
}

TEST(LimTest, GaussianElimination1) {
    dd::StabilizerGroup G;
    dd::LimEntry<32>    zi{"ZI"};
    dd::LimEntry<32>    zz{"ZZ"};
    G.push_back(&zi);
    G.push_back(&zz);
    std::cout << "Group before Gaussian elimination:\n";
    dd::Pauli::printStabilizerGroup(G);
    dd::Pauli::GaussianElimination(G);
    std::cout << "Group after Gaussian elimination:\n";
    dd::Pauli::printStabilizerGroup(G);
    dd::StabilizerGroup expectedGroup;
    dd::LimEntry<32>    iz("IZ");
    expectedGroup.push_back(&zi);
    expectedGroup.push_back(&iz);
    EXPECT_EQ(dd::Pauli::stabilizerGroupsEqual(G, expectedGroup), true);
}

TEST(LimTest, GaussianElimination2) {
    dd::StabilizerGroup G;
    dd::LimEntry<>      zzi {"ZZI"};
    dd::LimEntry<>      zzi2{"ZZI"};
    dd::LimEntry<>      ziz {"ZIZ"};
    dd::LimEntry<>      izz {"IZZ"};
    G.push_back(&zzi);
    G.push_back(&zzi2);
    G.push_back(&ziz);
    G.push_back(&izz);
    std::cout << "Group before Gaussian elimination:\n";
    dd::Pauli::printStabilizerGroup(G);
    dd::Pauli::GaussianElimination(G);
    std::cout << "Group after Gaussian elimination:\n";
    dd::Pauli::printStabilizerGroup(G);

    // build expected group
    dd::LimEntry<>      ziz_exp{"ZIZ"};
    dd::LimEntry<>      iii_exp{"III"};
    dd::LimEntry<>      izz_exp{"IZZ"};
    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(&ziz_exp);
    expectedGroup.push_back(&iii_exp);
    expectedGroup.push_back(&izz_exp);
    expectedGroup.push_back(&iii_exp);
    //    std::cout << "Expected group:\n";
    //    dd::Pauli::printStabilizerGroup(expectedGroup);
    EXPECT_EQ(dd::Pauli::stabilizerGroupsEqual(G, expectedGroup), true);
}

TEST(LimTest, columnEchelonForm1) {
    dd::StabilizerGroup G;
    dd::LimEntry<>      zzi {"ZZI"};
    dd::LimEntry<>      zzi2{"ZZI"};
    dd::LimEntry<>      ziz {"ZIZ"};
    dd::LimEntry<>      izz {"IZZ"};
    G.push_back(&zzi);
    G.push_back(&zzi2);
    G.push_back(&ziz);
    G.push_back(&izz);
    std::cout << "Group before column echelon form:\n";
    dd::Pauli::printStabilizerGroup(G);
    dd::Pauli::toColumnEchelonForm(G);
    std::cout << "Group after column echelon form:\n";
    dd::Pauli::printStabilizerGroup(G);

    dd::LimEntry<>      ziz_exp{"ZIZ"};
    dd::LimEntry<>      izz_exp{"IZZ"};
    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(&ziz_exp);
    expectedGroup.push_back(&izz_exp);
    EXPECT_EQ(dd::Pauli::stabilizerGroupsEqual(G, expectedGroup), true);
}
