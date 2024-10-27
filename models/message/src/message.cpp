#include "../include/message.h"

Message::Message(const std::string &sender_id, const std::string &content)
    : sender_id(sender_id), content(content), time_stamp(current_date_time()) {}

std::string Message::get_sender_id() const { return sender_id; }

std::string Message::get_content() const { return content; }

std::string Message::get_time_stamp() const { return time_stamp; }

std::string Message::current_date_time() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::ostringstream oss;
  oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  return oss.str();
}
