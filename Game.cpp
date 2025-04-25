#include "Game.h"

void Game::start()
{
	while (true)
	{
		int choice = menu.show();
		clearScreen();

		switch (choice)
		{
		case 1:
			/*createPC.initialize(PC);*/
			createPC.TestPC(PC);
			std::cout << "Character Create Successfully" << std::endl;
			initEnemies();
			CapitalCity.setMain("Capital City", "capitalCity.txt");
			initLevels();
			clearScreen();
			while (true)
			{
				int switchControl = MenuControl();
				if (switchControl == 6) { break; }
			}
			break;
		case 2:
			GameDataManager::LoadGame(*this, "autosave2.bin");
			CapitalCity.setMain("Capital City", "capitalCity.txt");
			initLevels();
			std::cout << CapitalCity.getSize() << std::endl;
			GameDataManager::LoadLocationsStatus(*this, "autosaveLocStatus.bin");

			while (true)
			{

				int switchControl = MenuControl();
				if (switchControl == 6) { break; }
			}
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			GameDataManager::SaveGame(*this, "autosave2.bin");
			GameDataManager::SaveLocationsStatus(*this, "autosaveLocStatus.bin");
			return;
		default:
			break;
		}
	}
}