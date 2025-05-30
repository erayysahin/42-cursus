#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>
int main() 
{
    ClapTrap bot("Bob");
    ScavTrap scav("Serena");
    FragTrap frag("John");
    std::cout << std::endl;
    bot.attack("Alice");
    bot.takeDamage(5);
    bot.beRepaired(3);
    std::cout << std::endl;
    scav.attack("Eve");
    scav.guardGate();
    scav.takeDamage(30);
    scav.beRepaired(10);
    std::cout << std::endl;
    frag.attack("Mark");
    frag.highFivesGuys();
    std::cout << std::endl;
    return 0;
}
