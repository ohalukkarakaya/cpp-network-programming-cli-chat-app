#include "../include/process_incoming_messages.h"

void process_incoming_messages(std::string& ipAddress)
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return;
    }
#endif

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    // TCP soketi oluştur
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        perror("Socket failed");
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // Portu yeniden kullanmak için ayarlar
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) == SOCKET_ERROR)
    {
        perror("Setsockopt failed");
        closesocket(server_fd);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // Bağlantı adres bilgilerini ayarlayın
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    address.sin_port = htons(LISTEN_PORT);

    // Soketi belirtilen port ve IP ile bağlayın
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
    {
        perror("Bind failed");
        closesocket(server_fd);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // Gelen bağlantıları dinlemeye başla
    if (listen(server_fd, 3) == SOCKET_ERROR)
    {
        perror("Listen failed");
        closesocket(server_fd);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    std::cout << "Listening for incoming messages of room " << BOLD_GREEN << getSelectedRoom().getRoomId() << RESET <<  " on " << BOLD_GREEN << ipAddress << ":" << LISTEN_PORT << RESET << std::endl;

    while (isRunning)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(server_fd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            perror("Select error");
            break;
        }

        if (!isRunning) break;

        if (FD_ISSET(server_fd, &readfds))
        {
            if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) == INVALID_SOCKET)
            {
                perror("Accept failed");
                break;
            }

            int valread = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
            if (valread > 0)
            {
                buffer[valread] = '\0';
                std::string received_message(buffer);

                RequestData* Prequest_data = parse_request_data(received_message);
                if (Prequest_data)
                {
                    RequestData request_data = *Prequest_data;
                    process_incoming_command(request_data);
                }
                else
                {
                    std::cerr << "Failed to parse request data." << std::endl;
                }
            }
        }
    }

    closesocket(new_socket);
    closesocket(server_fd);

#ifdef _WIN32
    WSACleanup();
#endif
}
