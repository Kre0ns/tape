#pragma once

#include <string_view>

#include "Runner.h"

class REPL
{
public:
    REPL();

    void init();

private:
    static constexpr std::string_view ReplVersion = "0.1.0";
    static constexpr std::string_view ExitKeyword = "exit";

    Runner _runner;
};
