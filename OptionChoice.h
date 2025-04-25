#pragma once
#include <memory>
#include <fstream>

class OptionChoice {
private:
    size_t* stages;
    size_t capacity;
    size_t size;

public:
    OptionChoice(size_t cap = 0)
        : capacity(cap), size(0), stages(cap > 0 ? new size_t[cap] : nullptr) {
    }

    OptionChoice(const OptionChoice& other)
        : capacity(other.capacity), size(other.size), stages(new size_t[other.capacity]) {
        for (size_t i = 0; i < size; ++i) {
            stages[i] = other.stages[i];
        }
    }

    OptionChoice& operator=(const OptionChoice& other) {
        if (this == &other) return *this;
        delete[] stages;
        capacity = other.capacity;
        size = other.size;
        stages = new size_t[capacity];
        for (size_t i = 0; i < size; ++i) {
            stages[i] = other.stages[i];
        }
        return *this;
    }

    OptionChoice(OptionChoice&& other) noexcept
        : stages(other.stages), capacity(other.capacity), size(other.size) {
        other.stages = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    OptionChoice& operator=(OptionChoice&& other) noexcept {
        if (this == &other) return *this;
        delete[] stages;
        stages = other.stages;
        capacity = other.capacity;
        size = other.size;
        other.stages = nullptr;
        other.capacity = 0;
        other.size = 0;
        return *this;
    }

    ~OptionChoice() {
        delete[] stages;
    }

    bool addChoice(size_t index) {
        if (size >= capacity) {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
            size_t* newStages = new size_t[newCapacity];
            for (size_t i = 0; i < size; ++i) {
                newStages[i] = stages[i];
            }
            delete[] stages;
            stages = newStages;
            capacity = newCapacity;
        }
        stages[size++] = index;
        return true;
    }

    size_t getSize() const {
        return size;
    }

    size_t operator[](size_t i) const {
        return stages[i];
    }

    void serialize(std::ostream& out) const {
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            out.write(reinterpret_cast<const char*>(&stages[i]), sizeof(size_t));
        }
    }

    static OptionChoice deserialize(std::istream& in) {
        size_t size = 0;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));

        OptionChoice choice(size);
        choice.size = size;
        for (size_t i = 0; i < size; ++i) {
            in.read(reinterpret_cast<char*>(&choice.stages[i]), sizeof(size_t));
        }

        return choice;
    }
};
