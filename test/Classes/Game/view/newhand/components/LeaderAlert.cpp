#include "LeaderAlert.h"
#include "manager/LayerManager.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "model/newhand/vo/NewhandConst.h"
#include "bear/manager/DisplayObjectManager.h"
#include "view/scene/components/Scene.h"
#include "events/GameDispatcher.h"
#include "manager/ViewManager.h"
#include "model/scene/vo/SceneConst.h"

LeaderAlert *_preInstance = 0;

LeaderAlert::LeaderAlert( string info, int type, bool isModel, CCNode *pTarget, SEL_CallFuncND selector, void *data )
{
	_type = type;
	m_pri = -2000;
	_callBack.m_pSelectorTarget = pTarget;
	_callBack.m_pCallFuncND = selector;
	_callBack.m_data = data;
	_pGlow = NULL;
	if(_type == 1)
	{
		//小提示框，如战斗失败提示
		//_skin = Reflection.createInstance("eAlertFail");
	}
	else if(_type == 2)
	{
		//大提示框，如水晶升级提示
		//_skin = Reflection.createInstance("eAlertNovice");
	}
	else if(_type == 3)
	{
		//领取金币、前往报道
		//_skin = Reflection.createInstance("eAlertLead");
	}
	else if(_type == 4)
	{
		//招募伊莎贝尔
		//_skin = Reflection.createInstance("_mcTutor");
	}
	else if(_type == 5)
	{
		//各种新增功能
		//_skin = Reflection.createInstance("ui_newSysTip");
	}
	else
	{
		return;
	}
	
	/*_skin.x = StageProxy.width - _skin.width >> 1;
	_skin.y = StageProxy.height - _skin.height >> 1;
	setModel(isModel);*/
	//LayerManager::windowLayer->addChild(_skin);
	/*info = info.replace(/#l/g, "<font color='#FFCC00'>");
	info = info.replace(/#r/g, "</font>");*/

	bool isShow = false;
    int picId = atoi(info.c_str());
	switch(_type){
	case 1:
		//_skin.y += 200;
		//playInfo1(info);
		return;
		break;
	case 2:
		//_skin.y += 200;
		//playInfo2(info);
		return;
		break;
	case 3:
		isShow = playInfo3(info);
		break;
	case 4:
		//playInfo4(int(info));
		return;
		break;
	case 5:
		isShow = playInfo5(picId);
		break;
	}
	if(!isShow)
	{
	}
	else
	{
		this->setContentSize(CCDirector::sharedDirector()->getWinSize());
		this->setAnchorPoint(CCPointZero);
		//LayerManager::windowLayer->addChild(this);

		//Doyang 20120726
		LayerManager::newhandLayer->addChild(this, -1);

        if(picId == 3 || picId == 4)
        {
            //Doyang 20120821
            GameDispatcher::getInstance()->addEventListener(PopContainer::OPEN_CONTAINER, this, callfuncND_selector(LeaderAlert::onPopContainerOpen));
        }
	}

	// newhandhelpview
	//int para = picId+5000;
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::RESET_NEWHELP_VIEW , (void*)&para);

	//Doyang 20120814
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::WALK_COMPLETE,0);
	Scene *pScene = ViewManager::getInstance()->_scene;
	if(pScene && pScene->_role && pScene->_role->poseState)
	{
		pScene->_role->poseState->state(SceneConst::STAND);
	}
}

LeaderAlert::~LeaderAlert() 
{
	CCTextureCache::sharedTextureCache()->removeTextureForKey("res_loading.pvr.ccz");
}

LeaderAlert* LeaderAlert::show( string info, int type, bool isModel, CCNode *pTarget, SEL_CallFuncND selector, void *data )
{
	if(_preInstance)
	{
		_preInstance->close();
	}
	_preInstance = new LeaderAlert(info, type, isModel, pTarget, selector, data);
	if(_preInstance && _preInstance->init())
	{
		return _preInstance;
	}
	return NULL;
}

void LeaderAlert::close()
{
	closeModel();
	dispose();
}

/* 显示领取金币、前往报道 */
bool LeaderAlert::playInfo3( string info )
{
	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	this->setPosition(POS(ccp(0, 90), ScaleUtil::CENTER_LEFT));


	// LH
	CCSize _winSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground * pBack = new CCUIBackground();
	pBack->initWithSpriteFrame("ui.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_winSize.width , POSX(400)));
	pBack->setPosition(ccp(POSX(0) , /*_winSize.height/2 - POSX(200)*/POSX(0)));
	this->addChild(pBack);
	pBack->release();

	CCUIBackground * pContentBack = new CCUIBackground();
	pContentBack->initWithSpriteFrame("ui2.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_winSize.width/2 + POSX(60), POSX(225)));
	pContentBack->setPosition(ccp(POSX(140 + 190) , /*_winSize.height/2 - POSX(126)*/POSX(85)));
	this->addChild(pContentBack,1);
	pContentBack->release();

	// leader pic
	CCSprite * pLeader = new CCSprite();
	if (pLeader)
	{
		bool bSuc = pLeader->initWithSpriteFrameName("loading/girl.png");
		if (!bSuc)
		{
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/loading/res_loading.plist");
			pLeader->initWithSpriteFrameName("loading/girl.png");
		}
		pLeader->setFlipX(true);
		pLeader->setAnchorPoint(CCPointZero);
		pLeader->setPosition(ccp(POSX(-30),POSX(10)));
		pLeader->setScale(1.0);
		this->addChild(pLeader , 2);
		pLeader->release();
	}
	
	CCLabelTTF *pContentLabel = CCLabelTTF::labelWithString(pValueUtil->getString("NH001").c_str(), 
		CCSizeMake(POSX(500 - 10), POSX(90+30)),
		CCTextAlignmentLeft,
		"Arial", 
		POSX(30));
	if(pContentLabel)
	{
		pContentLabel->setColor(ccc3(255, 255, 0));
		pContentLabel->setAnchorPoint(CCPointZero);
		pContentLabel->setPosition(ccp(POSX(210 + 160), POSX(190 - 20)));
		this->addChild(pContentLabel , 3);
	}

	/*
	CCSprite *pNpcHalfIcon = CCSprite::spriteWithFile("assets/ui/newhand/newhand_alert_001.png");
	if(pNpcHalfIcon)
	{
		pNpcHalfIcon->setAnchorPoint(CCPointZero);
		pNpcHalfIcon->setPosition(ccp(POSX(-116), POSX(4)));
		this->addChild(pNpcHalfIcon);
	}
	*/
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/newhand/res_newhand_wel.plist");
	CCSprite *pTitleSprite = CCSprite::spriteWithSpriteFrameName("newhand/newhand_alert_002.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/newhand/res_newhand_wel.plist");
	if(pTitleSprite)
	{
		pTitleSprite->setAnchorPoint(CCPointZero);
		pTitleSprite->setPosition(ccp(POSX(188 + 180), POSX(330)));
		this->addChild(pTitleSprite);
	}
	
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pNormalSprite || !pPressedSprite)
	{
		return false;
	}
	CCMenuItemSprite *pGoldItem = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this,
		menu_selector(LeaderAlert::menuCallback) );
	if(pGoldItem)
	{
		pGoldItem->setPosition(ccp(POSX(480), POSX(20)));
		pGoldItem->setAnchorPoint(CCPointZero);
		pGoldItem->setScaleX(1.0f);
		pGoldItem->setTag(3);
		CCMenu *pGoldMenu = CCMenu::menuWithItems(pGoldItem, NULL);
		pGoldMenu->setPosition(CCPointZero);
		pGoldMenu->setTouchLayer(m_pri - 1);
		this->addChild(pGoldMenu);
	}
	

	CCLabelTTF *pGoldLabel = CCLabelTTF::labelWithString(pValueUtil->getString("NH002").c_str(), 
		CCSizeMake(POSX(190), POSX(30)),
		CCTextAlignmentLeft,
		"Arial", 
		POSX(26));
	if(pGoldLabel)
	{
		pGoldLabel->setColor(ccc3(255, 230, 182));
		pGoldLabel->setAnchorPoint(CCPointZero);
		pGoldLabel->setPosition(ccp(POSX(486+10), POSX(28)));
		this->addChild(pGoldLabel);
	}

	_pGlow = new ObjectGlow(pGoldItem, NewhandConst::LOC_DEFAULT, this, 11, "", false, ccpAdd(this->getPosition(), ccp(POSX(330), POSX(6))));

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/loading/res_loading.plist");
	

	return true;
}

void LeaderAlert::menuCallback( CCObject *pSender )
{
	if(!pSender)
	{
		return;
	}

	CCMenu *pTaskMenu = (CCMenu *) pSender;
	int tag = pTaskMenu->getTag();
	switch(tag)
	{
	case 1:
		break;

	case 2:
		break;

	case 3:
		// First 200 Gold.
		//领取金币，前往报道
		{
			close();
			//DisplayObjectManager::getInstance()->showFirstGoldEffect();	

			if (ViewManager::getInstance()->_secNavigate)
			{
				ViewManager::getInstance()->_secNavigate->popUIHandlerLoginReward(0);
			}
		}
		break;

	case 4:
		break;

	case 5:
		{
			close();
			_callBack.execute();
		}
		break;

	default:
		break;
	}

	// close pop
	{
		if (ViewManager::getInstance()->dialogView
			&& ViewManager::getInstance()->dialogView->getisPop())
		{
			ViewManager::getInstance()->dialogView->setisPop(false);
		}		
	}
}

void LeaderAlert::dispose()
{
	if(_pGlow)
	{
		_pGlow->stopAndClear();
	}
	if(this->getParent())
		this->removeFromParentAndCleanup(true);
}

void LeaderAlert::closeModel()
{

}

bool LeaderAlert::playInfo5( int picId )
{
	//
	//assets\icon\tips
	//ValuesUtil *pValueUtil = ValuesUtil::Instance();
	this->setAnchorPoint(CCPointZero);
	this->setPosition(CCPointZero);
	this->setIsRelativeAnchorPoint(true);

	CCLayer *tipLayer = new CCLayer();
	tipLayer->setPosition(POS(ccp(190, 126), ScaleUtil::CENTER));
	tipLayer->setAnchorPoint(CCPointZero);
	tipLayer->setContentSize(CCSizeMake(POSX(556), POSX(452)));

	//this->setPosition(POS(ccp(190, 126), ScaleUtil::CENTER));

	/*
	CCUIBackground *pBackgroundFrame1 = new CCUIBackground();
	if(pBackgroundFrame1)
	{
		pBackgroundFrame1->initWithFile("assets/ui/popuibg/bg1.png", CCPointZero, CCPointZero, CCSizeMake(POSX(556), POSX(452)));
		pBackgroundFrame1->setAnchorPoint(CCPointZero);
		tipLayer->addChild(pBackgroundFrame1);
		pBackgroundFrame1->release();
	}


	CCUIBackground* pBackgroundFrame2 = new CCUIBackground();
	if(pBackgroundFrame2)
	{
		pBackgroundFrame2->initWithFile("assets/ui/popuibg/bg2.png", ccp(POSX(14), POSX(98)), CCPointZero, CCSizeMake(POSX(528), POSX(330)));
		pBackgroundFrame2->setAnchorPoint(CCPointZero);
		tipLayer->addChild(pBackgroundFrame2);
		pBackgroundFrame2->release();
	}
	*/
	CCSize _winSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground * pBack = new CCUIBackground();
	pBack->initWithSpriteFrame("ui.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_winSize.width , POSX(400)));
	pBack->setPosition(ccp(POSX(-190) , /*_winSize.height/2 - POSX(200)*/POSX(0)));
	tipLayer->addChild(pBack);
	pBack->release();

	CCUIBackground * pContentBack = new CCUIBackground();
	pContentBack->initWithSpriteFrame("ui2.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_winSize.width/2 + POSX(60), POSX(305)));
	pContentBack->setPosition(ccp(POSX(140) , /*_winSize.height/2 - POSX(126)*/POSX(70)));
	tipLayer->addChild(pContentBack,1);
	pContentBack->release();

	// leader pic
	CCSprite * pLeader = new CCSprite();
	if (pLeader)
	{
		bool bSuc = pLeader->initWithSpriteFrameName("loading/girl.png");
		if (!bSuc)
		{
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/loading/res_loading.plist");
			pLeader->initWithSpriteFrameName("loading/girl.png");
		}
		pLeader->setFlipX(true);
		pLeader->setAnchorPoint(CCPointZero);
		pLeader->setPosition(ccp(POSX(-30),POSX(136)));
		pLeader->setScale(1.0);
		this->addChild(pLeader , 2);
		pLeader->release();
	}

	char pPath[128];
	sprintf(pPath, "assets/icon/tips/res_tips_%d.plist", picId);
	std::string szPath(pPath);

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGB565 );
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(szPath.c_str());
	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );

	memset(pPath , 0 ,sizeof(pPath));
	sprintf(pPath, "tips_%d/%d.jpg", picId , picId);

	CCSprite *pPicSprite = CCSprite::spriteWithSpriteFrameName(pPath);
	if(pPicSprite)
	{
		pPicSprite->setAnchorPoint(CCPointZero);
		pPicSprite->setPosition(ccp(POSX(24 + 132), POSX(120 -40)));
		tipLayer->addChild(pPicSprite,3);
	}
	else
	{
		memset(pPath , 0 , sizeof(pPath));
		sprintf(pPath, "tips_%d/%d.png", picId , picId);
		pPicSprite = CCSprite::spriteWithSpriteFrameName(pPath);
		if (!pPicSprite)
		{
			return false;
		}
		pPicSprite->setAnchorPoint(CCPointZero);
		pPicSprite->setPosition(ccp(POSX(24 + 132), POSX(120 -40)));
		tipLayer->addChild(pPicSprite,3);
	}
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(szPath.c_str());

	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pNormalSprite || !pPressedSprite)
	{
		return false;
	}
	CCMenuItemSprite *pGoldItem = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this,
		menu_selector(LeaderAlert::menuCallback) );
	if(pGoldItem)
	{
		pGoldItem->setPosition(ccp(POSX(212), POSX(26)));
		pGoldItem->setAnchorPoint(CCPointZero);
		pGoldItem->setScaleX(1.2f);
		pGoldItem->setTag(5);
		CCMenu *pGoldMenu = CCMenu::menuWithItems(pGoldItem, NULL);
		pGoldMenu->setPosition(/*CCPointZero*/ccp(POSX(150) , POSX(-10)));
		pGoldMenu->setTouchLayer(m_pri - 1);
		tipLayer->addChild(pGoldMenu);
	}

	

	CCLabelTTF *pGoldLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("NH003").c_str(), 
		CCSizeMake(POSX(148), POSX(52)),
		CCTextAlignmentCenter,
		"Arial", 
		POSX(30));
	if(pGoldLabel)
	{
		pGoldLabel->setColor(ccc3(255, 230, 182));
		pGoldLabel->setAnchorPoint(CCPointZero);
		pGoldLabel->setPosition(ccp(POSX(362), POSX(13)));
		tipLayer->addChild(pGoldLabel);
	}

	this->addChild(tipLayer);
	tipLayer->release();


	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/loading/res_loading.plist");

	return true;
}

void LeaderAlert::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, m_pri, true);
}

bool LeaderAlert::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	//Doyang 20120813
	return true;

	switch(_type)
	{
	case 1:
		this->close();
		break;

	case 2:
		this->close();
		break;

	case 3:
		// do nothing.
        return true;
		break;

	case 4:
		this->close();
		break;

	case 5:
		// jae0816
		this->close();
		break;
	default:
		this->close();
		break;
	}
	return false;
}

bool LeaderAlert::init()
{
	if(!LayerNode::init())
	{
		return false;
	}
	this->setIsTouchEnabled(true);
	return true;
}

void LeaderAlert::onPopContainerOpen( CCNode *pNode, void *pData )
{
	this->close();
}
