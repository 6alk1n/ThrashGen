#pragma once
#include "Item.hpp"
#include <vector>

class ItemStorage
{
public:
	ItemStorage();
	~ItemStorage();

	int ResizeInventory(unsigned int, unsigned int);
	int AddItem(Item&);

	std::vector<Item> _inventory;
	unsigned int w, h;
	double totalweight;
	ThrashEngine::PropertyClass property;
protected:

};