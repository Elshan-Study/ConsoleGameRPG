#pragma once
#include "Skill.h"
#include "Item.h"
#include <fstream>
#include <iostream>
class Specialization
{
public:
	IntSkill Alchemy;
	IntSkill Mechanics;
	IntSkill Magic;
	BrawnSkill Athletics;
	BrawnSkill Resilience;
	BrawnSkill Melee;
	AgilitySkill Coordination; 
	AgilitySkill Stealth;
	AgilitySkill Ranged;
	WillpowerSkill Discipline;
	WillpowerSkill Vigilance;
	WillpowerSkill Coercion;
	CunningSkill Perception;
	CunningSkill Skullduggery;
	CunningSkill Survival;
	PresenceSkill Cool;
	PresenceSkill Charm;
	PresenceSkill Negotiation;

	Specialization(){};
	virtual ~Specialization() = default;
	void setAllDices(Archetype* parameter)
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

	virtual void Serialize(std::ostream& out) const = 0;

	void SerializeSkills(std::ostream& out) const {
		Alchemy.Serialize(out);     Mechanics.Serialize(out);   Magic.Serialize(out);
		Athletics.Serialize(out);   Resilience.Serialize(out);  Melee.Serialize(out);
		Coordination.Serialize(out); Stealth.Serialize(out);   Ranged.Serialize(out);
		Discipline.Serialize(out);  Vigilance.Serialize(out);  Coercion.Serialize(out);
		Perception.Serialize(out);  Skullduggery.Serialize(out); Survival.Serialize(out);
		Cool.Serialize(out);        Charm.Serialize(out);      Negotiation.Serialize(out);
	}
	void DeserializeSkills(std::istream& in, Archetype* archetype) {
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

};

class Wizard final : public Specialization
{
public:
	Wizard()
	{
		Alchemy = 2;
		Magic = 2;
		Discipline = 2;
		Perception = 2;
	}

	void Serialize(std::ostream& out) const override {
		std::string type = "Wizard";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);
	}
};

class Knight final : public Specialization
{
public:
	Knight()
	{
		Athletics = 2;
		Resilience = 2;
		Melee = 2;
		Coercion = 2;
	}

	 void Serialize(std::ostream& out) const {
		 std::string type = "Knight";
		 size_t len = type.size();
		 out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		 out.write(type.c_str(), len);
	 }
};

class Archer final : public Specialization
{
public:
	Archer()
	{
		Coordination = 2;
		Ranged = 2;
		Perception = 2;
		Survival = 2;
	}

	void Serialize(std::ostream& out) const override {
		std::string type = "Archer";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);
	}
};

class Thief final : public Specialization
{
public:
	Thief()
	{
		Coordination = 2;
		Melee = 2;
		Stealth = 2;
		Skullduggery = 2;
	}

	void Serialize(std::ostream& out) const override {
		std::string type = "Thief";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);
	}
};

class Craftsman final : public Specialization
{
public:
	Craftsman()
	{
		Cool = 2;
		Charm = 2;
		Negotiation = 2;
		Mechanics = 2;
	}

	void Serialize(std::ostream& out) const override {
		std::string type = "Craftsman";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);
	}
};

std::unique_ptr<Specialization> SpecializationDeserialize(std::istream& in);