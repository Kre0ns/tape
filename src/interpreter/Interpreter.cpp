#include "Interpreter.h"

#include <memory>
#include <stack>
#include <cstdint>
#include <iostream>
#include <limits>
#include <cstdio>
#include <format>

#include "RuntimeError.h"

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif


namespace {
    char getRawChar()
    {
#ifdef _WIN32
        return static_cast<char>(_getch());
#else
        char buffer = 0;

        struct termios oldAttr;
        struct termios newAttr;

        tcgetattr(STDIN_FILENO, &oldAttr);
        newAttr = oldAttr;
        newAttr.c_lflag &= ~(ICANON | ECHO);
        newAttr.c_cc[VMIN] = 1;
        newAttr.c_cc[VTIME] = 0;

        tcsetattr(STDIN_FILENO, TCSANOW, &newAttr);

        read(STDIN_FILENO, &buffer, 1);

        tcsetattr(STDIN_FILENO, TCSANOW, &oldAttr);

        return buffer;
#endif
    }
}

Interpreter::Interpreter(MachineState& state)
    : _state(state), _needsNewline(false)
{
}

void Interpreter::run(const ASTNode& astRoot)
{
    std::stack<ExecutionFrame> frameStack;
    frameStack.push({&astRoot, 0});

    this->_needsNewline = false;

    while (!frameStack.empty())
    {
        ExecutionFrame& currentFrame = frameStack.top();
        const ASTNode* currentParent = currentFrame.node;

        if (currentFrame.childIndex >= currentParent->children.size())
        {
            if (currentParent->type == NodeType::Loop && this->_state.tape[this->_state.pointer] != 0)
            {
                currentFrame.childIndex = 0;
                continue; 
            }

            frameStack.pop();
            continue;
        }

        ASTNode* currentChild = currentParent->children[currentFrame.childIndex].get();

        currentFrame.childIndex++;

        switch (currentChild->type)
        {
            using enum NodeType;

            case Inc:
                this->_state.tape[this->_state.pointer]++;
                break;

            case Dec:
                this->_state.tape[this->_state.pointer]--;
                break;

            case MoveLeft:
                if (this->_state.pointer <= 0) 
                {
                    std::string msg = std::format("'<' at {}:{} moves out of bounds", currentChild->line, currentChild->column);
                    throw RuntimeError(msg);
                }

                this->_state.pointer--;
                break;

            case MoveRight:
                if (this->_state.pointer >= MachineState::TapeSize - 1)
                {
                    std::string msg = std::format("'>' at {}:{} moves out of bounds", currentChild->line, currentChild->column);
                    throw RuntimeError(msg);
                }

                this->_state.pointer++;
                break;
            
            case Input:
                {
                    char input = getRawChar();

                    this->_state.tape[this->_state.pointer] = static_cast<uint8_t>(input);
                }
                break;
                
            case Output:
                {
                    uint8_t output = static_cast<uint8_t>(this->_state.tape[this->_state.pointer]); 

                    std::cout.put(output);
                    std::cout.flush();
                    
                    this->_needsNewline = output == '\n' ? false : true;
                    break;    
                }    

            case Loop:
                if (this->_state.tape[this->_state.pointer] != 0) frameStack.push({currentChild, 0});
                break;

            default:
                break;
        }
    }
}

bool Interpreter::getNeedsNewline() const
{
    return this->_needsNewline;
}