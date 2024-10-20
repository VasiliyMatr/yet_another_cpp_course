#ifndef P04_07_HPP
#define P04_07_HPP

#include <cstdint>
#include <type_traits>

namespace ya_cpp {

using UInt = uint64_t;

template <UInt N>
struct Fibonacci
    : std::integral_constant<UInt, Fibonacci<N - 1>{} + Fibonacci<N - 2>{}> {};

template <> struct Fibonacci<1> : std::integral_constant<UInt, 0> {};
template <> struct Fibonacci<2> : std::integral_constant<UInt, 1> {};

} // namespace ya_cpp

#endif // P04_07_HPP
