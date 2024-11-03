#include "../include/send_with_tcp.h"

int create_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed" << std::endl;
    }
    return sock;
}

bool connect_to_server(int sock, const std::string& ip, int port, sockaddr_in& server_addr) {
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return false;
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection to " << ip << " failed" << std::endl;
        return false;
    }
    return true;
}

bool send_message(int sock, const std::string& message) {
    if (send(sock, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Failed to send message" << std::endl;
        return false;
    }
    return true;
}

int send_with_tcp(int port, const std::string& ip, const std::string& message, const std::string& type) {
    int sock = create_socket();
    if (sock < 0) {
        return -1;
    }

    sockaddr_in server_addr;
    if (!connect_to_server(sock, ip, port, server_addr)) {
        close(sock);
        return -1;
    }

    std::string full_message = type + ":" + message;
    if (!send_message(sock, full_message)) {
        close(sock);
        return -1;
    }

    return sock;
}
