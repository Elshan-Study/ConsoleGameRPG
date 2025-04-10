#pragma once
#include "Archetype.h"
class Skill
{
protected:
	size_t value;
	size_t dices;
public:
	Skill() : value(0), dices(0) {};
	explicit Skill(size_t value) : value(value), dices(0) {};

	void changeValue(size_t mod) { value += mod; }
	virtual void setDices(Archetype* parameter) = 0;

	virtual ~Skill() = default;
};

class IntSkill final : public Skill
{
public:
	explicit IntSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }
	
	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->getIntellect();
	}
};

class BrawnSkill final : public Skill
{
public:
	explicit BrawnSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->getBrawn();
	}
};

class CunningSkill final : public Skill
{
public:
	explicit CunningSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->getCunning();
	}
};

class AgilitySkill final : public Skill
{
public:
	explicit AgilitySkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->getAgility();
	}
};

class WillpowerSkill final : public Skill
{
public:
	explicit WillpowerSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->getWillpower();
	}
};

class PresenceSkill final : public Skill
{
public:
	explicit PresenceSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->getPresence();
	}
};