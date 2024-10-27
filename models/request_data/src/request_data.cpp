#include "../include/request_data.h"

RequestData::RequestData(Command command, std::string sender_id, std::string sender_ip, std::string message, std::string command_time)
        : command(command), sender_id(std::move(sender_id)), sender_ip(std::move(sender_ip)), message(std::move(message)), command_time(std::move(command_time)) {}

Command& RequestData::get_command() {
    return command;
}

std::string& RequestData::get_sender_id() {
    return sender_id;
}

std::string& RequestData::get_sender_ip() {
    return sender_ip;
}

std::string& RequestData::get_message() {
    return message;
}

std:: string& RequestData::get_command_time() {
    return command_time;
}
