#include "PopContainer.h"
#include "manager/layer/WindowLayer.h"
#include "manager/PopManage.h"
#include "events/GameDispatcher.h"
#include "manager/sound/SoundManager.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"

PopContainer::PopContainer()
{
	setIsNeedClose(true);
	_isPop = false;
	_UIStage = 0;
	_NeedBg = NeedBg_YES;
}

void PopContainer::popUp(WindowLayer* layer)
{
	layer->addChild(this, 0, key);
}

bool PopContainer::getisPop()
{
	return _isPop;
}

void PopContainer::setisPop(bool var)
{
	changeStage(0);
	if (var)
	{
		_isPop = true;
		g_pPopManage->popUp(this);
		reinit();

		g_pGlobalManage->showAllUI(false);

		//Doyang 20120727
		GameDispatcher::getInstance()->dispatchEvent(PopContainer::OPEN_CONTAINER, &key);

		//g_pGlobalManage->showAllUI(false);

		g_pGlobalManage->setIsShowAllUILock(true);
		//消失聊天小栏和按钮
		CCNode* chatview = (CCNode*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
		if (chatview && chatview->getIsVisible() == true)
		{
			chatview->setIsVisible(false);
		}
		CCNode* chatBtn = (CCNode*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatBtn);
		{
			chatBtn->setIsVisible(false);
		}
	}
	else
	{
		removeDataObjectChild();

		_isPop = false;
		g_pPopManage->popBack(this);
		//Doyang 20120727
		GameDispatcher::getInstance()->dispatchEvent(PopContainer::CLOSE_CONTAINER, &key);
		g_pGlobalManage->setIsShowAllUILock(false);
		g_pGlobalManage->showAllUI(true);
		//显示聊天小栏和按钮
		CCNode* chatview = (CCNode*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
		if (chatview && chatview->getIsVisible() == false)
		{
			chatview->setIsVisible(true);
		}
		CCNode* chatBtn = (CCNode*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatBtn);
		{
			chatBtn->setIsVisible(true);
		}
	}

	//SoundManager::Instance()->playPopContainerEffectSound();
	
}

//CC_PROPERTY(int32, _UIStage, UIStage)
int32 PopContainer::getUIStage()
{
	return _UIStage;
}

void PopContainer::setUIStage(int32 var)
{
	_UIStage = var;
}


//CC_PROPERTY(int32, NeedBg, _NeedBg)
int32 PopContainer::getNeedBg()
{
	return _NeedBg;
}

void PopContainer::setNeedBg(int32 var)
{
	_NeedBg = var;
}

/**
	*  Click on close
	* @param e
	* 
protected function clickCloseHandler(e:MouseEvent):void
{
	this.isPop=false;
}
*/
void PopContainer::clickCloseHandler(CCObject* pSender)
{
	setisPop(false);
}

/**
	*Forced close
	* 
	*/		
void PopContainer::close()
{
	setisPop(false);
	g_pPopManage->popBack(this);//Redundant?
	GameDispatcher::getInstance()->dispatchEvent(PopContainer::CLOSE_CONTAINER, NULL);
}

//CC_PROPERTY(CCSize, _popContentSize, PopContentSize)
CCSize PopContainer::getPopContentSize()
{
	return _popContentSize;
}

void PopContainer::setPopContentSize(CCSize var)
{
	_popContentSize = var;
}

