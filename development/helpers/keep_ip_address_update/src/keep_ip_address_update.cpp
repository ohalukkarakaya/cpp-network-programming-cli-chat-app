#include "../include/keep_ip_address_update.h"

void keep_ip_address_update()
{
    std::string previous_ip_address = getIPAddress();
    currentIpAddress = previous_ip_address;

    while (isRunning)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5)); // Check every 5 seconds

        std::string new_ip_address = getIPAddress();
        if (new_ip_address != previous_ip_address) {
            std::cout << "IP address changed from " << previous_ip_address << " to " << new_ip_address << std::endl;
            previous_ip_address = new_ip_address;

            update_ip_address(new_ip_address);
        }

        if( !isRunning ) break;
    }
}