#include "../include/audio_recorder.h"

AudioRecorder::AudioRecorder() = default;

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
    // Chocolatey var mı kontrol et
    if (system("choco -v >nul 2>&1")) {  // `choco -v` komutu başarısızsa, Chocolatey yüklü değil demektir.
        std::cout << "Chocolatey bulunamadı. Yükleniyor..." << std::endl;
        system("Set-ExecutionPolicy Bypass -Scope Process -Force; "
               "[System.Net.ServicePointManager]::SecurityProtocol = "
               "[System.Net.SecurityProtocolType]::Tls12; "
               "iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))");
    }
    // Chocolatey üzerinden bağımlılığı kur
    std::string installCommand = "choco install " + command + " -y";

#elif __APPLE__
    // Homebrew var mı kontrol et
    if (system("brew -v > /dev/null 2>&1")) {  // `brew -v` komutu başarısızsa, Homebrew yüklü değil demektir.
        std::cout << "Homebrew bulunamadı. Yükleniyor..." << std::endl;
        system("/bin/bash -c \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"");
    }
    // Homebrew üzerinden bağımlılığı kur
    std::string installCommand = "brew install " + command;

#elif __linux__
    // `apt` var mı kontrol et
    if (system("which apt > /dev/null 2>&1")) {
        std::cerr << "apt bulunamadı. Yükleniyor..." << std::endl;
        system("sudo apt-get update && sudo apt-get install -y apt");
    }
    // `apt` ile bağımlılığı kur
    std::string installCommand = "sudo apt install " + command + " -y";
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

    // Sox ile ses kaydı komutu
    std::string command = "rec -r 44100 -c 1 " + outputFileName + " trim 0 " + std::to_string(static_cast<int>(durationInSeconds));
    system(command.c_str());
}