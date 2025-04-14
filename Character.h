#pragma once
#include "Archetype.h"
#include <iostream>
#include <memory>
#include "Inventory.h"
#include "Specialization.h"

class Character
{
public:
	std::string name;
	size_t currentHP;
	size_t currentAP;
	std::unique_ptr<Archetype> archetype;
	std::unique_ptr<Specialization> specialization;
	Inventory inventory;

	Character() : name("name"), archetype(nullptr), specialization(nullptr), currentHP(0), currentAP(0) {};
	explicit Character(const std::string& name, std::unique_ptr<Archetype> archetype,
		std::unique_ptr<Specialization> specialization) : name(name), archetype(std::move(archetype)), specialization(std::move(specialization))
	{
		currentHP = this->archetype->getHP();
		currentAP = this->archetype->getAP();
		this->specialization->setAllDices(this->archetype.get());
	}

	~Character() = default;

	void SetAll()
	{
		if (!archetype || !specialization) { return; }
		currentHP = archetype->getHP();
		currentAP = archetype->getAP();
		specialization->setAllDices(archetype.get());
	}

	size_t alchemy() const { if (!specialization) { return 0; } return specialization->Alchemy.getDices(); };
	size_t mechanics() const { if (!specialization) { return 0; } return specialization->Mechanics.getDices(); };
	size_t magic() const { if (!specialization) { return 0; } return specialization->Magic.getDices(); };
	size_t athletics() const { if (!specialization) { return 0; } return specialization->Athletics.getDices(); };
	size_t resilience() const { if (!specialization) { return 0; } return specialization->Resilience.getDices(); };
	size_t melee() const { if (!specialization) { return 0; } return specialization->Melee.getDices(); };
	size_t coordination() const { if (!specialization) { return 0; } return specialization->Coordination.getDices(); };
	size_t stealth() const { if (!specialization) { return 0; } return specialization->Stealth.getDices(); };
	size_t ranged() const { if (!specialization) { return 0; } return specialization->Ranged.getDices(); };
	size_t discipline() const { if (!specialization) { return 0; } return specialization->Discipline.getDices(); };
	size_t vigilance() const { if (!specialization) { return 0; } return specialization->Vigilance.getDices(); };
	size_t coercion() const { if (!specialization) { return 0; } return specialization->Coercion.getDices(); };
	size_t perception() const { if (!specialization) { return 0; } return specialization->Perception.getDices(); };
	size_t skullduggery() const { if (!specialization) { return 0; } return specialization->Skullduggery.getDices(); };
	size_t survival() const { if (!specialization) { return 0; } return specialization->Survival.getDices(); };
	size_t cool() const { if (!specialization) { return 0; } return specialization->Cool.getDices(); };
	size_t charm() const { if (!specialization) { return 0; } return specialization->Charm.getDices(); };
	size_t negotiation() const { if (!specialization) { return 0; } return specialization->Negotiation.getDices(); };
	size_t Alchemy() const { if (!specialization) { return 0; } return specialization->Alchemy.getValue(); };
	size_t Mechanics() const { if (!specialization) { return 0; } return specialization->Mechanics.getValue(); };
	size_t Magic() const { if (!specialization) { return 0; } return specialization->Magic.getValue(); };
	size_t Athletics() const { if (!specialization) { return 0; } return specialization->Athletics.getValue(); };
	size_t Resilience() const { if (!specialization) { return 0; } return specialization->Resilience.getValue(); };
	size_t Melee() const { if (!specialization) { return 0; } return specialization->Melee.getValue(); };
	size_t Coordination() const { if (!specialization) { return 0; } return specialization->Coordination.getValue(); };
	size_t Stealth() const { if (!specialization) { return 0; } return specialization->Stealth.getValue(); };
	size_t Ranged() const { if (!specialization) { return 0; } return specialization->Ranged.getValue(); };
	size_t Discipline() const { if (!specialization) { return 0; } return specialization->Discipline.getValue(); };
	size_t Vigilance() const { if (!specialization) { return 0; } return specialization->Vigilance.getValue(); };
	size_t Coercion() const { if (!specialization) { return 0; } return specialization->Coercion.getValue(); };
	size_t Perception() const { if (!specialization) { return 0; } return specialization->Perception.getValue(); };
	size_t Skullduggery() const { if (!specialization) { return 0; } return specialization->Skullduggery.getValue(); };
	size_t Survival() const { if (!specialization) { return 0; } return specialization->Survival.getValue(); };
	size_t Cool() const { if (!specialization) { return 0; } return specialization->Cool.getValue(); };
	size_t Charm() const { if (!specialization) { return 0; } return specialization->Charm.getValue(); };
	size_t Negotiation() const { if (!specialization) { return 0; } return specialization->Negotiation.getValue(); };
	size_t Brawn() const { if (!archetype) { return 0; } return archetype->Brawn; };
	size_t Agility() const { if (!archetype) { return 0; } return archetype->Agility; };
	size_t Intellect() const { if (!archetype) { return 0; } return archetype->Intellect; };
	size_t Cunning() const { if (!archetype) { return 0; } return archetype->Cunning; };
	size_t Willpower() const { if (!archetype) { return 0; } return archetype->Willpower; };
	size_t Presence() const { if (!archetype) { return 0; } return archetype->Presence; };
	void recoverHP() { if (!archetype) { return; } currentHP = archetype->getHP(); }
	void recoverAP() { if (!archetype) { return; } currentAP = archetype->getAP(); }
	void fullRecover() { if (!archetype) { return; } recoverHP(); recoverAP(); }


	size_t useItem(int effect, std::string name) 
	{ 
		for (size_t i = 0; i < inventory.getSize(); i++)
		{
			if (inventory.items[i]->Name() == name)
			{
				return inventory.items[i]->useItem(effect);
				break;
			}
		}
		return 0;
	}
	
	template <typename T>
	size_t useItem(int effect) {
		for (size_t i = 0; i < inventory.getSize(); ++i) {
			if (auto item = dynamic_cast<T*>(inventory[i])) {
				return item->useItem(effect); 
			}
		}
		return 0;
	}

	bool addItem(Item* item) { inventory.addItem(item); }

	void printInfo()
	{
		if (!archetype || !specialization) { return; }
		std::cout << name << "\n";
		std::cout << "HP: " << currentHP << "/" << archetype->getHP() << "\n";
		std::cout << "AP: " << currentHP << "/" << archetype->getAP() << "\n";
		std::cout << "\nCharacteristics: \n";
		std::cout << "Brawn: " << Brawn() << " | Agility: " << Agility()
			<< " | Intellect: " << Intellect() << " | Cunning: " << Cunning()
			<< " | Willpower: " << Willpower() << " | Presence: " << Presence() << "\n";
		std::cout << "\nSkills: \n";
		std::cout << "Alchemy: " << Alchemy() << "(" << alchemy() << " dices) | "
			<< "Mechanics: " << Mechanics() << "(" << mechanics() << " dices) | "
			<< "Magic: " << Magic() << "(" << magic() << " dices)\n"
			<< "Athletics: " << Athletics() << "(" << athletics() << " dices) | "
			<< "Resilience: " << Resilience() << "(" << resilience() << " dices) | "
			<< "Melee: " << Melee() << "(" << melee() << " dices)\n"
			<< "Coordination: " << Coordination() << "(" << coordination() << " dices) | "
			<< "Stealth: " << Stealth() << "(" << stealth() << " dices) | "
			<< "Ranged: " << Ranged() << "(" << ranged() << " dices)\n"
			<< "Discipline: " << Discipline() << "(" << discipline() << " dices) | "
			<< "Vigilance: " << Vigilance() << "(" << vigilance() << " dices) | "
			<< "Coercion: " << Coercion() << "(" << coercion() << " dices)\n"
			<< "Perception: " << Perception() << "(" << perception() << " dices) | "
			<< "Skullduggery: " << Skullduggery() << "(" << skullduggery() << " dices) | "
			<< "Survival: " << Survival() << "(" << survival() << " dices)\n"
			<< "Cool: " << Cool() << "(" << cool() << " dices) | "
			<< "Charm: " << Charm() << "(" << charm() << " dices) | "
			<< "Negotiation: " << Negotiation() << "(" << negotiation() << " dices)\n";
	}
};

