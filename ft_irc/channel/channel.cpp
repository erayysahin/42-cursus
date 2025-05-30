#include "channel.hpp"

Channel::Channel(const std::string &name)
    : _channelName(name), _key(false), _limits(false), _inviteOnlyMode(false), _topicRestriction(false), _userLimit(0) {}

void Channel::addUser(const std::string &nick)
{
    if (_limits && _users.size() >= _userLimit)
    {
        throw std::runtime_error(": 471 " + nick + " " + _channelName + " :Cannot join channel (+l)\r\n");
        return;
    }

    _users.push_back(nick);
}

void Channel::removeUser(const std::string &nick)
{
    _users.erase(std::remove(_users.begin(), _users.end(), nick), _users.end());
}

const std::vector<std::string> &Channel::getUsers() const
{
    return _users;
}

void Channel::setCreator(const std::string &nick)
{
    _creator = nick;
}

std::string Channel::getCreator() const
{
    return _creator;
}

void Channel::setChannelTopic(const std::string &newTopic)
{
    _topic = newTopic;
}

std::string Channel::getChannelTopic() const
{
    return _topic;
}

void Channel::setChannelUserLimit(const size_t limit)
{
    if (limit > 0)
    {
        _limits = true;
        _userLimit = limit;
    }
    else
    {
        _limits = false;
        _userLimit = 0;
    }
}

size_t Channel::getChannelUserLimit() const
{
    return _userLimit;
}

void Channel::setInviteOnly(bool isInviteOnly)
{
    _inviteOnlyMode = isInviteOnly;
}

bool Channel::getInviteOnly() const
{
    return _inviteOnlyMode;
}

void Channel::setTopicRestriction(bool restrictTopic)
{
    _topicRestriction = restrictTopic;
}

bool Channel::getTopicRestriction() const
{
    return _topicRestriction;
}

void Channel::rmvChannelOperator(const std::string &user)
{
    _operators.erase(std::remove(_operators.begin(), _operators.end(), user), _operators.end());
}

void Channel::addChannelOperator(const std::string &user)
{
    if (!isOperator(user))
    {
        _operators.push_back(user);
    }
}

bool Channel::isOperator(const std::string &user) const
{
    return std::find(_operators.begin(), _operators.end(), user) != _operators.end();
}

void Channel::setChannelKey(bool isKey, const std::string &key)
{
    _key = isKey;
    if (_key)
    {
        _channelKey = key;
    }
}


std::string Channel::getChannelKey()
{
    return _channelKey;
}

bool Channel::isKeyActive() const
{
    return _key;
}

bool Channel::isUser(const std::string &nick) const
{
    return std::find(_users.begin(), _users.end(), nick) != _users.end();
}

void Channel::addInvite(const std::string &nick)
{
    if (!isInvited(nick))
        _inviteList.push_back(nick);
}

bool Channel::isInvited(const std::string &nick) const
{
    return std::find(_inviteList.begin(), _inviteList.end(), nick) != _inviteList.end();
}

void Channel::removeInvite(const std::string &nick)
{
    _inviteList.erase(
        std::remove(_inviteList.begin(), _inviteList.end(), nick),
        _inviteList.end());
}
