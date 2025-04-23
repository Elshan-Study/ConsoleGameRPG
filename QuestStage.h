#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Character.h"

class QuestStage
{
protected:
    std::string name;
	size_t mainIndex;
    size_t cost;
public:
    size_t nextIndex;
	QuestStage() : name("Not set"), mainIndex(0), nextIndex(0), cost(0) {};
	explicit QuestStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost) : name(name), mainIndex(mainIndex), nextIndex(nextIndex), cost(cost) {};
	virtual ~QuestStage() = default;
    virtual bool on() = 0;
    size_t getIndex() const { return mainIndex; }
    std::string showName() const { return name; }
};

class TextStage final : public QuestStage
{
private:
    Character& Main;
public:
    explicit TextStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, Character& Main) :
        QuestStage(name, mainIndex, nextIndex, cost), Main(Main) {};

    bool on() override
    {
        if (Main.currentAP >= cost)
        {
            Main.currentAP -= cost;
            return 1;
        }
        else { return 0; }
    }
};

class AttackStage : public QuestStage
{
public:
    enum WeaponStatus
    {
        Default,
        Mellee,
        Ranged
    };
private:
    size_t successDiff;
   /* WeaponStatus status;*/
    Character& Main;
    /*Character& Target;*/
public:
    explicit AttackStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, 
        size_t successDiff, Character& Main/*, Character& Target*/) :
        QuestStage(name, mainIndex, nextIndex, cost), successDiff(successDiff), 
        /*status(WeaponStatus::Default),*/ Main(Main)/*, Target(Target)*/ {
    };

    bool on() override
    {
        /*DON'T USE IN CURRENT VERSION OF GAME*/

        /*bool trueWeapon = false;
        size_t itemIndex = 0;

        for (size_t i = 0; i < Main.inventory.getSize(); i++)
        {
            if (status == WeaponStatus::Ranged && (Main.inventory[i]->Name() == "Bow" || Main.inventory[i]->Name() == "Crossbow")) {
                trueWeapon = true;
                itemIndex = i;
                break;
            }     
            else if (status == WeaponStatus::Mellee && (Main.inventory[i]->Name() != "Sword" || Main.inventory[i]->Name() != "Knife")) {
                trueWeapon = true;
                itemIndex = i;
                break;
            }
        }

        size_t dices = status == WeaponStatus::Mellee ? Main.melee() : Main.ranged();*/

        if (Main.currentAP >= cost)
        {
           /* Main.attack(Target, trueWeapon, itemIndex, dices, successDiff);
            Main.inventory.CheckInventory();*/
            Main.currentAP -= cost;
            return 1;
        }
        
        return 0;
    }
};

class useQuestItemStage : public QuestStage
{
private:
    Character& Main;
    std::string itemName;
public:
    explicit useQuestItemStage(const std::string& name, size_t mainIndex, size_t nextIndex,
        Character& Main, const std::string& itemName) :
        QuestStage(name, mainIndex, nextIndex, 0), Main(Main), itemName(itemName) {
    };

    bool on() override
    {
        for (size_t i = 0; i < Main.inventory.getSize(); i++)
        {
            if (Main.inventory[i]->Name() == itemName) {
                Main.useItem(0, itemName);
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
    size_t successDiff;
    Character& Main;
    size_t numDice;
public:
    explicit skillCheckStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, 
        size_t successDiff, Character& Main, size_t numDice) :
        QuestStage(name, mainIndex, nextIndex, cost), successDiff(successDiff),
        Main(Main), numDice(numDice){
    };

    bool on() override
    {
        if (Main.currentAP >= cost)
        {
            Main.currentAP -= cost;
            bool check = Main.skillCheck(numDice, successDiff);
            return check;
        }

        return 0;
    }
};

class giveItemStage : public QuestStage
{
private:
    Character& Main;
    std::unique_ptr<Item> item;
public:
    explicit giveItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost,
        Character& Main, std::unique_ptr<Item> item) :
        QuestStage(name, mainIndex, nextIndex, cost), Main(Main), item(std::move(item)){};

    bool on() override
    {
        if (Main.currentAP >= cost)
        {
            Main.currentAP -= cost;
            Main.inventory.addItem(std::move(item));
        }
        return true;
    }
};
