#pragma once
#include <Engine/Object.hpp>

const int ItemType_Com = 1;
const int ItemType_Inst = 2; 
const int ItemType_Equip = 3;
const int ItemType_Build = 4;
const int ItemType_Other = 5;

const int ItemSyze_s_w = 1;
const int ItemSyze_s_h = 1; 
const int ItemSyze_m_w = 2;
const int ItemSyze_m_h = 2;
const int ItemSyze_l_w = 3;
const int ItemSyze_l_h = 3;
const int ItemSyze_n_w = 0;
const int ItemSyze_n_h = 0;

class Item 
{
public:
	Item();
	~Item();

	unsigned int _itemID;
	unsigned int count;
	unsigned int maxstack;
	double weightpercount;
	unsigned int w, h;
	unsigned int type;

	ThrashEngine::PropertyClass itemproperty;
protected:

};