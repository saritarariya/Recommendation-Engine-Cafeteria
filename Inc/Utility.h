#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class Utility
{
public:
    static std::string getNonEmptyInput(const std::string &prompt, const std::string &errorMessage);
    static std::string getNumericInput(const std::string &prompt, const std::string &errorMessage);
    static std::string getBinaryInput(const std::string &prompt, const std::string &errorMessage);
    static bool isValidType(const std::string &type);
    static bool isValidSpiceLevel(const std::string &spiceLevel);
    static bool isValidCuisine(const std::string &cuisine);
    static std::string getValidatedInput(const std::string &prompt, const std::string &errorMessage, bool (*isValid)(const std::string &));
    static bool isValidCategory(const std::string &category);
};

#endif
