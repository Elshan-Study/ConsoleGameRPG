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
	void setAllDices(Archetype* parameter);

	virtual void Serialize(std::ostream& out) const = 0;

	void SerializeSkills(std::ostream& out) const;
	void DeserializeSkills(std::istream& in, Archetype* archetype);

};

class Wizard final : public Specialization
{
public:
	Wizard();

	void Serialize(std::ostream& out) const override;
};

class Knight final : public Specialization
{
public:
	Knight();

	void Serialize(std::ostream& out) const override;
};

class Archer final : public Specialization
{
public:
	Archer();

	void Serialize(std::ostream& out) const override;
};

class Thief final : public Specialization
{
public:
	Thief();
	void Serialize(std::ostream& out) const override;
};

class Craftsman final : public Specialization
{
public:
	Craftsman();

	void Serialize(std::ostream& out) const override;
};

std::unique_ptr<Specialization> SpecializationDeserialize(std::istream& in);