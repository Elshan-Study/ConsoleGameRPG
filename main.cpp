#include <iostream>
#include "Archetype.h"

int main()
{
    std::unique_ptr<Archetype> obj = std::make_unique<Aristocrat>();
    std::cout << obj->getBrawn();

}

