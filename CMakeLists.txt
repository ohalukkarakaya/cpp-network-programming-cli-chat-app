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

        development/helpers/parse_server_response/parse_user_info/parse_user_info.h
        development/helpers/parse_server_response/parse_user_info/parse_user_info.cpp

        development/global_variables/global_variables.h
        development/global_variables/global_variables.cpp

        development/helpers/join_a_room/include/join_a_room.h
        development/helpers/join_a_room/src/join_a_room.cpp

        models/command/include/command.h
        models/command/src/command.cpp

        development/helpers/parse_command/include/parse_command.h
        development/helpers/parse_command/src/parse_command.cpp

        models/request_data/include/request_data.h
        models/request_data/src/request_data.cpp

        development/helpers/get_current_time/include/get_current_time.h
        development/helpers/get_current_time/src/get_current_time.cpp

        development/helpers/process_incoming_messages/include/process_incoming_messages.h
        development/helpers/process_incoming_messages/src/process_incoming_messages.cpp

        development/helpers/signal_handler/signal_handler.h
        development/helpers/signal_handler/signal_handler.cpp

        development/helpers/process_incoming_command/include/process_incoming_command.h
        development/helpers/process_incoming_command/src/process_incoming_command.cpp

        development/helpers/get_user_input/include/get_user_input.h
        development/helpers/get_user_input/src/get_user_input.cpp

        development/helpers/process_input/include/process_input.h
        development/helpers/process_input/src/process_input.cpp
        development/helpers/keep_ip_address_update/include/keep_ip_address_update.h
        development/helpers/keep_ip_address_update/src/keep_ip_address_update.cpp
        development/helpers/update_ip_address/include/update_ip_address.h
        development/helpers/update_ip_address/src/update_ip_address.cpp
        development/helpers/audio_recorder/include/audio_recorder.h
        development/helpers/audio_recorder/src/audio_recorder.cpp
        development/helpers/is_number/include/is_number.h
        development/helpers/is_number/src/is_number.cpp
)
