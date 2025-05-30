#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    {
        const Animal* meta = new Animal();
        const Animal* j = new Dog();
        const Animal* i = new Cat();
        std::cout << meta->getType() << std::endl;
        std::cout << j->getType() << std::endl;
        std::cout << i->getType() << std::endl;
        j->makeSound();
        i->makeSound();
        delete j;
        delete i;
        delete meta;
    }
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;

    {
        const int ARRAY_SIZE = 4;
        Animal* animals[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (i < ARRAY_SIZE / 2)
                animals[i] = new Dog();
            else
                animals[i] = new Cat();
        }
        for (int i = 0; i < ARRAY_SIZE; i++) {
            delete animals[i];
        }
    }
    std::cout << std::endl; 
    std::cout << "--------------------------" << std::endl;

    {
        Dog* dog1 = new Dog();
        dog1->getBrain()->ideas[0] = "Chasing cats";
        dog1->getBrain()->ideas[1] = "Barking at the mailman";
        std::cout << "dog1 brain idea[0]: " << dog1->getBrain()->ideas[0] << std::endl;
        std::cout << "dog1 brain idea[1]: " << dog1->getBrain()->ideas[1] << std::endl;
        Dog dog2(*dog1);
        std::cout << "dog2 brain idea[0] (after copy): " << dog2.getBrain()->ideas[0] << std::endl;

        dog1->getBrain()->ideas[0] = "Eating bone";
        std::cout << "dog1 brain idea[0] (after modification): " << dog1->getBrain()->ideas[0] << std::endl;
        std::cout << "dog2 brain idea[0] (should remain unchanged): " << dog2.getBrain()->ideas[0] << std::endl;

        delete dog1;
    }

    return 0;
}
