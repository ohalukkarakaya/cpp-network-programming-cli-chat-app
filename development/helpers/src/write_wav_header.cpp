#include "../include/write_wav_header.h"

// Little-endian dönüşümü
template <typename T>
void write_little_endian(std::ofstream &out, T value, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        out.put(static_cast<char>((value >> (i * 8)) & 0xFF));
    }
}

// WAV başlığı oluşturma
void write_wav_header(std::ofstream &out, int sample_rate, int bits_per_sample, int channels, int data_size) {
    int byte_rate = sample_rate * channels * bits_per_sample / 8;
    int block_align = channels * bits_per_sample / 8;

    out.write("RIFF", 4);
    int file_size = data_size + 36;
    write_little_endian(out, file_size, 4);
    out.write("WAVE", 4);
    out.write("fmt ", 4);
    int sub_chunk_1_size = 16;
    write_little_endian(out, sub_chunk_1_size, 4);
    short audio_format = 1;
    write_little_endian(out, audio_format, 2);
    write_little_endian(out, channels, 2);
    write_little_endian(out, sample_rate, 4);
    write_little_endian(out, byte_rate, 4);
    write_little_endian(out, block_align, 2);
    write_little_endian(out, bits_per_sample, 2);
    out.write("data", 4);
    write_little_endian(out, data_size, 4);
}

void update_wav_header(std::ofstream &out, int data_size) {
    // Dosya boyutu için konum
    out.seekp(4, std::ios::beg);
    int file_size = data_size + 36;
    write_little_endian(out, file_size, 4);

    // Veri boyutu için konum
    out.seekp(40, std::ios::beg);
    write_little_endian(out, data_size, 4);
}
