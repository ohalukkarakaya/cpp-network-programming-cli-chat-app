#include "../../models/room/include/room.h"
#include "global_variables.h"

Room selected_room;

Room& getSelectedRoom() {
    return selected_room;
}

std::string mainUserId;

std::atomic<bool> isRunning{true};

int join_socket;

std::string currentIpAddress;