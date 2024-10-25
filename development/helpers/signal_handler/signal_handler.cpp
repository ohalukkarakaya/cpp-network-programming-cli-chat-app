//
// Created by Ö. Haluk KARAKAYA on 25.10.2024.
//

#include "signal_handler.h"

void signal_handler( int signum )
{
    std::cout << std::endl;
    std::cout << BOLD_RED   << "Signal (" << signum << ") received. Shutting down..." << RESET << std::endl;
    running   =  false;
}
