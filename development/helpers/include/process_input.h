#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#include <iostream>

#include "../../global_variables/global_variables.h"

#include "../../../models/include/command.h"
#include "../../../models/include/room.h"

#include "send_with_tcp.h"
#include "is_number.h"
#include "audio_recorder.h"

void process_input(const std::string& cmd, const std::string& message);

#endif //PROCESS_INPUT_H
