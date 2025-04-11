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
	CunningSkill Skulduggery;
	CunningSkill Survival;
	PresenceSkill Cool;
	PresenceSkill Charm;
	PresenceSkill Negotiation;

	Specialization(){};
	Specialization(const Specialization&) = delete;
	Specialization& operator=(const Specialization&) = delete;
	virtual ~Specialization() = default;
	
};

