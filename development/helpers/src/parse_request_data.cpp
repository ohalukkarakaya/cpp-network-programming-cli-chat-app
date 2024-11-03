#include "../include/parse_request_data.h"

std::unique_ptr<RequestData> handle_missing_parameter() {
    std::cerr << "Missing Parameter" << std::endl;
    return std::make_unique<RequestData>(UNKNOWN, "", "", "", "");
}

std::unique_ptr<RequestData> parse_audio_request(const std::string& raw_request) {
    size_t colon_pos = raw_request.find(':');
    std::string sender_id = (colon_pos != std::string::npos) ? raw_request.substr(colon_pos + 1) : "";
    return std::make_unique<RequestData>(AUDIO, sender_id, "", "", "");
}

std::unique_ptr<RequestData> parse_request_data(std::string& raw_request) {
    if (raw_request.rfind("AUDIO:", 0) == 0) {
        return parse_audio_request(raw_request);
    }

    size_t first_colon = raw_request.find(':');
    if (first_colon == std::string::npos) return handle_missing_parameter();

    size_t second_colon = raw_request.find(':', first_colon + 1);
    if (second_colon == std::string::npos) return handle_missing_parameter();

    size_t first_slash = raw_request.find('/', second_colon + 1);
    if (first_slash == std::string::npos) return handle_missing_parameter();

    size_t second_slash = raw_request.find('/', first_slash + 1);

    std::string type = raw_request.substr(0, first_colon);
    std::string cmd = raw_request.substr(first_colon + 1, second_colon - first_colon - 1);
    std::string sender_id = raw_request.substr(second_colon + 1, first_slash - second_colon - 1);
    std::string sender_ip = raw_request.substr(first_slash + 1,
                                               second_slash != std::string::npos ? (second_slash - first_slash - 1) : std::string::npos);
    std::string message = second_slash != std::string::npos ? raw_request.substr(second_slash + 1) : "";

    Command command = get_command_type(cmd);
    std::string command_time = get_current_time_as_string();
    return std::make_unique<RequestData>(command, sender_id, sender_ip, message, command_time);
}