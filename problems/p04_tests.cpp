#include <gtest/gtest.h>

#include "p04_07.hpp"

TEST(p04_07, basic_fibonacci) {
    ASSERT_EQ(ya_cpp::Fibonacci<1>{}.value, 0);
    ASSERT_EQ(ya_cpp::Fibonacci<2>{}.value, 1);
    ASSERT_EQ(ya_cpp::Fibonacci<10>{}.value, 34);
    ASSERT_EQ(ya_cpp::Fibonacci<20>{}.value, 4181);
}
