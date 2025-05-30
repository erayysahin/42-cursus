#include "commands.hpp"
#include <stdexcept>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>

void CommandHandler::handleUser(server &server, std::vector<Client> &clients, const std::string &line, int userIndex)
{
    Client &me = clients[userIndex];
    const std::string &nick = me.getNickname();
    std::istringstream ss(line);

    std::string username, hostname, servername;
    if (!(ss >> username >> hostname >> servername))
        throw std::runtime_error(": 461 " + nick + " USER :Not enough parameters\r\n");

    std::string realname;
    if (ss.peek() == ' ')
        ss.get();
    if (ss.peek() == ':')
    {
        ss.get();
        std::getline(ss, realname);
    }
    if (realname.empty())
        throw std::runtime_error(": 461 " + nick + " USER :Not enough parameters\r\n");

    me.setUsername(username);
    me.setRealname(realname);

    completeRegistration(server, me);
}

void CommandHandler::handleUserInfo(server &server, std::vector<Client> &clients, int userIndex)
{
    Client &me = clients[userIndex];

    const std::string &nick = me.getNickname();
    const std::string &user = me.getUsername();
    const std::string &realname = me.getRealname();

    std::string whoisUser = ":" + server.getServername() + " 311 " + nick + " " + nick + " " + user + " * :" + realname + "\r\n";
    send(me.getFd(), whoisUser.c_str(), whoisUser.size(), 0);

    std::string whoisServer = ":" + server.getServername() + " 312 " + nick + " " + nick + " " + server.getServername() + " :Server info" + "\r\n";
    send(me.getFd(), whoisServer.c_str(), whoisServer.size(), 0);

    std::string endWhois = ":" + server.getServername() + " 318 " + nick + " " + nick + " :End of /WHOIS list" + "\r\n";
    send(me.getFd(), endWhois.c_str(), endWhois.size(), 0);
}
