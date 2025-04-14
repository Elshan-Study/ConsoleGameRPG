#pragma once
#include <iostream>
#include "Character.h"
#include "Interface.h"
class Game
{
private:
	Character PC;
	PCCharacterCreate createPC;
public:
	Game() = default;
	~Game() = default;

	void Start()
	{
		createPC.initialize(PC);
		std::cout << "Character Create Sucessfully" << std::endl;
	}
};

