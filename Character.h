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
	size_t money;
	std::unique_ptr<Archetype> archetype;
	std::unique_ptr<Specialization> specialization;
	Inventory inventory;

	Character();
	explicit Character(const std::string& name, std::unique_ptr<Archetype> archetype,
		std::unique_ptr<Specialization> specialization);
	Character(const Character& other) = delete;

	Character& operator=(const Character& other) = delete;

	Character(Character&& other) noexcept;
	Character& operator=(Character&& other) noexcept;

	~Character() = default;

	void SetAll();

	size_t alchemy() const;
	size_t mechanics() const;
	size_t magic() const;
	size_t athletics() const;
	size_t resilience() const;
	size_t melee() const;
	size_t coordination() const;
	size_t stealth() const;
	size_t ranged() const;
	size_t discipline() const;
	size_t vigilance() const;
	size_t coercion() const;
	size_t perception() const;
	size_t skullduggery() const;
	size_t survival() const;
	size_t cool() const;
	size_t charm() const;
	size_t negotiation() const;
	size_t Alchemy() const;
	size_t Mechanics() const;
	size_t Magic() const;
	size_t Athletics() const;
	size_t Resilience() const;
	size_t Melee() const;
	size_t Coordination() const;
	size_t Stealth() const;
	size_t Ranged() const;
	size_t Discipline() const;
	size_t Vigilance() const;
	size_t Coercion() const;
	size_t Perception() const;
	size_t Skullduggery() const;
	size_t Survival() const;
	size_t Cool() const;
	size_t Charm() const;
	size_t Negotiation() const;
	size_t Brawn() const;
	size_t Agility() const;
	size_t Intellect() const;
	size_t Cunning() const;
	size_t Willpower() const;
	size_t Presence() const;
	void recoverHP();
	void recoverAP();
	void fullRecover();


	bool addItem(std::unique_ptr<Item> item);

	size_t useItem(int effect, const std::string& name);

	template<typename T>
	void useItem(int effect) {
		for (size_t i = 0; i < inventory.getSize(); ++i)
		{
			Item* rawPtr = inventory[i].get();
			if (T* specific = dynamic_cast<T*>(rawPtr)) {
				specific->useItem(effect);
			}
		}
	}

	size_t rollDice(size_t numDice, size_t difficulty);

	void attack(Character& target, bool trueWeapon, size_t itemIndex, size_t numDice, size_t successDiff);

	bool skillCheck(size_t numDice, size_t successDiff);

	size_t initiative(size_t numDice);

	void printInfo();

	void serialize(std::ostream& out) const;

	void deserialize(std::istream& in);
};