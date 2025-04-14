#pragma once
#include <iostream>
#include <fstream>
#include <string>
class Location
{
protected:
    std::string name;
	std::string description_file;
public:
	Location() : name("Unknown"), description_file("Unknown") {};
	Location(const std::string& name, const std::string& filename) : name(name), description_file(filename) {};
	virtual ~Location() = default;

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
    /*Quest quest;*/
public:
    QuestGetPointer(const std::string& name, const std::string& description_filename, const std::string& key) : Location(name, description_filename), key(key) {};

    std::string getKey() const { return key; }
};

class QuestPointer final : public Location
{
private:
    std::string lock;
    bool activate_status;
    /*Quest quest;*/
public:
    QuestPointer(const std::string& name, const std::string& description_filename, const std::string& lock) : Location(name, description_filename), lock(lock), activate_status(false){};

    void Activate(const std::string& key)
    {
        if (key == lock)
        {
            activate_status = true;
        }
    }
};

class Map final : public Location
{
protected:
    static const size_t MAX_LOCATION = 5;
    size_t size;
    std::unique_ptr<Location> locations[MAX_LOCATION];
public:
    Map(const std::string& name, const std::string& description_filename) : Location(name, description_filename), size(0) {};
    
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
};
