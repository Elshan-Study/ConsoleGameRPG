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
	Sturdy() : Archetype(3, 2, 2, 2, 1, 2) { setHP(); setAP(); }
	void setHP() override { HP = 12 + Brawn; }
	void setAP() override {	AP = 8 + Willpower; }

	void Serialize(std::ostream& out) const override {
		std::string type = "Sturdy";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
		out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
		out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
		out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
		out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
		out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
		out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
		out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
	}
};

class Genius final : public Archetype
{
public:
	Genius() : Archetype(2, 1, 3, 2, 2, 2) { setHP(); setAP(); }
	void setHP() override { HP = 8 + Brawn; }
	void setAP() override { AP = 12 + Willpower; }

	void Serialize(std::ostream& out) const override {
		std::string type = "Genius";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
		out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
		out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
		out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
		out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
		out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
		out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
		out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
	}
};

class Aristocrat final : public Archetype
{
public:
	Aristocrat() : Archetype(1, 2, 2, 2, 2, 3) { setHP(); setAP(); }
	void setHP() override { HP = 10 + Brawn; }
	void setAP() override { AP = 10 + Willpower; }

	void Serialize(std::ostream& out) const override {
		std::string type = "Aristocrat";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
		out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
		out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
		out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
		out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
		out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
		out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
		out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
	}
};

class Simpleton final : public Archetype
{
public:
	Simpleton() : Archetype(2, 2, 2, 2, 2, 2) { setHP(); setAP(); }
	void setHP() override { HP = 10 + Brawn; }
	void setAP() override { AP = 10 + Willpower; }

	void Serialize(std::ostream& out) const override {
		std::string type = "Simpleton";
		size_t len = type.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(type.c_str(), len);

		out.write(reinterpret_cast<const char*>(&Brawn), sizeof(Brawn));
		out.write(reinterpret_cast<const char*>(&Agility), sizeof(Agility));
		out.write(reinterpret_cast<const char*>(&Intellect), sizeof(Intellect));
		out.write(reinterpret_cast<const char*>(&Cunning), sizeof(Cunning));
		out.write(reinterpret_cast<const char*>(&Willpower), sizeof(Willpower));
		out.write(reinterpret_cast<const char*>(&Presence), sizeof(Presence));
		out.write(reinterpret_cast<const char*>(&HP), sizeof(HP));
		out.write(reinterpret_cast<const char*>(&AP), sizeof(AP));
	}
};

std::unique_ptr<Archetype> DeserializeArchetype(std::istream& in);