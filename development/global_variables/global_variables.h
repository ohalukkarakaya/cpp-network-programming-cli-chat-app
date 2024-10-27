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

extern Room &get_selected_room();
extern std::string main_user_id;
extern std::atomic<bool> is_running;

extern std::string current_ip_address;

extern int join_socket;

#endif // GLOBAL_VARIABLES_H
