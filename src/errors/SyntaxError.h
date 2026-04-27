#pragma once

#include "Error.h"

class SyntaxError : public Error
{
public:
    explicit SyntaxError(const std::string& message)
        : Error("Syntax Error: " + message)
    {
    }
};

