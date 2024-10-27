#include "../../models/include/room.h"
#include "global_variables.h"

Room selected_room;

Room& get_selected_room() {
    return selected_room;
}

std::string main_user_id;

std::atomic<bool> is_running{true};

int join_socket;

std::string current_ip_address;