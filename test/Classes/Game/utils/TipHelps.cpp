#include "TipHelps.h"
#include "utils/TipBase.h"
#include "utils/TipsEquipCanvas.h"
#include "utils/TipsSkillCanvas.h"
#include "utils/TipsXHCanvas.h"
#include "manager/LayerManager.h"

TipHelps::TipHelps()
{}

TipHelps::~TipHelps()
{}

void TipHelps::init(bool isEquip, int32 type, bool isSkill, bool isXH)
{
	_isEquip = isEquip;
	_isSkill = isSkill;
	_isXH = isXH;
	_type = type;
}

void TipHelps::setToolTips(LayerNode* sprite, TipBase* tips)//, std::string tips
{
	if (sprite == 0)
		return;

	_sprite = sprite;
	_toolTips = tips;


}


/**
	*  
	* @param tips
	* @param otherTips
	* 
	*/		

void TipHelps::setTips(TipBase* tips, TipBase* otherTips)//std::string tips, std::string otherTips
{
	CCPoint globalPoint = ccp(0, 0);
	if (tips != 0)
	{
		_toolTips = tips;
	}

	if (_isTip)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
		g_pTipsEquipCanvas = 0;
		g_pTipsSkillCanvas = 0;
		g_pTipsXHCanvas = 0;
		//

		globalPoint = getScreenPos(_sprite);//_sprite->convertToWorldSpaceAR(ccp(_sprite->getPosition().x, _sprite->getPosition().y));
	
		if (_isXH)
		{
			if (!g_pTipsXHCanvas)
			{
				g_pTipsXHCanvas = new TipsXHCanvas();
				LayerManager::tipsLayer->addChild(g_pTipsXHCanvas, TipsLayer::TipsLayerZ_itemInfoShow+100,TipsLayer::TipsLayerTAG_itemInfoShow);
				g_pTipsXHCanvas->release();//Kenfly 20130204
			}
			g_pTipsXHCanvas->removeAllChildrenWithCleanup(true);
			if (!g_pTipsXHCanvas->displayTip(ccp(globalPoint.x, globalPoint.y), _toolTips, (char*)_sprite, _toolTips))
			{
				LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
			}
		}
		else if (_isEquip)
		{
			if (!g_pTipsEquipCanvas)
			{
				g_pTipsEquipCanvas = new TipsEquipCanvas();
				LayerManager::tipsLayer->addChild(g_pTipsEquipCanvas, TipsLayer::TipsLayerZ_itemInfoShow+100,TipsLayer::TipsLayerTAG_itemInfoShow);
				g_pTipsEquipCanvas->release(); // 20120116
			}
			g_pTipsEquipCanvas->removeAllChildrenWithCleanup(true);
			if (!g_pTipsEquipCanvas->displayTip(ccp(globalPoint.x, globalPoint.y), _toolTips, _type, (char*)_toolTips))
			{
				LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
			}
		}
		else if (_isSkill)
		{
			if (!g_pTipsSkillCanvas)
			{
				g_pTipsSkillCanvas = new TipsSkillCanvas();
				LayerManager::tipsLayer->addChild(g_pTipsSkillCanvas, TipsLayer::TipsLayerZ_itemInfoShow+100,TipsLayer::TipsLayerTAG_itemInfoShow);
				g_pTipsSkillCanvas->release();//Kenfly 20130204
			}
			g_pTipsSkillCanvas->removeAllChildrenWithCleanup(true);
			if (!g_pTipsSkillCanvas->displayTip(ccp(globalPoint.x, globalPoint.y), _toolTips, (char*)_sprite, _toolTips))
			{
				LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
			}
		}
		else
		{}
	}
}

void TipHelps::timerComplete()
{
	setTips();
}

void TipHelps::rollOverHander()
{
	_isTip = true;
	timerComplete();
}
