#include "RewardListView.h"
#include "../../../model/onlineReward/OnlineRewardManager.h"
#include "RewardItem.h"
#include "UIListView/CCUIListView.h"
#include "manager/TouchLayerEnum.h"
#include "model/onlineReward/OnlineRewardProxy.h"
#include "control/AppFacade.h"
#include "../RewardMediator.h"
#include "utils/ValuesUtil.h"
#include "manager/ViewManager.h"
#include "model/newhand/NewhandManager.h"

RewardListView::RewardListView() : _pListView(0)
{
	
}

RewardListView::~RewardListView()
{
	CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		pChildLayer->removeFromParentAndCleanup(true);
		pChildLayer->release();
	}

	//_pListView->release();
}

bool RewardListView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);
	
	return true;
}

void RewardListView::load()
{
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(CCRECT_REWARD_LISTVIEW.origin.x,
		CCRECT_REWARD_LISTVIEW.origin.y,
		CCRECT_REWARD_LISTVIEW.size.width,
		CCRECT_REWARD_LISTVIEW.size.height), 
		false);

	if(!_pListView) 
		return ;
	_pListView->setAnchorPoint(CCPointZero);
	_pListView->m_pri = TLE::WindowLayer -1;
	_pListView->setWorldSpaceLeftBottomPoint(ccpAdd(this->getParent()->getPosition()  , ccpAdd(this->getPosition() , _pListView->getPosition())));
	_pListView->setSpacingVertical(POSX(14));
	//_pListView->setAdapter(this);
	_pListView->setOnItemActionListener(this);
	this->setContentSize(_pListView->getContentSize());
	_pListView->setTag(TAG_LIST);
	this->addChild(_pListView);
	_pListView->release();
}

void RewardListView::refresh()
{
	CCUIListView * pListView = (CCUIListView *)this->getChildByTag(TAG_LIST);
	if (pListView)
	{
		CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
		CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
		for(it = listChilds->begin();
			it != listChilds->end();
			++ it)
		{
			LayerNode *pChildLayer = (LayerNode *) *it;
			if(!pChildLayer)
				continue;

			pChildLayer->removeFromParentAndCleanup(true);
			pChildLayer->release();
		}
		pListView->setAdapter(this);
	}
}

int RewardListView::getCount()
{
	return OnlineRewardManager::Instance()->getSize();
}

LayerNode * RewardListView::getView(int position)
{
	//LayerNode * pLayer = new LayerNode();
	//pLayer->init();

	std::vector<OnlineRewardVo> *pDic = OnlineRewardManager::Instance()->getRewardDic();
	if (!pDic)
	{
		return 0;
	}

	RewardItem * pItem = new RewardItem((*pDic)[position].goodsList);

	if (!pItem)
	{
		return 0;
	}

	OnlineRewardProxy * pProxy = (OnlineRewardProxy *)g_pFacade->retrieveProxy(AppFacade_OnlineReward_Proxy);
	//menu
	if (pProxy)
	{
		int activeAwardIsGet = pProxy->_presentValue;
		int curDayIndex = pProxy->_addValue;

		CCLog("activeAwardIsGet = %x , curDayIndex = %x " , activeAwardIsGet , curDayIndex);
		
		if (position <= curDayIndex-1)
		{
			if (position == (curDayIndex-1))
			{
				if ((1 << position) & activeAwardIsGet)
				{
					CCSprite * pGetedSprite = CCSprite::spriteWithSpriteFrameName("reward/geted.png");
					pGetedSprite->setPosition(ccp(POSX(640) , POSX(60)));
					pItem->addChild(pGetedSprite , 1);
				}
				else
				{
					CCSprite * pNormal = CCSprite::spriteWithSpriteFrameName("button3_0.png");
					CCSprite * pSelect = CCSprite::spriteWithSpriteFrameName("button3_1.png");
					CCSprite * pDisable = CCSprite::spriteWithSpriteFrameName("button3_2.png");
					CCMenuItemSprite * pMenuItem = CCMenuItemSprite::itemFromNormalSprite(
						pNormal,
						pSelect,
						pDisable,
						this,
						menu_selector(RewardListView::onClickGetReward));
					pMenuItem->setPosition(ccp(POSX(640) , POSX(60)));

					CCSize size = pMenuItem->getContentSize();
					CCLabelTTF * pLab = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("RED001").c_str() , CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentCenter , "Arial" , POSX(26));
					pLab->setPosition(ccp(size.width/2 , size.height/2));
					pLab->setColor(ccc3(255,215,0));
					pMenuItem->addChild(pLab , 0);

					CCMenu * pMenu = CCMenu::menuWithItem(pMenuItem);
					pMenu->setPosition(ccp(0,0));
					pMenu->setTouchLayer(TLE::WindowLayer - 2);
					pItem->addChild(pMenu , 1);
				}
			}
			else if (position < (curDayIndex - 1))
			{
				std::string strPath("");
				if ((1 << position) & activeAwardIsGet)
				{
					strPath = "reward/geted.png";
				}
				else
				{
					strPath = "reward/overtime.png";
				}				
				CCSprite * pGetedSprite = CCSprite::spriteWithSpriteFrameName(strPath.c_str());
				pGetedSprite->setPosition(ccp(POSX(640) , POSX(60)));
				pItem->addChild(pGetedSprite , 1);
			}
		}

		if ((curDayIndex == getCount()) && ((1 << (getCount()-1)) & activeAwardIsGet) )
		{
			if (ViewManager::getInstance()->_secNavigate)
			{
				if (ViewManager::getInstance()->_secNavigate->getChildByTag(SecNavigate::TAG_LOGIN_REWARD))
				{
					ViewManager::getInstance()->_secNavigate->removeButton(SecNavigate::TAG_LOGIN_REWARD);
				}
			}
		}
	}

	// descript
	char path[32] = {0};
	sprintf(path , ValuesUtil::Instance()->getString("RED002").c_str() , position + 1);
	CCLabelTTF * pLabDis = CCLabelTTF::labelWithString( path , CCSizeMake(POSX(300) , POSX(30)) , CCTextAlignmentCenter , "Arial" , POSX(30));
	pLabDis->setColor(ccc3(12,233,25));
	pLabDis->setPosition(ccp(POSX(55) , POSX(60)));
	pItem->addChild(pLabDis , 1);

	((LayerNode *)pItem)->setvisibleSize(pItem->getContentSize());

	return ((LayerNode *)pItem);
}

void RewardListView::onItemClickListener( LayerNode *itemCell, int position )
{

}

void RewardListView::onItemTouchListener( LayerNode *itemCell, int position )
{

}

void RewardListView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{

}

void RewardListView::onClickGetReward(CCObject * pSender)
{
	RewardMediator * pRewardM = (RewardMediator *)g_pFacade->retrieveMediator(AppFacade_OnlineReward_Mediator);
	if (pRewardM)
	{
		pRewardM->getADReward();
		pRewardM->getADRewardInfo();
	}

	// new hand
	if (ViewManager::getInstance()->_pOLRewardView && NewhandManager::Instance()->_isNewAcount)
	{
		ViewManager::getInstance()->_pOLRewardView->clickCloseHandler(0);
	}
}