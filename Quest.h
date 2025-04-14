#pragma once
#include <iostream>
#include <string>
#include "Character.h"

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
public:
	Quest() : title("Unknown"), isFinished(false), currentStatus(Status::Default) {};
	Quest(const std::string& title) : title(title), isFinished(false), currentStatus(Status::Default) {};

	virtual ~Quest() = 0;

	virtual void startQuest(Character& PC) = 0;

	void Win() { currentStatus = Status::Victory; }
	void Defeat() { currentStatus = Status::Defeat; }
};