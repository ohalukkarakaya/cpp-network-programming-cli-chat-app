#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h> // close() için
#include <cstring>  // memset() için

#include "development/global_variables/global_variables.h"

#include "development/helpers/get_ip_adress/include/getIpAdress.h"
#include "development/helpers/random_bytes/include/random_bytes.h"
#include "development/helpers/join_a_room/include/join_a_room.h"

#define BUFFER_SIZE 1024

int main() {
  mainUserId = generateRandomBytesHex(10);
  std::string serverIp = "127.0.0.1";
  std::string ipAdress = getIPAddress();

  join_a_room(mainUserId, serverIp, ipAdress);

  // to listen incoming
  //std::thread messageThread(processIncomingMessages, sock);

  // end thread
  //messageThread.join(); // Thread'in tamamlanmasını bekle
  return 0;
}
