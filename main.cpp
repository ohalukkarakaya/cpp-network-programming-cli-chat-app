#include <thread>
#include <iostream>
#include <string>

#include "development/global_variables/global_variables.h"
#include "development/helpers/signal_handler/signal_handler.h"
#include "development/helpers/get_ip_adress/include/getIpAdress.h"
#include "development/helpers/get_user_input/include/get_user_input.h"
#include "development/helpers/join_a_room/include/join_a_room.h"
#include "development/helpers/process_incoming_messages/include/process_incoming_messages.h"
#include "development/helpers/random_bytes/include/random_bytes.h"

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    isRunning = true;

    signal(SIGINT, signal_handler);
    mainUserId = generateRandomBytesHex(10);
    std::string serverIp = "127.0.0.1";
    std::string ipAdress = getIPAddress();

    join_a_room(mainUserId, serverIp, ipAdress);

    // listen incoming messages if the argument is not "--shouldListen=false"
    bool shouldListen = true;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--shouldListen=false") {
            shouldListen = false;
            break;
        }
    }

    std::thread messageThread;
    if (shouldListen) {
        messageThread = std::thread(process_incoming_messages, std::ref(ipAdress));
    }

    // listen user inputs
    std::thread inputThread(get_user_input);

    // end threads
    if (shouldListen) {
        messageThread.join();
    }

    inputThread.join();

    return 0;
}