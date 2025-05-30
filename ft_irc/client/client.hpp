#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <set>
#include <vector>
#include "../channel/channel.hpp"
class Client
{
public:
    Client();
    Client(int fd);

    int getFd() const;
    const std::string &getNickname() const;
    const std::string &getUsername() const;
    const std::string &getRealname() const;
    const std::string &getBuffer() const;
    std::string& getBuffer();


    bool isAuthenticated() const;
    bool isPasswordPassed() const;

    void setNickname(const std::string &nick);
    void setUsername(const std::string &user);
    void setRealname(const std::string &real);
    void appendToBuffer(const std::string &data);
    void clearBuffer();
    void setAuthenticated(bool value);
    void setPasswordPassed(bool value);


private:
    int _fd;
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _buffer;
    bool _authenticated;
    bool _passwordPassed;
};

#endif
