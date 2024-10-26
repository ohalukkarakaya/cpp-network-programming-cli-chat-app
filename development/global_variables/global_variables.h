//
// Created by Ö. Haluk KARAKAYA on 22.10.2024.
//

#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_GLOBAL_VARIABLES_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_GLOBAL_VARIABLES_H

#define PORT 9090
#define LISTEN_PORT 8080

#define BUFFER_SIZE 1024

#define BOLD_RED "\033[1;31m"
#define RESET "\033[0m"

#include <string>

class Room;

extern Room &getSelectedRoom();
extern std::string mainUserId;
extern std::atomic<bool> isRunning;

extern int join_socket;

#endif // CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_GLOBAL_VARIABLES_H
