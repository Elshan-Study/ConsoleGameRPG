#include "Game.h"

void Game::addKey(std::string key)
{
	keys[keySize++] = key;
}

void Game::addEnemy(Character&& enemy)
{
	enemies[enemySize++] = std::move(enemy);
}

/*QuestPointer EvilSwamp("Evil Swamp", "evilSwamp.txt", key2);
	QuestPointer DragonCaves("Dragon Caves", "dragonCaves.txt", key3);*/

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
	/*EvilSwamp.reset();
	BlackMountain.reset(); */
}

void Game::initLevel1()
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
		"Look at the symbols and try to recognize them (3 AP)", 111, 1111, 999, 1, 2, PC, PC.perception());
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

void Game::initLevel2()
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

void Game::initLevels()
{
	initLevel1();
	initLevel2();
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
	std::unique_ptr<Item> weapon = std::make_unique<Weapon>("Knife", 3, 2);
	cultist.addItem(std::move(weapon));
	std::unique_ptr<Item> mantle = std::make_unique<Armor>("Mantle", 5, 1);
	cultist.addItem(std::move(mantle));

	addEnemy(std::move(cultist));
}

void Game::loadLocation(size_t index, Map& map, FightingScene& fight)
{
	if (auto rawPtr = dynamic_cast<QuestPointer*>(map[index].get()))
	{
		for (size_t i = 0; i < keySize; i++)
		{
			rawPtr->activate(keys[i]);
			if (rawPtr->status())
			{
				rawPtr->readDescription();
				bool isQuestEnded = sceneControl.loadQuest(PC, rawPtr, fight, 999, 50, 60);
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
		bool isKeyAdded = sceneControl.loadNPCScene(rawPtr, map.getFinishStatus());
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
	FightingScene sewerFight(&enemies[0], PC, 10, 10, FightingScene::Cool, FightingScene::MeleeMod);
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
		loadLocation(choice - 1, CapitalCity, sewerFight);
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
		CapitalCity.setMain("Capital City", "capitalCity.txt");
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
			CapitalCity.setMain("Capital City", "capitalCity.txt");
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
				if (switchControl == 6) { break; }
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