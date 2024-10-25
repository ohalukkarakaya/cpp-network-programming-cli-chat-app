#ifndef PROCESS_INCOMING_MESSAGES_H
#define PROCESS_INCOMING_MESSAGES_H

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

#ifdef _WIN32
#include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif

#include "../../../global_variables/global_variables.h"
#include "../../parse_command/include/parse_command.h"

void process_incoming_messages( std::string& ipAddress );

#endif //PROCESS_INCOMING_MESSAGES_H
