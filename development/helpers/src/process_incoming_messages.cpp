#include "../include/process_incoming_messages.h"

void process_incoming_messages(std::string& ip_address) {
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return;
    }
#endif

    int tcp_socket, udp_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    // TCP soketi oluştur
    if ((tcp_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("TCP socket failed");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    int opt = 1;
    if (setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) == SOCKET_ERROR) {
        perror("TCP setsockopt failed");
        closesocket(tcp_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // UDP soketi oluştur
    if ((udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        perror("UDP socket failed");
        closesocket(tcp_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // Adres bilgilerini ayarla
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address.c_str());
    address.sin_port = htons(LISTEN_PORT);

    // TCP için bind
    if (bind(tcp_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        perror("TCP bind failed");
        closesocket(tcp_socket);
        closesocket(udp_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // UDP için bind
    if (bind(udp_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        perror("UDP bind failed");
        closesocket(tcp_socket);
        closesocket(udp_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // TCP için dinlemeye başla
    if (listen(tcp_socket, 3) == SOCKET_ERROR) {
        perror("Listen failed");
        closesocket(tcp_socket);
        closesocket(udp_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    std::cout << "Listening for incoming messages of room " << BOLD_GREEN << get_selected_room().get_room_id() << RESET <<  " on " << BOLD_GREEN << ip_address << ":" << LISTEN_PORT << RESET << std::endl;

    while (is_running) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(tcp_socket, &readfds);
        FD_SET(udp_socket, &readfds);

        int max_sd = std::max(tcp_socket, udp_socket);
        struct timeval timeout = {1, 0};

        int activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);
        if (activity < 0 && errno != EINTR) {
            perror("Select error");
            break;
        }

        // TCP soketinde etkinlik varsa
        if (FD_ISSET(tcp_socket, &readfds)) {
            int new_socket;
            if ((new_socket = accept(tcp_socket, (struct sockaddr*)&address, &addrlen)) != INVALID_SOCKET) {
                int valread = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
                if (valread > 0) {

                    buffer[valread] = '\0';
                    std::string received_message(buffer);
                    RequestData* p_request_data = parse_request_data(received_message);

                    if (p_request_data->get_command() == AUDIO) {
                        receive_audio_with_tcp(new_socket);
                        play_audio("./received_audio.wav");

                        std::remove("./received_audio.wav");
                    }

                    if (p_request_data) {
                        process_incoming_command(*p_request_data);
                    }

                }
                closesocket(new_socket);
            }
        }

        // UDP soketinde etkinlik varsa
        if (FD_ISSET(udp_socket, &readfds)) {
            struct sockaddr_in client_address;
            socklen_t client_len = sizeof(client_address);
            int bytes_received = recvfrom(udp_socket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_address, &client_len);

            if (bytes_received > 0) {
                buffer[bytes_received] = '\0';
                std::string received_message(buffer);
                RequestData* p_request_data = parse_request_data(received_message);
                if (p_request_data && p_request_data->get_command() == AUDIO) {
                    process_incoming_command(*p_request_data);
                }
            }
        }
    }

    closesocket(tcp_socket);
    closesocket(udp_socket);

#ifdef _WIN32
    WSACleanup();
#endif
}