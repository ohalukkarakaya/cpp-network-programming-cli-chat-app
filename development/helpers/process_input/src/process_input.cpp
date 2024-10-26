//
// Created by Ö. Haluk KARAKAYA on 26.10.2024.
//

#include "../include/process_input.h"

void process_input(const std::string& cmd, const std::string& message)
{
    Command command = getCommandType(cmd);

    switch (command) {
        case MESSAGE: {
            std::cout << BOLD_GREEN << "YOU: " << RESET << message << std::endl;
            std::string message_to_send = "MESSAGE:" + mainUserId + "/0/" + message;
            for (auto &member : getSelectedRoom().getMembers()) {
                if (member.getUserId() != mainUserId) {
                    sendToIp(LISTEN_PORT, member.getUserIp(), message_to_send,
                             getCommandAsString(command));
                }
            }
            break;
        }
        case AUDIO: {
            std::cout << "Audio file will send by FTP -- TO DO" << std::endl;
            break;
        }
        case WHISPER: {
            std::cout << "Audio will send by UDP -- TO DO" << std::endl;
            break;
        }
        case NOTIFICATION:
        {
            break;
        }
        case JOINROOM:
        {
            break;
        }
        case LEAVEROOM:
        {
            break;
        }
        case UPDATEIP:
        {
            break;
        }
        case UNKNOWN:
        default:
            break;
    }

    return;
}