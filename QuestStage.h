#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Character.h"

class QuestStage
{
protected:
	size_t mainIndex;
    size_t cost;
public:
    size_t nextIndex;
	QuestStage() : mainIndex(0), nextIndex(0), cost(0) {};
	explicit QuestStage(size_t mainIndex, size_t nextIndex, size_t cost) : mainIndex(mainIndex), nextIndex(nextIndex), cost(cost) {};
	virtual ~QuestStage() = default;
    virtual bool on() = 0;
    size_t getIndex() const { return mainIndex; }
};

class TextStage final : public QuestStage
{
private:
	std::string filename;
public:
    explicit TextStage(const std::string& filename, size_t mainIndex, size_t nextIndex, size_t cost) :
        QuestStage(mainIndex, nextIndex, cost), filename(filename) {};

    bool on() override
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
public:
    enum WeaponStatus
    {
        Default,
        Mellee,
        Ranged
    };
private:
    std::string name;
    size_t successDiff;
    WeaponStatus status;
    Character& Main;
    Character& Target;
public:
    explicit AttackStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, 
        size_t successDiff, Character& Main, Character& Target) :
        QuestStage(mainIndex, nextIndex, cost), name(name), successDiff(successDiff), 
        status(WeaponStatus::Default), Main(Main), Target(Target) {
    };

    bool on() override
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
    Character& Main;
    std::string itemName;
public:
    explicit useQuestItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, 
        size_t successDiff, Character& Main, const std::string& itemName) :
        QuestStage(mainIndex, nextIndex, cost), name(name), successDiff(successDiff),
        Main(Main), itemName(itemName) {
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
    std::string name;
    size_t successDiff;
    Character& Main;
    size_t numDice;
public:
    explicit skillCheckStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, 
        size_t successDiff, Character& Main, size_t numDice) :
        QuestStage(mainIndex, nextIndex, cost), name(name), successDiff(successDiff),
        Main(Main), numDice(numDice){
    };

    bool on() override
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
    Character& Main;
    std::unique_ptr<Item> item;
public:
    explicit giveItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t successDiff,
        Character& Main, std::unique_ptr<Item> item) :
        QuestStage(mainIndex, nextIndex, cost), name(name), successDiff(successDiff),
        Main(Main), item(std::move(item)){};

    bool on() override
    {
        if (Main.currentAP <= cost)
        {
            Main.currentAP -= cost;
            Main.inventory.addItem(std::move(item));
        }
        return true;
    }
};
