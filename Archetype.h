#pragma once
class Archetype 
{
protected:
	size_t Brawn;
	size_t Agility;
	size_t Intellect;
	size_t Cunning;
	size_t Willpower;
	size_t Presence;
	size_t HP;
	size_t AP;
public:
	Archetype() : Brawn(0), Agility(0), Intellect(0), Cunning(0), Willpower(0), Presence(0), HP(0), AP(0) {};
	explicit Archetype(size_t brawn, size_t agility, size_t intellect, size_t cunning, size_t willpower, size_t presence) : HP(0), AP(0)
	{
		Brawn = brawn;
		Agility = agility;
		Intellect = intellect;
		Cunning = cunning;
		Willpower = willpower;
		Presence = presence;
	};
	virtual ~Archetype() = default;
	virtual void setHP() = 0;
	virtual void setAP() = 0;

	size_t getBrawn() const { return Brawn; }
	size_t getAgility() const { return Agility; }
	size_t getIntellect() const { return Intellect; }
	size_t getCunning() const { return Cunning; }
	size_t getWillpower() const { return Willpower; }
	size_t getPresence() const { return Presence; }

	void changeBrawn(int value) { Brawn += value; }
	void changeAgility(int value) { Agility += value; }
	void changeIntellect(int value) { Intellect += value; }
	void changeCunning(int value) { Cunning += value; }
	void changeWillpower(int value) { Willpower += value; }
	void changePresence(int value) { Presence += value; }

};

class Sturdy final : public Archetype
{
public:
	Sturdy() : Archetype(3, 2, 2, 2, 1, 2) { setHP(); setAP(); }
	void setHP() override { HP = 12 + Brawn; }
	void setAP() override { HP = 8 + Willpower; }
};

class Genius final : public Archetype
{
public:
	Genius() : Archetype(2, 1, 3, 2, 2, 2) { setHP(); setAP(); }
	void setHP() override { HP = 8 + Brawn; }
	void setAP() override { HP = 12 + Willpower; }
};

class Aristocrat final : public Archetype
{
public:
	Aristocrat() : Archetype(1, 2, 2, 2, 2, 3) { setHP(); setAP(); }
	void setHP() override { HP = 10 + Brawn; }
	void setAP() override { HP = 10 + Willpower; }
};

class Simpleton final : public Archetype
{
public:
	Simpleton() : Archetype(2, 2, 2, 2, 2, 2) { setHP(); setAP(); }
	void setHP() override { HP = 10 + Brawn; }
	void setAP() override { HP = 10 + Willpower; }
};