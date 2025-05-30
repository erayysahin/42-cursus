#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <iostream>
#include <vector>
#include <algorithm>  

class Channel
{
    private:

        bool _key;
        bool _limits;
        bool _inviteOnlyMode;
        bool _topicRestriction;

        std::string _channelName;
        std::string _topic;
        std::string _channelkey;
        size_t _userLimit;
        std::string _creator;
        std::string _channelKey;

        std::vector<std::string> _users;
        std::vector<std::string> _operators;
        std::vector<std::string> _clients;
        std::vector<std::string>    _inviteList;



        public:


        Channel(const std::string& name);

        const std::string& getChannelName() const
        {return _channelName;}

        void addUser(const std::string& nick);
        void removeUser(const std::string& nick);


        const std::vector<std::string>& getUsers() const ;


        void setChannelTopic(const std::string& newTopic);
        std::string getChannelTopic() const ;

        void setChannelUserLimit( const size_t limit);
        size_t getChannelUserLimit() const;
        void setTopicRestriction(bool restrictTopic);
        bool getTopicRestriction() const;


        void setInviteOnly(bool isInviteOnly);
        bool getInviteOnly() const;

        void addChannelOperator(const std::string& user);
        void rmvChannelOperator(const std::string& user);
        bool isOperator(const std::string& user) const;

        void setCreator(const std::string &creator);
        std::string getCreator()const ;

        void setChannelKey(bool isKey, const std::string& key);
        bool isKeyActive() const;
        std::string getChannelKey();

        bool isUser(const std::string& nick) const;


        void addInvite(const std::string& nick);
        bool isInvited(const std::string& nick) const;
        void removeInvite(const std::string& nick);


};
#endif
