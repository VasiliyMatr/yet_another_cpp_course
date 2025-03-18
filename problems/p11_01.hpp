#ifndef P11_01_HPP
#define P11_01_HPP

namespace ya_cpp::p11_01 {

struct Mediator;
Mediator selfReturningFunc();

struct Mediator {
    decltype(selfReturningFunc) *func = &selfReturningFunc;
};

Mediator selfReturningFunc() {
    return Mediator{};
}

} // namespace ya_cpp::p11_01

#endif // P11_01_HPP
