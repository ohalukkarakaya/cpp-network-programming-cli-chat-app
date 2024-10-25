#include "../include/command.h"

Command getCommandType(const std::string &command)
{
    std::string cmd = command;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c) { return std::toupper(c); });

    if( cmd == "MESSAGE" ){ return MESSAGE; }
    if( cmd == "NOTIFICATION" ){ return NOTIFICATION; }
    if( cmd == "JOINROOM" ){ return JOINROOM; }
    if( cmd == "LEAVEROOM" ){ return LEAVEROOM; }
    if( cmd == "UPDATEIP" ){ return UPDATEIP; }
    if( cmd == "AUDIO" ){ return AUDIO; }
    if( cmd == "WHISPER" ){ return WHISPER;}

    return UNKNOWN;
}