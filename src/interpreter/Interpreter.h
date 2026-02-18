#pragma once

#include "AST.h"
#include "MachineState.h"

class Interpreter
{
public:
    Interpreter(MachineState& state);

    void run(const ASTNode& astRoot);

    bool getNeedsNewline() const;
private:
    struct ExecutionFrame
    {
        const ASTNode* node;
        size_t childIndex;
    };

    MachineState& _state;
    bool _needsNewline;
};
