#include "commands.hpp"
#include <stdexcept> 
#include <exception>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include "utils.hpp"


bool CommandHandler::handleCommand(server &server, int &fd, const std::string &line)
{

    std::vector<Client> &clients = server.users;
    int idx = findClientIndex(clients, fd);
    if (idx == -1)
        return false;
    try
    {
        std::istringstream stream(line);
        std::string command;
        std::string argument;

        stream >> command;
        Utils::toUpperCase(command);
        std::getline(stream, argument);
        Utils::trim(argument);
        if (!clients[idx].isAuthenticated())
        {
            if (command != "PASS" && command != "NICK" && command != "USER" && command != "QUIT")
            {
                std::string err = ":" + server.getServername() + " 451 * :You have not registered\r\n";
                send(fd, err.c_str(), err.size(), 0);
                return false;
            }
        }
        if (command == "PASS")
        {
            handlePass(server, argument, idx);
            return true;
        }
        if (command == "NICK")
        {
            if (argument.empty())
                throw std::runtime_error(
                    ": 431 " + clients[idx].getNickname() + " :No nickname given\r\n");
            handleNick(server, clients, argument, idx);
            return true;
        }
        else if (command == "USER")
        {
            handleUser(server, clients, argument, idx);
            return true;
        }
        else if (command == "JOIN")
        {
            handleJoin(server, argument, idx);
            return true;
        }
        else if (command == "INVITE")
        {
            handleInvite(server, argument, idx);
            return true;
        }
        else if (command == "QUIT")
        {
            handleQuit(server, clients, argument, idx);
            return false;
        }
        else if (command == "PING")
        {
            handlePing(server, clients, argument, idx);
            return true;
        }
        else if (command[0] == '!')
        {
            argument = command + " " + argument;
            handleBot(server, clients, argument, idx);
            return true;
        }
        else if (command == "PRIVMSG")
        {
            handlePrivmsg(server, clients, argument, idx);
            return true;
        }
        else if (command == "KICK")
        {
            handleKick(server, argument, idx);
            return true;
        }
        else if (command == "TOPIC")
        {
            handleTopic(server, clients, argument, idx);
            return true;
        }
        else if (command == "PART")
        {
            handlePart(server, argument, idx);
            return true;
        }
        else if (command == "MODE")
        {
            handleMode(server, argument, idx);
            return true;
        }
        else if (command == "WHOAMI")
        {
            handleUserInfo(server, clients, idx);
            return true;
        }

        throw std::runtime_error(
            ": 421 " + clients[idx].getNickname() + " " + command + " :Unknown command\r\n");
    }
    catch (std::exception &ex)
    {
        const std::string msg = ex.what();
        if (send(fd, msg.c_str(), msg.size(), 0) < 0)
            std::cerr << "Mesaj gönderilemedi (catch içinde)\n";
        return false;
    }
}
