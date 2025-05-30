#include "commands.hpp"
#include <unistd.h>
#include  <sys/socket.h>

void  CommandHandler::completeRegistration(server &server, Client &me) {
if (!me.isAuthenticated() && me.isPasswordPassed() && !me.getNickname().empty() && !me.getUsername().empty() && !me.getRealname().empty())
{
    me.setAuthenticated(true);
    const std::string nick  = me.getNickname();
    const std::string servn = server.getServername();
    std::string msg;

    msg = ":" + servn + " 001 " + nick + " :Welcome to the IRC Network, " + nick + "!\r\n";
    send(me.getFd(), msg.c_str(), msg.size(), 0);

    msg = ":" + servn + " 002 " + nick + " :Your host is " + servn + ", running version 1.0\r\n";
    send(me.getFd(), msg.c_str(), msg.size(), 0);

    msg = ":" + servn + " 003 " + nick + " :This server was created on " __DATE__ " " __TIME__ "\r\n";
    send(me.getFd(), msg.c_str(), msg.size(), 0);

    msg = ":" + servn + " 004 " + nick + " " + servn + " ircserv 0.1 o o\r\n";
    send(me.getFd(), msg.c_str(), msg.size(), 0);
}

}
