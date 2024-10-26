#ifndef ROOMMEMBER_H
#define ROOMMEMBER_H

#include <ctime>
#include <iostream>
#include <string>

class RoomMember {
public:
  RoomMember(std::string userId, std::string userIp);

  void setUserIp( const std::string& new_ip_address );
  [[nodiscard]] const std::string &getUserId() const;
  [[nodiscard]] const std::string &getUserIp() const;
  time_t getJoinDate() const;

private:
  std::string userId;
  std::string userIp;
  time_t joinDate;
};

#endif // ROOMMEMBER_H
