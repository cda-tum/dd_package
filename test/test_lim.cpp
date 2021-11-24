
#include "dd/LimTable.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(LimTest, PauliToString) {
    dd::LimEntry limEntry{};
    limEntry.paulis |= 216u; // ...IIIYXZI

    auto str = limEntry.to_string();

    std::cout << str << "\n";

    ASSERT_STREQ(str.substr(str.length() - 5).c_str(), "IYXYI");
}