#include "Weapon.hpp"

Weapon::Weapon(std::string type)
{
    this->_type = type;
}
Weapon::~Weapon(void)
{
    std::cout << "Weapon Destroyed" << std::endl;
}

const std::string &Weapon::getType(void) const
{
    return (this->_type);
}

void Weapon::setType(std::string type)
{
    this->_type = type;
}