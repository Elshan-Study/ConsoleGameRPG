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
	Character EnemyCultist;
public:
	Game() = default;
	~Game() = default;

	void initLevel1()
	{
		std::string key1 = "011K";
		/*std::string key2 = "012K";
		std::string key3 = "021K";
		std::string key4 = "022K";
		std::string key5 = "031K";
		std::string key6 = "032K";*/

		QuestPointer Sewerage("Sewerage", "sewerage.txt", key1);
		/*QuestPointer BlackMarket("Black Market", "blackMarket.txt", key2);
		QuestPointer EvilSwamp("Evil Swamp", "evilSwamp.txt", key3);
		QuestPointer TrollEdge("Troll Edge", "trollEdge.txt", key4);
		QuestPointer DragonCaves("Dragon Caves", "dragonCaves.txt", key5);
		QuestPointer RoyalPeak("Royal Peak", "royalPeak.txt", key6);*/

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
		Sewerage.quest.addStage(std::move(stageSQ1)); /*0*/
		Sewerage.quest.addStage(std::move(stageSQ2)); /*1*/
		Sewerage.quest.addStage(std::move(stageSQ3)); /*2*/
		Sewerage.quest.addStage(std::move(stageSQ4)); /*3*/
		Sewerage.quest.addOption(std::move(optionSQ0)); /*0*/
		Sewerage.quest.linkStageToOption(0, 0);
		Sewerage.quest.linkStageToOption(1, 0);
		Sewerage.quest.linkStageToOption(2, 0);
		Sewerage.quest.linkStageToOption(3, 0);

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
		Sewerage.quest.addStage(std::move(stageSQ11)); /*4*/
		Sewerage.quest.addStage(std::move(stageSQ21)); /*5*/
		Sewerage.quest.addStage(std::move(stageSQ41)); /*6*/
		
		/*Option 1:*/
		std::unique_ptr<QuestStage> stageSQ111 = std::make_unique<skillCheckStage>(
			"Look at the symbols and try to recognize them (3 AP)", 111, 1111, 1, 2, PC, PC.perception());
		std::unique_ptr<QuestStage> stageSQ112 = std::make_unique<TextStage>(
			"Follow the tracks (2 AP)", 112, 1121, 2, PC);
		std::unique_ptr<OptionChoice> optionSQ1 = std::make_unique<OptionChoice>(2);
		Sewerage.quest.addStage(std::move(stageSQ111)); /*7*/
		Sewerage.quest.addStage(std::move(stageSQ112)); /*8*/
		Sewerage.quest.addOption(std::move(optionSQ1)); /*1*/
		Sewerage.quest.linkStageToOption(7, 1);
		Sewerage.quest.linkStageToOption(8, 1);

		/*Option 2:*/
		std::unique_ptr<QuestStage> stageSQ211 = std::make_unique<skillCheckStage>(
			"Perform an alchemical analysis on site (4 AP)", 211, 2111, 4, 2, PC, PC.alchemy());
		std::unique_ptr<Item> dangerSample = std::make_unique<QuestItem>("Danger Sample");
		std::unique_ptr<QuestStage> stageSQ212 = std::make_unique<giveItemStage>(
			"Save the sample and move on (1 AP)", 212, 0, 1, PC, std::move(dangerSample));
		std::unique_ptr<OptionChoice> optionSQ2 = std::make_unique<OptionChoice>(2);
		Sewerage.quest.addStage(std::move(stageSQ211)); /*9*/
		Sewerage.quest.addStage(std::move(stageSQ212)); /*10*/
		Sewerage.quest.addOption(std::move(optionSQ2)); /*2*/
		Sewerage.quest.linkStageToOption(9, 2);
		Sewerage.quest.linkStageToOption(10, 2);

		/*Option 3:*/
		std::unique_ptr<QuestStage> stageSQ31 = std::make_unique<skillCheckStage>(
			"Sneak silently in that direction (2 AP)", 31, 311, 2, 2, PC, PC.stealth());
		std::unique_ptr<QuestStage> stageSQ32 = std::make_unique<TextStage>(
			"Call - \"Is there anyone alive here ?\" (1 AP)", 32, 321, 1, PC);
		std::unique_ptr<OptionChoice> optionSQ3 = std::make_unique<OptionChoice>(2);
		Sewerage.quest.addStage(std::move(stageSQ31)); /*11*/
		Sewerage.quest.addStage(std::move(stageSQ32)); /*12*/
		Sewerage.quest.addOption(std::move(optionSQ3)); /*3*/
		Sewerage.quest.linkStageToOption(11, 3);
		Sewerage.quest.linkStageToOption(12, 3);

		/*Option 4:*/
		std::unique_ptr<QuestStage> stageSQ411 = std::make_unique<AttackStage>(
			"Attack First (3 AP)", 411, 4111, 3, 2, PC, EnemyCultist);
		std::unique_ptr<QuestStage> stageSQ412 = std::make_unique<skillCheckStage>(
			"Hide and watch (2 AP)", 412, 4121, 2, 2, PC, PC.stealth());
		std::unique_ptr<OptionChoice> optionSQ4 = std::make_unique<OptionChoice>(2);
		Sewerage.quest.addStage(std::move(stageSQ411)); /*13*/
		Sewerage.quest.addStage(std::move(stageSQ412)); /*14*/
		Sewerage.quest.addOption(std::move(optionSQ4)); /*4*/
		Sewerage.quest.linkStageToOption(13, 4);
		Sewerage.quest.linkStageToOption(14, 4);

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
		Sewerage.quest.addStage(std::move(stageSQ1111)); /*15*/
		Sewerage.quest.addStage(std::move(stageSQ1121)); /*16*/
		Sewerage.quest.addStage(std::move(stageSQ2111)); /*17*/
		Sewerage.quest.addStage(std::move(stageSQ311)); /*18*/
		Sewerage.quest.addStage(std::move(stageSQ321)); /*19*/
		Sewerage.quest.addStage(std::move(stageSQ4111)); /*20*/
		Sewerage.quest.addStage(std::move(stageSQ4121)); /*21*/

		/*Option 5:*/
		std::unique_ptr<QuestStage> stageSQ11211 = std::make_unique<skillCheckStage>(
			"Try to pick the lock (3 AP)", 11211, 112110, 3, 2, PC, PC.skullduggery());
		std::unique_ptr<OptionChoice> optionSQ5 = std::make_unique<OptionChoice>(2);
		std::unique_ptr<QuestStage> stageSQ11212 = std::make_unique<useQuestItemStage>(
			"Try using a Danger Sample (1 AP)", 11212, 112110, 1, PC, "Danger Sample");
		Sewerage.quest.addStage(std::move(stageSQ11211)); /*22*/
		Sewerage.quest.addStage(std::move(stageSQ11212)); /*23*/
		Sewerage.quest.addOption(std::move(optionSQ5)); /*5*/
		Sewerage.quest.linkStageToOption(22, 5);
		Sewerage.quest.linkStageToOption(23, 5);

		std::unique_ptr<QuestStage> stageSQ112110 = std::make_unique<TextStage>(
			"You open the door and enter the lab, attacking the cultist you caught off guard.",
			112110, 4111, 0, PC);
		Sewerage.quest.addStage(std::move(stageSQ112110)); /*24*/

		/*Endings:*/
		std::unique_ptr<QuestStage> stageSQ50 = std::make_unique<TextStage>(
			"You gather enough evidence to turn the case over to the city guard. The cult is exposed and the water contamination is stopped.",
			50, 0, 0, PC);
		std::unique_ptr<QuestStage> stageSQ60 = std::make_unique<TextStage>(
			"The city continues to suffer, and the disease slowly spreads. Perhaps you will return... when it is too late.",
			60, 0, 0, PC);
		std::unique_ptr<QuestStage> stageSQ70 = std::make_unique<TextStage>(
			"You bring the cultist's body and the contents of the lab upstairs. The people are grateful, but the fear of the underground secrets remains.",
			70, 0, 0, PC);
		Sewerage.quest.addStage(std::move(stageSQ50)); /*24*/
		Sewerage.quest.addStage(std::move(stageSQ60)); /*25*/
		Sewerage.quest.addStage(std::move(stageSQ70)); /*26*/
	}

	void initLevels()
	{
		initLevel1();
	}

	void start()
	{
		initLevels();
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

