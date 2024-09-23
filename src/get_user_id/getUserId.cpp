//
// Created by Ö. Haluk KARAKAYA on 23.09.2024.
//

#include "../../include/get_user_id/getUserId.h"

std::string getUserId(int maxLength)
{
    std::string userInput;
    std::cout << "\033[33mEnter User ID Of Someone You Want To Chat With:\033[0m ";

    while( true )
    {
        int ch = getch();

        // get out of loop when "ENTER" pressed
        if (ch == '\n')
        {
            break;
        }

        // delete with "BACKSPACE"
        if (ch == 127 && !userInput.empty())
        {
            userInput.pop_back();
            std::cout << "\b \b";
        }
        // accept only numbers and letters
        else if (std::isalnum(ch))
        {
            if (userInput.size() < maxLength)
            {
                char upperChar = std::toupper(ch);
                userInput += upperChar;

                std::cout << "\033[33m";
                std::cout << "\rEnter User ID Of Someone You Want To Chat With:\033[0m ";
                std::cout << "\033[1;34m" << userInput << "\033[0m";
            }
        }
    }

    std::cout << std::endl;

    return userInput;
}
