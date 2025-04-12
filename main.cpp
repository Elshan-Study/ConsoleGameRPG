#include <iostream>
#include "Archetype.h"
#include "Specialization.h"
#include "Inventory.h"

int main()
{
    /*std::unique_ptr<Archetype> arch = std::make_unique<Aristocrat>();
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
    std::cout << spec->Negotiation.getDices() << "\n";*/

    Inventory inventory;
    std::unique_ptr<Item> heal = std::make_unique<Potion>("Heal potion", 3);
    std::unique_ptr<Item> sword = std::make_unique<Weapon>("Sword", 5, 3);
   /* inventory.addItem(heal.get());
    inventory.addItem(sword.get());
    std::cout << inventory;
    inventory[0]->useItem(0);
    inventory.CheckInventory();
    std::cout << inventory;*/
    inventory[0] = sword.get();
    inventory[1] = sword.get();
    inventory[5] = sword.get();
    std::cout << inventory;

    return 0;

}

