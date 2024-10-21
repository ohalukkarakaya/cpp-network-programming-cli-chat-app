cmake_minimum_required(VERSION 3.27)
project(cpp_network_programming_cli_chat_app)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        cpp_network_programming_cli_chat_app main.cpp
        
        development/helpers/random_bytes/include/random_bytes.h
        development/helpers/random_bytes/src/random_bytes.cpp
        
        development/helpers/to_upper_case/include/toUpperCase.h
        development/helpers/to_upper_case/src/toUpperCase.cpp
        
        development/helpers/getch/include/getch.h
        development/helpers/getch/src/getch.cpp
        
        development/get_room_id/include/getRoomId.h
        development/get_room_id/src/getRoomId.cpp
        
        models/room/include/room.h
        models/room/src/room.cpp
        
        models/room_member/include/room_member.h
        models/room_member/src/room_member.cpp
        
        development/helpers/get_ip_adress/include/getIpAdress.h
        development/helpers/get_ip_adress/src/getIpAdress.cpp
        
        models/message/include/message.h
        models/message/src/message.cpp
        
        development/helpers/send_to_ip/include/sendToIp.h
        development/helpers/send_to_ip/src/sendToIp.cpp
        development/helpers/parse_server_response/parse_server_response.h
        development/helpers/parse_server_response/parse_server_response.cpp
)
