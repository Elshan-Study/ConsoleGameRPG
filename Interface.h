#pragma once
#include <iostream>
#include "Character.h"
#include "Location.h"
#include <memory>
#include "QuestStage.h"

static void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

static bool isNumber(const std::string& str) {
	if (str.empty()) return false;
	for (char ch : str) {
		if (!isdigit(ch)) return false;
	}
	return true;
}

class Interface
{
public:
	Interface() {};
	virtual ~Interface() {};
};

class PCCharacterCreate final : public Interface
{
public:
	size_t experience = 100;

	PCCharacterCreate() {};

	void ArchetypeChoice(Character& PC);

	void SpecializationChoice(Character& PC);

	void CharacteristicsEdit(Character& PC, size_t& experience);

	void SkillEdit(Character& PC, size_t& experience);

	void MainChoice(Character& PC);

	void CharacterEdit(Character& PC);

	void StartItemSet(Character& PC);
	
	void initialize(Character& PC);

	void TestPC(Character& PC);

};

class MainMenu final : public Interface
{
public:
	MainMenu() {};

	static int show()
	{
		int choice = 0;
		while (true)
		{
			std::cout << "Amazing Adventure\n";
			std::cout << "_________________________________________________\n";
			std::cout << "Main menu: \n";
			std::cout << "1. New Game\n";
			std::cout << "2. Continue Game\n";
			std::cout << "3. Save Game\n";
			std::cout << "4. Load Game\n";
			std::cout << "5. Exit\n";
			std::string input;
			std::cout << "Your choice: ";
			std::getline(std::cin, input);

			if (!isNumber(input)) {
				std::cout << "Wrong input!\n"; continue;
			}

			choice = std::stoi(input);
			if (choice < 1 || choice > 5) {
				std::cout << "Wrong choice!\n"; continue;
			}

			break;
		}

		return choice;

	}
};

class InsideGameMenu final : public Interface
{
public:
	InsideGameMenu() {};

	static int show()
	{
		int choice = 0;

		while (true)
		{
			std::cout << "1. Restore AP\n";
			std::cout << "2. Restore HP\n";
			std::cout << "3. Restore Armor\n";
			std::cout << "4. Visit Capital City\n";
			std::cout << "5. Visit Outskirts\n";
			std::cout << "6. Visit Black Mountain\n";
			std::cout << "7. Return to main menu\n";
			std::string input;
			std::cout << "Your choice: ";
			std::getline(std::cin, input);

			if (!isNumber(input)) {
				std::cout << "Wrong input!\n"; continue;
			}

			choice = std::stoi(input);
			if (choice < 1 || choice > 7) {
				std::cout << "Wrong choice!\n"; continue;
			}

			break;
		}

		return choice;
	}
};

class MapMenu final : public Interface
{
public:
	MapMenu() {};

	int show(Map& map)
	{
		int choice = 0;

		while (true)
		{
			for (size_t i = 0; i < map.getSize(); ++i)
			{
				std::cout << (i + 1) << ". " << map[i]->getName() << "\n";
			}
			std::cout << (map.getSize() + 1) << ". Return to menu\n";

			std::string input;
			std::cout << "Your choice: ";
			std::getline(std::cin, input);

			if (!isNumber(input)) {
				std::cout << "Wrong input!\n";
				continue;
			}

			choice = std::stoi(input);
			if (choice < 1 || choice > static_cast<int>(map.getSize() + 1)) {
				std::cout << "Wrong choice!\n";
				continue;
			}

			break;
		}

		return choice;
	}

};

class FightingScene final : public Interface
{
public:
	enum InitiativeSkill { Vigilance, Cool };
	enum EnemyBehavior { MeleeMod, BalanceMod, RangeMod };

private:
	Character* Enemy;
	Character& PC;
	size_t distanceBetween;
	size_t distanceMax;
	size_t initiativeSkill;
	size_t enemyBehavior;
	size_t coercionDiff;

	enum class CharacterQueue { PC, Enemy };

public:
	FightingScene(Character* enemy, Character& pc, size_t distanceBetween, size_t distanceMax, size_t coercionDiff, size_t initSkill, size_t behavior);


	bool isClose() const;

	void enemyMelee(size_t itemIndex);

	void enemyRanged(size_t itemIndex);

	void recoverEnemy() { Enemy->recoverHP(); }

	CharacterQueue initiativeCheck();

	bool start();
};

class SceneControl final : public Interface
{
public:

	enum class NPCSceneReaction
	{
		DefaultReaction = 10,
		WaitingReaction = 30,
		DefeatReaction = 40,
		WinReaction = 50
	};

	bool loadNPCScene(QuestGetPointer*& location, size_t questStatus, size_t questQetStage);

	bool loadQuest(Character& PC, QuestPointer*& location, FightingScene& fighting, size_t startStage, size_t winStage, size_t defeatStage);

};

class SaveLoadMenu final : public Interface
{
public:
	static int showSaves()
	{
		int choice = 0;
		while (true)
		{
			std::cout << "Save Menu\n";
			std::cout << "1. Save in Slot 1\n";
			std::cout << "2. Save in Slot 2\n";
			std::cout << "3. Save in Slot 3\n";
			std::cout << "4. Exit\n";
			std::string input;
			std::cout << "Your choice: ";
			std::getline(std::cin, input);

			if (!isNumber(input)) {
				std::cout << "Wrong input!\n"; continue;
			}

			choice = std::stoi(input);
			if (choice < 1 || choice > 4) {
				std::cout << "Wrong choice!\n"; continue;
			}

			break;
		}

		return choice;
	};

	static int showLoads()
	{
		int choice = 0;
		while (true)
		{
			std::cout << "Save Menu\n";
			std::cout << "1. Load Slot 1\n";
			std::cout << "2. Load Slot 2\n";
			std::cout << "3. Load Slot 3\n";
			std::cout << "4. Load Autosave\n";
			std::cout << "5. Exit\n";
			std::string input;
			std::cout << "Your choice: ";
			std::getline(std::cin, input);

			if (!isNumber(input)) {
				std::cout << "Wrong input!\n"; continue;
			}

			choice = std::stoi(input);
			if (choice < 1 || choice > 5) {
				std::cout << "Wrong choice!\n"; continue;
			}

			break;
		}

		return choice;
	};
};

