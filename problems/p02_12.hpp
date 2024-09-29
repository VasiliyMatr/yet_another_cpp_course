#ifndef P02_12_HPP
#define P02_12_HPP

#include <functional>

namespace ya_cpp {

template <class RandomIt, class Compare>
void buble_sort(RandomIt first, RandomIt last, Compare &cmp) {
    for (; first < last; ++first)
        for (auto j = first; j < last; ++j) {
            if (cmp(*j, *first)) {
                std::swap(*j, *first);
            }
        }
}

template <class RandomIt, class Compare>
void qsort(RandomIt first, RandomIt last, Compare &cmp) {
    static constexpr ssize_t kFallbackNum = 4;

    auto el_num = last - first;
    if (el_num <= kFallbackNum) {
        buble_sort(first, last, cmp);
        return;
    }

    auto mid_el = *(first + el_num / 2);
    auto left = first;
    auto right = last - 1;

    while (true) {
        while (cmp(*left, mid_el))
            ++left;
        while (cmp(mid_el, *right))
            --right;

        if (left >= right) {
            break;
        }

        std::swap(*left, *right);
        --right;
        ++left;
    }

    qsort(first, right + 1, cmp);
    qsort(right + 1, last, cmp);
}

template <class RandomIt> void qsort(RandomIt first, RandomIt last) {
    std::less<typename std::iterator_traits<RandomIt>::value_type> cmp{};
    qsort(first, last, cmp);
}

} // namespace ya_cpp

#endif // P02_12_HPP
