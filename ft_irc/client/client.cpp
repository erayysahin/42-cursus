#include "client.hpp"
#include <algorithm>

Client::Client(int fd) : _fd(fd), _authenticated(false), _passwordPassed(false)
{
}

int Client::getFd() const
{
    return _fd;
}

const std::string &Client::getNickname() const
{
    return this->_nickname;
}

const std::string &Client::getUsername() const
{
    return this->_username;
}

const std::string &Client::getRealname() const
{
    return this->_realname;
}



const std::string &Client::getBuffer() const
{
    return this->_buffer;
}
std::string &Client::getBuffer()
{
    return _buffer;
}
bool Client::isAuthenticated() const
{
    return _authenticated;
}

bool Client::isPasswordPassed() const
{
    return _passwordPassed;
}

void Client::setNickname(const std::string &nick)
{
    _nickname = nick;
}

void Client::setUsername(const std::string &user)
{
    _username = user;
}

void Client::setRealname(const std::string &realname)
{
    _realname = realname;
}



void Client::appendToBuffer(const std::string &data)
{
    _buffer += data;
} //----

void Client::clearBuffer()
{
    _buffer.clear();
} //------

void Client::setAuthenticated(bool value)
{
    _authenticated = value;
}

void Client::setPasswordPassed(bool value)
{
    _passwordPassed = value;
}
