#include <iostream>

#include "../include/random_bytes/random_bytes.h"
#include "../include/get_room_id/getRoomId.h"
#include "../include/room/room.h"
#include "../include/get_ip_adress/getIpAdress.h"

int main() {
    std::string randomId = generateRandomBytesHex(10);
    std::string ipAdress = getIPAddress();
    std::cout << "\033[33mYour User ID: \033[34m" << randomId << "\033[0m" << std::endl;


    const int maxLength = 10;
    std::string userInputRoomId = getRoomId(maxLength);

    std::system("clear");

    Room room(userInputRoomId);
    room.userJoined(randomId, ipAdress);



    return 0;
}
