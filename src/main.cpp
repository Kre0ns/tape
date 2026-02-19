#include <fstream>

#include "REPL.h"

void printUsage();

int main(int argc, char* argv[])
{
    std::vector<std::string_view> args(argv, argv + argc);

    if (argc == 1)
    {
        REPL repl;
        repl.init();
    }
    else if (argc == 2)
    {
        std::string filename(args[1]);

        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Cannot open file: " << filename << std::endl;
            printUsage();
            return 1;
        }

        Runner runner;

        runner.run(file);
    }
    else
    {
        std::cerr << "Too many arguments." << std::endl;
        printUsage();
        return 1;
    }

    return 0;
}

void printUsage()
{
    std::cerr << "Usage:" << std::endl;
    std::cerr << "  tape            -> start REPL" << std::endl;
    std::cerr << "  tape <file>     -> run script from file" << std::endl;
}