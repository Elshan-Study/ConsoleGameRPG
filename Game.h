#pragma once
#include <iostream>
#include "Character.h"
#include "Interface.h"
#include "Location.h"
#include "Quest.h"
class Game
{
private:
	const size_t QUESTCOUNT = 3;
	Character PC;
	PCCharacterCreate createPC;
	MainMenu menu;
	InsideGameMenu menu2;
	Map CapitalCity;
	Map EvilSwamp;
	Map BlackMountain;
	size_t winCount;
	size_t defeatCount;
public:
	Game() = default;
	~Game() = default;

	/*QuestPointer EvilSwamp("Evil Swamp", "evilSwamp.txt", key2);
		QuestPointer DragonCaves("Dragon Caves", "dragonCaves.txt", key3);*/

	std::string key1 = "011K";
	std::string key2 = "021K";
	std::string key3 = "031K";

	Character EnemyCultist;

	void initLevel1()
	{
		std::unique_ptr<Location> Sewerage = std::make_unique<QuestPointer>("Sewerage", "sewerage.txt", key1);
		QuestPointer* rawPtr = dynamic_cast<QuestPointer*>(Sewerage.get());

		/*Base thread:*/
		std::unique_ptr<QuestStage> stageSQ1 = std::make_unique<useQuestItemStage>(
			"Explore the nearest tunnel with Torch (2 AP)", 10, 11, 2, PC, "Torch");
		std::unique_ptr<QuestStage> stageSQ2 = std::make_unique<skillCheckStage>(
			"Check water for impurities or mucus (3 AP)", 20, 21, 3, 2, PC, PC.alchemy());
		std::unique_ptr<QuestStage> stageSQ3 = std::make_unique<skillCheckStage>(
			"Listen to the tunnels to see if they make any strange sounds (1 AP)", 30, 3, 1, 1, PC, PC.resilience());
		std::unique_ptr<QuestStage> stageSQ4 = std::make_unique<TextStage>(
			"Go straight ahead towards the grinding (5 AP)", 40, 41, 5, PC);
		std::unique_ptr<OptionChoice> optionSQ0 = std::make_unique<OptionChoice>(4);
		rawPtr->quest.addStage(std::move(stageSQ1)); /*0*/
		rawPtr->quest.addStage(std::move(stageSQ2)); /*1*/
		rawPtr->quest.addStage(std::move(stageSQ3)); /*2*/
		rawPtr->quest.addStage(std::move(stageSQ4)); /*3*/
		rawPtr->quest.addOption(std::move(optionSQ0)); /*0*/
		rawPtr->quest.linkStageToOption(0, 0);
		rawPtr->quest.linkStageToOption(1, 0);
		rawPtr->quest.linkStageToOption(2, 0);
		rawPtr->quest.linkStageToOption(3, 0);

		/*Thread 2:*/
		std::unique_ptr<QuestStage> stageSQ11 = std::make_unique<TextStage>(
			"You light a torch. The light casts ominous shadows. There are symbols on the walls that look like alchemy. There are charred marks on the floor.", 
			11, 1, 0, PC);
		std::unique_ptr<QuestStage> stageSQ21 = std::make_unique<TextStage>(
			"You take a water sample and notice strange purple fibers in it.Something is clearly unnatural.",
			21, 2, 0, PC);
		std::unique_ptr<QuestStage> stageSQ41 = std::make_unique<TextStage>(
			"You rush forward and find yourself in a lab hidden deep in the sewers. Flasks are boiling, bodies are mutilated in tanks, and someone in a hood turns to you...",
			41, 4, 0, PC);
		rawPtr->quest.addStage(std::move(stageSQ11)); /*4*/
		rawPtr->quest.addStage(std::move(stageSQ21)); /*5*/
		rawPtr->quest.addStage(std::move(stageSQ41)); /*6*/
		
		/*Option 1:*/
		std::unique_ptr<QuestStage> stageSQ111 = std::make_unique<skillCheckStage>(
			"Look at the symbols and try to recognize them (3 AP)", 111, 1111, 1, 2, PC, PC.perception());
		std::unique_ptr<QuestStage> stageSQ112 = std::make_unique<TextStage>(
			"Follow the tracks (2 AP)", 112, 1121, 2, PC);
		std::unique_ptr<OptionChoice> optionSQ1 = std::make_unique<OptionChoice>(2);
		rawPtr->quest.addStage(std::move(stageSQ111)); /*7*/
		rawPtr->quest.addStage(std::move(stageSQ112)); /*8*/
		rawPtr->quest.addOption(std::move(optionSQ1)); /*1*/
		rawPtr->quest.linkStageToOption(7, 1);
		rawPtr->quest.linkStageToOption(8, 1);

		/*Option 2:*/
		std::unique_ptr<QuestStage> stageSQ211 = std::make_unique<skillCheckStage>(
			"Perform an alchemical analysis on site (4 AP)", 211, 2111, 4, 2, PC, PC.alchemy());
		std::unique_ptr<Item> dangerSample = std::make_unique<QuestItem>("Danger Sample");
		std::unique_ptr<QuestStage> stageSQ212 = std::make_unique<giveItemStage>(
			"Save the sample and move on (1 AP)", 212, 0, 1, PC, std::move(dangerSample));
		std::unique_ptr<OptionChoice> optionSQ2 = std::make_unique<OptionChoice>(2);
		rawPtr->quest.addStage(std::move(stageSQ211)); /*9*/
		rawPtr->quest.addStage(std::move(stageSQ212)); /*10*/
		rawPtr->quest.addOption(std::move(optionSQ2)); /*2*/
		rawPtr->quest.linkStageToOption(9, 2);
		rawPtr->quest.linkStageToOption(10, 2);

		/*Option 3:*/
		std::unique_ptr<QuestStage> stageSQ31 = std::make_unique<skillCheckStage>(
			"Sneak silently in that direction (2 AP)", 31, 311, 2, 2, PC, PC.stealth());
		std::unique_ptr<QuestStage> stageSQ32 = std::make_unique<TextStage>(
			"Call - \"Is there anyone alive here ?\" (1 AP)", 32, 321, 1, PC);
		std::unique_ptr<OptionChoice> optionSQ3 = std::make_unique<OptionChoice>(2);
		rawPtr->quest.addStage(std::move(stageSQ31)); /*11*/
		rawPtr->quest.addStage(std::move(stageSQ32)); /*12*/
		rawPtr->quest.addOption(std::move(optionSQ3)); /*3*/
		rawPtr->quest.linkStageToOption(11, 3);
		rawPtr->quest.linkStageToOption(12, 3);

		/*Option 4:*/
		std::unique_ptr<QuestStage> stageSQ411 = std::make_unique<AttackStage>(
			"Attack First (3 AP)", 411, 4111, 3, 2, PC, EnemyCultist);
		std::unique_ptr<QuestStage> stageSQ412 = std::make_unique<skillCheckStage>(
			"Hide and watch (2 AP)", 412, 4121, 2, 2, PC, PC.stealth());
		std::unique_ptr<OptionChoice> optionSQ4 = std::make_unique<OptionChoice>(2);
		rawPtr->quest.addStage(std::move(stageSQ411)); /*13*/
		rawPtr->quest.addStage(std::move(stageSQ412)); /*14*/
		rawPtr->quest.addOption(std::move(optionSQ4)); /*4*/
		rawPtr->quest.linkStageToOption(13, 4);
		rawPtr->quest.linkStageToOption(14, 4);

		/*Thread 3:*/
		std::unique_ptr<QuestStage> stageSQ1111 = std::make_unique<TextStage>(
			"You determine that these are marks from an ancient alchemical book - someone is performing rituals here.Perhaps this is the source of the disease.",
			1111, 50, 0, PC);
		std::unique_ptr<QuestStage> stageSQ1121 = std::make_unique<TextStage>(
			"The tracks lead to a door with a slime-covered lock. It's clearly magical.",
			1121, 5, 0, PC);
		std::unique_ptr<QuestStage> stageSQ2111 = std::make_unique<TextStage>(
			"You determine that the water is contaminated with a mutagenic substance used in forbidden transformation rituals. It is dangerous.",
			2111, 50, 0, PC);
		std::unique_ptr<QuestStage> stageSQ311 = std::make_unique<TextStage>(
			"You see a figure, a haggard sewer worker, chained up.He whispers of \"The Eye That Stares Out of the Slime.\"",
			311, 0, 0, PC);
		std::unique_ptr<QuestStage> stageSQ321 = std::make_unique<TextStage>(
			"The scream echoes - and you hear a splash, as if someone is running away. Perhaps you scared someone.",
			321, 60, 0, PC);
		std::unique_ptr<QuestStage> stageSQ4111 = std::make_unique<TextStage>(
			"You engage in combat with an alchemist cultist. The battle is intense, but victory gives you evidence and ingredients for an antidote.",
			4111, 70, 0, PC);
		std::unique_ptr<QuestStage> stageSQ4121 = std::make_unique<TextStage>(
			"You overhear a conversation about supplies from the city pharmacy. Perhaps someone higher up is involved.",
			4121, 50, 0, PC);
		rawPtr->quest.addStage(std::move(stageSQ1111)); /*15*/
		rawPtr->quest.addStage(std::move(stageSQ1121)); /*16*/
		rawPtr->quest.addStage(std::move(stageSQ2111)); /*17*/
		rawPtr->quest.addStage(std::move(stageSQ311)); /*18*/
		rawPtr->quest.addStage(std::move(stageSQ321)); /*19*/
		rawPtr->quest.addStage(std::move(stageSQ4111)); /*20*/
		rawPtr->quest.addStage(std::move(stageSQ4121)); /*21*/

		/*Option 5:*/
		std::unique_ptr<QuestStage> stageSQ11211 = std::make_unique<skillCheckStage>(
			"Try to pick the lock (3 AP)", 11211, 112110, 3, 2, PC, PC.skullduggery());
		std::unique_ptr<OptionChoice> optionSQ5 = std::make_unique<OptionChoice>(2);
		std::unique_ptr<QuestStage> stageSQ11212 = std::make_unique<useQuestItemStage>(
			"Try using a Danger Sample (1 AP)", 11212, 112110, 1, PC, "Danger Sample");
		rawPtr->quest.addStage(std::move(stageSQ11211)); /*22*/
		rawPtr->quest.addStage(std::move(stageSQ11212)); /*23*/
		rawPtr->quest.addOption(std::move(optionSQ5)); /*5*/
		rawPtr->quest.linkStageToOption(22, 5);
		rawPtr->quest.linkStageToOption(23, 5);

		std::unique_ptr<QuestStage> stageSQ112110 = std::make_unique<TextStage>(
			"You open the door and enter the lab, attacking the cultist you caught off guard.",
			112110, 4111, 0, PC);
		rawPtr->quest.addStage(std::move(stageSQ112110)); /*24*/

		/*Endings:*/
		std::unique_ptr<QuestStage> stageSQ50 = std::make_unique<TextStage>(
			"You gather enough evidence to turn the case over to the city guard. The cult is exposed and the water contamination is stopped.",
			50, 50, 0, PC);
		std::unique_ptr<QuestStage> stageSQ60 = std::make_unique<TextStage>(
			"The city continues to suffer, and the disease slowly spreads. Perhaps you will return... when it is too late.",
			60, 60, 0, PC);
		std::unique_ptr<QuestStage> stageSQ70 = std::make_unique<TextStage>(
			"You bring the cultist's body and the contents of the lab upstairs. The people are grateful, but the fear of the underground secrets remains.",
			70, 70, 0, PC);
		rawPtr->quest.addStage(std::move(stageSQ50)); /*24*/
		rawPtr->quest.addStage(std::move(stageSQ60)); /*25*/
		rawPtr->quest.addStage(std::move(stageSQ70)); /*26*/

		CapitalCity.addLocation(std::move(Sewerage));
	}

	void initLevel2()
	{
		std::unique_ptr<Location> GuardBarracks = std::make_unique<QuestGetPointer>("GuardBarracks", "quardBarracks.txt", key1);
		QuestGetPointer* rawPtr = dynamic_cast<QuestGetPointer*>(GuardBarracks.get());

		/*Base*/
		std::unique_ptr<QuestStage> stageGB10 = std::make_unique<TextStage>(
			"Guard: Are you here about the mission? I hope you're not one of those hoping for easy money. Because the sewers aren't just dirt. They're... worse.",
			10, 0, 0, PC);
		std::unique_ptr<QuestStage> stageGB30 = std::make_unique<TextStage>(
			"Guard: We are waiting for you to take action.",
			30, 30, 0, PC);
		std::unique_ptr<QuestStage> stageGB40 = std::make_unique<TextStage>(
			"Guard: You let us down!",
			40, 40, 0, PC);
		std::unique_ptr<QuestStage> stageGB50 = std::make_unique<TextStage>(
			"Guard: Look, a real hero!",
			50, 50, 0, PC);
		rawPtr->quest.addStage(std::move(stageGB10)); /*0*/
		rawPtr->quest.addStage(std::move(stageGB30)); /*1*/
		rawPtr->quest.addStage(std::move(stageGB40)); /*2*/
		rawPtr->quest.addStage(std::move(stageGB50)); /*3*/
		
		/*Option*/
		std::unique_ptr<QuestStage> stageGB11 = std::make_unique<TextStage>(
			"I heard that someone there is sick. I want to find out.",
			11, 20, 0, PC);
		std::unique_ptr<QuestStage> stageGB12 = std::make_unique<TextStage>(
			"Money is not the main thing. I'm looking for where my skills will be useful.",
			12, 20, 0, PC);
		std::unique_ptr<QuestStage> stageGB13 = std::make_unique<TextStage>(
			"The sooner I get down there, the sooner you can sleep peacefully again.",
			13, 20, 0, PC);
		std::unique_ptr<QuestStage> stageGB14 = std::make_unique<TextStage>(
			"[Nod silently]",
			14, 20, 0, PC);
		std::unique_ptr<OptionChoice> optionGB0 = std::make_unique<OptionChoice>(4);
		rawPtr->quest.addStage(std::move(stageGB11)); /*4*/
		rawPtr->quest.addStage(std::move(stageGB12)); /*5*/
		rawPtr->quest.addStage(std::move(stageGB13)); /*6*/
		rawPtr->quest.addStage(std::move(stageGB14)); /*7*/
		rawPtr->quest.addOption(std::move(optionGB0));
		rawPtr->quest.linkStageToOption(4, 0);
		rawPtr->quest.linkStageToOption(5, 0);
		rawPtr->quest.linkStageToOption(6, 0);
		rawPtr->quest.linkStageToOption(7, 0);

		/*Quest Stage*/
		std::unique_ptr<QuestStage> stageGB20 = std::make_unique<TextStage>(
			"Guard: He snorts, not looking up. Okay. We're short-handed anyway.\n"
			"People are disappearing. The water is getting murky. None of my men will go there - they say,\n"
			"there's someone watching from below.\n" 
			"He rummages under the table, takes out a burnt torch.", 
			20, 21, 0, PC);
		std::unique_ptr<QuestStage> stageGB21 = std::make_unique<TextStage>(
			"[You receive: Torch]\n"
			"[New Quest : Sewerage Quest]",
			21, 22, 0, PC);
		std::unique_ptr<QuestStage> stageGB22 = std::make_unique<TextStage>(
			"Guard: The entrance to the tunnels is behind the market, under a hatch with the mark of an old guild sign.",
			22, 22, 0, PC);
		rawPtr->quest.addStage(std::move(stageGB20)); /*8*/
		rawPtr->quest.addStage(std::move(stageGB21)); /*9*/
		rawPtr->quest.addStage(std::move(stageGB22)); /*10*/

		CapitalCity.addLocation(std::move(GuardBarracks));
	}

	void initLevels()
	{
		initLevel1();
		initLevel2();
	}

	void gamePlay(size_t choice)
	{
		if (choice == 1)
		{
			if (PC.currentAP == PC.archetype->getAP())
			{
				std::cout << "AP is full!\n";
				return;
			}
			if (PC.skillCheck(PC.discipline(), 2))
			{
				PC.recoverAP();
				size_t mod = 5 - PC.Discipline();
				PC.currentAP -= mod;
				std::cout << "Some AP recovered\n";
			}
		}
		else if (choice == 2)
		{
			if (PC.currentHP == PC.archetype->getHP()) 
			{ 
				std::cout << "HP is full!\n";
				return; 
			}
			if (PC.skillCheck(PC.resilience(), 2))
			{
				PC.recoverHP();
				size_t mod = 5 - PC.Resilience();
				PC.currentHP -= mod;
				std::cout << "Some HP recovered\n";
			}
		}
		else if (choice == 3)
		{
			static_cast<char>(choice);
			CapitalCity.readDescription();
			std::cout << std::endl;
			MapMenu newMenu;
			choice = newMenu.show(CapitalCity);

			return;
		}
	}

	void start()
	{
		while (true)
		{
			CapitalCity.setMain("Capital City", "capitalCity.txt");
			initLevels();
			char choice = menu.show();

			switch (choice - 48)
			{
			case 1:
				createPC.initialize(PC);
				std::cout << "Character Create Successfully" << std::endl;
				choice = menu2.show();
				if (choice - 48 != 6)
				{
					gamePlay(choice - 48);
				}
				break;
			case 2:
				PC.printInfo();
				choice = menu2.show();
				if (choice - 48 != 6)
				{
					gamePlay(choice - 48);
				}
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				return;
			default:
				break;
			}
		}
	}
};

