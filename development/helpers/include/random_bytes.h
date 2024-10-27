#ifndef RANDOM_BYTES_H
#define RANDOM_BYTES_H

#include "to_upper_case.h"

#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// gets size
std::string generate_random_bytes_hex(size_t length);

#endif // RANDOM_BYTES_H
