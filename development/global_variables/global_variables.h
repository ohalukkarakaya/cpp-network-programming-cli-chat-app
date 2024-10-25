//
// Created by Ö. Haluk KARAKAYA on 22.10.2024.
//

#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_GLOBAL_VARIABLES_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_GLOBAL_VARIABLES_H

#define PORT 9090
#define BUFFER_SIZE 1024

#include <string>

class Room;

extern Room &getSelectedRoom();
extern std::string mainUserId;
inline volatile bool running;

#endif // CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_GLOBAL_VARIABLES_H
