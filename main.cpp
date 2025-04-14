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

    return 0;
}

