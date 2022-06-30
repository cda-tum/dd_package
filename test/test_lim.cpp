#include "dd/Export.hpp"
#include "dd/LimTable.hpp"
#include "dd/Package.hpp"
#include "dd/PauliAlgebra.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace dd::literals;

std::ostream& operator<<(std::ostream& out, const dd::CVec& vec) {
	for (unsigned int i=0; i<vec.size(); i++) {
		out << vec[i] << ' ';
	}
	return out;
}

TEST(LimTest, SinglePauliOps) {
    dd::LimEntry<1> id{0b000};
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

TEST(LimTest, PauliToStringWithPhase) {
    dd::LimEntry<5> lim0{"ZXY"};
    EXPECT_EQ(dd::LimEntry<5>::getPhase(&lim0), dd::phase_t::phase_one);
    EXPECT_EQ(lim0.getQubit(0), 'Z');
    EXPECT_EQ(lim0.getQubit(1), 'X');

    dd::LimEntry<5> lim1{"-ZI"};
    EXPECT_EQ(dd::LimEntry<5>::getPhase(&lim1), dd::phase_t::phase_minus_one);
    EXPECT_EQ(lim1.getQubit(0), 'Z');
    EXPECT_EQ(lim1.getQubit(1), 'I');

    dd::LimEntry<5> lim2{"iZI"};
    EXPECT_EQ(dd::LimEntry<5>::getPhase(&lim2), dd::phase_t::phase_i);
    EXPECT_EQ(lim2.getQubit(0), 'Z');
    EXPECT_EQ(lim2.getQubit(1), 'I');

    dd::LimEntry<5> lim3{"-iIZX"};
    EXPECT_EQ(dd::LimEntry<5>::getPhase(&lim3), dd::phase_t::phase_minus_i);
    EXPECT_EQ(lim3.getQubit(0), 'I');
    EXPECT_EQ(lim3.getQubit(1), 'Z');
    EXPECT_EQ(lim3.getQubit(2), 'X');
}

TEST(LimTest, muliplyByMinusOne) {
    dd::Complex z = dd::Complex::one;
    z.multiplyByMinusOne(false);
    EXPECT_TRUE(dd::ComplexTable<>::Entry::approximatelyEquals(dd::ComplexTable<>::Entry::val(z.r), -1));

    dd::Complex m = dd::Complex::minusOne();
    EXPECT_TRUE(z.approximatelyEquals(m));

    EXPECT_FALSE(z.approximatelyEquals(dd::Complex::one));

    dd::Complex s{&dd::ComplexTable<>::sqrt2_2, &dd::ComplexTable<>::one};
    s.multiplyByMinusOne(false);
    EXPECT_TRUE(dd::ComplexTable<>::Entry::approximatelyEquals(dd::ComplexTable<>::Entry::val(s.r), -dd::SQRT2_2));
    EXPECT_TRUE(dd::ComplexTable<>::Entry::approximatelyEquals(dd::ComplexTable<>::Entry::val(s.i), -1));
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

    // XZ = -iY
    dd::LimEntry<1> xz{"X"};
    xz.multiplyBy(z);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&xz).c_str(), "-iY");

    // ZX = iY
    dd::LimEntry<1> zx{"Z"};
    zx.multiplyBy(x);
    std::cout << "zx[2] = " << zx.paulis.test(2) << ", zx[3] = " << zx.paulis.test(3) << ".\n";
    std::cout << "zx = " << zx << std::endl;
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&zx).c_str(), "iY");

    // XY = iZ
    dd::LimEntry<1> xy{"X"};
    xy.multiplyBy(y);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&xy).c_str(), "iZ");

    // YX = -iZ
    dd::LimEntry<1> yx{"Y"};
    yx.multiplyBy(x);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&yx).c_str(), "-iZ");

    // ZY = -iX
    dd::LimEntry<1> zy{"Z"};
    zy.multiplyBy(y);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&zy).c_str(), "-iX");

    // YZ = iX
    dd::LimEntry<1> yz{"Y"};
    yz.multiplyBy(z);
    EXPECT_STREQ(dd::LimEntry<1>::to_string(&yz).c_str(), "iX");

    // (IX).(II).(XZ).(YZ).(ZZ) = (X).(I).(-iY).(iX).(I) = XIYXI
    //   here '.' is the tensor product
    dd::LimEntry<5> lim1{"IIXYZ"};
    dd::LimEntry<5> lim2{"XIZZZ"};
    lim1.multiplyBy(lim2);
    EXPECT_STREQ(dd::LimEntry<5>::to_string(&lim1).c_str(), "XIYXI");
}

TEST(LimTest, bitsetXOR) {
    std::bitset<3> bits0;
    std::bitset<3> bits1;
    std::cout << "[bitsetXOR] bits0 = " << bits0 << "  bits1 = " << bits1 << "\n";
    bits0.set(0, 1);
    bits1 ^= bits0;
    std::cout << "[bitsetXOR] after XORing, bits0 = " << bits0 << "  bits1 = " << bits1 << "\n";
    EXPECT_TRUE(bits1.test(0));
}

TEST(LimTest, getVectorLIMDD1) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge e0 = Z|0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    auto     vec = dd->getVectorLIMDD(e0);
    dd::CVec expectedVec;
    expectedVec.push_back({1.0, 0.0});
    expectedVec.push_back({0.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD2) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge Z|+>
    dd::LimEntry<>* lim = new dd::LimEntry<>("Z");
    auto            e0  = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, lim);

    auto     vec = dd->getVectorLIMDD(e0);
    dd::CVec expectedVec;
    expectedVec.push_back({1.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD3) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge Z|1>
    dd::LimEntry<>* lim = new dd::LimEntry<>("Z");
    auto            e0  = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, lim);

    std::cout << "[getVector3] constructing amplitude vector.\n";
    std::cout.flush();
    auto     vec = dd->getVectorLIMDD(e0);
    dd::CVec expectedVec;
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD4) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |1>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    auto vec0 = dd->getVectorLIMDD(e0);
    std::cout << "[getVectorLIMDD4 test] intermediate vec0: " << vec0 << '\n';

    // make edge ZI|1>|1>
    dd::LimEntry<>* lim = new dd::LimEntry<>("IZ");
    auto e1 = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, lim);

    auto     vec = dd->getVectorLIMDD(e1);
    dd::CVec expectedVec;//{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {-1.0,0.0}};
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});
    std::cout << "[getVectorLIMDD4 test] expected vector: " << expectedVec << '\n';
    std::cout << "[getVectorLIMDD4 test] result   vector: " << vec << '\n';

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD5) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge Z|1>
    dd::LimEntry<>* lim0 = new dd::LimEntry<>("Z");
    auto            e0   = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, lim0);

    // make edge ZI|1>|1>
    dd::LimEntry<>* lim1 = new dd::LimEntry<>("IZ");
    auto            e1   = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, lim1);

    auto     vec = dd->getVectorLIMDD(e1);
    dd::CVec expectedVec;
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({1.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD6) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge ZI|1>|0>
    dd::LimEntry<>* lim = new dd::LimEntry<>("IZ");
    auto            e1  = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, lim);

    auto     vec = dd->getVectorLIMDD(e1);
    dd::CVec expectedVec;
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});
    expectedVec.push_back({0.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD7) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |+>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge ZI|1>|+>
    dd::LimEntry<>* lim = new dd::LimEntry<>("Z");
    auto            e1  = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, lim);

    auto     vec = dd->getVectorLIMDD(e1);
    dd::CVec expectedVec;
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD8) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge Z|+>
    dd::LimEntry<>* lim0 = new dd::LimEntry<>("Z");
    auto            e0   = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, lim0);

    // make edge ZI|1>Z|+>
    dd::LimEntry<>* lim1 = new dd::LimEntry<>("IZ");
    std::cout << "[getVector8] lim1 = " << dd::LimEntry<>::to_string(lim1) << "\n";
    auto e1 = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, lim1);

    auto     vec = dd->getVectorLIMDD(e1);
    dd::CVec expectedVec;
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});
    expectedVec.push_back({1.0, 0.0});

    dd->printCVec(vec);

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD9) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |+>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge ZI|0>|+>
    dd::LimEntry<>* lim = new dd::LimEntry<>("IZ");
    auto            e1  = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, lim);

    auto     vec = dd->getVectorLIMDD(e1);
    dd::CVec expectedVec;
    expectedVec.push_back({1.0, 0.0});
    expectedVec.push_back({1.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({0.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD10) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge Z|+>
    dd::LimEntry<>* lim1 = new dd::LimEntry<>("Z");
    auto            e1   = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, lim1);

    // make edge ZZ(|0>|0> + |1>Z|+>)
    dd::LimEntry<>* lim2 = new dd::LimEntry<>("ZZ");
    auto            e2   = dd->makeDDNode(1, std::array{e0, e1}, false, lim2);

    auto     vec = dd->getVectorLIMDD(e2);
    dd::CVec expectedVec;
    expectedVec.push_back({1.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD11) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge ZZ(|0>|0> + |1>|+>)
    dd::LimEntry<>* lim2 = new dd::LimEntry<>("ZZ");
    auto            e2   = dd->makeDDNode(1, std::array{e0, e1}, false, lim2);

    auto     vec = dd->getVectorLIMDD(e2);
    dd::CVec expectedVec;
    expectedVec.push_back({1.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});
    expectedVec.push_back({1.0, 0.0});

    //    std::cout << "[getVector1] vec: " << vec << '\n';
    //    std::cout << "[getVector1] expected: " << expectedVec << '\n';

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, getVectorLIMDD12) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |+>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge Z|1>
    dd::LimEntry<>* lim1 = new dd::LimEntry<>("Z");
    auto            e1   = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, lim1);

    // make edge ZZ(|0>|+> + |1>Z|1>)
    dd::LimEntry<>* lim2 = new dd::LimEntry<>("ZZ");
    auto            e2   = dd->makeDDNode(1, std::array{e0, e1}, false, lim2);

    auto     vec = dd->getVectorLIMDD(e2);
    dd::CVec expectedVec;
    expectedVec.push_back({1.0, 0.0});
    expectedVec.push_back({-1.0, 0.0});
    expectedVec.push_back({0.0, 0.0});
    expectedVec.push_back({1.0, 0.0});

    EXPECT_TRUE(dd->vectorsApproximatelyEqual(vec, expectedVec));
}

TEST(LimTest, GramSchmidt1) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("Z"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("I");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("I");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt2) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("Z"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("Z");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("I");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt3) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("Z"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("ZZ");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("IZ");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt4) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("Z"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("YZ");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("iXZ");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt5) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("Y"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("YZ");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("IZ");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt6) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("YZ"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("YZ");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("I");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt7) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("YI"));
    G.push_back(new dd::LimEntry<>("IZ"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("YZ");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("I");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt8) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("IZ"));
    G.push_back(new dd::LimEntry<>("YI"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("YZ");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("II");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt9) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("IZ"));
    G.push_back(new dd::LimEntry<>("YX"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("YZ");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("-IX");
    std::cout << "[GramSchmidt9 test] y = " << *y << std::endl;
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt10) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("IYZ"));
    G.push_back(new dd::LimEntry<>("ZIZ"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("ZYI");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("I");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt11) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("IYZ"));
    G.push_back(new dd::LimEntry<>("ZXZ"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("ZYI");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("-IXI");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, GramSchmidt12) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("ZZZ"));
    G.push_back(new dd::LimEntry<>("IZZ"));
    G.push_back(new dd::LimEntry<>("IIZ"));
    dd::LimEntry<>* x        = new dd::LimEntry<>("ZZI");
    dd::LimEntry<>* y        = dd::Pauli::GramSchmidt(G, x);
    dd::LimEntry<>* expected = new dd::LimEntry<>("I");
    EXPECT_EQ(*y, *expected);
}

TEST(LimTest, intersectGroupsZ1) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZI"));
    G.push_back(new dd::LimEntry<>("IZ"));
    H.push_back(new dd::LimEntry<>("-ZI"));
    H.push_back(new dd::LimEntry<>("-IZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("ZZ"));
    std::cout << "[intersectGroupsZ1 test] intersection:\n";
    dd::Pauli::printStabilizerGroup(intersection);
    std::cout << "interssectGroupsZ1 test] expected intersection:\n";
    dd::Pauli::printStabilizerGroup(expectedIntersection);
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ2) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZII"));
    G.push_back(new dd::LimEntry<>("IZI"));
    G.push_back(new dd::LimEntry<>("IIZ"));
    H.push_back(new dd::LimEntry<>("-ZII"));
    H.push_back(new dd::LimEntry<>("IZI"));
    H.push_back(new dd::LimEntry<>("-IIZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("ZIZ"));
    expectedIntersection.push_back(new dd::LimEntry<>("IZI"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ3) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZIZ"));
    G.push_back(new dd::LimEntry<>("IZZ"));
    H.push_back(new dd::LimEntry<>("IZI"));
    H.push_back(new dd::LimEntry<>("IIZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("IZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ4) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("IZZ"));
    G.push_back(new dd::LimEntry<>("IIZ"));
    H.push_back(new dd::LimEntry<>("IZI"));
    H.push_back(new dd::LimEntry<>("IIZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("IZI"));
    expectedIntersection.push_back(new dd::LimEntry<>("IIZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ5) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZIIZ"));
    G.push_back(new dd::LimEntry<>("IZZZ"));
    H.push_back(new dd::LimEntry<>("IIZI"));
    H.push_back(new dd::LimEntry<>("IIIZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ6) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZIZ"));
    G.push_back(new dd::LimEntry<>("-IZI"));
    H.push_back(new dd::LimEntry<>("-ZIZ"));
    H.push_back(new dd::LimEntry<>("IZI"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("-ZZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ7) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZZIZ"));
    G.push_back(new dd::LimEntry<>("IIZZ"));
    H.push_back(new dd::LimEntry<>("-ZZZZ"));
    H.push_back(new dd::LimEntry<>("-IIZZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ8) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZIZI"));
    G.push_back(new dd::LimEntry<>("IZZI"));
    G.push_back(new dd::LimEntry<>("IIIZ"));
    H.push_back(new dd::LimEntry<>("-ZIII"));
    H.push_back(new dd::LimEntry<>("IZZZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("IZZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsZ9) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZIZI"));
    G.push_back(new dd::LimEntry<>("-IZZI"));
    G.push_back(new dd::LimEntry<>("-IIIZ"));
    H.push_back(new dd::LimEntry<>("-ZIII"));
    H.push_back(new dd::LimEntry<>("IZZZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsZ(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("IZZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli1) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("X"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("X"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli2) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("Z"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli3) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("-X"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli4) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("iX"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli5) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("-iX"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli6) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    G.push_back(new dd::LimEntry<>("Z"));
    H.push_back(new dd::LimEntry<>("-iY"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("-iY"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli7) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    G.push_back(new dd::LimEntry<>("-Z"));
    H.push_back(new dd::LimEntry<>("iY"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("iY"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli8) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZZ"));
    G.push_back(new dd::LimEntry<>("XX"));
    H.push_back(new dd::LimEntry<>("XX"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("XX"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli9) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("YY"));
    G.push_back(new dd::LimEntry<>("XX"));
    H.push_back(new dd::LimEntry<>("XX"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("XX"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli10) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("YY"));
    G.push_back(new dd::LimEntry<>("XX"));
    H.push_back(new dd::LimEntry<>("YY"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("YY"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli11) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("XX"));
    G.push_back(new dd::LimEntry<>("YY"));
    H.push_back(new dd::LimEntry<>("-ZZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("-ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli12) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("XX"));
    G.push_back(new dd::LimEntry<>("YY"));
    H.push_back(new dd::LimEntry<>("ZI"));
    H.push_back(new dd::LimEntry<>("-IZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("-ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli13) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("XX"));
    G.push_back(new dd::LimEntry<>("YY"));
    H.push_back(new dd::LimEntry<>("-ZI"));
    H.push_back(new dd::LimEntry<>("IZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("-ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli14) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("-YY"));
    G.push_back(new dd::LimEntry<>("XX"));
    H.push_back(new dd::LimEntry<>("-iZI"));
    H.push_back(new dd::LimEntry<>("iIZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli15) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZZ"));
    G.push_back(new dd::LimEntry<>("XX"));
    H.push_back(new dd::LimEntry<>("-YY"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("-YY"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli16) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZZ"));
    G.push_back(new dd::LimEntry<>("XX"));
    H.push_back(new dd::LimEntry<>("-YI"));
    H.push_back(new dd::LimEntry<>("iXZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli17) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZZ"));
    G.push_back(new dd::LimEntry<>("XX"));
    H.push_back(new dd::LimEntry<>("-YY"));
    H.push_back(new dd::LimEntry<>("XX"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::Pauli::toColumnEchelonForm(intersection);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("ZZ"));
    expectedIntersection.push_back(new dd::LimEntry<>("XX"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

// Removed because this functionality is not necessary
//TEST(LimTest, intersectGroupsPauli18) {
//    dd::StabilizerGroup G, H;
//    G.push_back(new dd::LimEntry<>("-I"));
//    H.push_back(new dd::LimEntry<>("X"));
//    H.push_back(new dd::LimEntry<>("Y"));
//    H.push_back(new dd::LimEntry<>("Z"));
//    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
//    dd::StabilizerGroup expectedIntersection;
//    expectedIntersection.push_back(new dd::LimEntry<>("-I"));
//    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
//}
//
//TEST(LimTest, intersectGroupsPauli19) {
//    dd::StabilizerGroup G, H;
//    G.push_back(new dd::LimEntry<>("iI"));
//    H.push_back(new dd::LimEntry<>("X"));
//    H.push_back(new dd::LimEntry<>("Y"));
//    H.push_back(new dd::LimEntry<>("Z"));
//    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
//    dd::StabilizerGroup expectedIntersection;
//    expectedIntersection.push_back(new dd::LimEntry<>("-I"));
//    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
//}

TEST(LimTest, intersectGroupsPauli20) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("XZ"));
    G.push_back(new dd::LimEntry<>("ZX"));
    H.push_back(new dd::LimEntry<>("iYZ"));
    H.push_back(new dd::LimEntry<>("IX"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("YY"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, intersectGroupsPauli21) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("XIZ"));
    G.push_back(new dd::LimEntry<>("YIZ"));
    G.push_back(new dd::LimEntry<>("IIZ"));
    H.push_back(new dd::LimEntry<>("ZIZ"));
    H.push_back(new dd::LimEntry<>("IYI"));
    H.push_back(new dd::LimEntry<>("IIZ"));
    dd::StabilizerGroup intersection = dd::Pauli::intersectGroupsPauli(G, H);
    dd::StabilizerGroup expectedIntersection;
    expectedIntersection.push_back(new dd::LimEntry<>("IIZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(intersection, expectedIntersection));
}

TEST(LimTest, CosetElementZ1) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("Z"));
    H.push_back(new dd::LimEntry<>("-Z"));
    dd::LimEntry<>* a = new dd::LimEntry<>("-I");
    dd::LimEntry<>* x = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    std::cout << "[CosetElementZ1 test] Found coset intersection element: " << dd::LimEntry<>::to_string(x) << "\n";
    dd::LimEntry<>* expected1 = new dd::LimEntry<>("I");
    dd::LimEntry<>* expected2 = new dd::LimEntry<>("Z");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected1) || dd::LimEntry<>::Equal(x, expected2));
}

TEST(LimTest, CosetElementZ2) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("ZI"));
    H.push_back(new dd::LimEntry<>("ZZ"));
    dd::LimEntry<>* a = new dd::LimEntry<>("IZ");
    dd::LimEntry<>* x = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    std::cout << "[CosetElementZ1 test] Found coset intersection element: " << dd::LimEntry<>::to_string(x) << "\n";
    dd::LimEntry<>* expected1 = new dd::LimEntry<>("ZI");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected1));
}

TEST(LimTest, CosetElementPauli1) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("Y"));
    dd::LimEntry<>* a = new dd::LimEntry<>("I");
    dd::LimEntry<>* x = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    std::cout << "[CosetElementZ1 test] Found coset intersection element: " << dd::LimEntry<>::to_string(x) << "\n";
    dd::LimEntry<>* expected1 = new dd::LimEntry<>("I");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected1));
}

TEST(LimTest, CosetElementPauli2) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("X"));
    dd::LimEntry<>* a = new dd::LimEntry<>("I");
    dd::LimEntry<>* x = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    std::cout << "[CosetElementZ1 test] Found coset intersection element: " << dd::LimEntry<>::to_string(x) << "\n";
    dd::LimEntry<>* expected1 = new dd::LimEntry<>("I");
    dd::LimEntry<>* expected2 = new dd::LimEntry<>("X");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected1) || dd::LimEntry<>::Equal(x, expected2));
}

TEST(LimTest, CosetElementPauli3) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("X"));
    dd::LimEntry<>* a = new dd::LimEntry<>("X");
    dd::LimEntry<>* x = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    std::cout << "[CosetElementZ1 test] Found coset intersection element: " << dd::LimEntry<>::to_string(x) << "\n";
    dd::LimEntry<>* expected1 = new dd::LimEntry<>("I");
    dd::LimEntry<>* expected2 = new dd::LimEntry<>("X");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected1) || dd::LimEntry<>::Equal(x, expected2));
}

TEST(LimTest, CosetElementPauli4) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("Y"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("-iX");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = dd::LimEntry<>::noLIM;
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli5) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("Y"));
    dd::LimEntry<>* a = new dd::LimEntry<>("X");
    dd::LimEntry<>* x = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    std::cout << "[coset element pauli test 5] found element: " << *x << "\n";
    dd::LimEntry<>* expected = new dd::LimEntry<>("X");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli6) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("Y"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("iX");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = dd::LimEntry<>::noLIM;
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli7) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("X"));
    H.push_back(new dd::LimEntry<>("Y"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("-X");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = dd::LimEntry<>::noLIM;
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli8) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("Y"));
    H.push_back(new dd::LimEntry<>("X"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("-iZ");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = dd::LimEntry<>::noLIM;
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli9) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("Y"));
    H.push_back(new dd::LimEntry<>("X"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("Z");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = dd::LimEntry<>::noLIM;
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli10) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("Y"));
    H.push_back(new dd::LimEntry<>("X"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("iZ");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = new dd::LimEntry<>("Y");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli11) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("XZ"));
    G.push_back(new dd::LimEntry<>("IZ"));
    H.push_back(new dd::LimEntry<>("XZ"));
    H.push_back(new dd::LimEntry<>("XY"));
    dd::LimEntry<>* a         = new dd::LimEntry<>("II");
    dd::LimEntry<>* x         = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected1 = new dd::LimEntry<>("II");
    dd::LimEntry<>* expected2 = new dd::LimEntry<>("XZ");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected1) || dd::LimEntry<>::Equal(x, expected2));
}

TEST(LimTest, CosetElementPauli12) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("XZ"));
    G.push_back(new dd::LimEntry<>("IZ"));
    H.push_back(new dd::LimEntry<>("ZI"));
    H.push_back(new dd::LimEntry<>("IX"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("YX");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = dd::LimEntry<>::noLIM;
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
}

TEST(LimTest, CosetElementPauli13) {
    dd::StabilizerGroup G, H;
    G.push_back(new dd::LimEntry<>("Z"));
    H.push_back(new dd::LimEntry<>("-Z"));
    dd::LimEntry<>* a        = new dd::LimEntry<>("-I");
    dd::LimEntry<>* x        = dd::Pauli::getCosetIntersectionElementPauli(G, H, a);
    dd::LimEntry<>* expected = new dd::LimEntry<>("Z");
    EXPECT_TRUE(dd::LimEntry<>::Equal(x, expected));
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
    dd::LimEntry<>      zzi{"ZZI"};
    dd::LimEntry<>      zzi2{"ZZI"};
    dd::LimEntry<>      ziz{"ZIZ"};
    dd::LimEntry<>      izz{"IZZ"};
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
    dd::LimEntry<>      zzi{"ZZI"};
    dd::LimEntry<>      zzi2{"ZZI"};
    dd::LimEntry<>      ziz{"ZIZ"};
    dd::LimEntry<>      izz{"IZZ"};
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
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(G, expectedGroup));
}

TEST(LimTest, columnEchelonForm2) {
    dd::StabilizerGroup G;
    G.push_back(new dd::LimEntry<>("ZI"));
    G.push_back(new dd::LimEntry<>("IZ"));
    G.push_back(new dd::LimEntry<>("ZI"));
    G.push_back(new dd::LimEntry<>("IZ"));
    dd::Pauli::toColumnEchelonForm(G);
    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZI"));
    expectedGroup.push_back(new dd::LimEntry<>("IZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(G, expectedGroup));
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

    e = dd->normalizeLIMDDPauli(e, false);

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
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode1.\n";
    std::cout.flush();

    // Create |+>
    dd::Edge<dd::vNode> e1{dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e1.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};

    // Create another |+>
    dd::Edge<dd::vNode> e2{dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e2.p->e = {dd::Package::vEdge::one, dd::Package::vEdge::one};

    dd::Edge<dd::vNode> e3{dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e3.p->e = {e1, e2};

    e3 = dd->normalizeLIMDDPauli(e3, false);

    // Assert: identity label on low edge
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e3.p->e[0].l));
    // Assert: identity label on high edge
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e3.p->e[1].l));
}

TEST(LimTest, CreateNode2) {
    auto dd = std::make_unique<dd::Package>(1, dd::Pauli_group);
    std::cout << "Test CreateNode2.\n";

    // Create node |+>
    dd::vNode* plus = dd->vUniqueTable.getNode();
    plus->e         = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    plus->v         = 0;

    // Create edge I|+>
    dd::Edge<dd::vNode> e0 = {plus, dd::Complex::one, nullptr};
    std::cout << "[CreateNode2 test] before normalize, e0 is " << e0;
    e0 = dd->normalize(e0, false);
    std::cout << "[CreateNode2 test] e0 is " << e0;

    // Create edge Z|+>
    dd::LimEntry<>*     l  = new dd::LimEntry<>("Z");
    dd::Edge<dd::vNode> e1 = {plus, dd::Complex::one, l};
    e1                     = dd->normalize(e1, false);
    std::cout << "[CreateNode2 test] e1 is " << e1 << ".\n";

    // Create edge |0>|e0> + |1>|e1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e                = {e0, e1};
    e.p->v                = 1;
    std::cout << "[CreateNode2 test] weights: " << e.p->e[0].w << ", " << e.p->e[1].w << ".\n";
    // normalize the edge / node
    e = dd->normalizeLIMDDPauli(e, false);
    std::cout << "[CreateNode2 test] root label: (should be I): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::isIdentityOperator(e.l), true);
    std::cout << "[CreateNode2 test] high label: (should be Z):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::Equal(e.p->e[1].l, l), true);
}

TEST(LimTest, CreateNode2_simple) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode2.\n";

    dd::Edge<dd::vNode> e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    std::cout << "[CreateNode2 test] e0 is " << e0;

    dd::LimEntry<>*     z  = new dd::LimEntry<>("Z");
    dd::Edge<dd::vNode> e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, z);

    std::cout << "[CreateNode2 test] e1 is " << e1;

    // Create edge |0>|e0> + |1>|e1>
    dd::Edge<dd::vNode> e = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);
    std::cout << "[CreateNode2 test] e is " << e;
    // normalize the edge / node

    std::cout << "[CreateNode2 test] root label: (should be I): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::isIdentityOperator(e.l), true);
    std::cout << "[CreateNode2 test] high label: (should be Z):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::Equal(e.p->e[1].l, z), true);
}

TEST(LimTest, CreateNode3) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode3.\n";

    // Create node |+>
    dd::vNode* plus = dd->vUniqueTable.getNode();
    plus->e         = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    plus->v         = 0;

    // Create edge Z|+>
    dd::LimEntry<>*     l  = new dd::LimEntry<>("Z");
    dd::Edge<dd::vNode> e0 = {plus, dd::Complex::one, l};

    // Create edge I|+>
    dd::Edge<dd::vNode> e1 = {plus, dd::Complex::one, nullptr};

    // Create edge |0>|e0> + |1>|e1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e                = {e0, e1};
    // normalize the edge / node
    e = dd->normalizeLIMDDPauli(e, false);
    std::cout << "root label: (should be Z): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::Equal(e.l, l), true);
    std::cout << "high label: (should be Z):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::Equal(e.p->e[1].l, l), true);
}

TEST(LimTest, CreateNode4) {
    auto dd = std::make_unique<dd::Package>(1);
    std::cout << "Test CreateNode4.\n";

    dd::LimEntry<>* lim = new dd::LimEntry<>("Z");
    // Create node |0>
    dd::vNode* zeroState = dd->vUniqueTable.getNode();
    zeroState->e         = {dd::Package::vEdge::one, dd::Package::vEdge::zero};
    // Add Z to the stabilizer group of zeroState
    zeroState->limVector.push_back(lim);

    // Create node |+>
    dd::vNode* plus = dd->vUniqueTable.getNode();
    plus->e         = {dd::Package::vEdge::one, dd::Package::vEdge::one};
    plus->v         = 0;

    // Create edge I|0>
    dd::Edge<dd::vNode> e0 = {zeroState, dd::Complex::one, nullptr};

    // Create edge Z|+>
    dd::Edge<dd::vNode> e1 = {plus, dd::Complex::one, lim};

    // Create edge |0>|e0> + |1>|e1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e                = {e0, e1};
    // normalize the edge / node
    e = dd->normalizeLIMDDPauli(e, false);
    std::cout << "root label: (should be Z): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::Equal(e.l, lim), true);
    std::cout << "high label: (should be I):  " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::isIdentityOperator(e.p->e[1].l), true);
}

TEST(LimTest, CreateNode6) {
    auto dd = std::make_unique<dd::Package>(2);
    std::cout << "Test CreateNode6.\n";

    // Create node |0>
    dd::vNode* zeroState = dd->vUniqueTable.getNode();
    zeroState->e         = {dd::Package::vEdge::one, dd::Package::vEdge::zero};
    // Add stabilizer Z
    dd::LimEntry<>* limZ = new dd::LimEntry<>("Z");
    zeroState->limVector.push_back(limZ);

    // Create node |0>|0>
    dd::vNode*          zeroZero = dd->vUniqueTable.getNode();
    dd::Edge<dd::vNode> e0       = {zeroState, dd::Complex::one, nullptr};
    zeroZero->e                  = {e0, dd::Package::vEdge::zero};
    // Add stabilizers ZI and IZ
    dd::LimEntry<>* limIZ = new dd::LimEntry<>("IZ");
    zeroZero->limVector.push_back(limZ);
    zeroZero->limVector.push_back(limIZ);

    // Create edge I |0>|0>
    dd::Edge<dd::vNode> zeroZeroEdge = {zeroZero, dd::Complex::one, nullptr};

    // Create edge ZZ |0>|0>
    dd::LimEntry<>*     limZZ         = new dd::LimEntry<>("ZZ");
    dd::Edge<dd::vNode> zeroZeroZEdge = {zeroZero, dd::Complex::one, limZZ};

    // Create node |0>|zeroZeroEdge> + |1>|zeroZeroZEdge>
    dd::vNode* v = dd->vUniqueTable.getNode();
    v->e         = {zeroZeroEdge, zeroZeroZEdge};

    // Create edge to v
    dd::Edge<dd::vNode> e = {v, dd::Complex::one, nullptr};

    // normalize the edge / node
    e = dd->normalizeLIMDDPauli(e, false);
    std::cout << "root label:                " << dd::LimEntry<>::to_string(e.l) << '\n';
    std::cout << "high label: (should be I): " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e.p->e[1].l));
}

TEST(LimTest, CreateNode7) {
    auto dd = std::make_unique<dd::Package>(2);
    std::cout << "Test CreateNode7\n";

    // Create edge I|0>
    dd::Edge<dd::vNode> zero = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zero.p->e                = {dd::Package::vEdge::one, dd::Package::vEdge::zero};
    // Construct stabilizer group of |0>
    zero.p->limVector.push_back(new dd::LimEntry<>("Z"));

    // Create edge II |0>|0>
    dd::Edge<dd::vNode> zeroZero0 = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zeroZero0.p->e                = {zero, dd::Package::vEdge::zero};
    // Construct stabilizer group
    zeroZero0.p->limVector.push_back(new dd::LimEntry<>("ZI"));
    zeroZero0.p->limVector.push_back(new dd::LimEntry<>("IZ"));
    // Create a second edge II |0>|0>
    dd::Edge<dd::vNode> zeroZero1 = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zeroZero1.p->e                = {zero, dd::Package::vEdge::zero};
    zeroZero1.p->limVector.push_back(new dd::LimEntry<>("ZI"));
    zeroZero1.p->limVector.push_back(new dd::LimEntry<>("IZ"));

    // Create edge I|0>|zeroZero0> + |0>|zeroZero1>
    dd::Edge<dd::vNode> e = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    e.p->e                = {zeroZero0, zeroZero1};
    e                     = dd->normalizeLIMDDPauli(e, false);

    std::cout << "root label: (should be I): " << dd::LimEntry<>::to_string(e.l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::isIdentityOperator(e.l), true);
    std::cout << "high label: (should be I): " << dd::LimEntry<>::to_string(e.p->e[1].l) << '\n';
    EXPECT_EQ(dd::LimEntry<>::isIdentityOperator(e.p->e[1].l), true);
}

TEST(LimTest, CreateNode8) {
    auto dd = std::make_unique<dd::Package>(2);
    std::cout << "Test CreateNode7\n";

    // Create edge I|0>
    dd::Edge<dd::vNode> zero = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zero.p->e                = {dd::Package::vEdge::one, dd::Package::vEdge::zero};
    // Construct stabilizer group of |0>
    zero.p->limVector.push_back(new dd::LimEntry<>("Z"));

    // Create edge II |0>|0>
    dd::Edge<dd::vNode> zeroZero = {dd->vUniqueTable.getNode(), dd::Complex::one, nullptr};
    zeroZero.p->e                = {zero, dd::Package::vEdge::zero};
    // Construct stabilizer group
    zeroZero.p->limVector.push_back(new dd::LimEntry<>("ZI"));
    zeroZero.p->limVector.push_back(new dd::LimEntry<>("IZ"));

    // Create edge ZI |1>|0>
    dd::Edge<dd::vNode> oneZero = {dd->vUniqueTable.getNode(), dd::Complex::one, new dd::LimEntry<>("IZ")};
    oneZero.p->e                = {dd::Package::vEdge::zero, zero};
    // Construct stabilizer group
    oneZero.p->limVector.push_back(new dd::LimEntry<>("ZI"));
    oneZero.p->limVector.push_back(new dd::LimEntry<>("-IZ"));
    // todo finish this test
}

TEST(LimTest, CreateNode9) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode9 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|->
    dd::Edge<dd::vNode> minusOne = dd::Package::vEdge::one;
    minusOne.w                   = dd::Complex::minusOne();
    dd::Edge<dd::vNode> e1       = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, minusOne}, false, nullptr);
    //  set the weight of this edge to -1
    e1.w = dd::Complex::minusOne();
    std::cout << "[CreateNode9 test] Root node of state |-> (Z expected): " << (*e1.l) << "\n";

    // make e2 = |0>|e0> + |1>|e1> = |0+> - |1->
    std::cout << "[CreateNode9 test] making edge |0>|+> - |1>|-> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode9 test] root label (IZ expected): " << *(e2.l) << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("IZ");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode9 test] high label  (Z expected): " << *(e2.p->e[1].l) << "\n";
    dd::LimEntry<>* expectedHighLabel = new dd::LimEntry<>("Z");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.p->e[1].l, expectedHighLabel));
}

TEST(LimTest, CreateNode10) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge e1 = -|+>, and set this phase in the LIM incoming to the edge
    dd::LimEntry<>* lim = dd::LimEntry<>::getIdentityOperator();
    lim->setPhase(dd::phase_t::phase_minus_one);
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, lim);

    std::cout << "[CreateNode10 test] amplitude of edge: " << e1.w.toString() << std::endl;
    std::cout << "[CreateNode10 test] amplitude low: " << e1.p->e[0].w << " amplitude high: " << e1.p->e[1].w << std::endl;
    //    EXPECT_EQ(e1.w, dd::Complex::minusOne());
    // TODO I wish to check whether the weight on the incoming edge is appropriate, without imposing or assuming a specific weight normalization scheme. How do I do that?
    EXPECT_EQ(dd::LimEntry<>::getPhase(e1.l), dd::phase_t::phase_one);
}

TEST(LimTest, CreateNode11) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode11 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -i|+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the weight of this edge to -i
    e1.w = {&dd::ComplexTable<>::zero, dd::ComplexTable<>::Entry::flipPointerSign(&dd::ComplexTable<>::one)};
    e0.w = dd::Complex::one;

    // make e2 = |0>|e0> + |1>|e1> = |0+> -i|1+>
    std::cout << "[CreateNode11 test] making edge |0>|+> -i |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode11 test] root label (IZ expected): " << *(e2.l) << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("IZ");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode11 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
    // TODO I expect that the high edge weight is 1
}

TEST(LimTest, CreateNode12) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode12 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the phase of this edge to i
    e1.w = {&dd::ComplexTable<>::zero, &dd::ComplexTable<>::one};

    // make e2 = |0>|e0> + |1>|e1>
    std::cout << "[CreateNode12 test] making edge |0>|+> - |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode12 test] root label (II expected): " << *(e2.l) << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("II");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode12 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
    // todo I expect that the root node has weight 1, and the high edge has weight i
}

TEST(LimTest, CreateNode13) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode13 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the weight of edge e0 to i and the weight of edge e1 to +1
    e0.w = {&dd::ComplexTable<>::zero, &dd::ComplexTable<>::one};
    e1.w = dd::Complex::one;

    // make e2 = i|0>|e0> + |1>|e1>
    std::cout << "[CreateNode13 test] making edge |0>|+> - |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode13 test] root label (IZ expected): " << *(e2.l) << "\n";
    std::cout << "[CreateNode13 test] root weight: (i expected):" << e2.w << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("IZ");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode13 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    std::cout << "[CreateNode13 test] high weight (i expected): " << e2.p->e[1].w << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
    // TODO I expect that the root has phase i, and the high edge has weight i
}

TEST(LimTest, CreateNode14) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = -i|+>
    std::cout << "[CreateNode14 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = |+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the phase of e0 to -i, and of e1 to +1
    e0.w = {&dd::ComplexTable<>::zero, dd::ComplexTable<>::Entry::flipPointerSign(&dd::ComplexTable<>::one)};
    e1.w = dd::Complex::one;

    // make e2 = |0>|e0> + |1>|e1>
    std::cout << "[CreateNode14 test] making edge -i|0>|+> + |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode14 test] root label (II expected): " << *(e2.l) << "\n";
    std::cout << "[CreateNode14 test] root weight: (-i expected):" << e2.w << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("II");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode14 test] high label  (I expected):  " << *(e2.p->e[1].l) << "\n";
    std::cout << "[CreateNode14 test] high weight (i expected): " << e2.p->e[1].w << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
}

TEST(LimTest, CreateNode15) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode15 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the weight of e0 to 1+i and the weight of e1 to +1
    e0.w = {&dd::ComplexTable<>::one, &dd::ComplexTable<>::one};
    e1.w = dd::Complex::one;

    // make e2 = |0>|e0> + |1>|e1>
    std::cout << "[CreateNode15 test] making edge |0>|+> - |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode15 test] root label (IZ expected):   " << *(e2.l) << "\n";
    std::cout << "[CreateNode15 test] root weight: (1+i expected):" << e2.w << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("II");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode15 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    std::cout << "[CreateNode15 test] high weight (1/(1+i) expected): " << e2.p->e[1].w << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
}

TEST(LimTest, CreateNode16) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode16 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the weight of edge e0 to -1 and the weight of e1 to -i
    e0.w = dd::Complex::minusOne();
    e1.w = {&dd::ComplexTable<>::zero, dd::ComplexTable<>::Entry::flipPointerSign(&dd::ComplexTable<>::one)};

    // make e2 = |0>|e0> + |1>|e1>
    std::cout << "[CreateNode16 test] making edge |0>|+> - |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode16 test] root label (II expected): " << *(e2.l) << "\n";
    std::cout << "[CreateNode16 test] root weight: (-1 expected):" << e2.w << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("II");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode16 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    std::cout << "[CreateNode16 test] high weight (i expected): " << e2.p->e[1].w << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
}

TEST(LimTest, CreateNode17) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode17 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the weight of edge e0 to -1 and the weight of e1 to i
    e0.w = dd::Complex::minusOne();
    e1.w = {&dd::ComplexTable<>::zero, &dd::ComplexTable<>::one};

    // make e2 = |0>|e0> + |1>|e1>
    std::cout << "[CreateNode17 test] making edge |0>|+> - |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode17 test] root label (II expected): " << *(e2.l) << "\n";
    std::cout << "[CreateNode17 test] root weight: (-1 expected):" << e2.w << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("IZ");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode17 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    std::cout << "[CreateNode17 test] high weight (i expected): " << e2.p->e[1].w << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
}

TEST(LimTest, CreateNode18) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[CreateNode18 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|+>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the weight of edge e0 to -1 and the weight of e1 to i
    e0.w = dd::Complex::minusOne();
    e1.w = dd::Complex::one;

    // make e2 = |0>|e0> + |1>|e1>
    std::cout << "[CreateNode18 test] making edge |0>|+> - |1>|+> by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[CreateNode18 test] root label (IZ expected): " << *(e2.l) << "\n";
    std::cout << "[CreateNode18 test] root weight: (-1 expected):" << e2.w << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("IZ");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[CreateNode18 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    std::cout << "[CreateNode18 test] high weight (1 expected): " << e2.p->e[1].w << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
}

TEST(LimTest, CreateNode19) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge e0 = |+>
    std::cout << "[CreateNode19 test] making edge |-> by calling MakeDDNode.\n";
    dd::Edge<dd::vNode> minusOne = {dd::vNode::terminal, dd::Complex::minus_one, nullptr};
    dd::Edge<dd::vNode> minus    = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, minusOne}, false, nullptr);

    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("Z");
    EXPECT_TRUE(dd::LimEntry<>::Equal(minus.l, expectedRootLabel));
}

TEST(LimTest, CreateNode20) {
    auto dd = std::make_unique<dd::Package>(1, dd::Pauli_group);
    std::cout << "[Test CreateNode20] start.\n";

    // Create node |+>
    dd::Edge<dd::vNode> plusEdge = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    std::cout << "[CreateNode20 test] plusEdge is " << plusEdge;

    EXPECT_TRUE(dd::ComplexTable<>::Entry::val(plusEdge.p->e[0].w.r) > 0);
    EXPECT_TRUE(dd::ComplexTable<>::Entry::val(plusEdge.p->e[1].w.r) > 0);
}

TEST(LimTest, constructStabilizerGroup2) {
    auto dd = std::make_unique<dd::Package>(1);

    auto l = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);
    std::cout << "Stabilizer group of |0>:\n";
    std::cout.flush();
    dd::Pauli::printStabilizerGroup(l.p->limVector);
    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("Z"));
    EXPECT_EQ(dd::Pauli::stabilizerGroupsEqual(l.p->limVector, expectedGroup), true);
}

TEST(LimTest, constructStabilizergroup3) {
    auto dd = std::make_unique<dd::Package>(1);

    auto l = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);
    std::cout << "Stabilizer group of |1>:\n";
    dd::Pauli::printStabilizerGroup(l.p->limVector);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-Z"));
    std::cout << "Expected group: \n";
    dd::Pauli::printStabilizerGroup(expectedGroup);

    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(l.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup4) {
    auto dd = std::make_unique<dd::Package>(1);

    dd::ComplexValue    twocn = dd::ComplexValue{2.0, 0.0};
    dd::Complex         twoc  = dd->cn.lookup(twocn);
    dd::Edge<dd::vNode> two   = {dd->vUniqueTable.getNode(), twoc, nullptr};
    two.p                     = dd::vNode::terminal;
    auto e                    = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, two}, false, nullptr);
    std::cout << "Stabilizer group of |0> + 2|1> :\n";
    dd::Pauli::printStabilizerGroup(e.p->limVector);

    dd::StabilizerGroup expectedGroup;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup5) {
    auto dd = std::make_unique<dd::Package>(2);

    // make e0 = |0>
    std::cout << "[constructStabilizerGroup5 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make e1 = |0>|0>
    std::cout << "[constructStabilizerGroup5 test] making edge |0>|0> by calling MakeDDNode.\n";
    auto e1 = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, nullptr);
    std::cout << "[constructStabilizergroup5 test]Stabilizer group of |0>|0>:\n";
    std::cout.flush();
    dd::Pauli::printStabilizerGroup(e1.p->limVector);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZI"));
    std::cout << "[constructStabilizergroup5 test] added ZI to expected group.\n";
    std::cout.flush();
    expectedGroup.push_back(new dd::LimEntry<>("IZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e1.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup6) {
    auto dd = std::make_unique<dd::Package>(2);

    // make e0 = |1>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make e1 = |0>|1>
    auto e1 = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, nullptr);
    std::cout << "[constructStabilizergroup6 test] Stabilizer group of |0>|1>:\n";
    dd::Pauli::printStabilizerGroup(e1.p->limVector);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-ZI"));
    expectedGroup.push_back(new dd::LimEntry<>("IZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e1.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup7) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    //make edge e1 = |1>|0>
    auto e1 = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, nullptr);
    std::cout << "[constructStabilizergroup7 test] Stabilizer group of |0>|1>:\n";
    dd::Pauli::printStabilizerGroup(e1.p->limVector);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZI"));
    expectedGroup.push_back(new dd::LimEntry<>("-IZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e1.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup8) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |1>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |1>|1>
    auto e1 = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, nullptr);
    std::cout << "[constructStabilizergroup7 test] Stabilizer group of |0>|1>:\n";
    dd::Pauli::printStabilizerGroup(e1.p->limVector);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-ZI"));
    expectedGroup.push_back(new dd::LimEntry<>("-IZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e1.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup9) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |1>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |00> + |11>
    std::cout << "[constructStabilizerGroup9] making node |00> + |11>\n";
    std::cout.flush();
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup10) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge 2|1>
    auto             e1    = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);
    dd::ComplexValue twocv = dd::ComplexValue{2.0, 0.0};
    dd::Complex      twoc  = dd->cn.lookup(twocv);
    e1.w                   = twoc;

    // make edge |00> + 2|11>
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup11) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |+>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge |0>|+>
    auto e1 = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("IZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e1.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup12) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |+>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge |1>|+>
    auto e1 = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e0}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-IZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e1.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup13) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |+>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge |1>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |0>|e0> + |1>|e1>
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expect trivial stabilizer group
    dd::StabilizerGroup expectedGroup;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup14) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |+>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge |0>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |0>|e0> + |1>|e1>
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expect trivial stabilizer group
    dd::StabilizerGroup expectedGroup;
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup15) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge |1>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |0>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |0>|e0> + |1>|e1>
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-ZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup16) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |00>
    auto e1 = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |000>
    auto e2 = dd->makeDDNode(2, std::array{e1, dd::Package::vEdge::zero}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZII"));
    expectedGroup.push_back(new dd::LimEntry<>("IZI"));
    expectedGroup.push_back(new dd::LimEntry<>("IIZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup17) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge |1>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |01>
    auto e1 = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |001>
    auto e2 = dd->makeDDNode(2, std::array{e1, dd::Package::vEdge::zero}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-ZII"));
    expectedGroup.push_back(new dd::LimEntry<>("IZI"));
    expectedGroup.push_back(new dd::LimEntry<>("IIZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup18) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge |1>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |01>
    auto e1 = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |101>
    auto e2 = dd->makeDDNode(2, std::array{dd::Package::vEdge::zero, e1}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-ZII"));
    expectedGroup.push_back(new dd::LimEntry<>("IZI"));
    expectedGroup.push_back(new dd::LimEntry<>("-IIZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e2.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup19) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |1>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |0>|e0> + |1>|e1>
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // make edge |0>|e2>
    auto e3 = dd->makeDDNode(2, std::array{e2, dd::Package::vEdge::zero}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZZI"));
    expectedGroup.push_back(new dd::LimEntry<>("IIZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e3.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup20) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge |1>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |0>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |0>|e0> + |1>|e1>
    auto e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // make edge |1>|e2>
    auto e3 = dd->makeDDNode(2, std::array{dd::Package::vEdge::zero, e2}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("-ZZI"));
    expectedGroup.push_back(new dd::LimEntry<>("-IIZ"));
    std::cout << "[construct stabilizer group test 22] Found stabilizer group:\n";
    dd::Pauli::printStabilizerGroup(e3.p->limVector);
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e3.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup21) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge |0>
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge |1>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);

    // make edge |0>|e0> + 2|1>|e1>
    auto             e2    = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);
    dd::ComplexValue twocv = dd::ComplexValue{2.0, 0.0};
    dd::Complex      twoc  = dd->cn.lookup(twocv);
    e1.w                   = twoc;

    // make edge |0>|e2>
    auto e3 = dd->makeDDNode(2, std::array{e2, dd::Package::vEdge::zero}, false, nullptr);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZZI"));
    expectedGroup.push_back(new dd::LimEntry<>("IIZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e3.p->limVector, expectedGroup));
}

TEST(LimTest, constructStabilizerGroup22) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge |0>
    std::cout << "[construct stabilizer group test 22] making edge |0>.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);
    std::cout << "[construct stabilizer group test 22] stabilizer group of |0>:\n";
    dd::Pauli::printStabilizerGroup(e0.p->limVector);

    // make edge |1>
    std::cout << "[construct stabilizer group test 22] making edge |1>.\n";
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);
    std::cout << "[construct stabilizer group test 22] stabilizer group of |1>:\n";
    dd::Pauli::printStabilizerGroup(e1.p->limVector);

    // make edge |00>
    std::cout << "[construct stabilizer group test 22] making edge |00>.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, dd::Package::vEdge::zero}, false, nullptr);
    std::cout << "[construct stabilizer group test 22] stabilizer group of |00>:\n";
    dd::Pauli::printStabilizerGroup(e2.p->limVector);

    // make edge |11>
    std::cout << "[construct stabilizer group test 22] making edge |11>.\n";
    auto e3 = dd->makeDDNode(1, std::array{dd::Package::vEdge::zero, e1}, false, nullptr);
    std::cout << "[construct stabilizer group test 22] stabilizer group of |11>:\n";
    dd::Pauli::printStabilizerGroup(e3.p->limVector);

    // make edge |0>|e2> + |1>|e3>>
    std::cout << "[construct stabilizer group test 22] making edge |000> + |111>.\n";
    auto e4 = dd->makeDDNode(2, std::array{e2, e3}, false, nullptr);
    std::cout << "[construct stabilizer group test 22] stabilizer group of |000> + |111>:\n";
    dd::Pauli::printStabilizerGroup(e4.p->limVector);

    dd::StabilizerGroup expectedGroup;
    expectedGroup.push_back(new dd::LimEntry<>("ZIZ"));
    expectedGroup.push_back(new dd::LimEntry<>("IZZ"));
    EXPECT_TRUE(dd::Pauli::stabilizerGroupsEqual(e4.p->limVector, expectedGroup));
}

TEST(LimTest, nextTest) {
    auto dd = std::make_unique<dd::Package>(2);

    auto state0 = dd->makeZeroState(2);

    auto state1 = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 0), state0);
    //auto state2 = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 1), state1);
    auto state3 = dd->multiply(dd->makeGateDD(dd::Zmat, 2, 0), state1);
    dd::export2Dot(state3, "state3.dot", false, true, true, false, true, false);
    auto str = dd::LimEntry<>::to_string(state3.l);
    std::cout << "resulting LIM with Z:" << str << '\n';
    auto state3_vec = dd->getVectorLIMDD(state3);
    for (const auto& i: state3_vec) {
        std::cout << "  " << i << "\n";
    }

    auto state4 = dd->multiply(dd->makeGateDD(dd::Zmat, 2, 0), state3);
    dd::export2Dot(state3, "state4.dot", false, true, true, false, true, false);

    str = dd::LimEntry<>::to_string(state4.l);
    std::cout << "resulting LIM with Z^2:" << str << '\n';
    auto state4_vec = dd->getVectorLIMDD(state4);
    for (const auto& i: state4_vec) {
        std::cout << "  " << i << "\n";
    }

    EXPECT_FALSE(dd->vectorsApproximatelyEqual(state4_vec, state3_vec));
}

TEST(LimTest, simpleMultiplicationBellState) {
    auto dd = std::make_unique<dd::Package>(2);

    auto h_gate     = dd->makeGateDD(dd::Hmat, 2, 1);
    auto cx_gate    = dd->makeGateDD(dd::Xmat, 2, 1_pc, 0);
    auto zero_state = dd->makeZeroState(2);

    auto bell_state = dd->multiply(dd->multiply(cx_gate, h_gate), zero_state);

    auto result = dd->getVector(bell_state);
    dd->printVector(bell_state);

    EXPECT_TRUE(abs(result[0].real() - 0.707) < 0.001 && abs(result[0].imag()) < 0.001);
    EXPECT_TRUE(abs(result[1].real()) < 0.001 && abs(result[1].imag()) < 0.001);
    EXPECT_TRUE(abs(result[2].real()) < 0.001 && abs(result[2].imag()) < 0.001);
    EXPECT_TRUE(abs(result[3].real() - 0.707) < 0.001 && abs(result[3].imag()) < 0.001);
}

TEST(LimTest, highLabelPauli1) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |+>
    std::cout << "[highLabelPauli1 test] making edge |0> by calling MakeDDNode.\n";
    dd::Edge<dd::vNode> e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e1 = -|+>
    dd::Edge<dd::vNode> e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //  set the weight of e0 to 1+i and the weight of e1 to +1
    e0.w = {&dd::ComplexTable<>::one, &dd::ComplexTable<>::one};
    e1.w = dd::Complex::one;

    // make e2 = |0>|e0> + |1>|e1>
    std::cout << "[highLabelPauli1 test] making edge |0>|+> - |1>|+> by calling MakeDDNode.\n";
    dd::Edge<dd::vNode> e2 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    // Expected: root label is IZ
    std::cout << "[highLabelPauli1 test] root label (IZ expected):   " << *(e2.l) << "\n";
    std::cout << "[highLabelPauli1 test] root weight: (1+i expected):" << e2.w << "\n";
    dd::LimEntry<>* expectedRootLabel = new dd::LimEntry<>("I");
    EXPECT_TRUE(dd::LimEntry<>::Equal(e2.l, expectedRootLabel));
    // Expected: high label Identity
    std::cout << "[highLabelPauli1 test] high label  (I expected): " << *(e2.p->e[1].l) << "\n";
    std::cout << "[highLabelPauli1 test] high weight (1/(1+i) expected): " << e2.p->e[1].w << "\n";
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e2.p->e[1].l));
}

TEST(LimTest, highLabelPauli2) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |0>
    std::cout << "[highLabelPauli2 test] making edge |0> by calling MakeDDNode.\n";
    dd::Edge<dd::vNode> e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e0.p->e[0].l));
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e0.p->e[1].l));
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e0.l));
}

TEST(LimTest, highLabelPauli3) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |0>
    std::cout << "[highLabelPauli3 test] making edge |1> by calling MakeDDNode.\n";
    dd::Edge<dd::vNode> e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);
    dd::LimEntry<> expectedRootLabel("X");

    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e0.p->e[0].l));
    EXPECT_TRUE(dd::LimEntry<>::isIdentityOperator(e0.p->e[1].l));
    EXPECT_TRUE(dd::LimEntry<>::Equal(e0.l, &expectedRootLabel));
}

TEST(LimTest, getIsomorphismPauli1) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge e0 = |0>
    std::cout << "[getIsomorphismPauli1 test] making edge |0> by calling MakeDDNode.\n";
    dd::Edge<dd::vNode> e0 = dd->makeDDNodeNonNormalized(std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero});
    //    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge e1 = |1>
    //    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);
    dd::Edge<dd::vNode> e1 = dd->makeDDNodeNonNormalized(std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one});

    dd::LimWeight<>* isomorphism         = dd::Pauli::getIsomorphismPauli(e0.p, e1.p, dd->cn);
    dd::LimWeight<>* expectedIsomorphism = new dd::LimWeight<>("X");
    std::cout << "Found isomorphism: " << dd::LimWeight<>::to_string(isomorphism) << std::endl;
    EXPECT_TRUE(dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, getIsomorphismPauli2) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge e0 = |0>
    std::cout << "[getIsomorpismPauli2 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge e1 = |+> = |0> + |1>
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    dd::LimWeight<>* isomorphism = dd::Pauli::getIsomorphismPauli(e0.p, e1.p, dd->cn);
    std::cout << "[getIsomorphismPauli2 test] Done finding isomorphism.\n";
    std::cout.flush();
    dd::LimWeight<>* expectedIsomorphism = dd::LimWeight<>::noLIM;

    std::cout << "Found isomorphism: " << dd::LimWeight<>::to_string(isomorphism) << std::endl;
    EXPECT_TRUE(dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, getIsomorphismPauli3) {
    auto dd = std::make_unique<dd::Package>(1);

    // make edge e0 = |0>
    std::cout << "[getIsomorpismPauli3 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNodeNonNormalized(std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one});

    // make edge e1 = |+> = |0> + |1>
    auto e1 = dd->makeDDNodeNonNormalized(std::array{dd::Package::vEdge::one, dd::Package::vEdge::one});

    dd::LimWeight<>* isomorphism         = dd::Pauli::getIsomorphismPauli(e0.p, e1.p, dd->cn);
    dd::LimWeight<>* expectedIsomorphism = dd::LimWeight<>::noLIM;
    std::cout << "Found isomorphism: " << dd::LimWeight<>::to_string(isomorphism) << std::endl;
    EXPECT_TRUE(dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, getIsomorphismPauli4) {
    //    auto dd = std::make_unique<dd::Package>(1);
    //
    //    // make edge e0 = |0>
    //    std::cout << "[getIsomorpismPauli4 test] making edge |0> by calling MakeDDNode.\n";
    //    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);
    //
    //    // make edge e1 = |+> = |0> + |1>
    //    std::cout << "[getIsomorpismPauli4 test] making edge |+> by calling MakeDDNode.\n";
    //    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //
    //    // make edge e00 = |00> + |1+>
    //    std::cout << "[getIsomorpismPauli4 test] making edge |00> + |1+> by calling MakeDDNode.\n";
    //    dd::Edge<dd::vNode> e2 = dd->makeDDNodeNonNormalized(std::array{e0, e1});
    //
    //    // make edge e11 = |0+> + |10> = |0>|e1> + |1>|e0>
    //    std::cout << "[getIsomorpismPauli4 test] making edge |0+> + |10> by calling MakeDDNode.\n";
    //    dd::Edge<dd::vNode> e3 = dd->makeDDNodeNonNormalized(std::array{e1, e0});
    ////    auto e3 = dd->makeDDNode(1, std::array{e1, e0}, false, nullptr);
    //
    //    std::cout << "[getIsomorpismPauli4 test] Seeing whether |e2> ~~ |e3>.\n";
    //    dd::LimEntry<>* isomorphism = dd::Pauli::getIsomorphismPauli(e2.p, e3.p);
    //    dd::LimEntry<>* expectedIsomorphism = new dd::LimEntry<>("XI");
    //    std::cout << "Found isomorphism: " << dd::LimEntry<>::to_string(isomorphism) << std::endl;
    //    EXPECT_TRUE(dd::LimEntry<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, getIsomorphismPauli5) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |0>
    std::cout << "[getIsomorpismPauli5 test] making edge |0> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    // make edge e00 = |00> - |11>
    dd::Edge<dd::vNode> e2 = dd->makeDDNodeNonNormalized(std::array{e0, e0});
    e2.p->e[1].l           = new dd::LimEntry<>("X");
    e2.p->e[1].w           = dd::Complex::minus_one;

    // make edge e11 = |00> + |11>
    dd::Edge<dd::vNode> e3 = dd->makeDDNodeNonNormalized(std::array{e0, e0});
    e3.p->e[1].l           = new dd::LimEntry<>("X");
    e3.p->e[1].w           = dd::Complex::one;

    std::cout << "[getIsomorpismPauli5 test] Made all edges; now finding isomorphism between |00>-|11> vs |00>+|11>.\n";
    dd::LimWeight<>* isomorphism          = dd::Pauli::getIsomorphismPauli(e2.p, e3.p, dd->cn);
    dd::LimWeight<>* expectedIsomorphism1 = new dd::LimWeight<>("IZ");
    dd::LimWeight<>* expectedIsomorphism2 = new dd::LimWeight<>("ZI");
    std::cout << "Found isomorphism: " << dd::LimWeight<>::to_string(isomorphism) << std::endl;
    EXPECT_TRUE(dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism1) || dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism2));
}

TEST(LimTest, getIsomorphismPauli6) {
}

TEST(LimTest, getIsomorphismPauli7) {
    auto dd = std::make_unique<dd::Package>(2);

    // make edge e0 = |0>
    std::cout << "[getIsomorpismPauli7 test] making edge |0> by calling MakeDDNode.\n";
    dd::Edge<dd::vNode> e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::zero}, false, nullptr);

    dd::Edge<dd::vNode> e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::zero, dd::Package::vEdge::one}, false, nullptr);
    e1.w                   = dd::Complex::minusOne();

    // make edge e00 = |00> - |11>
    dd::Edge<dd::vNode> e2 = dd->makeDDNodeNonNormalized(std::array{e0, e1});

    // make edge e11 = |10> + |11>
    dd::Edge<dd::vNode> e3 = dd->makeDDNodeNonNormalized(std::array{e0, e0});

    dd::LimWeight<>* isomorphism         = dd::Pauli::getIsomorphismPauli(e2.p, e3.p, dd->cn);
    dd::LimWeight<>* expectedIsomorphism = dd::LimWeight<>::noLIM;
    std::cout << "Found isomorphism: " << dd::LimWeight<>::to_string(isomorphism) << std::endl;
    EXPECT_TRUE(dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, getIsomorphismPauli8) {
    //    auto dd = std::make_unique<dd::Package>(2);
    //
    //    // make edge e0 = |+>
    //    std::cout << "[getIsomorpismPauli5 test] making edge |0> by calling MakeDDNode.\n";
    //    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    //
    //    // make edge e2 = |0>|e0> + |1>Z|e2>
    //    dd::Edge<dd::vNode> e2 = dd->makeDDNodeNonNormalized(std::array{e0, e0});
    //    e2.p->e[1].l = new dd::LimEntry<>("-X");
    //
    //    // make edge e3 = |0>|e2> + |1>
    //    dd::Edge<dd::vNode> e3 = dd->makeDDNodeNonNormalized(std::array{e0, e0});
    //    e3.p->e[1].l = nullptr;
    //
    //    dd::LimEntry<>* isomorphism = dd::Pauli::getIsomorphismPauli(e2.p, e3.p);
    //    dd::LimEntry<>* expectedIsomorphism = dd::LimEntry<>::noLIM;
    //    std::cout << "Found isomorphism: " << dd::LimEntry<>::to_string(isomorphism) << std::endl;
    //    EXPECT_TRUE(dd::LimEntry<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, rootLabel1) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge e5 = Z|+>
    std::cout << "[rootLabel1 test] making edge Z|+> by calling MakeDDNode.\n";
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, new dd::LimEntry<>("Z"));

    ASSERT_EQ(*e1.l, dd::LimEntry<>("Z"));
}

TEST(LimTest, distinctNodes1) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge e0 = |+>
    std::cout << "[distinctNodes1 test] making edge |+> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e5 = Z|+>
    std::cout << "[distinctNodes1 test] making edge Z|+> by calling MakeDDNode.\n";
    auto e1 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, new dd::LimEntry<>("Z"));

    // make edge e1 = |++>
    std::cout << "[distinctNodes1 test] making edge |+>*(" << e0.p << ") by calling MakeDDNode.\n";
    auto e2 = dd->makeDDNode(1, std::array{e0, e0}, false, nullptr);

    // make edge e2 = |0+> + |1>Z|+>
    std::cout << "[distinctNodes1 test] making edge |0>|+> (" << e0.p << ")  +  |1>Z|+> (" << e1.p << ") by calling MakeDDNode.\n";
    auto e3 = dd->makeDDNode(1, std::array{e0, e1}, false, nullptr);

    std::cout << "[distinctNodes1 test] e2: " << e2.p << " e2: " << e3.p << " Same = " << (e2.p == e3.p) << std::endl;
    ASSERT_NE(e2.p, e3.p);
}

TEST(LimTest, getIsomorphismPauli9) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge e0 = |+>
    std::cout << "[getIsomorpismPauli9 test] making edge |+> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e0Z = Z|+> = |->
    auto e0Z = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    e0Z.l    = new dd::LimEntry<>("Z");

    // make edge e1 = |++>
    auto e1 = dd->makeDDNode(1, std::array{e0, e0}, false, nullptr);

    // make edge e2 = |0+> + |1>Z|+>
    auto e2 = dd->makeDDNode(1, std::array{e0, e0Z}, false, nullptr);

    // make edge e3 = |0>|e2> + |1>|e3>
    auto e3 = dd->makeDDNodeNonNormalized(std::array{e1, e2});

    // make edge e4 = |0>|e3> + |1>|e2>
    auto e4 = dd->makeDDNodeNonNormalized(std::array{e2, e1});

    std::cout << "edge 1: " << e1;
    std::cout << "edge 2: " << e2;
    std::cout << "edge 3: " << e3;
    std::cout << "edge 4: " << e4;

    std::cout << "[getIsomorphismPauli9 test] Testing children of e3 and e4.\n";
    EXPECT_EQ(e3.p->e[0].p, e4.p->e[1].p);
    EXPECT_EQ(e3.p->e[1].p, e4.p->e[0].p);
    std::cout << "[getIsomorphismPauli9 test] Low label of e3: " << dd::LimEntry<>::to_string(e3.p->e[0].l) << " low label of e4: " << dd::LimEntry<>::to_string(e4.p->e[0].l) << std::endl;

    dd::LimWeight<>* isomorphism         = dd::Pauli::getIsomorphismPauli(e3.p, e4.p, dd->cn);
    dd::LimWeight<>* expectedIsomorphism = new dd::LimWeight<>("IIX");
    std::cout << "Found isomorphism: " << dd::LimWeight<>::to_string(isomorphism) << std::endl;
    EXPECT_TRUE(dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, getIsomorphismPauli10) {
    auto dd = std::make_unique<dd::Package>(3);

    // make edge e0 = |+>
    std::cout << "[getIsomorpismPauli10 test] making edge |+> by calling MakeDDNode.\n";
    auto e0 = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);

    // make edge e0Z = Z|+> = |->
    auto e0Z = dd->makeDDNode(0, std::array{dd::Package::vEdge::one, dd::Package::vEdge::one}, false, nullptr);
    e0Z.l    = new dd::LimEntry<>("Z");

    // make edge e1 = |++>
    dd::Edge<dd::vNode> e1 = dd->makeDDNode(1, std::array{e0, e0}, false, nullptr);

    // make edge e2 = |0+> + |1>Z|+>
    dd::Edge<dd::vNode> e2 = dd->makeDDNode(1, std::array{e0, e0Z}, false, nullptr);

    // make edge e3 = |0>|e1> + |1>|e2>
    dd::Edge<dd::vNode> e3 = dd->makeDDNodeNonNormalized(std::array{e1, e2});

    // make edge e4 = |0>|e1> + |1>|e1>
    dd::Edge<dd::vNode> e4 = dd->makeDDNodeNonNormalized(std::array{e2, e1});

    dd::LimWeight<>* isomorphism         = dd::Pauli::getIsomorphismPauli(e3.p, e4.p, dd->cn);
    dd::LimWeight<>* expectedIsomorphism = new dd::LimWeight<>("IIX");
    std::cout << "Found isomorphism: " << dd::LimWeight<>::to_string(isomorphism) << std::endl;
    EXPECT_TRUE(dd::LimWeight<>::Equal(isomorphism, expectedIsomorphism));
}

TEST(LimTest, returnToCache1) {
    auto dd = std::make_unique<dd::Package>(2);

	dd::Complex z = dd->cn.getCached();
	dd->cn.returnToCache(z);
}

TEST(LimTest, simpleCliffordCircuit_1) {
    auto dd = std::make_unique<dd::Package>(2);

    auto state = dd->makeZeroState(2);

    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Zmat, 2, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Zmat, 2, 1), state);

    state = dd->multiply(dd->makeGateDD(dd::Zmat, 2, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Zmat, 2, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 0), state);

    auto result = dd->getVectorLIMDD(state);

    EXPECT_TRUE(abs(result[0].real() - 1) < 0.0001 && abs(result[0].imag()) < 0.001);
    EXPECT_TRUE(abs(result[1].real()) < 0.0001 && abs(result[1].imag()) < 0.001);
    EXPECT_TRUE(abs(result[2].real()) < 0.0001 && abs(result[2].imag()) < 0.001);
    EXPECT_TRUE(abs(result[3].real()) < 0.0001 && abs(result[3].imag()) < 0.001);
}

TEST(LimTest, simpleCliffordCircuit_2) {
    auto dd = std::make_unique<dd::Package>(2);

    auto state = dd->makeZeroState(2);

    state = dd->multiply(dd->makeGateDD(dd::Xmat, 2, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 1), state);

    auto result = dd->getVectorLIMDD(state);

    EXPECT_TRUE(abs(result[0].real() - 0.5) < 0.0001 && abs(result[0].imag()) < 0.001);
    EXPECT_TRUE(abs(result[1].real() - 0.5) < 0.0001 && abs(result[1].imag()) < 0.001);
    EXPECT_TRUE(abs(result[2].real() + 0.5) < 0.0001 && abs(result[2].imag()) < 0.001);
    EXPECT_TRUE(abs(result[3].real() + 0.5) < 0.0001 && abs(result[3].imag()) < 0.001);
}

TEST(LimTest, simpleCliffordCircuit_3) {
    auto dd = std::make_unique<dd::Package>(2);

    auto state = dd->makeZeroState(2);

    state = dd->multiply(dd->makeGateDD(dd::Xmat, 2, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Zmat, 2, 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Hmat, 2, 1), state);

    auto result = dd->getVectorLIMDD(state);

    EXPECT_TRUE(abs(result[0].real() - 1) < 0.0001 && abs(result[0].imag()) < 0.001);
    EXPECT_TRUE(abs(result[1].real()) < 0.0001 && abs(result[1].imag()) < 0.001);
    EXPECT_TRUE(abs(result[2].real()) < 0.0001 && abs(result[2].imag()) < 0.001);
    EXPECT_TRUE(abs(result[3].real()) < 0.0001 && abs(result[3].imag()) < 0.001);
}

TEST(LimTest, simpleCliffordCircuit_4) {
	auto qmdd = std::make_unique<dd::Package>(3, dd::QMDD_group);

	auto state = qmdd->makeZeroState(3);

	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 0), state);        // x q[0];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 1), state);        // x q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), state);  // cx q[2],q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 0_pc, 1), state);  // cx q[0],q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Hmat, 3, 2), state);        // h q[2];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Tmat, 3, 0), state);        // t q[0];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Tdagmat, 3, 1), state);     // tdg q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Tmat, 3, 2), state);        // t q[2];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), state);  // cx q[2],q[1]
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 0_pc, 2), state);  // cx q[0],q[2];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Tmat, 3, 1), state);        // t q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 0_pc, 1), state);  // cx q[0],q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Tdagmat, 3, 2), state);     // tdg q[2];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Tdagmat, 3, 1), state);     // tdg q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 0_pc, 2), state);  // cx q[0],q[2];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), state);  // cx q[2],q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Tmat, 3, 1), state);        // t q[1];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Hmat, 3, 2), state);        // h q[2];
	state = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), state);  // cx q[2],q[1];


	auto result_qmdd = qmdd->getVectorLIMDD(state);

	std::cout << "[simpleCliffordCircuit 4] QMDD result: " << result_qmdd << "\n";

	auto limdd = std::make_unique<dd::Package>(3, dd::Pauli_group);

	auto stateLIMDD = limdd->makeZeroState(3);

	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 0), stateLIMDD);        // x q[0];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 1), stateLIMDD);        // x q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), stateLIMDD);  // cx q[2],q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 0_pc, 1), stateLIMDD);  // cx q[0],q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Hmat, 3, 2), stateLIMDD);        // h q[2];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Tmat, 3, 0), stateLIMDD);        // t q[0];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Tdagmat, 3, 1), stateLIMDD);     // tdg q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Tmat, 3, 2), stateLIMDD);        // t q[2];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), stateLIMDD);  // cx q[2],q[1]
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 0_pc, 2), stateLIMDD);  // cx q[0],q[2];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Tmat, 3, 1), stateLIMDD);        // t q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 0_pc, 1), stateLIMDD);  // cx q[0],q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Tdagmat, 3, 2), stateLIMDD);     // tdg q[2];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Tdagmat, 3, 1), stateLIMDD);     // tdg q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 0_pc, 2), stateLIMDD);  // cx q[0],q[2];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), stateLIMDD);  // cx q[2],q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Tmat, 3, 1), stateLIMDD);        // t q[1];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Hmat, 3, 2), stateLIMDD);        // h q[2];
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 2_pc, 1), stateLIMDD);  // cx q[2],q[1];
	auto result_limdd = limdd->getVectorLIMDD(stateLIMDD);

	std::cout << "[simpleCliffordCircuit 4] LIMDD result: " << result_limdd << "\n";
	// assertions
	EXPECT_TRUE(qmdd->vectorsApproximatelyEqual(result_qmdd, result_limdd));
}

TEST(LimTest, simpleCliffordCircuit_5) {
	auto qmdd = std::make_unique<dd::Package>(3, dd::QMDD_group);

	auto stateQMDD = qmdd->makeZeroState(3);

	stateQMDD = qmdd->multiply(qmdd->makeGateDD(dd::Xmat, 3, 0), stateQMDD);        // x q[0];
	stateQMDD = qmdd->multiply(qmdd->makeGateDD(dd::Hmat, 3, 1), stateQMDD);        // x q[0];
	stateQMDD = qmdd->multiply(qmdd->makeGateDD(dd::Hmat, 3, 2), stateQMDD);        // x q[0];
	stateQMDD = qmdd->multiply(qmdd->makeGateDD(dd::Zmat, 3, 0_pc, 1), stateQMDD);        // x q[0];
//	stateQMDD = qmdd->multiply(qmdd->makeGateDD(dd::Zmat, 3, 0_pc, 2), stateQMDD);        // x q[0];
//	stateQMDD = qmdd->multiply(qmdd->makeGateDD(dd::Hmat, 3, 1), stateQMDD);        // x q[0];
//	stateQMDD = qmdd->multiply(qmdd->makeGateDD(dd::Hmat, 3, 2), stateQMDD);        // x q[0];

	auto resultQMDD = qmdd->getVector(stateQMDD);
	std::cout << "[simpleCliffordCircuit 5] QMDD result: " << resultQMDD << '\n';

	auto limdd = std::make_unique<dd::Package>(3, dd::Pauli_group);

	auto stateLIMDD = limdd->makeZeroState(3);

	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Xmat, 3, 0), stateLIMDD);        // x q[0];
	dd::export2Dot(stateLIMDD, "simpleCliffordCircuit_5_1");
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Hmat, 3, 1), stateLIMDD);        // x q[0];
	dd::export2Dot(stateLIMDD, "simpleCliffordCircuit_5_2");
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Hmat, 3, 2), stateLIMDD);        // x q[0];
	dd::export2Dot(stateLIMDD, "simpleCliffordCircuit_5_3");
	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Zmat, 3, 0_pc, 1), stateLIMDD);        // x q[0];
	dd::export2Dot(stateLIMDD, "simpleCliffordCircuit_5_4");
//	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Zmat, 3, 0_pc, 2), stateLIMDD);        // x q[0];
//	dd::export2Dot(stateLIMDD, "simpleCliffordCircuit_5_5");
//	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Hmat, 3, 1), stateLIMDD);        // x q[0];
//	dd::export2Dot(stateLIMDD, "simpleCliffordCircuit_5_6");
//	stateLIMDD = limdd->multiply(limdd->makeGateDD(dd::Hmat, 3, 2), stateLIMDD);        // x q[0];
//	dd::export2Dot(stateLIMDD, "simpleCliffordCircuit_5_7");

	auto resultLIMDD = limdd->getVectorLIMDD(stateLIMDD);

	std::cout << "[simpleCliffordCircuit 5] LIMDDresult: " << resultLIMDD << '\n';
	EXPECT_TRUE(qmdd->vectorsApproximatelyEqual(resultQMDD, resultLIMDD));
}

TEST(LimTest, simpleTCircuit) {
    auto dd = std::make_unique<dd::Package>(1);

    auto state = dd->makeZeroState(dd->qubits());

    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 0), state); // h q[0];
    state = dd->multiply(dd->makeGateDD(dd::Tmat, dd->qubits(), 0), state); // t q[0];
    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 0), state); // h q[0];

    auto   result    = dd->getVectorLIMDD(state);
    double tolerance = 1e-5;
    EXPECT_NEAR(result[0].real(), 0.853553, tolerance);
    EXPECT_NEAR(result[0].imag(), 0.353553, tolerance);
    EXPECT_NEAR(result[1].real(), 0.146447, tolerance);
    EXPECT_NEAR(result[1].imag(), -0.353553, tolerance);
}

TEST(LimTest, multiQubitTCircuit) {
    auto dd = std::make_unique<dd::Package>(3);

    auto state = dd->makeZeroState(dd->qubits());

    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 0), state); // h q[0];
    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 1), state); // h q[1];
    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 2), state); // h q[2];
    state = dd->multiply(dd->makeGateDD(dd::Tmat, dd->qubits(), 0), state); // t q[0];
    state = dd->multiply(dd->makeGateDD(dd::Tmat, dd->qubits(), 1), state); // t q[1];
    state = dd->multiply(dd->makeGateDD(dd::Tmat, dd->qubits(), 2), state); // t q[2];
    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 0), state); // h q[0];
    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 1), state); // h q[1];
    state = dd->multiply(dd->makeGateDD(dd::Hmat, dd->qubits(), 2), state); // h q[1];

    auto result = dd->getVectorLIMDD(state);

    double tolerance = 1e-5;
    EXPECT_NEAR(result[0].real(), 0.301777, tolerance);
    EXPECT_NEAR(result[0].imag(), +0.728553, tolerance);
    EXPECT_NEAR(result[1].real(), 0.301777, tolerance);
    EXPECT_NEAR(result[1].imag(), -0.125, tolerance);
    EXPECT_NEAR(result[2].real(), 0.301777, tolerance);
    EXPECT_NEAR(result[2].imag(), -0.125, tolerance);
    EXPECT_NEAR(result[3].real(), -0.0517767, tolerance);
    EXPECT_NEAR(result[3].imag(), -0.125, tolerance);
    EXPECT_NEAR(result[4].real(), 0.301777, tolerance);
    EXPECT_NEAR(result[4].imag(), -0.125, tolerance);
    EXPECT_NEAR(result[5].real(), -0.0517767, tolerance);
    EXPECT_NEAR(result[5].imag(), -0.125, tolerance);
    EXPECT_NEAR(result[6].real(), -0.0517767, tolerance);
    EXPECT_NEAR(result[6].imag(), -0.125, tolerance);
    EXPECT_NEAR(result[7].real(), -0.0517767, tolerance);
    EXPECT_NEAR(result[7].imag(), +0.0214466, tolerance);
}

TEST(LimTest, simpleU3Circuit) {
    auto dd    = std::make_unique<dd::Package>(1);
    auto state = dd->makeZeroState(dd->qubits());

    state = dd->multiply(dd->makeGateDD(dd::U3mat(1, 2, 3), dd->qubits(), 0), state);

    auto   result    = dd->getVectorLIMDD(state);
    double tolerance = 1e-5;

    EXPECT_NEAR(result[0].real(), 0.0707372, tolerance);
    EXPECT_NEAR(result[0].imag(), 0, tolerance);
    EXPECT_NEAR(result[1].real(), -0.415104, tolerance);
    EXPECT_NEAR(result[1].imag(), +0.90702, tolerance);
}

TEST(LimTest, multiQubitU3Circuit) {
    auto dd    = std::make_unique<dd::Package>(3);
    auto state = dd->makeZeroState(dd->qubits());

    state = dd->multiply(dd->makeGateDD(dd::U3mat(1, 2, 3), dd->qubits(), 2), state);
    state = dd->multiply(dd->makeGateDD(dd::U3mat(4, 5, 6), dd->qubits(), 1), state);
    state = dd->multiply(dd->makeGateDD(dd::U3mat(7, 8, 9), dd->qubits(), 0), state);
    state = dd->multiply(dd->makeGateDD(dd::Tmat, dd->qubits(), 2), state);
    state = dd->multiply(dd->makeGateDD(dd::Tmat, dd->qubits(), 1), state);
    state = dd->multiply(dd->makeGateDD(dd::Tmat, dd->qubits(), 0), state);
    state = dd->multiply(dd->makeGateDD(dd::U3mat(0.1, 0.2, 0.3), dd->qubits(), 2), state);
    state = dd->multiply(dd->makeGateDD(dd::U3mat(0.4, 0.5, 0.6), dd->qubits(), 1), state);
    state = dd->multiply(dd->makeGateDD(dd::U3mat(0.7, 0.8, 0.9), dd->qubits(), 0), state);

    auto   result    = dd->getVectorLIMDD(state);
    double tolerance = 1e-5;

    EXPECT_NEAR(result[0].real(), 0.130746, tolerance);
    EXPECT_NEAR(result[0].imag(), -0.0179993, tolerance);
    EXPECT_NEAR(result[1].real(), -0.130704, tolerance);
    EXPECT_NEAR(result[1].imag(), -0.107643, tolerance);
    EXPECT_NEAR(result[2].real(), 0.019129, tolerance);
    EXPECT_NEAR(result[2].imag(), +0.00924575, tolerance);
    EXPECT_NEAR(result[3].real(), -0.00792028, tolerance);
    EXPECT_NEAR(result[3].imag(), -0.026082, tolerance);
    EXPECT_NEAR(result[4].real(), -0.592292, tolerance);
    EXPECT_NEAR(result[4].imag(), +0.0125283, tolerance);
    EXPECT_NEAR(result[5].real(), 0.527022, tolerance);
    EXPECT_NEAR(result[5].imag(), +0.547661, tolerance);
    EXPECT_NEAR(result[6].real(), -0.0805028, tolerance);
    EXPECT_NEAR(result[6].imag(), -0.0511337, tolerance);
    EXPECT_NEAR(result[7].real(), 0.0218042, tolerance);
    EXPECT_NEAR(result[7].imag(), +0.120397, tolerance);
}
