#ifndef ROOMMEMBER_H
#define ROOMMEMBER_H

#include <ctime>
#include <iostream>
#include <string>

class RoomMember {
public:
  RoomMember(std::string userId, std::string userIp);

  void set_user_ip( const std::string& new_ip_address );
  [[nodiscard]] const std::string &get_user_id() const;
  [[nodiscard]] const std::string &get_user_ip() const;
  time_t get_join_date() const;

private:
  std::string user_id;
  std::string user_ip;
  time_t join_date;
};

#endif // ROOMMEMBER_H
