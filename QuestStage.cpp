#include "QuestStage.h"

//std::unique_ptr<QuestStage> QuestStage::deserialize(std::istream& in, Character& Main) {
//    std::string type = readString(in);
//    std::string name = readString(in);
//
//    size_t mainIndex, nextIndex, cost;
//    in.read(reinterpret_cast<char*>(&mainIndex), sizeof(mainIndex));
//    in.read(reinterpret_cast<char*>(&nextIndex), sizeof(nextIndex));
//    in.read(reinterpret_cast<char*>(&cost), sizeof(cost));
//
//    if (type == "TextStage") {
//        return std::make_unique<TextStage>(name, mainIndex, nextIndex, cost, Main);
//    }
//    else if (type == "AttackStage") {
//        size_t successDiff;
//        in.read(reinterpret_cast<char*>(&successDiff), sizeof(successDiff));
//        return std::make_unique<AttackStage>(name, mainIndex, nextIndex, cost, successDiff, Main);
//    }
//    else if (type == "skillCheckStage") {
//        size_t successDiff, numDice;
//        in.read(reinterpret_cast<char*>(&successDiff), sizeof(successDiff));
//        in.read(reinterpret_cast<char*>(&numDice), sizeof(numDice));
//        return std::make_unique<skillCheckStage>(name, mainIndex, nextIndex, cost, successDiff, Main, numDice);
//    }
//    else if (type == "useQuestItemStage") {
//        std::string itemName = readString(in);
//        return std::make_unique<useQuestItemStage>(name, mainIndex, nextIndex, Main, itemName);
//    }
//    else if (type == "giveItemStage") {
//        std::unique_ptr<Item> item = Item::Deserialize(in);
//        return std::make_unique<giveItemStage>(name, mainIndex, nextIndex, cost, Main, std::move(item));
//    }
//
//    std::cerr << "Unknown QuestStage type: " << type << std::endl;
//    return nullptr;
//}