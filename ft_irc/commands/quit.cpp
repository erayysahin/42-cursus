#include "commands.hpp"
#include <unistd.h>
#include <sys/socket.h>

void CommandHandler::handleQuit(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex)
{
    Client &me = clients[userIndex];
    const std::string nick = me.getNickname();
    const int fd = me.getFd();

    std::string msg = argument;
    if (!msg.empty() && msg[0] == ':')
        msg.erase(0, 1);
    if (msg.empty())
        msg = "Client Quit";
    bool wasCreator = false;
    for (std::vector<Channel>::iterator it = server.Channels.begin();
         it != server.Channels.end();)
    {
        Channel &ch = *it;
        wasCreator = ch.getCreator() == nick;
        ch.removeUser(nick);
        if (ch.getUsers().empty())
        {
            it = server.Channels.erase(it);
        }
        else
        {
            ++it;
        }
        if (wasCreator)
        {
            const std::vector<std::string> &users = ch.getUsers();
            std::string newCreator;
            for (std::vector<std::string>::const_iterator ui = users.begin(); ui != users.end(); ++ui)
            {
                if (ch.isOperator(*ui))
                {
                    newCreator = *ui;
                    ch.rmvChannelOperator(newCreator);
                    break;
                }
            }
            if (newCreator.empty())
                newCreator = users.front();

            ch.setCreator(newCreator);
        }
    }
    std::string quitLine = ":" + nick + " QUIT :" + msg + "\r\n";
    for (std::vector<Channel>::iterator chanIt = server.Channels.begin();
         chanIt != server.Channels.end(); ++chanIt)
    {
        Channel &ch = *chanIt;
        const std::vector<std::string> &users = ch.getUsers();
        for (std::vector<std::string>::const_iterator userIt = users.begin();
             userIt != users.end(); ++userIt)
        {
            if (*userIt == nick)
                continue;
            Client &c = server.getClientByNick(*userIt);
            send(c.getFd(), quitLine.c_str(), quitLine.size(), 0);
            broadcastNamesReply(server, ch);
        }
    }

    std::string exit = ": " + server.getServername() + " :ERROR :Closing Link\r\n";
    send(fd, exit.c_str(), exit.size(), 0);
    shutdown(fd, SHUT_RDWR);
    clients.erase(clients.begin() + userIndex);
}
