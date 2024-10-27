#include "../include/room_member.h"

#include <utility>

RoomMember::RoomMember(std::string user_id, std::string user_ip)
    : user_id(std::move(user_id)), user_ip(std::move(user_ip)),
      join_date(std::time(nullptr)) {}


void RoomMember::set_user_ip( const std::string& new_ip_address )
{
    user_ip = new_ip_address;
}

const std::string &RoomMember::get_user_id() const { return user_id; }

const std::string &RoomMember::get_user_ip() const { return user_ip; }

time_t RoomMember::get_join_date() const { return join_date; }
