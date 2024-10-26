#include "../include/process_incoming_command.h"

void process_incoming_command(RequestData& request_data)
{
    switch( request_data.getCommand() )
    {
        case JOINROOM:
        {
            if( request_data.getMessage() != getSelectedRoom().getRoomId() || request_data.getSenderId() == mainUserId ) break;
            getSelectedRoom().userJoined(request_data.getSenderId(), request_data.getSenderIp() );
        }
        case LEAVEROOM:
        {
            if( request_data.getMessage() != getSelectedRoom().getRoomId() ) break;
            getSelectedRoom().userLeft(request_data.getSenderId());
            break;
        }
        case MESSAGE:
        {
            break;
        }
        case NOTIFICATION:
        {
            break;
        }
        case UPDATEIP:
        {
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