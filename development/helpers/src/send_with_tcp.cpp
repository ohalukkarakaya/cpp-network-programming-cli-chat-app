#include "../include/send_with_tcp.h"

int send_with_tcp(int port, const std::string &ip, const std::string &message, const std::string &type) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Socket creation failed" << std::endl;
    return -1;
  }

  sockaddr_in server_addr{};
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    // Set Server Ip Address
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "Connection to " << ip << " failed" << std::endl;
    close(sock);
    return -1;
  }

  std::string full_message = type + ":" + message;
  send(sock, full_message.c_str(), full_message.size(), 0);

  return sock;
}
