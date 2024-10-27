#ifndef JOIN_A_ROOM_H
#define JOIN_A_ROOM_H

#include <iostream>

#include "../../global_variables/global_variables.h"

#include "../../../models/include/room.h"

#include "send_with_tcp.h"
#include "parse_server_response.h"
#include "parse_user_info.h"
#include "get_room_id.h"

void join_a_room(const std::string &main_user_id, const std::string &server_ip, std::string &ip_address);

#endif //JOIN_A_ROOM_H
