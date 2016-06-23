#include "ReserveDepot.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "model/egg/EggProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "GoodsItem.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "view/egg/EggMediator.h"

#define w_bg1 POSX(928.0f)
#define h_bg1 POSX(562.0f)

#define w_bg2 POSX(910.0f)
#define h_bg2 POSX(524.0f)

const float FontSize = 24.0f;
const float FontSize2 = 24.0f;

ReserveDepot::ReserveDepot()
{
	_txtNum = 0;
		
	/** 保存当前点击的蛋蛋 */
	_curEggId = -1;
	/** 一共60个物品格子 */
	totalGrid = 30;
	/** 一共5页 */
	totalPage = 10;

	_curPage = 1;

	_goodsContainer = 0;

	_dispatcher = GameDispatcher::getInstance();
}

ReserveDepot::~ReserveDepot()
{}

bool ReserveDepot::init()
{
	if (!LayerNode::init())
		return false;
	this->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
	//_goodsContainer
	{
		LayerNode* layer = new LayerNode();
		layer->init();
		
		this->addChild(layer,3);
		layer->release();

		_goodsContainer = layer;
	}
	//_txtNum 
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("EGG006").c_str(), CCSizeMake(POSX(300), POSX(46.0f)), CCTextAlignmentLeft, "Arial", POSX(30.0f));
		pLabel->setPosition(ccp(POSX(44), POSX(640-580)));
		pLabel->setAnchorPoint(ccp(0, 0));
		this->addChild(pLabel, 4);
		pLabel->setColor(ccc3(254, 255, 91));	

		_txtNum = pLabel;
	}
	//_pageText
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("1/10", CCSizeMake(POSX(300), POSX(46.0f)), CCTextAlignmentCenter, "Arial", POSX(38.0f));
		pLabel->setPosition(ccp(POSX(472), POSX(640-580)));
		this->addChild(pLabel, 4);
		pLabel->setColor(ccc3(254, 255, 91));	

		_pageText = pLabel;
	}
	//
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	{
		CCUIBackground* _bg0 = new CCUIBackground();
		_bg0->initWithFile("assets/ui/ui2.png", CCPointZero,CCPointZero,screenSize);
		this->addChild(_bg0, 0);
		_bg0->release();
	}
	{
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(16.0f), POSX(12.0f)), ccp(0,0), CCSizeMake(w_bg1, h_bg1));
		this->addChild(_bg1, 1);
		_bg1->release();
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(25.0f), POSX(32.0f)), ccp(0,0), CCSizeMake(w_bg2, h_bg2));
		this->addChild(_bg2, 1);
		_bg2->release();
	}
	//_btnGetAll
	{
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/button3_0.png", 
			"assets/ui/egg/button3_1.png",
			"assets/ui/button2.png",
			this, 
			menu_selector(ReserveDepot::getAllHandler) );
		_btn->setPosition(ccp(POSX(845), POSX(640-580)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_egg);
		this->addChild(buttonMenu, 3);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("EGG035").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));
	}
	//X
	{
		CCMenuItemSprite* _btn = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png"), 
			CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png"),  
			this, 
			menu_selector(ReserveDepot::close) );
		_btn->setPosition(ccp(POSX(928), POSX(640-28)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_egg);
		this->addChild(buttonMenu);	
	}
	//bag_zhuangshi.png
	{
		//
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/bag_zhuangshi.png");
		sp->setPosition(ccp(POSX(92), POSX(640-305)));
		this->addChild(sp,3);	
		sp->release();
		sp->setFlipX(true);

		SpriteNode* spr = new SpriteNode();
		spr->initWithFile("assets/ui/egg/bag_zhuangshi.png");
		spr->setPosition(ccp(POSX(847), POSX(640-305)));
		this->addChild(spr,3);	
		spr->release();
		
	}
	//_btnPrev 
	{
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/btnpage_0.png", 
			"assets/ui/egg/btnpage_1.png", 
			this, 
			menu_selector(ReserveDepot::prevHandler) );
		_btn->setPosition(ccp(POSX(92), POSX(640-305)));
		_btn->setRotation(180.f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_egg);
		this->addChild(buttonMenu, 4);	
	}
	//_btnNext
	{
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/btnpage_0.png", 
			"assets/ui/egg/btnpage_1.png", 
			this, 
			menu_selector(ReserveDepot::nextHandler) );
		_btn->setPosition(ccp(POSX(847), POSX(640-305)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_egg);
		this->addChild(buttonMenu, 4);	
	}
	//frames
	CCPoint orginpos = ccp(POSX(140+17+77/2), POSX(550-9-77));
	for (int i = 0; i < totalGrid; i++)
	{
		int row = i/6;
		int lan = i%6;
		
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/item_bg_70.png");
		sp->setAnchorPoint(ccp(0, 0));
		this->addChild(sp, 2);
		sp->release();
		sp->setPosition(ccp(orginpos.x+ POSX(lan*(77+17)) , orginpos.y- POSX(row*(77+9))));
	}
	return true;
}

void ReserveDepot::prevHandler(CCObject* pSender)
{
	_curPage = _curPage-1;
	if (_curPage > totalPage) _curPage = totalPage;
	if (_curPage < 1) _curPage = 1;

	buildList(_curPage);
}
		
void ReserveDepot::nextHandler(CCObject* pSender)
{
	_curPage = _curPage+1;
	if (_curPage > totalPage) _curPage = totalPage;
	if (_curPage < 1) _curPage = 1;

	buildList(_curPage);
		
}

void ReserveDepot::close(CCObject* pSender)
{
	ReserveDepot* _depotView = (ReserveDepot*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_reserveDepot);
	if (_depotView)
	{
		_depotView->setIsVisible(false);
	}
}

/** 更新蛋蛋数量 */
void ReserveDepot::updateEggNum(int num)
{
	if(_txtNum)
	{
		char str[30];
		sprintf(str, "%s%d/%d", ValuesUtil::Instance()->getString("EGG006").c_str(), num, totalGrid * totalPage);
		_txtNum->setString(str);
	}
}

/** 一键拾取事件 */
void ReserveDepot::getAllHandler(CCObject* pSender)
{
	_dispatcher->dispatchEvent(EggMediator::GET_ALL, 0);
}
	

/** 创建仓库物品列表 */
void ReserveDepot::buildList(int page)
{
	if(page != _curPage)
	{
		page = _curPage;
	}

	_eggDic.clear();
	_goodsContainer->removeAllChildrenWithCleanup(true);

	CCPoint orginpos = ccp(POSX(140+17+77/2), POSX(550-9-77));
	std::vector<EggInfo>* arr = ((EggProxy*)g_pFacade->retrieveProxy(AppFacade_EGG_CHANGE))->getEggsByPage(page);
	if(arr != 0)
	{
		int len = arr->size();
		for (int i = 0; i < totalGrid; i++)
		{
			GoodsItem* item = new GoodsItem();
			item->init();
			item->setIsRelativeAnchorPoint(true);
			item->setAnchorPoint(ccp(0, 0));
			int row = i/6;
			int lan = i%6;
			item->setPosition(ccp(orginpos.x+ POSX(lan*(77+17)) , orginpos.y- POSX(row*(77+9))));
			if (i < len)
			{
				EggInfo egg = (*arr)[i];
				item->addGoods(egg);
				_eggDic[egg.eggId] = item;
			}
			_goodsContainer->addChild(item);
			item->release();
		}
	}
	updatePage(page);
}

void ReserveDepot::updatePage(int page)
{
	if(_pageText)
	{
		char str[30];
		sprintf(str, "%d/%d", page, totalPage);
		_pageText->setString(str);
	}
}