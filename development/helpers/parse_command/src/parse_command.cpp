#include "../include/parse_command.h"

RequestData* parse_request_data( std::string& rawRequest )
{
    std::string cmd, senderId;

    // Kalan kısmı '/' karakterlerine göre parçala
    size_t firstSlash  = rawRequest.find('/');
    size_t secondSlash = rawRequest.find('/',  firstSlash  + 1);

    if (firstSlash == std::string::npos || secondSlash == std::string::npos)
    {
        std::cerr << "Missing Parameter" << std::endl;
        running = false;
        return new RequestData( UNKNOWN, "", "" );
    }

    cmd = rawRequest.substr(0, firstSlash);

    Command command = getCommandType( cmd );
    senderId = rawRequest.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    std::string commandTime = getCurrentTimeAsString();

    std::cout << "request received: " << rawRequest << std::endl;

    return new RequestData( command, senderId, commandTime );
}
