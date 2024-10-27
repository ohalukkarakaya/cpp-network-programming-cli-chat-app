#include "../include/get_room_id.h"

std::string get_room_id(int max_length) {
  std::string user_input;
  std::cout << "\033[33mEnter a Room ID or Create One:\033[0m ";

  while (true) {
    int ch = getch();

    // get out of loop when "ENTER" pressed
    if (ch == '\n') {
      break;
    }

    // delete with "BACKSPACE"
    if (ch == 127 && !user_input.empty()) {
      user_input.pop_back();
      std::cout << "\b \b";
    }
    // accept only numbers and letters
    else if (std::isalnum(ch)) {
      if (user_input.size() < max_length) {
        char upper_char = std::toupper(ch);
        user_input += upper_char;

        std::cout << "\033[33m";
        std::cout << "\rEnter a Room ID or Create One:\033[0m ";
        std::cout << "\033[1;34m" << user_input << "\033[0m";
      }
    }
  }

  std::cout << std::endl;

  return user_input;
}
