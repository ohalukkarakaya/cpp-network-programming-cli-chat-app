#ifndef PARSE_REQUEST_DATA_H
#define PARSE_REQUEST_DATA_H

#include "../../global_variables/global_variables.h"

#include "../../../models/include/command.h"
#include "../../../models/include/request_data.h"

#include "get_current_time.h"
#include "write_wav_header.h"

RequestData* parse_request_data( std::string& raw_request );

#endif //PARSE_REQUEST_DATA_H
