#include "Item.h"

Item::Item() : name("Unknown"), isConsumable(0), isExist(1) {};
Item::Item(const Item& other) : name(other.name), isConsumable(other.isConsumable), isExist(other.isExist) {};
Item::Item(std::string name, bool isConsumable) : name(name), isConsumable(isConsumable), isExist(1) {};

std::ostream& operator<<(std::ostream& os, const Item& item) {
	item.print(os);
	return os;
}

std::string Item::Name() const { return name; }


Potion::Potion() : mod(0), count(1) {};
Potion::Potion(std::string name, int mod) : Item(name, 1), mod(mod), count(1) {};
Potion::Potion(const Potion& other) : Item(other), mod(other.mod), count(other.count) {};

size_t Potion::useItem(int effect)
{
	if (isExist == 0) { return 0; }
	count -= 1;
	if (count == 0) { isExist = 0; }
	return mod + effect;
}

void Potion::addCopy(size_t value)
{
	count += value;
	isExist = 1;
}

void Potion::print(std::ostream& os) const
{
	os << name << "(" << mod << ") : " << count << "\n";
}

void Potion::Serialize(std::ostream& out) const {
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

std::unique_ptr<Item> Potion::DeserializePotion(std::istream& in) {
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

Armor::Armor() : armor_hp(0), soak(0) {};
Armor::Armor(std::string name, size_t armor_hp, size_t soak) : Item(name, 0), armor_hp(armor_hp), soak(soak) {};
Armor::Armor(const Armor& other) : Item(other), armor_hp(other.armor_hp), soak(other.soak) {};

size_t Armor::useItem(int effect) 
{
	if (isExist == 0) { return 0; }
	armor_hp -= effect;
	if (armor_hp == 0) { isExist = 0; }
	return soak;
}

void Armor::addCopy(size_t value) {}

void Armor::print(std::ostream& os) const 
{
	os << name << "(Soak: " << soak << "; Armor HP: " << armor_hp << ")" << "\n";
}

void Armor::Serialize(std::ostream& out) const  {
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

std::unique_ptr<Item> Armor::DeserializeArmor(std::istream& in) {
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


Weapon::Weapon() : damage(0), critic(4) {};
Weapon::Weapon(std::string name, size_t damage, size_t critic) : Item(name, 0), damage(damage), critic(critic) {};
Weapon::Weapon(const Weapon& other) : Item(other), damage(other.damage), critic(other.critic) {};

size_t Weapon::useItem(int effect)
{
	if (isExist == 0) { return 0; }
	if (effect >= critic) { return damage * 2; }
	else { return damage; }
}

void Weapon::print(std::ostream& os) const
{
	os << name << "(Damage: " << damage << "; Critic: " << critic << ")" << "\n";
}

void Weapon::addCopy(size_t value) {}

void Weapon::Serialize(std::ostream& out) const {
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

std::unique_ptr<Item> Weapon::DeserializeWeapon(std::istream& in) {
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

QuestItem::QuestItem(std::string name) : Item(name, 0) {};
QuestItem::QuestItem(const QuestItem& other) : Item(other) {};

size_t QuestItem::useItem(int effect) 
{
	if (isExist == 0) { return 0; }
	isExist = 0;
	return 0;
}

void QuestItem::print(std::ostream& os) const 
{
	os << name << "\n";
}

void QuestItem::addCopy(size_t value) {}

void QuestItem::Serialize(std::ostream& out) const {
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

std::unique_ptr<Item> QuestItem::DeserializeQuestItem(std::istream& in) {
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

std::unique_ptr<Item> Item::Deserialize(std::istream& in) {
	size_t len;
	in.read(reinterpret_cast<char*>(&len), sizeof(len));
	std::string type(len, '\0');
	in.read(&type[0], len);

	if (type == "Potion") return Potion::DeserializePotion(in);
	if (type == "Armor") return Armor::DeserializeArmor(in);
	if (type == "Weapon") return Weapon::DeserializeWeapon(in);
	if (type == "QuestItem") return QuestItem::DeserializeQuestItem(in);

	throw std::runtime_error("Unknown item type during deserialization: " + type);
}