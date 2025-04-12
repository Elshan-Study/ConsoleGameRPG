#include <iostream>
#include "Archetype.h"
#include "Specialization.h"

int main()
{
    std::unique_ptr<Archetype> arch = std::make_unique<Aristocrat>();
    arch->setAP();
    arch->setHP();
    std::cout << arch->getHP() << "\n";
    std::unique_ptr<Specialization> spec = std::make_unique<Craftsman>();
    spec->setAllDices(arch.get());
    std::cout << spec->Negotiation.getValue() << "\n";
    std::cout << spec->Negotiation.getDices() << "\n";
    spec->Negotiation.changeValue(2,arch.get());
    std::cout << spec->Negotiation.getValue() << "\n";
    std::cout << spec->Negotiation.getDices() << "\n";
    spec->Negotiation.changeValue(-2, arch.get());
    std::cout << spec->Negotiation.getValue() << "\n";
    std::cout << spec->Negotiation.getDices() << "\n";

    return 0;

}

