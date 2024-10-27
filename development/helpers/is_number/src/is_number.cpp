#include "../include/is_number.h"

bool is_number( const std::string& str )
{
    std::istringstream iss( str );
    float number;
    iss >> number;
    return iss.eof() && !iss.fail();
}