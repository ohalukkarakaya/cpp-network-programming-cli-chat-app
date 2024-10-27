#ifndef AUDIO_RECORDER_H
#define AUDIO_RECORDER_H

#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

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
    AudioRecorder();

    void record_audio_to_wav(const std::string& output_file_name, float duration_in_seconds);
    void record_and_stream_to_multiple(const std::vector<std::pair<std::string, int>>& addresses, float duration_in_seconds);

private:
    static bool is_command_available(const std::string& command);
    static void install_dependency(const std::string& command);
};

#endif // AUDIO_RECORDER_H