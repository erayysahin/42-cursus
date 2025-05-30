#include "Zombie.hpp"

int	main(void)
{
	Zombie *zom = zombieHorde(5, "Alparslan");
	for (int i = 0; i < 5; i++)
		zom[i].announce();
	delete[] zom;
}