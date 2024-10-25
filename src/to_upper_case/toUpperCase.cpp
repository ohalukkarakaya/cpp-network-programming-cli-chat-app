//
// Created by Ö. Haluk KARAKAYA on 23.09.2024.
//

#include "../../include/to_upper_case/toUpperCase.h"

std::string toUpperCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return result;
}
