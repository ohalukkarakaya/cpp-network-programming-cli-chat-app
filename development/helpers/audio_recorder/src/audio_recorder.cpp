#include "../include/audio_recorder.h"

AudioRecorder::AudioRecorder() {
    // Gerekli başlatmalar burada yapılabilir
}

bool AudioRecorder::isCommandAvailable(const std::string& command) {
#ifdef _WIN32
    std::string checkCommand = "where " + command + " > nul 2>&1"; // Windows
#else
    std::string checkCommand = "which " + command + " > /dev/null 2>&1"; // Linux ve macOS
#endif
    return (system(checkCommand.c_str()) == 0);
}

void AudioRecorder::installDependency(const std::string& command) {
#ifdef _WIN32
    // Windows için bağımlılık kurulum komutları (örneğin Chocolatey)
    std::string installCommand = "choco install " + command + " -y";
#elif __linux__
    // Linux için bağımlılık kurulum komutları (örneğin apt)
    std::string installCommand = "sudo apt install " + command + " -y";
#elif __APPLE__
    // macOS için bağımlılık kurulum komutları (Homebrew)
    std::string installCommand = "brew install " + command;
#endif
    std::cout << "Installing " << command << "..." << std::endl;
    system(installCommand.c_str());
}

void AudioRecorder::recordAudioToWav(const std::string& outputFileName, float durationInSeconds) {
    const std::string soxCommand = "sox"; // Sox bağımlılığını kontrol et

    // Bağımlılığın kurulu olup olmadığını kontrol et
    if (!isCommandAvailable(soxCommand)) {
        std::cout << soxCommand << " is not installed. Installing..." << std::endl;
        installDependency(soxCommand);
        std::cout << soxCommand << " has been installed." << std::endl;
    }

#ifdef _WIN32
    // Windows için ses kaydı
    const int SAMPLE_RATE = 44100;
    const int BITS_PER_SAMPLE = 16;
    const int CHANNELS = 1; // Mono ses
    const int BUFFER_SIZE = SAMPLE_RATE * durationInSeconds;

    std::vector<short> buffer(BUFFER_SIZE);
    HWAVEIN hWaveIn;
    WAVEFORMATEX wfx;

    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = CHANNELS;
    wfx.nSamplesPerSec = SAMPLE_RATE;
    wfx.wBitsPerSample = BITS_PER_SAMPLE;
    wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    // Ses kaydediciyi aç
    if (waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        std::cerr << "Unable to open wave input device." << std::endl;
        return;
    }

    // Ses kaydını başlat
    waveInStart(hWaveIn);
    waveInAddBuffer(hWaveIn, (LPWAVEHDR)&buffer[0], sizeof(buffer[0]) * BUFFER_SIZE);

    Sleep(durationInSeconds * 1000); // Belirli bir süre bekle

    // Ses kaydını durdur
    waveInStop(hWaveIn);
    waveInClose(hWaveIn);

    // WAV dosyasını kaydet
    FILE* file;
    fopen_s(&file, outputFileName.c_str(), "wb");

    if (file) {
        // WAV başlığı yaz
        fwrite("RIFF", 1, 4, file);
        int fileSize = 36 + BUFFER_SIZE * sizeof(short);
        fwrite(&fileSize, 4, 1, file);
        fwrite("WAVE", 1, 4, file);
        fwrite("fmt ", 1, 4, file);
        int fmtChunkSize = 16;
        fwrite(&fmtChunkSize, 4, 1, file);
        fwrite(&wfx.wFormatTag, 2, 1, file);
        fwrite(&wfx.nChannels, 2, 1, file);
        fwrite(&wfx.nSamplesPerSec, 4, 1, file);
        fwrite(&wfx.nAvgBytesPerSec, 4, 1, file);
        fwrite(&wfx.nBlockAlign, 2, 1, file);
        fwrite(&wfx.wBitsPerSample, 2, 1, file);
        fwrite("data", 1, 4, file);
        fwrite(&BUFFER_SIZE, 4, 1, file);
        fwrite(buffer.data(), sizeof(short), BUFFER_SIZE, file);
        fclose(file);

        std::cout << "Recording saved to " << outputFileName << std::endl;
    } else {
        std::cerr << "Unable to open output file." << std::endl;
    }

#elif __linux__
    // Linux için ses kaydı
    std::string command = "arecord -f S16_LE -r 44100 -c 1 -d " + std::to_string(static_cast<int>(durationInSeconds)) + " " + outputFileName;
    system(command.c_str());
    std::cout << "Recording saved to " << outputFileName << std::endl;

#elif __APPLE__
    // macOS için ses kaydı
    std::string command = "rec -r 44100 -c 1 -d " + std::to_string(static_cast<int>(durationInSeconds)) + " " + outputFileName;
    system(command.c_str());
    std::cout << "Recording saved to " << outputFileName << std::endl;

#else
    std::cerr << "Unsupported platform!" << std::endl;
#endif
}