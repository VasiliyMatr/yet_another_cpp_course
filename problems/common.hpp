#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>

#define NODISCARD [[nodiscard]]

#define ASSERT(cond)                                                           \
    if (!(cond)) {                                                             \
        std::cerr << "Assertion failed on " << __FILE__ << ":" << __LINE__     \
                  << std::endl;                                                \
        std::terminate();                                                      \
    }

#endif // COMMON_HPP
