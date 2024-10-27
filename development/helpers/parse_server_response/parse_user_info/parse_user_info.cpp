#include "parse_user_info.h"

std::vector<RoomMember> parse_user_info( const std::string& user_info_list )
{
    std::vector<RoomMember> users;

    // Search keys to be used for parsing
    const std::string user_id_key = "\"userId\": \"";
    const std::string user_ip_key = "\"userIp\": \"";

    size_t pos = 0;

    // Loop to find all user information
    while (true) {
        // Search for user_ip
        size_t user_id_start = user_info_list.find(user_id_key, pos);
        if (user_id_start == std::string::npos) break; // If there are no more user_ids, exit

        user_id_start += user_id_key.size(); // Go to the next key
        size_t user_id_end = user_info_list.find('\"', user_id_start);
        std::string user_id = user_info_list.substr(user_id_start, user_id_end - user_id_start);

        // Search for user_ip
        size_t user_ip_start = user_info_list.find(user_ip_key, user_id_end);
        if (user_ip_start == std::string::npos) break; // If there is no more user_ip, exit

        user_ip_start += user_ip_key.size(); //  Go to the next key
        size_t user_ip_end = user_info_list.find("\"", user_ip_start);
        std::string user_ip = user_info_list.substr(user_ip_start, user_ip_end - user_ip_start);

        // Add user information to struct
        users.push_back({user_id, user_ip});

        // Update position to search next user
        pos = user_ip_end;
    }

    return users;
}