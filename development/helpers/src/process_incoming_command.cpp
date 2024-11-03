#include "../include/process_incoming_command.h"

void handle_join_room(RequestData& request_data) {
    if (request_data.get_message() == get_selected_room().get_room_id() &&
        request_data.get_sender_id() != main_user_id) {
        get_selected_room().user_joined(request_data.get_sender_id(), request_data.get_sender_ip());
    }
}

void handle_leave_room(RequestData& request_data) {
    if (request_data.get_message() == get_selected_room().get_room_id()) {
        get_selected_room().user_left(request_data.get_sender_id());
    }
}

void handle_message(RequestData& request_data) {
    if (request_data.get_sender_id() != main_user_id) {
        std::cout << BOLD_YELLOW << request_data.get_sender_id() << ": " << RESET
                  << request_data.get_message() << ITALIC_LIGHT_GRAY << " - "
                  << request_data.get_command_time() << RESET << std::endl;
    }
}

void handle_update_ip(RequestData& request_data) {
    if (request_data.get_sender_id() != main_user_id &&
        request_data.get_message() == get_selected_room().get_room_id()) {
        get_selected_room().update_member_ip(request_data.get_sender_id(), request_data.get_sender_ip());
    }
}

void handle_audio(RequestData& request_data) {
    if (request_data.get_sender_id() != main_user_id) {
        std::cout << BOLD_YELLOW << request_data.get_sender_id() << ": " << RESET
                  << "send an audio message..." << std::endl;
    }
}

void process_incoming_command(RequestData& request_data) {
    switch (request_data.get_command()) {
        case JOINROOM:
            handle_join_room(request_data);
            break;
        case LEAVEROOM:
            handle_leave_room(request_data);
            break;
        case MESSAGE:
            handle_message(request_data);
            break;
        case UPDATEIP:
            handle_update_ip(request_data);
            break;
        case AUDIO:
            handle_audio(request_data);
            break;
        case UNKNOWN:
        default:
            // unknown commands are ignored
            break;
    }
}
