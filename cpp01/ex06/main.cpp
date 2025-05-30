#include "Harl.hpp"

int main(int ac, char **av) {

    Harl harl;

    if (ac == 2 && (std::string(av[1]) == "DEBUG" ||
                    std::string(av[1]) == "INFO" ||
                    std::string(av[1]) == "WARNING" ||
                    std::string(av[1]) == "ERROR")) {
        harl.complain(av[1]);
    }
    else
    {
        std::cout << "Usage: ./harlFilter [DEBUG|INFO|WARNING|ERROR]" << std::endl;
    }
    return 0;
}