#include "PhoneBook.hpp"

int safe_getline(std::string &str)
{
	getline(std::cin, str);
    
    if (std::cin.eof())
    {
        return 1;
    }

    return 0;
}
bool ft_is_num(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true; 
}
void    Phonebook::initial_loop()
{
    std::string input;
    index = -1;
    total = -1;
    while(1)
    {
        if (std::cin.eof())
            break;
        if (index == 7)
            index = -1;
        std::cout << "Please select an option: ADD, SEARCH or EXIT" << std::endl;
        if(safe_getline(input))
            break;
        if(input == "ADD")
        {
            contacts[++index].add_user();
            if (total < index)
                total = index;
        }
        else if(input == "SEARCH")
        {
            search_user(contacts, (total));
        }
        else if(input == "EXIT")
            break ;
        else
            std::cout << "Wrong input :(" << std::endl;
    }
}

void Phonebook::search_user(Contact contacts[8], int index)
{
    std::string input;
    int user;
for (int j = 0; j < 4; j++) {
    std::cout << "|";
    std::cout << std::setw(11) << std::setfill('-');
}
    std::cout << "|" << std::endl;
    std::cout << "|" <<std::setw(10) << std::setfill(' ') << "Index";
    std::cout << "|" <<std::setw(10) << "First Name";
    std::cout << "|" <<std::setw(10) << "Last Name";
    std::cout << "|" <<std::setw(10) << "Nick Name";
    std::cout <<  "|" << std::endl;
    for (int j = 0; j < 4; j++) {
    std::cout << "|";
    std::cout << std::setw(11) <<std::setfill('-');
}
    std::cout <<  "|" << std::endl;
    for (int i = 0; i <= index; i++) {
        contacts->print_list(contacts[i], i);
    }
    std::cout << "Please select an user: " << std::endl;
    safe_getline(input);
    user = std::atoi(input.c_str());
    if ((ft_is_num(input) == true) && (user >= 0 && user <= index) && !input.empty())
        contacts[user].print_user(contacts[user]);
    else
        std::cout << "learn to type ;)" << std::endl;
    
}
