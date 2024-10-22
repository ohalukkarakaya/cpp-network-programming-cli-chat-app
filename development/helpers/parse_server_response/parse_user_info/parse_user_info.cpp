//
// Created by Ö. Haluk KARAKAYA on 22.10.2024.
//

#include "parse_user_info.h"

std::vector<RoomMember> parse_user_info( const std::string& user_info_list )
{
    std::vector<RoomMember> users;

    // Parse işlemi için kullanılacak arama anahtarları
    const std::string userIdKey = "\"userId\": \"";
    const std::string userIpKey = "\"userIp\": \"";

    size_t pos = 0;

    // Tüm kullanıcı bilgilerini bulmak için döngü
    while (true) {
        // userId'yi ara
        size_t userIdStart = user_info_list.find(userIdKey, pos);
        if (userIdStart == std::string::npos) break; // Daha fazla userId yoksa çık

        userIdStart += userIdKey.size(); // Anahtarın sonrasına git
        size_t userIdEnd = user_info_list.find("\"", userIdStart);
        std::string userId = user_info_list.substr(userIdStart, userIdEnd - userIdStart);

        // userIp'yi ara
        size_t userIpStart = user_info_list.find(userIpKey, userIdEnd);
        if (userIpStart == std::string::npos) break; // Daha fazla userIp yoksa çık

        userIpStart += userIpKey.size(); // Anahtarın sonrasına git
        size_t userIpEnd = user_info_list.find("\"", userIpStart);
        std::string userIp = user_info_list.substr(userIpStart, userIpEnd - userIpStart);

        // Kullanıcı bilgilerini struct'a ekle
        users.push_back({userId, userIp});

        // Bir sonraki kullanıcıyı aramak için pozisyonu güncelle
        pos = userIpEnd;
    }

    return users;
}