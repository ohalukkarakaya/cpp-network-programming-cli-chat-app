#ifndef PROCESS_INCOMING_MESSAGES_H
#define PROCESS_INCOMING_MESSAGES_H

#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif

#include "../../global_variables/global_variables.h"

#include "parse_request_data.h"
#include "process_incoming_command.h"
#include "receive_audio_with_tcp.h"

#include "../../../models/include/request_data.h"

void process_incoming_messages(std::string &ip_address);

#endif // PROCESS_INCOMING_MESSAGES_H
