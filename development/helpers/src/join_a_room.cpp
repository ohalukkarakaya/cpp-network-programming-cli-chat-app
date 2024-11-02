#include "../include/join_a_room.h"

void join_a_room(const std::string &main_user_id, const std::string &server_ip, std::string &ip_address, bool is_test, std::string test_room_id)
{
    std::string message;
    char buffer[BUFFER_SIZE] = {0};

    // get room list
    message = "GETROOMS/0/0/0";
    int sock = send_with_tcp(PORT, server_ip, message, "GETROOMS");

    // get server response
    int valread = read(sock, buffer, BUFFER_SIZE);
    if( !is_test )
    {
        std::vector<std::string> rooms = parse_server_response(buffer);

        // print rooms
        std::cout << std::endl;
        std::cout << "\033[1;33mActive Rooms:\033[0m" << std::endl;
        std::cout << std::endl;

        for (const std::string &room_name : rooms) {
            std::cout << "- " << room_name << std::endl;
        }
        std::cout << std::endl;

        //print users info
        std::cout << "\033[33mYour User ID: \033[34m" << main_user_id << "\033[0m" << std::endl;
    }

    // close socket
    close(sock);

    const int max_length = 10;

    std::string user_input_room_id;

    if( is_test )
    {
        user_input_room_id = test_room_id;
    }
    else
    {
        user_input_room_id = get_room_id(max_length);
    }
    get_selected_room().set_room_id(user_input_room_id);

    std::system("clear");

    message = "JOINROOM/" + main_user_id + "/" + ip_address + "/" + user_input_room_id;
    int joinSock = send_with_tcp(PORT, server_ip, message, "JOINROOM");

    valread = read(joinSock, buffer, BUFFER_SIZE);

    // parse resp
    std::vector<RoomMember> members = parse_user_info(buffer);

    for (const auto &user : members) {
        get_selected_room().user_joined(user.get_user_id(), user.get_user_ip(), false);

        if(user.get_user_id() != main_user_id)
        {
            std::string user_join_message = "JOINROOM:" + main_user_id + "/" + ip_address + "/" + user_input_room_id;
            int send_notification_sock = send_with_tcp(LISTEN_PORT, user.get_user_ip(), user_join_message, "NOTIFICATION");
            close(send_notification_sock);
        }
    }

    get_selected_room().notify_users_on_join(ip_address);

    // Socket kapat
    join_socket = joinSock;
}