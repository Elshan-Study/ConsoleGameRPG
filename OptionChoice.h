#pragma once
#include <memory>

class OptionChoice {
private:
    std::unique_ptr<std::shared_ptr<size_t>[]> stages;
    size_t capacity;
    size_t size;

public:
    OptionChoice(size_t cap)
        : capacity(cap), size(0),
        stages(std::make_unique<std::shared_ptr<size_t>[]>(cap)) {
    }

    OptionChoice(const OptionChoice& other)
        : capacity(other.capacity), size(other.size),
        stages(std::make_unique<std::shared_ptr<size_t>[]>(other.capacity)) {
        for (size_t i = 0; i < size; ++i) {
            stages[i] = other.stages[i];
        }
    }

    OptionChoice& operator=(const OptionChoice& other) {
        if (this == &other)
            return *this;

        capacity = other.capacity;
        size = other.size;
        stages = std::make_unique<std::shared_ptr<size_t>[]>(capacity);
        for (size_t i = 0; i < size; ++i) {
            stages[i] = other.stages[i];
        }

        return *this;
    }

    OptionChoice(OptionChoice&& other) noexcept
        : stages(std::move(other.stages)),
        capacity(other.capacity),
        size(other.size) {
        other.capacity = 0;
        other.size = 0;
    }

    OptionChoice& operator=(OptionChoice&& other) noexcept {
        if (this == &other)
            return *this;

        stages = std::move(other.stages);
        capacity = other.capacity;
        size = other.size;

        other.capacity = 0;
        other.size = 0;

        return *this;
    }

    bool addChoice(std::shared_ptr<size_t> index) {
        if (size < capacity) {
            stages[size++] = index;
            return true;
        }
        return false;
    }

    size_t getSize() const {
        return size;
    }
};
