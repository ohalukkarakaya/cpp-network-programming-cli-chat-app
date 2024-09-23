//
// Created by Ö. Haluk KARAKAYA on 23.09.2024.
//

#ifndef ROOMMEMBER_H
#define ROOMMEMBER_H


#include <iostream>
#include <string>

class RoomMember {
public:
    RoomMember(const std::string& userId, const std::string& userIp);

    const std::string& getUserId() const;
    const std::string& getUserIp() const;

private:
    std::string userId;
    std::string userIp;
};

#endif //ROOMMEMBER_H
