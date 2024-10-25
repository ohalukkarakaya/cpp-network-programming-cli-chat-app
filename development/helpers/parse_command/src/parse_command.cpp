#include "../include/parse_command.h"

RequestData* parse_request_data(std::string& rawRequest) {
    std::string type, cmd, senderId, senderIp, message;

    size_t firstColon = rawRequest.find(':');
    if (firstColon == std::string::npos) {
        std::cerr << "Missing Parameter" << std::endl;
        isRunning = false;
        return new RequestData(UNKNOWN, "", "", "", "");
    }

    size_t secondColon = rawRequest.find(':', firstColon + 1);
    if (secondColon == std::string::npos) {
        std::cerr << "Missing Parameter" << std::endl;
        isRunning = false;
        return new RequestData(UNKNOWN, "", "", "", "");
    }

    size_t firstSlash = rawRequest.find('/', secondColon + 1);
    if (firstSlash == std::string::npos) {
        std::cerr << "Missing Parameter" << std::endl;
        isRunning = false;
        return new RequestData(UNKNOWN, "", "", "", "");
    }

    size_t secondSlash = rawRequest.find('/', firstSlash + 1);

    type = rawRequest.substr(0, firstColon);
    cmd = rawRequest.substr(firstColon + 1, secondColon - firstColon - 1);
    senderId = rawRequest.substr(secondColon + 1, firstSlash - secondColon - 1);
    senderIp = rawRequest.substr(firstSlash + 1, secondSlash != std::string::npos ? (secondSlash - firstSlash - 1) : std::string::npos);

    message = secondSlash != std::string::npos ? rawRequest.substr(secondSlash + 1) : "";

    Command command = getCommandType(cmd);

    std::string commandTime = getCurrentTimeAsString();

    return new RequestData(command, senderId, senderIp, message, commandTime);
}