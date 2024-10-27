#include "../include/send_audio_with_tcp.h"

void send_audio_with_tcp(const std::string &ip, int port, const std::string &file_path) {
    // TCP soketi oluştur
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
        close(sock);
        return;
    }

    // Sunucuya bağlan
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection to server failed" << std::endl;
        close(sock);
        return;
    }

    // Başlık gönder
    std::string header = "AUDIO:" + main_user_id;
    if (send(sock, header.c_str(), header.size(), 0) < 0) {
        std::cerr << "Header send failed" << std::endl;
        close(sock);
        return;
    }

    // Dosyayı aç
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << file_path << std::endl;
        close(sock);
        return;
    }

    // Dosya içeriğini gönder
    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        if (send(sock, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Failed to send file data" << std::endl;
            file.close();
            close(sock);
            return;
        }
    }

    // Kalan veriyi gönder
    if (file.gcount() > 0) {
        if (send(sock, buffer, file.gcount(), 0) < 0) {
            std::cerr << "Failed to send remaining file data" << std::endl;
            file.close();
            close(sock);
            return;
        }
    }

    // Bitirme sinyalini gönder
    std::string end_signal = "END_AUDIO:";
    if (send(sock, end_signal.c_str(), end_signal.size(), 0) < 0) {
        std::cerr << "End signal send failed" << std::endl;
    }

    file.close();
    close(sock);
}