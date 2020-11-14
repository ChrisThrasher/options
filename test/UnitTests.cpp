#include <Options.h>

#include <gtest/gtest.h>

TEST(Options, ExitItem)
{
    constexpr int argc = 2;
    constexpr const char* argv[argc] = {"options", "--help"};
    Options options(argc, argv);

    const auto exit_success = [](const int exit_code) { return exit_code == 0; };
    EXPECT_EXIT(options.ExitItem({"--help"}, ""), exit_success, "");
}

TEST(Options, At)
{
    constexpr int argc = 3;
    constexpr const char* argv[argc] = {"program_name", "first_arg", "second_arg"};
    Options options(argc, argv);
    EXPECT_EQ("program_name", options.At(0));
    EXPECT_EQ("first_arg", options.At(1));
    EXPECT_EQ("second_arg", options.At(2));
    EXPECT_THROW(options.At(3), std::out_of_range);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}