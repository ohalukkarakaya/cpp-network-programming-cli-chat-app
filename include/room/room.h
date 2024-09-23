//
// Created by Ö. Haluk KARAKAYA on 23.09.2024.
//

#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "../room_member/roomMember.h"
#include "../message/message.h"
#include "../send_to_ip/sendToIp.h"

class Room {
public:
    Room(const std::string& id);

    void userJoined(const std::string& mainUserId, const std::string& userId, const std::string& userIp);
    void userLeft(const std::string& userId);
    void addMessage(const std::string& senderId, const std::string& content);
    void sendMessage(const std::string& senderId, const std::string& content);

    [[nodiscard]] const std::string& getRoomId() const;
    const std::vector<RoomMember>& getMembers() const;
    const std::vector<Message>& getMessages() const;

private:
    std::string roomId;
    std::vector<RoomMember> members;
    std::vector<Message> messages;
};

#endif // ROOM_H
