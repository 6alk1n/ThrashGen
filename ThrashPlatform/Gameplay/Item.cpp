#include "Item.hpp"

Item::Item()
{
	//init to null all items
	_itemID = count = maxstack = w = h = 0;
	type = ItemType_Com;
	weightpercount = 0.0;
}
Item::~Item()
{

}