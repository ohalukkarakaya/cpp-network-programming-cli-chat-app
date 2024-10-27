#ifndef REQUEST_DATA_H
#define REQUEST_DATA_H

#include <iostream>

#include "command.h"

class RequestData {
public:
    RequestData(Command command, std::string sender_id, std::string sender_ip, std::string message, std::string command_time);

    Command& get_command();
    std::string& get_sender_id();
    std::string& get_sender_ip();
    std::string& get_message();
    std::string& get_command_time();

private:
    Command command;
    std::string sender_id;
    std::string sender_ip;
    std::string message;
    std::string command_time;
};

#endif //REQUEST_DATA_H
