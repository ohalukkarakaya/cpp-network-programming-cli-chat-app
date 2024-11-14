#include "../include/join_a_room.h"

namespace {
    constexpr int MAX_LENGTH = 10;

    std::vector<std::string> get_room_list(int sock) {
        char buffer[BUFFER_SIZE] = {0};
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        return parse_server_response(buffer);
    }

    void display_active_rooms(const std::vector<std::string>& rooms) {
        std::cout << std::endl;
        std::cout << "\033[1;33mActive Rooms:\033[0m" << std::endl;
        std::cout << std::endl;
        for (const auto& room_name : rooms) {
            std::cout << "- " << room_name << std::endl;
        }
        std::cout << std::endl;
    }

    void display_user_info(const std::string& main_user_id) {
        std::cout << "\033[33mYour User ID: \033[34m" << main_user_id << "\033[0m" << std::endl;
    }

    void join_room(const std::string& main_user_id, std::string& ip_address, const std::string& user_input_room_id, const std::string& server_ip) {
        std::string message = "JOINROOM/" + main_user_id + "/" + ip_address + "/" + user_input_room_id;
        int joinSock = send_with_tcp(PORT, server_ip, message, "JOINROOM");

        char buffer[BUFFER_SIZE] = {0};
        int valread = read(joinSock, buffer, BUFFER_SIZE);
        if (valread < 0) {
            throw std::runtime_error("Failed to read from socket");
        }

        auto members = parse_user_info(buffer);

        for (const auto& user : members) {
            get_selected_room().user_joined(user.get_user_id(), user.get_user_ip(), false);
            if (user.get_user_id() != main_user_id) {
                std::string user_join_message = "JOINROOM:" + main_user_id + "/" + ip_address + "/" + user_input_room_id;
                int send_notification_sock = send_with_tcp(LISTEN_PORT, user.get_user_ip(), user_join_message, "NOTIFICATION");
                close(send_notification_sock);
            }
        }

        get_selected_room().notify_users_on_join(ip_address);
        join_socket = joinSock;
    }
}

void join_a_room(const std::string& main_user_id, const std::string& server_ip, std::string& ip_address, bool is_test, const std::string& test_room_id) {
    try {
        // Get room list
        std::string message = "GETROOMS/0/0/0";
        int sock = send_with_tcp(PORT, server_ip, message, "GETROOMS");
        auto rooms = get_room_list(sock);

        if (!is_test) {
            display_active_rooms(rooms);
            display_user_info(main_user_id);
        }

        close(sock);

        // Get or set room ID
        std::string user_input_room_id = is_test ? test_room_id : get_room_id(MAX_LENGTH);
        get_selected_room().set_room_id(user_input_room_id);

        std::system("clear");

        // Join room
        join_room(main_user_id, ip_address, user_input_room_id, server_ip);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}