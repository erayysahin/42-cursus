#include "Zombie.hpp"

Zombie::Zombie()
{
	std::cout << this->_name << "was born" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << this->_name << " Zombie died" << std::endl;
}

void Zombie::setName(std::string name)
{
	this->_name = name;
}

void Zombie::announce(void)
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}