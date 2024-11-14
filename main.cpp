#include <thread>
#include <string>
#include <csignal>

#include "development/global_variables/global_variables.h"

#include "development/helpers/include/signal_handler.h"
#include "development/helpers/include/get_ip_address.h"
#include "development/helpers/include/keep_ip_address_update.h"
#include "development/helpers/include/get_user_input.h"
#include "development/helpers/include/join_a_room.h"
#include "development/helpers/include/process_incoming_messages.h"
#include "development/helpers/include/random_bytes.h"

// Arguments are for taking users options (reason of it is described with more detail below)
bool parse_argument(int argc, char* argv[], const std::string& option) {
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == option) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    is_running = true;
    signal(SIGINT, signal_handler);

    // Generate user ID
    main_user_id = generate_random_bytes_hex(10);
    std::string server_ip = SERVERIP;
    std::string ip_address = get_ip_address();

    join_a_room(main_user_id, server_ip, ip_address);

    // Check if the user wants to listen to incoming messages
    // Since app receives messages from port 8080, when we run
    // Two client on same computer, one of them is not able to
    // Listen, so we are not listening for incoming messages
    // From one (For test reasons only)
    bool should_listen = parse_argument(argc, argv, "--shouldlisten=false") &&
                         parse_argument(argc, argv, "--should_listen=false");

    // Launch threads
    std::thread message_thread;
    if (should_listen) {
        message_thread = std::thread(process_incoming_messages, std::ref(ip_address));
    }

    std::thread ip_update_thread(keep_ip_address_update);
    std::thread input_thread(get_user_input);

    // Threads
    if (should_listen && message_thread.joinable()) {
        message_thread.join();
    }
    if (ip_update_thread.joinable()) {
        ip_update_thread.join();
    }
    if (input_thread.joinable()) {
        input_thread.join();
    }

    return 0;
}