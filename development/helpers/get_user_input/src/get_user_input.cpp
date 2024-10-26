#include "../include/get_user_input.h"

void get_user_input() {
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
        std::cout << "\r";
        std::cout.flush();

      std::getline(std::cin, userInput);

        std::cout << "\033[A\033[K";
        std::cout.flush();

      std::regex pattern("^:([^:]+):\\s*(.*)$");
      std::smatch matches;

      if (std::regex_match(userInput, matches, pattern)) {
        std::string type = matches[1].str();
        std::string input = matches[2].str();

        process_input(type, input);

      } else {
        std::cout << "Enter a valid message (exp. :M: your message)"
                  << std::endl;
      }
        std::cout.flush();
    } else if (activity == 0) {
      if (!isRunning)
        break;
    }
  }
}
