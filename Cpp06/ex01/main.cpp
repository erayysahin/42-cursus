#include "Serializer.hpp"
#include <iostream>

int main() {
    Data original(10, 2.718, 'A');
    uintptr_t raw = Serializer::serialize(&original);
    Data* ptr2 = Serializer::deserialize(raw);

    std::cout << "Original address: " << &original << "\n";
    std::cout << "Serialized raw  : " << raw << "\n";
    std::cout << "Deserialized ptr: " << ptr2 << "\n";

    if (ptr2 == &original)
        std::cout << "Success: pointers match\n";
    else
        std::cout << "Error: pointers differ\n";

    std::cout << "Data: i=" << ptr2->i
              << " d=" << ptr2->d
              << " c=" << ptr2->c << "\n";

    return 0;
}
