#include "commands.hpp"
#include "utils.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>

void CommandHandler::handleBot(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex)
{
    std::istringstream ss(argument);
    std::string command;

    ss >> command;
    if (ss.fail() || command.empty())
    {
        throw std::runtime_error("Hata: Lütfen geçerli bir komut giriniz.");
    }

    if (command == "!HELP")
    {
        std::string cmd;
        ss >> cmd;
        Utils::toUpperCase(cmd);
        if (ss.fail() || cmd.empty() || !ss.eof())
            throw std::runtime_error("Hata: Lütfen geçerli bir komut giriniz.");
        helpBot(cmd, server, clients, userIndex);
    }
    else if (command == "!DICT")
    {
        std::string word;
        ss >> word;
        if (ss.fail() || word.empty() || !ss.eof())
            throw std::runtime_error("Hata: Lütfen cevirmek istediginiz bir komutu girin");
        dictBot(server, word, clients, userIndex);
    }
}

void helpBot(std::string &help, server &server, std::vector<Client> &clients, int userIndex)
{
    std::string msg;
    if (help == "KOMUTLAR")
        msg = "Komutlar: JOIN - KICK - MODE - NICK - PART - PASS - TOPIC - USER\r\n";
    else if (help == "JOIN")
        msg = "JOIN: Bir kanala girmek için kullanılır.\nKullanım: JOIN <kanal adı> \r\n";
    else if (help == "KICK")
        msg = "KICK: Kanaldan kullanıcı atmak için kullanılır.\nKullanım: KICK <kanal adı> <kullanıcı adı>\r\n";
    else if (help == "MODE")
    {
        msg = R"(
            +-----+----------------------------+----------------------------------------+
            | Mod | Açıklama                   | Kullanım                              |
            +-----+----------------------------+----------------------------------------+
            | -k  | Kanalı kilitler            | MODE <kanal adı> +k                   |
            | -l  | Katılım limiti koyar       | MODE <kanal adı> +l <limit>           |
            | -i  | Kanal herkese kapalı       | MODE <kanal adı> +i                   |
            | -t  | Konuyu sadece op değiştirir| MODE <kanal adı> +t                   |
            | -o  | Kullanıcıyı operatör yapar | MODE <kanal adı> -o <kullanıcı adı>   |
            +-----+----------------------------+----------------------------------------+
            )"
              "\r\n";
    }
    else if (help == "NICK")
        msg = "NICK: Kullanıcı adını değiştirmek için kullanılır.\nKullanım: NICK <yeni kullanıcı adı>\r\n";
    else if (help == "PART")
        msg = "PART: Kanaldan ayrılmak için kullanılır.\nKullanım: PART <kanal adı>\r\n";
    else if (help == "PASS")
        msg = "PASS: Şifre girişi için kullanılır.\nKullanım: PASS <şifre>\r\n";
    else if (help == "TOPIC")
        msg = "TOPIC: Kanal başlığını değiştirmek için kullanılır.\nKullanım: TOPIC <kanal adı> <yeni başlık>\r\n";
    else if (help == "USER")
        msg = "USER: Kullanıcı bilgilerini ayarlamak için kullanılır.\nKullanım: USER <kullanıcı adı> <host> <gerçek ad>\r\n";
    else
        msg = "Hata: Geçersiz komut. Lütfen geçerli bir komut giriniz.\r\n";
    send(server.users[userIndex].getFd(), msg.c_str(), msg.size(), 0);
}

void dictBot(server &server, std::string &word, std::vector<Client> &clients, int userIndex)
{
    Client &me = server.users[userIndex];

    std::ifstream dictFile("words.txt");
    if (!dictFile.is_open())
    {
        std::cerr << "dosya açılmaı" << std::endl;
        return;
    }

    std::map<std::string, std::string> dataMap;

    std::string line;
    while (std::getline(dictFile, line))
    {
        std::size_t dPos = line.find("=");

        if (dPos != std::string::npos)
        {
            std::string key = line.substr(0, dPos);
            std::string value = line.substr(dPos + 1);

            dataMap[key] = value;
        }
    }
    dictFile.close();

    std::map<std::string, std::string>::iterator it = dataMap.find(word);

    if (it != dataMap.end())
    {
        std::string w = it->first + " => " + it->second + "\r\n";
        send(me.getFd(), w.c_str(), w.size(), 0);
    }
    else
    {
        static const char msg[] = "eşleşen kelime bulunamadı\r\n";
        send(me.getFd(), msg, sizeof(msg) - 1, 0);
    }
}