#include <iostream>

#include "development/get_room_id/include/getRoomId.h"
#include "development/helpers/get_ip_adress/include/getIpAdress.h"
#include "development/helpers/random_bytes/include/random_bytes.h"
#include "models/room/include/room.h"

int main() {
  std::string randomId = generateRandomBytesHex(10);
  std::string ipAdress = getIPAddress();


  std::cout << "\033[33mYour User ID: \033[34m" << randomId << "\033[0m" << std::endl;

  const int   maxLength       = 10;
  std::string userInputRoomId = getRoomId(maxLength);

  std::system("clear");

  Room room(userInputRoomId);
  room.userJoined(randomId, randomId, ipAdress);

  return 0;
}
