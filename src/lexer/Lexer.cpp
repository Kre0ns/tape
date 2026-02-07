#include "Lexer.h"

Lexer::Lexer(std::istream& input) 
    : _input(input)
{
}

bool Lexer::nextToken(TokenType& token)
{
    char currentChar;

    while (this->_input.get(currentChar))
    {
        switch (currentChar)
        {
        case '+':
            token = TokenType::Inc;
            return true;

        case '-':
            token = TokenType::Dec;
            return true;

        case '<':
            token = TokenType::MoveLeft;
            return true;
        
        case '>':
            token = TokenType::MoveRight;
            return true;

        case ',':
            token = TokenType::Input;
            return true;
        
        case '.':
            token = TokenType::Output;
            return true;

        case '[':
            token = TokenType::LoopStart;
            return true;

        case ']':
            token = TokenType::LoopEnd;
            return true;

        default:
            continue;
        }
    }

    return false;
}