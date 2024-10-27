#include "../include/random_bytes.h"

std::string generate_random_bytes_hex(size_t length) {
  // divide length to 2 so you can get character with the given size
  auto byte_length = static_cast<size_t>(std::ceil(length / 2.0));

  // create a vector for random bytes
  std::vector<unsigned char> random_bytes(byte_length);

  // random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 255);

  // fill all bytes with a random value
  for (auto &byte : random_bytes) {
    byte = static_cast<unsigned char>(dis(gen));
  }

  // convert bytes to hex string
  std::stringstream ss;
  for (const auto &byte : random_bytes) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
  }

  return to_upper_case(ss.str()); // return value
}
