#include <iostream>

#include "development/get_room_id/include/getRoomId.h"
#include "development/helpers/get_ip_adress/include/getIpAdress.h"
#include "development/helpers/random_bytes/include/random_bytes.h"
#include "models/room/include/room.h"

#define PORT 9090

int main() {
  std::string randomId = generateRandomBytesHex(10);
  std::string ipAdress = getIPAddress();

  int sock = 0;
  struct sockaddr_in serv_addr;
  // char* message = "JOIN/user123/192.168.1.1/room1";
  const char* message = "GETROOMS/0/0/0";
  char buffer[1024] = {0};

  // Socket oluşturma
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

    memset(&serv_addr, 0, sizeof(serv_addr)); // Servis adresini sıfırlayın
    serv_addr.sin_family = AF_INET; // AIPv4
    serv_addr.sin_port = htons(PORT); // Port numarasını ayarlayın

    // Sunucu IP adresini ayarla
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Sunucuya bağlan
    int connection = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (connection < 0) {
        std::cerr << "Connection Failed: " << connection << std::endl;
        return -1;
    }

    // Mesaj gönder
    send(sock, message, strlen(message), 0);
    std::cout << "Message sent: " << message << std::endl;

    // Sunucudan yanıt al
    int valread = read(sock, buffer, 1024);
    std::cout << "Response from server: " << buffer << std::endl;

    // Socket kapat
    close(sock);

  std::cout << "\033[33mYour User ID: \033[34m" << randomId << "\033[0m" << std::endl;

  const int   maxLength       = 10;
  std::string userInputRoomId = getRoomId(maxLength);

  std::system("clear");

  Room room(userInputRoomId);
  room.userJoined(randomId, randomId, ipAdress);

  return 0;
}
