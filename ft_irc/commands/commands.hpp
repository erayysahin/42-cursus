#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../client/client.hpp"
#include "../server.hpp"
#include "../channel/channel.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

class server;

class CommandHandler
{
    std::vector<std::string> channel;

public:
    bool handleCommand(server &server, int &fd, const std::string &line);

private:
    void broadcastNamesReply(server &server, const Channel &ch);
    void completeRegistration(server &server, Client &me);
    void handleDccReceive(std::istringstream &ss, server &server, std::vector<Client> &clients, int userIndex);
    void handlePing(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex);

    void handlePass(std::vector<Client> &client, std::string &args, int i);
    void handleNick(server &server, std::vector<Client> &clients, const std::string &newNick, int userIndex);
    void firstnick(server &srv,
                   std::vector<Client> &clients,
                   const std::string &newNick,
                   int userIndex);
    void handleCap(server &server, const std::string &arg, int i);
    void handleQuit(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex);

    void handleJoin(server &server, const std::string &line, int userIndex);
    void channelmsg(std::vector<Client> &client, std::string channelmsg, int idx);
    void handlePart(server &server, const std::string &line, int userIndex);
    void handleKick(server &server, std::string &channelName, int i);
    void handleInvite(server &server, std::string &arg, int i);
    void handleUser(server &server, std::vector<Client> &client, const std::string &std, int i);
    bool handlePass(server &server, std::string &serverPassword, int i);
    void handleUserInfo(server &server, std::vector<Client> &client, int userIndex);

    void handlePrivmsg(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex);

    void handleTopic(server &server, std::vector<Client> &clients, const std::string &line, int i);
    void handleMode(server &server, const std::string &line, int i);

    void handleBot(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex);
};
int clientmsg(int fd, const std::string &msg);
int findClientIndex(std::vector<Client> &clients, int actualFd);

void helpBot(std::string &help, server &server, std::vector<Client> &clients, int userIndex);
void dictBot(server &server, std::string &word, std::vector<Client> &clients, int userIndex);

#endif
