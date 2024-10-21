//
// Created by Ö. Haluk KARAKAYA on 21.10.2024.
//

#include "parse_server_response.h"

std::vector<std::string> parse_server_response( const std::string& response )
{
    const std::string nullSuffix = " :N";
    std::vector<std::string> values;
    std::string token;
    std::stringstream ss(response);

    if (response.size() >= nullSuffix.size() && response.compare(response.size() - nullSuffix.size(), nullSuffix.size(), nullSuffix) == 0)
    {
        values.push_back(response.substr(0, response.size() - nullSuffix.size()));
        return values;
    }

    // Virgül ile ayrılmış değerleri al
    while (std::getline(ss, token, ',')) {
        if (!token.empty()) { // Boş değerleri atla
            values.push_back(token);
        }
    }
    return values;
}