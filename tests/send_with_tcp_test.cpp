#include <gtest/gtest.h>
#include "../include/send_with_tcp.h"

TEST(SendWithTcpTest, ValidConnection) {
std::string ip = "127.0.0.1";
int port = 9090;
std::string message = "Test Message";
std::string type = "TEST";

int result = send_with_tcp(port, ip, message, type);
EXPECT_NE(result, -1) << "Connection to the server should succeed";
}
