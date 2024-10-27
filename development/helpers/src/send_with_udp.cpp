#include "../include/send_with_udp.h"

void send_with_udp(const std::string &ip, int port, const std::string &file_path)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << file_path << std::endl;
        close(sock);
        return;
    }

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        sendto(sock, buffer, sizeof(buffer), 0, (const sockaddr *)&server_addr, sizeof(server_addr));
    }

    if (file.gcount() > 0) {
        sendto(sock, buffer, file.gcount(), 0, (const sockaddr *)&server_addr, sizeof(server_addr));
    }

    file.close();
    close(sock);
}