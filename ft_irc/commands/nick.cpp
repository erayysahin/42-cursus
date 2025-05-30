#include "commands.hpp"
#include <stdexcept>
#include <cctype>
#include <unistd.h>
#include <sys/socket.h>
bool isSpecial(char c)
{
    return c == '[' || c == ']' || c == '-' || c == '_' || c == '\'' || c == '\\' || c == '|' || c == '^' || c == '{' || c == '}';
}

void CommandHandler::firstnick(server &srv, std::vector<Client> &clients, const std::string &newNick, int userIndex)
{
    if (newNick.empty())
        throw std::runtime_error(":" + srv.getServername() + " 431 * :No nickname given\r\n");

    std::string::size_type len = newNick.size();
    if (len < 2 || len > 9)
    {
        throw std::runtime_error(":" + srv.getServername() + " 432 * " + newNick + " :Erroneous nickname\r\n");
    }

    unsigned char c0 = static_cast<unsigned char>(newNick[0]);
    if (!std::isalpha(c0) && !isSpecial(static_cast<char>(c0)))
        throw std::runtime_error(":" + srv.getServername() + " 432 * " + newNick + " :Erroneous nickname\r\n");

    for (std::string::size_type i = 1; i < len; ++i)
    {
        unsigned char ci = static_cast<unsigned char>(newNick[i]);
        if (!std::isalnum(ci) && !isSpecial(static_cast<char>(ci)))
            throw std::runtime_error(":" + srv.getServername() + " 432 * " + newNick + " :Erroneous nickname\r\n");
    }

    for (std::vector<Client>::size_type j = 0;
         j < clients.size(); ++j)
    {
        if (static_cast<int>(j) != userIndex && clients[j].getNickname() == newNick)
        {
            throw std::runtime_error(
                ":" + srv.getServername() +
                " 433 * " + newNick +
                " :Nickname is already in use\r\n");
        }
    }
    Client &me = clients[userIndex];
    me.setNickname(newNick);
    std::string notice = ": !~user@localhost NICK " + newNick + "\r\n";
    for (std::vector<Channel>::size_type ci = 0; ci < srv.Channels.size(); ++ci)
    {
        Channel &ch = srv.Channels[ci];
        if (ch.isUser(newNick))
        {
            std::vector<std::string> users = ch.getUsers();
            for (std::vector<std::string>::size_type ui = 0; ui < users.size(); ++ui)
            {
                const std::string &nick = users[ui];
                for (std::vector<Client>::size_type j = 0; j < clients.size(); ++j)
                {
                    if (clients[j].getNickname() == nick)
                    {
                        int fd = clients[j].getFd();
                        if (fd != -1)
                            send(fd, notice.c_str(), notice.size(), 0);
                        break;
                    }
                }
            }
        }
    }
    completeRegistration(srv, me);
}

void CommandHandler::handleNick(server &srv, std::vector<Client> &clients, const std::string &newNick, int userIndex)
{
    Client &me = clients[userIndex];
    const std::string oldNick = me.getNickname();
    if (oldNick.empty())
    {
        firstnick(srv, clients, newNick, userIndex);
        return;
    }
    if (newNick.empty())
        throw std::runtime_error("431 * :No nickname given\r\n");
    std::string::size_type len = newNick.size();

    if (len < 2 || len > 9)
        throw std::runtime_error("432 * " + oldNick + " " + newNick + " :Erroneous nickname\r\n");

    unsigned char c0 = static_cast<unsigned char>(newNick[0]);
    if (!std::isalpha(c0) && !isSpecial(static_cast<char>(c0)))
        throw std::runtime_error("432 * " + oldNick + " " + newNick + " :Erroneous nickname\r\n");

    for (std::string::size_type i = 1; i < len; ++i)
    {
        unsigned char ci = static_cast<unsigned char>(newNick[i]);
        if (!std::isalnum(ci) && !isSpecial(static_cast<char>(ci)))
            throw std::runtime_error("432 * " + oldNick + " " + newNick + " :Erroneous nickname\r\n");
    }

    for (std::vector<Client>::size_type j = 0; j < clients.size(); ++j)
    {
        if (j != static_cast<std::vector<Client>::size_type>(userIndex) && clients[j].getNickname() == newNick)
            throw std::runtime_error("433 * " + oldNick + " " + newNick + " :Nickname is already in use\r\n");
    }

    if (oldNick == newNick)
        throw std::runtime_error("Nickname unchanged\r\n");

    me.setNickname(newNick);
    for (std::vector<Channel>::size_type ci = 0; ci < srv.Channels.size(); ++ci)
    {
        Channel &ch = srv.Channels[ci];
        if (ch.isUser(oldNick))
        {
            ch.removeUser(oldNick);
            ch.addUser(newNick);
            if (ch.getCreator() == oldNick)
                ch.setCreator(newNick);
            if (ch.isOperator(oldNick))
            {
                ch.rmvChannelOperator(oldNick);
                ch.addChannelOperator(newNick);
            }
        }
    }

    std::string notice = ":" + oldNick + "!~user@localhost NICK " + newNick + "\r\n";
    for (std::vector<Channel>::size_type ci = 0; ci < srv.Channels.size(); ++ci)
    {
        Channel &ch = srv.Channels[ci];
        if (ch.isUser(newNick))
        {
            std::vector<std::string> users = ch.getUsers();
            for (std::vector<std::string>::size_type ui = 0; ui < users.size(); ++ui)
            {
                const std::string &nick = users[ui];
                for (std::vector<Client>::size_type j = 0; j < clients.size(); ++j)
                {
                    if (clients[j].getNickname() == nick)
                    {
                        int fd = clients[j].getFd();
                        if (fd != -1)
                            send(fd, notice.c_str(), notice.size(), 0);
                        break;
                    }
                }
            }
        }
    }
    send(me.getFd(), notice.c_str(), notice.size(), 0);
}
