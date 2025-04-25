#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Quest.h"

class Location
{
protected:
    std::string name;
    std::string description_file;
    size_t finishStatus = 0;

public:
    enum class LocationType : uint8_t { Base, QuestPointer, QuestGetPointer, Map };

    Location() : name("Unknown"), description_file("Unknown") {};
    explicit Location(const std::string& name, const std::string& filename)
        : name(name), description_file(filename) {
    }
    virtual ~Location() = default;

    virtual void activate(const std::string& key) = 0;
    virtual bool status() const = 0;
    virtual LocationType getType() const = 0;

    virtual void serialize(std::ostream& out) const = 0;

    virtual void deserialize(std::istream& in) = 0;

    void setMain(const std::string& name, const std::string& filename) {
        this->name = name;
        description_file = filename;
    }

    std::string getName() const { return name; }

    void readDescription() {
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

    void setFinishStatus(size_t status) { finishStatus = status; }
    size_t getFinishStatus() const { return finishStatus; }
};

class QuestGetPointer final : public Location
{
private:
    std::string key;
    bool isQuestQet;

public:
    Quest quest;

    QuestGetPointer() : key(" "), isQuestQet(false) {};

    explicit QuestGetPointer(const std::string& name, const std::string& description_filename, const std::string& key)
        : Location(name, description_filename), key(key), isQuestQet(false) {
    }

    void activate(const std::string& key) override { isQuestQet = true; }
    bool status() const override { return isQuestQet; }
    LocationType getType() const override { return LocationType::QuestGetPointer; }

    void changeKey(const std::string& key) { this->key = key; }
    std::string getKey() const { return isQuestQet ? key : "Error"; }

    void serialize(std::ostream& out) const override {
        out.write(reinterpret_cast<const char*>(&finishStatus), sizeof(finishStatus));
        out.write(reinterpret_cast<const char*>(&isQuestQet), sizeof(isQuestQet));
        quest.serialize(out);
    }

    void deserialize(std::istream& in) override {
        in.read(reinterpret_cast<char*>(&finishStatus), sizeof(finishStatus));
        in.read(reinterpret_cast<char*>(&isQuestQet), sizeof(isQuestQet));
        quest.deserialize(in);
    }
};

class QuestPointer final : public Location
{
private:
    std::string lock;
    bool activate_status;

public:
    Quest quest;

    QuestPointer() : lock(" "), activate_status(false) {};

    explicit QuestPointer(const std::string& name, const std::string& description_filename, const std::string& lock)
        : Location(name, description_filename), lock(lock), activate_status(false) {
    }

    void activate(const std::string& key) override {
        if (key == lock) {
            activate_status = true;
        }
    }

    bool status() const override { return activate_status; }
    LocationType getType() const override { return LocationType::QuestPointer; }

    void serialize(std::ostream& out) const override {
        out.write(reinterpret_cast<const char*>(&finishStatus), sizeof(finishStatus));
        out.write(reinterpret_cast<const char*>(&activate_status), sizeof(activate_status));
        quest.serialize(out);
    }

    void deserialize(std::istream& in) override {
        in.read(reinterpret_cast<char*>(&finishStatus), sizeof(finishStatus));
        in.read(reinterpret_cast<char*>(&activate_status), sizeof(activate_status));
        quest.deserialize(in);
    }
};

class Map final : public Location
{
private:
    static const size_t MAX_LOCATION = 5;
    size_t size = 0;
    std::unique_ptr<Location> locations[MAX_LOCATION];

public:
    void activate(const std::string& key) override {}
    bool status() const override { return false; }
    LocationType getType() const override { return LocationType::Map; }

    void addLocation(std::unique_ptr<Location> location) {
        if (size < MAX_LOCATION) {
            locations[size++] = std::move(location);
        }
    }

    size_t getSize() const { return size; }

    std::unique_ptr<Location>& operator[](size_t index) {
        if (index >= MAX_LOCATION) {
            throw std::out_of_range("Index out of bounds");
        }
        if (index >= size) {
            size = index + 1;
        }
        return locations[index];
    }

    void serialize(std::ostream& out) const override {
        out.write(reinterpret_cast<const char*>(&finishStatus), sizeof(finishStatus));
        for (size_t i = 0; i < size; ++i) {
            locations[i]->serialize(out);
        }
    }

    void deserialize(std::istream& in) override {
        in.read(reinterpret_cast<char*>(&finishStatus), sizeof(finishStatus));
        for (size_t i = 0; i < size; ++i) {
            locations[i]->deserialize(in);
        }
    }
};
