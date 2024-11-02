#include "../include/process_incoming_messages.h"

// Platform management
void initialize_networking() {
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
#endif
}

void cleanup_networking(int socket) {
    closesocket(socket);
#ifdef _WIN32
    WSACleanup();
#endif
}

// TCP socket
int setup_tcp_socket(const std::string& ip_address) {
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == INVALID_SOCKET) {
        throw std::runtime_error("TCP socket creation failed");
    }

    int opt = 1;
    if (setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) == SOCKET_ERROR) {
        throw std::runtime_error("TCP setsockopt failed");
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address.c_str());
    address.sin_port = htons(LISTEN_PORT);

    if (bind(tcp_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        throw std::runtime_error("TCP bind failed");
    }

    if (listen(tcp_socket, 3) == SOCKET_ERROR) {
        throw std::runtime_error("Listen failed");
    }

    return tcp_socket;
}

void process_message(int socket) {
    char buffer[1024] = {0};
    int valread = recv(socket, buffer, sizeof(buffer) - 1, 0);
    if (valread > 0) {
        buffer[valread] = '\0';
        std::string received_message(buffer);
        auto p_request_data = parse_request_data(received_message);

        if (p_request_data) {
            if (p_request_data->get_command() == AUDIO && p_request_data->get_sender_id() != main_user_id) {
                receive_audio_with_tcp(socket);
                play_audio("./received_audio.wav");
                std::remove("./received_audio.wav");
            }
            process_incoming_command(*p_request_data);
        }
    }
}

void handle_incoming_messages(int tcp_socket, const std::string& ip_address) {
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    std::cout << "Listening for incoming messages of room " << BOLD_GREEN
              << get_selected_room().get_room_id() << RESET << " on "
              << BOLD_GREEN << ip_address << ":" << LISTEN_PORT << RESET << std::endl;

    while (is_running) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(tcp_socket, &readfds);

        int max_sd = tcp_socket;
        struct timeval timeout = {1, 0};

        int activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);
        if (activity < 0 && errno != EINTR) {
            perror("Select error");
            break;
        }

        if (FD_ISSET(tcp_socket, &readfds)) {
            int new_socket = accept(tcp_socket, (struct sockaddr*)&address, &addrlen);
            if (new_socket != INVALID_SOCKET) {
                process_message(new_socket);
                closesocket(new_socket);
            }
        }
    }
}

void process_incoming_messages(std::string& ip_address) {
    try {
        initialize_networking();
        int tcp_socket = setup_tcp_socket(ip_address);
        handle_incoming_messages(tcp_socket, ip_address);
        cleanup_networking(tcp_socket);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
