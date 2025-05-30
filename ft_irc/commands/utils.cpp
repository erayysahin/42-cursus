#include "utils.hpp"
#include "commands.hpp"
std::string &Utils::trim(std::string &s)
{
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    return s;
}

void Utils::toUpperCase(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
    {
        return std::toupper(c);
    });
}
int clientmsg(int fd, const std::string &msg)
{
    if (send(fd, msg.c_str(), msg.length(), 0) < 0)
    {
        std::cerr << "Mesaj gönderilemedi" << std::endl;
        return -1;
    }
    return 0;
}
int findClientIndex(std::vector<Client> &clients, int actualFd)
{
    for (size_t i = 0; i < clients.size(); ++i)
    {
        if (clients[i].getFd() == actualFd)
            return i;
    }
    return -1;
}
