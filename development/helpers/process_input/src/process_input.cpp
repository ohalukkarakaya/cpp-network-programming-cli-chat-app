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
                    send_with_tcp(LISTEN_PORT, member.getUserIp(), message_to_send, getCommandAsString(command));
                }
            }
            break;
        }
        case AUDIO: {
            float duration;
            if (is_number(message)) {
                duration = std::stof(message);
            } else {
                duration = 2.0f;
            }

            AudioRecorder recorder;
            std::string output_file_name = "./" + mainUserId + "_sound_message.wav";
            recorder.recordAudioToWav(output_file_name, duration);

            std::cout << "Audio file recorded to " << output_file_name << std::endl;
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