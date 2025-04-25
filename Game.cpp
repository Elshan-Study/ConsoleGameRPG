#include "Game.h"

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
			createPC.initialize(PC);
			/*createPC.TestPC(PC);*/
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
				if (switchControl == 6) { break; }
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