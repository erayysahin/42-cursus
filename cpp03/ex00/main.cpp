#include "ClapTrap.hpp"

int main()
{
    ClapTrap robot("Jack");
    robot.attack("Bandit");
    robot.takeDamage(5);
    robot.beRepaired(3);
    robot.takeDamage(10);
    robot.beRepaired(5);
    robot.attack("Dummy Target");

    return 0;
}