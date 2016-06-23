#include "PoolView.h"
#include "utils/TipHelps.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "ReserveDepot.h"
#include "manager/LayerManager.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "RewardPanel.h"
#include "manager/TouchLayerEnum.h"
#include "ShowItem.h"

PoolView::PoolView()
{
	_tabTips = 0;
	_txtGold = 0;
	_pContainer = 0;
	_txtCapacity = 0;

	plegeType[0] = 1;
	plegeType[1] = 2;

	plegeNum[0] = 1;
	plegeNum[1] = 10;
	plegeNum[2] = 50;

	plegeCost[0] = ValuesUtil::Instance()->getString("EGG020");
	plegeCost[1] = ValuesUtil::Instance()->getString("EGG021");
	plegeCost[2] = ValuesUtil::Instance()->getString("EGG022");

	total = 300;
	_type = 0;

	_lowPic = 0;
	_myRewardPanel = 0;
	_otherRewardPanel = 0;

	for (int i = 0; i < 10; i++)
		_eggGridDic[i] = 0;

	_dispatcher = GameDispatcher::getInstance();
}

PoolView::~PoolView()
{}

/** 设置圣光许愿池是否可见 */
void PoolView::setTab(bool b)
{
	if(_tabTips)
	{
		//_tabTips.dispose();
		//_tabTips = null;
	}
	if (b)
	{
		_type = plegeType[1];
		setPrizeContainer(2);
		showBg(2);
	}
	else
	{
		_type = plegeType[0];
		setPrizeContainer(1);
		showBg(1);
	}
	//if(b)
	//{
	//	_tab2.filters = [];
	//	_tab1.gotoAndStop(1);
	//	_tab2.gotoAndStop(2);
	//	_tab2.addEventListener(MouseEvent.CLICK,tabChange);
	//	_type = plegeType[1];
	//	showBg(2);
	//	setPrizeContainer(2);
	//}else{
	//	Utils.applyBlackAndWhiteFilter(_tab2);
	//	_tab1.gotoAndStop(2);
	//	_tab2.gotoAndStop(1);
	//	_tabTips = new TipHelps();
	//	_tabTips.setToolTips(_tab2,LangManager.getText("EGG023"));
	//	_type = plegeType[0];
	//	showBg(1);
	//	setPrizeContainer(1);
	//}
}

/** 打开宝箱*/
void PoolView::bagHandler(CCObject* pSender)
{
	_dispatcher->dispatchEvent(PopEventName::SHOW_UI_EGG_DEPOT, 0);
}

/** 更新自己的许愿历史奖励 */
void PoolView::updateMyReward(std::vector<EggInfo> arr)
{
	if(_myRewardPanel){
		_myRewardPanel->updateContianer(arr);
	}
}
		
/** 更新其他玩家的许愿历史奖励 */
void PoolView::updateOtherReward(std::vector<EggInfo> arr)
{
	if(_otherRewardPanel){
		_otherRewardPanel->updateContianer(arr);
	}
}

/** 更新心愿宝箱里的蛋蛋数量，显示在许愿池面板上 */
void PoolView::updateEggNumInDepot(int num)
{
	if(_txtCapacity)
	{
		char str[30];
		sprintf(str, "%s%d/%d", ValuesUtil::Instance()->getString("EGG002").c_str(), num, total);
		_txtCapacity->setString(str);
	}
}

/** 更新获得的特殊奖励（装备蛋，佣兵蛋） */
void PoolView::updatePrize()
{
	//if(!_prizeContainer){
	//	_prizeContainer = new PrizeContainer();
	//	__skin["_itemloc"].addChild(_prizeContainer);
	//}
	//_prizeContainer.buildList(arr);
}

void PoolView::setPrizeContainer(int type)
{
	//clean
	for (int i = 0; i < 10; i++)
	{
		if (_eggGridDic[i])
			_eggGridDic[i]->removeFromParentAndCleanup(true);
		_eggGridDic[i] = 0;
	}
	//create

	if (type == 1)
	{
		std::string picpath[10] =
		{
			"assets/ui/egg/egggriddic/orange_egg_open.png",//120X120 {1,0,5}
			"assets/ui/egg/egggriddic/red_egg_open.png",//120X120 {1,0,6}
			"assets/ui/egg/egggriddic/purple_egg_open.png",//70X70 {1,0,4}
			"assets/ui/egg/egggriddic/horner.png",//70X70 3,5,101
			"assets/ui/egg/egggriddic/gold.png",//70X70  3,1,102

			"assets/ui/egg/egggriddic/spirite.png",//70X70  3,3,102
			"assets/ui/egg/egggriddic/silver.png",//70X70  3,2,102
			"assets/ui/egg/egggriddic/practice.png",//70X70  3,3,102
			"assets/ui/egg/egggriddic/da_mo_jing_shi.png",//70X70  3,6,101
			"assets/ui/egg/egggriddic/xiao_mo_jing_shi.png",//70X70 3,6,102
		};
		int picItemIndex[10][3] =
		{
			{1,0,5}, {1,0,6}, {1,0,4}, {3,5,101}, {3,2,101},
			{3,3,102}, {3,2,102}, {3,3,102}, {3,6,101}, {3,6,102},		
		};
		//
		/*CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::WindowLayer_egg);
		_pContainer->addChild(buttonMenu, 2);	
		buttonMenu->release();*/

		for (int i = 0; i < 10; i++)
		{	
			_eggGridDic[i] = new ShowItem();
			_eggGridDic[i]->init(picpath[i]);
			_eggGridDic[i]->getEggExplain(picItemIndex[i][0], picItemIndex[i][1], picItemIndex[i][2]);
			//	s::itemFromNormalImage(
			//	picpath[i].c_str(), 
			//	picpath[i].c_str(),
			//	this, 
			//	menu_selector(PoolView::touchItem) );
			////_btn->setPosition(ccp(POSX(112+i*200), POSX(640-553)));//要配
			//_eggGridDic[i]->setTag(i);

			_pContainer->addChild(_eggGridDic[i], 5);
			_eggGridDic[i]->release();
		}	
		//
		//set pos
		_eggGridDic[0]->setPosition(ccp(POSX(225), POSX(640-315)));
		//_eggGridDic[0]->setScale(0.9f);
		_eggGridDic[1]->setPosition(ccp(POSX(370), POSX(640-315)));
		//_eggGridDic[1]->setScale(0.9f);

		_eggGridDic[2]->setPosition(ccp(POSX(190), POSX(640-185)));

		_eggGridDic[3]->setPosition(ccp(POSX(412), POSX(640-185)));

		_eggGridDic[4]->setPosition(ccp(POSX(105), POSX(640-262)));
		_eggGridDic[5]->setPosition(ccp(POSX(497), POSX(640-262)));

		_eggGridDic[6]->setPosition(ccp(POSX(105), POSX(640-360)));
		_eggGridDic[7]->setPosition(ccp(POSX(497), POSX(640-360)));

		_eggGridDic[8]->setPosition(ccp(POSX(190), POSX(640-444)));
		_eggGridDic[9]->setPosition(ccp(POSX(412), POSX(640-444)));
	}
	else
	{
	//未开放
	}
}


void PoolView::touchItem(CCObject* pSender)
{
	int tag = ((CCNode*)pSender)->getTag();
	_eggGridDic[tag]->_tips->rollOverHander();
}

void PoolView::close(CCObject* pSender)
{
	//删除心愿宝箱
	ReserveDepot* _depotView = (ReserveDepot*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_reserveDepot);
	if (_depotView)
		_depotView->removeFromParentAndCleanup(true);
	//
	this->clickCloseHandler(0);
}

/**
	* 设置许愿池背景 
	* @param type 	1精灵 2圣光
	* 
	*/		
void PoolView::showBg(int type)
{
	if(type == 1)
	{
		//__skin["_txt1"].visible = true;
		//__skin["_txt2"].visible = false;
		if (_lowPic)
			_lowPic->removeFromParentAndCleanup(true);
		if(!_lowPic)
		{
			_lowPic = new SpriteNode();
			_lowPic->initWithFile("assets/ui/egg/water_bg.png");
			_pContainer->addChild(_lowPic, 0);
			_lowPic->setAnchorPoint(ccp(0,0));
			_lowPic->setPosition(ccp(POSX(30-2), POSX(640-500-12)));
			_lowPic->release();
		}
	}
	else
	{
		if (_lowPic)
			_lowPic->removeFromParentAndCleanup(true);
		if(!_lowPic)
		{
			_lowPic = new SpriteNode();
			_lowPic->initWithFile("assets/ui/egg/water_bg.png");
			_pContainer->addChild(_lowPic, 0);
			_lowPic->setAnchorPoint(ccp(0,0));
			_lowPic->setPosition(ccp(POSX(30-2), POSX(640-500-12)));
			_lowPic->release();
		}
	}
}

/** 设置剩余金币数 */
void PoolView::setGold(int num)
{
	if(_txtGold)
	{
		char str[40];
		sprintf(str, "%s%d", LangManager::getText("EGG003").c_str(), num);
		_txtGold->setString(str);
	}
}