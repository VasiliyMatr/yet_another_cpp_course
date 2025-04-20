#ifndef P13_HPP
#define P13_HPP

#include <iomanip>
#include <sstream>
#include <string>

namespace ya_cpp::p13 {

template <class It> std::string bytes2hex(It first, It last) {
    std::stringstream s;

    s << std::hex << std::uppercase << std::setfill('0') << std::setw(2);
    for (; first != last; ++first) {
        s << static_cast<int>(*first);
    }

    return s.str();
}

} // namespace ya_cpp::p13

#endif // P13_HPP
