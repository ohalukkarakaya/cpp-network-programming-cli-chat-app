#include "../include/get_user_input.h"

void handle_user_input(const std::string& user_input) {
    std::regex pattern("^:([^:]+):\\s*(.*)$");
    std::smatch matches;

    if (std::regex_match(user_input, matches, pattern)) {
        std::string type = matches[1].str();
        std::string input = matches[2].str();
        process_input(type, input);
    } else {
        std::cout << "Enter a valid message (exp. :M: your message)" << std::endl;
    }
    std::cout.flush();
}

bool read_user_input(std::string& user_input) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int activity = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    if (activity > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
        std::getline(std::cin, user_input);
        return true;
    }
    return false;
}

void get_user_input() {
    std::string user_input;

    while (is_running) {
        if (read_user_input(user_input)) {
            // Clear the previous line before displaying the new input
            std::cout << "\033[A\033[K";
            std::cout.flush();

            handle_user_input(user_input);
        }

        if (!is_running) {
            break;
        }
    }
}
