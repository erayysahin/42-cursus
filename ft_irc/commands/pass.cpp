#include "commands.hpp"

bool CommandHandler::handlePass(server& server, std::string& serverPassword, int i)
{
    Client& me = server.users[i];

    if (me.isPasswordPassed())
    {
        static const char already[] = "ERROR :Password already set\r\n";
        send(me.getFd(), already, sizeof(already) - 1, 0);
        return false;
    }

    if (server.getServerPassword() == serverPassword)
    {
        me.setPasswordPassed(true);
        static const char ok[] = "NOTICE :Password accepted\r\n";
        send(me.getFd(), ok, sizeof(ok) - 1, 0);
        completeRegistration(server, me);
        return true;
    }
    else
    {
        throw std::runtime_error(": 464 " + me.getNickname() + " :Password incorrect\r\n"
        );
    }
}
