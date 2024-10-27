#ifndef PROCESS_USER_INPUT_H
#define PROCESS_USER_INPUT_H

#include <iostream>
#include <regex>
#include <sys/select.h>
#include <thread>
#include <unistd.h>

#include "../../global_variables/global_variables.h"

#include "process_input.h"

void get_user_input();

#endif // PROCESS_USER_INPUT_H
