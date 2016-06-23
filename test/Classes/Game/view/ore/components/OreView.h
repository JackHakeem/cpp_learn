#pragma once

#include "PopContainer.h"
#include "LayerNode.h"

class OreItem;
class PlantView;
class OreView:public PopContainer
{
public:
	OreView();
	~OreView();
	bool init();
	void clickClose(CCObject* pSender);
	void clickCloseHandler(CCObject* pSender);
	void UpdateOre(uint32 stoneNum, uint32 oreNum, uint32 buyCount);
	void HandleResponse(uint32 flag);
	void clickBuyStone(CCObject* pSender);
	void clickHelp(CCObject* pSender);
	void handleBuyStone(CCObject* pSender);
	void handleBuyStoneCancel(CCObject* pSender);
	void UpdatePlantProgress(uint32 progress);
	PlantView* getCurPlantView();
	uint32 GetPlantStateByOreID(uint32 oreID);
	CCNode * getNewHandItem(int id);
public:
	LayerNode* _pContainer;
	CCMenuItemSprite *_btnClose;
	int m_iOreNum;
	int m_iBuyCount;
	int m_iPlantStates;
};