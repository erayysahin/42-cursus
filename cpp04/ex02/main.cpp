#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    {
        const Animal* dog = new Dog();
        const Animal* cat = new Cat();
        std::cout << dog->getType() << std::endl;
        std::cout << cat->getType() << std::endl;
        dog->makeSound();
        cat->makeSound();
        delete dog;
        delete cat;
    }
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
    std::cout << "--------------------------" << std::endl;
    {
        Dog* dog1 = new Dog();
        dog1->getBrain()->ideas[0] = "Chasing cats";
        dog1->getBrain()->ideas[1] = "Barking at the mailman";
        std::cout << "dog1 brain idea[0]: " << dog1->getBrain()->ideas[0] << std::endl;

        Dog dog2(*dog1);
        std::cout << "dog2 brain idea[0] (after copy): " << dog2.getBrain()->ideas[0] << std::endl;

        dog1->getBrain()->ideas[0] = "Eating bone";
        std::cout << "dog1 brain idea[0] (after modification): " << dog1->getBrain()->ideas[0] << std::endl;
        std::cout << "dog2 brain idea[0] (should remain unchanged): " << dog2.getBrain()->ideas[0] << std::endl;

        delete dog1;
    }

    return 0;
}
