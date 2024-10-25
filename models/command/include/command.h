#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

enum Command { MESSAGE, NOTIFICATION, JOINROOM, LEAVEROOM, UPDATEIP, AUDIO, WHISPER, UNKNOWN };

Command getCommandType(const std::string &command);

#endif // COMMAND_H
