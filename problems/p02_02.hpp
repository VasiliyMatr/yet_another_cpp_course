#ifndef P02_02_HPP
#define P02_02_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "common.hpp"

using std::size_t;

using ULong = unsigned long long;
using Long = long long;

template <size_t radix_base = 10> class ArmstrongNumbersSearcher final {
    static_assert(radix_base != 0);

    using DigitsPowersBuff = std::array<ULong, radix_base>;

    std::vector<DigitsPowersBuff> m_digits_powers{};

    static int getDigitsNum(ULong num) noexcept {
        int i = 0;

        do {
            num /= radix_base;
            ++i;
        } while (num != 0);

        return i;
    }

  public:
    NODISCARD std::vector<ULong> find(ULong limit) {
        if (limit == 0) {
            return {};
        }

        /// [1] Calculate all needed digits powers
        auto limit_digits_num = getDigitsNum(limit);
        m_digits_powers.resize(limit_digits_num);

        std::iota(m_digits_powers[0].begin(), m_digits_powers[0].end(), 0);

        for (int i = 1; i != limit_digits_num; ++i) {
            for (int j = 0; j != radix_base; ++j) {
                m_digits_powers[i][j] = m_digits_powers[i - 1][j] * j;
            }
        }

        std::vector<ULong> out{};

        /// [2] Check all numbers
        ULong next_digit_limit = radix_base;
        size_t digits_num = 1;

        for (ULong i = 1; i != limit; ++i) {
            ULong to_check = i;
            ULong sum = 0;

            if (next_digit_limit == i) {
                ++digits_num;
                next_digit_limit *= radix_base; // overflow is OK
            }

            do {
                auto digit = to_check % radix_base;
                to_check /= radix_base;
                sum += m_digits_powers[digits_num - 1][digit];
            } while (to_check != 0);

            if (i == sum) {
                out.push_back(i);
            }
        }

        return out;
    }
};

template <class T> class FibonacciGenerator final {
    T m_prev;
    T m_prev_prev;

  public:
    FibonacciGenerator(const T &first, const T &second)
        : m_prev(second), m_prev_prev(first) {}

    NODISCARD T next() noexcept {
        auto out = m_prev + m_prev_prev;
        m_prev_prev = m_prev;
        m_prev = out;

        return out;
    }
};

NODISCARD inline ULong calcProperDividersSum(ULong num) {
    // 0 and 1 have no proper dividers
    if (num < 2) {
        return 0;
    }

    /// [1] Seek for max possible divider
    ULong max_possible_divider = 0;
    for (ULong i = sqrtl(num);; ++i) {
        if (i * i >= num) {
            max_possible_divider = i;
            break;
        }
    }

    /// [2] Check all possible dividers
    ULong out = 1; // 1 is always a divider

    for (ULong i = 2; i < max_possible_divider; ++i) {
        if (num % i == 0) {
            out += i;
            out += num / i;
        }
    }

    // Account square divider once
    if (max_possible_divider * max_possible_divider == num) {
        out += max_possible_divider;
    }

    return out;
}

NODISCARD inline std::vector<ULong> findAbundantNumbers(ULong limit) {
    std::vector<ULong> out{};

    for (ULong i = 1; i != limit; ++i) {
        ULong dividers_sum = calcProperDividersSum(i);

        if (i < dividers_sum) {
            out.push_back(i);
        }
    }

    return out;
}

NODISCARD inline auto findAmicablePairs(ULong limit) {
    /// [1] Calculate all proper dividers sums

    // Num -> proper dividers sum
    std::vector<ULong> proper_dividers_sum{};
    proper_dividers_sum.reserve(limit);

    for (ULong i = 0; i != limit; ++i) {
        proper_dividers_sum.push_back(calcProperDividersSum(i));
    }

    /// [2] Collect amicable pairs
    std::unordered_map<ULong, ULong> out{};

    // 0 and 1 can not belong to any amicable tuple
    for (ULong i = 2; i != limit; ++i) {
        auto j = proper_dividers_sum[i];

        if (j < limit && proper_dividers_sum[j] == i && i != j) {
            out.try_emplace(std::min(i, j), std::max(i, j));
        }
    }

    return out;
}

#endif // P02_02_HPP
