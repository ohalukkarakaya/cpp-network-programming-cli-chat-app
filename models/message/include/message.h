#ifndef MESSAGE_H
#define MESSAGE_H

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

class Message {
public:
  Message(const std::string &senderId, const std::string &content);

  std::string getSenderId() const;
  std::string getContent() const;
  std::string getTimestamp() const;

private:
  std::string senderId;
  std::string content;
  std::string timestamp;

  static std::string currentDateTime();
};

#endif // MESSAGE_H
