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
	Item(const Item& other) : name(other.name), isConsumable(other.isConsumable), isExist(other.isExist) {};
	explicit Item(std::string name, bool isConsumable) : name(name), isConsumable(isConsumable), isExist(1) {};

	virtual ~Item() {};
	virtual size_t useItem(int effect) = 0;
	virtual void print(std::ostream& os) const = 0;

	friend std::ostream& operator<<(std::ostream& os, const Item& item) {
		item.print(os);
		return os;
	}
	virtual void addCopy(size_t value) = 0;

	std::string Name() const { return name; }
};

class Potion final : public Item
{
private:
	int mod;
	size_t count;
public:
	Potion() : mod(0), count(1) {};
	explicit Potion(std::string name, int mod) : Item(name, 1), mod(mod), count(1) {};
	Potion(const Potion& other) : Item(other), mod(other.mod), count(other.count) {};
	
	size_t useItem(int effect = 0) override
	{
		if (isExist == 0) { return 0; }
		count -= 1;
		if (count == 0) { isExist = 0; }
		return mod + effect;
	}

	void addCopy(size_t value) override
	{
		count += value;
		isExist = 1;
	}

	void print(std::ostream& os) const override
	{
		os << name << "(" << mod << ") : " << count << "\n";
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
	Armor(const Armor& other) : Item(other), armor_hp(other.armor_hp), soak(other.soak) {};

	size_t useItem(int effect = 1) override
	{
		if (isExist == 0) { return 0; }
		armor_hp -= effect;
		if (armor_hp == 0) { isExist = 0; }
		return soak;
	}

	void print(std::ostream& os) const override
	{
		os << name << "(Soak: " << soak << "; Armor HP: " << armor_hp << ")" << "\n";
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
	Weapon(const Weapon& other) : Item(other), damage(other.damage), critic(other.critic) {};

	size_t useItem(int effect) override
	{
		if (isExist == 0) { return 0; }
		if (effect >= critic) { return damage * 2; }
		else { return damage; }
	}

	void print(std::ostream& os) const override
	{
		os << name << "(Damage: " << damage << "; Critic: " << critic << ")" << "\n";
	}

	void addCopy(size_t value) override {}
};

class QuestItem final : public Item
{
public:
	QuestItem() {};
	explicit QuestItem(std::string name) : Item(name, 0) {};
	QuestItem(const QuestItem& other) : Item(other) {};

	size_t useItem(int effect = 0) override
	{
		if (isExist == 0) { return 0; }
		isExist = 0;
		return 0;
	}

	void print(std::ostream& os) const override
	{
		os << name << "\n";
	}

	void addCopy(size_t value) override {}
};