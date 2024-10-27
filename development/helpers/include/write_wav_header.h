#ifndef WRITE_WAV_HEADER_H
#define WRITE_WAV_HEADER_H

#include <iostream>
#include <fstream>
#include <vector>

template <typename T>
void write_little_endian(std::ofstream &out, T value, std::size_t size);
void write_wav_header(std::ofstream &out, int sample_rate, int bits_per_sample, int channels, int data_size = 0);
void update_wav_header(std::ofstream &out, int data_size);

#endif //WRITE_WAV_HEADER_H
