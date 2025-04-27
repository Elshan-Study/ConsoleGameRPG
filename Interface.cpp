#include "Interface.h"

void PCCharacterCreate::ArchetypeChoice(Character& PC)
{
	std::unique_ptr<Archetype> arch;
	while (true)
	{
		std::cout << "Choose Archetype: \n";
		std::cout << "1.Sturdy - high Brawn, small Willpower\n";
		std::cout << "2.Genius - high Intellect, small Agility\n";
		std::cout << "3.Aristocrat - high Presence, small Brawn\n";
		std::cout << "4.Simpleton - balanced characteristics\n";
		std::string input;
		std::cout << "Your choice: ";
		std::getline(std::cin, input);

		if (!isNumber(input)) {
			std::cout << "Wrong input!\n"; continue;
		}

		int choice = std::stoi(input);
		if (choice < 1 || choice > 4) {
			std::cout << "Wrong choice!\n"; continue;
		}

		switch (choice)
		{
		case 1:
			arch = std::make_unique<Sturdy>();
			break;
		case 2:
			arch = std::make_unique<Genius>();
			break;
		case 3:
			arch = std::make_unique<Aristocrat>();
			break;
		case 4:
			arch = std::make_unique<Simpleton>();
			break;
		default:
			break;
		}
		break;
	}

	PC.archetype = std::move(arch);
}

void PCCharacterCreate::SpecializationChoice(Character& PC)
{
	std::unique_ptr<Specialization> spec;
	while (true)
	{
		std::cout << "Choose Specialization: \n";
		std::cout << "1.Wizard: Alchemy 2, Magic 2, Discipline 2, Perception 2\n";
		std::cout << "2.Knight: Athletics 2, Resilience 2, Melee 2, Coercion 2\n";
		std::cout << "3.Archer: Coordination 2, Ranged 2, Perception 2, Survival 2\n";
		std::cout << "4.Thief: Coordination 2, Melee 2, Stealth 2, Skullduggery 2\n";
		std::cout << "5.Craftsman: Cool 2, Charm 2, Negotiation 2, Mechanics 2\n";
		std::string input;
		std::cout << "Your choice: ";
		std::getline(std::cin, input);

		if (!isNumber(input)) {
			std::cout << "Wrong input!\n"; continue;
		}

		int choice = std::stoi(input);
		if (choice < 1 || choice > 5) {
			std::cout << "Wrong choice!\n"; continue;
		}

		switch (choice)
		{
		case 1:
			spec = std::make_unique<Wizard>();
			break;
		case 2:
			spec = std::make_unique<Knight>();
			break;
		case 3:
			spec = std::make_unique<Archer>();
			break;
		case 4:
			spec = std::make_unique<Thief>();
			break;
		case 5:
			spec = std::make_unique<Craftsman>();
			break;
		default:
			break;
		}
		break;
	}

	PC.specialization = std::move(spec);
}

void PCCharacterCreate::CharacteristicsEdit(Character& PC, size_t& experience)
{
	while (true)
	{
		std::cout << "1.Brawn\n";
		std::cout << "2.Agility\n";
		std::cout << "3.Intellect\n";
		std::cout << "4.Cunning\n";
		std::cout << "5.Willpower\n";
		std::cout << "6.Presence\n";
		std::string input;
		std::cout << "Your choice: ";
		std::getline(std::cin, input);

		if (!isNumber(input)) {
			std::cout << "Wrong input!\n"; continue;
		}

		int choice = std::stoi(input);
		if (choice < 1 || choice > 6) {
			std::cout << "Wrong choice!\n"; continue;
		}

		switch (choice)
		{
		case 1:
			if (PC.Brawn() != 5 && experience >= (PC.Brawn() + 1) * 10)
			{
				experience -= (PC.Brawn() + 1) * 10;
				PC.archetype->Brawn += 1;
			}
			break;
		case 2:
			if (PC.Agility() != 5 && experience >= (PC.Agility() + 1) * 10)
			{
				experience -= (PC.Agility() + 1) * 10;
				PC.archetype->Agility += 1;
			}
			break;
		case 3:
			if (PC.Intellect() != 5 && experience >= (PC.Intellect() + 1) * 10)
			{
				experience -= (PC.Intellect() + 1) * 10;
				PC.archetype->Intellect += 1;
			}
			break;
		case 4:
			if (PC.Cunning() != 5 && experience >= (PC.Cunning() + 1) * 10)
			{
				experience -= (PC.Cunning() + 1) * 10;
				PC.archetype->Cunning += 1;
			}
			break;
		case 5:
			if (PC.Willpower() != 5 && experience >= (PC.Willpower() + 1) * 10)
			{
				experience -= (PC.Willpower() + 1) * 10;
				PC.archetype->Willpower += 1;
			}
			break;
		case 6:
			if (PC.Presence() != 5 && experience >= (PC.Presence() + 1) * 10)
			{
				experience -= (PC.Presence() + 1) * 10;
				PC.archetype->Presence += 1;
			}
			break;
		default:
			break;
		}

		PC.SetAll();
		break;
	}
}

void PCCharacterCreate::SkillEdit(Character& PC, size_t& experience)
{
	while (true)
	{
		std::cout << "1.Alchemy\n";
		std::cout << "2.Mechanics\n";
		std::cout << "3.Magic\n";
		std::cout << "4.Athletics\n";
		std::cout << "5.Resilience\n";
		std::cout << "6.Melee\n";
		std::cout << "7.Coordination\n";
		std::cout << "8.Stealth\n";
		std::cout << "9.Ranged\n";
		std::cout << "10.Discipline\n";
		std::cout << "11.Vigilance\n";
		std::cout << "12.Coercion\n";
		std::cout << "13.Perception\n";
		std::cout << "14.Skullduggery\n";
		std::cout << "15.Survival\n";
		std::cout << "16.Cool\n";
		std::cout << "17.Charm\n";
		std::cout << "18.Negotiation\n";
		std::string input;
		std::cout << "Your choice: ";
		std::getline(std::cin, input);

		if (!isNumber(input)) {
			std::cout << "Wrong input!\n"; continue;
		}

		int choice = std::stoi(input);
		if (choice < 1 || choice > 18) {
			std::cout << "Wrong choice!\n"; continue;
		}

		switch (choice)
		{
		case 1:
			if (PC.Alchemy() != 5 && experience >= (PC.Alchemy() + 1) * 5)
			{
				experience -= (PC.Alchemy() + 1) * 5;
				PC.specialization->Alchemy += 1;
			}
			break;
		case 2:
			if (PC.Mechanics() != 5 && experience >= (PC.Mechanics() + 1) * 5)
			{
				experience -= (PC.Mechanics() + 1) * 5;
				PC.specialization->Mechanics += 1;

			}
			break;
		case 3:
			if (PC.Magic() != 5 && experience >= (PC.Magic() + 1) * 5)
			{
				experience -= (PC.Magic() + 1) * 5;
				PC.specialization->Magic += 1;

			}
			break;
		case 4:
			if (PC.Athletics() != 5 && experience >= (PC.Athletics() + 1) * 5)
			{
				experience -= (PC.Athletics() + 1) * 5;
				PC.specialization->Athletics += 1;

			}
			break;
		case 5:
			if (PC.Resilience() != 5 && experience >= (PC.Resilience() + 1) * 5)
			{
				experience -= (PC.Resilience() + 1) * 5;
				PC.specialization->Resilience += 1;

			}
			break;
		case 6:
			if (PC.Melee() != 5 && experience >= (PC.Melee() + 1) * 5)
			{
				experience -= (PC.Melee() + 1) * 5;
				PC.specialization->Melee += 1;

			}
			break;
		case 7:
			if (PC.Coordination() != 5 && experience >= (PC.Coordination() + 1) * 5)
			{
				experience -= (PC.Coordination() + 1) * 5;
				PC.specialization->Coordination += 1;

			}
			break;
		case 8:
			if (PC.Stealth() != 5 && experience >= (PC.Stealth() + 1) * 5)
			{
				experience -= (PC.Stealth() + 1) * 5;
				PC.specialization->Stealth += 1;

			}
			break;
		case 9:
			if (PC.Ranged() != 5 && experience >= (PC.Ranged() + 1) * 5)
			{
				experience -= (PC.Ranged() + 1) * 5;
				PC.specialization->Ranged += 1;

			}
			break;
		case 10:
			if (PC.Discipline() != 5 && experience >= (PC.Discipline() + 1) * 5)
			{
				experience -= (PC.Discipline() + 1) * 5;
				PC.specialization->Discipline += 1;

			}
			break;
		case 11:
			if (PC.Vigilance() != 5 && experience >= (PC.Vigilance() + 1) * 5)
			{
				experience -= (PC.Vigilance() + 1) * 5;
				PC.specialization->Vigilance += 1;

			}
			break;
		case 12:
			if (PC.Coercion() != 5 && experience >= (PC.Coercion() + 1) * 5)
			{
				experience -= (PC.Coercion() + 1) * 5;
				PC.specialization->Coercion += 1;

			}
			break;
		case 13:
			if (PC.Perception() != 5 && experience >= (PC.Perception() + 1) * 5)
			{
				experience -= (PC.Perception() + 1) * 5;
				PC.specialization->Perception += 1;
			}
			break;
		case 14:
			if (PC.Skullduggery() != 5 && experience >= (PC.Skullduggery() + 1) * 5)
			{
				experience -= (PC.Skullduggery() + 1) * 5;
				PC.specialization->Skullduggery += 1;

			}
			break;
		case 15:
			if (PC.Survival() != 5 && experience >= (PC.Survival() + 1) * 5)
			{
				experience -= (PC.Survival() + 1) * 5;
				PC.specialization->Survival += 1;

			}
			break;
		case 16:
			if (PC.Cool() != 5 && experience >= (PC.Cool() + 1) * 5)
			{
				experience -= (PC.Cool() + 1) * 5;
				PC.specialization->Cool += 1;

			}
			break;
		case 17:
			if (PC.Charm() != 5 && experience >= (PC.Charm() + 1) * 5)
			{
				experience -= (PC.Charm() + 1) * 5;
				PC.specialization->Charm += 1;

			}
			break;
		case 18:
			if (PC.Negotiation() != 5 && experience >= (PC.Negotiation() + 1) * 5)
			{
				experience -= (PC.Negotiation() + 1) * 5;
				PC.specialization->Negotiation += 1;

			}
			break;
		default:
			break;
		}

		PC.SetAll();
		break;
	}
}

void PCCharacterCreate::MainChoice(Character& PC)
{
	bool flag = true;
	bool spec = false;
	bool arch = false;

	std::cout << "Character create MENU: \n";
	std::cout << "Input your name: ";
	std::string name;
	std::getline(std::cin, name);
	PC.name = name;

	while (flag)
	{
		std::cout << "1.Choose Archetype\n";
		std::cout << "2.Choose Specialization\n";
		std::cout << "0.Finish\n";
		std::string input;
		std::cout << "Your choice: ";
		std::getline(std::cin, input);

		if (!isNumber(input)) {
			std::cout << "Wrong input!\n"; continue;
		}

		int choice = std::stoi(input);
		if (choice < 0 || choice > 2) {
			std::cout << "Wrong choice!\n"; continue;
		}

		switch (choice)
		{
		case 1:
			ArchetypeChoice(PC);
			clearScreen();
			arch = true;
			break;
		case 2:
			SpecializationChoice(PC);
			clearScreen();
			spec = true;
			break;
		case 0:
			if (!spec || !arch)
			{
				std::cout << "You must choice Archetype and Specialization" << std::endl;
			}
			else { flag = false; }
			break;
		default:
			break;
		}
	}
}

void PCCharacterCreate::CharacterEdit(Character& PC)
{
	bool flag = true;

	PC.SetAll();

	size_t alchemy = PC.Alchemy();
	size_t mechanics = PC.Mechanics();
	size_t magic = PC.Magic();
	size_t athletics = PC.Athletics();
	size_t resilience = PC.Resilience();
	size_t melee = PC.Melee();
	size_t coordination = PC.Coordination();
	size_t stealth = PC.Stealth();
	size_t ranged = PC.Ranged();
	size_t discipline = PC.Discipline();
	size_t vigilance = PC.Vigilance();
	size_t coercion = PC.Coercion();
	size_t perception = PC.Perception();
	size_t skullduggery = PC.Skullduggery();
	size_t survival = PC.Survival();
	size_t cool = PC.Cool();
	size_t charm = PC.Charm();
	size_t negotiation = PC.Negotiation();
	size_t brawn = PC.Brawn();
	size_t agility = PC.Agility();
	size_t intellect = PC.Intellect();
	size_t cunning = PC.Cunning();
	size_t willpower = PC.Willpower();
	size_t presence = PC.Presence();

	while (flag)
	{
		std::cout << "---------------------------------------------------------\n";
		PC.printInfo();

		std::cout << "You have " << experience << "exp\n";
		std::cout << "Cost of Characteristics = New Level * 10\n";
		std::cout << "Cost of Skills = New Level * 5\n";
		std::cout << "1.Increase Characteristics\n";
		std::cout << "2.Increase Skill\n";
		std::cout << "3.Reset\n";
		std::cout << "0.Finish\n";
		std::string input;
		std::cout << "Your choice: ";
		std::getline(std::cin, input);
		std::cout << "\n";

		if (!isNumber(input)) {
			std::cout << "Wrong input!\n"; continue;
		}

		int choice = std::stoi(input);
		if (choice < 0 || choice > 3) {
			std::cout << "Wrong choice!\n"; continue;
		}

		switch (choice)
		{
		case 1:
			CharacteristicsEdit(PC, experience);
			clearScreen();
			break;
		case 2:
			SkillEdit(PC, experience);
			clearScreen();
			break;
		case 3:
			PC.specialization->Alchemy = alchemy;
			PC.specialization->Mechanics = mechanics;
			PC.specialization->Magic = magic;
			PC.specialization->Athletics = athletics;
			PC.specialization->Resilience = resilience;
			PC.specialization->Melee = melee;
			PC.specialization->Coordination = coordination;
			PC.specialization->Stealth = stealth;
			PC.specialization->Ranged = ranged;
			PC.specialization->Discipline = discipline;
			PC.specialization->Vigilance = vigilance;
			PC.specialization->Coercion = coercion;
			PC.specialization->Perception = perception;
			PC.specialization->Skullduggery = skullduggery;
			PC.specialization->Survival = survival;
			PC.specialization->Cool = cool;
			PC.specialization->Charm = charm;
			PC.specialization->Negotiation = negotiation;
			PC.archetype->Brawn = brawn;
			PC.archetype->Agility = agility;
			PC.archetype->Intellect = intellect;
			PC.archetype->Cunning = cunning;
			PC.archetype->Willpower = willpower;
			PC.archetype->Presence = presence;
			experience = 100;
			PC.SetAll();
			break;
		case 0:
			if (experience != 0)
			{
				std::cout << "You must spend all experience" << std::endl;
			}
			else { flag = false; }
			break;
		default:
			break;
		}
	}
}

void PCCharacterCreate::StartItemSet(Character& PC)
{
	if (Wizard* wizard = dynamic_cast<Wizard*>(PC.specialization.get()))
	{
		std::unique_ptr<Item> item = std::make_unique<Potion>("Heal potion", 5);
		item->addCopy(2);
		PC.addItem(std::move(item));
	}

	if (Knight* knight = dynamic_cast<Knight*>(PC.specialization.get()))
	{
		std::unique_ptr<Item> item = std::make_unique<Weapon>("Sword", Weapon::Melee, 5, 3);
		PC.addItem(std::move(item));
		std::unique_ptr<Item> steelArmor = std::make_unique<Armor>("Steel Armor", 10, 2);
		PC.addItem(std::move(steelArmor));
	}

	if (Archer* archer = dynamic_cast<Archer*>(PC.specialization.get()))
	{
		std::unique_ptr<Item> item = std::make_unique<Weapon>("Bow", Weapon::Range, 6, 2);
		PC.addItem(std::move(item));
		std::unique_ptr<Item> mantle = std::make_unique<Armor>("Mantle", 5, 1);
		PC.addItem(std::move(mantle));
	}

	if (Thief* thief = dynamic_cast<Thief*>(PC.specialization.get()))
	{
		std::unique_ptr<Item> item = std::make_unique<Weapon>("Knife", Weapon::Melee, 3, 2);
		PC.addItem(std::move(item));
		item = std::make_unique<Potion>("Poison", 10);
		PC.addItem(std::move(item));
	}

	if (Craftsman* craftsman = dynamic_cast<Craftsman*>(PC.specialization.get()))
	{
		PC.money += 50;
	}
}

void PCCharacterCreate::initialize(Character& PC)
{
	MainChoice(PC);
	clearScreen();

	CharacterEdit(PC);
	clearScreen();

	StartItemSet(PC);
	clearScreen();

};

void PCCharacterCreate::TestPC(Character& PC)
{
	PC.name = "Test";
	std::unique_ptr<Archetype> arch = std::make_unique<Simpleton>();
	PC.archetype = std::move(arch);
	/*std::unique_ptr<Specialization> spec = std::make_unique<Wizard>();*/
	std::unique_ptr<Specialization> spec = std::make_unique<Craftsman>();
	PC.specialization = std::move(spec);
	/*PC.specialization->Alchemy += 2;*/
	PC.specialization->Magic += 2;
	PC.specialization->Melee += 2;
	PC.specialization->Ranged += 1;
	PC.SetAll();
	/*std::unique_ptr<Item> item = std::make_unique<Potion>("Heal potion", 5);
	item->addCopy(2);*/
	std::unique_ptr<Item> item = std::make_unique<Weapon>("Sword", Weapon::Melee, 5, 3);
	PC.addItem(std::move(item));
	std::unique_ptr<Item> item2 = std::make_unique<Weapon>("Bow", Weapon::Range, 3, 3);
	PC.addItem(std::move(item2));
	std::unique_ptr<Item> mantle = std::make_unique<Armor>("Mantle", 5, 1);
	PC.addItem(std::move(mantle));
}

FightingScene::FightingScene(Character* enemy, Character& pc, size_t distanceBetween, size_t distanceMax, size_t initSkill, size_t behavior)
	: Enemy(enemy), PC(pc), distanceBetween(distanceBetween), distanceMax(distanceMax),
	initiativeSkill(initSkill), enemyBehavior(behavior) {
}

bool FightingScene::isClose() const { return distanceBetween == 0; }

void FightingScene::enemyMelee(size_t itemIndex)
{
	if (isClose()) {
		std::cout << Enemy->name << " melee attack\n";
		Enemy->attack(PC, 1, itemIndex, Enemy->melee(), 2);
		std::cout << "Your HP now: " << PC.currentHP << "\n";
		PC.inventory.CheckInventory();
	}
	else {
		size_t steps = Enemy->Athletics() + 1;
		std::cout << Enemy->name << " make " << steps << " steps to you.\n";
		distanceBetween = steps >= distanceBetween ? 0 : distanceBetween - steps;
	}
	std::cin.get();
}

void FightingScene::enemyRanged(size_t itemIndex)
{
	if (!isClose()) {
		std::cout << Enemy->name << " ranged attack\n";
		Enemy->attack(PC, 1, itemIndex, Enemy->ranged(), 2);
		std::cout << "Your HP now : " << PC.currentHP << "\n";
		PC.inventory.CheckInventory();
	}
	else {
		size_t steps = Enemy->Athletics() + 1;
		std::cout << Enemy->name << " make " << steps << " steps from you.\n";
		distanceBetween = std::min(distanceBetween + steps, distanceMax);
	}
	std::cin.get();
}

FightingScene::CharacterQueue FightingScene::initiativeCheck()
{
	std::cout << Enemy->name << " roll initiative!\n";
	size_t enemyInitiative = (initiativeSkill == Vigilance) ? Enemy->initiative(Enemy->cool()) : Enemy->initiative(Enemy->vigilance());

	std::cout << PC.name << " roll initiative!\n";
	size_t pcInitiative = (initiativeSkill == Vigilance) ? PC.initiative(PC.vigilance()) : PC.initiative(PC.cool());
	std::cin.get();

	return pcInitiative >= enemyInitiative ? CharacterQueue::PC : CharacterQueue::Enemy;
}

bool FightingScene::start()
{
	Enemy->printInfo();
	std::cout << "Fight scene with " << Enemy->name << " start!\n";
	bool coercionStatus = false;
	CharacterQueue queue = initiativeCheck();

	while (true)
	{
		std::cout << "Distance between " << PC.name << " and " << Enemy->name << ": " << distanceBetween << " steps\n";
		std::cout << "Your current HP: " << PC.currentHP << "\n";
		std::cout << "Your current AP: " << PC.currentAP << "\n";
		std::cout << PC.inventory;
		std::cin.get();

		if (queue == CharacterQueue::Enemy)
		{
			std::cout << Enemy->name << " turn\n"; std::cin.get();

			if (!coercionStatus)
			{
				if (enemyBehavior == MeleeMod) enemyMelee(0);
				else if (enemyBehavior == RangeMod) enemyRanged(0);
				else if (enemyBehavior == BalanceMod)
				{
					int roll = rand() % 2;
					if (roll == 0) enemyMelee(0);
					else enemyRanged(1);
				}
			}
			else coercionStatus = false;

			if (PC.currentHP == 0)
			{
				std::cout << PC.name << " lost!\n"; std::cin.get();
				return false;
			}
			queue = CharacterQueue::PC;
		}
		else
		{
			bool turnInProgress = true;

			while (turnInProgress)
			{
				std::cout << "Your turn\n"; std::cin.get();
				std::cout << "Make choice:\n";
				std::cout << "1. Move to enemy\n2. Move from enemy\n";
				std::cout << (isClose() ? "3. Melee attack\n" : "3. Ranged attack\n");
				std::cout << "4. Use magic\n5. Use Coercion\n6. Use Heal Potion\n7. Use Poison\n";

				std::string input;
				std::cout << "Your choice: ";
				std::getline(std::cin, input);

				if (!isNumber(input)) {
					std::cout << "Wrong input!\n"; continue;
				}

				int choice = std::stoi(input);
				if (choice < 1 || choice > 7) {
					std::cout << "Wrong choice!\n"; continue;
				}

				size_t steps = PC.Athletics() + 1;
				bool skillCheck = false;
				bool itemUsed = false;
				size_t itemIndex = 0, effect = 0;
				std::string weapon1, weapon2, attackType;

				switch (choice)
				{
				case 1:
					std::cout << PC.name << " make " << steps << " steps to " << Enemy->name << ".\n";
					distanceBetween = steps >= distanceBetween ? 0 : distanceBetween - steps;
					turnInProgress = false;
					break;
				case 2:
					std::cout << PC.name << " make " << steps << " steps from " << Enemy->name << ".\n";
					distanceBetween = std::min(distanceBetween + steps, distanceMax);
					turnInProgress = false;
					break;
				case 3:
				{
					size_t dice = isClose() ? PC.melee() : PC.ranged();
					weapon1 = isClose() ? "Sword" : "Bow";
					weapon2 = isClose() ? "Knife" : "Crossbow";

					bool hasWeapon = false;
					for (size_t i = 0; i < PC.inventory.getSize(); i++) {
						if (PC.inventory[i]->Name() == weapon1 || PC.inventory[i]->Name() == weapon2) {
							hasWeapon = true; itemIndex = i; break;
						}
					}

					PC.attack(*Enemy, hasWeapon, itemIndex, dice, 2);
					std::cout << "Enemy HP now : " << Enemy->currentHP << "\n";
					std::cin.get();
					Enemy->inventory.CheckInventory();
					turnInProgress = false;
					break;
				}
				case 4:
					if (PC.Magic() == 0 || PC.currentAP == 0) {
						std::cout << "You can't use Magic!\n"; std::cin.get(); break;
					}
					skillCheck = PC.skillCheck(PC.magic(), 3);
					PC.currentAP = PC.currentAP > 0 ? PC.currentAP - 1 : 0;

					if (skillCheck) {
						std::srand(static_cast<unsigned>(std::time(nullptr)));
						switch (rand() % 4 + 1) {
						case 1: Enemy->currentHP = (Enemy->currentHP > 5) ? Enemy->currentHP - 5 : 0;
							std::cout << "Magic: Enemy HP -5. Now: " << Enemy->currentHP << "\n"; break;
						case 2: Enemy->currentHP = std::min(Enemy->currentHP + 5, Enemy->archetype->getHP());
							std::cout << "Magic: Enemy HP +5. Now: " << Enemy->currentHP << "\n"; break;
						case 3: Enemy->specialization->Athletics = std::max<size_t>(Enemy->specialization->Athletics.getValue() - 1, 0);
							std::cout << "Magic: Enemy Athletics -1\n"; break;
						case 4: Enemy->specialization->Athletics = std::min<size_t>(Enemy->specialization->Athletics.getValue() + 1, 5);
							std::cout << "Magic: Enemy Athletics +1\n"; break;
						}
					}
					else {
						std::cout << "Unsuccess!\n";
					}
					std::cin.get(); turnInProgress = false;
					break;
				case 5:
					if (PC.currentAP == 0) {
						std::cout << "You don't have any AP\n"; std::cin.get(); break;
					}
					skillCheck = PC.skillCheck(PC.coercion(), 2);
					PC.currentAP = PC.currentAP > 0 ? PC.currentAP - 1 : 0;
					std::cout << (skillCheck ? "Enemy is scared\n" : "Your attempts made the enemy laugh\n");
					coercionStatus = skillCheck;
					std::cin.get(); break;
				case 6:
				case 7:
				{
					std::string itemName = (choice == 6) ? "Heal potion" : "Poison";
					for (size_t i = 0; i < PC.inventory.getSize(); ++i) {
						if (PC.inventory[i] && PC.inventory[i]->Name() == itemName) {
							effect = PC.inventory[i]->useItem(0);
							if (choice == 6)
								PC.currentHP = std::min(PC.currentHP + effect, PC.archetype->getHP());
							else
								Enemy->currentHP = (Enemy->currentHP > effect) ? Enemy->currentHP - effect : 0;

							PC.inventory.CheckInventory();
							std::cout << itemName << " used\n";
							if (choice == 7) std::cout << "Enemy current HP: " << Enemy->currentHP << "\n";
							std::cin.get(); itemUsed = true; break;
						}
					}
					if (!itemUsed) {
						std::cout << "You don't have " << itemName << "\n"; std::cin.get();
					}
					break;
				}
				}
			}

			if (Enemy->currentHP == 0)
			{
				std::cout << PC.name << " won!\n"; std::cin.get();
				return true;
			}
			queue = CharacterQueue::Enemy;
		}
	}
}

bool SceneControl::loadNPCScene(QuestGetPointer*& location, size_t questStatus)
{
	size_t currentStage{};
	size_t nextStage;
	bool isKeyAdded = false;

	if (questStatus == Quest::win) { currentStage = static_cast<size_t>(NPCSceneReaction::WinReaction); }
	else if (questStatus == Quest::defeat) { currentStage = static_cast<size_t>(NPCSceneReaction::DefeatReaction); }
	else if (!location->status()) { currentStage = static_cast<size_t>(NPCSceneReaction::DefaultReaction); isKeyAdded = true; }
	else if (!location->quest.finishStatus()) { currentStage = static_cast<size_t>(NPCSceneReaction::WaitingReaction); }

	else { std::cerr << "Error of Scene Control" << std::flush; return isKeyAdded; }

	bool successStatus = true;
	std::string badOutput;

	QuestStage* stage = location->quest.findStage(currentStage);
	std::cout << stage->showName() << "\n";
	std::cin.get();
	nextStage = stage->nextIndex;

	while (true)
	{

		if (auto buyStage = dynamic_cast<buyItemStage*>(location->quest.findStage(nextStage)))
		{
			int choice;
			std::string input;
			std::cout << "Do you want buy this item?\n 1. Yes\n 2. No\n";
			std::cout << "Your choice: ";
			std::getline(std::cin, input);

			if (!isNumber(input)) {
				std::cout << "Wrong input!\n"; continue;
			}

			choice = std::stoi(input);
			if (choice < 1 || choice > 2) {
				std::cout << "Wrong choice!\n"; continue;
			}
			
			if (choice != 1)
			{
				std::cout << "You have left the location" << "\n\n";
				std::cin.get();
				return false;
			}
		}

		if (nextStage == currentStage) {
			std::cout << "You have left the location" << "\n\n";
			std::cin.get();
			return isKeyAdded;
		}
		else if (nextStage < 10)
		{
			currentStage = nextStage;
			OptionChoice* option = location->quest.getOption(currentStage);
			for (size_t i = 0; i < option->getSize(); i++)
			{
				stage = location->quest.findStage((*option)[i]);
				std::cout << i + 1 << ". " << stage->showName() << "\n";
			}
			std::cout << "\n";

			while (true)
			{
				int choice;
				std::string input;
				std::cout << "Your choice: ";
				std::getline(std::cin, input);

				if (!isNumber(input)) {
					std::cout << "Wrong input!\n"; continue;
				}

				choice = std::stoi(input);
				if (choice < 1 || choice > option->getSize()) {
					std::cout << "Wrong choice!\n"; continue;
				}

				stage = location->quest.findStage((*option)[choice - 1]);

				bool successStatus = stage->on();

				if (auto skillStage = dynamic_cast<skillCheckStage*>(stage))
				{
					nextStage = !successStatus ? skillStage->badIndex : skillStage->nextIndex;
					badOutput = "Unsuccess\n";
				}
				else if (auto buyStage = dynamic_cast<buyItemStage*>(stage))
				{
					nextStage = !successStatus ? currentStage : skillStage->nextIndex;
					badOutput = "You don't have enough money\n";
				}
				else { nextStage = stage->nextIndex; }

				break;
			}
		}
		else
		{
			currentStage = nextStage;
			stage = location->quest.findStage(currentStage);
			successStatus = stage->on();
			if(successStatus) { std::cout << stage->showName() << "\n"; }
			else { std::cout << badOutput; }
			std::cin.get();
			nextStage = stage->nextIndex;
		}

	}

	return isKeyAdded;
};

bool SceneControl::loadQuest(Character& PC, QuestPointer*& location, FightingScene& fighting, size_t startStage, size_t winStage, size_t defeatStage)
{

	if (location->quest.finishStatus())
	{
		std::cout << "You finished this quest\n\n";
		std::cin.get();
		return false;
	}

	size_t currentStage = startStage;
	QuestStage* stage = location->quest.findStage(currentStage);
	size_t nextStage = stage->nextIndex;
	bool successStatus = true;

	while (true)
	{
		if (!successStatus && currentStage != defeatStage)
		{
			std::cout << "Unsuccess!!!\n\n";
			std::cin.get();

			if (auto skillStage = dynamic_cast<skillCheckStage*>(stage))
			{
				nextStage = skillStage->badIndex;
			}
			else{ 
				currentStage = startStage; 
				stage = location->quest.findStage(currentStage);
				nextStage = stage->nextIndex;
			}
			successStatus = true;
			continue;
		}

		if (nextStage == currentStage)
		{
			if (currentStage == winStage) location->quest.setStatus(Quest::win);
			else if (currentStage == defeatStage) location->quest.setStatus(Quest::defeat);

			std::cout << "You have left the location\n\n";
			std::cin.get();
			location->quest.finish();
			return true;
		}

		if (PC.currentAP <= 0)
		{
			std::cout << "You don't have enough AP or HP to continue. Restore and come back!\n\n";
			std::cin.get();
			return false;
		}

		if (nextStage < 10)
		{
			std::cout << PC.name << "\n";
			std::cout << "Your current HP: " << PC.currentHP << "\n";
			std::cout << "Your current AP: " << PC.currentAP << "\n";
			std::cout << PC.inventory;

			currentStage = nextStage;
			OptionChoice* option = location->quest.getOption(currentStage);

			for (size_t i = 0; i < option->getSize(); ++i)
			{
				stage = location->quest.findStage((*option)[i]);
				std::cout << i + 1 << ". " << stage->showName() << "\n";
			}
			std::cout << "\n";

			while (true)
			{
				int choice;
				std::string input;
				std::cout << "Your choice: ";
				std::getline(std::cin, input);

				if (!isNumber(input)) {
					std::cout << "Wrong input!\n"; continue;
				}

				choice = std::stoi(input);
				if (choice < 1 || choice > option->getSize()) {
					std::cout << "Wrong choice!\n"; continue;
				}

				stage = location->quest.findStage((*option)[choice - 1]);
				successStatus = stage->on();
				if (auto attackStage = dynamic_cast<AttackStage*>(stage))
				{
					successStatus = fighting.start();
					std::cin.get();

					if (!successStatus)
					{
						currentStage = defeatStage;
						nextStage = defeatStage;
						stage = location->quest.findStage(currentStage);
						std::cout << stage->showName() << "\n\n";
						std::cin.get();
					}
					else
					{
						nextStage = stage->nextIndex;
					}
				}
				else if (successStatus)
				{
					nextStage = stage->nextIndex;
				}
				break;
			}
		}
		else
		{
			currentStage = nextStage;
			stage = location->quest.findStage(currentStage);

			if (auto attackStage = dynamic_cast<AttackStage*>(stage))
			{
				successStatus = fighting.start();
				std::cin.get();

				if (!successStatus)
				{
					currentStage = defeatStage;
					nextStage = defeatStage;
					stage = location->quest.findStage(currentStage);
				}
				else
				{
					nextStage = stage->nextIndex;
				}
			}
			else
			{
				nextStage = stage->nextIndex;
				std::cout << stage->showName() << "\n\n";
				std::cin.get();
			}
		
		}
	}
};