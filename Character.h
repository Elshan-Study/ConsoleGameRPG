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

	explicit Character(std::string name, Archetype* archetype, Specialization* specialization) : name(name), archetype(archetype), specialization(specialization)
	{ 
		currentHP = archetype->getHP(); 
		currentAP = archetype->getAP();
		specialization->setAllDices(archetype);
	}

	virtual ~Character() = default;

	size_t alchemy() const { return specialization->Alchemy.getDices(); };
	size_t mechanics() const { return specialization->Mechanics.getDices(); };
	size_t magic() const { return specialization->Magic.getDices(); };
	size_t athletics() const { return specialization->Athletics.getDices(); };
	size_t resilience() const { return specialization->Resilience.getDices(); };
	size_t melee() const { return specialization->Melee.getDices(); };
	size_t coordination() const { return specialization->Coordination.getDices(); };
	size_t stealth() const { return specialization->Stealth.getDices(); };
	size_t ranged() const { return specialization->Ranged.getDices(); };
	size_t discipline() const { return specialization->Discipline.getDices(); };
	size_t vigilance() const { return specialization->Vigilance.getDices(); };
	size_t coercion() const { return specialization->Coercion.getDices(); };
	size_t perception() const { return specialization->Perception.getDices(); };
	size_t skullduggery() const { return specialization->Skullduggery.getDices(); };
	size_t survival() const { return specialization->Survival.getDices(); };
	size_t cool() const { return specialization->Cool.getDices(); };
	size_t charm() const { return specialization->Charm.getDices(); };
	size_t negotiation() const { return specialization->Negotiation.getDices(); };
	void recoverHP() { currentHP = archetype->getHP(); }
	void recoverAP() { currentAP = archetype->getAP(); }
	void fullRecover() { recoverHP(); recoverAP(); }

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
};

