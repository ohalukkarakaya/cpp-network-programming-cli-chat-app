#include "../include/room_member.h"

#include <utility>

RoomMember::RoomMember(std::string userId, std::string userIp)
    : userId(std::move(userId)), userIp(std::move(userIp)),
      joinDate(std::time(nullptr)) {}

const std::string &RoomMember::getUserId() const { return userId; }

const std::string &RoomMember::getUserIp() const { return userIp; }

time_t RoomMember::getJoinDate() const { return joinDate; }
