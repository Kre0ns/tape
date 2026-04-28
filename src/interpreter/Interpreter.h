#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

#include "AST.h"

class Interpreter
{
public:
    Interpreter();

    void run(const ASTNode& astRoot);

    bool getNeedsNewline() const;
private:
    static constexpr std::size_t TAPE_SIZE = 30000;
    static constexpr std::uint8_t INITIAL_CELL_VALUE = 0;
    static constexpr std::size_t INITIAL_POINTER = 0;

    struct ExecutionFrame
    {
        const ASTNode* node;
        size_t childIndex;
    };
    
    std::vector<std::uint8_t> _tape;
    std::size_t _pointer;

    bool _needsNewline;
};
