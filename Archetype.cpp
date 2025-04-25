#include "Archetype.h"

Archetype::Archetype() : Brawn(1), Agility(1), Intellect(1), Cunning(1), Willpower(1), Presence(1), HP(1), AP(1) {};
Archetype::Archetype(size_t brawn, size_t agility, size_t intellect, size_t cunning, size_t willpower, size_t presence) : HP(0), AP(0)
{
	Brawn = brawn;
	Agility = agility;
	Intellect = intellect;
	Cunning = cunning;
	Willpower = willpower;
	Presence = presence;
};

Sturdy::Sturdy() : Archetype(3, 2, 2, 2, 1, 2) { setHP(); setAP(); }

void Sturdy::Serialize(std::ostream& out) const {
	std::string type = "Sturdy";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);

	out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
	out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
	out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
	out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
	out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
	out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
	out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
	out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
}

Genius::Genius() : Archetype(2, 1, 3, 2, 2, 2) { setHP(); setAP(); }

void Genius::Serialize(std::ostream& out) const {
	std::string type = "Genius";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);

	out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
	out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
	out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
	out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
	out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
	out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
	out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
	out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
}

Aristocrat::Aristocrat() : Archetype(1, 2, 2, 2, 2, 3) { setHP(); setAP(); }

void Aristocrat::Serialize(std::ostream& out) const {
	std::string type = "Aristocrat";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);

	out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
	out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
	out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
	out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
	out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
	out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
	out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
	out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
}

Simpleton::Simpleton() : Archetype(2, 2, 2, 2, 2, 2) { setHP(); setAP(); }

void Simpleton::Serialize(std::ostream& out) const {
	std::string type = "Simpleton";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);

	out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
	out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
	out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
	out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
	out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
	out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
	out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
	out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
}

std::unique_ptr<Archetype> DeserializeArchetype(std::istream& in) {
	size_t len;
	in.read(reinterpret_cast<char*>(&len), sizeof(len));
	std::string type(len, '\0');
	in.read(&type[0], len);

	std::unique_ptr<Archetype> archetype;

	if (type == "Sturdy") archetype = std::make_unique<Sturdy>();
	else if (type == "Genius") archetype = std::make_unique<Genius>();
	else if (type == "Aristocrat") archetype = std::make_unique<Aristocrat>();
	else if (type == "Simpleton") archetype = std::make_unique<Simpleton>();
	else throw std::runtime_error("Unknown Archetype type");

	in.read(reinterpret_cast<char*>(&archetype->Brawn), sizeof(archetype->Brawn));
	in.read(reinterpret_cast<char*>(&archetype->Agility), sizeof(archetype->Agility));
	in.read(reinterpret_cast<char*>(&archetype->Intellect), sizeof(archetype->Intellect));
	in.read(reinterpret_cast<char*>(&archetype->Cunning), sizeof(archetype->Cunning));
	in.read(reinterpret_cast<char*>(&archetype->Willpower), sizeof(archetype->Willpower));
	in.read(reinterpret_cast<char*>(&archetype->Presence), sizeof(archetype->Presence));
	in.read(reinterpret_cast<char*>(&archetype->HP), sizeof(archetype->HP));
	in.read(reinterpret_cast<char*>(&archetype->AP), sizeof(archetype->AP));

	return archetype;
}