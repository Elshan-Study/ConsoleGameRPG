#pragma once
#include "Archetype.h"
class Skill
{
protected:
	size_t value;
	size_t dices;
public:
	Skill() : value(0), dices(0) {};
	explicit Skill(size_t new_value) : value(new_value), dices(0) {};

	virtual void changeValue(int mod, Archetype* parameter) = 0;
	virtual void setDices(Archetype* parameter) = 0;
	size_t getDices() const { return dices; }
	size_t getValue() const { return value; }

	virtual ~Skill() = default;
	
	void operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
	void operator+=(size_t mod) { dices += mod; value += mod;} /*!Need exceptions: if mod < 0*/
	void operator-=(size_t mod) { dices -= mod; value -= mod; } /*!Need exceptions: if mod < 0 && mod > value */
};

class IntSkill final : public Skill
{
public:
	IntSkill() {};
	explicit IntSkill(size_t new_value) : Skill(new_value) {};
	
	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->Intellect;
	}

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
	}

	void operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
};

class BrawnSkill final : public Skill
{
public:
	BrawnSkill() {};
	explicit BrawnSkill(size_t new_value) : Skill(new_value) {};

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->Brawn;
	}

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
	}

	void operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
};

class CunningSkill final : public Skill
{
public:
	CunningSkill() {};
	explicit CunningSkill(size_t new_value) : Skill(new_value) {};

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->Cunning;
	}

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
	}

	void operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
};

class AgilitySkill final : public Skill
{
public:
	AgilitySkill() {};
	explicit AgilitySkill(size_t new_value) : Skill(new_value) {};

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->Agility;
	}

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
	}

	void operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
};

class WillpowerSkill final : public Skill
{
public:
	WillpowerSkill() {};
	explicit WillpowerSkill(size_t new_value) : Skill(new_value) {};

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->Willpower;
	}

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
	}

	void operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
};

class PresenceSkill final : public Skill
{
public:
	PresenceSkill() {};
	explicit PresenceSkill(size_t new_value) : Skill(new_value) {};

	void setDices(Archetype* parameter) override
	{
		dices = value + parameter->Presence;
	}

	void changeValue(int mod, Archetype* parameter) override
	{
		value += mod;
		setDices(parameter);
	}

	void operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
};