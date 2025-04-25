#include "Skill.h"

Skill::Skill() : value(0), dices(0) {};
Skill::Skill(size_t new_value) : value(new_value), dices(0) {};

size_t Skill::getDices() const { return dices; }
size_t Skill::getValue() const { return value; }

void Skill::operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
void Skill::operator+=(size_t mod) { dices += mod; value += mod; }
void Skill::operator-=(size_t mod) { dices -= mod; value -= mod; }

IntSkill::IntSkill(size_t new_value) : Skill(new_value) {};
void IntSkill::setDices(Archetype* parameter) 
{
	dices = value + parameter->Intellect;
}
void IntSkill::changeValue(int mod, Archetype* parameter) 
{
	value += mod;
	setDices(parameter);
}
void IntSkill::operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }

BrawnSkill::BrawnSkill(size_t new_value) : Skill(new_value) {};
void BrawnSkill::setDices(Archetype* parameter)
{
	dices = value + parameter->Brawn;
}
void BrawnSkill::changeValue(int mod, Archetype* parameter) 
{
	value += mod;
	setDices(parameter);
}
void BrawnSkill::operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }

CunningSkill::CunningSkill(size_t new_value) : Skill(new_value) {};
void CunningSkill::setDices(Archetype* parameter) 
{
	dices = value + parameter->Cunning;
}
void CunningSkill::changeValue(int mod, Archetype* parameter)
{
	value += mod;
	setDices(parameter);
}
void CunningSkill::operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }

AgilitySkill::AgilitySkill(size_t new_value) : Skill(new_value) {};
void AgilitySkill::setDices(Archetype* parameter) 
{
	dices = value + parameter->Agility;
}
void AgilitySkill::changeValue(int mod, Archetype* parameter)
{
	value += mod;
	setDices(parameter);
}
void AgilitySkill::operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }

WillpowerSkill::WillpowerSkill(size_t new_value) : Skill(new_value) {};
void WillpowerSkill::setDices(Archetype* parameter) 
{
	dices = value + parameter->Willpower;
}
void WillpowerSkill::changeValue(int mod, Archetype* parameter) 
{
	value += mod;
	setDices(parameter);
}
void WillpowerSkill::operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }

PresenceSkill::PresenceSkill(size_t new_value) : Skill(new_value) {};
void PresenceSkill::setDices(Archetype* parameter) 
{
	dices = value + parameter->Presence;
}
void PresenceSkill::changeValue(int mod, Archetype* parameter) 
{
	value += mod;
	setDices(parameter);
}
void PresenceSkill::operator=(int new_value) { dices -= value; value = new_value; dices += new_value; }
