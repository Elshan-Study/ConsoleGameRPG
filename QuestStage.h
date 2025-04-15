#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Character.h"

class QuestStage
{
protected:
	size_t index;
public:
	QuestStage() : index(0) {};
	explicit QuestStage(size_t index) : index(index) {};
	virtual ~QuestStage() = default;
    size_t getIndex() const { return index; }
};

class TextStage final : public QuestStage
{
private:
	std::string filename;
public:
    explicit TextStage(const std::string& filename, size_t index) :
        QuestStage(index), filename(filename) {};

    bool on()
    {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Can't open the file!" << std::endl;
            return 0;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();

    }
};

class AttackStage : public QuestStage
{
private:
    std::string name;
    size_t successDiff;
    size_t cost;
public:
    explicit AttackStage(const std::string& name, size_t index, size_t cost, size_t successDiff) :
        QuestStage(index), name(name), successDiff(successDiff), cost(cost) {
    };

    enum class WeaponStatus
    {
        Mellee,
        Ranged
    };

    bool on(Character& Main, Character& Target, WeaponStatus status)
    {
        bool trueWeapon = false;
        size_t itemIndex = 0;

        for (size_t i = 0; i < Main.inventory.getSize(); i++)
        {
            if (status == WeaponStatus::Ranged && Main.inventory[i]->Name() == "Bow") {
                trueWeapon = true;
                itemIndex = i;
                break;
            }     
            else if (status == WeaponStatus::Mellee && Main.inventory[i]->Name() != "Bow") {
                trueWeapon = true;
                itemIndex = i;
                break;
            }
        }

        size_t dices = status == WeaponStatus::Mellee ? Main.melee() : Main.ranged();

        if (Main.currentAP <= cost)
        {
            Main.attack(Target, trueWeapon, itemIndex, dices, successDiff);
            Main.inventory.CheckInventory();
            Main.currentAP -= cost;
            return 1;
        }
        
        return 0;
    }
};

class useQuestItemStage : public QuestStage
{
private:
    std::string name;
    size_t successDiff;
    size_t cost;
public:
    explicit useQuestItemStage(const std::string& name, size_t index, size_t cost, size_t successDiff) :
        QuestStage(index), name(name), successDiff(successDiff), cost(cost) {
    };

    bool on(Character& Main, const std::string& name)
    {
        for (size_t i = 0; i < Main.inventory.getSize(); i++)
        {
            if (Main.inventory[i]->Name() == name) {
                Main.useItem(0, name);
                Main.inventory.CheckInventory();
                return 1;
            }
            return 0;
        }
    }
};

class skillCheckStage : public QuestStage
{
private:
    std::string name;
    size_t successDiff;
    size_t cost;
public:
    explicit skillCheckStage(const std::string& name, size_t index, size_t cost, size_t successDiff) :
        QuestStage(index), name(name), successDiff(successDiff), cost(cost) {
    };

    bool on(Character& Main, size_t numDice, size_t successDiff)
    {
        if (Main.currentAP <= cost)
        {
            Main.currentAP -= cost;
            return Main.skillCheck(numDice, successDiff);
        }

        return 0;
    }
};

class giveItemStage : public QuestStage
{
private:
    std::string name;
    size_t successDiff;
    size_t cost;
public:
    explicit giveItemStage(const std::string& name, size_t index, size_t cost, size_t successDiff) :
        QuestStage(index), name(name), successDiff(successDiff), cost(cost) {
    };

    bool on(Character& Main, std::unique_ptr<Item> item)
    {
        if (Main.currentAP <= cost)
        {
            Main.currentAP -= cost;
            Main.inventory.addItem(std::move(item));
        }
        return true;
    }
};