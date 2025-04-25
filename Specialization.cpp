#include "Specialization.h"

void Specialization::setAllDices(Archetype* parameter)
{
	Alchemy.setDices(parameter);
	Mechanics.setDices(parameter);
	Magic.setDices(parameter);
	Athletics.setDices(parameter);
	Resilience.setDices(parameter);
	Melee.setDices(parameter);
	Coordination.setDices(parameter);
	Stealth.setDices(parameter);
	Ranged.setDices(parameter);
	Discipline.setDices(parameter);
	Vigilance.setDices(parameter);
	Coercion.setDices(parameter);
	Perception.setDices(parameter);
	Skullduggery.setDices(parameter);
	Survival.setDices(parameter);
	Cool.setDices(parameter);
	Charm.setDices(parameter);
	Negotiation.setDices(parameter);
}
void Specialization::SerializeSkills(std::ostream& out) const {
	Alchemy.Serialize(out);     Mechanics.Serialize(out);   Magic.Serialize(out);
	Athletics.Serialize(out);   Resilience.Serialize(out);  Melee.Serialize(out);
	Coordination.Serialize(out); Stealth.Serialize(out);   Ranged.Serialize(out);
	Discipline.Serialize(out);  Vigilance.Serialize(out);  Coercion.Serialize(out);
	Perception.Serialize(out);  Skullduggery.Serialize(out); Survival.Serialize(out);
	Cool.Serialize(out);        Charm.Serialize(out);      Negotiation.Serialize(out);
}
void Specialization::DeserializeSkills(std::istream& in, Archetype* archetype) {
	Alchemy.Deserialize(in, archetype);
	Mechanics.Deserialize(in, archetype);
	Magic.Deserialize(in, archetype);
	Athletics.Deserialize(in, archetype);
	Resilience.Deserialize(in, archetype);
	Melee.Deserialize(in, archetype);
	Coordination.Deserialize(in, archetype);
	Stealth.Deserialize(in, archetype);
	Ranged.Deserialize(in, archetype);
	Discipline.Deserialize(in, archetype);
	Vigilance.Deserialize(in, archetype);
	Coercion.Deserialize(in, archetype);
	Perception.Deserialize(in, archetype);
	Skullduggery.Deserialize(in, archetype);
	Survival.Deserialize(in, archetype);
	Cool.Deserialize(in, archetype);
	Charm.Deserialize(in, archetype);
	Negotiation.Deserialize(in, archetype);
}

Wizard::Wizard()
{
	Alchemy = 2;
	Magic = 2;
	Discipline = 2;
	Perception = 2;
}
void Wizard::Serialize(std::ostream& out) const  {
	std::string type = "Wizard";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);
}

Knight::Knight()
{
	Athletics = 2;
	Resilience = 2;
	Melee = 2;
	Coercion = 2;
}
void Knight::Serialize(std::ostream& out) const {
	std::string type = "Knight";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);
}

Archer::Archer()
{
	Coordination = 2;
	Ranged = 2;
	Perception = 2;
	Survival = 2;
}
void Archer::Serialize(std::ostream& out) const  {
	std::string type = "Archer";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);
}

Thief::Thief()
{
	Coordination = 2;
	Melee = 2;
	Stealth = 2;
	Skullduggery = 2;
}
void Thief::Serialize(std::ostream & out) const  {
	std::string type = "Thief";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);
}

Craftsman::Craftsman()
{
	Cool = 2;
	Charm = 2;
	Negotiation = 2;
	Mechanics = 2;
}
void Craftsman::Serialize(std::ostream& out) const  {
	std::string type = "Craftsman";
	size_t len = type.size();
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(type.c_str(), len);
}

std::unique_ptr<Specialization> SpecializationDeserialize(std::istream& in) {
	size_t len;
	in.read(reinterpret_cast<char*>(&len), sizeof(len));
	std::string type(len, '\0');
	in.read(&type[0], len);

	if (type == "Wizard") return std::make_unique<Wizard>();
	if (type == "Knight") return std::make_unique<Knight>();
	if (type == "Archer") return std::make_unique<Archer>();
	if (type == "Thief") return std::make_unique<Thief>();
	if (type == "Craftsman") return std::make_unique<Craftsman>();

	throw std::runtime_error("Unknown Specialization type during deserialization: " + type);
}