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
	Skill(size_t new_value) { dices -= value; value = new_value;  dices += value; }

	virtual void changeValue(int mod, Archetype* parameter) = 0;
	virtual void setDices(Archetype* parameter) = 0;
	size_t getDices() const { return dices; }

	virtual ~Skill() = default;

	void operator=(size_t new_value) { dices -= value; value = new_value;  dices += value;} /*!Need exceptions: if new_value < 0*/
	void operator+=(size_t mod) { dices += mod; value += mod;} /*!Need exceptions: if mod < 0*/
	void operator-=(size_t mod) { dices -= mod; value -= mod; } /*!Need exceptions: if mod < 0 && mod > value */
};

class IntSkill final : public Skill
{
public:
	IntSkill() {};
	explicit IntSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }
	IntSkill(size_t new_value) { dices -= value; value = new_value;  dices += value; }
	
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
	BrawnSkill() {};
	explicit BrawnSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }
	BrawnSkill(size_t new_value) { dices -= value; value = new_value;  dices += value; }

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
	CunningSkill() {};
	explicit CunningSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }
	CunningSkill(size_t new_value) { dices -= value; value = new_value;  dices += value; }

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
	AgilitySkill() {};
	explicit AgilitySkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }
	AgilitySkill(size_t new_value) { dices -= value; value = new_value;  dices += value; }

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
	WillpowerSkill() {};
	explicit WillpowerSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }
	WillpowerSkill(size_t new_value) { dices -= value; value = new_value;  dices += value; }

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
	PresenceSkill() {};
	explicit PresenceSkill(size_t value, Archetype* parameter) : Skill(value) { setDices(parameter); }
	PresenceSkill(size_t new_value) { dices -= value; value = new_value;  dices += value; }

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