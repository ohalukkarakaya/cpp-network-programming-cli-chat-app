cmake_minimum_required(VERSION 3.27)
project(cpp_network_programming_cli_chat_app)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_network_programming_cli_chat_app src/main.cpp
        include/random_bytes/random_bytes.h
        src/random_bytes/random_bytes.cpp
        include/to_upper_case/toUpperCase.h
        src/to_upper_case/toUpperCase.cpp
        include/getch/getch.h
        src/getch/getch.cpp
        include/get_user_id/getUserId.h
        src/get_user_id/getUserId.cpp
)
