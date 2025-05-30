#include "server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <set>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <signal.h>

Channel &server::getChannel(std::string &channelName)
{
    for (std::vector<Channel>::iterator it = this->Channels.begin(); it != this->Channels.end(); ++it)
    {
        if (it->getChannelName() == channelName)
        {
            return *it;
        }
    }
    throw std::runtime_error("Channel not found: " + channelName);
}

Client &server::getClientByNick(const std::string &nick)
{
    for (std::vector<Client>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if (it->getNickname() == nick)
        {
            return *it;
        }
    }
    throw std::runtime_error("No such nick: " + nick);
}

void server::setServername(std::string servername)
{
    _servername = servername;
}

std::string server::getServername() const
{
    return _servername;
}

void server::setServerPassword(const std::string &ServerPass)
{
    _serverPassword = ServerPass;
}

std::string server::getServerPassword() const
{
    return _serverPassword;
}

void server::clientfd(int fd)
{
    Client Newclients(fd);
    users.push_back(Newclients);
}

server::server()
{
    print = "sever";
}

void server::writer()
{
    std::cout << print << std::endl;
}

server::notenough::notenough(const std::string &msg)
{
    message = msg;
}

server::notenough::~notenough()
{
}

const char *server::notenough::what() const throw()
{
    return message.c_str();
}

void server::portcontroller(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!std::isdigit(str[i]))
            throw notenough("lutfen portu sayi olarak giriniz");
        i++;
    }
    i = std::atoi(str);

    if (i <= 1023 || i >= 65536)
        throw notenough("port 1023 - 65536 arasinda olmali");

    port = i;
}

std::string server::read_data(int fd)
{
    int res = 1;
    char buf;
    std::string str;

    while (res)
    {
        res = recv(fd, &buf, 1, 0);
        if (res == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            else
            {
                str = "error";
                return str;
            }
        }
        else if (res == 0)
        {
            return "error";
        }
        str += buf;
    }
    return str;
}

int *execsig(void)
{
    static int exec = 0;

    return &exec;
}

void handle_signal(int sig)
{
    *execsig() = 1;

}




void server::connectport()
{

    signal(SIGINT, handle_signal);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int i = 1;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) == -1)
        throw notenough("socket fauld");

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    bind(fd, (struct sockaddr *)&server, sizeof(server));
    listen(fd, 10);

    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    int epfd = epoll_create1(0);
    struct epoll_event event, checker[100];

    event.events = EPOLLIN;
    event.data.fd = fd;

    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);

    std::set<int> clients;
    while (*execsig() == 0)
    {
        int ret = epoll_wait(epfd, checker, 100, -1);
        int i = -1;

        while (++i < ret)
        {
            int checkfd = checker[i].data.fd;

            if (checkfd == fd)
            {
                struct sockaddr_in client;
                socklen_t clientlen = sizeof(client);
                int client_fd = accept(fd, (struct sockaddr *)&client, &clientlen);
                int flag = fcntl(client_fd, F_GETFL, 0);
                fcntl(client_fd, F_SETFL, flag | O_NONBLOCK);
                event.events = EPOLLIN;
                event.data.fd = client_fd;
                clients.insert(client_fd);
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &event);

                clientfd(client_fd);
                std::cout << "the " << client_fd << " has joined the channel" << std::endl;
            }
            else
            {
                std::string str;
                str = read_data(checkfd);
                if (str == "error")
                {
                    std::cout << "the " << checkfd << " has left" << std::endl;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, checkfd, NULL);
                    close(checkfd);
                    clients.erase(checkfd);
                }
                else
                {
                    int idx = findClientIndex(users, checkfd);
                    users[idx].appendToBuffer(str);
                    std::string &buf = users[idx].getBuffer();

                    size_t pos;
                    while ((pos = buf.find("\n")) != std::string::npos)
                    {
                        std::string line = buf.substr(0, pos);
                        buf.erase(0, pos + 1);
                        CommandHandler handler;
                        handler.handleCommand(*this, checkfd, line);
                    }
                }
            }
        }
    }
    clients.clear();

}
