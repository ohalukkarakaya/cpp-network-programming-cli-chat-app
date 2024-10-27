#include "../include/process_incoming_command.h"

void process_incoming_command(RequestData& request_data)
{
    switch( request_data.get_command() )
    {
        case JOINROOM:
        {
            if( request_data.get_message() != get_selected_room().get_room_id() || request_data.get_sender_id() == main_user_id ) break;
            get_selected_room().user_joined(request_data.get_sender_id(), request_data.get_sender_ip() );
            break;
        }
        case LEAVEROOM:
        {
            if( request_data.get_message() != get_selected_room().get_room_id() ) break;
            get_selected_room().user_left(request_data.get_sender_id());
            break;
        }
        case MESSAGE:
        {
            if( request_data.get_sender_id() != main_user_id )
            {
                std::cout << BOLD_YELLOW << request_data.get_sender_id() << ": " << RESET << request_data.get_message() << ITALIC_LIGHT_GRAY << " - " << request_data.get_command_time() << RESET << std::endl;
            }
            break;
        }
        case NOTIFICATION:
        {
            break;
        }
        case UPDATEIP:
        {
            if( request_data.get_sender_id() != main_user_id && request_data.get_message() == get_selected_room().get_room_id() )
            {
                get_selected_room().update_member_ip( request_data.get_sender_id(), request_data.get_sender_ip() );
            }
            break;
        }
        case AUDIO:
        {
            if ( request_data.get_sender_id() != main_user_id ) {
                std::cout << BOLD_YELLOW
                          << request_data.get_sender_id()
                          << ": " << RESET << "send an audio message..." << std::endl;
            }
            break;
        }
        case WHISPER:
        {
            break;
        }
        case UNKNOWN:
        default:
            break;
    }
}