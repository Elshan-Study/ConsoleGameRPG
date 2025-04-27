#pragma once
#include "Item.h"
#include <iostream>

class Inventory final
{
private:
	static const size_t MAX_ITEMS = 30;
	size_t size;
public:
	std::unique_ptr<Item> items[MAX_ITEMS];
	Inventory() : size(0) {}

	Inventory(const Inventory& other) = delete;

	Inventory& operator=(const Inventory& other) = delete;

	Inventory(Inventory&& other) noexcept;

	Inventory& operator=(Inventory&& other) noexcept;

	~Inventory() = default;

	size_t getSize() const;

	bool addItem(std::unique_ptr<Item> item);

	void CheckInventory();

	friend std::ostream& operator<<(std::ostream& os, const Inventory& inventory);

	std::unique_ptr<Item>& operator[](size_t index);

	void Serialize(std::ostream& out) const;

	void Deserialize(std::istream& in);
};