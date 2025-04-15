#pragma once
#include <iostream>
#include "Character.h"
#include "Interface.h"
#include "Location.h"
#include "Quest.h"
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

	void initLevels()
	{
		std::string key1 = "011K";
		std::string key2 = "012K";
		std::string key3 = "021K";
		std::string key4 = "022K";
		std::string key5 = "031K";
		std::string key6 = "032K";

		QuestPointer Sewerage("Sewerage", "sewerage.txt", key1);
		QuestPointer BlackMarket("Black Market", "blackMarket.txt", key2);
		QuestPointer EvilSwamp("Evil Swamp", "evilSwamp.txt", key3);
		QuestPointer TrollEdge("Troll Edge", "trollEdge.txt", key4);
		QuestPointer DragonCaves("Dragon Caves", "dragonCaves.txt", key5);
		QuestPointer RoyalPeak("Royal Peak", "royalPeak.txt", key6);

		/*------------------SewerageQuest-----------------------*/
		
		std::unique_ptr<QuestStage> stageSQ1 = std::make_unique<useQuestItemStage>(
			"Explore the nearest tunnel", 10, 11, 2, 4, PC, "Torch");

	}

	void start()
	{
		char choice = menu.show();

		switch (choice-48)
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

