#include "../include/parse_server_response.h"

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

    // Get comma separated values
    while (std::getline(ss, token, ',')) {
        // Clean up spaces and quotation marks
        token.erase(std::remove_if(token.begin(), token.end(), [](unsigned char c) {
            return std::isspace(c) || c == '\"'; // Remove extra spaces and quotation marks
        }), token.end());

        if (!token.empty()) { // Skip null values
            values.push_back(token);
        }
    }
    return values;
}