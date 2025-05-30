#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <iostream>
# include <iomanip>
# include <cstdlib>

class Contact
{
    private:
        std::string _FirstName;
        std::string _LastName;
        std::string _NickName;
        std::string _PhoneNumber;
        std::string _DarkestSecret;
    public:
        std::string resize_string(std::string str);
        void    add_user();
        void    print_user(Contact contact);
        void    print_list(Contact contact, int list_num);
};
int     safe_getline(std::string &str);
bool ft_is_num(const std::string& str);


#endif