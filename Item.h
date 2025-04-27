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
	Item();
	Item(const Item& other);
	explicit Item(std::string name, bool isConsumable);

	virtual ~Item() {};
	virtual size_t useItem(int effect) = 0;
	virtual void print(std::ostream& os) const = 0;

	friend std::ostream& operator<<(std::ostream& os, const Item& item);
	virtual void addCopy(size_t value) = 0;

	std::string Name() const;

	virtual void Serialize(std::ostream& out) const = 0;
	static std::unique_ptr<Item> Deserialize(std::istream& in);

};

class Potion final : public Item
{
private:
	int mod;
	size_t count;
public:
	Potion();
	explicit Potion(std::string name, int mod);
	Potion(const Potion& other);
	size_t useItem(int effect = 0) override;

	void addCopy(size_t value) override;
	void print(std::ostream& os) const override;
	void Serialize(std::ostream& out) const override;

	static std::unique_ptr<Item> DeserializePotion(std::istream& in);

};

class Armor final : public Item
{
private:
	size_t armor_hp;
	size_t soak;
public:
	size_t current_armor_hp;

	Armor();
	explicit Armor(std::string name, size_t armor_hp, size_t soak);
	Armor(const Armor& other);

	size_t getArmorHP() const;

	size_t useItem(int effect = 1) override;

	void addCopy(size_t value) override;
	
	void recoverArmorHP();

	void print(std::ostream& os) const override;

	void Serialize(std::ostream& out) const override;

	static std::unique_ptr<Item> DeserializeArmor(std::istream& in);

};

class Weapon final : public Item
{
private:
	size_t damage;
	size_t critic;
public:
	Weapon();
	explicit Weapon(std::string name, size_t damage, size_t critic);
	Weapon(const Weapon& other);

	size_t useItem(int effect) override;

	void print(std::ostream& os) const override;

	void addCopy(size_t value) override;

	void Serialize(std::ostream& out) const override;

	static std::unique_ptr<Item> DeserializeWeapon(std::istream& in);

};

class QuestItem final : public Item
{
public:
	QuestItem() {};
	explicit QuestItem(std::string name);
	QuestItem(const QuestItem& other);

	size_t useItem(int effect = 0) override;

	void print(std::ostream& os) const override;

	void addCopy(size_t value) override;

	void Serialize(std::ostream& out) const override;

	static std::unique_ptr<Item> DeserializeQuestItem(std::istream& in);

};