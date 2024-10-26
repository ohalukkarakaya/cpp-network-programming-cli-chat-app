#include "../include/process_incoming_command.h"

void process_incoming_command(RequestData& request_data)
{
    switch( request_data.getCommand() )
    {
        case JOINROOM:
        {
            if( request_data.getMessage() != getSelectedRoom().getRoomId() || request_data.getSenderId() == mainUserId ) break;
            getSelectedRoom().userJoined(request_data.getSenderId(), request_data.getSenderIp() );
            break;
        }
        case LEAVEROOM:
        {
            if( request_data.getMessage() != getSelectedRoom().getRoomId() ) break;
            getSelectedRoom().userLeft(request_data.getSenderId());
            break;
        }
        case MESSAGE:
        {
            if( request_data.getSenderId() != mainUserId )
            {
                std::cout << BOLD_YELLOW << request_data.getSenderId() << ": " << RESET << request_data.getMessage() << ITALIC_LIGHT_GRAY << " - " << request_data.getCommandTime() << RESET << std::endl;
            }
            break;
        }
        case NOTIFICATION:
        {
            break;
        }
        case UPDATEIP:
        {
            if( request_data.getSenderId() != mainUserId && request_data.getMessage() == getSelectedRoom().getRoomId() )
            {
                getSelectedRoom().updateMemberIp( request_data.getSenderId(), request_data.getSenderIp() );
            }
            break;
        }
        case AUDIO:
        {
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