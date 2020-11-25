#pragma once

#include <functional>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace opts
{

class Option
{
    std::set<std::string> m_flags;
    std::set<char> m_aliases;
    const std::string m_description;

protected:
    auto Flags() const -> std::vector<std::string>
    {
        std::vector<std::string> flags;
        for (const auto& alias : m_aliases)
            flags.push_back(std::string("-") + alias);
        for (const auto& flag : m_flags)
            flags.push_back("--" + flag);
        return flags;
    }

    Option(const std::string& flags, const std::string& description)
        : m_description(description)
    {
        std::stringstream ss(flags);
        while (ss.good())
        {
            std::string str;
            std::getline(ss, str, ',');
            if (str.size() == 1)
                m_aliases.emplace(str[0]);
            else
                m_flags.emplace(str);
        }
    }

public:
    auto Format() const -> std::string
    {
        std::string flags;
        std::string delim = "";
        for (const auto& flag : Flags())
        {
            flags += delim + flag;
            delim = ", ";
        }

        std::stringstream out;
        out << std::setfill(' ');
        out << "\n  " << std::left << std::setw(16) << flags << m_description;
        return out.str();
    }

    virtual void Find(const std::vector<std::string>& args) const = 0;
};

class BasicOption final : public Option
{
    const std::function<void()> m_callback;

public:
    BasicOption(const std::string& flags, const std::string& description, const std::function<void()>& callback)
        : Option(flags, description)
        , m_callback(callback)
    {
    }

    virtual void Find(const std::vector<std::string>& args) const
    {
        for (const auto& flag : Flags())
            for (const auto& arg : args)
                if (flag == arg)
                    return m_callback();
    }
};

class ValueOption final : public Option
{
    const std::function<void(std::string)> m_callback;

public:
    ValueOption(const std::string& flags,
                const std::string& description,
                const std::function<void(std::string)>& callback)
        : Option(flags, description)
        , m_callback(callback)
    {
    }

    virtual void Find(const std::vector<std::string>& args) const
    {
        for (const auto& flag : Flags())
            for (size_t i = 0; i + 1 < args.size(); ++i)
                if (flag == args[i])
                    return m_callback(args[i + 1]);
    }
};

} // namespace opts
