#include <gtest/gtest.h>

#include "p11_01.hpp"
#include "p11_03.hpp"

using namespace ya_cpp::p11_01;

TEST(p11_01, basic) { ASSERT_EQ(&selfReturningFunc, selfReturningFunc().func); }

using namespace ya_cpp::p11_03;

struct Foo {
    int a = 0;
};

TEST(p11_03, template_factory) {
    Factory<int, double, Factory<Foo>> f;

    f.addCreator<int>([]() { return 1; });
    f.addCreator<double>([]() { return 2.0; });
    f.addCreator<Factory<Foo>>([]() {
        Factory<Foo> out;
        out.addCreator<Foo>([]() { return Foo{13}; });
        return out;
    });

    ASSERT_EQ(f.create<int>(), 1);
    ASSERT_EQ(f.create<double>(), 2.0);

    auto ff = f.create<Factory<Foo>>();

    ASSERT_EQ(ff.create<Foo>().a, 13);
}

TEST(p11_03, dyn_factory) {
    DynFactory f;

    f.addCreator<int>([]() { return 1; });
    f.addCreator<double>([]() { return 2.0; });
    f.addCreator<DynFactory>([]() {
        DynFactory out;
        out.addCreator<Foo>([]() { return Foo{13}; });
        return out;
    });

    ASSERT_EQ(*f.create<int>(), 1);
    ASSERT_EQ(*f.create<double>(), 2.0);

    auto ff = f.create<DynFactory>();

    ASSERT_EQ(ff->create<Foo>()->a, 13);
}
