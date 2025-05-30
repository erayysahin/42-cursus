#ifndef SERVER_HPP
# define SERVER_HPP
#include "commands/commands.hpp"
#include <iostream>
#include <exception>
#include <sys/socket.h>
#include <vector>

class server
{
    private:
        std::string _servername;
        std::string print;
        int port;
        std::string _serverPassword;//-----

    public:
        Client& getClientByNick(const std::string& nick);
        std::string getServerPassword()const;
        void setServerPassword(const std::string& ServerPass);//-----
        server();
        void writer();
        void portcontroller(const char* str);
        void connectport();
        void clientfd(int fd);
        std::string read_data(int fd);
        Channel& getChannel(std::string& channel);
        void setServername(std::string servername);
        std::string getServername() const;

        std::vector<Client> users;
        std::vector<Channel> Channels;

    class notenough : public std::exception
    {
        private:
            std::string message;

        public:
            notenough(const std::string& msg);
            const char* what() const throw();
            ~notenough();
    };
};

#endif
