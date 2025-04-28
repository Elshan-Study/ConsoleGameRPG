#include "GameDataManager.h"
#include "Game.h"

void GameDataManager::SaveGame(const Game& game, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary);

    if (!outFile) {
        std::cerr << "Error opening file for saving game." << std::endl;
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&game.keySize), sizeof(game.keySize));
    outFile.write(reinterpret_cast<const char*>(&game.enemySize), sizeof(game.enemySize));
    outFile.write(reinterpret_cast<const char*>(&game.winCount), sizeof(game.winCount));
    outFile.write(reinterpret_cast<const char*>(&game.defeatCount), sizeof(game.defeatCount));

    for (size_t i = 0; i < game.QUESTCOUNT; ++i) {
        size_t keyLength = game.keys[i].size();
        outFile.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
        outFile.write(game.keys[i].c_str(), keyLength);
    }

    for (size_t i = 0; i < game.ENEMYCOUNT; ++i) {
        game.enemies[i].serialize(outFile);  
    }

    game.PC.serialize(outFile); 

    outFile.close();
}

void GameDataManager::SaveLocationsStatus(const Game& game, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary);

    if (!outFile) {
        std::cerr << "Error opening file for saving game." << std::endl;
        return;
    }

    game.CapitalCity.serialize(outFile);
    game.Outskirts.serialize(outFile);
    game.BlackMountain.serialize(outFile); 

    outFile.close();
}


void GameDataManager::LoadGame(Game& game, const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary);

    if (!inFile) {
        std::cerr << "Error opening file for loading game." << std::endl;
        return;
    }

    inFile.read(reinterpret_cast<char*>(&game.keySize), sizeof(game.keySize));
    inFile.read(reinterpret_cast<char*>(&game.enemySize), sizeof(game.enemySize));
    inFile.read(reinterpret_cast<char*>(&game.winCount), sizeof(game.winCount));
    inFile.read(reinterpret_cast<char*>(&game.defeatCount), sizeof(game.defeatCount));

    for (size_t i = 0; i < game.QUESTCOUNT; ++i) {
        size_t keyLength;
        inFile.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));
        game.keys[i].resize(keyLength);
        inFile.read(&game.keys[i][0], keyLength);
    }

    for (size_t i = 0; i < game.ENEMYCOUNT; ++i) {
        game.enemies[i].deserialize(inFile); 
    }

    game.PC.deserialize(inFile); 

    inFile.close();
}

void GameDataManager::LoadLocationsStatus(Game& game, const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary);

    if (!inFile) {
        std::cerr << "Error opening file for loading game." << std::endl;
        return;
    }

    game.CapitalCity.deserialize(inFile);
    game.Outskirts.deserialize(inFile);
    game.BlackMountain.deserialize(inFile);

    inFile.close();

}

