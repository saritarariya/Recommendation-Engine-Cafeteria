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

bool Utility::isValidType(const std::string &type)
{
    static const std::vector<std::string> validTypes = {"Vegetarian", "Non Vegetarian", "Eggetarian"};
    return std::find(validTypes.begin(), validTypes.end(), type) != validTypes.end();
}

bool Utility::isValidSpiceLevel(const std::string &spiceLevel)
{
    static const std::vector<std::string> validSpiceLevels = {"High", "Medium", "Low"};
    return std::find(validSpiceLevels.begin(), validSpiceLevels.end(), spiceLevel) != validSpiceLevels.end();
}

bool Utility::isValidCuisine(const std::string &cuisine)
{
    static const std::vector<std::string> validCuisines = {"North Indian", "South Indian", "Other"};
    return std::find(validCuisines.begin(), validCuisines.end(), cuisine) != validCuisines.end();
}

std::string Utility::getValidatedInput(const std::string &prompt, const std::string &errorMessage, bool (*isValid)(const std::string &))
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty() && isValid(input))
        {
            return input;
        }
        std::cout << errorMessage << std::endl;
    }
}

bool Utility::isValidCategory(const std::string &category)
{
    static const std::vector<std::string> validCategories = {"Breakfast", "Lunch", "Dinner"};
    return std::find(validCategories.begin(), validCategories.end(), category) != validCategories.end();
}
