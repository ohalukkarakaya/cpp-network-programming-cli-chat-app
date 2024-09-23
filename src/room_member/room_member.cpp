//
// Created by Ö. Haluk KARAKAYA on 23.09.2024.
//

#include "../../include/room_member/RoomMember.h"

RoomMember::RoomMember(const std::string& userId, const std::string& userIp)
        : userId(userId), userIp(userIp) {}

const std::string& RoomMember::getUserId() const {
    return userId;
}

const std::string& RoomMember::getUserIp() const {
    return userIp;
}