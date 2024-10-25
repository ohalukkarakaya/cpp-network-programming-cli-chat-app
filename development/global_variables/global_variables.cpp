//
// Created by Ö. Haluk KARAKAYA on 22.10.2024.
//

#include "../../models/room/include/room.h"
#include "global_variables.h"

// Global bir Room nesnesi
Room selected_room;

Room& getSelectedRoom() {
    return selected_room;
}

std::string mainUserId;