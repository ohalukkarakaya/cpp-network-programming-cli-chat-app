#include "../include/update_ip_address.h"

void update_ip_address( std::string new_ip_address )
{
    std::string command = getCommandAsString( UPDATEIP );
    std::string message_to_send = command + "/" + mainUserId + "/" + new_ip_address + "/" + getSelectedRoom().getRoomId();

    int send_notification_server_sock = sendToIp(PORT, SERVERIP, message_to_send, command);
    close(send_notification_server_sock);

    for( auto& member : getSelectedRoom().getMembers() )
    {
        if(member.getUserId() != mainUserId)
        {
            int send_notification_sock = sendToIp(LISTEN_PORT, member.getUserIp(), message_to_send, command);
            close(send_notification_sock);
        }
    }
}