#pragma once
#include <string>
#include <iostream>

class Item
{
protected:
	std::string name;
	bool isConsumable;
public:
	Item() : name("Unknown"), isConsumable(0) {};
	explicit Item(std::string name, bool isConsumable) : name(name), isConsumable(isConsumable) {};

	virtual ~Item() {};
	virtual int useItem(int effect) = 0;
	virtual bool getItem() = 0;

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
	Potion() : mod(0), count(0) {};
	explicit Potion(std::string name, int mod) : Item(name, 1), mod(mod), count(0) {};
	
	int useItem(int effect = 0) override
	{
		count -= 1;
		return mod + effect;
	}

	bool getItem() override
	{
		count += 1;
		return 1;
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
		armor_hp -= effect;
		return soak;
	}

	bool getItem() override
	{
		return 1;
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
		if (effect >= critic) { return damage * 2; }
		else { return damage; }
	}

	bool getItem() override
	{
		return 1;
	}
};

class QuestItem final : public Item
{
private:
	bool isExist;
public:
	QuestItem() : isExist(0) {};
	explicit QuestItem(std::string name) : Item(name, 1), isExist(0) {};

	int useItem(int effect = 0) override
	{
		isExist = 0;
		return 0;
	}

	bool getItem() override
	{
		isExist = 1;
		return 1;
	}
};