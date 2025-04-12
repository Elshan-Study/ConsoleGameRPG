#pragma once
#include <string>
#include <iostream>

class Item
{
protected:
	std::string name;
	bool isConsumable;
public:
	bool isExist;
	Item() : name("Unknown"), isConsumable(0), isExist(1) {};
	explicit Item(std::string name, bool isConsumable) : name(name), isConsumable(isConsumable), isExist(1) {};

	virtual ~Item() {};
	virtual int useItem(int effect) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << item.name << "\n";
        return os;
    }
};

class Potion final : public Item
{
private:
	int mod;
	size_t count;
public:
	Potion() : mod(0), count(1) {};
	explicit Potion(std::string name, int mod) : Item(name, 1), mod(mod), count(1) {};
	
	int useItem(int effect = 0) override
	{
		if (isExist == 0) { return 0; }
		count -= 1;
		if (count == 0) { isExist = 0; }
		return mod + effect;
	}

	void addCopy(size_t value)
	{
		count += value;
		isExist = 1;
	}
};

class Armor final : public Item
{
private:
	size_t armor_hp;
	size_t soak;
public:
	Armor() : armor_hp(0), soak(0) {};
	explicit Armor(std::string name, size_t armor_hp, size_t soak) : Item(name, 0), armor_hp(armor_hp), soak(soak) {};

	int useItem(int effect = 1) override
	{
		if (isExist == 0) { return 0; }
		armor_hp -= effect;
		if (armor_hp == 0) { isExist = 0; }
		return soak;
	}
};

class Weapon final : public Item
{
private:
	size_t damage;
	size_t critic;
public:
	Weapon() : damage(0), critic(4) {};
	explicit Weapon(std::string name, size_t damage, size_t critic) : Item(name, 0), damage(damage), critic(critic) {};

	int useItem(int effect) override
	{
		if (isExist == 0) { return 0; }
		if (effect >= critic) { return damage * 2; }
		else { return damage; }
	}
};

class QuestItem final : public Item
{
public:
	QuestItem() {};
	explicit QuestItem(std::string name) : Item(name, 1) {};

	int useItem(int effect = 0) override
	{
		if (isExist == 0) { return 0; }
		isExist = 0;
		return 0;
	}
};