//
// Created by Ö. Haluk KARAKAYA on 22.10.2024.
//

#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_JOIN_A_ROOM_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_JOIN_A_ROOM_H

#include <iostream>

#include "../../../global_variables/global_variables.h"

#include "../../../../models/room/include/room.h"

#include "../../send_to_ip/include/sendToIp.h"
#include "../../parse_server_response/parse_server_response.h"
#include "../../parse_server_response/parse_user_info/parse_user_info.h"
#include "../../../get_room_id/include/getRoomId.h"

void join_a_room(const std::string &mainUserId, const std::string &serverIp, std::string &ipAdress);

#endif //CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_JOIN_A_ROOM_H
