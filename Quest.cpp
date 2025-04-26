#include "Quest.h"

Quest::Quest()
    : stageCapacity(0), optionCapacity(0),
    stageSize(0), optionSize(0), reward(0), isFinished(false) {
}

void Quest::addStage(std::unique_ptr<QuestStage> stage) {
    if (stageSize >= stageCapacity) {
        resizeStages();
    }
    stages[stageSize++] = std::move(stage);
}

void Quest::addOption(std::unique_ptr<OptionChoice> option) {
    if (optionSize >= optionCapacity) {
        resizeOptions();
    }
    options[optionSize++] = std::move(option);
}

void Quest::setReward(size_t money)
{
    reward = money;
}

bool Quest::linkStageToOption(size_t stageIndex, size_t optionIndex) {
    if (stageIndex >= stageSize || optionIndex >= optionSize) {
        return false;
    }

    size_t targetStageIndex = stages[stageIndex]->getIndex();
    return options[optionIndex]->addChoice(targetStageIndex);
}

size_t Quest::getStageCount() const {
    return stageSize;
}

size_t Quest::getOptionCount() const {
    return optionSize;
}

QuestStage* Quest::getStage(size_t index) const {
    if (index < stageSize) return stages[index].get();
    return nullptr;
}

size_t Quest::getReward() const
{
    return reward;
}

QuestStage* Quest::findStage(size_t index) const {
    for (size_t i = 0; i < stageSize; i++)
    {
        if (stages[i]->getIndex() == index)
        {
            return stages[i].get();
        }
    }
    return nullptr;
}

OptionChoice* Quest::getOption(size_t index) const {
    if (index < optionSize) return options[index].get();
    return nullptr;
}

void Quest::setStatus(QuestStatus status) { this->status = status; }
int Quest::getStatus() const { return status; }
void Quest::finish() { isFinished = true; }
bool Quest::finishStatus() { return isFinished; }

void Quest::serialize(std::ostream& out) const {
    out.write(reinterpret_cast<const char*>(&isFinished), sizeof(isFinished));
    out.write(reinterpret_cast<const char*>(&status), sizeof(status));
}

void Quest::deserialize(std::istream& in) {
    in.read(reinterpret_cast<char*>(&isFinished), sizeof(isFinished));
    in.read(reinterpret_cast<char*>(&status), sizeof(status));
}

void Quest::resizeStages() {
    size_t newCapacity = stageCapacity == 0 ? 4 : stageCapacity * 2;
    auto newArray = std::make_unique<std::unique_ptr<QuestStage>[]>(newCapacity);

    for (size_t i = 0; i < stageSize; ++i) {
        newArray[i] = std::move(stages[i]);
    }

    stages = std::move(newArray);
    stageCapacity = newCapacity;
}

void Quest::resizeOptions() {
    size_t newCapacity = optionCapacity == 0 ? 4 : optionCapacity * 2;
    auto newArray = std::make_unique<std::unique_ptr<OptionChoice>[]>(newCapacity);

    for (size_t i = 0; i < optionSize; ++i) {
        newArray[i] = std::move(options[i]);
    }

    options = std::move(newArray);
    optionCapacity = newCapacity;
}