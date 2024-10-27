#ifndef RECEIVE_AUDIO_WITH_TCP_H
#define RECEIVE_AUDIO_WITH_TCP_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>

void receive_audio_with_tcp(int client_socket);

#endif //RECEIVE_AUDIO_WITH_TCP_H
