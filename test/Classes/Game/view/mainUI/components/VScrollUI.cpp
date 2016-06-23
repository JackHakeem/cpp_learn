#include "VScrollUI.h"
#include "manager/ViewManager.h"
#include "manager/CDManage.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ImageManager.h"
#include "model/player/RoleManage.h"
#include "VSCustomCD.h"
#include "manager/LevLimitConst.h"
#include "view/ore/OreMediator.h"
#include "utils/sort/SortUtil.h"
#include "utils/ScaleUtil.h"
#include "view/newhand/components/NewHandView.h"
#include "LHLabelTTF.h"
#include "model/newhand/NewhandManager.h"

#define FLOAT_DISTANCE (POSX(50))
#define INT_COLUM_NUM (3)
#define FLOAT_X_SPAN (POSX(-10))

const int ConstButtonArr[] = 
{
	LevLimitConst::Limit_Strength , 
	LevLimitConst::Limit_Levy,
	LevLimitConst::Limit_Ore,
	LevLimitConst::Limit_Arena,
	LevLimitConst::Limit_Train
}; 

VScrollUI::VScrollUI()
{
	_deltaPos = 0;
	setIsHide(false);
	setListCount(VScrollUI::Max_Count);
	_pHideMenuItem = 0;
	_pos = ccp(0 , 0);
	_btnPos = ccp(0,0);
	_btnCnt = 0;
	_cdCnt = 0;
	_otherCnt = 0;
	memset(_btnArr , 0 ,sizeof(_btnArr));
	memset(_cd , 0 ,sizeof(_cd));
	memset(_other , 0 ,sizeof(_other));
	initPos();
}

VScrollUI::~VScrollUI()
{
	stopTimer();
}

void VScrollUI::initPos()
{
	memset(levPos , -1 ,sizeof(levPos));
	levPos[LevLimitConst::Limit_Strength] = Item_strength;
	levPos[LevLimitConst::Limit_Levy] = Item_Levy;
	levPos[LevLimitConst::Limit_Ore] = Item_Ore;
	levPos[LevLimitConst::Limit_Arena] = Item_Arena;
	levPos[LevLimitConst::Limit_Train] = Item_Train;
	//add here
}

int VScrollUI::getLevByPos(int pos)
{
	for (int lev = 0 ; lev < 121 ; lev++)
	{
		if (levPos[lev] == pos)
		{
			return lev;
		}
	}
	return -1;
}

bool VScrollUI::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

#if CC_NEW_VSCROLLUI_OPEN
	this->setPosition(ccp(FLOAT_X_SPAN + POSX(0) , POSX(210)));
	this->setContentSize(CCSizeMake(FLOAT_DISTANCE , FLOAT_DISTANCE * INT_COLUM_NUM));

	_originPos = this->getPosition();
#else
	this->setPosition(ccp(POSX( 0 ) , winSize.height - CCSZIE_LISTVIEW.size.height - POSX(120)));
#endif

	this->setAnchorPoint(CCPointZero);
	_pos = this->getPosition();
	
#if CC_NEW_VSCROLLUI_OPEN
	loadItemNew();
#else
	loadItem();
#endif

	//
	startTimer();

	return true;
}

void VScrollUI::startTimer()
{
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(VScrollUI::updateTimer) , this , 2.0f , false);
}

void VScrollUI::stopTimer()
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(VScrollUI::updateTimer) , this);
}

void VScrollUI::loadItem()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/map/res_map.plist");
	//
	CCUIListView * pListView = CCUIListView::listViewWithCCRect(CCSZIE_LISTVIEW, false);
	pListView->m_pri = TLE::SceneUILayer - 1;
	pListView->setAnchorPoint(CCPointZero);
	pListView->setSpacingVertical(POSX(10));
	pListView->setOnItemActionListener(this);
	pListView->scrollToEnd(0);
	pListView->setWorldSpaceLeftBottomPoint(ccpAdd(pListView->getPosition() , this->getPosition()));
	pListView->setTag(Tag_ListView);
	pListView->setAdapter(this);
	this->addChild(pListView);
	pListView->release();

	CCPoint pos = pListView->getPosition();
	// up director button
	{
		CCSprite * pUpDir1 = new CCSprite();
		CCSprite * pUpDir2 = new CCSprite();
		pUpDir1->setRotation(90);
		pUpDir2->setRotation(90);
		pUpDir1->initWithSpriteFrameName("map/arrow.png");
		pUpDir2->initWithSpriteFrameName("map/arrow.png");
		CCMenuItemSprite * pDirMenuItemUp = CCMenuItemSprite::itemFromNormalSprite(
			pUpDir1,
			pUpDir2,
			this,
			menu_selector(VScrollUI::onClick2Up));
		pUpDir1->release();
		pUpDir2->release();
		CCMenu * pDirMenuUp = CCMenu::menuWithItem(pDirMenuItemUp);
		pDirMenuUp->setPosition(ccp(POSX(46) , POSX(40) + CCSZIE_LISTVIEW.size.height));
		pDirMenuUp->setTag(Tag_UpDir);
		this->addChild(pDirMenuUp , 1);
	}

	// down director button
	{
		CCSprite * pDownDir1 = new CCSprite();
		CCSprite * pDownDir2 = new CCSprite();

		pDownDir1->initWithSpriteFrameName("map/arrow.png");
		pDownDir2->initWithSpriteFrameName("map/arrow.png");
		pDownDir1->setRotation(270);
		pDownDir2->setRotation(270);
		CCMenuItemSprite * pDirMenuItemDown = CCMenuItemSprite::itemFromNormalSprite(
			pDownDir1,
			pDownDir2,
			this,
			menu_selector(VScrollUI::onClick2Down));
		pDownDir1->release();
		pDownDir2->release();
		CCMenu * pDirMenuDown = CCMenu::menuWithItem(pDirMenuItemDown);
		pDirMenuDown->setPosition(ccp(POSX( 50) + pDownDir2->getContentSize().width , POSX(-10)));
		pDirMenuDown->setTag(Tag_DownDir);
		this->addChild(pDirMenuDown , 1);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/map/res_map.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map.pvr.ccz");
	// hide button
	/*
	{
		CCUIBackground * pHideButton = new CCUIBackground();
		pHideButton->initWithSpriteFrame("ui2.png" , CCPointZero ,CCPointZero , CCSizeMake(POSX(40) , POSX(90)));
		pHideButton->setPosition(ccp(CCSZIE_LISTVIEW.origin.x + CCSZIE_LISTVIEW.size.width, CCSZIE_LISTVIEW.origin.y + CCSZIE_LISTVIEW.size.height - POSX(90)));
		_btnPos = pHideButton->getPosition();
		this->addChild(pHideButton , -1 , Tag_HideBack);
		pHideButton->release();
		pHideButton->setScale(0.7);
		
		CCSprite * pHide1 = new CCSprite();
		CCSprite * pHide2 = new CCSprite();
		//CCSprite * pHide3 = new CCSprite();

		pHide1->initWithSpriteFrameName("backlight/hideright1.png");
		pHide2->initWithSpriteFrameName("backlight/hideright2.png");
		pHide1->setFlipX(true);
		pHide2->setFlipX(true);

		CCMenuItemSprite * pHideMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pHide1,
			pHide2,
			this,
			menu_selector(VScrollUI::onClickHideVscroll));
		pHide1->release();
		pHide2->release();
		_pHideMenuItem = pHideMenuItem;
		CCMenu * pHideMenu = CCMenu::menuWithItem(pHideMenuItem);
		pHideMenu->setPosition(ccp(POSX(45) , POSX(20)));
		pHideMenu->setTouchLayer(TLE::SceneUILayer);
		pHideButton->addChild(pHideMenu , 1 , Tag_HideBtn);


		if (RoleManage::Instance()->roleLev() < 2 && !getIsHide())
		{
			clickHideVscroll();
		}
	}
	*/
	
}

void VScrollUI::loadItemNew()
{
	_moveSize = CCSizeMake( ((int)((_btnCnt-1)/3)+ 1) * CCSZIE_LISTVIEW.size.width + POSX(20) + FLOAT_X_SPAN , POSX(50));
	// background
	
	CCUIBackground * pBack = new CCUIBackground();
	pBack->initWithSpriteFrame("ui.png", ccp(POSX(0), POSX(0)), ccp(POSX(0), POSX(0)), 
		CCSizeMake(CCSZIE_LISTVIEW.size.width * ((int)((_btnCnt-1)/3)+ 1) + POSX(20), CCSZIE_LISTVIEW.size.height * (3.0f / 4.0f)));
	pBack->setTag(Tag_back);
	this->addChild(pBack , 0);
	pBack->release();

	// hide button
	CCSprite * pHide1 = new CCSprite();
	CCSprite * pHide2 = new CCSprite();
	bool var1 = pHide1->initWithFile("assets/ui/mainUI/vscroll/hide1.png");
	bool var2 = pHide2->initWithFile("assets/ui/mainUI/vscroll/hide2.png");
	CCPoint pos;
	if (var1 && var2)
	{
		CCMenuItemSprite * pItem = CCMenuItemSprite::itemFromNormalSprite(
			pHide1,
			pHide2,
			this,
			menu_selector(VScrollUI::onClickHideVscroll));
		pItem->setAnchorPoint(ccp(0,0.5));
		pItem->setPosition(ccp(CCSZIE_LISTVIEW.origin.x 
			+ CCSZIE_LISTVIEW.size.width *  ((int)((_btnCnt-1)/3)+ 1)  + POSX(15), 
			CCSZIE_LISTVIEW.origin.y + CCSZIE_LISTVIEW.size.height*(3.0f/4.0f) /2));
		pos = pItem->getPosition();
		pHide1->release();
		pHide2->release();
		_pHideMenuItem = pItem;
		CCMenu * pHideMenu = CCMenu::menuWithItem(pItem);
		pHideMenu->setPosition(CCPointZero);
		pHideMenu->setTouchLayer(TLE::SceneUILayer);
		this->addChild(pHideMenu , 2 , Tag_HideBtn);
	}
	// hide button back
	CCSprite * pHideBack = new CCSprite();
	bool var3 = pHideBack->initWithFile("assets/ui/mainUI/vscroll/btnback.png");
	if (var3)
	{
		pHideBack->setPosition(ccpAdd(ccp(POSX(21),0) , ccpAdd(pos, ccp(/*CCSZIE_LISTVIEW.size.width*/0,0)/*pHide1->getPosition()*/)));
		this->addChild(pHideBack , 1 , Tag_HideBtn + 1);
		pHideBack->release();
	}

	// CD Icon
	CCSprite * pCDSprite = new CCSprite();
	bool var4 = pCDSprite->initWithFile("assets/ui/mainUI/vscroll/msg.png");
	if (var4)
	{
		CCSize size = _pHideMenuItem->getContentSize();
		pCDSprite->setAnchorPoint(ccp(0.5,0.5));
		pCDSprite->setPosition(ccpAdd(_pHideMenuItem ? _pHideMenuItem->getPosition() : CCPointZero, 
			ccp(size.width /*+ POSX(80)*/ , size.height/2 - POSX(15))));
		pCDSprite->setTag(Tag_ItemCDIcon);
		this->addChild(pCDSprite , 3 );
		pCDSprite->release();

		LHLabelTTF * pCDText = new LHLabelTTF();
		pCDText->initWithString("" , CCSizeMake(POSX(30) , POSX(30)) , CCTextAlignmentCenter , 
			"Arial" , POSX(24) , POSX(1) < 1 ? 1 : POSX(1) , ccc3(0,0,0) );
		pCDText->setColor(ccc3(255,255,255));
		pCDText->setPosition(ccpAdd( CCPointZero , pCDSprite->getPosition()));
		pCDText->setTag(Tag_ItemCDText);
		this->addChild(pCDText , 4);
		pCDText->release();
	}

	//
	initItem();

	if (!getIsHide())
	{
		onClickHideVscroll(_pHideMenuItem);	
	}

	showUI(false);
}

void VScrollUI::initItem()
{
	int j = 0;
	int cnt = sizeof(ConstButtonArr)/sizeof(int);
	for (int i = 0 ; i  < cnt; i++)
	{
		if (ConstButtonArr[i] <= RoleManage::Instance()->roleLev())
		{
			_btnArr[j] = ConstButtonArr[i];
			++_btnCnt;
			addButton(_btnArr[j]);
			++j;
		}
	}
}

bool VScrollUI::isNeedAdded(int id)
{
	bool bNeed = false;
	int len1 = sizeof(ConstButtonArr)/sizeof(int);
	for (int i = 0 ; i <  len1; i++)
	{
		if (id == ConstButtonArr[i])
		{
			bNeed = true;
			break;
		}
	}

	int len2 = sizeof(_btnArr)/sizeof(int);
	for (int j= 0 ; j <  len2; j++)
	{
		if (id == _btnArr[j])
		{
			bNeed = false;
			break;
		}
	}
	return bNeed;
}

std::vector<string> VScrollUI::getPathById(int id)
{
	std::vector<string> pathVector;
	pathVector.push_back("");
	pathVector.push_back("");
	pathVector.push_back("");
	char path[128] = {0};
	switch (id)
	{
	case LevLimitConst::Limit_Strength:
		{
			sprintf(path , "mainUI/mn_btn%d_normal.png", 3);
			pathVector[0] = path;
			memset(path , 0 , sizeof(path));
			sprintf(path , "mainUI/mn_btn%d_pressed.png", 3);
			pathVector[1] = path;
		}
		break;
	case LevLimitConst::Limit_Levy:
		{
			sprintf(path , "mainUI/award.png");
			pathVector[0] = path;
			memset(path , 0 , sizeof(path));
			sprintf(path , "mainUI/award2.png");
			pathVector[1] = path;
		}
		break;
	case LevLimitConst::Limit_Arena:
		{
			sprintf(path , "mainUI/arena.png");
			pathVector[0] = path;
			memset(path , 0 , sizeof(path));
			sprintf(path , "mainUI/arena2.png");
			pathVector[1] = path;
		}
		break;
	case LevLimitConst::Limit_Train:
		{
			sprintf(path , "mainUI/mn_btn%d_normal.png", 10);
			pathVector[0] = path;
			memset(path , 0 , sizeof(path));
			sprintf(path , "mainUI/mn_btn%d_pressed.png", 10);
			pathVector[1] = path;
		}
		break;
	case LevLimitConst::Limit_Ore:
		{
			sprintf(path , "mainUI/mn_btn%d_normal.png", 8);
			pathVector[0] = path;
			memset(path , 0 , sizeof(path));
			sprintf(path , "mainUI/mn_btn%d_pressed.png", 8);
			pathVector[1] = path;
		}
		break;
	default:
		break;
	}
	return pathVector;
}

void VScrollUI::addButtonByLev(int lev)
{
	switch (lev)
	{
	case LevLimitConst::Limit_Strength:
		{

		}
		break;
	case LevLimitConst::Limit_Levy:
		{

		}
		break;
	case LevLimitConst::Limit_Arena:
		{

		}
		break;
	case LevLimitConst::Limit_Train:
		{

		}
		break;
	case LevLimitConst::Limit_Ore:
		{

		}
		break;
	default:
		break;
	}

	// test
	addButton(lev);

}

void VScrollUI::addButton(int id )
{
	if (isNeedAdded(id))
	{
		_btnArr[_btnCnt] = id;
		++_btnCnt;
	}	
	
	SortUtil::Instance()->reSort(_btnArr , _btnCnt , ConstButtonArr);

	// icon
	for (int i = 0 ; i < _btnCnt ; i++)
	{
		if (!_btnArr[i])
		{
			break;
		}		
		CCSprite * pIconSprite0 = new CCSprite();
		bool var0 = pIconSprite0->initWithSpriteFrameName(getPathById(_btnArr[i])[0].c_str());
		CCSprite * pIconSprite1 = new CCSprite();
		bool var1 =pIconSprite1->initWithSpriteFrameName(getPathById(_btnArr[i])[1].c_str());
		if (var0 && var1)
		{
			CCMenuItemSprite * pItem = CCMenuItemSprite::itemFromNormalSprite(
				pIconSprite0,
				pIconSprite1,
				this,
				menu_selector(VScrollUI::onItemClickHandle));
			pIconSprite0->release();
			pIconSprite1->release();
			pItem->setTag(_btnArr[i]);
			pItem->setPosition(ccp((2 * (i/INT_COLUM_NUM) + 1)*FLOAT_DISTANCE,
				(5 - 2 * (i % INT_COLUM_NUM)) * FLOAT_DISTANCE + POSX(25)));
			
			// back circle
			CCSize size = pItem->getContentSize();
			CCSprite * pBackSprite = new CCSprite();
			pBackSprite->initWithSpriteFrameName("mainui2/smallcircle.png");
			pBackSprite->setPosition(ccp(size.width/2 , size.height/2));
			pItem->addChild(pBackSprite , -1);
			pBackSprite->release();
			
			// CCSprite newhand item
			/*
			CCSprite * pNewHandSprite = new CCSprite();
			bool var3 = pNewHandSprite->initWithFile("assets/ui/mainUI/vscroll/msg.png");
			if (var3)
			{
				pNewHandSprite->setTag(Tag_NewHandSprite);
				pNewHandSprite->setOpacity(0);
				pNewHandSprite->setPosition(ccp(_originPos.x + _moveSize.width , _moveSize.height));
				pItem->addChild(pNewHandSprite , 0);
				pNewHandSprite->release();
			}
			*/

			CCMenu * pMenu = CCMenu::menuWithItem(pItem);
			if (pMenu)
			{
				pMenu->setPosition(ccp(0,0));
				if (this->getChildByTag(Tag_ItemMenu + _btnArr[i]))
				{
					this->removeChildByTag(Tag_ItemMenu + _btnArr[i] , true);
				}
				pMenu->setTag(Tag_ItemMenu + _btnArr[i]);				
				this->addChild(pMenu , 2);
				//pMenu->release();
			}

			// cd
			VSCustomCD * pCDItem = getCDItemById(_btnArr[i]);
			if (pCDItem)
			{
				pCDItem->setPosition( ccp(POSX(-45), POSX(-15)) );
				pCDItem->setTag(Tag_ItemCDText + _btnArr[i]);
				pItem->addChild(pCDItem , 3);
				pCDItem->release();
			}

			// other info
			LHLabelTTF * pLabel = getShowLabelById(_btnArr[i]);
			if (pLabel)
			{
				pLabel->setColor(ccc3(255,215,0));
				pLabel->setAnchorPoint(ccp(0.5,0.5));
				pLabel->setPosition( ccp(POSX(50), POSX(0)) );
				pLabel->setTag(Tag_ItemShowText + _btnArr[i]);
				pItem->addChild(pLabel , 3);
				pLabel->release();
			}
		}
	}
	//
	resetSize();
}

void VScrollUI::resetSize()
{
	CCSize size = CCSizeMake( ((int)((_btnCnt-1)/3)+ 1)* CCSZIE_LISTVIEW.size.width + POSX(20),
		CCSZIE_LISTVIEW.size.height* (3.0f / 4.0f));
	CCUIBackground * pBack = (CCUIBackground *)this->getChildByTag(Tag_back);
	if (pBack)
	{
		pBack->changeSize(size);
		this->setContentSize(size);
		if (_pHideMenuItem)
		{
			_pHideMenuItem->setPosition(ccp(CCSZIE_LISTVIEW.origin.x + size.width - POSX(5) , 
				CCSZIE_LISTVIEW.origin.y + CCSZIE_LISTVIEW.size.height * (3.0f/4.0f) / 2));
		}
	}

	if (_pHideMenuItem)
	{
		CCSize size = _pHideMenuItem->getContentSize();
		CCSprite * pCDSprite = (CCSprite *)this->getChildByTag(Tag_ItemCDIcon);
		if (pCDSprite)
		{
			pCDSprite->setPosition(ccpAdd(_pHideMenuItem ? _pHideMenuItem->getPosition() : CCPointZero, 
				ccp(size.width /*+ POSX(80)*/ , size.height/2 - POSX(15))));

			LHLabelTTF * pCDText = (LHLabelTTF *)this->getChildByTag(Tag_ItemCDText);
			if (pCDText)
			{
				pCDText->setPosition(ccpAdd( CCPointZero , pCDSprite->getPosition()));
			}
		}

		CCSprite * pHideBack = (CCSprite *)this->getChildByTag(Tag_HideBtn + 1);
		if (pHideBack)
		{
			pHideBack->setPosition(ccpAdd(ccp(POSX(21),0) , ccpAdd(_pHideMenuItem->getPosition(), ccp(/*CCSZIE_LISTVIEW.size.width*/0,0)/*pHide1->getPosition()*/)));
		}
		/*
		CCSprite * pNewhandItem = (CCSprite *)_pHideMenuItem->getChildByTag(0);
		if (pNewhandItem)
		{
			CCSize size = CCSizeMake( ((int)((_btnCnt-1)/3)+ 1) * CCSZIE_LISTVIEW.size.width + POSX(20) + FLOAT_X_SPAN , POSX(50));
			pNewhandItem->setPosition(ccp(_originPos.x + size.width , size.height));
		}
		*/
	}

	visit();
}

void VScrollUI::onItemClickHandle(CCObject * pSender )
{
	if (!pSender)
	{
		return;
	}

	MainNavigate * pMainUI = ViewManager::getInstance()->mainNavigate;
	SecNavigate * pSecondUI = ViewManager::getInstance()->_secNavigate;

	int tag = ((CCNode *)pSender)->getTag();
	switch (tag)
	{
	case LevLimitConst::Limit_Strength:
		{
			if (pMainUI)
			{
				pMainUI->popUIHandler3(0);
			}
		}
		break;
	case LevLimitConst::Limit_Levy:
		{
			if (pSecondUI)
			{
				pSecondUI->popUIHandler327Levy(0);
			}
		}
		break;
	case LevLimitConst::Limit_Ore:
		{
			if (pSecondUI)
			{
				pSecondUI->popUIHandlerOre(0);
			}
		}
		break;
	case LevLimitConst::Limit_Arena:
		{
			if (pMainUI)
			{
				pMainUI->popUIHandlerArena(0);
			}
		}
		break;
	case LevLimitConst::Limit_Train:
		{
			if (pMainUI)
			{
				pMainUI->popUIHandler10(0);
			}
		}
		break;
	default :
		break;
	}
}

void VScrollUI::onClickHideVscroll(CCObject * pSender)
{
#if CC_NEW_VSCROLLUI_OPEN
	if (_pHideMenuItem)
	{
		_pHideMenuItem->setIsEnabled(false);
	}
	CCSize size = CCSizeMake( ((int)((_btnCnt-1)/3)+ 1) * CCSZIE_LISTVIEW.size.width + POSX(20),
		CCSZIE_LISTVIEW.size.height);
	int plus = getIsHide() ? 0 : (-1);
	CCFiniteTimeAction * pMoveTo = CCMoveTo::actionWithDuration(/*0.1f*/ 0.2f , ccpAdd(_pos , ccp((plus) * (size.width + POSX(/*-100*/0) + FLOAT_X_SPAN) , 0)));
	CCCallFuncND * pCallBack = CCCallFuncND::actionWithTarget(this , callfuncND_selector(VScrollUI::movieCallback) , 0 );
	CCAction * pAction = CCSequence::actionOneTwo(pMoveTo , pCallBack);
	this->runAction(pAction);

	setIsHide(!getIsHide());

	CCMenuItemSprite * pHideMenuItem = (CCMenuItemSprite *)pSender;
	if (pHideMenuItem)
	{
		std::string strPath1("assets/ui/mainUI/vscroll/hide1.png");
		std::string strPath2("assets/ui/mainUI/vscroll/hide2.png");
		if (getIsHide())
		{
			strPath1 = "assets/ui/mainUI/vscroll/show1.png";
			strPath2 = "assets/ui/mainUI/vscroll/show2.png";
		}
		CCSprite * pHide1 = new CCSprite();
		CCSprite * pHide2 = new CCSprite();
		bool var1 = pHide1->initWithFile(strPath1.c_str());
		bool var2 = pHide2->initWithFile(strPath2.c_str());
		if (var1)
		{
			pHideMenuItem->setNormalImage(pHide1);
			pHide1->release();
		}
		if (var2)
		{
			pHideMenuItem->setSelectedImage(pHide2);
			pHide2->release();
		}
	}
	//

#else
	if (_pHideMenuItem)
	{
		_pHideMenuItem->setIsEnabled(false);
	}

	int plus = getIsHide() ? 0 : (-1);
	CCFiniteTimeAction * pMoveTo = CCMoveTo::actionWithDuration(/*0.1f*/ 0.0f , ccpAdd(_pos , ccp((plus) * (CCSZIE_LISTVIEW.size.width + POSX(30)) , 0)));
	CCCallFuncND * pCallBack = CCCallFuncND::actionWithTarget(this , callfuncND_selector(VScrollUI::movieCallback) , 0 );
	CCAction * pAction = CCSequence::actionOneTwo(pMoveTo , pCallBack);
	this->runAction(pAction);

	/*
	int plus2 = getIsHide() ? (0) : (1);
	CCFiniteTimeAction * pMoveTo2 = CCMoveTo::actionWithDuration(0.4f , ccpAdd(_btnPos , ccp((plus2) * CCSZIE_LISTVIEW.size.width , 0)));
	CCCallFuncND * pCallBack2 = CCCallFuncND::actionWithTarget(this , callfuncND_selector(VScrollUI::movieCallback) , 0 );
	CCAction * pAction2 = CCSequence::actionOneTwo(pMoveTo2 , pCallBack2);
	CCNode * pNode = (CCNode *)this->getChildByTag(Tag_HideBack);
	if (pNode)
	{
		pNode->runAction(pAction2);
	}
	*/

	setIsHide(!getIsHide());
	
	CCMenuItemSprite * pHideMenuItem = (CCMenuItemSprite *)pSender;
	if (pHideMenuItem)
	{
		CCSprite * pHide1 = CCSprite::spriteWithSpriteFrameName("backlight/hideright1.png");
		CCSprite * pHide2 = CCSprite::spriteWithSpriteFrameName("backlight/hideright2.png");
		if (!getIsHide())
		{
			pHide1->setFlipX(true);
			pHide2->setFlipX(true);
		}
		pHideMenuItem->setNormalImage(pHide1);
		pHideMenuItem->setSelectedImage(pHide2);
	}

#endif

}

void VScrollUI::movieCallback(CCNode * pNode , void * data)
{
	if (_pHideMenuItem)
	{
		_pHideMenuItem->setIsEnabled(true);
		/*
		if (getIsHide())
		{
			_pHideMenuItem->setOpacity(255);
		}
		else
		{
			_pHideMenuItem->setOpacity(0);
		}
		*/
	}

	int sum = getCDCnt() + getOtherCnt();
	showCDICon(getIsHide() && sum);

	// notify newhand
	NewHandView::Instance()->onMainNavigateChange(true);
}

void VScrollUI::onClick2Up(CCObject * pSender)
{

}

void VScrollUI::onClick2Down(CCObject * pSender)
{

}

void VScrollUI::resetListView()
{
	CCUIListView * pListView = (CCUIListView *)this->getChildByTag(Tag_ListView);
	if (!pListView)
	{
		return;
	}
	CCMutableArray<LayerNode *>* listChilds = pListView->getChilds();
	if (!listChilds)
	{
		return;
	}
	
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin(); it != listChilds->end(); it++)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		if ( pChildLayer->getParent() )
		{
			pChildLayer->removeFromParentAndCleanup(true);
		}

		pChildLayer->release();
	}
	_deltaPos = 0;
	pListView->setAdapter(this);
	//
	pListView->resetContentLayerPosition();

	if (getCount() <= 4)
	{
		setDirState(Stat_Hide);
	}
	else
	{
		setDirState(Stat_Normal);
	}
	
}

void VScrollUI::resetContentLayerPosition()
{
	CCUIListView * pListView = (CCUIListView *)this->getChildByTag(Tag_ListView);
	if (pListView)
	{
		pListView->resetContentLayerPosition();
	}	
}

void VScrollUI::scrollToItemByIndex(int index , ccTime duration)
{
	CCUIListView * pListView = (CCUIListView *)this->getChildByTag(Tag_ListView);
	if (pListView)
	{
		pListView->scrollToItemByIndex(index , duration);
	}	
}

int VScrollUI::getCount()
{
	return getMaxListItemCounts();
}

int VScrollUI::getMaxListItemCounts()
{
	int lev = RoleManage::Instance()->roleLev();
	int count = 0;

	for (int i = 0 ; i<121 ; i++)
	{
		if (i > lev)
		{
			 break;
		}
		if (levPos[i] >= 0)
		{
			++count;
		}		
	}
	
	return count;
}

LayerNode * VScrollUI::getView( int position )
{
	char path[64] = {0};
	int nTagCD = -1;

	int nPos = position;

	if (nPos > 1)
	{
		nPos += _deltaPos;
	}	

	while (getLevByPos(nPos) > RoleManage::Instance()->roleLev() && (nPos <121))
	{
		nPos++;
		_deltaPos++;
	}


	if (nPos >= 121)
	{
		return 0;
	}
	
	switch (nPos)
	{
	case Item_strength:
		{
			sprintf(path , "mainUI/stren.png" , 3);
			nTagCD = CDManage::STRENGTHEN;
		}
		break;
	case Item_Levy:
		{
			sprintf(path , "mainUI/award.png");
			nTagCD = CDManage::COLLECTION;
		}
		break;
	case Item_Arena:
		{
			sprintf(path , "mainUI/arena.png");
			nTagCD = CDManage::ARENA_CD;
		}
		break;
	case Item_Ore:
		{
			sprintf(path , "mainUI/crystal.png");
			//nTagCD = CDManage::Instance()->getTagByMinOreCD();
		}
		break;
	case Item_Train:
		{
			sprintf(path , "mainUI/mn_btn10_normal.png");
			//nTagCD = CDManage::Instance()->getTagByMinOreCD();
		}
		break;
	default:
		{
			return 0;
		}
		break;
	}

	// icon
	CCSprite * pIconSprite = new CCSprite();
	pIconSprite->initWithSpriteFrameName(path);
	CCSize size = pIconSprite->getContentSize();

	pIconSprite->setPosition(ccp(/*size.width/2*/ POSX(50.0f) +  POSX(-1), size.height/2 + POSX(8)));
	pIconSprite->setScale(0.8);

	LayerNode * pLayer = new LayerNode();
	pLayer->init();
	pLayer->setContentSize(size);
	pLayer->setvisibleSize(size);
	pIconSprite->setTag(Tag_Item);
	pLayer->addChild(pIconSprite , 1);
	pIconSprite->release();

	// background
	CCPoint pos = pIconSprite->getPosition();
	CCSprite * pBackSprite = new CCSprite();
	pBackSprite->initWithSpriteFrameName("mainui2/smallcircle.png");
	pBackSprite->setPosition(ccp(pos.x , pos.y-POSX(5)));
	//pBackSprite->setScale(0.96);
	pLayer->addChild(pBackSprite , -1);
	pBackSprite->release();

	// Hight light
	CCSprite * pLight = new CCSprite();
	pLight->initWithSpriteFrameName("backlight/light1.png");
	pLight->setPosition(pBackSprite->getPosition());
	pLight->setTag(Tag_ItemLight);
	pLayer->addChild(pLight , 0);
	pLight->release();

	// special strenth CD
	/*
	if (position == Item_strength)
	{
		CCSprite * pSprite = ImageManager::getRealSpriteFromImagePath(path);
		if (pSprite)
		{
			pSprite->setColor(ccc3(128,128,128));
			CCProgressTimer * pPercent = new CCProgressTimer();
			pPercent->initWithTexture(pSprite->getTexture());
			pPercent->setSprite(pSprite);
			pPercent->setType(kCCProgressTimerTypeRadialCCW);
			pPercent->setPosition(pIconSprite->getPosition());
			pLayer->addChild(pPercent , 2);
			pPercent->release();

			MainStrengView * pStrength =  ViewManager::getInstance()->_mainStrengView;
			if (pStrength && pStrength->strengPanel)
			{
				pPercent->setPercentage(100 - pStrength->strengPanel->_curStrengProb);
			}
		}
	}
	*/

	// CD
	if (nTagCD != -1)
	{
		VSCustomCD* pCDItem = new VSCustomCD( nTagCD);
		pCDItem->setPosition( ccp(POSX(-44), POSX(-8)) );
		pCDItem->setScale(0.8);
		pLayer->addChild( pCDItem );
		pCDItem->release();
		pCDItem->setPreLabString("");
		pCDItem->reinit();
		pCDItem->setIsCDReady(CDManage::Instance()->getCDReady(nTagCD));
	}

	// other show info
	switch (nPos)
	{
	case Item_strength:
		{
			//CD
		}
		break;
	case Item_Levy:
		{
			//CD
		}
		break;
	case Item_Arena:
		{
			//CD
		}
		break;
	case Item_Ore:
		{
			//Ore info
			OreMediator * pMdt = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
			if (pMdt)
			{
				memset(path , 0 ,  sizeof(path));
				sprintf(path , "%d/%d" , CDManage::Instance()->getNoCDOreNum() ,  pMdt->getOreNumber() );
				CCLabelTTF * pLabelPos = CCLabelTTF::labelWithString(path , CCSizeMake(POSX(120) , POSX(24)) , CCTextAlignmentCenter , "Arial" , POSX(22));
				pLabelPos->setColor(ccc3(233,133,25));
				pLabelPos->setPosition( ccp(CCSZIE_LISTVIEW.size.width/2, POSX(8)) );
				pLayer->addChild( pLabelPos );
			}
		}
		break;
	case Item_Train:
		{
			//train info
			memset(path , 0 ,  sizeof(path));
			sprintf(path , "%d/%d" , TrainManager::Instance()->getTrainNum() , TrainManager::Instance()->getTrainLim());
			CCLabelTTF * pLabelPos = CCLabelTTF::labelWithString(path , CCSizeMake(POSX(120) , POSX(24)) , CCTextAlignmentCenter , "Arial" , POSX(22));
			pLabelPos->setColor(ccc3(233,133,25));
			pLabelPos->setPosition( ccp(CCSZIE_LISTVIEW.size.width/2, POSX(8)) );
			pLayer->addChild( pLabelPos , 8);
		}
		break;
	default:
		{
			return 0;
		}
		break;
	}

	setItemLight(pLayer , false);

	return pLayer;
}

void VScrollUI::onItemClickListener( LayerNode *itemCell, int position )
{
	MainNavigate * pMainUI = ViewManager::getInstance()->mainNavigate;
	SecNavigate * pSecondUI = ViewManager::getInstance()->_secNavigate;

	int nPos = position;

	if (nPos > 1)
	{
		nPos += _deltaPos;
	}	
	/*
	while (getLevByPos(nPos) > RoleManage::Instance()->roleLev() && (nPos <121))
	{
		nPos++;
	}
	*/
	if (nPos >= 121)
	{
		return ;
	}

	switch (nPos)
	{
	case Item_strength:
		{
			if (pMainUI)
			{
				pMainUI->popUIHandler3(0);
			}
		}
		break;
	case Item_Levy:
		{
			if (pSecondUI)
			{
				pSecondUI->popUIHandler327Levy(0);
			}
		}
		break;
	case Item_Arena:
		{
			if (pMainUI)
			{
				pMainUI->popUIHandlerArena(0);
			}
		}
		break;
	case Item_Ore:
		{
			if (pSecondUI)
			{
				pSecondUI->popUIHandlerOre(0);
			}
		}
		break;
	case Item_Train:
		{
			if (pMainUI)
			{
				pMainUI->popUIHandler10(0);
			}
		}
		break;
	default:
		break;
	}	
}

void VScrollUI::onItemTouchListener( LayerNode *itemCell, int position )
{
	setItemLight(itemCell , true);
}

void VScrollUI::onItemTouchCancelListener( LayerNode *itemCell, int position )
{
	setItemLight(itemCell , false);
}

void VScrollUI::clickHideVscroll()
{
	//return;

	if (_pHideMenuItem)
	{
		//onClickHideVscroll(_pHideMenuItem);
		showUI(getIsHide());
	}	
}

CCNode * VScrollUI::getNewHandItem( int btnId )
{
#if CC_NEW_VSCROLLUI_OPEN
	
	/*
	int index = btnId - 20;
	if (index < 0)
	{
		return 0;
	}
	
	if (this->getChildByTag(Tag_ItemMenu + _btnArr[index]))
	{
		return this->getChildByTag(Tag_ItemMenu + _btnArr[index])->getChildByTag( _btnArr[index]);
	}
	*/

	
	NewhandManager::Instance()->setNavigateType(NewhandManager::Navigate_LeftVscroll);

	if (_btnCnt <= 0)
	{
		return 0;
	}
	
	int index = _btnCnt - 1;
	if (this->getChildByTag(Tag_ItemMenu + _btnArr[index]))
	{
		return this->getChildByTag(Tag_ItemMenu + _btnArr[index])->getChildByTag( _btnArr[index]);
		/*
		if (this->getChildByTag(Tag_ItemMenu + _btnArr[index])->getChildByTag( _btnArr[index]))
		{
			CCNode * pNode = this->getChildByTag(Tag_ItemMenu + _btnArr[index])->getChildByTag( _btnArr[index])->getChildByTag(Tag_NewHandSprite);
			return pNode;
		}
		*/
	}
	
	return 0;

#else

	int index = btnId - 20;
	if (index < 0)
	{
		return 0;
	}
	
	if (getCount() <= index)
	{
		--index;
	}	

	CCUIListView * pListView = (CCUIListView *)this->getChildByTag(Tag_ListView);
	if (pListView)
	{
		CCMutableArray<LayerNode *>* listChilds = pListView->getChilds();
		if (!listChilds)
		{
			return 0;
		}
		if (index>=listChilds->count())
		{
			return 0;
		}		
		
		LayerNode * pLayer = listChilds->getObjectAtIndex(index);
		if (pLayer)
		{
			CCNode * pNode = pLayer->getChildByTag(Tag_Item);
			return pNode;
		}
	}
	return 0;

#endif
}

void VScrollUI::setItemLight(LayerNode *itemCell , bool var)
{
	if (itemCell)
	{
		CCSprite * pLight = (CCSprite *)itemCell->getChildByTag(Tag_ItemLight);
		if (pLight)
		{
			pLight->setIsVisible(var);
		}		
	}	
}

void VScrollUI::showUI(bool var)
{
//	this->setIsVisible(_btnCnt > 0);


	if (_btnCnt <= 0)
	{
		return;
	}	


	if(getIsHide() ^ var)
	{
		return;
	}
	else
	{
		onClickHideVscroll(_pHideMenuItem);	
	}
}

void VScrollUI::showCDICon(bool var)
{
	bool bVar = var;
	
	LHLabelTTF * pText = (LHLabelTTF *)this->getChildByTag(Tag_ItemCDText);
	if (pText)
	{
		pText->setIsVisible(bVar);
	}

	CCSprite * pBackSprite = (CCSprite *)this->getChildByTag(Tag_ItemCDIcon);
	if (pBackSprite)
	{
		pBackSprite->setIsVisible(bVar);
	}	
}

void VScrollUI::updateShowLabel()
{
	for (int i = 0 ; i<_btnCnt ; i++)
	{
		int id = _btnArr[i];
		if (id <= 0)
		{
			return;
		}

		LHLabelTTF * pLabel = 0;
		char path[128] = {0};
		CCMenu * pMenu =(CCMenu *)this->getChildByTag(Tag_ItemMenu + id);
		if (pMenu)
		{
			CCNode * pNode = (CCNode *)pMenu->getChildByTag(id);
			if (pNode)
			{
				pLabel = (LHLabelTTF *)pNode->getChildByTag(Tag_ItemShowText + id);
				if (!pLabel)
				{
					continue;
				}
			}
		}		
		switch (id)
		{
		case LevLimitConst::Limit_Strength:
			{
				//nTagCD = CDManage::STRENGTHEN;
			}
			break;
		case LevLimitConst::Limit_Levy:
			{
				//nTagCD = CDManage::COLLECTION;
			}
			break;
		case LevLimitConst::Limit_Ore:
			{
				//nTagCD = CDManage::Instance()->getTagByMinOreCD();
				//Ore info
				OreMediator * pMdt = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
				if (pMdt)
				{
					memset(path , 0 ,  sizeof(path));
					int num1 = CDManage::Instance()->getNoCDOreNum();
					int num2 = pMdt->getOreNumber() ;
					sprintf(path , "%d/%d" , num2-num1 , num2 );
					if (pLabel)
					{
						pLabel->setString(path);
					}

					if (num1 > 0)
					{
						_other[id] = 1;
					}
					else
					{
						_other[id] = 0;
					}
				}
			}
			break;
		case LevLimitConst::Limit_Arena:
			{
				//nTagCD = CDManage::ARENA_CD;
			}
			break;
		case LevLimitConst::Limit_Train:
			{
				//nTagCD = CDManage::Instance()->getTagByMinOreCD();
				memset(path , 0 ,  sizeof(path));
				int num1 = TrainManager::Instance()->getTrainNum();
				int num2 = TrainManager::Instance()->getTrainLim();
				sprintf(path , "%d/%d" ,  num1 , num2 );				
				if (pLabel)
				{
					pLabel->setString(path);
				}

				if (num1 < num2)
				{
					_other[id] = 1;
				}
				else
				{
					_other[id] = 0;
				}		

			}
			break;
		default:
			{

			}
			break;
		}
	}
}

void VScrollUI::updateTimer(ccTime dt)
{
	_cdCnt = getCDCnt();
	updateShowLabel();
	_otherCnt = getOtherCnt();
	int sum = _cdCnt + _otherCnt;

	LHLabelTTF * pText = (LHLabelTTF *)this->getChildByTag(Tag_ItemCDText);
	if (pText)
	{
		char path[32] = {0};
		sprintf(path , "%d" , sum);
		pText->setString(path);
	}

	showCDICon(!!sum && getIsHide());
}

VSCustomCD * VScrollUI::getCDItemById(int id)
{
	int index = id;
	int nTagCD = -1;
	switch (index)
	{
	case LevLimitConst::Limit_Strength:
		{
			nTagCD = CDManage::STRENGTHEN;
		}
		break;
	case LevLimitConst::Limit_Levy:
		{
			nTagCD = CDManage::COLLECTION;
		}
		break;
	case LevLimitConst::Limit_Ore:
		{
			//nTagCD = CDManage::Instance()->getTagByMinOreCD();
		}
		break;
	case LevLimitConst::Limit_Arena:
		{
			nTagCD = CDManage::ARENA_CD;
		}
		break;
	case LevLimitConst::Limit_Train:
		{
			//nTagCD = CDManage::Instance()->getTagByMinOreCD();
		}
		break;
	default:
		{
			return 0;
		}
		break;
	}

	if (nTagCD != -1)
	{
		VSCustomCD* pCDItem = new VSCustomCD( nTagCD);
		pCDItem->setPosition( ccp(POSX(0), POSX(0)) );
		pCDItem->setScale(0.8);
		pCDItem->setPreLabString("");
		pCDItem->reinit();
		pCDItem->setIsCDReady(CDManage::Instance()->getCDReady(nTagCD));

		if (pCDItem->getIsCDReady())
		{
			_cd[index] = 1;
		}
		else
		{
			_cd[index] = 0;
		}
		

		return pCDItem;
	}
	return 0;
}

LHLabelTTF * VScrollUI::getShowLabelById(int id)
{
	int index = id;
	char path[128] = {0};
	LHLabelTTF * pLabel = 0;
	switch (index)
	{
	case LevLimitConst::Limit_Strength:
		{
			//nTagCD = CDManage::STRENGTHEN;
		}
		break;
	case LevLimitConst::Limit_Levy:
		{
			//nTagCD = CDManage::COLLECTION;
		}
		break;
	case LevLimitConst::Limit_Ore:
		{
			//nTagCD = CDManage::Instance()->getTagByMinOreCD();
			//Ore info
			OreMediator * pMdt = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
			if (pMdt)
			{
				memset(path , 0 ,  sizeof(path));
				sprintf(path , "%d/%d" , CDManage::Instance()->getNoCDOreNum() ,  pMdt->getOreNumber() );
				pLabel = new LHLabelTTF();
				pLabel->initWithString(path , CCSizeMake(POSX(120) , POSX(24)) ,
					CCTextAlignmentCenter , "Arial" , POSX(22) , POSX(1) < 1 ? 1 : POSX(1) , ccc3(0,0,0));
			}
		}
		break;
	case LevLimitConst::Limit_Arena:
		{
			//nTagCD = CDManage::ARENA_CD;
		}
		break;
	case LevLimitConst::Limit_Train:
		{
			//nTagCD = CDManage::Instance()->getTagByMinOreCD();
			memset(path , 0 ,  sizeof(path));
			sprintf(path , "%d/%d" , TrainManager::Instance()->getTrainNum() , TrainManager::Instance()->getTrainLim());
			pLabel = new LHLabelTTF();
			pLabel->initWithString(path , CCSizeMake(POSX(120) , POSX(24)) , 
				CCTextAlignmentCenter , "Arial" , POSX(22) , POSX(1) < 1 ? 1 : POSX(1) , ccc3(0,0,0));
		}
		break;
	default:
		{

		}
		break;
	}
	
	return pLabel;
}

int VScrollUI::getCDCnt()
{
	int sum = 0;
	for (int i = 0 ; i< sizeof(_cd)/sizeof(int) ; i++)
	{
		sum += _cd[i];
	}
	return sum;
}

int VScrollUI::getOtherCnt()
{
	int sum = 0;
	for (int i = 0 ; i< sizeof(_other)/sizeof(int) ; i++)
	{
		sum += _other[i];
	}
	return sum;
}

void VScrollUI::setDirState(int state)
{
	CCNode * pUpNode = (CCNode *)this->getChildByTag(Tag_UpDir);
	CCNode * pDownNode = (CCNode *)this->getChildByTag(Tag_DownDir);
	switch (state)
	{
	case Stat_Normal:
		{
			if (pUpNode)
			{
				pUpNode->stopAllActions();
				pUpNode->setIsVisible(true);
			}
			if (pDownNode)
			{
				pDownNode->stopAllActions();
				pDownNode->setIsVisible(true);
			}
		}
		break;
	case Stat_Up:
		{
			if (pUpNode)
			{
				//runMyAction(pUpNode , getMyAction(ActionType_0));
				pUpNode->setIsVisible(true);
			}
			if (pDownNode)
			{
				pDownNode->setIsVisible(false);
			}
			
		}
		break;
	case Stat_Down:
		{
			if (pUpNode)
			{
				pUpNode->setIsVisible(false);
			}
			if (pDownNode)
			{
				//runMyAction(pDownNode , getMyAction(ActionType_0));
				pDownNode->setIsVisible(true);
			}
		}
		break;
	case Stat_Hide:
		{
			if (pUpNode)
			{
				pUpNode->setIsVisible(false);
			}
			if (pDownNode)
			{
				//runMyAction(pDownNode , getMyAction(ActionType_0));
				pDownNode->setIsVisible(false);
			}
		}
		break;
	default:
		break;
	}
}

void VScrollUI::runMyAction(CCNode * pNode , CCAction * pAction)
{
	if (pNode && pAction)
	{
		pNode->runAction(pAction);
	}
}

CCAction * VScrollUI::getMyAction(int type)
{
	CCAction * pAction = 0;
	switch (type)
	{
	case ActionType_0:
		{
			CCFiniteTimeAction * pFadeTo1 = CCFadeTo::actionWithDuration(0.1f , 90);
			CCFiniteTimeAction * pFadeTo2 = CCFadeTo::actionWithDuration(0.1f , 255);
			pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeTo1 , pFadeTo2));
		}
		break;
	default:
		break;
	}
	return pAction;
}

void VScrollUI::reSortButtons()
{

}

CCSize VScrollUI::getListLayerSize()
{
	CCUIListView * pListView = (CCUIListView *)this->getChildByTag(Tag_ListView);
	if (pListView)
	{
		CCMutableArray<LayerNode *>* listChilds = pListView->getChilds();
		if (!listChilds)
		{
			return CCSizeMake(0,0);
		}
		
		LayerNode * pLayer = listChilds->getObjectAtIndex(0);
		if (!pLayer)
		{
			return CCSizeMake(0,0);
		}
		float vhight = pListView->getSpacingVertical();
		return CCSizeMake(pLayer->getContentSize().width , pLayer->getContentSize().height + vhight);
	}
	return CCSizeMake(0,0);
}

CCPoint VScrollUI::getNewHandItemPos(int index)
{
#if CC_NEW_VSCROLLUI_OPEN

	if (_pHideMenuItem)
	{
		return ccpAdd(_pHideMenuItem->getPosition() , _originPos);
	}
	return CCPointZero;
	/*
	if (_btnCnt < 0)
	{
		return CCPointZero;
	}	
	int npos = _btnCnt + 1; 

	return ccpAdd ( ccp((2 * (npos/INT_COLUM_NUM) + 1)*FLOAT_DISTANCE/2,
		(5 - 2 * (npos % INT_COLUM_NUM)) * FLOAT_DISTANCE/2 + POSX(25)) , _originPos);
	*/

	/*
	if (index <0)
	{
		return CCPointZero;
	}

	CCPoint pos = ccp(getPosition().x + getContentSize().width , getPosition().y);
	return ccpAdd( pos , ccp((2 * (index/INT_COLUM_NUM) + 1)*FLOAT_DISTANCE,
		(5 - 2 * (index % INT_COLUM_NUM)) * FLOAT_DISTANCE + POSX(10)  + POSX(30)) );
	*/
#else
	if (getCount() <= index)
	{
		--index;
	}	

	int nIndex = index;
	CCUIListView * pListView = (CCUIListView *)this->getChildByTag(Tag_ListView);
	if (!pListView || !pListView->getChilds())
	{
		return CCPointZero;
	}
	float deltaY = (nIndex+1) * this->getListLayerSize().height + (nIndex) * pListView->getSpacingVertical()  - pListView->getRect().size.height;
	while ( deltaY > POSX(46) && nIndex > 0)
	{
		nIndex -= 1;
		deltaY = (nIndex+1) * this->getListLayerSize().height + (nIndex) * pListView->getSpacingVertical()  - pListView->getRect().size.height;		
	}
	scrollToItemByIndex(index , 0);
	//CCPoint pos = ccp(this->getPosition().x + POSX(50)  , this->getPosition().y - POSX(46) + CCSZIE_LISTVIEW.size.height - this->getListLayerSize().height/*POSX(46)*/ * (nIndex));
	
	if (!pListView->getChilds()->getObjectAtIndex(index))
	{
		return CCPointZero;
	}
	CCPoint pos = getScreenPos(pListView->getChilds()->getObjectAtIndex(index));
	CCPoint delta = ccp(this->getListLayerSize().width/2 , this->getListLayerSize().height/2);
	pos = ccpAdd(pos , delta);
	if (pos.x < 0)
	{
		pos.x += CCSZIE_LISTVIEW.size.width;
	}
	return pos;
#endif
}