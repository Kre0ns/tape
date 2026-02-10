#pragma once

#include <memory>
#include <stack>

#include "Lexer.h"
#include "AST.h"
#include "SyntaxError.h"

class Parser
{
public:
    Parser(Lexer& lexer);

    std::unique_ptr<ASTNode> parse();

private:
    Lexer& _lexer;
};