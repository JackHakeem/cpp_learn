#include "RankingView.h"
#include "CapacityPanel.h"
#include "RenownPanel.h"
#include "manager/PopManage.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "../RankingMediator.h"

RankingView::RankingView()
{
	_pContainer = 0;
	_curTab = TAG_RENOWN_BTN;

	for (int i = 0; i < MAX_BTN_NUM; ++i)
		_rankingPanel[i] = 0;
}

RankingView::~RankingView()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist"); 
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_icon.pvr.ccz");
}

void RankingView::removeDataObjectChild()
{
	RankingMediator * pMediator = (RankingMediator *)g_pFacade->retrieveMediator(AppFacade_Ranking_Mediator);
	if (pMediator)
	{
		pMediator->_pRankingView = 0;
	}
}

bool RankingView::init()
{
    do
    {
		CC_BREAK_IF(! CCLayer::init());

		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist"); 

		_curTab = TAG_RENOWN_BTN;
		this->key = PopEventName::RANKING;
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->setPopContentSize(winSize);
		this->setContentSize(winSize);

        if (! _pContainer)
        {
            _pContainer = new CCLayer();
            this->addChild(_pContainer);
            _pContainer->setAnchorPoint(CCPointZero);
            _pContainer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
            _pContainer->release();
        }

		CC_BREAK_IF(! initTopButtons());

		//init title
		{
			SpriteNode* spTitle = new SpriteNode();
			if (spTitle->initWithFile("assets/ui/ranking/title.png"))
			{
				_pContainer->addChild(spTitle, 10);
				spTitle->release();
				spTitle->setPosition(ccp(POSX(565 - 90), POSX(640 - 85)));
			}
			else
				CC_SAFE_DELETE(spTitle);
		}
		return true;
    } while (0);
	CCLOG("RankingView: init faild!");
	return false;
}

bool RankingView::initTopButtons()
{
    do
    {
        ValuesUtil* pVU = ValuesUtil::Instance();
        CC_BREAK_IF(! pVU);
		//Begin : init fight button
		CCMenuItem*& pFightButton = _pButtons[TAG_CAPACITY_BTN];
		pFightButton = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this,
			menu_selector(RankingView::onTabHandler)
			);
		CCLabelTTF* pFightLabel = CCLabelTTF::labelWithString(pVU->getString("RK001").c_str(), g_sSimHeiFont, POSX(24));
		CC_BREAK_IF(! pFightButton || ! pFightLabel);
		pFightLabel->setPosition(ccp(POSX(154.0f/2.0f), POSX(61.0f/2.0f)));
		pFightButton->addChild(pFightLabel);
		pFightButton->setTag(TAG_CAPACITY_BTN);
		//End

		//Begin : init renown button
		CCMenuItem*& pRenownButton = _pButtons[TAG_RENOWN_BTN];
		pRenownButton = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this,
			menu_selector(RankingView::onTabHandler)
			);
		CCLabelTTF* pRenownLabel = CCLabelTTF::labelWithString(pVU->getString("RK002").c_str(), g_sSimHeiFont, POSX(24));
		CC_BREAK_IF(! pRenownButton || ! pRenownLabel);
		pRenownLabel->setPosition(ccp(POSX(154.0f/2.0f), POSX(61.0f/2.0f)));
		pRenownButton->addChild(pRenownLabel);
		pRenownButton->setTag(TAG_RENOWN_BTN);
		//End 

		CCMenu* pTabMenu = CCMenu::menuWithItems(pRenownButton, pFightButton, NULL);
		pTabMenu->setContentSize(CCSizeMake(POSX(570), POSX(61)));
		pTabMenu->setAnchorPoint(CCPointZero);
		pTabMenu->setPosition(ccp(POSX(141 + 20), POSX(575 + 15)));
		pTabMenu->alignItemsHorizontallyWithPadding(POSX(10.0f));
		pTabMenu->setTouchLayer(TLE::WindowLayer_Common_btn);

		_pContainer->addChild(pTabMenu);

		//set default
		for (int i = 0; i < MAX_BTN_NUM; ++i)
		{
			if (_pButtons[i])
				_pButtons[i]->setIsEnabled(true);
		}
		if (_pButtons[_curTab])
			_pButtons[_curTab]->setIsEnabled(false);
		return true;
    } while (0);
	return false;
}


void RankingView::showPanel(int tag)
{
	if (tag < 0 && tag >= MAX_BTN_NUM)
		return;

	RankingPanel* panel = 0;
	switch (tag)
	{
	case TAG_CAPACITY_BTN:
		panel = new CapacityPanel();
		break;
	case TAG_RENOWN_BTN:
		panel = new RenownPanel();
		break;
	}
	if (panel && panel->init())
	{
		panel->setAnchorPoint(CCPointZero);
		panel->setPosition(ccp(POSX(35.0f), POSX(30.0f)));
		_pContainer->addChild(panel);

		panel->release(); //LH20130110

		int type = panel->getRankType();
		_rankingPanel[tag] = panel;  //must before dispatchevent
		panel->addEventListener(RankingPanel::RANK_ITEM_SELECTED, this, callfuncND_selector(RankingView::onListItemSelected));
		dispatchEvent(REQUEST_RANKING_LIST, &type);
	}
	else
		CC_SAFE_DELETE(panel);
}

void RankingView::closePanel(int tag)
{
	if (tag < 0 && tag >= MAX_BTN_NUM)
		return;
	if (_rankingPanel[tag])
	{
		//_rankingPanel[tag]->removeAllChildrenWithCleanup(true);
		_rankingPanel[tag]->removeFromParentAndCleanup(true);
		_rankingPanel[tag] = 0;
	}
	
}

void RankingView::onTabHandler(CCObject* pSender)
{
	do 
	{
		CC_BREAK_IF(! pSender);
		int tab = ((CCNode*)pSender)->getTag();
		CC_BREAK_IF(_curTab == tab);

		if (_pButtons[_curTab])
			_pButtons[_curTab]->setIsEnabled(true);
		closePanel(_curTab);
				
		_curTab = tab;

		if (_pButtons[_curTab])
			_pButtons[_curTab]->setIsEnabled(false);
		showPanel(_curTab);
		
	} while (0);

}

void RankingView::updateRankList(const std::vector<RankItemVo>& array)
{
	do 
	{
		CC_BREAK_IF(array.empty());
		int type = array[0].type;

		for (int i = 0; i < MAX_BTN_NUM; ++i)
		{
			if (_rankingPanel[i] && _rankingPanel[i]->getRankType() == type)
			{
				_rankingPanel[i]->updateRankList(array);
				break;
			}
		}
	} while (0);
}

void RankingView::updateMyRank(int rank)
{
	do 
	{
		CC_BREAK_IF(! _rankingPanel[_curTab]);
		_rankingPanel[_curTab]->updateMyRank(rank);
	} while (0);
}

void RankingView::updateEquipments(const std::vector<EquipItemVo>& array)
{
	do 
	{
		CC_BREAK_IF(! _rankingPanel[_curTab]);
		_rankingPanel[_curTab]->updateEquipments(array);
	} while (0);
}

void RankingView::onListItemSelected(CCNode* node, void* data)
{
	dispatchEvent(REQUEST_EQUIP_INFO, data);
}

void RankingView::clickCloseHandler(CCObject* pSender)
{
	closePanel(_curTab);
	PopContainer::clickCloseHandler(pSender);
}

void RankingView::popUpView()
{
	if (this->getisPop())
	{
		closePanel(_curTab);
		this->setisPop(false);
	}
	else
	{
		showPanel(_curTab);
		this->setisPop(true);

		release(); //LH20130110
	}
}