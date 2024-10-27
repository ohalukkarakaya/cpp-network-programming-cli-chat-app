#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include <string>

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#else
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#endif

class AudioRecorder {
public:
    // Constructor
    AudioRecorder();

    // Ses kaydını başlat
    void record_audio_to_wav(const std::string& output_file_name, float duration_in_seconds);
private:
    static bool is_command_available(const std::string& command);
    static void install_dependency(const std::string& command);
};

#endif // AUDIO_RECORDER_H