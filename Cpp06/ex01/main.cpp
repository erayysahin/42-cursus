#include "Serializer.hpp"
#include <iostream>

int main() {
    Data d;
    d.value = 42;
    d.str = "test data";

    uintptr_t raw = Serializer::serialize(&d);
    Data* pd = Serializer::deserialize(raw);

    std::cout << "Orijinal adres:      " << &d << std::endl;
    std::cout << "Serialize edilmiş:   " << raw << std::endl;
    std::cout << "Deserialize edilmiş: " << pd << std::endl;
    std::cout << "Data* içeriği:       " << pd->value << ", " << pd->str << std::endl;

    return 0;
}
