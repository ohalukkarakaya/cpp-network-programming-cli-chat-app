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
        include/get_room_id/getRoomId.h
        src/get_room_id/getRoomId.cpp
        include/room/room.h
        src/room/room.cpp
        include/room_member/roomMember.h
        src/room_member/room_member.cpp
        include/get_ip_adress/getIpAdress.h
        src/get_ip_adress/getIpAdress.cpp
        include/message/message.h
        src/message/message.cpp
        include/send_to_ip/sendToIp.h
        src/send_to_ip/sendToIp.cpp
)
