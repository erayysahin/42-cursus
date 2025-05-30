#include "commands.hpp"
#include <stdexcept>    // std::runtime_error
#include <sstream>      // std::istringstream
#include <unistd.h>     // send()
#include <sys/socket.h> // send()
#include <vector>
#include <string>

void CommandHandler::broadcastNamesReply(server &server, const Channel &ch)
{
    const std::vector<std::string> &users = ch.getUsers();
    for (std::vector<std::string>::const_iterator ui = users.begin(); ui != users.end(); ++ui)
    {
        const std::string &receiver = *ui;
        std::ostringstream oss;
        oss << ":" << server.getServername()
            << " 353 " << receiver
            << " = " << ch.getChannelName() << " :";
        for (size_t j = 0; j < users.size(); ++j)
        {
            const std::string &usr = users[j];
            if (ch.getCreator() == usr)
                oss << "+";
            else if (ch.isOperator(usr))
                oss << "@";
            oss << usr;
            if (j + 1 < users.size())
                oss << " ";
        }
        oss << "\r\n";
        Client &c = server.getClientByNick(receiver);
        send(c.getFd(), oss.str().c_str(), oss.str().size(), 0);
        std::ostringstream endnames;
        endnames << ":" << server.getServername() << " 366 " << receiver << " " << ch.getChannelName() << " :End of /NAMES list\r\n";
        send(c.getFd(), endnames.str().c_str(), endnames.str().size(), 0);
    }
}

void CommandHandler::handlePart(server &server, const std::string &line, int userIndex)
{
    Client &me = server.users[userIndex];
    const std::string &nick = me.getNickname();
    std::istringstream ss(line);

    std::string channelName;
    if (!(ss >> channelName) || channelName.empty())
        throw std::runtime_error(": 461 " + nick + " PART :Not enough parameters\r\n");

    std::string comment;
    if (ss.peek() == ' ')
        ss.get();
    std::getline(ss, comment);
    if (!comment.empty() && comment[0] == ':')
        comment.erase(0, 1);

    std::vector<Channel>::iterator it = server.Channels.begin();
    for (; it != server.Channels.end(); ++it)
    {
        if (it->getChannelName() == channelName)
            break;
    }
    if (it == server.Channels.end())
        throw std::runtime_error(": 403 " + nick + " " + channelName + " :No such channel\r\n");

    Channel &ch = *it;
    if (!ch.isUser(nick))
        throw std::runtime_error(": 442 " + nick + " " + channelName + " :You're not on that channel\r\n");

    std::vector<std::string> targets = ch.getUsers();
    std::string partMsg = ":" + nick + " PART " + channelName;
    if (!comment.empty())
        partMsg += " :" + comment;
    partMsg += "\r\n";

    bool wasCreator = (ch.getCreator() == nick);
    ch.removeUser(nick);

    if (ch.isOperator(nick))
        ch.rmvChannelOperator(nick);

    if (ch.getUsers().empty())
        server.Channels.erase(it);
    else if (wasCreator)
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

    for (std::vector<std::string>::size_type ui = 0; ui < targets.size(); ++ui)
    {
        Client &c = server.getClientByNick(targets[ui]);
        send(c.getFd(), partMsg.c_str(), partMsg.size(), 0);
    }
    broadcastNamesReply(server, ch);
}
