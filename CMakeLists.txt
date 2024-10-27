cmake_minimum_required(VERSION 3.27)
project(cpp_network_programming_cli_chat_app)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        cpp_network_programming_cli_chat_app main.cpp

        development/helpers/include/random_bytes.h
        development/helpers/src/random_bytes.cpp

        development/helpers/include/to_upper_case.h
        development/helpers/src/to_upper_case.cpp

        development/helpers/include/getch.h
        development/helpers/src/getch.cpp

        development/helpers/include/get_room_id.h
        development/helpers/src/get_room_id.cpp

        models/include/room.h
        models/src/room.cpp

        models/include/room_member.h
        models/src/room_member.cpp

        development/helpers/include/get_ip_address.h
        development/helpers/src/get_ip_address.cpp

        models/include/message.h
        models/src/message.cpp

        development/helpers/include/send_with_tcp.h
        development/helpers/src/send_with_tcp.cpp

        development/helpers/include/send_with_udp.h
        development/helpers/src/send_with_udp.cpp

        development/helpers/include/parse_server_response.h
        development/helpers/src/parse_server_response.cpp

        development/helpers/include/parse_user_info.h
        development/helpers/src/parse_user_info.cpp

        development/global_variables/global_variables.h
        development/global_variables/global_variables.cpp

        development/helpers/include/join_a_room.h
        development/helpers/src/join_a_room.cpp

        models/include/command.h
        models/src/command.cpp

        development/helpers/include/parse_command.h
        development/helpers/src/parse_command.cpp

        models/include/request_data.h
        models/src/request_data.cpp

        development/helpers/include/get_current_time.h
        development/helpers/src/get_current_time.cpp

        development/helpers/include/process_incoming_messages.h
        development/helpers/src/process_incoming_messages.cpp

        development/helpers/include/signal_handler.h
        development/helpers/src/signal_handler.cpp

        development/helpers/include/process_incoming_command.h
        development/helpers/src/process_incoming_command.cpp

        development/helpers/include/get_user_input.h
        development/helpers/src/get_user_input.cpp

        development/helpers/include/process_input.h
        development/helpers/src/process_input.cpp

        development/helpers/include/keep_ip_address_update.h
        development/helpers/src/keep_ip_address_update.cpp

        development/helpers/include/update_ip_address.h
        development/helpers/src/update_ip_address.cpp

        development/helpers/include/audio_recorder.h
        development/helpers/src/audio_recorder.cpp

        development/helpers/include/is_number.h
        development/helpers/src/is_number.cpp
)
