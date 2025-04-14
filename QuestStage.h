#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "Interface.h"
class QuestStage
{
protected:
	size_t index;
    std::shared_ptr<OptionChoice> option;
public:
	QuestStage() : index(0) {};
	explicit QuestStage(size_t index, std::shared_ptr<OptionChoice> option) : index(index), option(option) {};
	virtual ~QuestStage() = default;
    size_t getIndex() const { return index; }
};

class TextStage final : public QuestStage
{
private:
	std::string filename;
public:
    explicit TextStage(const std::string& filename, size_t index, std::shared_ptr<OptionChoice> option) :
        QuestStage(index, option), filename(filename) {};

    void read()
    {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Can't open the file!" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    }
};

class ActionStage final : public QuestStage
{
private:
    std::string name;
    size_t dice;
public:
    explicit ActionStage(const std::string& name, size_t index, std::shared_ptr<OptionChoice> option) :
        QuestStage(index, option), name(name) {
    };

    
    }

    
};