#pragma once

#include <argon/Argument.h>

#include <iomanip>
#include <sstream>

namespace argon
{

enum Count
{
    SINGLE = 0,
    VARIADIC
};

class Position final : public Argument
{
    std::string m_name;
    std::string m_description;

public:
    Position(const std::string& name, const std::string& description, const Count count)
        : m_name(count == SINGLE ? name : name + "...")
        , m_description(description)
    {
    }

    virtual auto Format() const -> std::string
    {
        std::stringstream out;
        out << std::setfill(' ');
        out << "\n  " << std::left << std::setw(m_format_width) << m_name << m_description;
        return out.str();
    }

    auto Name() const -> std::string { return m_name; }
};

} // namespace argon
