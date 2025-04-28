#include "Game.h"

void Game::addKey(std::string key)
{
	keys[keySize++] = key;
}

void Game::addEnemy(Character&& enemy)
{
	enemies[enemySize++] = std::move(enemy);
}

void Game::reset()
{
	keySize = 0;
	enemySize = 0;
	winCount = 0;
	defeatCount = 0;

	for (size_t i = 0; i < QUESTCOUNT; ++i)
	{
		keys[i].clear();
	}

	for (size_t i = 0; i < ENEMYCOUNT; ++i)
	{
		enemies[i] = Character();
	}

	PC = Character();


	CapitalCity = Map();
	Outskirts = Map();
	BlackMountain = Map();
}

void Game::initMaps()
{
	CapitalCity.setMain("Capital City", "capitalCity.txt");
	Outskirts.setMain("Outskirts", "outskirts.txt");
	BlackMountain.setMain("BlackMountain", "blackMountain.txt");
}

void Game::initLevel10()
{
	std::unique_ptr<Location> GuardBarracks = std::make_unique<QuestGetPointer>("Guard Barracks", "quardBarracks.txt", key1);
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
	std::unique_ptr<Item> Torch = std::make_unique<QuestItem>("Torch");
	std::unique_ptr<QuestStage> stageGB21 = std::make_unique<giveItemStage>(
		"[You receive: Torch]\n"
		"[New Quest : Sewerage Quest]",
		21, 22, 0, PC, std::move(Torch));
	std::unique_ptr<QuestStage> stageGB22 = std::make_unique<TextStage>(
		"Guard: The entrance to the tunnels is behind the market, under a hatch with the mark of an old guild sign.",
		22, 22, 0, PC);
	rawPtr->quest.addStage(std::move(stageGB20)); /*8*/
	rawPtr->quest.addStage(std::move(stageGB21)); /*9*/
	rawPtr->quest.addStage(std::move(stageGB22)); /*10*/

	CapitalCity.addLocation(std::move(GuardBarracks));
}

void Game::initLevel11()
{
	std::unique_ptr<Location> Sewerage = std::make_unique<QuestPointer>("Sewerage", "sewerage.txt", key1);
	QuestPointer* rawPtr = dynamic_cast<QuestPointer*>(Sewerage.get());

	/*Base thread:*/
	std::unique_ptr<QuestStage> stageSQ1 = std::make_unique<useQuestItemStage>(
		"Explore the nearest tunnel with Torch", 10, 11, PC, "Torch");
	std::unique_ptr<QuestStage> stageSQ2 = std::make_unique<skillCheckStage>(
		"Check water for impurities or mucus (3 AP)", 20, 21, 999, 3, 2, PC, PC.alchemy());
	std::unique_ptr<QuestStage> stageSQ3 = std::make_unique<skillCheckStage>(
		"Listen to the tunnels to see if they make any strange sounds (1 AP)", 30, 3, 999, 1, 1, PC, PC.resilience());
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
		"Look at the symbols and try to recognize them (3 AP)", 111, 1111, 999, 3, 2, PC, PC.perception());
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
		"Perform an alchemical analysis on site (4 AP)", 211, 2111, 999, 4, 2, PC, PC.alchemy());
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
		"Sneak silently in that direction (2 AP)", 31, 311, 411, 2, 2, PC, PC.stealth());
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
		"Attack First (3 AP)", 411, 4111, 3, 2, PC);
	std::unique_ptr<QuestStage> stageSQ412 = std::make_unique<skillCheckStage>(
		"Hide and watch (2 AP)", 412, 4121, 411, 2, 2, PC, PC.stealth());
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
		4111, 50, 0, PC);
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
		"Try to pick the lock (3 AP)", 11211, 112110, 0, 3, 2, PC, PC.skullduggery());
	std::unique_ptr<OptionChoice> optionSQ5 = std::make_unique<OptionChoice>(2);
	std::unique_ptr<QuestStage> stageSQ11212 = std::make_unique<useQuestItemStage>(
		"Try using a Danger Sample", 11212, 112110, PC, "Danger Sample");
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
	std::unique_ptr<QuestStage> stageSQ0 = std::make_unique<TextStage>(
		"The cool air smells of mold, moisture runs down the walls. Somewhere ahead, you hear a strange metallic grinding sound...", 999, 0, 0, PC);
	rawPtr->quest.addStage(std::move(stageSQ50)); /*24*/
	rawPtr->quest.addStage(std::move(stageSQ60)); /*25*/
	rawPtr->quest.addStage(std::move(stageSQ0));

	rawPtr->quest.setReward(100);
	CapitalCity.addLocation(std::move(Sewerage));
}

void Game::initLevel20() 
{
	std::unique_ptr<Location> AlchemistHut = std::make_unique<QuestGetPointer>("Alchemist Hut", "alchemistHut.txt", key2);
	QuestGetPointer* rawPtr = dynamic_cast<QuestGetPointer*>(AlchemistHut.get());

	/*Base*/
	std::unique_ptr<QuestStage> stage10 = std::make_unique<TextStage>(
		"Alchemist: When you enter, he doesn't even raise his head:\ndid you come here, traveler? The swamps don't like extra eyes.",
		10, 0, 0, PC);
	std::unique_ptr<QuestStage> stage30 = std::make_unique<TextStage>(
		"Alchemist: Oh, you're back already? What? You haven't completed the task yet? When you do, then we'll talk.",
		30, 2, 0, PC);
	std::unique_ptr<QuestStage> stage40 = std::make_unique<TextStage>(
		"Alchemist: You have no business here!!",
		40, 40, 0, PC);
	std::unique_ptr<QuestStage> stage50 = std::make_unique<TextStage>(
		"Alchemist: Come in, come in, there are new products for you!",
		50, 2, 0, PC);
	rawPtr->quest.addStage(std::move(stage10)); /*0*/
	rawPtr->quest.addStage(std::move(stage30)); /*1*/
	rawPtr->quest.addStage(std::move(stage40)); /*2*/
	rawPtr->quest.addStage(std::move(stage50)); /*3*/

	/*Main Option*/
	std::unique_ptr<QuestStage> stage11 = std::make_unique<TextStage>(
		"Looking for adventure.I heard there are dangerous places here.",
		11, 111, 0, PC);
	std::unique_ptr<QuestStage> stage12 = std::make_unique<TextStage>(
		"I'm lost. Can you tell me the way?",
		12, 121, 0, PC);
	std::unique_ptr<QuestStage> stage13 = std::make_unique<TextStage>(
		"Do you know who kidnaps people in these parts?",
		13, 131, 0, PC);
	std::unique_ptr<QuestStage> stage14 = std::make_unique<TextStage>(
		"I heard you have some useful stuff to buy...",
		14, 141, 0, PC);
	std::unique_ptr<QuestStage> stage15 = std::make_unique<skillCheckStage>(
		"Treat me please! (2 AP)",
		15, 151, 152, 2, 2, PC, PC.charm());
	std::unique_ptr<OptionChoice> option0 = std::make_unique<OptionChoice>(5);
	rawPtr->quest.addStage(std::move(stage11)); /*4*/
	rawPtr->quest.addStage(std::move(stage12)); /*5*/
	rawPtr->quest.addStage(std::move(stage13)); /*6*/
	rawPtr->quest.addStage(std::move(stage14)); /*7*/
	rawPtr->quest.addStage(std::move(stage15)); /*8*/
	rawPtr->quest.addOption(std::move(option0));
	rawPtr->quest.linkStageToOption(4, 0);
	rawPtr->quest.linkStageToOption(5, 0);
	rawPtr->quest.linkStageToOption(6, 0);
	rawPtr->quest.linkStageToOption(7, 0);
	rawPtr->quest.linkStageToOption(8, 0);

	/*Quest Stage*/
	std::unique_ptr<QuestStage> stage111 = std::make_unique<TextStage>(
		"The alchemist grins with one edge of his dry lips:\n"
		"Adventures, you say? Ha! There's enough of them here until your bones become softer than swamp mud."
		"I have a deal.If you want to risk your skin, listen carefully.",
		111, 20, 0, PC);
	std::unique_ptr<QuestStage> stage121 = std::make_unique<TextStage>(
		"The alchemist shakes his head:\n"
		"In these parts there is only one road - to the quagmire and the unmarked grave."
		"But if you still want to live - I can show you the way. But there will be a price for you: risk and stench.",
		121, 20, 0, PC);
	std::unique_ptr<QuestStage> stage131 = std::make_unique<TextStage>(
		"The alchemist becomes serious for a moment:\n"
		"What lurks in the fog does not call by name. The swamp itself takes its own."
		"But there is a place there... the rotting heart of this land. If you want to know more, go there.",
		131, 20, 0, PC);
	std::unique_ptr<QuestStage> stage20 = std::make_unique<TextStage>(
		"Alchemist: There is a place in the swamps where even rottenness does not willingly go. Ancient muck has awakened there...\n"
		"If you remove the artifact \"Heart of the Swamps\", it will cease to live.\n"
		"If you really want to test yourself - go there. But keep in mind: not everyone returns.",
		20, 21, 0, PC);
	std::unique_ptr<QuestStage> stage21 = std::make_unique<TextStage>(
		"[New Quest : Evil Swamp Quest]",
		21, 21, 0, PC);
	rawPtr->quest.addStage(std::move(stage111)); /*9*/
	rawPtr->quest.addStage(std::move(stage121)); /*10*/
	rawPtr->quest.addStage(std::move(stage131)); /*11*/
	rawPtr->quest.addStage(std::move(stage20)); /*12*/
	rawPtr->quest.addStage(std::move(stage21)); /*13*/

	/*Merchant line*/
	std::unique_ptr<QuestStage> stage141 = std::make_unique<TextStage>(
		"The alchemist grins: Yeah, you can... But everything has its price.",
		141, 1, 0, PC);
	rawPtr->quest.addStage(std::move(stage141)); /*14*/

	std::unique_ptr<QuestStage> stage1411 = std::make_unique<skillCheckStage>(
		"Bargain for a Healing Potion (2 AP)",
		1411, 14111, 14112, 2, 2, PC, PC.negotiation());
	std::unique_ptr<QuestStage> stage1412 = std::make_unique<skillCheckStage>(
		"Bargain for a Poison (2 AP)",
		1412, 14121, 14122, 2, 2, PC, PC.negotiation()); 
	std::unique_ptr<OptionChoice> option1 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addStage(std::move(stage1411)); /*15*/
	rawPtr->quest.addStage(std::move(stage1412)); /*16*/
	rawPtr->quest.addOption(std::move(option1));
	rawPtr->quest.linkStageToOption(15, 1);
	rawPtr->quest.linkStageToOption(16, 1);

	std::unique_ptr<Item> healPotion = std::make_unique<Potion>("Heal potion", 5);
	std::unique_ptr<Item> healPotion2 = std::make_unique<Potion>("Heal potion", 5);
	std::unique_ptr<Item> poison = std::make_unique<Potion>("Poison", 5);
	std::unique_ptr<Item> poison2 = std::make_unique<Potion>("Poison", 5);

	std::unique_ptr<QuestStage> stage14111 = std::make_unique<buyItemStage>(
		"Good trade. Price: 25.",
		14111, 141111, 0, 25, PC, std::move(healPotion)); 
	std::unique_ptr<QuestStage> stage14112 = std::make_unique<buyItemStage>(
		"Bad trade. Price: 50.",
		14112, 141111, 0, 50, PC, std::move(healPotion2)); 
	std::unique_ptr<QuestStage> stage14121 = std::make_unique<buyItemStage>(
		"Good trade. Price: 50.",
		14121, 141211, 0, 50, PC, std::move(poison));
	std::unique_ptr<QuestStage> stage14122 = std::make_unique<buyItemStage>(
		"Bad trade. Price: 75.",
		14122, 141211, 0, 75, PC, std::move(poison2));
	rawPtr->quest.addStage(std::move(stage14111)); /*17*/
	rawPtr->quest.addStage(std::move(stage14112)); /*18*/
	rawPtr->quest.addStage(std::move(stage14121)); /*19*/
	rawPtr->quest.addStage(std::move(stage14122)); /*20*/

	std::unique_ptr<QuestStage> stage141111 = std::make_unique<TextStage>(
		"[You receive: Heal Point]",
		141111, 141111, 0, PC);
	std::unique_ptr<QuestStage> stage141211 = std::make_unique<TextStage>(
		"[You receive: Poison]",
		141211, 141211, 0, PC);
	rawPtr->quest.addStage(std::move(stage141111)); /*21*/
	rawPtr->quest.addStage(std::move(stage141211)); /*22*/

	/*Heal line*/
	std::unique_ptr<QuestStage> stage151 = std::make_unique<RestStage>(
		"Alchemist: Yes, of course!", 151, 151, 0, static_cast<size_t>(RestStage::RestoreChoice::HPRestore), PC);
	std::unique_ptr<QuestStage> stage152 = std::make_unique<TextStage>(
		"Alchemist: I'm busy now. Come later.",
		152, 152, 0, PC);
	rawPtr->quest.addStage(std::move(stage151)); /*23*/
	rawPtr->quest.addStage(std::move(stage152)); /*24*/

	/*Option 2*/
	std::unique_ptr<QuestStage> stage51 = std::make_unique<TextStage>(
		"Goodbye!", 51, 51, 0, PC);
	std::unique_ptr<OptionChoice> option2 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addStage(std::move(stage51)); /*25*/
	rawPtr->quest.addOption(std::move(option2));
	rawPtr->quest.linkStageToOption(25, 2);
	rawPtr->quest.linkStageToOption(7, 2);
	rawPtr->quest.linkStageToOption(8, 2);

	Outskirts.addLocation(std::move(AlchemistHut));

};

void Game::initLevel21()
{
	std::unique_ptr<Location> EvilSwamp = std::make_unique<QuestPointer>("Evil Swamp", "evilSwamp.txt", key2);
	QuestPointer* rawPtr = dynamic_cast<QuestPointer*>(EvilSwamp.get());

	/*Base:*/
	std::unique_ptr<QuestStage> stage0 = std::make_unique<TextStage>(
		"Where are you going?", 999, 0, 0, PC);
	std::unique_ptr<QuestStage> stage1 = std::make_unique<TextStage>(
		"Walk along a barely visible path (2 AP)", 10, 11, 2, PC);
	std::unique_ptr<QuestStage> stage2 = std::make_unique<TextStage>(
		"Walk straight through the fog (3 AP)", 20, 21, 3, PC);
	std::unique_ptr<QuestStage> stage3 = std::make_unique<TextStage>(
		"Check out the strange glowing mushrooms by the water (1 AP)", 30, 31, 1, PC);
	std::unique_ptr<OptionChoice> option0 = std::make_unique<OptionChoice>(3);
	rawPtr->quest.addStage(std::move(stage0)); /*0*/
	rawPtr->quest.addStage(std::move(stage1)); /*1*/
	rawPtr->quest.addStage(std::move(stage2)); /*2*/
	rawPtr->quest.addStage(std::move(stage3)); /*3*/
	rawPtr->quest.addOption(std::move(option0)); 
	rawPtr->quest.linkStageToOption(1, 0);
	rawPtr->quest.linkStageToOption(2, 0);
	rawPtr->quest.linkStageToOption(3, 0);

	std::unique_ptr<QuestStage> stage11 = std::make_unique<TextStage>(
		"You choose a narrow, almost invisible path between the swamps.Branches scratch your face, the earth squelches under your boots.", 11, 1, 0, PC);
	std::unique_ptr<QuestStage> stage21 = std::make_unique<TextStage>(
		"You inhale the damp air and step straight into the white shroud. With each step it becomes colder and harder to breathe.", 21, 2, 0, PC);
	std::unique_ptr<QuestStage> stage31 = std::make_unique<TextStage>(
		"On the surface of the swamp, blue and green lights shimmer - mushrooms that you have never seen before. Their glow is mesmerizing.", 31, 3, 0, PC);
	rawPtr->quest.addStage(std::move(stage11)); /*4*/
	rawPtr->quest.addStage(std::move(stage21)); /*5*/
	rawPtr->quest.addStage(std::move(stage31)); /*6*/

	/*Option 1:*/
	std::unique_ptr<QuestStage> stage111 = std::make_unique<skillCheckStage>(
		"Carefully make your way around the quagmire (2 AP)", 111, 1111, 1112, 2, 2, PC, PC.coordination());
	std::unique_ptr<QuestStage> stage112 = std::make_unique<skillCheckStage>(
		"Hurry to get out faster (1 AP)", 112, 1121, 1112, 1, 2, PC, PC.athletics());
	std::unique_ptr<OptionChoice> option1 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addStage(std::move(stage111)); /*7*/
	rawPtr->quest.addStage(std::move(stage112)); /*8*/
	rawPtr->quest.addOption(std::move(option1));
	rawPtr->quest.linkStageToOption(7, 1);
	rawPtr->quest.linkStageToOption(8, 1);

	/*Option 2:*/
	std::unique_ptr<QuestStage> stage211 = std::make_unique<skillCheckStage>(
		"Navigate by hearing (3 AP)", 211, 2111, 2112, 3, 3, PC, PC.perception());
	std::unique_ptr<QuestStage> stage212 = std::make_unique<skillCheckStage>(
		"Go ahead, relying on swamp survival skills (2 AP)", 212, 2121, 2112, 2, 3, PC, PC.survival());
	std::unique_ptr<OptionChoice> option2 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addStage(std::move(stage211)); /*9*/
	rawPtr->quest.addStage(std::move(stage212)); /*10*/
	rawPtr->quest.addOption(std::move(option2)); 
	rawPtr->quest.linkStageToOption(9, 2);
	rawPtr->quest.linkStageToOption(10, 2);

	/*Option 3:*/
	std::unique_ptr<QuestStage> stage311 = std::make_unique<skillCheckStage>(
		"Move carefully, trying not to make noise (2 AP)", 311, 1111, 3111, 2, 3, PC, PC.stealth());
	std::unique_ptr<QuestStage> stage312 = std::make_unique<skillCheckStage>(
		"Hurry to get out faster (1 AP)", 312, 3121, 3111, 1, 3, PC, PC.athletics());
	std::unique_ptr<OptionChoice> option3 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addStage(std::move(stage311)); /*11*/
	rawPtr->quest.addStage(std::move(stage312)); /*12*/
	rawPtr->quest.addOption(std::move(option3));
	rawPtr->quest.linkStageToOption(11, 3);
	rawPtr->quest.linkStageToOption(12, 3);

	/*Good results:*/
	std::unique_ptr<Item> protectiveTalisman = std::make_unique<QuestItem>("Protective Talisman");
	std::unique_ptr<QuestStage> stage1111 = std::make_unique<giveItemStage>(
		"You come to an abandoned altar, where among the moss you find the Protective Talisman.", 1111, 999, 0, PC, std::move(protectiveTalisman));
	std::unique_ptr<QuestStage> stage1121 = std::make_unique<TextStage>(
		"You reach the end of the trail, tired but whole.", 1121, 999, 0, PC);
	std::unique_ptr<QuestStage> stage2111 = std::make_unique<TextStage>(
		"You break out of the fog at the last moment and find traces of the victim of the swamp forces.", 2111, 999, 0, PC);
	std::unique_ptr<QuestStage> stage2121 = std::make_unique<TextStage>(
		"You navigate around the quicksand and reach the center of the swamp without incident.", 2121, 40, 0, PC);
	std::unique_ptr<QuestStage> stage3121 = std::make_unique<TextStage>(
		"You reach the end of the trail, tired but whole.", 3121, 40, 0, PC);
	rawPtr->quest.addStage(std::move(stage1111)); /*13*/
	rawPtr->quest.addStage(std::move(stage1121)); /*14*/
	rawPtr->quest.addStage(std::move(stage2111)); /*15*/
	rawPtr->quest.addStage(std::move(stage2121)); /*16*/
	rawPtr->quest.addStage(std::move(stage3121)); /*17*/

	/*Bad results:*/
	std::unique_ptr<QuestStage> stage1112 = std::make_unique<AttackStage>(
		"If you stumble, you attract the attention of a swamp creature.", 1112, 40, 0, 0, PC);
	std::unique_ptr<QuestStage> stage2112 = std::make_unique<TextStage>(
		"Lost, you find yourself trapped by spirits.", 2112, 50, 0, PC);
	std::unique_ptr<QuestStage> stage3111 = std::make_unique<AttackStage>(
		"You were careless and triggered the swamp creature onto yourself.", 3111, 999, 0, 0, PC);
	rawPtr->quest.addStage(std::move(stage1112)); /*18*/
	rawPtr->quest.addStage(std::move(stage2112)); /*19*/
	rawPtr->quest.addStage(std::move(stage3111)); /*20*/

	/*Endings:*/
	std::unique_ptr<QuestStage> stage40 = std::make_unique<TextStage>(
		"You reach the very center of the swamp and destroy the \"Heart of the Swamp\". Now new creatures will no longer appear.",
		40, 40, 0, PC);
	std::unique_ptr<QuestStage> stage50 = std::make_unique<TextStage>(
		"When you manage to get out of the swamp after a long time, wounded and tired, you think: \"The swamps do not tolerate the weak."
		"I barely got out alive.I will not go back there again.\"",
		50, 50, 0, PC);
	rawPtr->quest.addStage(std::move(stage40)); /*21*/
	rawPtr->quest.addStage(std::move(stage50)); /*22*/

	rawPtr->quest.setReward(150);
	Outskirts.addLocation(std::move(EvilSwamp));
}

void Game::initLevel30() 
{
	std::unique_ptr<Location> MountainPeak = std::make_unique<QuestGetPointer>("Mountain Peak", "mountainPeak.txt", key3);
	QuestGetPointer* rawPtr = dynamic_cast<QuestGetPointer*>(MountainPeak.get());

	/*Base*/
	std::unique_ptr<QuestStage> stage10 = std::make_unique<TextStage>(
		"Blacksmith: Guests don't often wander here. What are you looking for - steel, rest, or a challenge?",
		10, 0, 0, PC);
	std::unique_ptr<QuestStage> stage30 = std::make_unique<TextStage>(
		"Blacksmith: How's life?",
		30, 2, 0, PC);
	std::unique_ptr<QuestStage> stage40 = std::make_unique<TextStage>(
		"Blacksmith: I spit in the face of people like you!",
		40, 40, 0, PC);
	std::unique_ptr<QuestStage> stage50 = std::make_unique<TextStage>(
		"Blacksmith: Legends will be written about you!",
		50, 2, 0, PC);
	rawPtr->quest.addStage(std::move(stage10)); /*0*/
	rawPtr->quest.addStage(std::move(stage30)); /*1*/
	rawPtr->quest.addStage(std::move(stage40)); /*2*/
	rawPtr->quest.addStage(std::move(stage50)); /*3*/

	/*Main Option*/
	std::unique_ptr<QuestStage> stage11 = std::make_unique<TextStage>(
		"I'm looking for something important.",
		11, 20, 0, PC);
	std::unique_ptr<QuestStage> stage12 = std::make_unique<TextStage>(
		"I was told you knew about the Dragon Caves.",
		12, 20, 0, PC);
	std::unique_ptr<QuestStage> stage13 = std::make_unique<TextStage>(
		"I just want to talk.",
		13, 20, 0, PC);
	std::unique_ptr<QuestStage> stage14 = std::make_unique<TextStage>(
		"Let's haggle.",
		14, 141, 0, PC);
	std::unique_ptr<QuestStage> stage15 = std::make_unique<skillCheckStage>(
		"Can I take a break with you? (2 AP)",
		15, 151, 152, 2, 4, PC, PC.charm());
	std::unique_ptr<QuestStage> stage16 = std::make_unique<skillCheckStage>(
		"Can you fix my armor? (2 AP)",
		16, 161, 162, 2, 2, PC, PC.charm());
	std::unique_ptr<QuestStage> stage17 = std::make_unique<TextStage>(
		"Bye!",
		17, 17, 0, PC);
	std::unique_ptr<OptionChoice> option0 = std::make_unique<OptionChoice>(5);
	rawPtr->quest.addStage(std::move(stage11)); /*4*/
	rawPtr->quest.addStage(std::move(stage12)); /*5*/
	rawPtr->quest.addStage(std::move(stage13)); /*6*/
	rawPtr->quest.addStage(std::move(stage14)); /*7*/
	rawPtr->quest.addStage(std::move(stage15)); /*8*/
	rawPtr->quest.addStage(std::move(stage16)); /*9*/
	rawPtr->quest.addStage(std::move(stage17)); /*10*/
	rawPtr->quest.addOption(std::move(option0));
	rawPtr->quest.linkStageToOption(4, 0);
	rawPtr->quest.linkStageToOption(5, 0);
	rawPtr->quest.linkStageToOption(6, 0);
	rawPtr->quest.linkStageToOption(7, 0);
	rawPtr->quest.linkStageToOption(8, 0);

	/*Quest Stage*/
	std::unique_ptr<QuestStage> stage20 = std::make_unique<TextStage>(
		"Blacksmith: Ha! So fate has brought you to me. Below, in the depths of the mountain, the Ancient One sleeps.\n"
		"The treasures he guards may help the city. But wake him carefully.\n"
		"I can tell you the way... if you are willing to risk it.",
		20, 21, 0, PC);
	std::unique_ptr<QuestStage> stage21 = std::make_unique<TextStage>(
		"[New Quest : DragonCaves]",
		21, 21, 0, PC);
	rawPtr->quest.addStage(std::move(stage20)); /*11*/
	rawPtr->quest.addStage(std::move(stage21)); /*12*/

	/*Merchant line*/
	std::unique_ptr<QuestStage> stage141 = std::make_unique<TextStage>(
		"Blacksmith: If you need a better blade or a more powerful crossbow, we can negotiate.\n But know this: my craft is not for the poor.",
		141, 1, 0, PC);
	rawPtr->quest.addStage(std::move(stage141)); /*13*/

	std::unique_ptr<QuestStage> stage1411 = std::make_unique<skillCheckStage>(
		"Bargain for the Great Sword (2 AP)",
		1411, 14111, 14112, 2, 3, PC, PC.negotiation());
	std::unique_ptr<QuestStage> stage1412 = std::make_unique<skillCheckStage>(
		"Bargain for the Crossbow (2 AP)",
		1412, 14121, 14122, 2, 3, PC, PC.negotiation());
	std::unique_ptr<QuestStage> stage1413 = std::make_unique<skillCheckStage>(
		"Bargain for the Great Armor (2 AP)",
		1413, 14131, 14132, 2, 3, PC, PC.negotiation());
	std::unique_ptr<OptionChoice> option1 = std::make_unique<OptionChoice>(3);
	rawPtr->quest.addStage(std::move(stage1411)); /*14*/
	rawPtr->quest.addStage(std::move(stage1412)); /*15*/
	rawPtr->quest.addStage(std::move(stage1413)); /*16*/
	rawPtr->quest.addOption(std::move(option1));
	rawPtr->quest.linkStageToOption(14, 1);
	rawPtr->quest.linkStageToOption(15, 1);
	rawPtr->quest.linkStageToOption(16, 1);

	std::unique_ptr<Item> item1 = std::make_unique<Weapon>("Great Sword", Weapon::Melee, 7, 3);
	std::unique_ptr<Item> item2 = std::make_unique<Weapon>("Great Sword", Weapon::Melee, 7, 3);
	std::unique_ptr<Item> item3 = std::make_unique<Weapon>("Crossbow", Weapon::Range, 7, 3);
	std::unique_ptr<Item> item4 = std::make_unique<Weapon>("Crossbow", Weapon::Range, 7, 3);
	std::unique_ptr<Item> item5 = std::make_unique<Armor>("Great Armor", 20, 3);
	std::unique_ptr<Item> item6 = std::make_unique<Armor>("Great Armor", 20, 3);

	std::unique_ptr<QuestStage> stage14111 = std::make_unique<buyItemStage>(
		"Good trade. Price: 100.",
		14111, 141111, 0, 100, PC, std::move(item1));
	std::unique_ptr<QuestStage> stage14112 = std::make_unique<buyItemStage>(
		"Bad trade. Price: 150.",
		14112, 141111, 0, 150, PC, std::move(item2));
	std::unique_ptr<QuestStage> stage14121 = std::make_unique<buyItemStage>(
		"Good trade. Price: 100.",
		14121, 141211, 0, 100, PC, std::move(item3));
	std::unique_ptr<QuestStage> stage14122 = std::make_unique<buyItemStage>(
		"Bad trade. Price: 150.",
		14122, 141211, 0, 150, PC, std::move(item4));
	std::unique_ptr<QuestStage> stage14131 = std::make_unique<buyItemStage>(
		"Good trade. Price: 150.",
		14131, 141311, 0, 150, PC, std::move(item5));
	std::unique_ptr<QuestStage> stage14132 = std::make_unique<buyItemStage>(
		"Bad trade. Price: 200.",
		14132, 141311, 0, 200, PC, std::move(item6));
	rawPtr->quest.addStage(std::move(stage14111)); /*16*/
	rawPtr->quest.addStage(std::move(stage14112)); /*17*/
	rawPtr->quest.addStage(std::move(stage14121)); /*18*/
	rawPtr->quest.addStage(std::move(stage14122)); /*19*/
	rawPtr->quest.addStage(std::move(stage14131)); /*20*/
	rawPtr->quest.addStage(std::move(stage14132)); /*21*/

	std::unique_ptr<QuestStage> stage141111 = std::make_unique<TextStage>(
		"[You receive: Great Sword]",
		141111, 141111, 0, PC);
	std::unique_ptr<QuestStage> stage141211 = std::make_unique<TextStage>(
		"[You receive: Crossbow]",
		141211, 141211, 0, PC);
	std::unique_ptr<QuestStage> stage141311 = std::make_unique<TextStage>(
		"[You receive: Great Armor]",
		141311, 141311, 0, PC);
	rawPtr->quest.addStage(std::move(stage141111)); /*22*/
	rawPtr->quest.addStage(std::move(stage141211)); /*23*/
	rawPtr->quest.addStage(std::move(stage141311)); /*24*/

	/*Service line 1*/
	std::unique_ptr<QuestStage> stage151 = std::make_unique<RestStage>(
		"Blacksmith: I see fatigue on your face. If you want, spend the night by my hearth. But the morning will be cold.", 
		151, 151, 0, static_cast<size_t>(RestStage::RestoreChoice::APRestore), PC);
	std::unique_ptr<QuestStage> stage152 = std::make_unique<TextStage>(
		"Blacksmith: Sorry. I'm expecting guests today.",
		152, 152, 0, PC);
	rawPtr->quest.addStage(std::move(stage151)); /*25*/
	rawPtr->quest.addStage(std::move(stage152)); /*26*/

	/*Service line 2*/
	std::unique_ptr<QuestStage> stage161 = std::make_unique<RestStage>(
		"Blacksmith: Sure, come here.",
		161, 161, 0, static_cast<size_t>(RestStage::RestoreChoice::ArmorHP), PC);
	std::unique_ptr<QuestStage> stage162 = std::make_unique<TextStage>(
		"Blacksmith: Sorry, I have a lot of work!",
		162, 162, 0, PC);
	rawPtr->quest.addStage(std::move(stage161)); /*27*/
	rawPtr->quest.addStage(std::move(stage162)); /*28*/

	/*Option 2*/
	std::unique_ptr<OptionChoice> option2 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addOption(std::move(option2));
	rawPtr->quest.linkStageToOption(7, 2);
	rawPtr->quest.linkStageToOption(8, 2);
	rawPtr->quest.linkStageToOption(9, 2);
	rawPtr->quest.linkStageToOption(10, 2);

	BlackMountain.addLocation(std::move(MountainPeak));
};

void Game::initLevel31()
{
	std::unique_ptr<Location> DragonCaves = std::make_unique<QuestPointer>("Dragon Caves", "dragonCaves.txt", key3);
	QuestPointer* rawPtr = dynamic_cast<QuestPointer*>(DragonCaves.get());

	/*Base:*/
	std::unique_ptr<QuestStage> stage0 = std::make_unique<TextStage>(
		"Where are you going?", 999, 0, 0, PC);
	std::unique_ptr<QuestStage> stage1 = std::make_unique<TextStage>(
		"Inspect the entrance to the caves (1 AP)", 10, 11, 1, PC);
	std::unique_ptr<QuestStage> stage2 = std::make_unique<TextStage>(
		"Go deeper along the main path (2 AP)", 20, 21, 2, PC);
	std::unique_ptr<QuestStage> stage3 = std::make_unique<useQuestItemStage>(
		"Look for a hidden passage (if you have a Protective Talisman)", 30, 31, PC, "Protective Talisman");
	std::unique_ptr<QuestStage> stage4 = std::make_unique<skillCheckStage>(
		"Try to pass without a talisman (4 AP)", 40, 41, 42, 4, 3, PC, PC.alchemy());
	std::unique_ptr<OptionChoice> option0 = std::make_unique<OptionChoice>(4);
	rawPtr->quest.addStage(std::move(stage0)); /*0*/
	rawPtr->quest.addStage(std::move(stage1)); /*1*/
	rawPtr->quest.addStage(std::move(stage2)); /*2*/
	rawPtr->quest.addStage(std::move(stage3)); /*3*/
	rawPtr->quest.addStage(std::move(stage4)); /*4*/
	rawPtr->quest.addOption(std::move(option0));
	rawPtr->quest.linkStageToOption(1, 0);
	rawPtr->quest.linkStageToOption(2, 0);
	rawPtr->quest.linkStageToOption(3, 0);
	rawPtr->quest.linkStageToOption(4, 0);

	std::unique_ptr<QuestStage> stage11 = std::make_unique<TextStage>(
		"You carefully examine the rocks, trying to figure out if the path can be made safe. The stones crumble under your feet.", 11, 1, 0, PC);
	std::unique_ptr<QuestStage> stage21 = std::make_unique<TextStage>(
		"The path leads into a huge stone gut. The deeper you go, the more you feel the heaviness in your chest. It becomes difficult to breathe.", 21, 2, 0, PC);
	std::unique_ptr<QuestStage> stage31 = std::make_unique<TextStage>(
		"The talisman begins to vibrate slightly on your chest, pointing to a thin crack in the rock.", 31, 32, 0, PC);
	std::unique_ptr<QuestStage> stage32 = std::make_unique<TextStage>(
		"You enter a huge hall. In the center, a dragon sleeps, its scales gleaming in the dim light of the magma.", 32, 3, 0, PC);
	std::unique_ptr<QuestStage> stage41 = std::make_unique<TextStage>(
		"Clearing the way safely.", 41, 32, 0, PC);
	std::unique_ptr<QuestStage> stage42 = std::make_unique<TextStage>(
		"Absorbed by toxic fumes.", 42, 60, 0, PC);
	rawPtr->quest.addStage(std::move(stage11)); /*5*/
	rawPtr->quest.addStage(std::move(stage21)); /*6*/
	rawPtr->quest.addStage(std::move(stage31)); /*7*/
	rawPtr->quest.addStage(std::move(stage32)); /*8*/
	rawPtr->quest.addStage(std::move(stage41)); /*9*/
	rawPtr->quest.addStage(std::move(stage42)); /*10*/

	/*Option 1:*/
	std::unique_ptr<QuestStage> stage111 = std::make_unique<skillCheckStage>(
		"Try to secure the trail with improvised means (2 AP)", 111, 1111, 1112, 2, 3, PC, PC.mechanics());
	std::unique_ptr<QuestStage> stage112 = std::make_unique<skillCheckStage>(
		"Pass without delay (2 AP)", 112, 1121, 1122, 2, 3, PC, PC.coordination());
	std::unique_ptr<OptionChoice> option1 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addStage(std::move(stage111)); /*11*/
	rawPtr->quest.addStage(std::move(stage112)); /*12*/
	rawPtr->quest.addOption(std::move(option1));
	rawPtr->quest.linkStageToOption(11, 1);
	rawPtr->quest.linkStageToOption(12, 1);

	std::unique_ptr<QuestStage> stage1111 = std::make_unique<TextStage>(
		"Safe descent, passage becomes stable.", 1111, 32, 0, PC);
	std::unique_ptr<QuestStage> stage1121 = std::make_unique<TextStage>(
		"You deftly jump over dangerous areas.", 1121, 32, 0, PC);
	std::unique_ptr<QuestStage> stage1112 = std::make_unique<DamageStage>(
		"Rockfall, you take damage, but you can continue.", 1112, 32, 0, static_cast<size_t>(DamageStage::DamageChoice::HPDamage), 5, PC);
	std::unique_ptr<QuestStage> stage1122 = std::make_unique<DamageStage>(
		"You slip and lose some health.", 1122, 32, 0, static_cast<size_t>(DamageStage::DamageChoice::HPDamage), 3, PC);
	rawPtr->quest.addStage(std::move(stage1111)); /*13*/
	rawPtr->quest.addStage(std::move(stage1121)); /*14*/
	rawPtr->quest.addStage(std::move(stage1112)); /*15*/
	rawPtr->quest.addStage(std::move(stage1122)); /*16*/

	/*Option 2:*/
	std::unique_ptr<QuestStage> stage211 = std::make_unique<skillCheckStage>(
		"Focus and overcome fear (3 AP)", 211, 2111, 2112, 3, 3, PC, PC.discipline());
	std::unique_ptr<QuestStage> stage212 = std::make_unique<skillCheckStage>(
		"Slow down your breathing and walk carefully (2 AP)", 212, 2121, 2122, 2, 3, PC, PC.skullduggery());
	std::unique_ptr<OptionChoice> option2 = std::make_unique<OptionChoice>(2);
	rawPtr->quest.addStage(std::move(stage211)); /*17*/
	rawPtr->quest.addStage(std::move(stage212)); /*18*/
	rawPtr->quest.addOption(std::move(option2));
	rawPtr->quest.linkStageToOption(17, 2);
	rawPtr->quest.linkStageToOption(18, 2);

	std::unique_ptr<QuestStage> stage2111 = std::make_unique<TextStage>(
		"Safe descent, passage becomes stable.", 2111, 32, 0, PC);
	std::unique_ptr<QuestStage> stage2121 = std::make_unique<TextStage>(
		"You deftly jump over dangerous areas.", 2121, 32, 0, PC);
	std::unique_ptr<QuestStage> stage2112 = std::make_unique<DamageStage>(
		"Rockfall, you take damage, but you can continue.", 2112, 32, 0, static_cast<size_t>(DamageStage::DamageChoice::APDamage), 3, PC);
	std::unique_ptr<QuestStage> stage2122 = std::make_unique<DamageStage>(
		"You slip and lose some health.", 2122, 32, 0, static_cast<size_t>(DamageStage::DamageChoice::HPDamage), 3, PC);
	rawPtr->quest.addStage(std::move(stage2111)); /*19*/
	rawPtr->quest.addStage(std::move(stage2121)); /*20*/
	rawPtr->quest.addStage(std::move(stage2112)); /*21*/
	rawPtr->quest.addStage(std::move(stage2122)); /*22*/

	/*Option 3:*/
	std::unique_ptr<QuestStage> stage321 = std::make_unique<skillCheckStage>(
		"Sneak up and steal some of the treasure (4 AP)", 321, 3211, 3212, 4, 4, PC, PC.stealth());
	std::unique_ptr<QuestStage> stage322 = std::make_unique<TextStage>(
		"Rely on your own strength and attack the dragon.", 322, 3212, 0, PC);
	std::unique_ptr<QuestStage> stage323 = std::make_unique<skillCheckStage>(
		"Conduct a chemical reaction to distract (5 AP)", 323, 3231, 3212, 5, 4, PC, PC.alchemy());
	std::unique_ptr<OptionChoice> option3 = std::make_unique<OptionChoice>(3);
	rawPtr->quest.addStage(std::move(stage321)); /*23*/
	rawPtr->quest.addStage(std::move(stage322)); /*24*/
	rawPtr->quest.addStage(std::move(stage323)); /*25*/
	rawPtr->quest.addOption(std::move(option3));
	rawPtr->quest.linkStageToOption(23, 3);
	rawPtr->quest.linkStageToOption(24, 3);
	rawPtr->quest.linkStageToOption(25, 3);

	std::unique_ptr<QuestStage> stage3211 = std::make_unique<TextStage>(
		"You steal the treasure and leave without a fight.", 3211, 50, 0, PC);
	std::unique_ptr<QuestStage> stage3231 = std::make_unique<TextStage>(
		"The dragon is temporarily blinded, you can quickly steal the treasure.", 3231, 50, 0, PC);
	std::unique_ptr<QuestStage> stage3212 = std::make_unique<AttackStage>(
		"The Ancient Dragon Awakens.", 3212, 50, 0, 0, PC);
	rawPtr->quest.addStage(std::move(stage3211)); /*26*/
	rawPtr->quest.addStage(std::move(stage3231)); /*27*/
	rawPtr->quest.addStage(std::move(stage3212)); /*28*/

	/*Endings:*/
	std::unique_ptr<QuestStage> stage50 = std::make_unique<TextStage>(
		"Having skillfully avoided or defeated the dragon, you return from the depths with the stolen treasure.\n"
		"The fame of your feat quickly spreads, opening up new opportunities and respect in the eyes of nobles and commoners.",
		50, 50, 0, PC);
	std::unique_ptr<QuestStage> stage60 = std::make_unique<TextStage>(
		"Miscalculating or losing in battle, you are forced to retreat from the Caves in panic, leaving behind only traces of shame\n"
		"The road to the dragon is forever closed to you, and the memory of the missed opportunity will be a heavy burden on your path.",
		60, 60, 0, PC);
	rawPtr->quest.addStage(std::move(stage50)); /*29*/
	rawPtr->quest.addStage(std::move(stage60)); /*30*/

	rawPtr->quest.setReward(200);
	BlackMountain.addLocation(std::move(DragonCaves));
}

void Game::initLevels()
{
	initLevel10();
	initLevel11();
	initLevel20();
	initLevel21();
	initLevel30();
	initLevel31();
}

void Game::initEnemies()
{
	/*Cultist*/
	std::unique_ptr<Archetype> arch = std::make_unique<Genius>();
	std::unique_ptr<Specialization> spec = std::make_unique<Thief>();
	Character cultist("Cultist", std::move(arch), std::move(spec));
	cultist.specialization->Athletics += 2;
	cultist.specialization->Melee += 2;
	cultist.specialization->Vigilance += 2;
	cultist.SetAll();
	std::unique_ptr<Item> weapon = std::make_unique<Weapon>("Knife", Weapon::Melee, 3, 2);
	cultist.addItem(std::move(weapon));
	std::unique_ptr<Item> mantle = std::make_unique<Armor>("Mantle", 5, 1);
	cultist.addItem(std::move(mantle));

	addEnemy(std::move(cultist));

	/*Swamp Spawn*/
	std::unique_ptr<Archetype> arch2 = std::make_unique<Simpleton>();
	std::unique_ptr<Specialization> spec2 = std::make_unique<Archer>();
	Character spawn("Swamp Spawn", std::move(arch2), std::move(spec2));
	spawn.specialization->Athletics += 1;
	spawn.specialization->Cool += 2;

	spawn.SetAll();
	spawn.archetype->changeHP(8);
	spawn.currentHP = spawn.archetype->getHP();

	std::unique_ptr<Item> weapon2 = std::make_unique<Weapon>("Mud ball", Weapon::Range, 4, 3);
	spawn.addItem(std::move(weapon2));
	std::unique_ptr<Item> armor = std::make_unique<Armor>("Slippery body", 10, 1);
	spawn.addItem(std::move(armor));

	addEnemy(std::move(spawn));

	/*Dragon*/
	std::unique_ptr<Archetype> arch3 = std::make_unique<Sturdy>();
	std::unique_ptr<Specialization> spec3 = std::make_unique<Knight>();
	Character dragon("Dragon", std::move(arch3), std::move(spec3));
	dragon.specialization->Vigilance += 2;
	dragon.specialization->Ranged += 2;

	dragon.SetAll();
	dragon.archetype->changeHP(8);
	dragon.currentHP = dragon.archetype->getHP();

	std::unique_ptr<Item> weapon3 = std::make_unique<Weapon>("Claws", Weapon::Melee, 5, 2);
	dragon.addItem(std::move(weapon3));
	std::unique_ptr<Item> weapon4 = std::make_unique<Weapon>("Fire", Weapon::Range, 6, 4);
	dragon.addItem(std::move(weapon4));
	std::unique_ptr<Item> armor1 = std::make_unique<Armor>("Dragon scales", 40, 3);
	dragon.addItem(std::move(armor1));

	addEnemy(std::move(dragon));
}

void Game::loadLocation(size_t index, Map& map, FightingScene& fight, size_t winStage, size_t defeatStage, size_t questQetStage)
{
	if (auto rawPtr = dynamic_cast<QuestPointer*>(map[index].get()))
	{
		for (size_t i = 0; i < keySize; i++)
		{
			rawPtr->activate(keys[i]);
			if (rawPtr->status())
			{
				rawPtr->readDescription();
				bool isQuestEnded = sceneControl.loadQuest(PC, rawPtr, fight, 999, winStage, defeatStage);
				if (isQuestEnded)
				{
					if (rawPtr->quest.getStatus() == Quest::win) {
						winCount += 1;
						size_t reward = rawPtr->quest.getReward();
						std::cout << "You get " << reward << " money for quest!\n";
						std::cin.get();
						PC.money += reward;
						map.setFinishStatus(Quest::win);
					}
					else if (rawPtr->quest.getStatus() == Quest::defeat) {
						defeatCount += 1;
						map.setFinishStatus(Quest::defeat);
					}
				}
				clearScreen();

				return;
			}
		}

		std::cout << "Meeting location prohibited!\n\n";
		std::cin.get();
	}
	else if (auto rawPtr = dynamic_cast<QuestGetPointer*>(map[index].get()))
	{
		rawPtr->readDescription();
		std::cout << "\n";
		std::cin.get();
		bool isKeyAdded = sceneControl.loadNPCScene(rawPtr, map.getFinishStatus(), questQetStage);
		if (isKeyAdded)
		{
			rawPtr->activate("OK");
			std::string newKey = rawPtr->getKey();
			addKey(newKey);
			std::cout << "Key Added!\n\n";
			std::cin.get();
			clearScreen();
		}
	}
}

void Game::gamePlay(size_t choice)
{
	MapMenu newMenu;
	bool isArmor = false;
	FightingScene sewerFight(&enemies[0], PC, 10, 10, 2, FightingScene::Cool, FightingScene::MeleeMod);
	FightingScene swampFight(&enemies[1], PC, 3, 15, 3, FightingScene::Vigilance, FightingScene::RangeMod);
	FightingScene caveFight(&enemies[2], PC, 3, 20, 4, FightingScene::Cool, FightingScene::BalanceMod);
	size_t maxAP = PC.archetype->getAP() - (5 - PC.Discipline());
	size_t maxHP = PC.archetype->getHP() - (5 - PC.Resilience());
	size_t maxArmorHP;

	switch (choice)
	{
	case 1:
		if (PC.currentAP == PC.archetype->getAP() || PC.currentAP >= maxAP)
		{
			std::cout << "AP have reached its maximum possible!\n";
			std::cin.get();
		}
		else if (PC.skillCheck(PC.discipline(), 2))
		{
			size_t mod = 5 - PC.Discipline();
			PC.currentAP = (PC.currentAP + mod < maxAP) ? PC.currentAP + mod : maxAP;
			std::cout << "Some AP recovered\n";
			std::cin.get();
		}
		else { std::cout << "Unsuccess\n"; std::cin.get();}
		break;
	case 2:
		if (PC.currentHP == PC.archetype->getHP() || PC.currentHP >= maxHP)
		{
			std::cout << "HP have reached its maximum possible!\n";
			std::cin.get();
		}
		else if (PC.skillCheck(PC.resilience(), 2))
		{
			size_t mod = 5 - PC.Resilience();
			PC.currentHP = (PC.currentHP + mod < maxHP) ? PC.currentHP + mod : maxHP;
			std::cout << "Some HP recovered\n";
			std::cin.get();
		}
		else { std::cout << "Unsuccess\n"; std::cin.get();}
		break;
	case 3:
		for (size_t i = 0; i < PC.inventory.getSize(); ++i)
		{
			Item* item = PC.inventory[i].get();
			if (Armor* armor = dynamic_cast<Armor*>(item))
			{
				isArmor = true;
				maxArmorHP = armor->getArmorHP() / 2 + 1;
				int mod = 5 - PC.Mechanics();

				if(armor->current_armor_hp == armor->getArmorHP() || armor->current_armor_hp >= maxArmorHP) 
				{std::cout << armor->Name() << " HP have reached its maximum possible!\n"; std::cin.get();}
				else if (PC.skillCheck(PC.mechanics(), 2))
				{
					armor->current_armor_hp = (armor->current_armor_hp + mod < maxArmorHP) ? armor->current_armor_hp + mod : maxArmorHP;
					std::cout << "Armor " << armor->Name() << " HP is recovered\n";
					std::cin.get();
				}
				else { std::cout << "Unsuccess\n"; std::cin.get(); }
			}
		}
		if (!isArmor) { std::cout << "You don't have any armor\n"; std::cin.get();}
		break;
	case 4:
		CapitalCity.readDescription();
		std::cout << std::endl;
		choice = newMenu.show(CapitalCity);
		clearScreen();
		if (choice > CapitalCity.getSize()) { return; }
		loadLocation(choice - 1, CapitalCity, sewerFight, 50, 60, 22);
		break;
	case 5:
		Outskirts.readDescription();
		std::cout << std::endl;
		choice = newMenu.show(Outskirts);
		clearScreen();
		if (choice > Outskirts.getSize()) { return; }
		loadLocation(choice - 1, Outskirts, swampFight, 40, 50, 21);
		break;
	case 6:
		BlackMountain.readDescription();
		std::cout << std::endl;
		choice = newMenu.show(BlackMountain);
		clearScreen();
		if (choice > BlackMountain.getSize()) { return; }
		loadLocation(choice - 1, BlackMountain, caveFight, 50, 60, 21);
		break;
	default:
		break;
	}
}

int Game::MenuControl()
{
	while (true)
	{
		PC.printInfo();
		int choice = InsideGameMenu::show();
		clearScreen();
		if (choice != 7)
		{
			gamePlay(choice);
			clearScreen();
		}
		return choice;
	}
}

void Game::SaveControl()
{
	int choice = SaveLoadMenu::showSaves();

	switch (choice)
	{
	case 1:
		GameDataManager::SaveGame(*this, "saveSlot1.bin");
		GameDataManager::SaveLocationsStatus(*this, "saveSlot1LocStatus.bin");
		break;
	case 2:
		GameDataManager::SaveGame(*this, "saveSlot2.bin");
		GameDataManager::SaveLocationsStatus(*this, "saveSlot2LocStatus.bin");
		break;
	case 3:
		GameDataManager::SaveGame(*this, "saveSlot3.bin");
		GameDataManager::SaveLocationsStatus(*this, "saveSlot3LocStatus.bin");
		break;
	default:
		break;
	}
}

bool Game::fileExists(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}

void Game::LoadControl(bool& gameActive)
{
	int choice = SaveLoadMenu::showLoads();

	std::string saveFile, locStatusFile;

	switch (choice)
	{
	case 1:
		saveFile = "saveSlot1.bin";
		locStatusFile = "saveSlot1LocStatus.bin";
		break;
	case 2:
		saveFile = "saveSlot2.bin";
		locStatusFile = "saveSlot2LocStatus.bin";
		break;
	case 3:
		saveFile = "saveSlot3.bin";
		locStatusFile = "saveSlot3LocStatus.bin";
		break;
	case 4:
		saveFile = "autosave1.bin";
		locStatusFile = "autosaveLocStatus1.bin";
		break;
	default:
		return;
	}

	if (fileExists(saveFile) && fileExists(locStatusFile))
	{
		reset();
		GameDataManager::LoadGame(*this, saveFile);
		initMaps();
		initLevels();
		GameDataManager::LoadLocationsStatus(*this, locStatusFile);
		gameActive = true;
	}
	else
	{
		std::cout << "One or both save files were not found. Unable to load..\n";
	}
}

void Game::start()
{
	bool gameActive = false;

	while (true)
	{
		int choice = MainMenu::show();
		clearScreen();

		switch (choice)
		{
		case 1:
			reset();
			/*createPC.initialize(PC);*/
			createPC.TestPC(PC);
			std::cout << "Character Create Successfully" << std::endl;
			initEnemies();
			initMaps();
			initLevels();
			std::cin.get();
			clearScreen();
			gameActive = true;

			while (true)
			{
				int switchControl = MenuControl();
				if (switchControl == 7) { break; }
			}
			break;
		case 2:
			if (!gameActive) { break; }

			while (true)
			{

				int switchControl = MenuControl();
				if (switchControl == 7) { break; }
			}

			std::cin.get();
			clearScreen();
			break;
		case 3:
			SaveControl();
			std::cin.get();
			clearScreen();
			break;
		case 4:
			LoadControl(gameActive);
			std::cin.get();
			clearScreen();
			break;
		case 5:
			GameDataManager::SaveGame(*this, "autosave1.bin");
			GameDataManager::SaveLocationsStatus(*this, "autosaveLocStatus1.bin");
			return;
		default:
			break;
		}
	}
}