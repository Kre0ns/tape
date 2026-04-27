#include "Lexer.h"

Lexer::Lexer(std::istream& input) 
    : _input(input)
{
}

bool Lexer::nextToken(Token& token)
{
    char currentChar;

    while (this->_input.get(currentChar))
    {
        this->_column++;

        if (currentChar == '\n')
        {
            this->_line++;
            this->_column = 0;
            continue;
        }

        switch (currentChar)
        {
            using enum TokenType;

            case '+':
                token = {Inc, this->_line, this->_column};
                return true;

            case '-':
                token = {Dec, this->_line, this->_column};
                return true;

            case '<':
                token = {MoveLeft, this->_line, this->_column};
                return true;
            
            case '>':
                token = {MoveRight, this->_line, this->_column};
                return true;

            case ',':
                token = {Input, this->_line, this->_column};
                return true;
            
            case '.':
                token = {Output, this->_line, this->_column};
                return true;

            case '[':
                token = {LoopStart, this->_line, this->_column};
                return true;

            case ']':
                token = {LoopEnd, this->_line, this->_column};
                return true;

            default:
                continue;
        }
    }

    return false;
}