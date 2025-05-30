#include "ScavTrap.hpp"
#include <iostream>

ScavTrap::ScavTrap(const std::string &name)
    : ClapTrap(name)
{
    _hit = 100;
    _energy = 50;
    _attack = 20;
    std::cout << "ScavTrap " << _name << " has entered battle mode!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other)
    : ClapTrap(other)
{
    std::cout << "ScavTrap copy constructor called!" << std::endl;

}

ScavTrap &ScavTrap::operator=(const ScavTrap &other)
{
    std::cout << "ScavTrap copy assignment operator called!" << std::endl;
    if (this != &other) {
        ClapTrap::operator=(other); 
    }
    return *this;
}
void ScavTrap::attack(const std::string& target)
{
    if(_hit > 0 && _energy > 0)
    {
    _energy -= 1;
    std::cout << "ScavTrap " << _name << " aggressively attacks " << target
                  << ", causing " << _attack << " points of damage!" << std::endl;
    return;
    }
    std::cout << _name << "does not have sufficient conditions to attack" << std::endl;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << _name << " has been deactivated!" << std::endl;
}
void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << _name << " is now in Gate keeper mode!" << std::endl;
}