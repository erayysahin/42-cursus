#include "commands.hpp"
#include <iostream>
void CommandHandler::handleInvite(server &server, std::string &arg, int i)
{
    std::istringstream ss(arg);
    std::string chanName, targetNick;
    ss >> targetNick >> chanName;

    Client &me = server.users[i];
    const std::string &nick = me.getNickname();

    if (chanName.empty() || targetNick.empty())
        throw std::runtime_error(": 461 " + nick + " INVITE :Not enough parameters\r\n");

    Channel &ch = server.getChannel(chanName);

    if (!ch.isUser(nick))
        throw std::runtime_error(": 442 " + nick + " " + chanName + " :You're not on that channel\r\n");

    if (!(ch.isOperator(nick) || ch.getCreator() == nick))
        throw std::runtime_error(": 482 " + nick + " " + chanName + " :You're not channel operator\r\n");

    Client &target = server.getClientByNick(targetNick);

    ch.addInvite(targetNick);

    std::string inviteMsg = ":" + nick + " INVITE " + targetNick + " " + chanName + "\r\n";
    send(target.getFd(), inviteMsg.c_str(), inviteMsg.size(), 0);

    std::string ack = ":" + server.getServername() + " 341 " + nick + " " + targetNick + " " + chanName + "\r\n";
    send(me.getFd(), ack.c_str(), ack.size(), 0);
}