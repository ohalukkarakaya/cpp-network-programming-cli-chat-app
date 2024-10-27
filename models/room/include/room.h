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
    Room() : room_id("") {}

  void set_room_id(std::string &room_id);
  void notify_users_on_join( std::string &user_ip );
  void user_joined(const std::string &user_id, const std::string &user_ip, const bool should_give_notification = true);
  void user_left(const std::string &user_id);
  void add_message(const std::string &sender_id, const std::string &content);
  void send_message(const std::string &sender_id, const std::string &content);
  void update_member_ip(const std::string &sender_id, const std::string &new_ip);

  [[nodiscard]] const std::string &get_room_id() const;
  const std::vector<RoomMember> &get_members() const;
  const std::vector<Message> &get_messages() const;

private:
  std::string room_id;
  std::vector<RoomMember> members;
  std::vector<Message> messages;
};

#endif // ROOM_H
