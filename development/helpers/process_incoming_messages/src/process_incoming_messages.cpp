#include "../include/process_incoming_messages.h"

void process_incoming_messages(std::string& ipAddress)
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // TCP soketi oluştur
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        return;
    }

    // Portu tekrar kullanabilmek için ayarları yap
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed");
        close(server_fd);
        return;
    }

    // Bağlantı adres bilgilerini ayarla
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    address.sin_port = htons(LISTEN_PORT);

    // Soketi belirtilen IP ve PORT'a bağla
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return;
    }

    // Gelen bağlantıları dinlemeye başla
    if (listen(server_fd, 3) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        return;
    }

    std::cout << "Listening for incoming messages on " << ipAddress << ":" << LISTEN_PORT << std::endl;

    while (isRunning)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);

        // Zaman aşımı yapısı
        struct timeval timeout;
        timeout.tv_sec = 1;  // 1 saniye bekle
        timeout.tv_usec = 0;

        int activity = select(server_fd + 1, &readfds, NULL, NULL, &timeout);

        if (activity < 0 && errno != EINTR)
        {
            perror("Select error");
            break;
        }

        // `isRunning` kontrolü - false ise döngüden çık
        if (!isRunning) break;

        // Bağlantı var mı kontrol et
        if (FD_ISSET(server_fd, &readfds))
        {
            if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
            {
                perror("Accept failed");
                break;
            }

            int valread = read(new_socket, buffer, 1024);
            if (valread > 0)
            {
                std::cout << "Received message: " << buffer << std::endl;
            }

            // İşlem tamamlandıktan sonra bağlantıyı kapat
            close(new_socket);
        }
    }

    // Ana socketi kapat
    close(server_fd);
}