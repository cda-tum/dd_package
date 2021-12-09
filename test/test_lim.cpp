#include "dd/LimTable.hpp"
#include "dd/Package.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

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

    EXPECT_STREQ(str.c_str(), "IYZXI");

    auto str_default = dd::LimEntry<5>::to_string(nullptr);
    std::cout << str_default << "\n";

    EXPECT_STREQ(str_default.c_str(), "IIIII");
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

    root_edge.p->v_lim.push_back(y);
    root_edge.p->v_lim.push_back(y);
    root_edge.p->v_lim.push_back(i);

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
