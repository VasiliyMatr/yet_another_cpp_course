#include <gmock/gmock.h>
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

// std algos tests for 11.12
// Disclaimer: Some string manipulations can look strange (as std::string
// methods can be used instead). But those are used for demonstration

TEST(p11_12, std_count) {
    std::vector<int> v{1, 2, 3, 4, 5, 5, 5, 5};
    EXPECT_EQ(std::count(v.begin(), v.end(), 5), 4);
    EXPECT_EQ(std::count_if(v.begin(), v.end(),
                            [](const auto &val) { return val % 2 == 1; }),
              6);
}

TEST(p11_12, std_mismatch) {
    std::string s1 = "qwerty";
    std::string s2 = "qweRty";
    auto common = std::string(
        s1.begin(), std::mismatch(s1.begin(), s1.end(), s2.begin()).first);

    EXPECT_STREQ(common.c_str(), "qwe");

    auto CoMmOn = std::string(
        s1.begin(),
        std::mismatch(s1.begin(), s1.end(), s2.begin(), [](auto c1, auto c2) {
            return std::tolower(c1) == std::tolower(c2);
        }).first);

    EXPECT_STREQ(CoMmOn.c_str(), "qwerty");
}

TEST(p11_12, std_equal) {
    std::vector<int> v1{1, 2, 3, 2, 1};
    EXPECT_TRUE(std::equal(v1.begin(), v1.end(), v1.rbegin()));

    // Funny overload :)
    std::string s1 = "abc";
    std::string s2 = "abcde";
    EXPECT_FALSE(std::equal(s1.begin(), s1.end(), s2.begin(), s2.end()));
}

TEST(p11_12, std_search) {
    std::string search =
        "When choosing a container, remember vector is best; Leave a "
        "comment to explain if you choose from the rest!";

    std::string target = "rest";

    std::string found = std::string(
        std::search(search.begin(), search.end(), target.begin(), target.end()),
        search.end());

    EXPECT_STREQ(found.c_str(), "rest!");
}

TEST(p11_12, std_replace) {
    std::vector<int> v1 = {1, 2, 3, 4, 5};

    std::replace(v1.begin(), v1.end(), 1, 10);
    EXPECT_THAT(v1, testing::ElementsAre(10, 2, 3, 4, 5));

    std::replace_if(
        v1.begin(), v1.end(), [](auto) { return true; }, 10);
    EXPECT_THAT(v1, testing::ElementsAre(10, 10, 10, 10, 10));
}

TEST(p11_12, std_remove) {
    std::vector<int> v1{1, 2, 3, 3, 4, 5};
    std::vector<int> v2 = v1;

    std::remove(v1.begin(), v1.end(), 3);
    EXPECT_THAT(v1, testing::ElementsAre(1, 2, 4, 5, 4, 5));

    std::remove_if(v2.begin(), v2.end(), [](auto) { return true; });
    EXPECT_THAT(v2, testing::ElementsAre(1, 2, 3, 3, 4, 5));
}

TEST(p11_12, std_unique) {
    std::vector<int> v1{1, 2, 2, 2, 3, 3, 4, 5, 5, 5, 5};

    auto last = std::unique(v1.begin(), v1.end());
    v1.resize(last - v1.begin());
    EXPECT_THAT(v1, testing::ElementsAre(1, 2, 3, 4, 5));

    auto last2 =
        std::unique(v1.begin(), v1.end(), [](auto, auto) { return true; });
    EXPECT_EQ(last2, v1.begin() + 1);
}

TEST(p11_12, std_rotate) {
    std::vector<int> v1{1, 2, 3, 4, 5};

    // Simple left rotation
    std::rotate(v1.begin(), v1.begin() + 1, v1.end());
    EXPECT_THAT(v1, testing::ElementsAre(2, 3, 4, 5, 1));

    // Simple right rotation
    std::rotate(v1.rbegin(), v1.rbegin() + 2, v1.rend());
    EXPECT_THAT(v1, testing::ElementsAre(5, 1, 2, 3, 4));
}

TEST(p11_12, std_partition) {
    std::vector<int> v1{-2, -4, -10, 11, 1, 2, -5};

    std::partition(v1.begin(), v1.end(), [](auto val) { return val >= 0; });
    EXPECT_EQ(v1.size(), 7);
    EXPECT_GE(v1[0], 0);
    EXPECT_GE(v1[1], 0);
    EXPECT_GE(v1[2], 0);
    EXPECT_TRUE(v1[3] < 0);
    EXPECT_TRUE(v1[4] < 0);
    EXPECT_TRUE(v1[5] < 0);
    EXPECT_TRUE(v1[6] < 0);
}

TEST(p11_12, std_nth_element) {
    std::vector<int> v1{10, 15, -5, 6, 7, 8};
    auto median_it = v1.begin() + v1.size() / 2;

    std::nth_element(v1.begin(), median_it, v1.end());

    EXPECT_EQ(*median_it, 8);

    auto end = v1.end();
    for (auto i = v1.begin(); i != median_it; ++i)
        for (auto j = median_it; j != end; ++j) {
            EXPECT_FALSE(*j < *i);
        }
}
