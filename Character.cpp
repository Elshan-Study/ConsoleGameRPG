#include "Character.h"

Character::Character() : name("name"), archetype(nullptr), specialization(nullptr), currentHP(0), currentAP(0) {};
Character::Character(const std::string& name, std::unique_ptr<Archetype> archetype,
	std::unique_ptr<Specialization> specialization) : name(name), archetype(std::move(archetype)), specialization(std::move(specialization))
{
	currentHP = this->archetype->getHP();
	currentAP = this->archetype->getAP();
	this->specialization->setAllDices(this->archetype.get());
}

Character::Character(Character&& other) noexcept
	: name(std::move(other.name)),
	currentHP(other.currentHP),
	currentAP(other.currentAP),
	archetype(std::move(other.archetype)),
	specialization(std::move(other.specialization)),
	inventory(std::move(other.inventory)) {
}

Character& Character::operator=(Character&& other) noexcept {
	if (this != &other) {
		name = std::move(other.name);
		currentHP = other.currentHP;
		currentAP = other.currentAP;
		archetype = std::move(other.archetype);
		specialization = std::move(other.specialization);
		inventory = std::move(other.inventory);
	}
	return *this;
}

void Character::SetAll()
{
	if (!archetype || !specialization) { return; }
	archetype->setHP();
	archetype->setAP();
	currentHP = archetype->getHP();
	currentAP = archetype->getAP();
	specialization->setAllDices(archetype.get());
}

size_t Character::alchemy() const { if (!specialization) { return 0; } return specialization->Alchemy.getDices(); };
size_t Character::mechanics() const { if (!specialization) { return 0; } return specialization->Mechanics.getDices(); };
size_t Character::magic() const { if (!specialization) { return 0; } return specialization->Magic.getDices(); };
size_t Character::athletics() const { if (!specialization) { return 0; } return specialization->Athletics.getDices(); };
size_t Character::resilience() const { if (!specialization) { return 0; } return specialization->Resilience.getDices(); };
size_t Character::melee() const { if (!specialization) { return 0; } return specialization->Melee.getDices(); };
size_t Character::coordination() const { if (!specialization) { return 0; } return specialization->Coordination.getDices(); };
size_t Character::stealth() const { if (!specialization) { return 0; } return specialization->Stealth.getDices(); };
size_t Character::ranged() const { if (!specialization) { return 0; } return specialization->Ranged.getDices(); };
size_t Character::discipline() const { if (!specialization) { return 0; } return specialization->Discipline.getDices(); };
size_t Character::vigilance() const { if (!specialization) { return 0; } return specialization->Vigilance.getDices(); };
size_t Character::coercion() const { if (!specialization) { return 0; } return specialization->Coercion.getDices(); };
size_t Character::perception() const { if (!specialization) { return 0; } return specialization->Perception.getDices(); };
size_t Character::skullduggery() const { if (!specialization) { return 0; } return specialization->Skullduggery.getDices(); };
size_t Character::survival() const { if (!specialization) { return 0; } return specialization->Survival.getDices(); };
size_t Character::cool() const { if (!specialization) { return 0; } return specialization->Cool.getDices(); };
size_t Character::charm() const { if (!specialization) { return 0; } return specialization->Charm.getDices(); };
size_t Character::negotiation() const { if (!specialization) { return 0; } return specialization->Negotiation.getDices(); };
size_t Character::Alchemy() const { if (!specialization) { return 0; } return specialization->Alchemy.getValue(); };
size_t Character::Mechanics() const { if (!specialization) { return 0; } return specialization->Mechanics.getValue(); };
size_t Character::Magic() const { if (!specialization) { return 0; } return specialization->Magic.getValue(); };
size_t Character::Athletics() const { if (!specialization) { return 0; } return specialization->Athletics.getValue(); };
size_t Character::Resilience() const { if (!specialization) { return 0; } return specialization->Resilience.getValue(); };
size_t Character::Melee() const { if (!specialization) { return 0; } return specialization->Melee.getValue(); };
size_t Character::Coordination() const { if (!specialization) { return 0; } return specialization->Coordination.getValue(); };
size_t Character::Stealth() const { if (!specialization) { return 0; } return specialization->Stealth.getValue(); };
size_t Character::Ranged() const { if (!specialization) { return 0; } return specialization->Ranged.getValue(); };
size_t Character::Discipline() const { if (!specialization) { return 0; } return specialization->Discipline.getValue(); };
size_t Character::Vigilance() const { if (!specialization) { return 0; } return specialization->Vigilance.getValue(); };
size_t Character::Coercion() const { if (!specialization) { return 0; } return specialization->Coercion.getValue(); };
size_t Character::Perception() const { if (!specialization) { return 0; } return specialization->Perception.getValue(); };
size_t Character::Skullduggery() const { if (!specialization) { return 0; } return specialization->Skullduggery.getValue(); };
size_t Character::Survival() const { if (!specialization) { return 0; } return specialization->Survival.getValue(); };
size_t Character::Cool() const { if (!specialization) { return 0; } return specialization->Cool.getValue(); };
size_t Character::Charm() const { if (!specialization) { return 0; } return specialization->Charm.getValue(); };
size_t Character::Negotiation() const { if (!specialization) { return 0; } return specialization->Negotiation.getValue(); };
size_t Character::Brawn() const { if (!archetype) { return 0; } return archetype->Brawn; };
size_t Character::Agility() const { if (!archetype) { return 0; } return archetype->Agility; };
size_t Character::Intellect() const { if (!archetype) { return 0; } return archetype->Intellect; };
size_t Character::Cunning() const { if (!archetype) { return 0; } return archetype->Cunning; };
size_t Character::Willpower() const { if (!archetype) { return 0; } return archetype->Willpower; };
size_t Character::Presence() const { if (!archetype) { return 0; } return archetype->Presence; };
void Character::recoverHP() { if (!archetype) { return; } currentHP = archetype->getHP(); }
void Character::recoverAP() { if (!archetype) { return; } currentAP = archetype->getAP(); }
void Character::fullRecover() { if (!archetype) { return; } recoverHP(); recoverAP(); }


bool Character::addItem(std::unique_ptr<Item> item) {
	inventory.addItem(std::move(item));
	return true;
}

size_t Character::useItem(int effect, const std::string& name) {
	for (size_t i = 0; i < inventory.getSize(); ++i) {
		if (inventory[i] && inventory[i]->Name() == name) {
			return inventory[i]->useItem(effect);
		}
	}
	return 0;
}

size_t Character::rollDice(size_t numDice, size_t difficulty) {
	std::cout << "(check value: " << difficulty << ")\n";
	size_t successCount = 0;

	for (int i = 0; i < numDice; ++i) {
		int roll = rand() % 10 + 1;
		std::cout << "Dice #" << (i + 1) << ": " << roll << "\n";
		if (roll >= difficulty) {
			successCount++;
		}
	}
	std::cout << "\n";

	return successCount;
}

void Character::attack(Character& target, bool trueWeapon, size_t itemIndex, size_t numDice, size_t successDiff)
{
	size_t soak = 0;
	size_t damage = 0;
	std::cout << "Difficult: " << successDiff << " success ";
	size_t roll = rollDice(numDice, 6);

	if (roll >= successDiff)
	{
		for (size_t i = 0; i < target.inventory.getSize(); ++i)
		{
			Item* item = target.inventory[i].get();
			if (dynamic_cast<Armor*>(item) != nullptr)
			{
				soak = item->useItem(1);
				break;
			}
		}

		size_t itemEffect = 0;
		if (trueWeapon && (itemIndex < inventory.getSize()))
		{
			Item* weapon = inventory[itemIndex].get();
			if (dynamic_cast<Weapon*>(weapon) != nullptr)
			{
				itemEffect = weapon->useItem(roll);
				std::cout << *weapon;
			}
		}

		if (itemEffect == 0)
		{
			itemEffect = Brawn();
			std::cout << name << " without weapon attack\n";
		}

		if (soak >= itemEffect)
		{
			damage = 0;
		}
		else
		{
			damage = itemEffect - soak;
		}
		std::cout << "Total damage: " << damage << "\n";

		target.currentHP = (damage >= target.currentHP) ? 0 : target.currentHP - damage;
	}
	else { std::cout << "Unsuccess!\n"; }
}

bool Character::skillCheck(size_t numDice, size_t successDiff)
{
	size_t roll = rollDice(numDice, 5);

	if (roll >= successDiff)
	{
		return 1;
	}

	return 0;
}

size_t Character::initiative(size_t numDice)
{
	return rollDice(numDice, 3);
}

void Character::printInfo()
{
	if (!archetype || !specialization) { return; }
	std::cout << name << "\n";
	std::cout << "HP: " << currentHP << "/" << archetype->getHP() << "\n";
	std::cout << "AP: " << currentAP << "/" << archetype->getAP() << "\n";
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
	std::cout << "Inventory: \n" << inventory;
}

void Character::serialize(std::ostream& out) const {
	size_t nameLength = name.size();
	out.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
	out.write(name.c_str(), nameLength);

	out.write(reinterpret_cast<const char*>(&currentHP), sizeof(currentHP));
	out.write(reinterpret_cast<const char*>(&currentAP), sizeof(currentAP));

	bool hasArchetype = archetype != nullptr;
	out.write(reinterpret_cast<const char*>(&hasArchetype), sizeof(hasArchetype));
	if (hasArchetype) {
		archetype->Serialize(out);
	}

	bool hasSpecialization = specialization != nullptr;
	out.write(reinterpret_cast<const char*>(&hasSpecialization), sizeof(hasSpecialization));
	if (hasSpecialization) {
		specialization->Serialize(out);
		specialization->SerializeSkills(out);
	}

	inventory.Serialize(out);
}

void Character::deserialize(std::istream& in) {
	size_t nameLength;
	in.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
	name.resize(nameLength);
	in.read(&name[0], nameLength);

	in.read(reinterpret_cast<char*>(&currentHP), sizeof(currentHP));
	in.read(reinterpret_cast<char*>(&currentAP), sizeof(currentAP));

	bool hasArchetype;
	in.read(reinterpret_cast<char*>(&hasArchetype), sizeof(hasArchetype));
	if (hasArchetype) {
		archetype = std::move(DeserializeArchetype(in));
	}

	bool hasSpecialization;
	in.read(reinterpret_cast<char*>(&hasSpecialization), sizeof(hasSpecialization));
	if (hasSpecialization) {
		specialization = std::move(SpecializationDeserialize(in));
		specialization->DeserializeSkills(in, archetype.get());
	}

	inventory.Deserialize(in);
}