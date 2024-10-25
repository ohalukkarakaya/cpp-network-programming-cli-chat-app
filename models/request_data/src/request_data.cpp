#include "../include/request_data.h"

RequestData::RequestData(Command command, std::string senderId, std::string senderIp, std::string message, std::string commandTime)
        : command(command), senderId(std::move(senderId)), senderIp(std::move(senderIp)), message(std::move(message)), commandTime(std::move(commandTime)) {}

Command& RequestData::getCommand() {
    return command;
}

std::string& RequestData::getSenderId() {
    return senderId;
}

std::string& RequestData::getSenderIp() {
    return senderIp;
}

std::string& RequestData::getMessage() {
    return message;
}

std:: string& RequestData::getCommandTime() {
    return commandTime;
}
