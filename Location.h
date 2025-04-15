#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Quest.h"
class Location
{
protected:
    std::string name;
	std::string description_file;
public:
	Location() : name("Unknown"), description_file("Unknown") {};
    explicit Location(const std::string& name, const std::string& filename) : name(name), description_file(filename) {};
	virtual ~Location() = default;

    virtual void activate(const std::string& key) = 0;
    virtual bool status() const = 0;

    void setMain(const std::string& name, const std::string& filename) { this->name = name, description_file = filename; }

	void readDescription()
	{
        std::ifstream file(description_file); 

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

class QuestGetPointer final : public Location
{
private:
    std::string key;
    bool isQuestQet;
    Quest quest;
public:
    explicit QuestGetPointer(const std::string& name, const std::string& description_filename,
        const std::string& key, size_t stageCap, size_t optionCap)
        : Location(name, description_filename),
        key(key),
        isQuestQet(false)
    {};


    void activate(const std::string& key) override { isQuestQet = true; }
    bool status() const override { return isQuestQet; }

    void changeKey(const std::string& key) { this->key = key;}
    std::string getKey() const { if (isQuestQet) { return key; } else { "Error"; } }
};

class QuestPointer final : public Location
{
private:
    std::string lock;
    bool activate_status;
    Quest quest;
public:
    explicit QuestPointer(const std::string& name, const std::string& description_filename,
        const std::string& lock, size_t stageCap, size_t optionCap)
        : Location(name, description_filename),
        lock(lock),
        activate_status(false)
    {
    };

    void activate(const std::string& key) override
    {
        if (key == lock)
        {
            activate_status = true;
        }
    }
    bool status() const override { return activate_status; }
};

class Map final : public Location
{
protected:
    static const size_t MAX_LOCATION = 5;
    size_t size = 0;
    std::unique_ptr<Location> locations[MAX_LOCATION];
public:
    
    void activate(const std::string& key) override {};
    
    void addLocation(std::unique_ptr<Location> location)
    {
        if (size < MAX_LOCATION) {
            locations[size++] = std::move(location);
            return;
        }
        else 
        {
            std::cerr << "Map is full!\n";
        }
    }

    size_t getSize() const { return size; }

    std::unique_ptr<Location>& operator[](size_t index)
    {
        if (index >= MAX_LOCATION) {
            throw std::out_of_range("Index out of bounds");
        }
        if (index >= size) {
            size = index + 1;
        }
        return locations[index];
    }

    bool status() const override { return 0; };
};
