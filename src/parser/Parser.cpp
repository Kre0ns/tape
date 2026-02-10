#include "Parser.h"

Parser::Parser(Lexer& lexer)
    : _lexer(lexer)
{
}

std::unique_ptr<ASTNode> Parser::parse()
{
    std::stack<ASTNode*> scopeStack;

    std::unique_ptr<ASTNode> root = std::make_unique<ASTNode>(NodeType::Root);
    scopeStack.push(root.get());

    TokenType currentToken;

    while (this->_lexer.nextToken(currentToken))
    {
        ASTNode* currentScope = scopeStack.top();

        switch (currentToken)
        {
        case TokenType::Inc: 
            currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Inc));
            break;
        
        case TokenType::Dec:
            currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Dec));
            break;
        
        case TokenType::MoveLeft:
            currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::MoveLeft));
            break;

        case TokenType::MoveRight:
            currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::MoveRight));
            break;

        case TokenType::Input:
            currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Input));
            break;

        case TokenType::Output:
            currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Output));
            break;

        case TokenType::LoopStart:
            currentScope->children.emplace_back(std::make_unique<ASTNode>(NodeType::Loop));
            scopeStack.push(currentScope->children.back().get());
            break;

        case TokenType::LoopEnd:
            if (currentScope->type != NodeType::Loop) throw SyntaxError("Unexpected token ']': No matching open loop found.");
            scopeStack.pop();
            break;

        default:
            break;
        }
    }

    if (scopeStack.top()->type != NodeType::Root) throw SyntaxError("Unexpected end of input: Unclosed loop '['.");

    return root;
}