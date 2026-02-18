#include "Runner.h"

#include "Parser.h"
#include "Error.h"

Runner::Runner()
    : _interpreter(_state)
{
}

void Runner::run(std::istream& input)
{
    Lexer lexer(input);

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