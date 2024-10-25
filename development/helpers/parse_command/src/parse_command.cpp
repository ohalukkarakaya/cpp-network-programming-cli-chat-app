#include "../include/parse_command.h"

RequestData* parse_request_data( std::string& rawRequest )
{
    std::string cmd, senderId, message;

    // parse command, sender id and message with '/'
    size_t firstSlash  = rawRequest.find('/');
    size_t secondSlash = rawRequest.find('/',  firstSlash  + 1);
    size_t thirdSlash = rawRequest.find('/',  secondSlash  + 1);

    if (firstSlash == std::string::npos || secondSlash == std::string::npos)
    {
        std::cerr << "Missing Parameter" << std::endl;
        isRunning = false;
        return new RequestData( UNKNOWN, "", "" );
    }

    cmd = rawRequest.substr(0, firstSlash);
    Command command = getCommandType( cmd );

    senderId = rawRequest.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    message = rawRequest.substr(secondSlash +1, thirdSlash - secondSlash - 1);
    std::string commandTime = getCurrentTimeAsString();

    std::cout << "request received: " << rawRequest << std::endl;

    return new RequestData( command, senderId, commandTime );
}