#include "../include/message.h"

Message::Message(const std::string &senderId, const std::string &content)
    : senderId(senderId), content(content), timestamp(currentDateTime()) {}

std::string Message::getSenderId() const { return senderId; }

std::string Message::getContent() const { return content; }

std::string Message::getTimestamp() const { return timestamp; }

std::string Message::currentDateTime() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::ostringstream oss;
  oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  return oss.str();
}
