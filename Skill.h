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

	virtual void changeValue(int mod, Archetype* parameter) = 0;
	virtual void setDices(Archetype* parameter) = 0;
	size_t getDices() const { return dices; }

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

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
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

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
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

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
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

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
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

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
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

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
	}
};