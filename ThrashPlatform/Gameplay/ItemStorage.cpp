#include "ItemStorage.hpp"

ItemStorage::ItemStorage()
{
	w = h = 0;
	totalweight = 0;
	ResizeInventory(0, 0);
}
ItemStorage::~ItemStorage()
{

}

int ItemStorage::ResizeInventory(unsigned int w, unsigned int h)
{
	if (w == 0 || h == 0) return 0;
	std::vector<Item> copy = _inventory;
	_inventory.resize(w*h);
	unsigned int iterator = 0;
	for (auto i = copy.begin(); i != copy.end() && iterator<w*h; i++)
	{
		_inventory[iterator] = *i; //copy item
		iterator++;//select next copy item
	}
	this->w = w;
	this->h = h;
	return 1;
}
int ItemStorage::AddItem(Item& additem)
{
	if (additem.count == 0) return 0;
	
	//find place for item
	for (auto i = _inventory.begin(); i != _inventory.end(); i++)
	{
		if (i->_itemID == 0) //free place
		{
			if (additem.count <= additem.maxstack) 
			{
				*i = additem; //just copy
				additem.count = 0;
				return 1;
			}
			else
			{
				*i = additem; //just copy
				i->count = i->maxstack;
				additem.count -= additem.maxstack;
			}
		}
		if (i->_itemID == additem._itemID && i->count < i->maxstack) //same item id with place and has place for item
		{
			unsigned int freeplace = i->maxstack - i->count;
			if (additem.count < freeplace)
			{
				i->count += additem.count = 0;
				additem.count = 0;
				return 1;
			}
			else
			{
				i->count = i->maxstack;
				additem.count -= freeplace;
			}
		}
	}
	if (additem.count == 0) return 0;
	return 1;
}