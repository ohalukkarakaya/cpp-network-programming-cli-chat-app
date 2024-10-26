#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#define SERVERIP "127.0.0.1"

#define PORT 9090
#define LISTEN_PORT 8080

#define BUFFER_SIZE 1024

#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define ITALIC_LIGHT_GRAY "\033[3;37m"
#define RESET "\033[0m"

#include <string>

class Room;

extern Room &getSelectedRoom();
extern std::string mainUserId;
extern std::atomic<bool> isRunning;

extern std::string currentIpAddress;

extern int join_socket;

#endif // GLOBAL_VARIABLES_H
