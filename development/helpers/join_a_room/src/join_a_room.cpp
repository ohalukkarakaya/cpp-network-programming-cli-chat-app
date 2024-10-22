//
// Created by Ö. Haluk KARAKAYA on 22.10.2024.
//

#include "../include/join_a_room.h"

void join_a_room(const std::string &mainUserId, const std::string &serverIp, std::string &ipAdress)
{
    std::string message;
    char buffer[BUFFER_SIZE] = {0};

    // get room list
    message = "GETROOMS/0/0/0";
    int sock = sendToIp(serverIp, message, "GETROOMS");

    // get server response
    int valread = read(sock, buffer, BUFFER_SIZE);
    std::vector<std::string> rooms = parse_server_response(buffer);

    // print rooms
    std::cout << std::endl;
    std::cout << "\033[1;33mActive Rooms:\033[0m" << std::endl;
    std::cout << std::endl;

    for (const std::string &room_name : rooms) {
        std::cout << "- " << room_name << std::endl;
    }
    std::cout << std::endl;

    // close socket
    close(sock);

    //print users info
    std::cout << "\033[33mYour User ID: \033[34m" << mainUserId << "\033[0m" << std::endl;

    const int maxLength = 10;
    std::string userInputRoomId = getRoomId(maxLength);
    getSelectedRoom().setRoomId(userInputRoomId);

    std::system("clear");

    message = "JOINROOM/" + mainUserId + "/" + ipAdress + "/" + userInputRoomId;
    int joinSock = sendToIp(serverIp, message, "JOINROOM");

    valread = read(joinSock, buffer, BUFFER_SIZE);

    // parse resp
    std::vector<RoomMember> members = parse_user_info(buffer);

    for (const auto &user : members) {
        getSelectedRoom().userJoined(user.getUserId(), user.getUserIp(), false);
    }

    getSelectedRoom().notifyUsersOnJoin(ipAdress);

    // Socket kapat
    close(joinSock);
}