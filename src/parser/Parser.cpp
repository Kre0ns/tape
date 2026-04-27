#include "Parser.h"

#include <stack>
#include <format>

#include "SyntaxError.h"

Parser::Parser(Lexer& lexer)
    : _lexer(lexer)
{
}

std::unique_ptr<ASTNode> Parser::parse()
{
    std::stack<ASTNode*> scopeStack;

    std::unique_ptr<ASTNode> root = std::make_unique<ASTNode>(NodeType::Root, 0, 0);
    scopeStack.push(root.get());

    Token currentToken;

    while (this->_lexer.nextToken(currentToken))
    {
        ASTNode* currentScope = scopeStack.top();

        switch (currentToken.type)
        {
            case TokenType::Inc: 
                currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Inc, currentToken.line, currentToken.column));
                break;
            
            case TokenType::Dec:
                currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Dec, currentToken.line, currentToken.column));
                break;
            
            case TokenType::MoveLeft:
                currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::MoveLeft, currentToken.line, currentToken.column));
                break;

            case TokenType::MoveRight:
                currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::MoveRight, currentToken.line, currentToken.column));
                break;

            case TokenType::Input:
                currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Input, currentToken.line, currentToken.column));
                break;

            case TokenType::Output:
                currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Output, currentToken.line, currentToken.column));
                break;

            case TokenType::LoopStart:
                currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Loop, currentToken.line, currentToken.column));
                scopeStack.push(currentScope->children.back().get());
                break;

            case TokenType::LoopEnd:
                if (currentScope->type != NodeType::Loop)
                {
                    std::string msg = std::format("Unexpected token ']' at {}:{}", currentToken.line, currentToken.column);
                    throw SyntaxError(msg);
                } 
                
                scopeStack.pop();
                break;

            default:
                break;
        }
    }

    if (scopeStack.top()->type != NodeType::Root)
    {
        std::string msg = std::format("Unclosed loop '[' at {}:{}", scopeStack.top()->line, scopeStack.top()->column);
        throw SyntaxError(msg);
    }

    return root;
}