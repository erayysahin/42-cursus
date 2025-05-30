#include "Zombie.hpp"

int	main(void)
{
	{
		Zombie	z;
		z.setName("Zombie1");
		z.announce();
	}
	Zombie	*ptr;
	ptr = newZombie("Zombie2");
	ptr->announce();
	delete(ptr);
	randomChump("Zombie3");
	return (0);
}