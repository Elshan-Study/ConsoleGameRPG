#pragma once
#include <iostream>
#include <fstream> 
#include "Character.h"
#include "Interface.h"
#include "Location.h"
#include "GameDataManager.h"
#include "Quest.h"

class Game
{
private:
	PCCharacterCreate createPC;
	SceneControl sceneControl;
	Map CapitalCity;
	Map Outskirts;
	Map BlackMountain;
	size_t keySize = 0;
	size_t enemySize = 0;
	size_t winCount;
	size_t defeatCount;
	std::string* keys = new std::string[QUESTCOUNT];
	Character* enemies = new Character[ENEMYCOUNT];
	static const size_t QUESTCOUNT = 3;
	static const size_t ENEMYCOUNT = 3;
	Character PC;

	friend class GameDataManager;
public:

	Game() = default;
	~Game() { delete[] keys; delete[] enemies; }

	void addKey(std::string key);

	void addEnemy(Character&& enemy);

	std::string key1 = "011K";
	std::string key2 = "021K";
	std::string key3 = "031K";

	void reset();

	void initMaps();

	void initLevel10();

	void initLevel11();

	void initLevel20();

	void initLevel21();

	void initLevel30();

	void initLevel31();

	void initLevels();

	void initEnemies();

	void loadLocation(size_t index, Map& map, FightingScene& fight, size_t winStage, size_t defeatStage);

	void gamePlay(size_t choice);

	int MenuControl();

	void SaveControl();

	bool fileExists(const std::string& filename);

	void LoadControl(bool& gameActive);

	void start();
};

