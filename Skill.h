#pragma once
#include "Archetype.h"
class Skill
{
protected:
	size_t value;
	size_t dices;
public:
	Skill();
	explicit Skill(size_t new_value);

	virtual void changeValue(int mod, Archetype* parameter) = 0;
	virtual void setDices(Archetype* parameter) = 0;
	size_t getDices() const;
	size_t getValue() const;

	virtual ~Skill() = default;
	
	void operator=(int new_value);
	void operator+=(size_t mod);
	void operator-=(size_t mod);

	virtual void Serialize(std::ostream& out) const {
		out.write(reinterpret_cast<const char*>(&value), sizeof(value));
	}

	virtual void Deserialize(std::istream& in, Archetype* parameter) {
		in.read(reinterpret_cast<char*>(&value), sizeof(value));
		setDices(parameter);
	}
};

class IntSkill final : public Skill
{
public:
	IntSkill() {};
	explicit IntSkill(size_t new_value);
	
	void setDices(Archetype* parameter) override;

	void changeValue(int mod, Archetype* parameter) override;

	void operator=(int new_value);
};

class BrawnSkill final : public Skill
{
public:
	BrawnSkill() {};
	explicit BrawnSkill(size_t new_value);

	void setDices(Archetype* parameter) override;

	void changeValue(int mod, Archetype* parameter) override;

	void operator=(int new_value);
};

class CunningSkill final : public Skill
{
public:
	CunningSkill() {};
	explicit CunningSkill(size_t new_value);

	void setDices(Archetype* parameter) override;
	void changeValue(int mod, Archetype* parameter) override;

	void operator=(int new_value);
};

class AgilitySkill final : public Skill
{
public:
	AgilitySkill() {};
	explicit AgilitySkill(size_t new_value);

	void setDices(Archetype* parameter) override;
	void changeValue(int mod, Archetype* parameter) override;

	void operator=(int new_value);
};

class WillpowerSkill final : public Skill
{
public:
	WillpowerSkill() {};
	explicit WillpowerSkill(size_t new_value);

	void setDices(Archetype* parameter) override;

	void changeValue(int mod, Archetype* parameter) override;

	void operator=(int new_value);
};

class PresenceSkill final : public Skill
{
public:
	PresenceSkill() {};
	explicit PresenceSkill(size_t new_value);

	void setDices(Archetype* parameter) override;

	void changeValue(int mod, Archetype* parameter) override;
	void operator=(int new_value);
};