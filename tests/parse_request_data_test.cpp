#include <gtest/gtest.h>
#include "../include/parse_request_data.h"

TEST(ParseRequestDataTest, ValidRequest) {
std::string raw_request = "MESSAGE:MESSAGE:test_user/127.0.0.1/Hello, World!";
std::unique_ptr<RequestData> request_ptr = parse_request_data(raw_request);
RequestData* request = request_ptr.get();

ASSERT_NE(request, nullptr);
EXPECT_EQ(request->get_command(), MESSAGE);
EXPECT_EQ(request->get_sender_id(), "test_user");
EXPECT_EQ(request->get_message(), "Hello, World!");

delete request;
}

TEST(ParseRequestDataTest, InvalidRequest) {
std::string raw_request = "INVALID_FORMAT";
std::unique_ptr<RequestData> request_ptr = parse_request_data(raw_request);
RequestData* request = request_ptr.get();

ASSERT_NE(request, nullptr);
EXPECT_EQ(request->get_command(), UNKNOWN);

delete request;
}