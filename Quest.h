#pragma once
#include "QuestStage.h"
#include "OptionChoice.h"
#include <memory>
#include <string>

class Quest {
public:
    enum QuestStatus
    {
        neutral,
        win,
        defeat
    };
private:
    std::unique_ptr<std::unique_ptr<QuestStage>[]> stages;
    std::unique_ptr<std::unique_ptr<OptionChoice>[]> options;
    size_t stageCapacity;
    size_t optionCapacity;
    size_t stageSize;
    size_t optionSize;
    bool isFinished;
    int status = QuestStatus::neutral;

public:
    Quest()
        : stageCapacity(0), optionCapacity(0),
        stageSize(0), optionSize(0), isFinished(false) {
    }

    void addStage(std::unique_ptr<QuestStage> stage) {
        if (stageSize >= stageCapacity) {
            resizeStages();
        }
        stages[stageSize++] = std::move(stage);
    }

    void addOption(std::unique_ptr<OptionChoice> option) {
        if (optionSize >= optionCapacity) {
            resizeOptions();
        }
        options[optionSize++] = std::move(option);
    }

    bool linkStageToOption(size_t stageIndex, size_t optionIndex) {
        if (stageIndex >= stageSize || optionIndex >= optionSize) {
            return false;
        }

        size_t targetStageIndex = stages[stageIndex]->getIndex();
        return options[optionIndex]->addChoice(targetStageIndex);
    }

    size_t getStageCount() const {
        return stageSize;
    }

    size_t getOptionCount() const {
        return optionSize;
    }

    QuestStage* getStage(size_t index) const {
        if (index < stageSize) return stages[index].get();
        return nullptr;
    }

    QuestStage* findStage(size_t index) const {
        for (size_t i = 0; i < stageSize; i++)
        {
            if (stages[i]->getIndex() == index)
            {
                return stages[i].get();
            }
        }
        return nullptr;
    }

    OptionChoice* getOption(size_t index) const {
        if (index < optionSize) return options[index].get();
        return nullptr;
    }

    void setStatus(QuestStatus status) { this->status = status; }
    int getStatus() const { return status; }
    void finish() { isFinished = true; }
    bool finishStatus() { return isFinished; }


private:
    void resizeStages() {
        size_t newCapacity = stageCapacity == 0 ? 4 : stageCapacity * 2;
        auto newArray = std::make_unique<std::unique_ptr<QuestStage>[]>(newCapacity);

        for (size_t i = 0; i < stageSize; ++i) {
            newArray[i] = std::move(stages[i]);
        }

        stages = std::move(newArray);
        stageCapacity = newCapacity;
    }

    void resizeOptions() {
        size_t newCapacity = optionCapacity == 0 ? 4 : optionCapacity * 2;
        auto newArray = std::make_unique<std::unique_ptr<OptionChoice>[]>(newCapacity);

        for (size_t i = 0; i < optionSize; ++i) {
            newArray[i] = std::move(options[i]);
        }

        options = std::move(newArray);
        optionCapacity = newCapacity;
    }
};