#include "../include/keep_ip_address_update.h"

void check_and_update_ip_address(std::string& previous_ip_address) {
    std::string new_ip_address = get_ip_address();
    if (new_ip_address != previous_ip_address) {
        std::cout << "IP address changed from " << previous_ip_address
                  << " to " << new_ip_address << std::endl;
        previous_ip_address = new_ip_address;
        update_ip_address(new_ip_address);
    }
}

void keep_ip_address_update() {
    std::string previous_ip_address = get_ip_address();
    current_ip_address = previous_ip_address;

    while (is_running) {
        std::this_thread::sleep_for(std::chrono::seconds(5)); // check each 5 seconds

        check_and_update_ip_address(previous_ip_address);
    }
}
