#include "HeroRankView.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"
#include "socket/command/s28/SCMD285.h"
#include "manager/TouchLayerEnum.h"
#include "HeroRankItem.h"
#include "model/arena/ArenaProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

const float FontSize = 30.0f;

HeroRankView::HeroRankView()
{

}

HeroRankView::~HeroRankView()
{
	ArenaProxy* proxy = (ArenaProxy*)g_pFacade->retrieveProxy(AppFacade_ARENA_PROXY);
	proxy->_heroRankView = 0;

	std::vector<CCObject*>::iterator iter = _scrollPaneContent.begin();
	for (;iter != _scrollPaneContent.end();iter++)
	{
		HeroRankItem * pHeroRankItem = (HeroRankItem *)(*iter);
		if (pHeroRankItem && pHeroRankItem->getParent())
		{
			pHeroRankItem->removeFromParentAndCleanup(true);
			pHeroRankItem->release();
		}
	}
/*
	CCMutableArray<LayerNode *> * pLayerItems = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it = pLayerItems->begin();
	for (it;it != pLayerItems->end();it++)
	{
		LayerNode * pLayerItem = (LayerNode *)(*it);
		if (pLayerItem && pLayerItem->getParent())
		{
			pLayerItem->removeFromParentAndCleanup(true);
			pLayerItem->release();
		}
	}*/

	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/arena/res_arena_title.pvr.ccz");	
}

bool HeroRankView::init()
{
	if (!LayerNode::init())
		return false;

	this->setPosition(ccp(POSX((960-600)/2), POSX(640-540)));
	this->setContentSize(CCSizeMake(POSX(600), POSX(450)));

	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("ui.png", ccp(0, 0), ccp(POSX(6), POSX(7)), CCSizeMake(POSX(600), POSX(450)));
	this->addChild(_bg1, HeroRankViewZ_bg1, HeroRankViewTAG_bg1);
	//Doyang 20120712
	_bg1->release();
	//
	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(10), POSX(40)), ccp(0,0), CCSizeMake(POSX(580), POSX(370)));
	this->addChild(_bg2, HeroRankViewZ_bg2, HeroRankViewTAG_bg2);
	//Doyang 20120712
	_bg2->release();


	//list
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(10), POSX(44), POSX(580), POSX(300)), false);
	_pListView->setIsRelativeAnchorPoint(true);
    _pListView->setAnchorPoint(ccp(0,0));
	_pListView->setSpacingVertical(0);

	_pListView->setWorldSpaceLeftBottomPoint(ccp(POSX(10+200), POSX(640-540+44)));//+(960-600)/2  
	_pListView->setOnItemActionListener(this);
	this->addChild(_pListView, HeroRankViewZ_ListView, HeroRankViewTAG_ListView);
	_pListView->release();//Kenfly 20130125
	//
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(HeroRankView::clickClose) );
		_btnClose->setPosition(ccp(POSX(600), POSX(450)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer-1);
		this->addChild(buttonMenu, HeroRankViewZ_closebtn, HeroRankViewTAG_closebtn);		
	}
	//
	float height_offset = 640.0f-275.0f;
	//排名
	{
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC035").c_str(), CCSizeMake(POSX(60), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(56), POSX(height_offset)));
		pLable_1->setColor(ccc3(255, 255, 255));
		this->addChild(pLable_1, HeroRankViewZ_title, HeroRankViewTAG_title_0);		
	}
	//玩家
	{
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC036").c_str(), CCSizeMake(POSX(300), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(380), POSX(height_offset)));
		pLable_1->setColor(ccc3(255, 255, 255));
		this->addChild(pLable_1, HeroRankViewZ_title, HeroRankViewTAG_title_1);		
	}	
	//等级
	{
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC037").c_str(), CCSizeMake(POSX(80), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(500), POSX(height_offset)));
		pLable_1->setColor(ccc3(255, 255, 255));
		this->addChild(pLable_1, HeroRankViewZ_title, HeroRankViewTAG_title_2);		
	}
	//每天22点统计...
	{
		CCLabelTTF* pLable_1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC038").c_str(), CCSizeMake(POSX(580), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLable_1->setPosition(ccp(POSX(300), POSX(20)));
		pLable_1->setColor(ccc3(254, 189, 0));
		this->addChild(pLable_1, HeroRankViewZ_title, HeroRankViewTAG_title_3);		
	}
	//英雄榜
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/arena/res_arena_title.plist");
		SpriteNode* titleSp = new SpriteNode();
		titleSp->initWithSpriteFrameName("arena/herorank_title.png");
		titleSp->setPosition(ccp(POSX(300), POSX(640.0f-212.0f)));
		this->addChild(titleSp, HeroRankViewZ_title, HeroRankViewTAG_title_name);
		titleSp->release();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/arena/res_arena_title.plist");
	}
	return false;
}

void HeroRankView::updateRes()
{
	_pListView->setAdapter(this);
}

int HeroRankView::getCount()
{
	return _scrollPaneContent.size();
}

LayerNode * HeroRankView::getView( int position )
{
	if (position >= 0 && position < _scrollPaneContent.size())
		return (LayerNode*)_scrollPaneContent[position];
	else
		return 0;
}

void HeroRankView::clickClose(CCObject* pSender)
{
	HeroRankView* pHRV = (HeroRankView*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_heroUi);
	if (pHRV)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_heroUi, true);
	}
}

void HeroRankView::update(SCMD285* param)
{
	std::vector<HeroRankVo> arr;
	
	int arrsize = param->d_rankArr.size();
	int preRank = 0;
	//HeroRankVo* heroRankVo = 0;
	for (int i = 0; i < arrsize; i++)
	{
		SCMD285Node* node = &param->d_rankArr[i];

		while (preRank < node->a_rank) 
		{
			HeroRankVo heroRankVo;
			heroRankVo.rank = preRank+1;// 从0-24 
			heroRankVo.id = 0;
			heroRankVo.lev = getMaxLevByRange(param->a_meRank);  // 当时的竞技场区间 
			arr.push_back(heroRankVo);
			preRank++;
		}

		HeroRankVo heroRankVo;
		heroRankVo.rank = node->a_rank + 1;  // 从0-24 
		heroRankVo.id = node->b_playerId;
		heroRankVo.name = node->c_playerName;
		heroRankVo.lev = node->d_level;
		arr.push_back(heroRankVo);
				
		preRank = heroRankVo.rank;
	}

	while (preRank<25)
	{  // max is 24
		HeroRankVo heroRankVo;
		heroRankVo.rank = preRank + 1;  
		heroRankVo.id = 0;
		heroRankVo.lev = getMaxLevByRange(param->a_meRank);
		arr.push_back(heroRankVo);
		preRank++;

	}
			
	//arr.sort
 	createItems(arr);

	arr.clear(); // LH0717LEAK
}

void HeroRankView::createItems(std::vector<HeroRankVo>& arr)
{
	_scrollPaneContent.clear();
	//
	for (int i = 0;i < arr.size(); i++)
	{
		HeroRankItem* newitem = new HeroRankItem();
		newitem->init(arr[i]);
		_scrollPaneContent.push_back(newitem);
	}

	updateRes();
}



// 区间 range取值  0 1 2 3 对应水晶等级 21-40  41-60 61-80 81-100
int HeroRankView::getMaxLevByRange(int range)
{
	int maxLev = 0;
	switch(range)
	{
		case 0:
			maxLev = 40;
			break;
		case 1:
			maxLev = 60;
			break;
		case 2:
			maxLev = 80;
			break;
		case 3:
			maxLev = 100;
			break;
		default:
			maxLev = 40;
	}
	return maxLev;
}