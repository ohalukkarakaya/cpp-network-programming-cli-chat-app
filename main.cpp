#include <thread>
#include <string>

#include "development/global_variables/global_variables.h"

#include "development/helpers/include/signal_handler.h"
#include "development/helpers/include/get_ip_address.h"
#include "development/helpers/include/keep_ip_address_update.h"
#include "development/helpers/include/get_user_input.h"
#include "development/helpers/include/join_a_room.h"
#include "development/helpers/include/process_incoming_messages.h"
#include "development/helpers/include/random_bytes.h"

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    is_running = true;

    signal(SIGINT, signal_handler);
    main_user_id = generate_random_bytes_hex(10);
    std::string server_ip = SERVERIP;
    std::string ip_address = get_ip_address();

    join_a_room(main_user_id, server_ip, ip_address);

    // listen incoming messages if the argument is not "--shouldlisten=false" or "--should_listen=false" for test
    bool should_listen = true;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--shouldlisten=false" || std::string(argv[i]) == "--should_listen=false") // Just for test
        {
            should_listen = false;
            break;
        }
    }

    std::thread message_thread;
    if (should_listen) {
        message_thread = std::thread(process_incoming_messages, std::ref(ip_address));
    }

    std::thread ip_update_thread(keep_ip_address_update);

    // listen user inputs
    std::thread input_thread(get_user_input);

    // end threads
    if (should_listen) {
        message_thread.join();
    }

    ip_update_thread.join();
    input_thread.join();

    return 0;
}