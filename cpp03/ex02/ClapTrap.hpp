#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>

class ClapTrap
{
protected:
   std::string _name;
   unsigned int _hit;
   unsigned int _energy;
   unsigned int _attack;
public:
    ClapTrap(std::string const &name);
    ~ClapTrap();
    ClapTrap(const ClapTrap &other);
    ClapTrap &operator=(const ClapTrap &other);
    void attack(const std::string& target); 
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};




#endif