#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "Character.h"
#include "Item.h"

class QuestStage {
protected:
    std::string name;
    size_t mainIndex;
    size_t cost;

public:
    size_t nextIndex;

    QuestStage() : name("Not set"), mainIndex(0), nextIndex(0), cost(0) {}
    explicit QuestStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost)
        : name(name), mainIndex(mainIndex), nextIndex(nextIndex), cost(cost) {
    }

    virtual ~QuestStage() = default;

    virtual bool on() = 0;
    size_t getIndex() const { return mainIndex; }
    std::string showName() const { return name; }
};

class TextStage final : public QuestStage {
private:
    Character& Main;

public:
    TextStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, Character& Main)
        : QuestStage(name, mainIndex, nextIndex, cost), Main(Main) {
    }

    bool on() override {
        if (Main.currentAP >= cost) {
            Main.currentAP -= cost;
            return true;
        }
        return false;
    }
};

class AttackStage : public QuestStage {
private:
    size_t successDiff;
    Character& Main;

public:
    AttackStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t successDiff, Character& Main)
        : QuestStage(name, mainIndex, nextIndex, cost), successDiff(successDiff), Main(Main) {
    }

    bool on() override {
        if (Main.currentAP >= cost) {
            Main.currentAP -= cost;
            return true;
        }
        return false;
    }
};

class useQuestItemStage : public QuestStage {
private:
    Character& Main;
    std::string itemName;

public:
    useQuestItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, Character& Main, const std::string& itemName)
        : QuestStage(name, mainIndex, nextIndex, 0), Main(Main), itemName(itemName) {
    }

    bool on() override {
        for (size_t i = 0; i < Main.inventory.getSize(); i++) {
            if (Main.inventory[i]->Name() == itemName) {
                Main.useItem(0, itemName);
                Main.inventory.CheckInventory();
                return true;
            }
        }
        return false;
    }
};

class skillCheckStage : public QuestStage {
private:
    size_t successDiff;
    Character& Main;
    size_t numDice;

public:
    skillCheckStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t successDiff, Character& Main, size_t numDice)
        : QuestStage(name, mainIndex, nextIndex, cost), successDiff(successDiff), Main(Main), numDice(numDice) {
    }

    bool on() override {
        if (Main.currentAP >= cost) {
            Main.currentAP -= cost;
            return Main.skillCheck(numDice, successDiff);
        }
        return false;
    }
};

class giveItemStage : public QuestStage {
private:
    Character& Main;
    std::unique_ptr<Item> item;

public:
    giveItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, Character& Main, std::unique_ptr<Item> item)
        : QuestStage(name, mainIndex, nextIndex, cost), Main(Main), item(std::move(item)) {
    }

    bool on() override {
        if (Main.currentAP >= cost) {
            Main.currentAP -= cost;
            Main.inventory.addItem(std::move(item));
        }
        return true;
    }
};
