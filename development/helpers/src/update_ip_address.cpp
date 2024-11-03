#include "../include/update_ip_address.h"

void send_ip_update(const std::string& ip_address, const std::string& message, const std::string& command) {
    int socket = send_with_tcp(LISTEN_PORT, ip_address, message, command);
    if (socket != -1) {
        close(socket);
    } else {
        std::cerr << "Failed to send IP update to " << ip_address << std::endl;
    }
}

void update_ip_address(const std::string& new_ip_address) {
    std::string command = get_command_as_string(UPDATEIP);
    std::string message_to_send = command + "/" + main_user_id + "/" + new_ip_address + "/" + get_selected_room().get_room_id();

    // to server
    send_ip_update(SERVERIP, message_to_send, command);

    // to members
    for (const auto& member : get_selected_room().get_members()) {
        if (member.get_user_id() != main_user_id) {
            send_ip_update(member.get_user_ip(), message_to_send, command);
        }
    }
}