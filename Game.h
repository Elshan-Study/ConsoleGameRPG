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
	MainMenu menu;
	Map CapitalCity;
	Map EvilSwamp;
	Map BlackMountain;
public:
	Game() = default;
	~Game() = default;

	void Start()
	{
		int choice = menu.Show();

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (1)
		{
		case 1:
			createPC.initialize(PC);
			std::cout << "Character Create Successfully" << std::endl;
			break;
		default:
			break;
		}
	}
};

