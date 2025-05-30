#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
	this->_name = name;
    std::cout << "HumanB " << _name << " has been created." << std::endl;
	this->_weapon = NULL;
}
HumanB::~HumanB()
{
	std::cout << "HumanB " << this->_name << " has been destroyed." << std::endl;
}
void HumanB::attack()
{
	if (this->_weapon)
		std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
    this->_weapon = &weapon;
}