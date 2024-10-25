#ifndef CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_PARSE_COMMAND_H
#define CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_PARSE_COMMAND_H

#include "../../../global_variables/global_variables.h"

#include "../../../../models/command/include/command.h"
#include "../../../../models/request_data/include/request_data.h"

#include "../../get_current_time/include/get_current_time.h"

RequestData* parse_request_data( std::string& rawRequest );

#endif //CPP_NETWORK_PROGRAMMING_CLI_CHAT_APP_PARSE_COMMAND_H
