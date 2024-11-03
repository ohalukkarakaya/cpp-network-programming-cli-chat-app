#include "../include/receive_audio_with_tcp.h"
#include <array>
#include <fstream>
#include <iostream>
#include <string>

void receive_audio_with_tcp(int client_socket) {
    constexpr size_t BUFFER_SIZE = 1024;
    std::array<char, BUFFER_SIZE> buffer;
    std::ofstream audio_file("./received_audio.wav", std::ios::binary);

    if (!audio_file.is_open()) {
        std::cerr << "Failed to open file: ./received_audio.wav, Error: " << strerror(errno) << std::endl;
        close(client_socket);
        return;
    }

    size_t total_data_received = 0;
    while (true) {
        ssize_t bytes_read = recv(client_socket, buffer.data(), buffer.size(), 0);

        if (bytes_read > 0) {
            audio_file.write(buffer.data(), bytes_read);
            total_data_received += bytes_read;
        } else if (bytes_read == 0) {
            // Connection closed gracefully by the client
            std::cout << "Connection closed by client. Total data received: " << total_data_received << " bytes." << std::endl;
            break;
        } else {
            // An error occurred during receiving
            std::cerr << "Error occurred while receiving data: " << strerror(errno) << std::endl;
            break;
        }
    }

    audio_file.close();
    close(client_socket);
}