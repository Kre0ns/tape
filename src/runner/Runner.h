#pragma once

#include <iostream>

#include "Interpreter.h"

class Runner
{
public:
    Runner();

    void run(std::istream& input);

private:
    MachineState _state;
    Interpreter _interpreter;
};
