#include "../include/process_user_input.h"

void process_user_input() {
    std::string userInput;

    while (isRunning) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

        if (activity > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
            std::getline(std::cin, userInput);

            std::regex pattern("^:([^:]+):\\s*(.*)$");
            std::smatch matches;

            if (std::regex_match(userInput, matches, pattern)) {
                std::string type = matches[1].str();
                std::string input = matches[2].str();

                const std::string greenBold = "\033[1;32m";
                const std::string reset = "\033[0m";

                std::cout << greenBold << "Type: " << type << reset << std::endl;
                std::cout << greenBold << "Input: " << input << reset << std::endl;

            } else {
                std::cout << "Enter a valid message (exp. :M: your message)" << std::endl;
            }

        } else if (activity == 0) {
            if (!isRunning) break;
        }
    }
}