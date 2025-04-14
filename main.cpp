#include <iostream>
#include "Archetype.h"
#include "Specialization.h"
#include "Inventory.h"
#include "Character.h"
#include "Interface.h"

int main()
{
    Character PC;
    PCCharacterCreate createPC;

    createPC.initialize(PC);

    PC.printInfo();

    PC.useItem<Potion>(0); 

    PC.printInfo();

    return 0;
}

