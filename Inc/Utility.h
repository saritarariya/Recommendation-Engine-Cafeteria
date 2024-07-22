#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

class Utility
{
public:
    static std::string getNonEmptyInput(const std::string &prompt, const std::string &errorMessage);
    static std::string getNumericInput(const std::string &prompt, const std::string &errorMessage);
    static std::string getBinaryInput(const std::string &prompt, const std::string &errorMessage);
};

#endif
