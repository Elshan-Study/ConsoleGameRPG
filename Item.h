#pragma once
#include <string>
#include <iostream>
#include <memory>

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

	virtual void Serialize(std::ostream& out) const = 0;
	static std::unique_ptr<Item> Deserialize(std::istream& in);

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

	void Serialize(std::ostream& out) const override {
		std::string type = "Potion";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		size_t name_len = name.size();
		out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
		out.write(name.c_str(), name_len);

		out.write(reinterpret_cast<const char*>(&isConsumable), sizeof(isConsumable));
		out.write(reinterpret_cast<const char*>(&isExist), sizeof(isExist));
		out.write(reinterpret_cast<const char*>(&mod), sizeof(mod));
		out.write(reinterpret_cast<const char*>(&count), sizeof(count));
	}

	static std::unique_ptr<Item> DeserializePotion(std::istream& in) {
		size_t name_len;
		in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
		std::string name(name_len, '\0');
		in.read(&name[0], name_len);

		bool isConsumable;
		bool isExist;
		int mod;
		size_t count;

		in.read(reinterpret_cast<char*>(&isConsumable), sizeof(isConsumable));
		in.read(reinterpret_cast<char*>(&isExist), sizeof(isExist));
		in.read(reinterpret_cast<char*>(&mod), sizeof(mod));
		in.read(reinterpret_cast<char*>(&count), sizeof(count));

		auto potion = std::make_unique<Potion>(name, mod);
		potion->isExist = isExist;
		potion->addCopy(count - 1); 
		return potion;
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

	void addCopy(size_t value) override {}

	void print(std::ostream& os) const override
	{
		os << name << "(Soak: " << soak << "; Armor HP: " << armor_hp << ")" << "\n";
	}

	void Serialize(std::ostream& out) const override {
		std::string type = "Armor";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		size_t name_len = name.size();
		out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
		out.write(name.c_str(), name_len);

		out.write(reinterpret_cast<const char*>(&isConsumable), sizeof(isConsumable));
		out.write(reinterpret_cast<const char*>(&isExist), sizeof(isExist));
		out.write(reinterpret_cast<const char*>(&armor_hp), sizeof(armor_hp));
		out.write(reinterpret_cast<const char*>(&soak), sizeof(soak));
	}

	static std::unique_ptr<Item> DeserializeArmor(std::istream& in) {
		size_t name_len;
		in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
		std::string name(name_len, '\0');
		in.read(&name[0], name_len);

		bool isConsumable;
		bool isExist;
		size_t armor_hp;
		size_t soak;

		in.read(reinterpret_cast<char*>(&isConsumable), sizeof(isConsumable));
		in.read(reinterpret_cast<char*>(&isExist), sizeof(isExist));
		in.read(reinterpret_cast<char*>(&armor_hp), sizeof(armor_hp));
		in.read(reinterpret_cast<char*>(&soak), sizeof(soak));

		auto armor = std::make_unique<Armor>(name, armor_hp, soak);
		armor->isExist = isExist;
		return armor;
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

	void Serialize(std::ostream& out) const override {
		std::string type = "Weapon";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		size_t name_len = name.size();
		out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
		out.write(name.c_str(), name_len);

		out.write(reinterpret_cast<const char*>(&isConsumable), sizeof(isConsumable));
		out.write(reinterpret_cast<const char*>(&isExist), sizeof(isExist));
		out.write(reinterpret_cast<const char*>(&damage), sizeof(damage));
		out.write(reinterpret_cast<const char*>(&critic), sizeof(critic));
	}

	static std::unique_ptr<Item> DeserializeWeapon(std::istream& in) {
		size_t name_len;
		in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
		std::string name(name_len, '\0');
		in.read(&name[0], name_len);

		bool isConsumable;
		bool isExist;
		size_t damage;
		size_t critic;

		in.read(reinterpret_cast<char*>(&isConsumable), sizeof(isConsumable));
		in.read(reinterpret_cast<char*>(&isExist), sizeof(isExist));
		in.read(reinterpret_cast<char*>(&damage), sizeof(damage));
		in.read(reinterpret_cast<char*>(&critic), sizeof(critic));

		auto weapon = std::make_unique<Weapon>(name, damage, critic);
		weapon->isExist = isExist;
		return weapon;
	}

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

	void Serialize(std::ostream& out) const override {
		std::string type = "QuestItem";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		size_t name_len = name.size();
		out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
		out.write(name.c_str(), name_len);

		out.write(reinterpret_cast<const char*>(&isConsumable), sizeof(isConsumable));
		out.write(reinterpret_cast<const char*>(&isExist), sizeof(isExist));
	}

	static std::unique_ptr<Item> DeserializeQuestItem(std::istream& in) {
		size_t name_len;
		in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
		std::string name(name_len, '\0');
		in.read(&name[0], name_len);

		bool isConsumable;
		bool isExist;

		in.read(reinterpret_cast<char*>(&isConsumable), sizeof(isConsumable));
		in.read(reinterpret_cast<char*>(&isExist), sizeof(isExist));

		auto questItem = std::make_unique<QuestItem>(name);
		questItem->isExist = isExist;
		return questItem;
	}

};