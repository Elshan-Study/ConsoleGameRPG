#pragma once
#include <string>
#include <fstream>
class Game;

class GameDataManager
{
public:
    static void SaveGame(const Game& game, const std::string& filename);
    static void LoadGame(Game& game, const std::string& filename);
};

