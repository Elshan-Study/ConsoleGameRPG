#pragma once
class Archetype final
{
private:
	size_t Brawn;
	size_t Agility;
	size_t Intellect;
	size_t Cunning;
	size_t Willpower;
	size_t Presence;
public:
	Archetype() : Brawn(0), Agility(0), Intellect(0), Cunning(0), Willpower(0), Presence(0) {};
	explicit Archetype(size_t brawn, size_t agility, size_t intellect, size_t cunning, size_t willpower, size_t presence)
	{
		Brawn = brawn;
		Agility = agility;
		Intellect = intellect;
		Cunning = cunning;
		Willpower = willpower;
		Presence = presence;
	};
	~Archetype() = default;

	size_t getBrawn() const { return Brawn; }
	size_t getAgility() const { return Agility; }
	size_t getIntellect() const { return Intellect; }
	size_t getCunning() const { return Cunning; }
	size_t getWillpower() const { return Willpower; }
	size_t getPresence() const { return Presence; }

	void changeBrawn(size_t value) { Brawn += value; }
	void changeAgility(size_t value) { Agility += value; }
	void changeIntellect(size_t value) { Intellect += value; }
	void changeCunning(size_t value) { Cunning += value; }
	void changeWillpower(size_t value) { Willpower += value; }
	void changePresence(size_t value) { Presence += value; }

};

