#include "Inventory.h"

Inventory::Inventory(Inventory&& other) noexcept : size(other.size) {
	for (size_t i = 0; i < MAX_ITEMS; ++i) {
		items[i] = std::move(other.items[i]);
	}
	other.size = 0;
}

Inventory& Inventory::operator=(Inventory&& other) noexcept {
	if (this != &other) {
		size = other.size;
		for (size_t i = 0; i < MAX_ITEMS; ++i) {
			items[i] = std::move(other.items[i]);
		}
		other.size = 0;
	}
	return *this;
}

size_t Inventory::getSize() const { return size; }

bool Inventory::addItem(std::unique_ptr<Item> item) {
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

void Inventory::CheckInventory() {
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

std::ostream& operator<<(std::ostream& os, const Inventory& inventory) {
	for (int i = 0; i <= inventory.size; i++) {
		if (inventory.items[i]) {
			os << *(inventory.items[i]);
		}
	}
	os << "\n";
	return os;
}

std::unique_ptr<Item>& Inventory::operator[](size_t index)
{
	if (index >= MAX_ITEMS) {
		throw std::out_of_range("Index out of bounds");
	}
	if (index >= size) {
		size = index + 1;
	}
	return items[index];
}

void Inventory::Serialize(std::ostream& out) const {
	out.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (size_t i = 0; i < size; ++i) {
		if (items[i]) {
			bool hasItem = true;
			out.write(reinterpret_cast<const char*>(&hasItem), sizeof(hasItem));
			items[i]->Serialize(out);
		}
		else {
			bool hasItem = false;
			out.write(reinterpret_cast<const char*>(&hasItem), sizeof(hasItem));
		}
	}
}

void Inventory::Deserialize(std::istream& in) {
	in.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (size_t i = 0; i < size; ++i) {
		bool hasItem;
		in.read(reinterpret_cast<char*>(&hasItem), sizeof(hasItem));
		if (hasItem) {
			items[i] = Item::Deserialize(in);
		}
	}
}