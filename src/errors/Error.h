#pragma once

#include <string>
#include <stdexcept>

class Error : public std::runtime_error
{
public:
    Error(const std::string& message)
        : std::runtime_error(message)
    {
    }
};