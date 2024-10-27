#ifndef MESSAGE_H
#define MESSAGE_H

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

class Message {
public:
  Message(const std::string &sender_id, const std::string &content);

  std::string get_sender_id() const;
  std::string get_content() const;
  std::string get_time_stamp() const;

private:
  std::string sender_id;
  std::string content;
  std::string time_stamp;

  static std::string current_date_time();
};

#endif // MESSAGE_H
