#include "Item.h"

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