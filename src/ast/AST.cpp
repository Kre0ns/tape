#include "AST.h"

ASTNode::ASTNode(NodeType t, int l, int c) 
    : type(t), line(l), column(c)
{
}