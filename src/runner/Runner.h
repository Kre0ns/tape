#pragma once

#include <iostream>

#include "Interpreter.h"

class Runner
{
public:
    void run(std::istream& input);

private:
    Interpreter _interpreter;
};
