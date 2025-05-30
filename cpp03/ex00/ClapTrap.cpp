#include "ClapTrap.hpp"
#include <iostream>
ClapTrap::ClapTrap(const std::string &name):_name(name),_hit(10),_energy(10),_attack(0)
{
    std::cout << "ClapTrap " << _name << " is constructed!" << std::endl;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << _name << " is destroyed!" << std::endl;
}
ClapTrap::ClapTrap(const ClapTrap &other)
{
    std::cout << "ClapTrap copy constructor called!\n";
    *this = other; 
}
ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    std::cout << "ClapTrap copy assignment operator called!\n";
    if (this != &other) {
        this->_name = other._name;
        this->_hit = other._hit;
        this->_energy = other._energy;
        this->_attack = other._attack;
    }
    return *this;
}

void ClapTrap::attack(const std::string& target)
{
    if(_hit > 0 && _energy > 0)
    {
    _energy -= 1;
    std::cout << "ClapTrap " << _name << " attacks " << target
              << ", causing " << _attack << " points of damage!" << std::endl;
    return;
    }
    std::cout << _name << "does not have sufficient conditions to attack" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if(0 < _hit - amount)
        _hit -= amount;
    else
        _hit = 0;
    std::cout << "ClapTrap " << _name << " takes " << amount
              << " points of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if(_hit > 0 && _energy > 0)
    {
        _energy -= 1;
        _hit += amount;
        std::cout << "ClapTrap " << _name << " is repaired for " << amount
              << " hit points!" << std::endl;
    }      
}