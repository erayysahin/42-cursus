#include "commands.hpp"
#include "utils.hpp"
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>

void CommandHandler::handlePrivmsg(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex)
{
    Client &me = clients[userIndex];
    const std::string &nick = me.getNickname();

    std::istringstream ss(argument);
    std::string target;
    ss >> target;

    std::string msg;
    std::getline(ss, msg);
    Utils::trim(msg);
    if (!msg.empty() && msg[0] == ':')
        msg.erase(0,1);

    if (target[0] == '#')
    {
        Channel &ch = server.getChannel(target);
        if (!ch.isUser(nick))
            throw std::runtime_error(": 404 " + nick + " " + target + " :Cannot send to channel\r\n");

        std::string out = ":" + nick + " PRIVMSG " + target + " :" + msg + "\r\n";
        const std::vector<std::string> &users = ch.getUsers();
        for (std::vector<std::string>::const_iterator it = users.begin(); it != users.end(); ++it)
        {
            if (*it == nick) continue;
            Client &c = server.getClientByNick(*it);
            send(c.getFd(), out.c_str(), out.size(), 0);
        }
    }
    else
    {
        try {
            Client &dest = server.getClientByNick(target);
            std::string out = ":" + nick + " PRIVMSG " + target + " :" + msg + "\r\n";
            send(dest.getFd(), out.c_str(), out.size(), 0);
        }
        catch (std::runtime_error &)
        {
            throw std::runtime_error(": 401 " + nick + " " + target + " :No such nick\r\n"
            );
        }
    }
}
