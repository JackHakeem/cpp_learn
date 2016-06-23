#pragma once

#include "BaseType.h"

class PlantItem:public LayerNode
{
public:
	PlantItem();
	~PlantItem();

	bool init(uint32 oreID, uint32 plantID, bool opened);
	void clickPlant(CCObject* pSender);
	void clickPlantOpen(CCObject* pSender);

public:
	uint32 m_iOreID;
	uint32 m_iPlantID;
};