#include <cstring>
#include <unistd.h>
#include <thread>

#include "development/global_variables/global_variables.h"

#include "development/helpers/get_ip_adress/include/getIpAdress.h"
#include "development/helpers/random_bytes/include/random_bytes.h"
#include "development/helpers/join_a_room/include/join_a_room.h"
#include "development/helpers/process_incoming_messages/include/process_incoming_messages.h"

#define BUFFER_SIZE 1024

int main() {
  mainUserId = generateRandomBytesHex(10);
  std::string serverIp = "127.0.0.1";
  std::string ipAdress = getIPAddress();

  join_a_room(mainUserId, serverIp, ipAdress);

  // listen incoming messages
   std::thread messageThread(process_incoming_messages, std::ref(ipAdress));

  // end thread
  messageThread.join();
  return 0;
}