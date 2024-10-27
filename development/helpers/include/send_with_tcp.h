#ifndef SENDWITHTCP_H
#define SENDWITHTCP_H

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int send_with_tcp(int port, const std::string &ip, const std::string &message, const std::string &type = "message");

#endif // SENDWITHTCP_H
