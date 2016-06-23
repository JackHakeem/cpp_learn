#pragma once

#include "BaseType.h"

class PlantView:public LayerNode
{
public:
	PlantView();
	~PlantView();

	bool init(uint32 oreID);
	void clickPlant(CCObject* pSender);
	void clickRefresh(CCObject* pSender);
	void clickFullLv(CCObject* pSender);
	void clickClose(CCObject* pSender);
	void UpdatePlantState(uint32 plantState);
	void handleRefresh(CCObject* pSender);
	void handleRefreshCancel(CCObject* pSender);
	void handleFullLv(CCObject* pSender);
public:
	LayerNode* _pContainer;
	CCMenuItemSprite *_plantbtn;
	CCMenuItemSprite *_btnClose;
	int m_iOreID;
	int m_iPlantState;
};