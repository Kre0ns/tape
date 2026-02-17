#include "Interpreter.h"

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
        case NodeType::Inc:
            this->_state.tape[this->_state.pointer]++;
            break;

        case NodeType::Dec:
            this->_state.tape[this->_state.pointer]--;
            break;

        case NodeType::MoveLeft:
            if (this->_state.pointer <= 0) throw RuntimeError("Illegal operation '<' - Moves out of bounds");

            this->_state.pointer--;
            break;

        case NodeType::MoveRight:
            if (this->_state.pointer >= this->_state.TapeSize - 1) throw RuntimeError("Illegal operation '>' - Moves out of bounds");

            this->_state.pointer++;
            break;
        
        case NodeType::Input:
            {
                int input = std::cin.get();

                if (input == EOF) 
                {
                    this->_state.tape[this->_state.pointer] = 0;
                    std::cin.clear();
                    std::clearerr(stdin);
                }
                else
                {
                    this->_state.tape[this->_state.pointer] = static_cast<uint8_t>(input);

                    if (input != '\n') 
                    {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }
            break;
            
        case NodeType::Output:
            {
                uint8_t output = static_cast<uint8_t>(this->_state.tape[this->_state.pointer]); 

                std::cout.put(output);
                
                this->_needsNewline = output == '\n' ? false : true;
                break;    
            }    

        case NodeType::Loop:
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