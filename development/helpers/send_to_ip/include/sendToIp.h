#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SENDTOIP_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SENDTOIP_H

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int sendToIp(const std::string &ip, const std::string &message, const std::string &type = "message");

#endif // CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_SENDTOIP_H
