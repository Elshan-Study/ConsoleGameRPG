#pragma once
#include "Item.h"
#include <iostream>

class Inventory final
{
private:
	static const size_t MAX_ITEMS = 20;
	size_t size;
public:
	std::unique_ptr<Item> items[MAX_ITEMS];
	Inventory() : size(0) {}

	~Inventory() = default;

	size_t getSize() const { return size; }

	bool addItem(std::unique_ptr<Item> item) {
		for (size_t i = 0; i < size; i++) {
			Item* existing = items[i].get();

			if (auto* existingPotion = dynamic_cast<Potion*>(existing)) {
				if (auto* newPotion = dynamic_cast<Potion*>(item.get())) {
					if (existingPotion->Name() == newPotion->Name()) {
						existingPotion->addCopy(1);
						return true;
					}
				}
			}
		}

		if (size < MAX_ITEMS) {
			items[size++] = std::move(item);
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
					items[j] = std::move(items[j + 1]); 
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

	std::unique_ptr<Item>& operator[](size_t index)
	{
		if (index >= MAX_ITEMS) {
			throw std::out_of_range("Index out of bounds");
		}
		if (index >= size) {
			size = index + 1;
		}
		return items[index];
	}

};