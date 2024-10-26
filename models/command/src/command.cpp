#include "../include/command.h"

Command getCommandType(const std::string &command)
{
    std::string cmd = command;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) { return std::toupper(c); });

    if( cmd == "MESSAGE" || cmd == "M" ){ return MESSAGE; }
    if( cmd == "NOTIFICATION" || cmd == "N" ){ return NOTIFICATION; }
    if( cmd == "JOINROOM" || cmd == "J" ){ return JOINROOM; }
    if( cmd == "LEAVEROOM" || cmd == "L" ){ return LEAVEROOM; }
    if( cmd == "UPDATEIP" || cmd == "UIP" ){ return UPDATEIP; }
    if( cmd == "AUDIO" || cmd == "A" ){ return AUDIO; }
    if( cmd == "WHISPER" || cmd == "W" ){ return WHISPER;}

    return UNKNOWN;
}

std::string getCommandAsString(Command command)
{
    switch (command) {
        case MESSAGE: {
            return "MESSAGE";
            break;
        }
        case NOTIFICATION: {
            return "NOTIFICATION";
            break;
        }
        case JOINROOM: {
            return "JOINROOM";
            break;
        }
        case LEAVEROOM: {
            return "LEAVEROOM";
            break;
        }
        case UPDATEIP: {
            return "UPDATEIP";
            break;
        }
        case AUDIO: {
            return "AUDIO";
            break;
        }
        case WHISPER: {
            return "WHISPER";
            break;
        }
        case UNKNOWN:
        default:
            return "UNKNOWN";
            break;
    }
}