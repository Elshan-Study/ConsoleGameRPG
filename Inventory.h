#pragma once
#include "Item.h"
#include <iostream>

class Inventory final
{
private:
	const size_t MAX_ITEMS = 20;
	size_t size = 0;
	std::unique_ptr<Item* []> items;
public:
	Inventory() { items = std::make_unique<Item * []>(MAX_ITEMS); }

	~Inventory() = default;

	bool addItem(Item* item) {
		if (size < MAX_ITEMS) {
			items[size++] = item;
			return true;
		}
		std::cerr << "Inventory is full!\n";
		return false;
	}

	void CheckInventory() {
		size_t i = 0;
		while (i < size) {
			if (items[i] && items[i]->isExist == 0) {
				for (size_t j = i; j < size - 1; ++j) {
					items[j] = items[j + 1];
				}
				items[size - 1] = nullptr; 
				--size; 
			}
			else {
				++i;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Inventory& inventory) {
		for (int i = 0; i <= inventory.size; i++) {
			if (inventory.items[i]) {
				os << *(inventory.items[i]);
			}
		}
		os << "\n";
		return os;
	}

	Item*& operator[](size_t index)
	{
		if (index <= 0 || index >= MAX_ITEMS)
		{
			return items[0];
		}
		if (index >= size)
		{
			size = index;
		}
		return items[index];
	}
};