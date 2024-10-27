#ifndef SEND_WITH_UDP_H
#define SEND_WITH_UDP_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

void send_with_udp(const std::string &ip, int port, const std::string &file_path);

#endif //SEND_WITH_UDP_H