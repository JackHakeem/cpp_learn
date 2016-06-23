#include "FriendView.h"
#include "manager/PopEventName.h"
#include "FPContainer.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "PopUIBg.h"
#include "FriendEventConst.h"
#include "TextInputConfirm.h"
#include "manager/layer/WindowLayer.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LevLimitConst.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/ButtonIDConst.h"
#include "manager/ViewManager.h"
#include "../FriendMediator.h"
#include "control/AppFacade.h"
#include "../FriendListenerMediator.h"

FriendView::FriendView()
{
	hasInit = false;
	_pageNum = 0;
	_fpContainer = 0;
	_friCrystalEnabel = false;
	_pContainer = 0;
	_btn_tuijian = 0;
	_btn_Alladd = 0;
}

FriendView::~FriendView()
{
	FriendMediator * pM = (FriendMediator *)g_pFacade->retrieveMediator(AppFacade_Friend_PROXY_CHANGE);
	if (pM)
	{
		pM->_view = 0;
	}
	FriendListenerMediator * p = (FriendListenerMediator *)g_pFacade->retrieveMediator(AppFacade_Friend_PROXY_CHANGE);
	if (p)
	{
		p->_view = 0;
	}
	
	ViewManager::getInstance()->friendView = 0;
	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/friend/res_friend.plist");
}


bool FriendView::init()
{
	if (!CCLayer::init())
	{

		return false;
	}

	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA8888 );

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/friend/res_friend.plist");

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );

	if(!_pContainer)
	{
		_pContainer = new CCLayer();
		_pContainer->setAnchorPoint(CCPointZero);
		_pContainer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));

	}

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);

	//初始化key
	key = PopEventName::FRIEND;	
	//随用户操作变化的面板
	_fpContainer = FPContainer::friendScrollViewWithCCRect(CCRectMake(POSX(28), POSX(92), POSX(904), POSX(446)));
	int pagecount = 20;
	for (int i = 0; i < pagecount; i++)
	{
	//	g_pFPContainer->addLayerByTag(i);
	}

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	_pContainer->addChild(_fpContainer);
    _fpContainer->release();
	//_fpContainer->setPosition(ccp(POSX(0), POSX(0)));

	//title
	CCSprite* title = new CCSprite();
	title->initWithSpriteFrameName("friend/title.png");
	_pContainer->addChild(title, FriendViewZ_title, FriendViewTAG_title);
	title->setPosition(ccp(POSX(470), POSX(550)));

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	//_btn_black
	CCMenuItemSprite *_btn_black = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		this, 
		menu_selector(FriendView::btn_black) );
	_btn_black->setPosition(ccp(POSX(480), POSX(600)));

	CCMenu *buttonMenu_btn_black = new CCMenu();
	buttonMenu_btn_black->init();
	buttonMenu_btn_black->addChild(_btn_black, 0, 0);
	buttonMenu_btn_black->setPosition(ccp(0, 0));
	buttonMenu_btn_black->setTouchLayer(TLE::WindowLayer_Friend);
	_pContainer->addChild(buttonMenu_btn_black, FriendViewZ_btn_black, FriendViewTAG_btn_black);
	buttonMenu_btn_black->release();

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	CCLabelTTF* pLable_btn_black = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI002").c_str(), CCSizeMake(POSX(100), POSX(20)),CCTextAlignmentCenter, "Arial", POSX(20));
	pLable_btn_black->setPosition(ccp(buttonMenu_btn_black->getPosition().x + _btn_black->getContentSize().width/2, 
		buttonMenu_btn_black->getPosition().y + _btn_black->getContentSize().height/2));
	_btn_black->addChild(pLable_btn_black, 2);
	pLable_btn_black->setColor(ccc3(254, 189, 0));

	//_btn_haoyou
	CCMenuItemSprite *_btn_haoyou = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		this, 
		menu_selector(FriendView::btn_haoyou) );
	_btn_haoyou->setPosition(ccp(POSX(306), POSX(600)));

	CCMenu *buttonMenu_btn_haoyou = new CCMenu();
	buttonMenu_btn_haoyou->init();
	buttonMenu_btn_haoyou->addChild(_btn_haoyou, 0, 0);
	buttonMenu_btn_haoyou->setPosition(ccp(0, 0));
	buttonMenu_btn_haoyou->setTouchLayer(TLE::WindowLayer_Friend);
	_pContainer->addChild(buttonMenu_btn_haoyou, FriendViewZ_btn_haoyou, FriendViewTAG_btn_haoyou);
	buttonMenu_btn_haoyou->release();

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	CCLabelTTF* pLable_btn_haoyou = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI001").c_str(), 
		CCSizeMake(POSX(100), POSX(20)),
		CCTextAlignmentCenter,
		"Arial", 
		POSX(20));
	pLable_btn_haoyou->setPosition(ccp(_btn_haoyou->getContentSize().width/2, _btn_haoyou->getContentSize().height/2));
	_btn_haoyou->addChild(pLable_btn_haoyou, 2);
	pLable_btn_haoyou->setColor(ccc3(254, 189, 0));

	//_btn_tuijian
	_btn_tuijian = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		this, 
		menu_selector(FriendView::btn_tuijian) );
	_btn_tuijian->setPosition(ccp(POSX(654), POSX(600)));

	CCMenu *buttonMenu_btn_tuijian = new CCMenu();
	buttonMenu_btn_tuijian->init();
	buttonMenu_btn_tuijian->addChild(_btn_tuijian, 0, 0);
	buttonMenu_btn_tuijian->setPosition(ccp(0, 0));
	buttonMenu_btn_tuijian->setTouchLayer(TLE::WindowLayer_Friend);
	_pContainer->addChild(buttonMenu_btn_tuijian, FriendViewZ_btn_tuijian, FriendViewTAG_btn_tuijian);
	buttonMenu_btn_tuijian->release();

	CCLabelTTF* pLable_btn_tuijian = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI003").c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	pLable_btn_tuijian->setPosition(ccp(_btn_tuijian->getContentSize().width/2, _btn_tuijian->getContentSize().height/2));
	_btn_tuijian->addChild(pLable_btn_tuijian, 2);
	pLable_btn_tuijian->setColor(ccc3(254, 189, 0));

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	//左右箭头
	CCSprite *pLeftNormalSprite = CCSprite::spriteWithSpriteFrameName("friend/arrow.png");
	CCSprite *pLeftPressedSprite = CCSprite::spriteWithSpriteFrameName("friend/arrow.png");
	CCMenuItemSprite *arrow_left = CCMenuItemSprite::itemFromNormalSprite(
		pLeftNormalSprite,
		pLeftPressedSprite,
		this, 
		menu_selector(FriendView::handleArrowBtnPrePage) );
	arrow_left->setPosition(ccp(POSX(740), POSX(50)));

	CCMenu *buttonMenu_arrow_left = new CCMenu();
	buttonMenu_arrow_left->init();
	buttonMenu_arrow_left->addChild(arrow_left, 0, 0);
	buttonMenu_arrow_left->setPosition(ccp(0, 0));
	//buttonMenu_arrow_left->setTouchLayer(TLE::WindowLayer_Friend);
	_pContainer->addChild(buttonMenu_arrow_left, FriendViewZ_arrow_left, FriendViewTAG_arrow_left);
	buttonMenu_arrow_left->release();

	CCSprite *pRightNormalSprite = CCSprite::spriteWithSpriteFrameName("friend/arrow.png");
	CCSprite *pRightPressedSprite = CCSprite::spriteWithSpriteFrameName("friend/arrow.png");
	CCMenuItemSprite *arrow_right = CCMenuItemSprite::itemFromNormalSprite(
		pRightNormalSprite,
		pRightPressedSprite,
		this, 
		menu_selector(FriendView::handleArrowBtnNextPage) );
	arrow_right->setPosition(ccp(POSX(860), POSX(50)));
	arrow_right->setRotation(180.0f);

	CCMenu *buttonMenu_arrow_right = new CCMenu();
	buttonMenu_arrow_right->init();
	buttonMenu_arrow_right->addChild(arrow_right, 0, 0);
	buttonMenu_arrow_right->setPosition(ccp(0, 0));
	//buttonMenu_arrow_right->setTouchLayer(TLE::WindowLayer_Friend);
	_pContainer->addChild(buttonMenu_arrow_right, FriendViewZ_arrow_right, FriendViewTAG_arrow_right);
	buttonMenu_arrow_right->release();

	//页数
	char pTp[10];
	sprintf(pTp, "%d/%d", _pageNum, _fpContainer->totalScreens);
	CCLabelTTF* pLable_pTp = CCLabelTTF::labelWithString(pTp, 
		CCSizeMake(POSX(200), POSX(50)),
		CCTextAlignmentCenter,
		"Arial", 
		POSX(50));
	pLable_pTp->setPosition(ccp(POSX(800), POSX(50)));
	_pContainer->addChild(pLable_pTp, FriendViewZ_page, FriendViewTAG_page);
	pLable_pTp->setColor(ccc3(254, 189, 0));
	//初化按钮
	changeBtn(0);
	_fpContainer->setindex(0);


	//
	this->addChild(_pContainer);
	_pContainer->release();

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	return true;
}

void FriendView::updatePageShow(int max, int index)
{
	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);
	CCLabelTTF* pLable_pTp = (CCLabelTTF*)_pContainer->getChildByTag(FriendViewTAG_page);
	if (pLable_pTp)
	{
		char pTp[10];
		sprintf(pTp, "%d/%d", index, max);

		pLable_pTp->setString(pTp);
	}
}

void FriendView::btn_haoyou(CCObject* pSender)
{
	onTabIndexChange(0);
}

void FriendView::btn_black(CCObject* pSender)
{
	onTabIndexChange(3);
}

void FriendView::btn_tuijian(CCObject* pSender)
{
	onTabIndexChange(2);
}

void FriendView::btn_addPlayer(CCObject* pSender)
{
	// add CCTextFieldTTF
	TextInputConfirm* pConfirm = new TextInputConfirm();
	pConfirm->initWithParam(ValuesUtil::Instance()->getString("FRI017").c_str(), this, menu_selector(FriendView::handleAddPlayerConfirm), menu_selector(FriendView::handleAddPlayerCancel));
	//LayerManager::windowLayer->addChild(pConfirm,WindowLayer::WindowLayerZ_textInputConfirm, WindowLayer::WindowLayerTAG_textInputConfirm);
	LayerManager::tipsLayer->addChild(pConfirm, TipsLayer::TipsLayerZ_textInputConfirm,TipsLayer::TipsLayerTAG_textInputConfirm);
	pConfirm->release();
}

void FriendView::btn_oneClickAddAllPlayer(CCObject* pSender)
{
	//new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Friend) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Friend , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_FRIEND_OVER);
	}

	quickAddRecommendFriends();
}

void FriendView::btn_toBlack(CCObject* pSender)
{

}

void FriendView::handleArrowBtnNextPage(CCObject* pSender)
{
	if (_fpContainer)
		_fpContainer->handleTouchEndPageNext();
}

void FriendView::handleArrowBtnPrePage(CCObject* pSender)
{
	if (_fpContainer)
		_fpContainer->handleTouchEndPagePre();
}

void FriendView::handleAddPlayerConfirm(CCObject* pSender)
{
	//addGrid(tmp_num, tmp_money);
	//??????
	//_pBankCreate->setHeightLine(tmp_sitNum, false);
	//remove??
	//
		
	//this->dispatchEvent(FriendEventConst::ADD_FRIEND, (void*)&param->name);//new ParamEvent(FriendEventConst.ADD_FRIEND, (event.param as FriendInfoVo).name));


	TextInputConfirm* pConfirm = (TextInputConfirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_textInputConfirm);
	if (pConfirm)
	{
		char p[50];// = pConfirm->getString();
		strcpy(p, pConfirm->getString());
		std::string data = p;
		if (data.size() == 0)
		{
			LangManager::msgShow( "FRI016" );
			return;
		}
		this->dispatchEvent(FriendEventConst::ADD_FRIEND, (void*)&data);
	}

	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;
}

void FriendView::handleAddPlayerCancel(CCObject* pSender)
{
	//??????
	//_pBankCreate->setHeightLine(tmp_sitNum, false);
	//remove??
	TextInputConfirm* pConfirm = (TextInputConfirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_textInputConfirm);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
	return;
}




void FriendView::onClickPre()
{
	int32 data = _pageNum-1;
	dispatchEvent(CHANGE_PAGE, &data);
}

//点击下一页
void FriendView::onClickNext()
{	
	int32 data = _pageNum+1;
	this->dispatchEvent(CHANGE_PAGE, &data);
}

/**
	* 更新列表 
	* @param arr
	* 
	*/		
void FriendView::updateList(std::list<FriendInfoVo>* arr, int32 page)
{
	if (!_fpContainer) return;
	//_fpContainer->removeAllChildrenWithCleanup(true);
	CCLayer* l = _fpContainer->getLayerByTag(page-1);
	if (l)
		l->removeAllChildrenWithCleanup(true);
	else
	{//新建页
		l = _fpContainer->addLayerByTag(page-1);
	}

	CCLog("release run to: line:%d file: %s", __LINE__, __FILE__);

	_fpContainer->_list.clear();//这里也要清除掉控件的所有条目
	std::list<FriendInfoVo>::iterator it;
	int32 index = 0;
	for (it = arr->begin(); it != arr->end(); it++, index++)
	{
		_fpContainer->setlistItem(*it, index, l);	
	}
	//_fpContainer->updateFList();//更新显示
	hasInit = true;
	//_fpContainer.index +1;
	bool same = (_pageNum == page)?true:false;
	_fpContainer->handleTouchEndAfter(same, page-1);
	_pageNum = page;

	//更新当前页总页数
	//updatePageShow();

}


/**
	* 设置分页条 
	* @param max
	* @param index
	* 
	*/		
void FriendView::setPage(int32 max, int32 index)
{
	//更新当前页总页数
	updatePageShow(max, index);
}

/**
	* 用户切换列表时 
	* @param event
	* 
	*/		
void FriendView::onTabIndexChange(int32 type)
{
	if (!_fpContainer)
		return;
	//随用户操作变化的面板
    //_fpContainer->release();
	//int old_currentScreen = _fpContainer->currentScreen;
    _fpContainer->removeFromParentAndCleanup(true);
	_pContainer->removeChild(_fpContainer, true);
	_fpContainer = FPContainer::friendScrollViewWithCCRect(CCRectMake(POSX(28), POSX(92), POSX(904), POSX(446)));
	//_fpContainer->currentScreen = old_currentScreen;
	int pagecount = 20;
	for (int i = 0; i < pagecount; i++)
	{
		//g_pFPContainer->addLayerByTag(i);
	}

	_pContainer->addChild(_fpContainer);
    _fpContainer->release();
	switch(type)
	{
	case 0://好友
		changeBtn(0);
		_fpContainer->setindex(0);
		break;
//				case "_tab2"://最近联系
//					changeBtn(1);
//					_fpContainer.index =1;
//
//					Type = 1;
//					break;
	case 3://黑名单
		changeBtn(3);
		_fpContainer->setindex(2);
		break;
	case 2://在线玩家
		changeBtn(2);
		_fpContainer->setindex(3);
		break;
	}

	dispatchEvent(CHANGE_LIST, &type);
}

void FriendView::changeBtn(int32 type)
{
	//CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//delete old
	CCMenu* del = (CCMenu*)_pContainer->getChildByTag(FriendViewTAG_btn0);
	if (del)
		_pContainer->removeChildByTag(FriendViewTAG_btn0, true);
	//create new
	switch (type)
	{
	case 0://好友
		{
			//添加好友
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				this, 
				menu_selector(FriendView::btn_addPlayer) );
			_btn_check->setPosition(ccp(POSX(280/* + 60*/), POSX(50)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu_btn_check = new CCMenu();
			buttonMenu_btn_check->init();
			buttonMenu_btn_check->addChild(_btn_check, 0, 0);
			buttonMenu_btn_check->setPosition(ccp(0, 0));
			buttonMenu_btn_check->setTouchLayer(TLE::WindowLayer_Friend-1);
			_pContainer->addChild(buttonMenu_btn_check, FriendViewZ_btn0, FriendViewTAG_btn0);
			buttonMenu_btn_check->release();	
		
			CCLabelTTF* pLable_btn_check = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI007").c_str(),
				CCSizeMake(POSX(200), POSX(20)),
				CCTextAlignmentCenter,
				"Arial",
				POSX(20));
			pLable_btn_check->setPosition(ccp(_btn_check->getContentSize().width/2, _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn_check, 2);
			pLable_btn_check->setColor(ccc3(254, 189, 0));
			//pLable_btn_check->setScaleX(1.2f);
		}
		break;
	case 3://黑名单
		{
			//添加好友
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return;
			}
			CCMenuItemSprite *_btn_check = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				this, 
				menu_selector(FriendView::btn_addPlayer) );
			_btn_check->setPosition(ccp(POSX(280), POSX(50)));

			//_btn_check->setScaleX(0.8f);//规模

			CCMenu *buttonMenu_btn_check = new CCMenu();
			buttonMenu_btn_check->init();
			buttonMenu_btn_check->addChild(_btn_check, 0, 0);
			buttonMenu_btn_check->setPosition(ccp(0, 0));
			buttonMenu_btn_check->setTouchLayer(TLE::WindowLayer_Friend-1);
			_pContainer->addChild(buttonMenu_btn_check, FriendViewZ_btn0, FriendViewTAG_btn0);
			buttonMenu_btn_check->release();	
		
			CCLabelTTF* pLable_btn_check = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI007").c_str(),
				CCSizeMake(POSX(200), POSX(20)),
				CCTextAlignmentCenter,
				"Arial", 
				POSX(20));
			pLable_btn_check->setPosition(ccp(_btn_check->getContentSize().width/2, _btn_check->getContentSize().height/2));
			_btn_check->addChild(pLable_btn_check, 2);
			pLable_btn_check->setColor(ccc3(254, 189, 0));
			//pLable_btn_check->setScaleX(1.2f);
		}
		break;
	case 2://在线玩家
		{
			//一键
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			if(!pNormalSprite || !pPressedSprite)
			{
				return;
			}
			_btn_Alladd = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite, 
				this, 
				menu_selector(FriendView::btn_oneClickAddAllPlayer) );
			_btn_Alladd->setPosition(ccp(POSX(280 + 60), POSX(50)));

			_btn_Alladd->setScaleX(1.4f);//规模

			CCMenu *buttonMenu_btn_check = new CCMenu();
			buttonMenu_btn_check->init();
			buttonMenu_btn_check->addChild(_btn_Alladd, 0, 0);
			buttonMenu_btn_check->setPosition(ccp(0, 0));
			buttonMenu_btn_check->setTouchLayer(TLE::WindowLayer_Friend-1);
			_pContainer->addChild(buttonMenu_btn_check, FriendViewZ_btn0, FriendViewTAG_btn0);
			buttonMenu_btn_check->release();	
		
			CCLabelTTF* pLable_btn_check = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FRI008").c_str(),
				CCSizeMake(POSX(200), POSX(20)),
				CCTextAlignmentCenter,
				"Arial",
				POSX(20));
			pLable_btn_check->setPosition(ccp(_btn_Alladd->getContentSize().width/2, _btn_Alladd->getContentSize().height/2));
			_btn_Alladd->addChild(pLable_btn_check, 2);
			pLable_btn_check->setColor(ccc3(254, 189, 0));
			pLable_btn_check->setScaleX(0.8f);

			// new hand
			if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Friend) == NewhandManager::Flag_New)
			{
				NewhandManager::Instance()->touchNextEvent(802);
			}
		}
		break;
	}
}

void FriendView::clickCloseHandler(CCObject* pSender)
{
	PopContainer::clickCloseHandler(pSender);

	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Friend) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextScript("addBtn" , ButtonIDConst::ButtonID_Friend);
	}
	else if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Friend) == NewhandManager::Flag_Done)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Friend , NewhandManager::Flag_Close);
		NewhandManager::Instance()->doTaskFollow();
	}
}

void FriendView::quickAddRecommendFriends()
{
	//this.dispatchEvent(new Event(FriendEventConst.QUICK_ADD_RECOMMEND_FRIENDS));
	this->dispatchEvent(FriendEventConst::QUICK_ADD_RECOMMEND_FRIENDS, 0);
}

CCNode * FriendView::getNewHandItem(int id)
{
	switch (id)
	{
	case 100:
		{
			return _btn_tuijian;
		}
		break;
	case 101:
		{
			return _btn_Alladd;
		}
		break;
	default:
		break;
	}
	
	return 0;
}
