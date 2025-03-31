#include <gtest/gtest.h>

#include "p12.hpp"

TEST(p12_06, basic1) {
    std::string s = "heLLo, woRLD";
    ya_cpp::p12::fixLetterCase(s.data());
    EXPECT_STREQ(s.c_str(), "Hello, World");
}

TEST(p12_06, basic2) {
    std::string s = "bAsIc fixLetterCase Test";
    ya_cpp::p12::fixLetterCase(s.data());
    EXPECT_STREQ(s.c_str(), "Basic Fixlettercase Test");
}

TEST(p12_06, numbers) {
    std::string s = "123with 456nUMBERS";
    ya_cpp::p12::fixLetterCase(s.data());
    EXPECT_STREQ(s.c_str(), "123With 456Numbers");
}

TEST(p12_06, dash) {
    std::string s = "dash-test";
    ya_cpp::p12::fixLetterCase(s.data());
    EXPECT_STREQ(s.c_str(), "Dash-Test");
}

TEST(p12_07, basic_rng_1) {
    std::vector<std::string> to_concat {"foo"};
    auto s = ya_cpp::p12::concat_rng("; ", to_concat.begin(), to_concat.end());
    EXPECT_STREQ(s.c_str(), "foo");
}

TEST(p12_07, basic_rng_3) {
    std::vector<std::string> to_concat {"foo", "bar", "buz"};
    auto s = ya_cpp::p12::concat_rng("; ", to_concat.begin(), to_concat.end());
    EXPECT_STREQ(s.c_str(), "foo; bar; buz");
}

TEST(p12_07, basic_1) {
    auto s = ya_cpp::p12::concat("; ", "foo");
    EXPECT_STREQ(s.c_str(), "foo");
}

TEST(p12_07, basic_3) {
    auto s = ya_cpp::p12::concat("; ", "foo", "bar", "buz");
    EXPECT_STREQ(s.c_str(), "foo; bar; buz");
}

TEST(p12_07, mixed_1) {
    auto s = ya_cpp::p12::concat(std::string("; "), std::string_view("foo"));
    EXPECT_STREQ(s.c_str(), "foo");
}

TEST(p12_07, mixed_3) {
    std::string s1 = "foo";
    std::string s2 = "bar";

    auto s = ya_cpp::p12::concat("; ", s1, std::move(s2), std::string("buz"));
    EXPECT_STREQ(s.c_str(), "foo; bar; buz");
}
