#pragma once
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

	Archetype() : Brawn(1), Agility(1), Intellect(1), Cunning(1), Willpower(1), Presence(1), HP(1), AP(1) {};
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
	virtual void setHP() {};
	virtual void setAP() {};
	size_t getHP() const { return HP; };
	size_t getAP() const { return AP; };
	void changeHP(int mod) { HP += mod; }; /*!Need exceptions: if mod > value */
	void changeAP(int mod) { AP += mod; }; /*!Need exceptions: if mod > value */
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