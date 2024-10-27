#ifndef ROOM_H
#define ROOM_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../../../development/global_variables/global_variables.h"

#include "../../../development/helpers/send_with_tcp/include/send_with_tcp.h"
#include "../../message/include/message.h"
#include "../../room_member/include/room_member.h"

class Room {
public:
    Room() : roomId("") {}

  void setRoomId(std::string &roomId);
  void notifyUsersOnJoin( std::string &userIp );
  void userJoined(const std::string &userId, const std::string &userIp, const bool shouldGiveNotification = true);
  void userLeft(const std::string &userId);
  void addMessage(const std::string &senderId, const std::string &content);
  void sendMessage(const std::string &senderId, const std::string &content);
  void updateMemberIp(const std::string &senderId, const std::string &newIp);

  [[nodiscard]] const std::string &getRoomId() const;
  const std::vector<RoomMember> &getMembers() const;
  const std::vector<Message> &getMessages() const;

private:
  std::string roomId;
  std::vector<RoomMember> members;
  std::vector<Message> messages;
};

#endif // ROOM_H
