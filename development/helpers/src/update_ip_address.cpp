#include "../include/update_ip_address.h"

void update_ip_address( std::string new_ip_address )
{
    std::string command = get_command_as_string( UPDATEIP );
    std::string message_to_send = command + "/" + main_user_id + "/" + new_ip_address + "/" + get_selected_room().get_room_id();

    int send_notification_server_sock = send_with_tcp(PORT, SERVERIP, message_to_send, command);
    close(send_notification_server_sock);

    for( auto& member : get_selected_room().get_members() )
    {
        if(member.get_user_id() != main_user_id)
        {
            int send_notification_sock = send_with_tcp(LISTEN_PORT, member.get_user_ip(), message_to_send, command);
            close(send_notification_sock);
        }
    }
}