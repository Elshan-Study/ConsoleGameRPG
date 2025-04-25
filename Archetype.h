#pragma once
#include <iostream>
#include <fstream>
class Archetype 
{
protected:
	size_t HP;
	size_t AP;
public:
	size_t Brawn;
	size_t Agility;
	size_t Intellect;
	size_t Cunning;
	size_t Willpower;
	size_t Presence;

	Archetype();
	explicit Archetype(size_t brawn, size_t agility, size_t intellect, size_t cunning, size_t willpower, size_t presence);
	virtual ~Archetype() = default;
	virtual void setHP() = 0;
	virtual void setAP() = 0;
	size_t getHP() const { return HP; };
	size_t getAP() const { return AP; };
	void changeHP(int mod) { HP += mod; }; 
	void changeAP(int mod) { AP += mod; };

	virtual void Serialize(std::ostream& out) const = 0;
	friend std::unique_ptr<Archetype> DeserializeArchetype(std::istream& in);

};

class Sturdy final : public Archetype
{
public:
	Sturdy();
	void setHP() override { HP = 12 + Brawn; }
	void setAP() override {	AP = 8 + Willpower; }

	void Serialize(std::ostream& out) const override;
};

class Genius final : public Archetype
{
public:
	Genius();
	void setHP() override { HP = 8 + Brawn; }
	void setAP() override { AP = 12 + Willpower; }

	void Serialize(std::ostream& out) const override;
};

class Aristocrat final : public Archetype
{
public:
	Aristocrat();
	void setHP() override { HP = 10 + Brawn; }
	void setAP() override { AP = 10 + Willpower; }

	void Serialize(std::ostream& out) const override;
};

class Simpleton final : public Archetype
{
public:
	Simpleton();
	void setHP() override { HP = 10 + Brawn; }
	void setAP() override { AP = 10 + Willpower; }

	void Serialize(std::ostream& out) const override;
};

std::unique_ptr<Archetype> DeserializeArchetype(std::istream& in);