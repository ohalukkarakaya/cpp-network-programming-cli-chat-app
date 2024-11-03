#include "../include/send_audio_with_tcp.h"

void close_socket(int sock) {
    if (sock >= 0) {
        close(sock);
    }
}

bool send_data(int sock, const char* data, size_t size) {
    if (send(sock, data, size, 0) < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return false;
    }
    return true;
}

void send_audio_with_tcp(const std::string& ip, int port, const std::string& file_path) {
    // TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid IP address" << std::endl;
        close_socket(sock);
        return;
    }

    // connect to server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection to server failed" << std::endl;
        close_socket(sock);
        return;
    }

    // set header
    std::string header = "AUDIO:" + main_user_id;
    if (!send_data(sock, header.c_str(), header.size())) {
        close_socket(sock);
        return;
    }

    // open file
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << file_path << std::endl;
        close_socket(sock);
        return;
    }

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        if (!send_data(sock, buffer, sizeof(buffer))) {
            file.close();
            close_socket(sock);
            return;
        }
    }

    if (file.gcount() > 0) {
        if (!send_data(sock, buffer, file.gcount())) {
            file.close();
            close_socket(sock);
            return;
        }
    }

    std::string end_signal = "END_AUDIO:";
    if (!send_data(sock, end_signal.c_str(), end_signal.size())) {
        std::cerr << "End signal send failed" << std::endl;
    }

    file.close();
    close_socket(sock);
}