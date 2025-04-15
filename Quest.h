#pragma once
#include <memory>
#include "QuestStage.h"
#include "OptionChoice.h"

class Quest {
private:
    std::unique_ptr<std::unique_ptr<QuestStage>[]> stages;
    std::unique_ptr<std::unique_ptr<OptionChoice>[]> options;
    size_t stageCapacity;
    size_t optionCapacity;
    size_t stageSize;
    size_t optionSize;

public:
    Quest()
        : stageCapacity(10), optionCapacity(10), stageSize(0), optionSize(0) {
        stages = std::make_unique<std::unique_ptr<QuestStage>[]>(stageCapacity);
        options = std::make_unique<std::unique_ptr<OptionChoice>[]>(optionCapacity);
    }

    explicit Quest(size_t stageCap, size_t optionCap)
        : stageCapacity(stageCap), optionCapacity(optionCap), stageSize(0), optionSize(0) {
        stages = std::make_unique<std::unique_ptr<QuestStage>[]>(stageCapacity);
        options = std::make_unique<std::unique_ptr<OptionChoice>[]>(optionCapacity);
    }

    Quest(Quest&& other) noexcept
        : stages(std::move(other.stages)),
        options(std::move(other.options)),
        stageCapacity(other.stageCapacity),
        optionCapacity(other.optionCapacity),
        stageSize(other.stageSize),
        optionSize(other.optionSize) {
        other.stageCapacity = 0;
        other.optionCapacity = 0;
        other.stageSize = 0;
        other.optionSize = 0;
    }

    Quest& operator=(Quest&& other) noexcept {
        if (this == &other) return *this;

        stages = std::move(other.stages);
        options = std::move(other.options);
        stageCapacity = other.stageCapacity;
        optionCapacity = other.optionCapacity;
        stageSize = other.stageSize;
        optionSize = other.optionSize;

        other.stageCapacity = 0;
        other.optionCapacity = 0;
        other.stageSize = 0;
        other.optionSize = 0;

        return *this;
    }

    bool addStage(std::unique_ptr<QuestStage> stage) {
        if (stageSize < stageCapacity) {
            stages[stageSize++] = std::move(stage);
            return true;
        }
        return false;
    }

    bool addOptionChoice(std::unique_ptr<OptionChoice> option) {
        if (optionSize < optionCapacity) {
            options[optionSize++] = std::move(option);
            return true;
        }
        return false;
    }

    bool connectStageToChoice(size_t stageIndex, size_t optionIndex) {
        if (stageIndex >= stageSize || optionIndex >= optionSize || !stages[stageIndex]) {
            return false;
        }

        auto sharedIndex = std::make_shared<size_t>(stages[stageIndex]->getIndex());
        return options[optionIndex] ? options[optionIndex]->addChoice(sharedIndex) : false;
    }

    size_t getStageSize() const { return stageSize; }
    size_t getOptionSize() const { return optionSize; }

    QuestStage* getStage(size_t index) {
        return (index < stageSize && stages[index]) ? stages[index].get() : nullptr;
    }

    OptionChoice* getOption(size_t index) {
        return (index < optionSize && options[index]) ? options[index].get() : nullptr;
    }
};
