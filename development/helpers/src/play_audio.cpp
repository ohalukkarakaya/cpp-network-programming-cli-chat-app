#include "../include/play_audio.h"

void play_audio(const std::string& file_path) {
    std::string command;

#ifdef _WIN32
    command = "start " + file_path; // Windows için "start" komutu
#elif __APPLE__
    command = "afplay " + file_path; // macOS için "afplay" komutu
#else
    command = "xdg-open " + file_path; // Linux için "xdg-open" komutu
#endif

    if (std::system(command.c_str()) != 0) {
        std::cerr << "Failed to play audio file: " << file_path << std::endl;
        throw std::runtime_error("Error executing system command");
    }
}
