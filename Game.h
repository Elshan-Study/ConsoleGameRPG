#pragma once
#include <iostream>
#include "Character.h"
#include "Interface.h"
#include "Location.h"
class Game
{
private:
	Character PC;
	PCCharacterCreate createPC;
	Map CapitalCity;
	Map EvilSwamp;
	Map BlackMountain;
public:
	Game() = default;
	~Game() = default;

	void Start()
	{
		MainMenu menu;
		int choice = menu.Show();

		switch (choice)
		{
		case 1:
			createPC.initialize(PC);
			std::cout << "Character Create Successfully" << std::endl;
		default:
			break;
		}
	}
};

