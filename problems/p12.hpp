#ifndef P12_HPP
#define P12_HPP

#include <algorithm>
#include <cctype>
#include <span>
#include <string>

namespace ya_cpp::p12 {

// Solution for p12.06
// Convert start words letters to upper case and all other letters to lower case
void fixLetterCase(char *str) {
    bool prev_is_alpha = false;
    for (; *str != '\0'; ++str) {
        auto &c = *str;
        if (prev_is_alpha) {
            c = static_cast<char>(std::tolower(c));
        } else {
            c = static_cast<char>(std::toupper(c));
        }
        prev_is_alpha = std::isalpha(c);
    }
}

// Solution for p12.07 (ver 1)
// Concatenate strings in given iterator range with given delimiter
template <class It>
std::string concat_rng(std::string_view delim, It first, It last) {
    std::string out{};

    if (first != last) {
        out += *first++;
    }

    for (; first != last; ++first) {
        out += delim;
        out += *first;
    }

    return out;
}

// Impl for p12.07 (ver 2)
template <class Delim, class Arg0, class... ArgN>
struct ConcatImpl final {
    static std::string concat(const Delim &delim, Arg0 &&arg0, ArgN &&...argn) {
        std::string out;
        out += std::forward<Arg0>(arg0);
        out += delim;
        out += ConcatImpl<Delim, ArgN...>::concat(delim,
                                                  std::forward<ArgN>(argn)...);
        return out;
    }
};

// Impl for p12.07 (ver 2)
template <class Delim, class Arg0>
struct ConcatImpl<Delim, Arg0> {
    static std::string concat(const Delim &, Arg0 &&arg0) {
        std::string out;
        out += arg0;
        return out;
    }
};

// Solution for p12.07 (ver 2)
// Concatenate given arguments to string with given delimiter
template <class Delim, class Arg0, class... ArgN>
std::string concat(const Delim &delim, Arg0 &&arg0, ArgN &&...argn) {
    return ConcatImpl<Delim, Arg0, ArgN...>::concat(
        delim, std::forward<Arg0>(arg0), std::forward<ArgN>(argn)...);
}

} // namespace ya_cpp::p12

#endif // P12_HPP
