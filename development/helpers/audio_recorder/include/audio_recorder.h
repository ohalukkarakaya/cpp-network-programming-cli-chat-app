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
    void recordAudioToWav(const std::string& outputFileName, float durationInSeconds);
private:
    bool isCommandAvailable(const std::string& command);
    void installDependency(const std::string& command);
};

#endif // AUDIO_RECORDER_H