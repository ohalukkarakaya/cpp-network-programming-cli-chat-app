//
// Created by Ö. Haluk KARAKAYA on 22.10.2024.
//

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