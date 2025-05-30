#include "commands.hpp"
#include <stdexcept>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>

void CommandHandler::handleTopic(server& server, std::vector<Client>& clients, const std::string& line, int idx)
{
    Client& me = clients[idx];
    const std::string& nick = me.getNickname();
    std::istringstream ss(line);

    std::string channelName;
    if (!(ss >> channelName) || channelName.empty())
        throw std::runtime_error(": 461 " + nick + " TOPIC :Not enough parameters\r\n");

    std::vector<Channel>::iterator it = server.Channels.begin();
    for (; it != server.Channels.end(); ++it)
    {
        if (it->getChannelName() == channelName)
            break;
    }
    if (it == server.Channels.end())
        throw std::runtime_error(": 403 " + nick + " " + channelName + " :No such channel\r\n");

    Channel& ch = *it;

    if (!ch.isUser(nick))
        throw std::runtime_error(": 442 " + nick + " " + channelName + " :You're not on that channel\r\n");

    std::string topic;
    std::getline(ss, topic);
    Utils::trim(topic);

    if (topic.empty())
    {
        const std::string& curr = ch.getChannelTopic();
        std::string reply;
        if (!curr.empty())
            reply = ":" + server.getServername() + " 332 " + nick + " " + channelName + " :" + curr + "\r\n";
        else
            reply = ":" + server.getServername() + " 331 " + nick + " " + channelName + " :No topic is set\r\n";
        send(me.getFd(), reply.c_str(), reply.size(), 0);
        return;
    }

    if ( !ch.getTopicRestriction() || (ch.isOperator(nick) || ch.getCreator() == nick) ) {
        ch.setChannelTopic(topic);
    } else {
        throw std::runtime_error(": 482 " + nick + " " + channelName + " :You're not channel operator\r\n");
    }

    std::string notice = ":" + nick + " TOPIC " + channelName + " :" + topic + "\r\n";

    const std::vector<std::string>& users = ch.getUsers();
    for (std::vector<std::string>::size_type j = 0; j < users.size(); ++j)
    {
        Client& c = server.getClientByNick(users[j]);
        send(c.getFd(), notice.c_str(), notice.size(), 0);
    }
}
