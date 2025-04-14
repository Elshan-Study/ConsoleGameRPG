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
		std::cout << "Character create MENU: \n";
	};

};