#include "QuestStage.h"

QuestStage::QuestStage() : name("Not set"), mainIndex(0), nextIndex(0), cost(0) {}
QuestStage::QuestStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost)
    : name(name), mainIndex(mainIndex), nextIndex(nextIndex), cost(cost) {
}
size_t QuestStage::getIndex() const { return mainIndex; }
std::string QuestStage::showName() const { return name; }

TextStage::TextStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, Character& Main)
    : QuestStage(name, mainIndex, nextIndex, cost), Main(Main) {
}
bool TextStage::on()  {
    if (Main.currentAP >= cost) {
        Main.currentAP -= cost;
        return true;
    }
    return false;
}

AttackStage::AttackStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t successDiff, Character& Main)
    : QuestStage(name, mainIndex, nextIndex, cost), successDiff(successDiff), Main(Main) {
}
bool AttackStage::on()  {
    if (Main.currentAP >= cost) {
        Main.currentAP -= cost;
        return true;
    }
    return false;
}


useQuestItemStage::useQuestItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, Character& Main, const std::string& itemName)
    : QuestStage(name, mainIndex, nextIndex, 0), Main(Main), itemName(itemName) {
}
bool useQuestItemStage::on()  {
    for (size_t i = 0; i < Main.inventory.getSize(); i++) {
        if (Main.inventory[i]->Name() == itemName) {
            Main.useItem(0, itemName);
            Main.inventory.CheckInventory();
            return true;
        }
    }
    return false;
}

skillCheckStage::skillCheckStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t badIndex, size_t cost, size_t successDiff, Character& Main, size_t numDice)
    : QuestStage(name, mainIndex, nextIndex, cost), successDiff(successDiff), badIndex(badIndex), Main(Main), numDice(numDice) {
}
bool skillCheckStage::on()  {
    if (Main.currentAP >= cost) {
        Main.currentAP -= cost;
        return Main.skillCheck(numDice, successDiff);
    }
    return false;
}

giveItemStage::giveItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, Character& Main, std::unique_ptr<Item> item)
        : QuestStage(name, mainIndex, nextIndex, cost), Main(Main), item(std::move(item)) {
    }
bool giveItemStage::on() {
        if (Main.currentAP >= cost) {
            Main.currentAP -= cost;
            Main.inventory.addItem(std::move(item));
        }
        return true;
    }

buyItemStage::buyItemStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t itemCost, Character& Main, std::shared_ptr<Item> item) 
    : QuestStage(name, mainIndex, nextIndex, cost), itemCost(itemCost), Main(Main), item(item) {
}

bool buyItemStage::on() {
    if (Main.money >= itemCost) {
        Main.money -= itemCost;

        if (item) {
            Main.inventory.addItem(item->clone());
        }

        return true;
    }
    return false;
}

RestStage::RestStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t serviceChoice, Character& Main)
    : QuestStage(name, mainIndex, nextIndex, cost), serviceChoice(serviceChoice), Main(Main) {
}

bool RestStage::on()
{
    if (serviceChoice == static_cast<size_t>(RestoreChoice::HPRestore))
    {
        Main.recoverHP();
    }
    else if (serviceChoice == static_cast<size_t>(RestoreChoice::APRestore))
    {
        Main.recoverAP();
    }
    else if (serviceChoice == static_cast<size_t>(RestoreChoice::ArmorHP))
    {
        for (size_t i = 0; i < Main.inventory.getSize(); ++i)
        {
            Item* item = Main.inventory[i].get();
            if (Armor* armor = dynamic_cast<Armor*>(item))
            {
                armor->recoverArmorHP();
            }
        }
    }

    return true;
}

DamageStage::DamageStage(const std::string& name, size_t mainIndex, size_t nextIndex, size_t cost, size_t damageChoice, int damageValue, Character& Main)
    : QuestStage(name, mainIndex, nextIndex, cost), damageChoice(damageChoice), damageValue(damageValue), Main(Main) {
}

bool DamageStage::on()
{
    if (damageChoice == static_cast<size_t>(DamageChoice::HPDamage))
    {
        Main.currentHP -= damageValue;
    }
    else if (damageChoice == static_cast<size_t>(DamageChoice::APDamage))
    {
        Main.currentAP -= damageValue;
    }

    return true;
}