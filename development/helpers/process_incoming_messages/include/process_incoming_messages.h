#ifndef PROCESS_INCOMING_MESSAGES_H
#define PROCESS_INCOMING_MESSAGES_H

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_PORT 8080

#include "../../parse_command/include/parse_command.h"

void process_incoming_messages( std::string& ipAddress );

#endif //PROCESS_INCOMING_MESSAGES_H
