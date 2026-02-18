#include "REPL.h"

#include <sstream>

REPL::REPL()
    : _runner()
{ 
}

void REPL::init()
{
    std::string input;

    std::cout << "tape " << ReplVersion << std::endl;
    std::cout << "Type \"" << ExitKeyword << "\" to exit" << std::endl;

    while (true)
    {
        std::cout << "tape> ";
        
        if (!std::getline(std::cin, input)) 
        {
            std::cout << std::endl;
            break;
        }

        if (input == ExitKeyword) break;
        
        std::stringstream stringStream(input);

        this->_runner.run(stringStream);
    }
}