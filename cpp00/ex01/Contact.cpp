#include "PhoneBook.hpp"
#include "Contact.hpp"
bool set_alpha(const std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||  
              (str[i] >= 'A' && str[i] <= 'Z') || 
               str[i] == ' ' ||             
              (str[i] >= 9 && str[i] <= 12))) {   
            return false;
        }
    }
    return true;
}
bool set_ascii(const std::string& str) {
    for (size_t i = 0; i < str.length(); i++) 
    {
        if (!(str[i] >= 0 && str[i] <= 127)) {   
            return false;
        }
    }
    return true;
}

bool prompt_input(const std::string& prompt, std::string& target, bool (*validation)(const std::string&) = 0, const std::string& error_msg = "Invalid input.") {
    std::string input;
    do {
        std::cout << prompt << std::endl;
        if (safe_getline(input)) {
            std::cout << "EOF detected. Exiting user input..." << std::endl;
            return false;
        }
        if (!validation || validation(input)) {
            target = input;
        } else {
            std::cout << error_msg << std::endl;
        }
    } while (target.empty());
    return true;
}

void Contact::add_user() {
    if (!prompt_input("Please enter a first name:", this->_FirstName, set_alpha, "Please use only letters and spaces.")) return;
    if (!prompt_input("Please enter a last name:", this->_LastName, set_alpha, "Please use only letters and spaces.")) return;
    if (!prompt_input("Please enter a nickname:", this->_NickName,set_ascii)) return;
    if (!prompt_input("Please enter a phone number:", this->_PhoneNumber, ft_is_num, "Please use only numbers.")) return;
    if (!prompt_input("Please enter a darkest secret:", this->_DarkestSecret,set_ascii)) return;
}


void    Contact::print_user(Contact contact)
{
    std::cout << "First name: " << contact._FirstName << std::endl;
    std::cout << "Last name: " << contact._LastName << std::endl;
    std::cout << "Nickname: " << contact._NickName << std::endl;
    std::cout << "Phone number: " << contact._PhoneNumber << std::endl;
    std::cout << "Darkest secret: " << contact._DarkestSecret << std::endl;
}

void    Contact::print_list(Contact contact, int list_num)
{
    
    std::cout << "|" << std::setw(10) << std::setfill(' ') << list_num << "|";
    std::cout << std::setw(10) << resize_string(contact._FirstName) << "|";
    std::cout << std::setw(10) << resize_string(contact._LastName) << "|";
    std::cout << std::setw(10) << resize_string(contact._NickName) << "|";
    std::cout << std::endl;
    for (int j = 0; j < 4; j++) {
    std::cout << "|";
    std::cout << std::setw(11) <<std::setfill('-');
    }
    std::cout <<  "|" << std::endl;
}

std::string Contact::resize_string(std::string str)
{
	if (str.length() > 10)
	{
		str.resize(9);
		str += ".";
	}
	return str;
}