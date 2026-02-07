#pragma once

#include <vector>
#include <memory>

enum class NodeType {
    Root,
    Inc, 
    Dec, 
    MoveLeft, 
    MoveRight, 
    Input, 
    Output, 
    Loop 
};

struct ASTNode
{
    NodeType type;
    std::vector<std::unique_ptr<ASTNode>> children;

    ASTNode(NodeType t);
};
