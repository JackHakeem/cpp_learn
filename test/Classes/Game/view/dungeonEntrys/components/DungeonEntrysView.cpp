#include "DungeonEntrysView.h"
#include "CCUIBackground.h"
#include "manager/PopEventName.h"
#include "PopUIBg.h"
#include "utils/ScaleUtil.h"
#include "manager/ViewManager.h"
#include "../DungeonEntrysMediator.h"
#include "manager/TouchLayerEnum.h"

DungeonEntrysView::DungeonEntrysView()
{
	dungeonScrollView = NULL;
	_pContainer = 0;
}

bool DungeonEntrysView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->key = PopEventName::JUMP_COPYS;
	this->setIsTouchEnabled(true);
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(CCPointZero);
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());
	//CCUIBackground* _container = new CCUIBackground();
	//_container->initWithSpriteFrame("ui.png", ccp(0,-20), ccp(0,0), CCSizeMake(464,550));
	//this->addChild(_container);
	//_viewSize = _container->getContentSize();
	//_container->release();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/entrance/res_entrance.plist");

	if(!_pContainer)
	{
		_pContainer = new CCLayer();
		_pContainer->setAnchorPoint(CCPointZero);
		_pContainer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
	}

	addScrollViews();

	addDirs();

	this->addChild(_pContainer);
	_pContainer->release();

	return true;
}

void DungeonEntrysView::addDirs()
{
	
	CCMenuItemImage * pLeftDirImage = CCMenuItemImage::itemFromNormalImage(
		"assets/ui/common/direct.png",
		"assets/ui/common/direct_pressed.png",
		this,
		menu_selector(DungeonEntrysView::onClickDir));
	pLeftDirImage->setTag(0);
	CCMenu * pLeftDirMenu = CCMenu::menuWithItem(pLeftDirImage);
	pLeftDirMenu->setTouchLayer(TLE::WindowLayer_Common);
	pLeftDirMenu->setPosition(POS(ccp(420, 420), ScaleUtil::CENTER_TOP));
	pLeftDirMenu->setScale(1.0);
	pLeftDirMenu->setTag(TAG_DIR_LEFT);
	if (_pContainer->getChildByTag(TAG_DIR_LEFT))
	{
		_pContainer->removeChildByTag(TAG_DIR_LEFT,true);
	}
	_pContainer->addChild(pLeftDirMenu,2);

	//right
	CCMenuItemImage * pRightDirImage = CCMenuItemImage::itemFromNormalImage(
		"assets/ui/common/direct0.png",
		"assets/ui/common/direct_pressed0.png",
		this,
		menu_selector(DungeonEntrysView::onClickDir));
	pRightDirImage->setTag(1);
	CCMenu * pRightDirMenu = CCMenu::menuWithItem(pRightDirImage);
	pRightDirMenu->setTouchLayer(TLE::WindowLayer_Common);
	pRightDirMenu->setPosition(POS(ccp(540, 420), ScaleUtil::CENTER_TOP));
	pRightDirMenu->setScale(1.0);
	pRightDirMenu->setTag(TAG_DIR_RIGHT);
	if (_pContainer->getChildByTag(TAG_DIR_RIGHT))
	{
		_pContainer->removeChildByTag(TAG_DIR_RIGHT,true);
	}
	_pContainer->addChild(pRightDirMenu,2);
	
	if (dungeonScrollView)
	{
		int nCurPage = dungeonScrollView->currentScreen;
		int totalPage = dungeonScrollView->totalScreens;

		char path[64] = {0};
		sprintf(path , "%d / %d" , nCurPage , totalPage);
		LHLabelTTF * pLabel = new LHLabelTTF();
		bool var = pLabel->initWithString(path , CCSizeMake(POSX(210) , POSX(36)) ,
			CCTextAlignmentCenter , "Arial" , POSX(32) , POSX(1) < 1 ? 1 : POSX(1) , ccc3(0,0,0));
		if (var)
		{
			pLabel->setPosition(POS(ccp(480, 420), ScaleUtil::CENTER_TOP));
			pLabel->setTag(TAG_DIR_Text);
			_pContainer->addChild(pLabel , 2);
		}
	}
	
}

void DungeonEntrysView::onClickDir(CCObject * pSender)
{
	if (!pSender)
	{
		return;
	}
	int tag = ((CCNode *)pSender)->getTag();

	if (dungeonScrollView)
	{
		if (tag == 1)
		{
			if (dungeonScrollView->currentScreen < dungeonScrollView->totalScreens)
			{
				dungeonScrollView->moveToNextPage();
			}
		}
		else if (tag == 0)
		{
			if (dungeonScrollView->currentScreen > 1)
			{
				dungeonScrollView->moveToPreviousPage();
			}
		}		
		
	}
		
}

void DungeonEntrysView::updateDirText(std::string str)
{
	if (!_pContainer)
	{
		return;
	}

	if (dungeonScrollView)
	{
		int nCurPage = dungeonScrollView->currentScreen;
		int totalPage = dungeonScrollView->totalScreens;

		char path[64] = {0};
		sprintf(path , "%d / %d" , nCurPage , totalPage);
		LHLabelTTF * pLabel = (LHLabelTTF *)_pContainer->getChildByTag(TAG_DIR_Text);
		if (pLabel)
		{
			pLabel->setString(path);
		}
	}
	
}

void DungeonEntrysView::addScrollViews()
{
	if (!dungeonScrollView) // passive
	{
		//dungeonScrollView = new DungeonEntrysCreate(CCRectMake(18,33,437,447));
		/*CCSize size = this->getContentSize();
		float left = POSX(18.0f);
		float bottom = POSX(18.0f);*/
		//POSX edwardliu
		dungeonScrollView = new DungeonEntrysCreate(CCRectMake(POSX(18.0f), POSX(24.0f), POSX(924)/*(size.width) - (2 * left)*/, POSX(515)/*size.height - (2 * bottom)*/));
		_pContainer->addChild(dungeonScrollView);
		dungeonScrollView->release();
	}
	if(dungeonScrollView)
	{
		CCLayer* newlayer = dungeonScrollView->addLayerByTag(0);
		dungeonScrollView->addDungeonEntries();
	}
}

CCNode * DungeonEntrysView::getNewHandItem(int id)
{
	switch (id)
	{
	case 100:
		{
			if (dungeonScrollView)
			{
				return dungeonScrollView->_btChallengeEnter;
			}
		}
		break;
	case 101:
		{
			if (dungeonScrollView)
			{
				return dungeonScrollView->_btStoryEnter;
			}
		}
		break;
	case 102:
		{
			if (ViewManager::getInstance()->storyMapsView
				&& ViewManager::getInstance()->storyMapsView->_storyMapList)
			{
				LayerNode * pLayer = ViewManager::getInstance()->storyMapsView->_storyMapList->m_vMapList.find(0)->second;
				if (pLayer)
				{
					return ((TouchMapNode *)pLayer->getChildByTag(0))->_btnGUA;
				}
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

DungeonEntrysView::~DungeonEntrysView()
{
	DungeonEntrysMediator* pMeditor = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	pMeditor->dungeonEntrysView = 0;

	ViewManager::getInstance()->dungeonEntrysView = 0;

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/entrance/res_entrance.plist");
}

void DungeonEntrysView::clickCloseHandler(CCObject* pSender)//kevinshit
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
