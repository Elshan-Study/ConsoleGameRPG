#pragma once
#include <iostream>
#include "Character.h"
#include "Location.h"
#include <memory>
#include "QuestStage.h"

static void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

static bool isNumber(const std::string& str) {
	if (str.empty()) return false;
	for (char ch : str) {
		if (!isdigit(ch)) return false;
	}
	return true;
}

class Interface
{
public:
	Interface() {};
	virtual ~Interface() {};
};

class PCCharacterCreate final : public Interface
{
public:
	size_t experience = 100;

	PCCharacterCreate() {};

	void ArchetypeChoice(Character& PC)
	{
		std::unique_ptr<Archetype> arch;
		while (true)
		{
			char choice;
			std::cout << "Choose Archetype: \n";
			std::cout << "1.Sturdy - high Brawn, small Willpower\n";
			std::cout << "2.Genius - high Intellect, small Agility\n";
			std::cout << "3.Aristocrat - high Presence, small Brawn\n";
			std::cout << "4.Simpleton - balanced characteristics\n";
			std::cout << "Your choice: ";
			std::cin >> choice;
			std::cout << "\n";

			if (choice-48 < 0 || choice-48 > 4)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice-48)
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

	void SpecializationChoice(Character& PC)
	{
		std::unique_ptr<Specialization> spec;
		while (true)
		{
			char choice;
			std::cout << "Choose Specialization: \n";
			std::cout << "1.Wizard: Alchemy 2, Magic 2, Discipline 2, Perception 2\n";
			std::cout << "2.Knight: Athletics 2, Resilience 2, Melee 2, Coercion 2\n";
			std::cout << "3.Archer: Coordination 2, Ranged 2, Perception 2, Survival 2\n";
			std::cout << "4.Thief: Coordination 2, Melee 2, Stealth 2, Skullduggery 2\n";
			std::cout << "5.Craftsman: Cool 2, Charm 2, Negotiation 2, Mechanics 2\n";
			std::cout << "Your choice: ";
			std::cin >> choice;
			std::cout << "\n";

			if (choice-48 < 0 || choice-48 > 5)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice-48)
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

	void CharacteristicsEdit(Character& PC, size_t& experience)
	{
		while (true)
		{
			char choice;
			std::cout << "1.Brawn\n";
			std::cout << "2.Agility\n";
			std::cout << "3.Intellect\n";
			std::cout << "4.Cunning\n";
			std::cout << "5.Willpower\n";
			std::cout << "6.Presence\n";
			std::cout << "Your choice: ";
			std::cin >> choice;
			std::cout << "\n";

			if (choice-48 < 1 || choice-48 > 6)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice-48)
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

	void SkillEdit(Character& PC, size_t& experience)
	{
		while (true)
		{
			char choice;
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
			std::cout << "Your choice: ";
			std::cin >> choice;
			std::cout << "\n";

			if (choice-48 < 1 || choice-48 > 18)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice-48)
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

	void MainChoice(Character& PC) 
	{
		char choice;
		bool flag = true;
		bool spec = false;
		bool arch = false;

		std::cout << "Character create MENU: \n";
		std::cout << "Input your name: " << std::flush;
		std::string name;
		std::cin >> name;
		PC.name = name;

		while (flag)
		{
			std::cout << "1.Choose Archetype\n";
			std::cout << "2.Choose Specialization\n";
			std::cout << "0.Finish\n";
			std::cout << "Your choice: ";
			std::cin >> choice;
			std::cout << "\n";

			if (choice-48 < 0 || choice-48 > 2)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice-48)
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

	void CharacterEdit(Character& PC)
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
			char choice;
			std::cout << "---------------------------------------------------------\n";
			PC.printInfo();

			std::cout << "You have " << experience << "exp\n";
			std::cout << "Cost of Characteristics = New Level * 10\n";
			std::cout << "Cost of Skills = New Level * 5\n";
			std::cout << "1.Increase Characteristics\n";
			std::cout << "2.Increase Skill\n";
			std::cout << "3.Reset\n";
			std::cout << "0.Finish\n";
			std::cout << "Your choice: ";
			std::cin >> choice;
			std::cout << "\n";

			if (choice-48 < 0 || choice-48 > 3)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice-48)
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

	void StartItemSet(Character& PC)
	{
		if (Wizard* wizard = dynamic_cast<Wizard*>(PC.specialization.get()))
		{
			std::unique_ptr<Item> item = std::make_unique<Potion>("Heal potion", 5);
			item->addCopy(2);
			PC.addItem(std::move(item));
		}

		if (Knight* knight = dynamic_cast<Knight*>(PC.specialization.get()))
		{
			std::unique_ptr<Item> item = std::make_unique<Weapon>("Sword", 5, 3);
			PC.addItem(std::move(item));
		}

		if (Archer* archer = dynamic_cast<Archer*>(PC.specialization.get()))
		{
			std::unique_ptr<Item> item = std::make_unique<Weapon>("Bow", 6, 2);
			PC.addItem(std::move(item));
		}

		if (Thief* thief = dynamic_cast<Thief*>(PC.specialization.get()))
		{
			std::unique_ptr<Item> item = std::make_unique<Weapon>("Knife", 3, 2);
			PC.addItem(std::move(item));
			item = std::make_unique<Potion>("Poison", 10);
			PC.addItem(std::move(item));
		}

		if (Craftsman* craftsman = dynamic_cast<Craftsman*>(PC.specialization.get()))
		{
			std::unique_ptr<Item> item = std::make_unique<QuestItem>("Bag of coins");
			PC.addItem(std::move(item));
		}
	}
	
	void initialize(Character& PC)
	{
		MainChoice(PC);
		clearScreen();
		
		CharacterEdit(PC);
		clearScreen();

		StartItemSet(PC);
		clearScreen();

	};

	void TestPC(Character& PC)
	{
		PC.name = "Test";
		std::unique_ptr<Archetype> arch = std::make_unique<Simpleton>();
		PC.archetype = std::move(arch);
		std::unique_ptr<Specialization> spec = std::make_unique<Wizard>();
		PC.specialization = std::move(spec);
		PC.specialization->Alchemy += 2;
		PC.SetAll();
	}

};

class MainMenu final : public Interface
{
public:
	MainMenu() {};

	char show()
	{
		char choice;

		while (true)
		{
			std::cout << "Amazing Adventure\n";
			std::cout << "_________________________________________________\n";
			std::cout << "Main menu: \n";
			std::cout << "1. New Game\n";
			std::cout << "2. Continue Game\n";
			std::cout << "3. Save Game\n";
			std::cout << "4. Load Game\n";
			std::cout << "5. Exit\n";
			std::cout << "\nYour choice: ";
			std::cin >> choice;
			std::cout << std::endl;

			if (choice-48 < 1 || choice-48 > 5)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			break;
		}

		return choice;

	}
};

class InsideGameMenu final : public Interface
{
public:
	InsideGameMenu() {};

	char show()
	{
		char choice;

		while (true)
		{
			std::cout << "1. Restore AP\n";
			std::cout << "2. Restore HP\n";
			std::cout << "3. Visit Capital City\n";
			std::cout << "4. Visit Evil Swamp\n";
			std::cout << "5. Visit Black Mountain\n";
			std::cout << "6. Return to main menu\n";
			std::cout << "\nYour choice: ";
			std::cin >> choice;
			std::cout << std::endl;

			if (choice - 48 < 1 || choice - 48 > 6)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			break;
		}

		return choice;
	}
};

class MapMenu final : public Interface
{
public:
	MapMenu() {};

	char show(Map& map)
	{
		char choice;

		while (true)
		{
			std::cout << "1. " << map[0]->getName() << "\n";
			std::cout << "2. " << map[1]->getName() << "\n";
			std::cout << "3. Return to menu\n";

			std::cout << "\nYour choice: ";
			std::cin >> choice;
			std::cout << std::endl;

			if (choice - 48 < 1 || choice - 48 > 3)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			break;
		}

		return choice;
	}

};

class FightingScene final : public Interface
{
public:
	enum InitiativeSkill
	{
		Vigilance,
		Cool
	};

	enum EnemyBehavior
	{
		MeleeMod,
		BalanceMod,
		RangeMod
	};

private:
	Character& Enemy;
	Character& PC;
	size_t distanceBetween;
	size_t distanceMax;
	size_t initiativeSkill;
	size_t enemyBehavior;

	enum class CharacterQueue
	{
		PC,
		Enemy
	};

public:
	FightingScene(Character& enemy, Character& PC, size_t distanceBetween, size_t distanceMax, size_t initiativeSkill, size_t enemyBehavior) : Enemy(enemy), PC(PC),
		distanceBetween(distanceBetween), distanceMax(distanceMax), initiativeSkill(initiativeSkill), enemyBehavior(enemyBehavior) {};

	bool isClose() { if (distanceBetween == 0) return 1; return 0; }

	void enemyMelee(size_t itemIndex)
	{
		if (isClose())
		{
			Enemy.attack(PC, itemIndex, 0, Enemy.melee(), 2);
			std::cout << Enemy.name << " melee attack\n";
			std::cout << "Your HP now: " << PC.currentHP << "\n";
			std::cin.get();
		}
		else
		{
			size_t steps = Enemy.Athletics() + 1;
			std::cout << Enemy.name << " make" << steps << "steps to you.\n";
			std::cin.get();

			if (steps > distanceBetween)
			{
				distanceBetween -= steps;
			}
			else {
				distanceBetween = 0;
			}
		}
	}

	void enemyRanged(size_t itemIndex)
	{
		if (!isClose())
		{
			Enemy.attack(PC, itemIndex, 0, Enemy.ranged(), 2);
			std::cout << Enemy.name << " ranged attack\n";
			std::cout << "Your HP now: " << PC.currentHP << "\n";
			std::cin.get();
		}
		else
		{
			size_t steps = Enemy.Athletics() + 1;
			std::cout << Enemy.name << " make" << steps << "steps from you.\n";
			std::cin.get();

			if (distanceBetween + steps < distanceMax)
			{
				distanceBetween += steps;
			}
			else {
				distanceBetween = distanceMax;
			}
		}
	}

	CharacterQueue initiativeCheck()
	{
		std::cout << Enemy.name << " roll initiative!\n";
		std::cin.get();

		size_t enemyInitiative = 0;
		size_t pcInitiative = 0;

		if (initiativeSkill == InitiativeSkill::Vigilance)
		{
			size_t enemyInitiative = Enemy.initiative(Enemy.vigilance());
		}
		else { size_t enemyInitiative = Enemy.initiative(Enemy.cool()); }

		std::cout << PC.name << " roll initiative!\n";

		if (initiativeSkill == InitiativeSkill::Vigilance)
		{
			size_t pcInitiative = PC.initiative(PC.vigilance());
		}
		else { size_t pcInitiative = PC.initiative(PC.cool()); }

		CharacterQueue queue = pcInitiative >= enemyInitiative ? CharacterQueue::PC : CharacterQueue::Enemy;

		return queue;
	}

	bool start()
	{
		std::cout << "Fight scene with " << Enemy.name << " start!\n";

		bool coercionStatus = 0;

		CharacterQueue queue = initiativeCheck();

		while (true)
		{
			std::cout << "Distance between " << PC.name << " and " << Enemy.name << " " << distanceBetween << " steps\n";
			std::cin.get();

			if (queue == CharacterQueue::Enemy)
			{
				std::cout << Enemy.name << " turn\n";
				std::cin.get();

				if (enemyBehavior == EnemyBehavior::MeleeMod && !coercionStatus)
				{
					enemyMelee(0);
				}
				else if (enemyBehavior == EnemyBehavior::RangeMod && !coercionStatus)
				{
					enemyRanged(0);
				}
				else if (enemyBehavior == EnemyBehavior::BalanceMod && !coercionStatus)
				{
					std::srand(static_cast<unsigned int>(std::time(nullptr)));
					int roll = rand() % 2 + 1;
					if (roll == 1)
					{
						enemyMelee(0);
					}
					else
					{
						enemyRanged(1);
					}
				}
				else
				{
					coercionStatus = 0;
				}

				queue = CharacterQueue::PC;
			}
			else
			{
				bool flag = true;

				while (flag)
				{
					std::cout << "Your turn\n";
					std::cin.get();

					std::cout << "Make choice: \n";
					std::cout << "1. Main action: Make steps to enemy.\n";
					std::cout << "2. Main action: Make steps from enemy.\n";
					if (isClose()) { std::cout << "3. Main action: Melee attack.\n"; }
					else { std::cout << "3. Main action: Ranged attack.\n"; }
					std::cout << "4. Main action: Use magic.\n";
					std::cout << "5. Additional action: Use Heal Potion.\n";
					std::cout << "6. Additional action: Use Poison.\n";
					std::cin.get();
					std::string input;
					std::cout << "Your choice: ";

					std::getline(std::cin, input);

					if (!isNumber(input)) {
						std::cout << "Wrong input!" << std::endl;
						continue;
					}

					int choice = std::stoi(input);

					if (choice < 0 || choice > 5) {
						std::cout << "Wrong choice!" << std::endl;
						continue;
					}

					switch (choice)
					{
					case 1:
						size_t steps = PC.Athletics() + 1;
						std::cout << PC.name << " make" << steps << "steps to " << Enemy.name << ".\n";
						std::cin.get();

						if (steps > distanceBetween)
						{
							distanceBetween -= steps;
						}
						else {
							distanceBetween = 0;
						}

						flag = false;
						break;
					case 2:
						size_t steps = PC.Athletics() + 1;
						std::cout << PC.name << " make" << steps << "steps from " << Enemy.name << ".\n";
						std::cin.get();

						if (distanceBetween + steps < distanceMax)
						{
							distanceBetween += steps;
						}
						else {
							distanceBetween = distanceMax;
						}
						flag = false;
						break;
					case 3:
						if (isClose())
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					}
				}
				

				/*if (itemIndex < PC.inventory.getSize())
				{
					for (size_t i = 0; i < PC.inventory.getSize(); ++i) {
						if (PC.inventory[i] && PC.inventory[i]->Name() == "Heal potion") {
							itemIndex = i;
							choiceMax += 1;
							
						}
					}
				}*/
			}
		}
		
		
			


	}
};

class SceneControl final : public Interface
{
public:

	bool loadNPCScene(QuestGetPointer*& location, size_t questStatus)
	{
		size_t currentStage{};
		size_t nextStage;
		bool isKeyAdded = false;
		
		if (questStatus == Quest::win) { currentStage = 50; }
		else if (questStatus == Quest::defeat) { currentStage = 40; }
		else if (!location->status()) { currentStage = 10; isKeyAdded = true; }
		else if (!location->quest.finishStatus()) { currentStage = 30; }
		
		else { std::cerr << "Error of Scene Control" << std::flush; return isKeyAdded; }

		QuestStage* stage = location->quest.findStage(currentStage);
		std::cout << stage->showName() << "\n";
		std::cin.get();
		nextStage = stage->nextIndex;
		
		while (true)
		{
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
					char choice;
					std::cout << "Your choice: ";
					std::cin >> choice;
					std::cout << "\n";

					if (choice - 48 < 1 || choice - 48 > option->getSize())
					{
						std::cout << "Wrong choice!\n";
						continue;
					}

					stage = location->quest.findStage((*option)[choice - 49]);
					nextStage = stage->nextIndex;

					break;
				}
			}
			else
			{
				currentStage = nextStage;
				stage = location->quest.findStage(currentStage);
				stage->on();
				std::cout << stage->showName() << "\n\n";
				std::cin.get();
				nextStage = stage->nextIndex;
			}

		}
		
		return isKeyAdded;
	};

	bool loadQuest(Character& PC, QuestPointer*& location, size_t startStage, size_t winStage, size_t defeatStage)
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
			if (!successStatus)
			{
				std::cout << "Unsuccess. Try next time\n\n";
				std::cin.get();
				currentStage = startStage;
				stage = location->quest.findStage(currentStage);
				nextStage = stage->nextIndex;
				successStatus = true;
				continue;
			}

			if (PC.currentAP <= 0)
			{
				std::cout << "You don't have enough AP or HP to continue. Restore and come back!\n\n";
				std::cin.get();
				return false;
			}

			if (nextStage == currentStage)
			{
				if (currentStage == winStage) location->quest.setStatus(Quest::win);
				else if (currentStage == defeatStage) location->quest.setStatus(Quest::defeat);
				std::cout << "Check get status: " << location->quest.getStatus();

				std::cout << "You have left the location\n\n";
				std::cin.get();
				location->quest.finish();
				return true;
			}

			if (nextStage < 10)
			{
				std::cout << PC.name << "\n";
				std::cout << "Your current HP: " << PC.currentHP << "\n";
				std::cout << "Your current AP: " << PC.currentAP << "\n";
				std::cout << PC.inventory;
				std::cin.get();

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
					std::cout << "Your choice: ";
					char choice;
					std::cin >> choice;

					int choiceNum = choice - '0';

					if (choiceNum < 1 || choiceNum > option->getSize())
					{
						std::cout << "Wrong choice!\n";
						continue;
					}

					stage = location->quest.findStage((*option)[choiceNum - 1]);
					successStatus = stage->on();
					if (auto attackStage = dynamic_cast<AttackStage*>(stage))
					{
						std::cout << "Fight start\n";
						std::cin.get();

						if (!successStatus)
						{
							currentStage = defeatStage;
							nextStage = defeatStage;
						}
						else
						{
							nextStage = stage->nextIndex;
						}
					}
					else
					{
						nextStage = stage->nextIndex;
					}
					nextStage = stage->nextIndex;
					break;
				}
			}
			else 
			{
				currentStage = nextStage;
				stage = location->quest.findStage(currentStage);
				std::cout << stage->showName() << "\n\n";
				std::cin.get();
				nextStage = stage->nextIndex;
			}
		}
	}


};
