#pragma once
#include "Character.h"
class Interface
{
public:
	Interface() {};
	virtual ~Interface() {};
};

class PCCharacterCreate final : public Interface
{
public:

	void initialize(Character& PC)
	{
		PC.archetype = std::make_unique<Aristocrat>();
		PC.specialization = std::make_unique<Craftsman>();
		std::cout << "Character create MENU: \n";
	};

};