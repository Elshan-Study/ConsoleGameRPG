#pragma once
#include "QuestStage.h"
#include "OptionChoice.h"
#include <memory>
#include <string>
#include <fstream>

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
    Quest();

    void addStage(std::unique_ptr<QuestStage> stage);

    void addOption(std::unique_ptr<OptionChoice> option);

    bool linkStageToOption(size_t stageIndex, size_t optionIndex);

    size_t getStageCount() const;

    size_t getOptionCount() const;

    QuestStage* getStage(size_t index) const;

    QuestStage* findStage(size_t index) const;

    OptionChoice* getOption(size_t index) const;

    void setStatus(QuestStatus status);
    int getStatus() const;
    void finish();
    bool finishStatus();

    void serialize(std::ostream& out) const;

    void deserialize(std::istream& in);


private:
    void resizeStages();

    void resizeOptions();
};
