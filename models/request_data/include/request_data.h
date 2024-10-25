#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_REQUEST_DATA_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_REQUEST_DATA_H

#include <iostream>

#include "../../command/include/command.h"

class RequestData {
public:
    RequestData( Command command, std::string senderId, std::string commandTime );

    Command& getCommand();
    std::string& getSenderId();
    std::string& getCommandTime();

private:
    Command& command;
    std::string senderId;
    std::string commandTime;
};

#endif //CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_REQUEST_DATA_H
