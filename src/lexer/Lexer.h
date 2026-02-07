#pragma once

#include <istream>

#include "TokenType.h"

class Lexer
{
public:
    Lexer(std::istream& input);

    bool nextToken(TokenType& token);

private:
    std::istream& _input;
};
