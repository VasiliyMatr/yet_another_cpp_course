#include <random>

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

#include "p02_11.hpp"

TEST(p02_11, heap_sort_basic) {
    std::vector<int> to_sort = {4, 2, 3, 1, 7, 9, -1};

    ya_cpp::heap_sort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_11, heap_sort_equal) {
    std::vector<int> to_sort = {1, 1, 1, 1, 1, 1, 1};

    ya_cpp::heap_sort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_11, heap_sort_sorted) {
    std::vector<int> to_sort = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    ya_cpp::heap_sort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_11, heap_sort_reversed) {
    std::vector<int> to_sort = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    ya_cpp::heap_sort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_11, heap_sort_many_big_numbers) {
    static constexpr size_t kToSortSize = 1'000'000;

    std::mt19937 mt{};

    std::vector<unsigned> to_sort(kToSortSize, 0);

    for (auto &&el : to_sort) {
        el = mt();
    }

    ya_cpp::heap_sort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_11, heap_sort_many_small_numbers) {
    static constexpr size_t kToSortSize = 1'000'000;
    static constexpr size_t kMaxNum = 255;

    std::mt19937 mt{};

    std::vector<unsigned> to_sort(kToSortSize, 0);

    for (auto &&el : to_sort) {
        el = mt() % (kMaxNum + 1);
    }

    ya_cpp::heap_sort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_11, heap_sort_many_bool_numbers) {
    static constexpr size_t kToSortSize = 1'000'000;
    static constexpr size_t kMaxNum = 1;

    std::mt19937 mt{};

    std::vector<unsigned> to_sort(kToSortSize, 0);

    for (auto &&el : to_sort) {
        el = mt() % (kMaxNum + 1);
    }

    ya_cpp::heap_sort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

#include "p02_12.hpp"

TEST(p02_12, qsort_basic) {
    std::vector<int> to_sort = {4, 2, 3, 1, 7, 9, -1};

    ya_cpp::qsort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_12, qsort_equal) {
    std::vector<int> to_sort = {1, 1, 1, 1, 1, 1, 1};

    ya_cpp::qsort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_12, qsort_sorted) {
    std::vector<int> to_sort = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    ya_cpp::qsort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_12, qsort_reversed) {
    std::vector<int> to_sort = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    ya_cpp::qsort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_12, qsort_many_big_numbers) {
    static constexpr size_t kToSortSize = 1'000'000;

    std::mt19937 mt{};

    std::vector<unsigned> to_sort(kToSortSize, 0);

    for (auto &&el : to_sort) {
        el = mt();
    }

    ya_cpp::qsort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_12, qsort_many_small_numbers) {
    static constexpr size_t kToSortSize = 1'000'000;
    static constexpr size_t kMaxNum = 255;

    std::mt19937 mt{};

    std::vector<unsigned> to_sort(kToSortSize, 0);

    for (auto &&el : to_sort) {
        el = mt() % (kMaxNum + 1);
    }

    ya_cpp::qsort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}

TEST(p02_12, qsort_many_bool_numbers) {
    static constexpr size_t kToSortSize = 1'000'000;
    static constexpr size_t kMaxNum = 1;

    std::mt19937 mt{};

    std::vector<unsigned> to_sort(kToSortSize, 0);

    for (auto &&el : to_sort) {
        el = mt() % (kMaxNum + 1);
    }

    ya_cpp::qsort(to_sort.begin(), to_sort.end());
    ASSERT_TRUE(std::is_sorted(to_sort.begin(), to_sort.end()));
}
