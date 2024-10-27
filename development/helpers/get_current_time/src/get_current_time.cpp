#include "../include/get_current_time.h"

std::string getCurrentTimeAsString()
{
    // Şu anki zamanı al
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Zamanı formatlayarak stringe çevir
    std::stringstream timeStream;
    timeStream << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S");

    return timeStream.str();
}
