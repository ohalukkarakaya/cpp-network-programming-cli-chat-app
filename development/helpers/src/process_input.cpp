#include "../include/process_input.h"

void send_message_to_room_members(const std::string& message, const Command& command) {
    std::string command_string = get_command_as_string(command);
    for (const auto& member : get_selected_room().get_members()) {
        if (member.get_user_id() != main_user_id) {
            send_with_tcp(LISTEN_PORT, member.get_user_ip(), message, command_string);
        }
    }
}

void handle_audio_command(const std::string& message) {
    float duration = is_number(message) ? std::stof(message) : 2.0f;

    AudioRecorder recorder;
    std::string output_file_name = "./" + main_user_id + "_sound_message.wav";
    recorder.record_audio_to_wav(output_file_name, duration);

    for (const auto& member : get_selected_room().get_members()) {
        if (member.get_user_id() != main_user_id) {
            send_audio_with_tcp(member.get_user_ip(), LISTEN_PORT, output_file_name);
        }
    }

    std::remove(output_file_name.c_str());
    std::cout << BOLD_GREEN << "YOU: " << RESET << "send an audio message..." << std::endl;
}

void process_input(const std::string& cmd, const std::string& message) {
    Command command = get_command_type(cmd);

    switch (command) {
        case MESSAGE: {
            std::cout << BOLD_GREEN << "YOU: " << RESET << message << std::endl;
            std::string message_to_send = "MESSAGE:" + main_user_id + "/" + current_ip_address + "/" + message;
            send_message_to_room_members(message_to_send, command);
            break;
        }
        case AUDIO: {
            handle_audio_command(message);
            break;
        }
        case UNKNOWN:
        default:
            std::cerr << "Unknown command received: " << cmd << std::endl;
            break;
    }
}