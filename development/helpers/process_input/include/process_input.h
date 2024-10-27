//
// Created by Ö. Haluk KARAKAYA on 26.10.2024.
//

#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_PROCESS_INPUT_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_PROCESS_INPUT_H

#include <iostream>

#include "../../../global_variables/global_variables.h"

#include "../../../../models/command/include/command.h"
#include "../../../../models/room/include/room.h"

#include "../../send_with_tcp/include/send_with_tcp.h"
#include "../../is_number/include/is_number.h"
#include "../../audio_recorder/include/audio_recorder.h"

void process_input(const std::string& cmd, const std::string& message);

#endif //CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_PROCESS_INPUT_H
