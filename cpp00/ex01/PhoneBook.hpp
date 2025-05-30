#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class Phonebook
{
    private:
        Contact contacts[8];
        int     index;
        int     total;
        void search_user(Contact contacts[8], int index);
    public:
        void initial_loop();
};

#endif