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

    Location();
    explicit Location(const std::string& name, const std::string& filename);
    virtual ~Location() = default;

    virtual void activate(const std::string& key) = 0;
    virtual bool status() const = 0;
    virtual LocationType getType() const = 0;

    virtual void serialize(std::ostream& out) const = 0;

    virtual void deserialize(std::istream& in) = 0;

    void setMain(const std::string& name, const std::string& filename);

    std::string getName() const;

    void readDescription();

    void setFinishStatus(size_t status);
    size_t getFinishStatus() const;
};

class QuestGetPointer final : public Location
{
private:
    std::string key;
    bool isQuestQet;

public:
    Quest quest;

    QuestGetPointer();

    explicit QuestGetPointer(const std::string& name, const std::string& description_filename, const std::string& key);

    void activate(const std::string& key) override;
    bool status() const override;
    LocationType getType() const override;

    void changeKey(const std::string& key);
    std::string getKey() const;

    void serialize(std::ostream& out) const override;

    void deserialize(std::istream& in) override;
};

class QuestPointer final : public Location
{
private:
    std::string lock;
    bool activate_status;

public:
    Quest quest;

    QuestPointer();

    explicit QuestPointer(const std::string& name, const std::string& description_filename, const std::string& lock);

    void activate(const std::string& key) override;

    bool status() const override;
    LocationType getType() const override;

    void serialize(std::ostream& out) const override;

    void deserialize(std::istream& in) override;
};

class Map final : public Location
{
private:
    static const size_t MAX_LOCATION = 5;
    size_t size = 0;
    std::unique_ptr<Location> locations[MAX_LOCATION];

public:
    void activate(const std::string& key) override;
    bool status() const override;
    LocationType getType() const override;

    void addLocation(std::unique_ptr<Location> location);

    size_t getSize() const;

    std::unique_ptr<Location>& operator[](size_t index);

    void serialize(std::ostream& out) const override;

    void deserialize(std::istream& in) override;
};
