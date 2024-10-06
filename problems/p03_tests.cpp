#include <gtest/gtest.h>

struct Foo {
    virtual ~Foo() = default;
    virtual const char *name() { return "Foo"; }
};

struct Bar {
    virtual ~Bar() = default;
    virtual const char *name() { return "Bar"; }
};

struct Baz final : public Foo, Bar {
    const char *name() override { return "Baz"; }
};

struct Foo2 : public Foo {
    virtual const char *nameFoo() = 0;
    const char *name() override { return nameFoo(); }
};

struct Bar2 : public Bar {
    virtual const char *nameBar() = 0;
    const char *name() override { return nameBar(); }
};

struct Baz2 final : public Foo2, Bar2 {
    const char *nameFoo() override { return "Baz as Foo"; }
    const char *nameBar() override { return "Baz as Bar"; }
};

TEST(p03_04, override_twin_funcs_basic) {
    Baz baz{};
    ASSERT_STREQ(static_cast<Foo *>(&baz)->name(), "Baz");
    ASSERT_STREQ(static_cast<Bar *>(&baz)->name(), "Baz");

    Baz2 baz2{};
    ASSERT_STREQ(static_cast<Foo *>(&baz2)->name(), "Baz as Foo");
    ASSERT_STREQ(static_cast<Bar *>(&baz2)->name(), "Baz as Bar");
}

TEST(p03_05, dynamic_cast_basic) {
    Baz baz{};
    Foo *baz_foo = &baz;
    Bar *baz_bar = &baz;

    Foo foo{};
    Bar bar{};

    // Down-casts
    ASSERT_NE(dynamic_cast<Baz*>(baz_foo), nullptr);
    ASSERT_NE(dynamic_cast<Baz*>(baz_bar), nullptr);
    // Can not turn off GCC warnings for these lines
    // ASSERT_EQ(dynamic_cast<Baz*>(&foo), nullptr);
    // ASSERT_EQ(dynamic_cast<Baz*>(&bar), nullptr);

    // Side-casts
    ASSERT_NE(dynamic_cast<Bar*>(baz_foo), nullptr);
    ASSERT_NE(dynamic_cast<Foo*>(baz_bar), nullptr);
    // Can not turn off GCC warnings for these lines
    // ASSERT_EQ(dynamic_cast<Bar*>(&foo), nullptr);
    // ASSERT_EQ(dynamic_cast<Foo*>(&bar), nullptr);
}
