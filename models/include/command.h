#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

enum Command { MESSAGE, NOTIFICATION, JOINROOM, LEAVEROOM, UPDATEIP, AUDIO, WHISPER, UNKNOWN };

Command get_command_type(const std::string &command);

std::string get_command_as_string( Command command );

#endif // COMMAND_H
