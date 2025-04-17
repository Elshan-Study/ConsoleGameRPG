#pragma once
#include <memory>

class OptionChoice {
private:
    size_t* stages;
    size_t capacity;
    size_t size;

public:
    OptionChoice(size_t cap)
        : capacity(cap), size(0), stages(new size_t[cap]) {
    }

    OptionChoice(const OptionChoice& other)
        : capacity(other.capacity), size(other.size), stages(new size_t[other.capacity]) {
        for (size_t i = 0; i < size; ++i) {
            stages[i] = other.stages[i];
        }
    }

    OptionChoice& operator=(const OptionChoice& other) {
        if (this == &other)
            return *this;

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
        if (this == &other)
            return *this;

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
};
