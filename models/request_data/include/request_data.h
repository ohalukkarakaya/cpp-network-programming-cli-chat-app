#ifndef REQUEST_DATA_H
#define REQUEST_DATA_H

#include <iostream>

#include "../../command/include/command.h"

class RequestData {
public:
    RequestData(Command command, std::string senderId, std::string senderIp, std::string message, std::string commandTime);

    Command& getCommand();
    std::string& getSenderId();
    std::string& getSenderIp();
    std::string& getMessage();
    std::string& getCommandTime();

private:
    Command command;
    std::string senderId;
    std::string senderIp;
    std::string message;
    std::string commandTime;
};

#endif //REQUEST_DATA_H
