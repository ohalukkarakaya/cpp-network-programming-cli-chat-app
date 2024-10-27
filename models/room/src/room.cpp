#include "../include/room.h"

void Room::set_room_id(std::string &new_room_id)
{
    room_id = new_room_id;
}

void Room::notify_users_on_join( std::string &user_ip )
{
    std::string message = "{userId: " + main_user_id + "," + "userIp: " + user_ip + "}";
    for( const auto &member : members )
    {
        if(member.get_user_id() != main_user_id)
        {
            send_with_tcp(PORT, member.get_user_ip(), message, "NOTIFICATION");
        }
    }
}

void Room::user_joined(const std::string &user_id, const std::string &user_ip, const bool should_give_notification)
{
  members.emplace_back(user_id, user_ip);
  if (main_user_id != user_id && should_give_notification)
  {
    std::cout << "\033[33m" << user_id << "\033[1;34m" << " joined chat in room " << "\033[33m" << room_id << "\033[0m" << std::endl;
  }
}

void Room::user_left(const std::string &user_id)
{
  auto it = std::remove_if(
   members.begin(), members.end(),
   [&user_id](const RoomMember &member)
   {
     return member.get_user_id() == user_id;
   });

  if (it != members.end())
  {
    members.erase(it, members.end());
    std::cout << "\033[33m" << user_id << BOLD_RED << " left chat in room " << "\033[33m" << room_id << RESET << std::endl;

    if ( members.empty() )
    {
      std::cout << BOLD_RED << "Room " << room_id << " is now empty and will be deleted." << RESET << std::endl;
    }
  }
}

void Room::add_message(const std::string &sender_id, const std::string &content) {
  messages.emplace_back(sender_id, content);
}

void Room::send_message(const std::string &sender_id, const std::string &content) {
  add_message(sender_id, content);

  std::string message = sender_id + ": " + content;
  for (const auto &member : members) {
    if (member.get_user_id() != sender_id) {
        send_with_tcp(PORT, member.get_user_ip(), message);
    }
  }
}

void Room::update_member_ip(const std::string &sender_id, const std::string &new_ip)
{
    auto it = std::find_if(members.begin(), members.end(),
                           [&sender_id](const RoomMember &member) {
                               return member.get_user_id() == sender_id;
                           });

    if (it != members.end()) {
        it->set_user_ip(new_ip);
        std::cout << "Updated IP for user " << sender_id << " to " << new_ip << std::endl;
    } else {
        std::cout << "User " << sender_id << " not found in room " << room_id << std::endl;
    }
}

const std::string &Room::get_room_id() const { return room_id; }

const std::vector<RoomMember> &Room::get_members() const { return members; }

const std::vector<Message> &Room::get_messages() const { return messages; }
