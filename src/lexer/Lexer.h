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

struct Token {
    TokenType type;
    int line;
    int column;
};

class Lexer
{
public:
    explicit Lexer(std::istream& input);

    bool nextToken(Token& token);

private:
    std::istream& _input;
    int _line = 1;
    int _column = 0;
};
