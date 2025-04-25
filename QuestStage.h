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

    QuestStage();
    explicit QuestStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost);

    virtual ~QuestStage() = default;

    virtual bool on() = 0;
    size_t getIndex() const;
    std::string showName() const;
};

class TextStage final : public QuestStage {
private:
    Character& Main;

public:
    TextStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, Character& Main);

    bool on() override;
};

class AttackStage : public QuestStage {
private:
    size_t successDiff;
    Character& Main;

public:
    AttackStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t successDiff, Character& Main);

    bool on() override;
};

class useQuestItemStage : public QuestStage {
private:
    Character& Main;
    std::string itemName;

public:
    useQuestItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, Character& Main, const std::string& itemName);

    bool on() override;
};

class skillCheckStage : public QuestStage {
private:
    size_t successDiff;
    Character& Main;
    size_t numDice;

public:
    skillCheckStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t successDiff, Character& Main, size_t numDice);

    bool on() override;
};

class giveItemStage : public QuestStage {
private:
    Character& Main;
    std::unique_ptr<Item> item;

public:
    giveItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, Character& Main, std::unique_ptr<Item> item);

    bool on() override;
};
