#include <gtest/gtest.h>

#include "p13.hpp"

TEST(p13_01, basic) {
    std::vector<uint8_t> bytes = {0x01, 0x23, 0x45, 0x60, 0xab};
    auto s = ya_cpp::p13::bytes2hex(bytes.begin(), bytes.end());

    EXPECT_EQ(s, "01234560AB");
}
