#include "commands.hpp"
#include <stdexcept>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
void CommandHandler::handleJoin(server &server, const std::string &line, int userIndex)
{
    Client &me = server.users[userIndex];
	std::istringstream ss(line);
	std::string channelName, key;
    ss >> channelName;
    
    const std::string &nick = me.getNickname();

    if (channelName.empty())
        throw std::runtime_error(": 461 " + nick + " JOIN :Not enough parameters\r\n");

    if (channelName[0] != '#')
        throw std::runtime_error(": 476 " + nick + " " + channelName + " :Bad Channel Mask\r\n");

    Channel *chPtr = NULL;
    for (std::vector<Channel>::iterator it = server.Channels.begin();
         it != server.Channels.end(); ++it)
    {
        if (it->getChannelName() == channelName)
        {
            chPtr = &(*it);
            break;
        }
    }
    if (chPtr == NULL)
    {
        server.Channels.push_back(Channel(channelName));
        chPtr = &server.Channels.back();
        chPtr->setCreator(nick);
    }
    Channel &ch = *chPtr;
    if (ch.getInviteOnly() && !ch.isOperator(nick) && !ch.isInvited(nick))
        throw std::runtime_error(": 473 " + nick + " " + channelName + " :Cannot join channel (+i)\r\n");
    if (ch.isUser(me.getNickname()))
        return;

	if(ch.isKeyActive())
	{
		ss >> key;
		if (ss.fail() || !ss.eof())
		    throw std::runtime_error(": 475 " + nick + " " + channelName + " :Cannot join channel (+k)\r\n");
		if(key != ch.getChannelKey())
		    throw std::runtime_error(": 475 " + nick + " " + channelName + " :Cannot join channel (+k)\r\n");

	}
    ch.addUser(nick);

    if (ch.isInvited(nick))
        ch.removeInvite(nick);

    std::string joinMsg = ":" + nick + " JOIN " + channelName + "\r\n";
    std::vector<std::string> users = ch.getUsers();
    for (std::vector<std::string>::size_type j = 0;
         j < users.size(); ++j)
    {
        Client &c = server.getClientByNick(users[j]);
        send(c.getFd(), joinMsg.c_str(), joinMsg.size(), 0);
    }
    std::ostringstream oss;
    oss << ":" << server.getServername() << " 353 " << nick<< " = " << channelName << " :";
    for (size_t i = 0; i < ch.getUsers().size(); ++i)
    {
        if (ch.getCreator() == ch.getUsers()[i])
            oss << " +";
        if (ch.isOperator(ch.getUsers()[i]))
            oss << " @";
        oss << ch.getUsers()[i];
        if (i + 1 < ch.getUsers().size())
            oss << " ";
    }
    oss << "\r\n";
    send(server.users[userIndex].getFd(), oss.str().c_str(), oss.str().size(), 0);
    std::ostringstream endnames;
    endnames << ":" << server.getServername() << " 366 " << nick << " " << channelName << " :End of /NAMES list\r\n";
    send(me.getFd(), endnames.str().c_str(), endnames.str().size(), 0);
}
