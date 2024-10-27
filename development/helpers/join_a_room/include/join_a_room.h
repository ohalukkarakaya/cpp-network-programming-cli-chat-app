#ifndef JOIN_A_ROOM_H
#define JOIN_A_ROOM_H

#include <iostream>

#include "../../../global_variables/global_variables.h"

#include "../../../../models/room/include/room.h"

#include "../../send_with_tcp/include/send_with_tcp.h"
#include "../../parse_server_response/parse_server_response.h"
#include "../../parse_server_response/parse_user_info/parse_user_info.h"
#include "../../../get_room_id/include/getRoomId.h"

void join_a_room(const std::string &mainUserId, const std::string &serverIp, std::string &ipAdress);

#endif //JOIN_A_ROOM_H
