// commands.cpp

#include "commands.hpp"
#include <stdexcept> 
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>

void CommandHandler::handleMode(server &server, const std::string &line, int userIndex)
{
    std::istringstream ss(line);
    std::string channelName, modeStr, param;

    ss >> channelName >> modeStr;
    Client &me = server.users[userIndex];
    const std::string &nick = me.getNickname();

    if (channelName.empty() || modeStr.empty())
        throw std::runtime_error(": 461 " + nick + " MODE :Not enough parameters\r\n");

    std::vector<Channel>::iterator it = server.Channels.begin();
    for (; it != server.Channels.end(); ++it)
    {
        if (it->getChannelName() == channelName)
            break;
    }
    if (it == server.Channels.end())
        throw std::runtime_error(": 403 " + nick + " " + channelName + " :No such channel\r\n");

    Channel &ch = *it;

    bool isOp = (nick == ch.getCreator()) || ch.isOperator(nick);

    if (modeStr.size() != 2 ||
        (modeStr[0] != '+' && modeStr[0] != '-'))
        throw std::runtime_error(": 472 " + nick + " " + modeStr + " :is unknown mode char to me\r\n");

    char sign = modeStr[0];
    char mode = modeStr[1];

    if (mode == 'k')
    {
        if (!isOp)
            throw std::runtime_error(": 482 " + nick + " " + channelName + " :You're not channel operator\r\n");
        if (sign == '+')
        {
            if (!(ss >> param) || param.empty() || !ss.eof())
                throw std::runtime_error(": 461 " + nick + " MODE :Not enough parameters\r\n");
            ch.setChannelKey(1, param);
        }
        else
        {
            ch.setChannelKey(0, "");
        }
    }
    else if (mode == 'l')
    {
        if (!isOp)
            throw std::runtime_error(": 482 " + nick + " " + channelName + " :You're not channel operator\r\n");
        if (sign == '+')
        {
            unsigned int limit;
            if (!(ss >> limit))
                throw std::runtime_error(": 461 " + nick + " MODE :Not enough parameters\r\n");
            ch.setChannelUserLimit(limit);
        }
        else
        {
            ch.setChannelUserLimit(0);
        }
    }
    else if (mode == 'i')
    {
        if (!isOp)
            throw std::runtime_error(": 482 " + nick + " " + channelName + " :You're not channel operator\r\n");
        ch.setInviteOnly(sign == '+');
    }
    else if (mode == 't')
    {
        if (!isOp)
            throw std::runtime_error(": 482 " + nick + " " + channelName + " :You're not channel operator\r\n");
        ch.setTopicRestriction(sign == '+');
    }
    else if (mode == 'o')
    {
        if (!isOp)
            throw std::runtime_error(": 482 " + nick + " " + channelName + " :You're not channel operator\r\n");
        if (!(ss >> param) || param.empty())
            throw std::runtime_error(": 461 " + nick + " MODE :Not enough parameters\r\n");
        if (!ch.isUser(param))
            throw std::runtime_error(": 461 MODE " + param + " They aren't on that channel \r\n");
        if (sign == '+')
            ch.addChannelOperator(param);
        else
            ch.rmvChannelOperator(param);
    }
    else
        throw std::runtime_error(": 472 " + nick + " " + modeStr + " :is unknown mode char to me\r\n");

    std::string notice = ":" + nick + " MODE " + channelName + " " + modeStr;
    if (!param.empty() && (mode == 'k' || mode == 'l' || mode == 'o'))
        notice += " " + param;
    notice += "\r\n";
    const std::vector<std::string> &users = ch.getUsers();
    for (std::vector<std::string>::size_type idx2 = 0;
         idx2 < users.size(); ++idx2)
    {
        Client &c = server.getClientByNick(users[idx2]);
        send(c.getFd(), notice.c_str(), notice.size(), 0);
    }
}
