#include "Utility.h"

std::string Utility::getNonEmptyInput(const std::string &prompt, const std::string &errorMessage)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty())
        {
            return input;
        }
        std::cout << errorMessage << " Please press enter to provide input again." << std::endl;
    }
}

std::string Utility::getNumericInput(const std::string &prompt, const std::string &errorMessage)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty() && std::all_of(input.begin(), input.end(), ::isdigit))
        {
            return input;
        }
        std::cout << errorMessage << std::endl;
    }
}

std::string Utility::getBinaryInput(const std::string &prompt, const std::string &errorMessage)
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input == "1" || input == "0")
        {
            return input;
        }
        std::cout << errorMessage << std::endl;
    }
}
