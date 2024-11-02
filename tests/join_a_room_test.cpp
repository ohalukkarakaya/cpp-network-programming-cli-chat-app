#include <gtest/gtest.h>
#include "../include/join_a_room.h"

TEST(JoinRoomTest, SuccessfulJoin) {
std::string user_id = "test_user";
std::string server_ip = "127.0.0.1";
std::string ip_address = "192.168.1.1";

join_a_room(user_id, server_ip, ip_address);

EXPECT_EQ(get_selected_room().get_room_id().empty(), false) << "Room ID should not be empty";
}