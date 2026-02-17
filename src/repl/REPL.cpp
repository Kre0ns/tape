#include "REPL.h"

REPL::REPL()
    : _interpreter(_state)
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

        Lexer lexer(stringStream);

        Parser parser(lexer);

        try
        {
            std::unique_ptr<ASTNode> ast = parser.parse();

            this->_interpreter.run(*ast);

            if (this->_interpreter.getNeedsNewline()) std::cout << std::endl;
        }
        catch (const Error& e)
        {
            if (this->_interpreter.getNeedsNewline()) std::cout << std::endl;

            std::cout << e.what() << std::endl;
        }

    }
}