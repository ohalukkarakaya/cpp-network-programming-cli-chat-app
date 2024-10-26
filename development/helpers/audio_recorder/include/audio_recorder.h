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
};

#endif // AUDIO_RECORDER_H