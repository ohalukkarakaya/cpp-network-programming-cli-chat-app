#include "../include/process_input.h"

void process_input(const std::string& cmd, const std::string& message)
{
    Command command = get_command_type(cmd);

    switch (command) {
        case MESSAGE: {
            std::cout << BOLD_GREEN << "YOU: " << RESET << message << std::endl;
            std::string message_to_send = "MESSAGE:" + main_user_id + "/" + current_ip_address + "/" + message;
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

            for( auto &member : get_selected_room().get_members())
            {
                if( member.get_user_id() != main_user_id )
                {
                    send_audio_with_tcp(member.get_user_ip(), LISTEN_PORT, output_file_name);
                }
            }

            std::remove(output_file_name.c_str());

            std::cout << BOLD_GREEN
                      << "YOU: "
                      << RESET << "send an audio message..." << std::endl;

            break;
        }
        case WHISPER: {
            float duration;
            if (is_number(message)) {
                duration = std::stof(message);
            } else {
                duration = 2.0f;
            }

            std::vector<std::pair<std::string, int>> members_addresses;
            for (auto &member : get_selected_room().get_members()) {
                if (member.get_user_id() != main_user_id) {
                    members_addresses.emplace_back(member.get_user_ip(), LISTEN_PORT);
                }
            }

            AudioRecorder recorder;
            recorder.record_and_stream_to_multiple(members_addresses);

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