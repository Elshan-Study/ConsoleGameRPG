#pragma once
#include <memory>
#include <fstream>

class OptionChoice {
private:
    size_t* stages;
    size_t capacity;
    size_t size;

public:
    OptionChoice(size_t cap = 0);

    OptionChoice(const OptionChoice& other);

    OptionChoice& operator=(const OptionChoice& other);

    OptionChoice(OptionChoice&& other) noexcept;

    OptionChoice& operator=(OptionChoice&& other) noexcept;

    ~OptionChoice() {
        delete[] stages;
    }

    bool addChoice(size_t index);

    size_t getSize() const;

    size_t operator[](size_t i) const;

    void serialize(std::ostream& out) const;

    static OptionChoice deserialize(std::istream& in);
};
