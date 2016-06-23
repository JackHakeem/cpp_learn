#pragma once

#include "BaseType.h"

class PlantView;

class OreItem:public LayerNode
{
public:
	OreItem();
	~OreItem();

	bool init(uint32 oreID, bool opened);
	void clickOre(CCObject* pSender);
	void clickOreOpen(CCObject* pSender);
	void handleBuy(CCObject* pSender);
	void handleBuyCancel(CCObject* pSender);
	bool isInCD();
public:
	uint32 m_oreID;
	CCMenuItemImage *_btnOre;
	PlantView* _plant;
};