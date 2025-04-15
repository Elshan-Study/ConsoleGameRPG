#pragma once
#include <memory>
class OptionChoice
{
private:
    std::shared_ptr<std::shared_ptr<size_t>[]> stages;  
    size_t capacity;
    size_t size;
public:
    OptionChoice(size_t cap) : capacity(cap), size(0) {
        stages = std::make_shared<std::shared_ptr<size_t>[]>(capacity); 
    }

    bool addChoice(std::shared_ptr<size_t> index)
    {
        if (size < capacity) {
            stages[size] = index;  
            ++size;
            return true;
        }

        return false;
    }

    std::shared_ptr<size_t> nextStage(size_t index)
    {
        return stages[index];  
    }

    size_t getSize() const {
        return size;
    }
};