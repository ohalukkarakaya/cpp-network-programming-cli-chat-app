#ifndef PARSE_COMMAND_H
#define PARSE_COMMAND_H

#include "../../../global_variables/global_variables.h"

#include "../../../../models/command/include/command.h"
#include "../../../../models/request_data/include/request_data.h"

#include "../../get_current_time/include/get_current_time.h"

RequestData* parse_request_data( std::string& raw_request );

#endif //PARSE_COMMAND_H
