#include "../include/process_input.h"

void process_input(const std::string& cmd, const std::string& message)
{
    Command command = get_command_type(cmd);

    switch (command) {
        case MESSAGE: {
            std::cout << BOLD_GREEN << "YOU: " << RESET << message << std::endl;
            std::string message_to_send = "MESSAGE:" + main_user_id + "/0/" + message;
            for (auto &member : get_selected_room().get_members()) {
                if (member.get_user_id() != main_user_id) {
                    send_with_tcp(LISTEN_PORT, member.get_user_ip(), message_to_send, get_command_as_string(command));
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
            std::string output_file_name = "./" + main_user_id + "_sound_message.wav";
            recorder.record_audio_to_wav(output_file_name, duration);

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