#include "../include/request_data.h"

RequestData::RequestData(Command command, std::string senderId, std::string commandTime)
        : command(std::move(command)), senderId(std::move(senderId)), commandTime(std::move(commandTime)) {}

Command& RequestData::getCommand() {
    return command;
}

std::string& RequestData::getSenderId() {
    return senderId;
}

std:: string& RequestData::getCommandTime() {
    return commandTime;
}
