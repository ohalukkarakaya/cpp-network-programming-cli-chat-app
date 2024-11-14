#include "../include/get_current_time.h"

std::string get_current_time_as_string()
{
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    // return time to string with format
    std::stringstream time_stream;
    time_stream << std::put_time(std::localtime(&current_time), "%Y-%m-%d %H:%M:%S");

    return time_stream.str();
}
