#include <iostream>

#include "../include/random_bytes/random_bytes.h"
#include "../include/get_user_id/getUserId.h"

int main() {
    std::string randomId = generateRandomBytesHex(10);
    std::cout << "\033[33mYour User ID: \033[34m" << randomId << "\033[0m" << std::endl;

    const int maxLength = 10;
    std::string userInput = getUserId(maxLength);

    std::cout << "user input: " << userInput << std::endl;

    return 0;
}
