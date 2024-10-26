#include <thread>
#include <string>

#include "development/global_variables/global_variables.h"
#include "development/helpers/signal_handler/signal_handler.h"
#include "development/helpers/get_ip_adress/include/getIpAdress.h"
#include "development/helpers/keep_ip_address_update/include/keep_ip_address_update.h"
#include "development/helpers/get_user_input/include/get_user_input.h"
#include "development/helpers/join_a_room/include/join_a_room.h"
#include "development/helpers/process_incoming_messages/include/process_incoming_messages.h"
#include "development/helpers/random_bytes/include/random_bytes.h"

#include "development/helpers/audio_recorder/include/audio_recorder.h"

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    isRunning = true;

    signal(SIGINT, signal_handler);
    mainUserId = generateRandomBytesHex(10);
    std::string serverIp = SERVERIP;
    std::string ipAdress = getIPAddress();

    join_a_room(mainUserId, serverIp, ipAdress);

    AudioRecorder recorder;
    // 5 saniye boyunca ses kaydet ve output.wav dosyasına yaz
    recorder.recordAudioToWav("./output.wav", 5.0f);

    // listen incoming messages if the argument is not "--shouldlisten=false"
    bool shouldListen = true;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--shouldlisten=false" || std::string(argv[i]) == "--should_listen=false") // Just for test
        {
            shouldListen = false;
            break;
        }
    }

    std::thread messageThread;
    if (shouldListen) {
        messageThread = std::thread(process_incoming_messages, std::ref(ipAdress));
    }

    std::thread ipMonitorThread(keep_ip_address_update);

    // listen user inputs
    std::thread inputThread(get_user_input);

    // end threads
    if (shouldListen) {
        messageThread.join();
    }

    ipMonitorThread.join();
    inputThread.join();

    return 0;
}