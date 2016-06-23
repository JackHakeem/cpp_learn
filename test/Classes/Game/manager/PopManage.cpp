#include "PopManage.h"
#include "PopContainer.h"
#include "manager/layer/WindowLayer.h"
#include "manager/LayerManager.h"
#include "PopUIBg.h"
#include "events/GameDispatcher.h"
#include "GlobalManage.h"

PopManage* g_pPopManage = 0;

int32 PopManage::g_tagflag = 0;

PopManage::PopManage():layer(0)
{
	for (int i = 0; i < PopEventName::MAX_COUNT; i++)
	{
		popList[i] = 0;
	}
	//Init withList
	for (int i = 0; i < PopEventName::MAX_COUNT*10; i++)
	{
		withList[i/PopEventName::MAX_COUNT][i%PopEventName::MAX_COUNT] = 0;
	}
	withList[PopEventName::BAG][0] = PopEventName::BAG;
	withList[PopEventName::BAG][1] = PopEventName::BANK;
	withList[PopEventName::BAG][2] = PopEventName::SHOP;
	withList[PopEventName::BAG][3] = PopEventName::FIGURE;
	withList[PopEventName::BAG][4] = PopEventName::APPOINT;
	withList[PopEventName::BAG][5] = PopEventName::RANDGIFT;
	//withList[PopEventName::BAG][6] = PopEventName::MAP_AWARD;

	withList[PopEventName::BANK][0] = PopEventName::BANK;
	withList[PopEventName::BANK][1] = PopEventName::BAG;

	withList[PopEventName::RANDGIFT][0] = PopEventName::RANDGIFT;
	withList[PopEventName::RANDGIFT][1] = PopEventName::BAG;


	//withList[PopEventName::TRAIN][0] = PopEventName::FIGURE;

	withList[PopEventName::FIGURE][0] = PopEventName::FIGURE;
	withList[PopEventName::FIGURE][1] = PopEventName::WASH;
	withList[PopEventName::FIGURE][2] = PopEventName::BAG;
	withList[PopEventName::FIGURE][3] = PopEventName::OTHER_FIGURE;
	withList[PopEventName::FIGURE][4] = PopEventName::PEIYANG;
	withList[PopEventName::FIGURE][5] = PopEventName::SKILL;
	withList[PopEventName::FIGURE][6] = PopEventName::IDENTIFY;
	//withList[PopEventName::FIGURE][6] = PopEventName::TRAIN;


	withList[PopEventName::SKILL][0] = PopEventName::SKILL;  // added by lh 0416
	withList[PopEventName::SKILL][1] = PopEventName::FIGURE; // added by lh 0416

	withList[PopEventName::PEIYANG][0] = PopEventName::PEIYANG;  // added by lh 0419
	withList[PopEventName::PEIYANG][1] = PopEventName::FIGURE; // added by lh 0419
	//withList[PopEventName::PEIYANG][2] = PopEventName::SKILL; // added by lh 0419

	withList[PopEventName::IDENTIFY][0] = PopEventName::IDENTIFY;
	withList[PopEventName::IDENTIFY][1] = PopEventName::FIGURE;

	withList[PopEventName::OTHER_FIGURE][0] = PopEventName::OTHER_FIGURE;
	withList[PopEventName::OTHER_FIGURE][1] = PopEventName::FIGURE;
	withList[PopEventName::OTHER_FIGURE][2] = PopEventName::ARMY;
	withList[PopEventName::OTHER_FIGURE][3] = PopEventName::GUILD;

	withList[PopEventName::WASH][0] = PopEventName::WASH;
	withList[PopEventName::WASH][1] = PopEventName::FIGURE;

	withList[PopEventName::SHOP][0] = PopEventName::SHOP;
	withList[PopEventName::SHOP][1] = PopEventName::BAG;

	withList[PopEventName::PRE_GUILD][0] = PopEventName::PRE_GUILD;
	withList[PopEventName::PRE_GUILD][1] = PopEventName::GUILD;

	withList[PopEventName::GUILD][0] = PopEventName::GUILD;
	withList[PopEventName::GUILD][1] = PopEventName::PRE_GUILD;

	withList[PopEventName::APPOINT][0] = PopEventName::APPOINT;
	withList[PopEventName::APPOINT][1] = PopEventName::BAG;

	withList[PopEventName::REPORT_LIST][0] = PopEventName::REPORT_LIST;
	withList[PopEventName::REPORT_LIST][1] = PopEventName::REPORT;
	
	withList[PopEventName::MAP_AWARD][0] = PopEventName::MAP_AWARD;
	//withList[PopEventName::MAP_AWARD][1] = PopEventName::BAG;
		
	//Init withOpenList
	for (int i = 0; i < PopEventName::MAX_COUNT*10; i++)
	{
		withOpenList[i/PopEventName::MAX_COUNT][i%PopEventName::MAX_COUNT] = 0;
	}
	withOpenList[PopEventName::BANK][0] = PopEventName::BAG;

	withOpenList[PopEventName::SHOP][0] = PopEventName::FIGURE;

	withOpenList[PopEventName::BAG][0] = PopEventName::BANK;
	withOpenList[PopEventName::BAG][1] = PopEventName::SHOP;
	withOpenList[PopEventName::BAG][2] = PopEventName::RANDGIFT;

	withOpenList[PopEventName::FIGURE][0] = PopEventName::WASH;

	withOpenList[PopEventName::REPORT][0] = PopEventName::REPORT_LIST;
	
	//withOpenList[PopEventName::MAP_AWARD][0] = PopEventName::BAG;
	//withOpenList[PopEventName::BAG][3] = PopEventName::MAP_AWARD;

	//Init withBackList
	for (int i = 0; i < PopEventName::MAX_COUNT*10; i++)
	{
		withBackList[i/PopEventName::MAX_COUNT][i%PopEventName::MAX_COUNT] = 0;
	}
	withBackList[PopEventName::BAG][0] = PopEventName::BANK;
	withBackList[PopEventName::BAG][1] = PopEventName::SHOP;
	withBackList[PopEventName::BAG][2] = PopEventName::RANDGIFT;

	withBackList[PopEventName::FIGURE][0] = PopEventName::WASH;
}

bool PopManage::hasPopedConteainer()
{
	for (int j = 0; j < PopEventName::MAX_COUNT; j++)
	{
		if (popList[j] )
		{
			return true;
		}
	}
	return false;
}

void PopManage::setlayer(WindowLayer* pLayer)
{
	if (pLayer)
		layer = pLayer;
}

/**
* [method] pop-up
* @param popCon
*
*/
void PopManage::popUp(PopContainer* popCon)
{
	if (!popCon) return;
	//删除TIPS对话框
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	CCSize StageProxy = CCDirector::sharedDirector()->getWinSize();
	//Set appear coordinates (full screen center)
	popCon->setPosition(ccp( (StageProxy.width - popCon->getContentSize().width)/2,
		(StageProxy.height - popCon->getContentSize().height)/2));
	// =================
	// =================
	//If their can and any other panel coexistence, if not to execute the inside of the statement
	if (1 && popCon->key)//selfWithAllOther.indexOf(popCon.key)==-1 //LH20120108
	{
		//int* keyArr = 0;
		//if (withList[popCon->key][0])
		//{
		//	keyArr = withList[popCon->key];
		//}
		//concat Add any panel can coexist with the id

		//Turn off the other not coexist
		for (int j = 0; j < PopEventName::MAX_COUNT; j++)
		{
			if (popList[j] == 0)
				continue;
			bool pass = false;//Can coexist with popCon flag
			for (int i = 0; i < 10; i++)
			{
				if (!withList[popCon->key][i])
				{
					break;
				}
				if (popList[j]->key == withList[popCon->key][i])
				{
					pass = true;
					break;
				}
			}
			if (!pass)
			{//popList[j] Cannot coexist
				popList[j]->setisPop(false);
			}
		}
	}

	// ==============
	//
	popCon->popUp(layer);

	//
	if (popCon->key == 0)
	{
		if(popList[0])
		{
			popList[0]->setisPop(false);
		}
		popList[popCon->key] = popCon;

		//Reset position
		adjustCordinate();
		return;
	}
	// ==============

	popList[popCon->key] = popCon;
	//Open the window to open at the same time
	if (withOpenList[popCon->key][0])
	{
		for (int i = 0; i < 10; i++)
		{
			int8 openid = withOpenList[popCon->key][i];
			//popup(openid); May be triggered by events _dispatcher.dispatchEvent(new ParamEvent(PopEventName.EventName+key));
			if (openid != 0)
			{
				//GameDispatcher::getInstance()->dispatchEvent(openid+PopEventName::EventName, 0) ;
				//popCon->popUp(layer);
				//break;
			}
		}
	}
	//Reset position
	adjustCordinate();


	//加入PopUIBg
	int popedcount = 0;
	for (int j = 0; j < PopEventName::MAX_COUNT; j++)
	{
		if (popList[j] && popList[j]->getNeedBg() == true)
			popedcount++;
	}

	CCNode* _PopUIBg = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_PopUIBg);
	if (popedcount <= 0)
	{}
	else if (popedcount == 1 || !_PopUIBg)
	{
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/popuibg/res_popuibg.plist");

		PopUIBg* l = new PopUIBg();
		l->init();
		l->setBackBtnShow(false);
		if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_PopUIBg))
		{
			int i = 0;
		}
		LayerManager::windowLayer->addChild(l, WindowLayer::WindowLayerZ_PopUIBg-1, WindowLayer::WindowLayerTAG_PopUIBg);
		l->release();
	}

	// Add by Doyang.
	GameDispatcher::getInstance()->dispatchEvent(popCon->key, NULL);
}

/**
* [method] bouncing
* @param popCon
*
*/
void PopManage::popBack(PopContainer* popCon)
{
	int32 thekey = popCon->key;
	PopContainer* obj = (PopContainer*)layer->getChildByTag(popCon->getTag());
	if (!obj) return;

	popList[thekey] = 0;
	
// 	if (layer->getChildByTag(popCon->getTag()))
// 	{
		layer->removeChildByTag(popCon->getTag(), true);
//	}

	//删除返回
	PopUIBg* _PopUIBg = (PopUIBg*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_PopUIBg);
	if (_PopUIBg)
		_PopUIBg->setBackBtnShow(false);
	

	//删除TIPS对话框
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	//关闭同时要关闭的窗口
	if(withBackList[thekey][0])
	{
		for (int i = 0; i < PopEventName::MAX_COUNT; i++)
		{
			if (!popList[i]) 
				continue;
			for (int j = 0 ; j < 10; j++)
			{
				if (withBackList[thekey][j] == popList[i]->key)
				{
					popList[i]->setisPop(false);
					
					break;
				}
			}
		}
	}
	//Reset position
	adjustCordinate();

	//删除PopUIBg
	int popedcount = 0;
	for (int j = 0; j < PopEventName::MAX_COUNT; j++)
	{
		if (popList[j] && popList[j]->getNeedBg() == true)
			popedcount++;
	}

	if (popedcount == 0 && _PopUIBg)
	{
		
		if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_PopUIBg)) //LH
		{
			LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_PopUIBg, true);	
		}
	}

	// LH0711
	if (popCon->key == PopEventName::MAP)
	{
		g_pGlobalManage->setIsInWordMap(false);
	}
}

void PopManage::adjustCordinate()
{
	//The current full screen SIZE
	CCSize StageProxy = CCDirector::sharedDirector()->getWinSize();

	float tempw = 0;

	std::list<PopContainer*> popArr;
	for (int i = 0; i < PopEventName::MAX_COUNT; i++)
	{
		if (popList[i])
		{
			popArr.push_back(popList[i]); 
			tempw += popList[i]->getPopContentSize().width;
		}
	}

	if (tempw > StageProxy.width)//Panel total wider than scene
	{
		for (std::list<PopContainer*>::iterator it = popArr.begin(); it != popArr.end(); it++)
		{
			PopContainer* obj = *it;
			if (obj && obj->key != 0)
			{
				float x = (StageProxy.width - obj->getPopContentSize().width)/2;
				float y = (StageProxy.height - obj->getPopContentSize().height)/2;
				obj->setPosition(ccp(x,y));
			}			
		}
	}
	else
	{
		float startX = (StageProxy.width - tempw)/2;
		for (std::list<PopContainer*>::iterator it = popArr.begin(); it != popArr.end(); it++)
		{
			PopContainer* obj = *it;
			if (obj && obj->key != 0)
			{
				float x = startX;
				float y = (StageProxy.height - obj->getPopContentSize().height)/2;
				//obj->runAction(cocos2d::CCMoveTo::actionWithDuration(0.275f, ccp(x,y)));
				obj->setPosition(ccp(x,y));
				startX += obj->getPopContentSize().width;
			}
		}
	}
}

/**
	*Judge whether window is already open
	* @param key PopEventName.key
	* @return 
	* 
	*/		
bool PopManage::isViewPop(int32 key)
{
	return popList[key] != 0;
}

int32 PopManage::getCurPopNum()
{
	int c = 0;
	for (int32 i = 0; i < PopEventName::MAX_COUNT; i++)
	{
		if (popList[i])
			c++;
	}
	return c;
}

void PopManage::handleBackHandler()
{
	for (int i = 0; i < PopEventName::MAX_COUNT; i++)
	{
		if (popList[i])
		{
			popList[i]->handleBack();
		}
	}
}

void PopManage::handleCloseHandler()
{
	for (int i = 0; i < PopEventName::MAX_COUNT; i++)
	{
		if (popList[i] 	
		&& popList[i]->getIsNeedClose()) // LH
		{
			popList[i]->clickCloseHandler(0);
		}
	}

	g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());

	//g_pGlobalManage->showAllUI(true);
}

void PopManage::setIsNeedClose(int index , bool var)
{
	PopContainer * pPopCon = popList[index];
	if (pPopCon && index>=0 && index< PopEventName::MAX_COUNT )
	{
		pPopCon->setIsNeedClose(var);
	}
}

CCNode * PopManage::getBtnX()
{
	CCNode* pPopUIBg = LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_PopUIBg);
	if (pPopUIBg)
	{
		CCMenu * pButtonMenu = (CCMenu *)pPopUIBg->getChildByTag(PopUIBg::PopUIBgTAG_btn_X);
		if (pButtonMenu)
		{
			return pButtonMenu->getChildByTag(0);
		}
	}
	return 0;
}