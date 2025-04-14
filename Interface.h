#pragma once
#include "Character.h"
#include <memory>
class Interface
{
public:
	Interface() {};
	virtual ~Interface() {};
};

class PCCharacterCreate final : public Interface
{
public:

	PCCharacterCreate() {};

	void initialize(Character& PC)
	{

		std::unique_ptr<Archetype> arch;
		std::unique_ptr<Specialization> spec;
		int choice;
		bool flag = true;
		while (flag)
		{
			std::cout << "Character create MENU: \n";

			std::string name;
			std::cout << "Input your name: ";
			std::getline(std::cin, name);
			std::cout << std::endl;

			PC.name = name;

			std::cout << "1.Choose Archetype\n";
			std::cout << "2.Choose Specialization\n";
			std::cout << "0.Finish\n";
			std::cout << "Your choice: ";
			std::cin >> choice;
			std::cout << "\n";

			if (choice < 0 || choice > 2)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice)
			{
			case 1:
				while (!arch)
				{
					std::cout << "Choose Archetype: \n";
					std::cout << "1.Sturdy - high Brawn, small Willpower\n";
					std::cout << "2.Genius - high Intellect, small Agility\n";
					std::cout << "3.Aristocrat - high Presence, small Brawn\n";
					std::cout << "4.Simpleton - balanced characteristics\n";
					std::cout << "Your choice: ";
					std::cin >> choice;
					std::cout << "\n";

					if (choice < 0 || choice > 4)
					{
						std::cout << "Wrong choice!" << std::endl;
						continue;
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
				break;
			case 2:
				while (!spec)
				{
					std::cout << "Choose Specialization: \n";
					std::cout << "1.Wizard: Alchemy 2, Magic 2, Discipline 2, Perception 2\n";
					std::cout << "2.Knight: Athletics 2, Resilience 2, Melee 2, Coercion 2\n";
					std::cout << "3.Archer: Coordination 2, Ranged 2, Perception 2, Survival 2\n";
					std::cout << "4.Thief: Coordination 2, Melee 2, Stealth 2, Skullduggery 2\n";
					std::cout << "5.Craftsman: Cool 2, Charm 2, Negotiation 2, Mechanics 2\n";
					std::cout << "Your choice: ";
					std::cin >> choice;
					std::cout << "\n";

					if (choice < 0 || choice > 4)
					{
						std::cout << "Wrong choice!" << std::endl;
						continue;
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
		
		PC.archetype = std::move(arch);
		PC.specialization = std::move(spec);

		flag = true;

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
			size_t experience = 100;

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

			if (choice < 0 || choice > 3)
			{
				std::cout << "Wrong choice!" << std::endl;
				continue;
			}

			switch (choice)
			{
			case 1:
				while (true)
				{
					std::cout << "1.Brawn\n";
					std::cout << "2.Agility\n";
					std::cout << "3.Intellect\n";
					std::cout << "4.Cunning\n";
					std::cout << "5.Willpower\n";
					std::cout << "6.Presence\n";
					std::cout << "Your choice: ";
					std::cin >> choice;
					std::cout << "\n";

					if (choice < 1 || choice > 6)
					{
						std::cout << "Wrong choice!" << std::endl;
						continue;
					}

					switch (choice)
					{
					case 1:
						if (PC.Brawn() != 5 && experience >= (PC.Brawn() + 1) * 10)
						{
							PC.archetype->Brawn += 1;
							experience -= (PC.Brawn() + 1) * 10;
						}
						break;
					case 2:
						if (PC.Agility() != 5 && experience >= (PC.Agility() + 1) * 10)
						{
							PC.archetype->Agility += 1;
							experience -= (PC.Agility() + 1) * 10;
						}
						break;
					case 3:
						if (PC.Intellect() != 5 && experience >= (PC.Intellect() + 1) * 10)
						{
							PC.archetype->Intellect += 1;
							experience -= (PC.Intellect() + 1) * 10;
						}
						break;
					case 4:
						if (PC.Cunning() != 5 && experience >= (PC.Cunning() + 1) * 10)
						{
							PC.archetype->Cunning += 1;
							experience -= (PC.Cunning() + 1) * 10;
						}
						break;
					case 5:
						if (PC.Willpower() != 5 && experience >= (PC.Willpower() + 1) * 10)
						{
							PC.archetype->Willpower += 1;
							experience -= (PC.Willpower() + 1) * 10;
						}
						break;
					case 6:
						if (PC.Presence() != 5 && experience >= (PC.Presence() + 1) * 10)
						{
							PC.archetype->Presence += 1;
							experience -= (PC.Presence() + 1) * 10;
						}
						break;
					default:
						break;
					}

					PC.SetAll();
					break;
				}
				break;
			case 2:
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
					std::cout << "Your choice: ";
					std::cin >> choice;
					std::cout << "\n";

					if (choice < 1 || choice > 18)
					{
						std::cout << "Wrong choice!" << std::endl;
						continue;
					}

					switch (choice)
					{
					case 1:
						if (PC.Alchemy() != 5 && experience >= (PC.Alchemy() + 1) * 5)
						{
							PC.specialization->Alchemy += 1;
							experience -= (PC.Alchemy() + 1) * 5;
						}
						break;
					case 2:
						if (PC.Mechanics() != 5 && experience >= (PC.Mechanics() + 1) * 5)
						{
							PC.specialization->Mechanics += 1;
							experience -= (PC.Mechanics() + 1) * 5;
						}
						break;
					case 3:
						if (PC.Magic() != 5 && experience >= (PC.Magic() + 1) * 5)
						{
							PC.specialization->Magic += 1;
							experience -= (PC.Magic() + 1) * 5;
						}
						break;
					case 4:
						if (PC.Athletics() != 5 && experience >= (PC.Athletics() + 1) * 5)
						{
							PC.specialization->Athletics += 1;
							experience -= (PC.Athletics() + 1) * 5;
						}
						break;
					case 5:
						if (PC.Resilience() != 5 && experience >= (PC.Resilience() + 1) * 5)
						{
							PC.specialization->Resilience += 1;
							experience -= (PC.Resilience() + 1) * 5;
						}
						break;
					case 6:
						if (PC.Melee() != 5 && experience >= (PC.Melee() + 1) * 5)
						{
							PC.specialization->Melee += 1;
							experience -= (PC.Melee() + 1) * 5;
						}
						break;
					case 7:
						if (PC.Coordination() != 5 && experience >= (PC.Coordination() + 1) * 5)
						{
							PC.specialization->Coordination += 1;
							experience -= (PC.Coordination() + 1) * 5;
						}
						break;
					case 8:
						if (PC.Stealth() != 5 && experience >= (PC.Stealth() + 1) * 5)
						{
							PC.specialization->Stealth += 1;
							experience -= (PC.Stealth() + 1) * 5;
						}
						break;
					case 9:
						if (PC.Ranged() != 5 && experience >= (PC.Ranged() + 1) * 5)
						{
							PC.specialization->Ranged += 1;
							experience -= (PC.Ranged() + 1) * 5;
						}
						break;
					case 10:
						if (PC.Discipline() != 5 && experience >= (PC.Discipline() + 1) * 5)
						{
							PC.specialization->Discipline += 1;
							experience -= (PC.Discipline() + 1) * 5;
						}
						break;
					case 11:
						if (PC.Vigilance() != 5 && experience >= (PC.Vigilance() + 1) * 5)
						{
							PC.specialization->Vigilance += 1;
							experience -= (PC.Vigilance() + 1) * 5;
						}
						break;
					case 12:
						if (PC.Coercion() != 5 && experience >= (PC.Coercion() + 1) * 5)
						{
							PC.specialization->Coercion += 1;
							experience -= (PC.Coercion() + 1) * 5;
						}
						break;
					case 13:
						if (PC.Perception() != 5 && experience >= (PC.Perception() + 1) * 5)
						{
							PC.specialization->Perception += 1;
							experience -= (PC.Perception() + 1) * 5;
						}
						break;
					case 14:
						if (PC.Skullduggery() != 5 && experience >= (PC.Skullduggery() + 1) * 5)
						{
							PC.specialization->Skullduggery += 1;
							experience -= (PC.Skullduggery() + 1) * 5;
						}
						break;
					case 15:
						if (PC.Survival() != 5 && experience >= (PC.Survival() + 1) * 5)
						{
							PC.specialization->Survival += 1;
							experience -= (PC.Survival() + 1) * 5;
						}
						break;
					case 16:
						if (PC.Cool() != 5 && experience >= (PC.Cool() + 1) * 5)
						{
							PC.specialization->Cool += 1;
							experience -= (PC.Cool() + 1) * 5;
						}
						break;
					case 17:
						if (PC.Charm() != 5 && experience >= (PC.Charm() + 1) * 5)
						{
							PC.specialization->Charm += 1;
							experience -= (PC.Charm() + 1) * 5;
						}
						break;
					case 18:
						if (PC.Negotiation() != 5 && experience >= (PC.Negotiation() + 1) * 5)
						{
							PC.specialization->Negotiation += 1;
							experience -= (PC.Negotiation() + 1) * 5;
						}
						break;
					default:
						break;
					}

					PC.SetAll();
					break;
				}
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

		if (Wizard* wizard = dynamic_cast<Wizard*>(spec.get())) 
		{
			std::shared_ptr<Item> healer = std::make_shared<Potion>("Heal potion", 5);
			healer->addCopy(3);
			PC.addItem(healer.get());
		}

	};

};