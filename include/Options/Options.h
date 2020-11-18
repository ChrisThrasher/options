#pragma once

#include <iostream>
#include <string>
#include <vector>

struct TerminalOption
{
    std::vector<std::string> flags;
    std::string description;
    std::string output;
};

class Options
{
    const std::vector<std::string> args{};

    void ExitItem(const TerminalOption&) const;

public:
    Options(const int, const char* const[]);
    void Help(const std::string&) const;
    void Version(const std::string&) const;
    auto At(const int, const std::string&) const -> std::string;
    auto Args() const -> std::vector<std::string>;
};

Options::Options(const int argc, const char* const argv[])
    : args(std::vector<std::string>(argv, argv + argc))
{
}

void Options::Help(const std::string& help_text) const { ExitItem({{"-h", "--help"}, "", help_text}); }

void Options::Version(const std::string& version_text) const { ExitItem({{"-v", "--version"}, "", version_text}); }

auto Options::At(const int pos, const std::string& name) const -> std::string
{
    const auto i = static_cast<size_t>(pos);
    if (i < args.size())
        return args[i];
    throw std::out_of_range("Failed to find " + name + " at index " + std::to_string(i));
}

auto Options::Args() const -> std::vector<std::string>
{
    return std::vector<std::string>(args.begin() + 1, args.end());
}

void Options::ExitItem(const TerminalOption& option) const
{
    if (args.size() == 1)
        return;

    for (const auto& flag : option.flags)
    {
        if (args[1] == flag)
        {
            std::cout << option.description << '\n';
            std::exit(0);
        }
    }
}
