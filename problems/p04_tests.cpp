#include <gtest/gtest.h>

#include "p04_07.hpp"

TEST(p04_07, basic_fibonacci) {
    ASSERT_EQ(ya_cpp::Fibonacci<1>{}.value, 0);
    ASSERT_EQ(ya_cpp::Fibonacci<2>{}.value, 1);
    ASSERT_EQ(ya_cpp::Fibonacci<10>{}.value, 34);
    ASSERT_EQ(ya_cpp::Fibonacci<20>{}.value, 4181);
}

#include "p04_08.hpp"

TEST(p04_08, basic_binomial) {
    ASSERT_EQ((ya_cpp::BinomialCoefficient<1, 1>{}), 1);
    ASSERT_EQ((ya_cpp::BinomialCoefficient<2, 2>{}), 1);
    ASSERT_EQ((ya_cpp::BinomialCoefficient<3, 3>{}), 1);

    ASSERT_EQ((ya_cpp::BinomialCoefficient<2, 1>{}), 2);
    ASSERT_EQ((ya_cpp::BinomialCoefficient<3, 1>{}), 3);
    ASSERT_EQ((ya_cpp::BinomialCoefficient<3, 2>{}), 3);

    ASSERT_EQ((ya_cpp::BinomialCoefficient<20, 7>{}), 77'520);
    ASSERT_EQ((ya_cpp::BinomialCoefficient<20, 10>{}), 184'756);
}
