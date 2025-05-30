#include <iostream>

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    } else {
        for (int j = 1; j < argc; ++j) {
            for (int i = 0; argv[j][i] != '\0'; ++i) {
                std::cout << static_cast<char>(std::toupper(argv[j][i]));
            }
        }
    }
    std::cout << std::endl;
    return 0;
}

