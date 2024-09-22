#include <gtest/gtest.h>

#include "p02_02.hpp"

TEST(p02_02, armstrong_basic) {
    ArmstrongNumbersSearcher searcher{};
    auto numbers = searcher.find(1000);
    std::vector<ULong> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407};

    ASSERT_EQ(numbers, expected);
}

#if 0
// Will need a few minutes
TEST(p02_02, armstrong_big) {
    ArmstrongNumbersSearcher searcher{};
    auto numbers = searcher.find(1'000'000'000);
    std::vector<ULong> expected{
        1,          2,          3,           4,           5,
        6,          7,          8,           9,           153,
        370,        371,        407,         1'634,       8'208,
        9'474,      54'748,     92'727,      93'084,      548'834,
        1'741'725,  4'210'818,  9'800'817,   9'926'315,   24'678'050,
        24'678'051, 88'593'477, 146'511'208, 472'335'975, 534'494'836,
        912'985'153};

    ASSERT_EQ(numbers, expected);
}
#endif

TEST(p02_02, fibonacci_basic) {
    FibonacciGenerator gen{0, 1};

    std::vector<int> numbers{0, 1};

    while (numbers.back() < 100) {
        numbers.push_back(gen.next());
    }

    std::vector<int> expected = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};

    ASSERT_EQ(numbers, expected);
}

TEST(p02_02, fibonacci_fp) {
    // Won't have rounding erros with such init values for a while
    FibonacciGenerator gen{-2.5, 1.5};

    std::vector<float> numbers{};

    for (int i = 0; i != 10; ++i) {
        numbers.push_back(gen.next());
    }

    std::vector<float> expected = {-1.,  0.5, -0.5, 0,    -0.5,
                                   -0.5, -1., -1.5, -2.5, -4.};

    ASSERT_EQ(numbers, expected);
}

TEST(p02_02, abundant_basic) {
    auto numbers = findAbundantNumbers(120);

    std::vector<ULong> expected = {12, 18, 20, 24,  30,  36,  40,  42,  48,
                                   54, 56, 60, 66,  70,  72,  78,  80,  84,
                                   88, 90, 96, 100, 102, 104, 108, 112, 114};

    ASSERT_EQ(numbers, expected);
}

TEST(p02_02, amicable_basic) {
    auto pairs = findAmicablePairs(3000);

    // Expect 3 pairs
    ASSERT_EQ(pairs.size(), 3);

    ASSERT_EQ(pairs[220], 284);
    ASSERT_EQ(pairs[1184], 1210);
    ASSERT_EQ(pairs[2620], 2924);
}
