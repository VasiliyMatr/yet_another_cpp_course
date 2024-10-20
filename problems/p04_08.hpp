#ifndef P04_08_HPP
#define P04_08_HPP

#include <cstdint>
#include <type_traits>

namespace ya_cpp {

using UInt = uint64_t;

template <UInt N, UInt K>
struct Factorial : std::integral_constant<UInt, N * Factorial<N - 1, K>{}> {
    static_assert(N > K);
};

template <UInt N> struct Factorial<N, N> : std::integral_constant<UInt, 1> {};

template <UInt N, UInt K>
struct BinomialCoefficient
    : std::integral_constant<UInt, Factorial<N, K>{} / Factorial<N - K, 1>{}> {
    static_assert(N > K);
};

template <UInt N>
struct BinomialCoefficient<N, N> : std::integral_constant<UInt, 1> {};

} // namespace ya_cpp

#endif // P04_08_HPP
