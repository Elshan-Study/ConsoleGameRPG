#pragma once
#include "Skill.h"
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

	Specialization(const Specialization&) = delete;
	Specialization& operator=(const Specialization&) = delete;
	virtual ~Specialization() = default;
	/*virtual Item getClassStartItem() = 0;*/
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
};