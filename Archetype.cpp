#include "Archetype.h"

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
