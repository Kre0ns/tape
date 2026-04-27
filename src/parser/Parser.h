#pragma once

#include <memory>

#include "Lexer.h"
#include "AST.h"

class Parser
{
public:
    explicit Parser(Lexer& lexer);

    std::unique_ptr<ASTNode> parse();

private:
    Lexer& _lexer;
};