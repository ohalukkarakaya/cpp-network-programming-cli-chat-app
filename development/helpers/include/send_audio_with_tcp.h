#ifndef SEND_AUDIO_WITH_TCP_H
#define SEND_AUDIO_WITH_TCP_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../../global_variables/global_variables.h"

void send_audio_with_tcp(const std::string &ip, int port, const std::string &file_path);

#endif //SEND_AUDIO_WITH_TCP_H
