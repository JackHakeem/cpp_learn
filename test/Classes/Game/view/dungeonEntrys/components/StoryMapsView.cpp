#include "StoryMapsView.h"
#include "manager/PopEventName.h"
#include "PopUIBg.h"
//#include "CCUIBackground.h"
#include "../DungeonEntrysMediator.h"
#include "manager/ViewManager.h"

StoryMapsView::StoryMapsView()
{
	_storyCityList = NULL;
	_storyMapList = NULL;
	_container1 = NULL;
	_container2 = NULL;
	layer = NULL;
}

bool StoryMapsView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
		"assets/ui/entrance/entranceIcon/res_entrance_ic.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
		"assets/ui/entrance/res_entrance.plist");

	this->key = PopEventName::STORYMAP_COPYS;
	this->setIsTouchEnabled(true);
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(CCPointZero);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);
	setPopContentSize(winSize);

	if(!layer)
	{
		layer = new CCLayer();
		layer->init();
		layer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
		layer->setAnchorPoint(CCPointZero);
	}

	addScrollViews();

	if(layer->getParent() == NULL)
	{
		this->addChild(layer, STORYMAP_LAYER);
	}

	return true;
}

void StoryMapsView::clickCloseHandler(CCObject* pSender)//kevinshit
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
	//	"assets/ui/entrance/entranceIcon/res_entrance_ic.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
	//	"assets/ui/entrance/res_entrance.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey(
	//	"assets/ui/entrance/entranceIcon/res_entrance_ic.pvr.ccz");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey(
	//	"assets/ui/entrance/res_entrance.pvr.ccz");

	setisPop(false);
}

void StoryMapsView::addScrollViews()
{
	//if (!dungeonScrollView) // passive
	//{
	//	//dungeonScrollView = new DungeonEntrysCreate(CCRectMake(18,33,437,447));
	//	CCSize size = this->getContentSize();
	//	float left = 18.0f;
	//	float bottom = 18.0f;
	//	dungeonScrollView = new DungeonEntrysCreate(CCRectMake(left, bottom, size.width - (2 * left), size.height - (2 * bottom)));
	//	this->addChild(dungeonScrollView);
	//}
	//if(dungeonScrollView)
	//{
	//	dungeonScrollView->addLayerByTag(0);
	//	dungeonScrollView->addDungeonEntries();
	//}
	if(!_container1)
	{
		_container1 = new CCUIBackground();
		//POSX edwardliu
		_container1->initWithSpriteFrame("ui2.png", ccp(POSX(26), POSX(20)), ccp(0, 0), CCSizeMake(POSX(240), POSX(525)));
		layer->addChild(_container1, STORYMAP_CONTAINER1);
		//Doyang 20120712
		_container1->release();
	}

	if(!_container2)
	{
		_container2 = new CCUIBackground();
		//POSX edwardliu
		_container2->initWithSpriteFrame("ui2.png", ccp(POSX(266), POSX(20)), ccp(0, 0), CCSizeMake(POSX(670), POSX(525)));
		layer->addChild(_container2, STORYMAP_CONTAINER2);
		//Doyang 20120712
		_container2->release();
	}

	//_viewSize = _container1->getContentSize();
	//_container1->release();

	if(!_storyCityList)
	{
		_storyCityList = new StoryCityLists();
		_storyCityList->setAnchorPoint(CCPointZero);
		_storyCityList->setPosition(ccp(POSX(26), POSX(20)));
		layer->addChild(_storyCityList, 10);
		_storyCityList->release();

		_storyCityList->startListViewHandler();
	}

	if(!_storyMapList)
	{
		_storyMapList = new StoryMapLists();
		_storyMapList->setAnchorPoint(CCPointZero);
		_storyMapList->setPosition(ccp(POSX(266), POSX(20)));
		layer->addChild(_storyMapList, 10);
		_storyMapList->release();

		_storyMapList->startListViewHandler();
	}
}

void StoryMapsView::openCity(int index, bool open)
{
	if(_storyCityList)
	{
		_storyCityList->initDataList(index, open);
	}
}

void StoryMapsView::selectTab(int tab, bool byInit)
{
	/*if(tab >= 1 && tab <= 7)
	{
		var preTabMc:MovieClip = citysTab["_tab"+curTab];
		if(preTabMc){
			preTabMc.gotoAndStop(1);
			preTabMc.addEventListener(MouseEvent.ROLL_OVER,onRollOver);
			preTabMc.addEventListener(MouseEvent.ROLL_OUT,onRollOut);
		}
		curTab = tab;
		var curTabMc:MovieClip = citysTab["_tab"+curTab];
		if(curTabMc){
			curTabMc.gotoAndStop(2);
			curTabMc.removeEventListener(MouseEvent.ROLL_OVER,onRollOver);
			curTabMc.removeEventListener(MouseEvent.ROLL_OUT,onRollOut);
		}
		if(byInit){
			if(tab == 6){
				citysTab.x = -rollDistance;
			}
			if(tab == 7){
				citysTab.x = -2*rollDistance;
			}
			if(tab == 1){
				citysTab.x = 0;
			}
			if(tab == 2){
				citysTab.x = 0;
			}
			updateBackAndNextBtn();
		}
	}*/
}

void StoryMapsView::setViewAdapter()
{
	if(_storyCityList)
		_storyCityList->setViewAdapter();
}

void StoryMapsView::addIcons(std::vector<MapData>& data)
{
	if(!_storyMapList)
		return;

	int tipId = 0;
	std::vector<MapData>::iterator iter = data.begin();
	for(; iter != data.end(); ++iter)
	{
		MapData obj = *iter;
		if(obj._star == 0)
		{
			tipId = obj._id;
		}
		_storyMapList->initDataList(*iter, true);
	}

	if(tipId != 0)
	{
		_storyMapList->setLastMapTip(tipId);
	}

	// LH
	_storyMapList->setNowMapId(tipId);


	if(_storyMapList)
		_storyMapList->setViewAdapter();

	//var tipId:int = 0;
	//for each(var obj:Object in data)
	//{
	//	var tmpPic:PicLoadingContent = new PicLoadingContent("assets/icon/mapIcon/"+obj.id+".png");
	//	(icon["_monsterContainer"] as MovieClip).addChild(tmpPic);
	//	(icon["_txtName"] as TextField).text = obj.name;
	//	tmpPic.x = -67;
	//	tmpPic.y = -62;
	//	var mapIcon:MapIcon = new MapIcon(obj.id,icon);
	//	var pos:Point = getNextPoint();
	//	mapIcon.x = pos.x;
	//	mapIcon.y = pos.y;
	//	iconArea.addChild(mapIcon);
	//	if(obj.star == 0)
	//	{
	//		// 0表示已开启未通关
	//		icon.gotoAndStop(1);
	//		mapIcon.addEventListener(MouseEvent.CLICK,onClickMapIcon);
	//		tipId = mapIcon.id;
	//	}
	//	else if(obj.star == 4)
	//	{
	//		// 4表示未开启
	//		icon.gotoAndStop(3);
	//	}
	//	else
	//	{
	//		icon.gotoAndStop(1);
	//		(icon["_grade"] as MovieClip).gotoAndStop(obj.star + 1);
	//		mapIcon.addEventListener(MouseEvent.CLICK,onClickMapIcon);
	//	}
	//	mapIcon.mouseChildren = false;
	//}
}

void StoryMapsView::deleteIcons()
{
	if(_storyMapList)
	{
		_storyMapList->deleteIcons();
	}
}

void StoryMapsView::clearCityDataList()
{
	if(_storyMapList)
	{
		_storyCityList->clearDataList();
	}
}

StoryMapsView::~StoryMapsView()
{
	DungeonEntrysMediator* pMeditor = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	pMeditor->storyMapsView = 0;
	ViewManager::getInstance()->storyMapsView = 0;

	if (_storyMapList)
	{
		_storyMapList->removeFromParentAndCleanup(true);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
		"assets/ui/entrance/entranceIcon/res_entrance_ic.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
		"assets/ui/entrance/res_entrance.plist");

	CCTextureCache::sharedTextureCache()->removeTextureForKey(
		"assets/ui/entrance/entranceIcon/res_entrance_ic.pvr.ccz");
	CCTextureCache::sharedTextureCache()->removeTextureForKey(
		"assets/ui/entrance/res_entrance.pvr.ccz");
}

//void StoryMapsView::removeDataObjectChild()
//{
//	/*if(_storyMapList && _storyMapList->getParent())
//	{
//		_storyMapList->removeFromParentAndCleanup(true);
//		_storyMapList = NULL;
//	}*/
//	
//	PopContainer::removeDataObjectChild();
//
//}
