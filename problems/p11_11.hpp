#ifndef P11_11_HPP
#define P11_11_HPP

#include <optional>
#include <type_traits>

namespace ya_cpp::p11 {

template <class InputIt, class OutputIt, class UnaryMaybeTransform>
OutputIt transform_if(InputIt first, InputIt last, OutputIt output,
                      UnaryMaybeTransform unary_maybe_transform) {
    for (; first != last; ++first)
        if (auto maybe_el = unary_maybe_transform(*first)) {
            *(output++) = *maybe_el;
        }

    return output;
}

} // namespace ya_cpp::p11

#endif // P11_11_HPP
