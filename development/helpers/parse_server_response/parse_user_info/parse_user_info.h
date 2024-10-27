#ifndef PARSE_USER_INFO_H
#define PARSE_USER_INFO_H

#include "../../../../models/room_member/include/room_member.h"

std::vector<RoomMember> parse_user_info( const std::string& user_info_list );

#endif //PARSE_USER_INFO_H
