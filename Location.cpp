#include "Location.h"

Location::Location() : name("Unknown"), description_file("Unknown") {};
Location::Location(const std::string& name, const std::string& filename)
    : name(name), description_file(filename) {
}

void Location::setMain(const std::string& name, const std::string& filename) {
    this->name = name;
    description_file = filename;
}

std::string Location::getName() const { return name; }

void Location::readDescription() {
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

void Location::setFinishStatus(size_t status) { finishStatus = status; }
size_t Location::getFinishStatus() const { return finishStatus; }

QuestGetPointer::QuestGetPointer() : key(" "), isQuestQet(false) {};

QuestGetPointer::QuestGetPointer(const std::string& name, const std::string& description_filename, const std::string& key)
        : Location(name, description_filename), key(key), isQuestQet(false) {
    }

void QuestGetPointer::activate(const std::string& key)  { isQuestQet = true; }
bool QuestGetPointer::status() const { return isQuestQet; }
Location::LocationType QuestGetPointer::getType() const  { return LocationType::QuestGetPointer; }

void QuestGetPointer::changeKey(const std::string& key) { this->key = key; }
std::string QuestGetPointer::getKey() const { return isQuestQet ? key : "Error"; }

void QuestGetPointer::serialize(std::ostream& out) const  {
    out.write(reinterpret_cast<const char*>(&finishStatus), sizeof(finishStatus));
    out.write(reinterpret_cast<const char*>(&isQuestQet), sizeof(isQuestQet));
    quest.serialize(out);
}

void QuestGetPointer::deserialize(std::istream& in)  {
    in.read(reinterpret_cast<char*>(&finishStatus), sizeof(finishStatus));
    in.read(reinterpret_cast<char*>(&isQuestQet), sizeof(isQuestQet));
    quest.deserialize(in);
}

QuestPointer::QuestPointer() : lock(" "), activate_status(false) {};

QuestPointer::QuestPointer(const std::string& name, const std::string& description_filename, const std::string& lock)
        : Location(name, description_filename), lock(lock), activate_status(false) {
    }

void QuestPointer::activate(const std::string& key)  {
    if (key == lock) {
        activate_status = true;
    }
}

bool QuestPointer::status() const  { return activate_status; }
Location::LocationType QuestPointer::getType() const  { return LocationType::QuestPointer; }

void QuestPointer::serialize(std::ostream& out) const  {
    out.write(reinterpret_cast<const char*>(&finishStatus), sizeof(finishStatus));
    out.write(reinterpret_cast<const char*>(&activate_status), sizeof(activate_status));
    quest.serialize(out);
}

void QuestPointer::deserialize(std::istream& in)  {
    in.read(reinterpret_cast<char*>(&finishStatus), sizeof(finishStatus));
    in.read(reinterpret_cast<char*>(&activate_status), sizeof(activate_status));
    quest.deserialize(in);
}

void Map::activate(const std::string& key)  {}
bool Map::status() const  { return false; }
Location::LocationType Map::getType() const  { return LocationType::Map; }

void Map::addLocation(std::unique_ptr<Location> location) {
    if (size < MAX_LOCATION) {
        locations[size++] = std::move(location);
    }
}

size_t Map::getSize() const { return size; }

std::unique_ptr<Location>& Map::operator[](size_t index) {
    if (index >= MAX_LOCATION) {
        throw std::out_of_range("Index out of bounds");
    }
    if (index >= size) {
        size = index + 1;
    }
    return locations[index];
}

void Map::serialize(std::ostream& out) const  {
    out.write(reinterpret_cast<const char*>(&finishStatus), sizeof(finishStatus));
    for (size_t i = 0; i < size; ++i) {
        locations[i]->serialize(out);
    }
}

void Map::deserialize(std::istream& in)  {
    in.read(reinterpret_cast<char*>(&finishStatus), sizeof(finishStatus));
    for (size_t i = 0; i < size; ++i) {
        locations[i]->deserialize(in);
    }
}
