#pragma once

#include <istream>

enum class TokenType {
    Inc, 
    Dec, 
    MoveLeft, 
    MoveRight, 
    Input, 
    Output, 
    LoopStart,
    LoopEnd
};

class Lexer
{
public:
    Lexer(std::istream& input);

    bool nextToken(TokenType& token);

private:
    std::istream& _input;
};
