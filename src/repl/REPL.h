#pragma once

#include <string> 
#include <iostream>
#include <sstream> 
#include <string_view>

#include "MachineState.h"
#include "Interpreter.h"
#include "Lexer.h"
#include "Parser.h"
#include "Error.h"

class REPL
{
public:
    REPL();

    void init();

private:
    static constexpr std::string_view ReplVersion = "0.1.0";
    static constexpr std::string_view ExitKeyword = "exit";

    MachineState _state;
    Interpreter _interpreter;
};
