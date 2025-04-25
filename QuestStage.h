#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "Character.h"
#include "Item.h"

//static void writeString(std::ostream& out, const std::string& str) {
//    size_t len = str.size();
//    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
//    out.write(str.c_str(), len);
//}
//
//static std::string readString(std::istream& in) {
//    size_t len;
//    in.read(reinterpret_cast<char*>(&len), sizeof(len));
//    std::string str(len, '\0');
//    in.read(&str[0], len);
//    return str;
//}

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

    virtual void serialize(std::ostream& out) const = 0;
    virtual std::string getTypeName() const = 0;

    /*static std::unique_ptr<QuestStage> deserialize(std::istream& in, Character& Main);*/
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

    //void serialize(std::ostream& out) const override {
    //    writeString(out, getTypeName());
    //    writeString(out, name);
    //    out.write(reinterpret_cast<const char*>(&mainIndex), sizeof(mainIndex));
    //    out.write(reinterpret_cast<const char*>(&nextIndex), sizeof(nextIndex));
    //    out.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
    //}

    std::string getTypeName() const override { return "TextStage"; }
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

    /*void serialize(std::ostream& out) const override {
        writeString(out, getTypeName());
        writeString(out, name);
        out.write(reinterpret_cast<const char*>(&mainIndex), sizeof(mainIndex));
        out.write(reinterpret_cast<const char*>(&nextIndex), sizeof(nextIndex));
        out.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
        out.write(reinterpret_cast<const char*>(&successDiff), sizeof(successDiff));
    }*/

    std::string getTypeName() const override { return "AttackStage"; }
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

    /*void serialize(std::ostream& out) const override {
        writeString(out, getTypeName());
        writeString(out, name);
        out.write(reinterpret_cast<const char*>(&mainIndex), sizeof(mainIndex));
        out.write(reinterpret_cast<const char*>(&nextIndex), sizeof(nextIndex));
        writeString(out, itemName);
    }*/

    std::string getTypeName() const override { return "useQuestItemStage"; }
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

    /*void serialize(std::ostream& out) const override {
        writeString(out, getTypeName());
        writeString(out, name);
        out.write(reinterpret_cast<const char*>(&mainIndex), sizeof(mainIndex));
        out.write(reinterpret_cast<const char*>(&nextIndex), sizeof(nextIndex));
        out.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
        out.write(reinterpret_cast<const char*>(&successDiff), sizeof(successDiff));
        out.write(reinterpret_cast<const char*>(&numDice), sizeof(numDice));
    }*/

    std::string getTypeName() const override { return "skillCheckStage"; }
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

    /*void serialize(std::ostream& out) const override {
        writeString(out, getTypeName());
        writeString(out, name);
        out.write(reinterpret_cast<const char*>(&mainIndex), sizeof(mainIndex));
        out.write(reinterpret_cast<const char*>(&nextIndex), sizeof(nextIndex));
        out.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
        if (item) {
            item->Serialize(out);
        }
    }*/

    std::string getTypeName() const override { return "giveItemStage"; }
};
