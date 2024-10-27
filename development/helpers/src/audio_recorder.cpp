#include "../include/audio_recorder.h"

AudioRecorder::AudioRecorder() = default;

bool AudioRecorder::is_command_available(const std::string& command) {
#ifdef _WIN32
    std::string check_command = "where " + command + " > nul 2>&1"; // windows
#else
    std::string check_command = "which " + command + " > /dev/null 2>&1"; // linux and macos
#endif
    return (system(check_command.c_str()) == 0);
}

void AudioRecorder::install_dependency(const std::string& command) {
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
    std::string install_command = "choco install " + command + " -y";

#elif __APPLE__
    if (system("brew -v > /dev/null 2>&1")) {  // `brew -v` komutu başarısızsa, Homebrew yüklü değil demektir.
        std::cout << "Homebrew bulunamadı. Yükleniyor..." << std::endl;
        system("/bin/bash -c \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"");
    }
    // Homebrew üzerinden bağımlılığı kur
    std::string install_command = "brew install " + command;

#elif __linux__
    // `apt` var mı kontrol et
    if (system("which apt > /dev/null 2>&1")) {
        std::cerr << "apt bulunamadı. Yükleniyor..." << std::endl;
        system("sudo apt-get update && sudo apt-get install -y apt");
    }
    // `apt` ile bağımlılığı kur
    std::string install_command = "sudo apt install " + command + " -y";
#endif

    std::cout << "Installing " << command << "..." << std::endl;
    system(install_command.c_str());
}

void AudioRecorder::record_audio_to_wav(const std::string& output_file_name, float duration_in_seconds) {
    const std::string sox_command = "sox";

    if (!is_command_available(sox_command)) {
        std::cout << sox_command << " is not installed. Installing..." << std::endl;
        install_dependency(sox_command);
        std::cout << sox_command << " has been installed." << std::endl;
    }

    std::string command;

#ifdef _WIN32
    command = "rec -r 44100 -c 1 " + output_file_name + " trim 0 " + std::to_string(static_cast<int>(duration_in_seconds)) + " > NUL 2>&1";
#else
    command = "rec -r 44100 -c 1 " + output_file_name + " trim 0 " + std::to_string(static_cast<int>(duration_in_seconds)) + " > /dev/null 2>&1";
#endif
    system(command.c_str());
}

void AudioRecorder::record_and_stream_to_multiple(const std::vector<std::pair<std::string, int>>& addresses, float duration_in_seconds)
{
    const std::string sox_command = "sox";

    if (!is_command_available(sox_command)) {
        std::cout << sox_command << " is not installed. Installing..." << std::endl;
        install_dependency(sox_command);
        std::cout << sox_command << " has been installed." << std::endl;
    }

    // UDP soketini oluştur
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    std::vector<sockaddr_in> server_addresses;
    for (const auto& [ip, port] : addresses) {
        sockaddr_in server_addr;
        std::memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
        server_addresses.push_back(server_addr);
    }

    // `sox` komutunu pipe ile kullanarak ses kaydı başlat
    std::string command;

#ifdef _WIN32
    command = "sox -d -r 44100 -c 1 -b 16 -t raw - trim 0 " + std::to_string(static_cast<int>(duration_in_seconds)) + " > NUL 2>&1";
#else
    command = "sox -d -r 44100 -c 1 -b 16 -t raw - trim 0 " + std::to_string(static_cast<int>(duration_in_seconds)) + " > /dev/null 2>&1";
#endif

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run sox command." << std::endl;
        close(sock);
        return;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), pipe)) > 0) {
        for (const auto& server_addr : server_addresses) {
            sendto(sock, buffer, bytes_read, 0, (const sockaddr*)&server_addr, sizeof(server_addr));
        }
    }

    pclose(pipe);
    close(sock);
}
