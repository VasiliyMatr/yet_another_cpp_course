#ifndef P02_11_HPP
#define P02_11_HPP

#include <functional>

namespace ya_cpp {

template <class RandomIt, class Compare>
void heap_sink(RandomIt it, size_t to_sink, size_t n, Compare &cmp) {
    auto child = 2 * to_sink + 1;

    while (child < n) {
        if (child < n - 1 && cmp(it[child], it[child + 1])) {
            ++child;
        }

        if (!cmp(it[to_sink], it[child])) {
            break;
        } else {
            std::swap(it[to_sink], it[child]);
        }

        to_sink = child;
        child = 2 * to_sink + 1;
    }
}

template <class RandomIt, class Compare>
void heap_sort(RandomIt first, RandomIt last, Compare &cmp) {
    size_t n = last - first;

    // Turn range into heap
    for (size_t i = n / 2, end = n; i != end; ++i) {
        heap_sink(first, n - 1 - i, n, cmp);
    }

    // Shrink heap until all elements are sorted
    while (n > 0) {
        // Max element is on top of the heap
        std::swap(first[0], first[n - 1]);
        // Restore heap invariant
        heap_sink(first, 0, --n, cmp);
    }
}

template <class RandomIt> void heap_sort(RandomIt first, RandomIt last) {
    std::less<typename std::iterator_traits<RandomIt>::value_type> cmp{};
    heap_sort(first, last, cmp);
}

} // namespace ya_cpp

#endif // P02_11_HPP
