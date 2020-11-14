#include <Options.h>

#include <gtest/gtest.h>

TEST(Help, Short)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "-h"};
    Options options(argc, argv);

    EXPECT_EXIT(options.Help("my help text"), testing::ExitedWithCode(0), "");
}

TEST(Help, Long)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--help"};
    Options options(argc, argv);

    EXPECT_EXIT(options.Help("my help text"), testing::ExitedWithCode(0), "");
}

TEST(ExitItem, Checkout)
{
    constexpr int argc = 3;
    constexpr const char* argv[argc] = {"options", "--flag", "-v"};
    Options options(3, argv);

    EXPECT_EXIT(options.ExitItem({"--flag"}, ""), testing::ExitedWithCode(0), "");
    options.ExitItem({"-v"}, "this won't be detected");
}

TEST(At, Checkout)
{
    constexpr int argc = 3;
    constexpr const char* argv[argc] = {"program_name", "first_arg", "second_arg"};
    Options options(argc, argv);
    EXPECT_EQ("program_name", options.At(0, ""));
    EXPECT_EQ("first_arg", options.At(1, ""));
    EXPECT_EQ("second_arg", options.At(2, ""));
    EXPECT_THROW(options.At(3, ""), std::out_of_range);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}