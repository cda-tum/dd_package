#include "dd/LimTable.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(LimTest, SinglePauliOps) {
    dd::LimEntry<1> id{0b000};
    dd::LimEntry<1> z{0b001};
    dd::LimEntry<1> x{0b010};
    dd::LimEntry<1> y{0b011};

    EXPECT_EQ(id.getQubit(0), 'I');
    EXPECT_EQ(x.getQubit(0), 'X');
    EXPECT_EQ(y.getQubit(0), 'Y');
    EXPECT_EQ(z.getQubit(0), 'Z');
}

TEST(LimTest, PauliToString) {
    dd::LimEntry<5> limEntry{0b011011000u}; // ...IIIYXZI. Bit order!

    auto str = limEntry.to_string();

    std::cout << str << "\n";

    ASSERT_STREQ(str.c_str(), "IYZXI");
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