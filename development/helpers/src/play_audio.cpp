#include "../include/play_audio.h"

void play_audio(const std::string &file_path) {
#ifdef _WIN32
    std::string command = "start " + file_path; // Windows için "start" komutu kullanılır
#elif __APPLE__
    std::string command = "afplay " + file_path; // macOS için "afplay" komutu
#else
    std::string command = "xdg-open " + file_path; // Linux için "xdg-open" komutu
#endif
    system(command.c_str());
}