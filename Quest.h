#pragma once
#include <iostream>
#include <string>
#include "QuestStage.h"
#include "OptionChoice.h"

class Quest
{
public:
	enum class Status {
		Default,
		Victory,
		Defeat
	};

protected:
	std::string title;
	bool isFinished;
	Status currentStatus;

	std::shared_ptr<std::shared_ptr<OptionChoice>[]> choices;
	std::shared_ptr<std::shared_ptr<QuestStage>[]> stages;

	size_t stagesSize;
	size_t stagesCapacity;

	size_t choicesSize;
	size_t choicesCapacity;

	void resizeStages() {
		size_t newCapacity = stagesCapacity * 2;
		auto newArray = std::shared_ptr<std::shared_ptr<QuestStage>[]>(new std::shared_ptr<QuestStage>[newCapacity]);
		for (size_t i = 0; i < stagesSize; ++i) {
			newArray[i] = stages[i];
		}
		stages = newArray;
		stagesCapacity = newCapacity;
	}

	void resizeChoices() {
		size_t newCapacity = choicesCapacity * 2;
		auto newArray = std::shared_ptr<std::shared_ptr<OptionChoice>[]>(new std::shared_ptr<OptionChoice>[newCapacity]);
		for (size_t i = 0; i < choicesSize; ++i) {
			newArray[i] = choices[i];
		}
		choices = newArray;
		choicesCapacity = newCapacity;
	}

public:
	Quest()
		: title("Unknown"),
		isFinished(false),
		currentStatus(Status::Default),
		stagesSize(0),
		stagesCapacity(4),
		choicesSize(0),
		choicesCapacity(4)
	{
		stages = std::shared_ptr<std::shared_ptr<QuestStage>[]>(new std::shared_ptr<QuestStage>[stagesCapacity]);
		choices = std::shared_ptr<std::shared_ptr<OptionChoice>[]>(new std::shared_ptr<OptionChoice>[choicesCapacity]);
	}

	explicit Quest(const std::string& title)
		: title(title),
		isFinished(false),
		currentStatus(Status::Default),
		stagesSize(0),
		stagesCapacity(4),
		choicesSize(0),
		choicesCapacity(4)
	{
		stages = std::shared_ptr<std::shared_ptr<QuestStage>[]>(new std::shared_ptr<QuestStage>[stagesCapacity]);
		choices = std::shared_ptr<std::shared_ptr<OptionChoice>[]>(new std::shared_ptr<OptionChoice>[choicesCapacity]);
	}

	virtual ~Quest() = 0;

	void Win() { currentStatus = Status::Victory; }
	void Defeat() { currentStatus = Status::Defeat; }

	void addStage(const std::shared_ptr<QuestStage>& stage) {
		if (stagesSize >= stagesCapacity) {
			resizeStages();
		}
		stages[stagesSize++] = stage;
	}

	void addChoice(const std::shared_ptr<OptionChoice>& choice) {
		if (choicesSize >= choicesCapacity) {
			resizeChoices();
		}
		choices[choicesSize++] = choice;
	}
};
