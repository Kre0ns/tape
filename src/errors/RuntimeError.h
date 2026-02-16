#pragma once

#include "Error.h"

class RuntimeError : public Error
{
public:
    RuntimeError(const std::string& message)
        : Error("Runtime Error: " + message)
    {
    }
};

