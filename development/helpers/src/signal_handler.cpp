#include "../include/signal_handler.h"

void signal_handler( int signum )
{
    std::cout << std::endl;
    std::cout << BOLD_RED   << "Signal (" << signum << ") received. Shutting down..." << RESET << std::endl;
    is_running   =  false;
    close( join_socket );
}
