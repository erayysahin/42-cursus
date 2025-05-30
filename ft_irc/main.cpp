#include "server.hpp"
#include <signal.h>

int main(int ac, char **av)
{
    signal(SIGPIPE, SIG_IGN);

    try
    {
        if (ac != 3)
            throw server::notenough("port ve sifreyi giriniz");
        server serv;

        serv.portcontroller(av[1]);
        serv.setServerPassword(av[2]);
        serv.setServername("127.0.0.1");
        serv.connectport();
    }
    catch (server::notenough &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
