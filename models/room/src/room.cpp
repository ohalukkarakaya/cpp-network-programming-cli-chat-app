// TO DO: Members boş kalıyor onu doldurmamızın bir yolu olmalı

#include "../include/room.h"

void Room::setRoomId(std::string &newRoomId)
{
    roomId = newRoomId;
}

void Room::notifyUsersOnJoin( std::string &userIp )
{
    std::string message = "{userId: " + mainUserId + "," + "userIp: " + userIp + "}";
    for( const auto &member : members )
    {
        if(member.getUserId() != mainUserId)
        {
            send_with_tcp(PORT, member.getUserIp(), message, "NOTIFICATION");
        }
    }
}

void Room::userJoined(const std::string &userId, const std::string &userIp, const bool shouldGiveNotification)
{
  members.emplace_back(userId, userIp);
  if (mainUserId != userId && shouldGiveNotification)
  {
    std::cout << "\033[33m" << userId << "\033[1;34m" << " joined chat in room " << "\033[33m" << roomId << "\033[0m" << std::endl;
  }
}

void Room::userLeft(const std::string &userId)
{
  auto it = std::remove_if(
   members.begin(), members.end(),
   [&userId](const RoomMember &member)
   {
     return member.getUserId() == userId;
   });

  if (it != members.end())
  {
    members.erase(it, members.end());
    std::cout << "\033[33m" << userId << BOLD_RED << " left chat in room " << "\033[33m" << roomId << RESET << std::endl;

    if ( members.empty() )
    {
      std::cout << BOLD_RED << "Room " << roomId << " is now empty and will be deleted." << RESET << std::endl;
    }
  }
}

void Room::addMessage(const std::string &senderId, const std::string &content) {
  messages.emplace_back(senderId, content);
}

void Room::sendMessage(const std::string &senderId,
                       const std::string &content) {
  addMessage(senderId, content);

  std::string message = senderId + ": " + content;
  for (const auto &member : members) {
    if (member.getUserId() != senderId) {
        send_with_tcp(PORT, member.getUserIp(), message);
    }
  }
}

void Room::updateMemberIp(const std::string &senderId, const std::string &newIp)
{
    auto it = std::find_if(members.begin(), members.end(),
                           [&senderId](const RoomMember &member) {
                               return member.getUserId() == senderId;
                           });

    if (it != members.end()) {
        it->setUserIp(newIp);
        std::cout << "Updated IP for user " << senderId << " to " << newIp << std::endl;
    } else {
        std::cout << "User " << senderId << " not found in room " << roomId << std::endl;
    }
}

const std::string &Room::getRoomId() const { return roomId; }

const std::vector<RoomMember> &Room::getMembers() const { return members; }

const std::vector<Message> &Room::getMessages() const { return messages; }
