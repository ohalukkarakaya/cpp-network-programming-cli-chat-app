#include <iostream>

#include "development/get_room_id/include/getRoomId.h"
#include "development/helpers/get_ip_adress/include/getIpAdress.h"
#include "development/helpers/random_bytes/include/random_bytes.h"
#include "development/helpers/send_to_ip/include/sendToIp.h"
#include "development/helpers/parse_server_response/parse_server_response.h"

#include "models/room/include/room.h"

#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
  std::string randomId = generateRandomBytesHex(10);
  std::string ipAdress = getIPAddress();

  std::string serverIp = "127.0.0.1";
  std::string message;
  message = "GETROOMS/0/0/0";

  char buffer[BUFFER_SIZE] = {0};

  int sock = sendToIp(serverIp, message, "GETROOMS");

  // Sunucudan yanıt al
  int valread = read(sock, buffer, 1024);
  std::vector<std::string> rooms = parse_server_response( buffer );

  std::cout << std::endl;
  std::cout << "\033[1;33mActive Rooms:\033[0m" << std::endl;
  std::cout << std::endl;

  for( const std::string& room_name : rooms ){
      std::cout << "- " << room_name << std::endl;
  }
  std::cout << std::endl;

  // Socket kapat
  close(sock);

  std::cout << "\033[33mYour User ID: \033[34m" << randomId << "\033[0m" << std::endl;

  const int   maxLength       = 10;
  std::string userInputRoomId = getRoomId(maxLength);

  std::system("clear");

  message = "JOINROOM/" + randomId + "/" + ipAdress + "/" + userInputRoomId;
  int joinSock = sendToIp(serverIp, message, "JOINROOM");

  valread = read(sock, buffer, 1024);

  std::cout << "- " << buffer << std::endl;
  // Socket kapat
  close(joinSock);

  Room room(userInputRoomId);
  room.userJoined(randomId, randomId, ipAdress);

  return 0;
}
