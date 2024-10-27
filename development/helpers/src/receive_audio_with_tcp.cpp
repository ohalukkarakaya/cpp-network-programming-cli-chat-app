#include "../include/receive_audio_with_tcp.h"

void receive_audio_with_tcp(int client_socket) {
    char buffer[1024];
    std::ofstream audio_file("./received_audio.wav", std::ios::binary);

    if (!audio_file.is_open()) {
        std::cerr << "Dosya açılamadı: ./received_audio.wav, Hata kodu: " << strerror(errno) << std::endl;
        close(client_socket);
        return;
    }

    bool receiving_audio = true;
    size_t total_data_size = 0;

    while (receiving_audio) {
        ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_read > 0) {
            audio_file.write(buffer, bytes_read);
            total_data_size += bytes_read;
        } else if (bytes_read == 0) {
            // Bağlantı kapandı
            std::cout << "Connection closed by client." << std::endl;
            receiving_audio = false;
        } else {
            // Hata oluştu
            std::cerr << "Error occurred while receiving data: " << strerror(errno) << std::endl;
            receiving_audio = false;
        }
    }

    audio_file.close();
    close(client_socket);
}

