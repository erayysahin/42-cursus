#include "Intern.hpp"
#include <iostream>

int main() {
    Intern intern;
    AForm* form;

    try {
        form = intern.makeForm("shrubbery creation", "Home");
        delete form;
        form = intern.makeForm("robotomy request", "Bender");
        delete form;
        form = intern.makeForm("presidential pardon", "Arthur");
        delete form;
        intern.makeForm("invalid form", "None");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
