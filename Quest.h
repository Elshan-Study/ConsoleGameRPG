#pragma once
#include "QuestStage.h"
#include "OptionChoice.h"

class Quest {
private:
    QuestStage** stages;
    OptionChoice** options;
    size_t stageCapacity;
    size_t optionCapacity;
    size_t stageSize;
    size_t optionSize;

public:
    Quest()
        : stages(nullptr), options(nullptr),
        stageCapacity(10), optionCapacity(10),
        stageSize(0), optionSize(0) {
    }

    ~Quest() {
        for (size_t i = 0; i < stageSize; ++i) {
            delete stages[i];
        }
        delete[] stages;

        for (size_t i = 0; i < optionSize; ++i) {
            delete options[i];
        }
        delete[] options;
    }

    void addStage(QuestStage* stage) {
        if (stageSize >= stageCapacity) {
            resizeStages();
        }
        stages[stageSize++] = stage;
    }

    void addOption(OptionChoice* option) {
        if (optionSize >= optionCapacity) {
            resizeOptions();
        }
        options[optionSize++] = option;
    }

    bool linkStageToOption(size_t stageIndex, size_t optionIndex) {
        if (stageIndex >= stageSize || optionIndex >= optionSize) {
            return false;
        }

        size_t targetStageIndex = stages[stageIndex]->getIndex();
        return options[optionIndex]->addChoice(std::make_shared<size_t>(targetStageIndex));
    }

    size_t getStageCount() const {
        return stageSize;
    }

    size_t getOptionCount() const {
        return optionSize;
    }

    QuestStage* getStage(size_t index) const {
        if (index < stageSize) return stages[index];
        return nullptr;
    }

    OptionChoice* getOption(size_t index) const {
        if (index < optionSize) return options[index];
        return nullptr;
    }

private:
    void resizeStages() {
        size_t newCapacity = stageCapacity == 0 ? 4 : stageCapacity * 2;
        QuestStage** newArray = new QuestStage * [newCapacity];

        for (size_t i = 0; i < stageSize; ++i) {
            newArray[i] = stages[i];
        }

        delete[] stages;
        stages = newArray;
        stageCapacity = newCapacity;
    }

    void resizeOptions() {
        size_t newCapacity = optionCapacity == 0 ? 4 : optionCapacity * 2;
        OptionChoice** newArray = new OptionChoice * [newCapacity];

        for (size_t i = 0; i < optionSize; ++i) {
            newArray[i] = options[i];
        }

        delete[] options;
        options = newArray;
        optionCapacity = newCapacity;
    }
};
