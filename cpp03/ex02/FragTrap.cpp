#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap(const std::string &name)
    : ClapTrap(name)
{
    _hit = 100;
    _energy = 100;
    _attack = 30;
    std::cout << "FragTrap " << _name << " is constructed!" << std::endl;
}

FragTrap::FragTrap(const FragTrap &other)
    : ClapTrap(other)
{
    std::cout << "FragTrap copy constructor called!" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other)
{
    std::cout << "FragTrap copy assignment operator called!" << std::endl;
    if (this != &other)
    {
        ClapTrap::operator=(other); 
    }
    return *this;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << _name << " is destroyed!" << std::endl;
}

void FragTrap::attack(const std::string &target)
{
    if (_hit > 0 && _energy > 0)
    {
        _energy--;
        std::cout << "FragTrap " << _name << " attacks " << target
                  << ", causing " << _attack << " points of damage!" << std::endl;
    }
    else
    {
        std::cout << "FragTrap " << _name << " doesn't have enough hit points or energy to attack!" << std::endl;
    }
}
void FragTrap::highFivesGuys(void)
{   if (_hit > 0 && _energy > 0)
    {
    std::cout << "FragTrap " << _name << " requests a high five! Positive vibes only!" << std::endl;
    }
    else
    {
        std::cout << "FragTrap " << _name << " is in no condition to high-five." << std::endl;
    }
}
