#include "view/figure/components/FigureView.h"
#include "manager/ViewManager.h"
#include "model/figure/vo/WashVo.h"
#include "model/player/FigureBaseManage.h"
#include "model/player/RoleManage.h"
#include "utils/ValuesUtil.h"
#include "SkillView.h"
#include "PeiyangView.h"
#include "model/figure/EquipmentManager.h"
#include "socket/command/c17/CCMD170.h"
#include "socket/network/GameServerSocket.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "EquiptmentItem.h"
#include "utils/TipHelps.h"
#include "NameUIPartialScrollView.h"
#include "utils/ScaleUtil.h"
#include "view/figure/components/SkillItem.h"
#include "utils/TipHelps.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "MessageInfoBox.h"
#include "StuntsLayer.h"
#include "model/skill/SkillManager.h"
#include "model/skill/vo/SkillType.h"
#include "Message.h"
#include "model/backpack/BagProxy.h"
#include "control/AppFacade.h"
#include "model/task/TaskProxy.h"
#include "view/equipmentDrop/DropMediator.h"
#include "FigureCreate.h"
#include "model/newhand/vo/TestNewhand.h"
#include "model/newhand/NewhandManager.h"
#include "SkillUIPartialScrollView.h"
#include "manager/LevLimitConst.h"
#include "utils/TipsSkillCanvas.h"
#include "manager/PopManage.h"

FigureView::FigureView()
{
	_currentId = 0;
	_statPanel = STAT_ROLE;
	_stateSkill = 0;
	_skillV = 0;
	_peiyangV = 0;
	__container = NULL;
	_attrLayer = 0;
	_skillPopLayer = 0;

	_highLightIndex = 0;
	_IsStuntsPop = false;
	_nTouchCount = 0;
	_pCurSelectEquip = 0;
	_nClickIndex = -1;
	_nClickIndexCount = 0;
	_isSelected = false;

	_buttonAtr = 0;
	_buttonTrain = 0;
	_buttonPeiyang = 0;
	_buttonJianding = 0;

	buttonMenuAtr = 0;
	buttonMenuTrain = 0;
	buttonMenuPeiyang = 0;
	buttonMenuJianding = 0;
	buttonMenuChucu = 0;

	memset(RoleID,0,sizeof(RoleID));
	memset(SkillID,0,sizeof(SkillID));
	init();
}

FigureView::FigureView(CCSize& size)
{
	m_viewSize.height = size.height;
	m_viewSize.width = size.width;
	_currentId = 0;
	_skillV = 0;
	_peiyangV = 0;
	_statPanel = STAT_ROLE;
	_stateSkill = 0;
	__container = NULL;
	_attrLayer = 0;
	_skillPopLayer = 0;

	_highLightIndex = 0;
	_nTouchCount = 0;
	_pCurSelectEquip = 0;
	_nClickIndex = -1;
	_nClickIndexCount = 0;
	_IsStuntsPop = false;

	_buttonAtr = 0;
	_buttonTrain = 0;
	_buttonPeiyang = 0;
	_buttonJianding = 0;

	buttonMenuAtr = 0;
	buttonMenuTrain = 0;
	buttonMenuPeiyang = 0;
	buttonMenuJianding = 0;
	buttonMenuChucu = 0;

	memset(RoleID,0,sizeof(RoleID));
	memset(SkillID,0,sizeof(SkillID));
	init();
}

bool FigureView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_viewSize = CCSizeMake(POSX(444),CCDirector::sharedDirector()->getWinSize().height);

	if(!__container)
	{
		__container = new LayerNode();
		__container->setAnchorPoint(CCPointZero);
		__container->setIsRelativeAnchorPoint(true);
		__container->setPosition(CCPointZero);
		__container->setTag(TAG_Container);
		this->addChild(__container,0);

		__container->release(); //LH20120109
	}

    //return true;
    
	SpriteNode * sTitle = new SpriteNode();
	sTitle->initWithSpriteFrameName("new/figure.png");
	sTitle->setAnchorPoint(CCPointZero);
	sTitle->setIsRelativeAnchorPoint(true);

	sTitle->setPosition(ccp(POSX(440), POSX(530)));
	this->addChild(sTitle);
	sTitle->release(); //LH20120109

	addButton();

	return true;
}

void FigureView::addButton()
{
	CCSize csBt( POSX(154), POSX(61) );
	_csBt = csBt;
	// shuxing
	_buttonAtr = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		this, 
		menu_selector(FigureView::clickButtonAtt));
	_buttonAtr->setTag(TAG_BTN_IMG);
	_buttonAtr->setIsEnabled(false);
	buttonMenuAtr = CCMenu::menuWithItems(_buttonAtr, NULL);
	buttonMenuAtr->setTag(TAG_BTN_SHUXING);
	buttonMenuAtr->setTouchLayer( TLE::WindowLayer_Common_btn );
	buttonMenuAtr->setPosition(ccp(POSX(176+100-330+176), POSX(588)));
	__container->addChild(buttonMenuAtr, RENDERZ_button);

	CCLabelTTF* pLabel1 = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("MUI200").c_str(),
		CCSizeMake(_buttonAtr->getContentSize().width, _buttonAtr->getContentSize().height),
		CCTextAlignmentCenter,
		g_sSimHeiFont, 
		POSX(20) );
	pLabel1->setColor(ccc3(255,240,0));
	pLabel1->setPosition( ccp(csBt.width/ 2.0f,csBt.height/2) );
	_buttonAtr->addChild(pLabel1);

	// xunlian
	_buttonTrain = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
		this, 
		menu_selector(FigureView::clickButtonTrain));
	_buttonTrain->setTag(TAG_BTN_IMG);
	buttonMenuTrain = CCMenu::menuWithItems(_buttonTrain, NULL);
	buttonMenuTrain->setTag(TAG_BTN_XUNLIAN);
	buttonMenuTrain->setTouchLayer( TLE::WindowLayer_Common_btn );
	buttonMenuTrain->setPosition(ccp(POSX(176+100-330+176), POSX(588)));
	__container->addChild(buttonMenuTrain, RENDERZ_button);

	pLabel1 = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("MUI004").c_str(),
		CCSizeMake(_buttonTrain->getContentSize().width, _buttonTrain->getContentSize().height),
		CCTextAlignmentCenter,
		g_sSimHeiFont, 
		POSX(20) );
	pLabel1->setColor(ccc3(255,240,0));
	pLabel1->setPosition( ccp(csBt.width/ 2.0f,csBt.height/2) );
	_buttonTrain->addChild(pLabel1);

	// peiyang
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Peiyang)
	{
		_buttonPeiyang = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this, 
			menu_selector(FigureView::clickButtonPeiyang));
		_buttonPeiyang->setTag(TAG_BTN_IMG);
		buttonMenuPeiyang = CCMenu::menuWithItems(_buttonPeiyang, NULL);
		buttonMenuPeiyang->setTag(TAG_BTN_PEIYANG);
		buttonMenuPeiyang->setTouchLayer( TLE::WindowLayer_Common_btn );
		buttonMenuPeiyang->setPosition(ccp(POSX(176+100), POSX(588)));
		__container->addChild(buttonMenuPeiyang, RENDERZ_button);
		if (RoleManage::Instance()->roleLev() < LevLimitConst::Limit_Peiyang)
		{
			buttonMenuPeiyang->setIsVisible(false);
		}	

		pLabel1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("peiyang").c_str(),
			CCSizeMake(_buttonPeiyang->getContentSize().width,_buttonPeiyang->getContentSize().height),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20));
		pLabel1->setColor(ccc3(255,240,0));
		pLabel1->setPosition( ccp(csBt.width/ 2.0f,csBt.height/2) );
		_buttonPeiyang->addChild(pLabel1);
	}	

	{
		// jianding
		_buttonJianding = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this, 
			menu_selector(FigureView::clickButtonIdentify));
		_buttonJianding->setTag(TAG_BTN_IMG);
		buttonMenuJianding = CCMenu::menuWithItems(_buttonJianding, NULL);
		buttonMenuJianding->setTag(TAG_BTN_IDENTIFY);
		buttonMenuJianding->setTouchLayer( TLE::WindowLayer_Common_btn );
		buttonMenuJianding->setPosition(ccp(POSX(484), POSX(588)));
		__container->addChild(buttonMenuJianding, RENDERZ_button);

		pLabel1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("IDT005").c_str(),
			CCSizeMake(_buttonJianding->getContentSize().width,_buttonJianding->getContentSize().height),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20));
		pLabel1->setColor(ccc3(255,240,0));
		pLabel1->setPosition( ccp(csBt.width/ 2.0f,csBt.height/2) );
		_buttonJianding->addChild(pLabel1);

		buttonMenuJianding->setIsVisible(false); // LH20121016 unused
	}

	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(pNormalSprite && pPressedSprite)
	{
		CCMenuItemSprite *_buttonSkill = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(FigureView::clickButtonSkill));

		CCMenu *buttonMenuSkill = CCMenu::menuWithItems(_buttonSkill, NULL);
		buttonMenuSkill->setPosition(CCPointZero);
		_buttonSkill->setPosition(ccp(POSX(590), POSX(40)));
		__container->addChild(buttonMenuSkill, RENDERZ_buttonSkill);
		CCLabelTTF* pLabel2 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("skill").c_str(),
			CCSizeMake(_buttonSkill->getContentSize().width,_buttonSkill->getContentSize().height),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20));
		pLabel2->setColor(ccc3(255,240,0));
		pLabel2->setPosition(ccp(POSX(590), POSX(40)));
		__container->addChild(pLabel2, RENDERZ_lableSkill);

		buttonMenuSkill->setIsTouchEnabled(false);
		buttonMenuSkill->setIsVisible(false);	
		pLabel2->setIsVisible(false);

	}

	// zhuangbeichuchu
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_1.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_1.png");
		CCMenuItemSprite *_button = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(FigureView::clickButtonEQ));
		//_button->setScaleX(2.0f);

		buttonMenuChucu = CCMenu::menuWithItems(_button, NULL);
		buttonMenuChucu->setTag(TAG_BTN_EQ);
		buttonMenuChucu->setTouchLayer( TLE::IntervalLayer_guild+10 );
		buttonMenuChucu->setPosition(CCPointZero);
		_button->setPosition(ccp(POSX(730), POSX(592)));
		__container->addChild(buttonMenuChucu, RENDERZ_button);

		pLabel1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("eq").c_str(),
			CCSizeMake(_button->getContentSize().width,_button->getContentSize().height),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(20));
		pLabel1->setColor(ccc3(255,240,0));
		pLabel1->setPosition( ccp(csBt.width/ 2.0f-10.0f,csBt.height/2-4.0f) );
		_button->addChild(pLabel1);
	}
	
}

void FigureView::clickButtonIdentify(CCObject * pSender)
{
	if(STAT_IDETIFY == _statPanel)
	{
		_statPanel = STAT_ROLE;
	}
	else
	{
		_statPanel = STAT_IDETIFY;
	}
	//GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_TRAIN, 0 );
	IdentifyView * pIdentifyView = ViewManager::getInstance()->_pIdentifyView;
	if (!pIdentifyView)
	{
		pIdentifyView = new IdentifyView();
		pIdentifyView->init();
		ViewManager::getInstance()->_pIdentifyView = pIdentifyView;
	}	
	pIdentifyView->setisPop(!pIdentifyView->getisPop());
	changePopContainerSize();

	if (_buttonAtr)
	{
		_buttonAtr->setIsEnabled(true);
	}
	if (_buttonPeiyang)
	{
		_buttonPeiyang->setIsEnabled(true);
	}
	if (_buttonJianding)
	{
		_buttonJianding->setIsEnabled(false);
	}
}

void FigureView::clickButtonTrain(CCObject* pSender)
{
	//enableButton(TAG_BTN_PEIYANG , true);
	//enableButton(TAG_BTN_XUNLIAN , false);
	//TestNewhand *pNewhand = new TestNewhand("evt",0,0);
	//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, pNewhand);

	if(STAT_TRAIN == _statPanel)
	{
		_statPanel = STAT_ROLE;
	}
	else if(STAT_PEIYANG == _statPanel)
	{
		if(!_peiyangV)
		{
			_peiyangV = ViewManager::getInstance()->_peiyangView;
		}
		_peiyangV->setisPop(!_peiyangV->getisPop());
		
		_statPanel = STAT_TRAIN;
	}
	else
	{
		_statPanel = STAT_TRAIN;
	}
	GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_TRAIN, 0 );
	changePopContainerSize();

	g_pFigureScrollView->moveToPageImmediately(2);
	// train board
	TrainView * pTrainView = ViewManager::getInstance()->trainView;
	if ( pTrainView && pTrainView->getisPop() )
	{
		pTrainView->roleItemClickHandler( 1 );
	}
	if (_buttonTrain && buttonMenuTrain)
	{
		buttonMenuTrain->setIsVisible(true);
		_buttonTrain->setIsEnabled(false);
	}
	if (buttonMenuAtr)
	{
		buttonMenuAtr->setIsVisible(false);
	}
	if (buttonMenuPeiyang)
	{
		buttonMenuPeiyang->setIsVisible(false);
	}

	// by LONGHUI 20121012
	// start train button
	NewhandManager::Instance()->touchNextEvent(102); 
}

void FigureView::resetBtn()
{
	if (_buttonAtr)
	{
		_buttonAtr->setIsEnabled(false);
		buttonMenuAtr->setIsVisible(true);
	}
	if (_buttonPeiyang)
	{
		_buttonPeiyang->setIsEnabled(true);
		buttonMenuPeiyang->setIsVisible(true);
	}
	if (_buttonTrain)
	{
		buttonMenuTrain->setIsVisible(false);
		_buttonTrain->setIsEnabled(false);
	}
}

void FigureView::clickButtonPeiyang(CCObject* pSender)
{
	//enableButton(TAG_BTN_PEIYANG , false);
	//enableButton(TAG_BTN_XUNLIAN , true);
	if (RoleManage::Instance()->roleLev() < LevLimitConst::Limit_Peiyang)
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("EOE7").c_str() , LevLimitConst::Limit_Peiyang);
		MessageInfoBox::Instance()->show(path,ccc3(233,12,25));
		return;
	}

	_peiyangV = ViewManager::getInstance()->_peiyangView;
	if (!_peiyangV)
	{
		_peiyangV = new PeiyangView();
		ViewManager::getInstance()->_peiyangView = _peiyangV;
	}
	
	_peiyangV->getPrice(0); // require price

	if(STAT_ROLE == _statPanel)
	{
		_peiyangV->loadItems(false);
		_peiyangV->setisPop(!_peiyangV->getisPop());
		//LH 20120107
		if (_peiyangV && _peiyangV->retainCount() > 2) // with touch event == 3
		{
			_peiyangV->release();
		}

		_statPanel = STAT_PEIYANG;
	}
	else if (STAT_PEIYANG == _statPanel)
	{
		_peiyangV->setisPop(!_peiyangV->getisPop());
		//LH 20120107
		/*
		if (_peiyangV && _peiyangV->retainCount() > 2) // with touch event == 3
		{
			_peiyangV->release();
		}
		*/

		_statPanel = STAT_ROLE;
	}
	else if(STAT_SKILL == _statPanel)
	{
		_peiyangV->loadItems(false);
		_peiyangV->setisPop(!_peiyangV->getisPop());
		//LH 20120107
		if (_peiyangV && _peiyangV->retainCount() > 2) // with touch event == 3
		{
			_peiyangV->release();
		}

		_statPanel = STAT_PEIYANG;
	}
	else if(STAT_TRAIN == _statPanel)
	{
		GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_TRAIN, 0 );
		_peiyangV->loadItems(false);
		_peiyangV->setisPop(!_peiyangV->getisPop());
		//LH 20120107
		if (_peiyangV && _peiyangV->retainCount() > 2) // with touch event == 3
		{
			_peiyangV->release();
		}

		_statPanel = STAT_PEIYANG;
	}
	else if(STAT_IDETIFY == _statPanel)
	{
		IdentifyView * pIdentifyView = ViewManager::getInstance()->_pIdentifyView;
		if (!pIdentifyView)
		{
			pIdentifyView = new IdentifyView();
			pIdentifyView->init();
			ViewManager::getInstance()->_pIdentifyView = pIdentifyView;
		}	
		pIdentifyView->setisPop(!pIdentifyView->getisPop());

		_peiyangV->loadItems(false);
		_peiyangV->setisPop(!_peiyangV->getisPop());
		//LH 20120107
		if (_peiyangV && _peiyangV->retainCount() > 2) // with touch event == 3
		{
			_peiyangV->release();
		}

		_statPanel = STAT_PEIYANG;
	}
	changePopContainerSize();


	if (_buttonAtr)
	{
		_buttonAtr->setIsEnabled(true);
	}
	if (_buttonPeiyang)
	{
		_buttonPeiyang->setIsEnabled(false);
	}
	if (_buttonJianding)
	{
		_buttonJianding->setIsEnabled(true);
	}
}

void FigureView::clickButtonSkill(CCObject* pSender)
{
	_skillV = ViewManager::getInstance()->_skillView;
	if (!_skillV)
	{
		_skillV = new SkillView();
		ViewManager::getInstance()->_skillView = _skillV;
	}
	if(STAT_ROLE == _statPanel)
	{
		_skillV->addSkillCellAndItem();
		_skillV->setisPop(!_skillV->getisPop());
		_statPanel = STAT_SKILL;
	}
	else if (STAT_SKILL == _statPanel)
	{
		_skillV->setisPop(!_skillV->getisPop());
		_statPanel = STAT_ROLE;
	}
	else if(STAT_PEIYANG == _statPanel)
	{
		_skillV->addSkillCellAndItem();
		_skillV->setisPop(!_skillV->getisPop());
		_statPanel = STAT_SKILL;
	}
	changePopContainerSize();
}

void FigureView::clickButtonAtt(CCObject* obj)
{
	//GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_FIGURE,	0 );
	//GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_FIGURE,	0 );
	
	if (_peiyangV && _peiyangV->getisPop())
	{
		_peiyangV->setisPop(!_peiyangV->getisPop());
	}
	
	/*
	if (ViewManager::getInstance()->figureView
		 && ViewManager::getInstance()->figureView->getisPop())
	{
		ViewManager::getInstance()->figureView->closeView();
	}
	*/
	//GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_FIGURE,	0 );
	//GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_FIGURE,	0 );

	if (_buttonAtr)
	{
		_buttonAtr->setIsEnabled(false);
	}
	if (_buttonPeiyang)
	{
		_buttonPeiyang->setIsEnabled(true);
	}
	if (_buttonJianding)
	{
		_buttonJianding->setIsEnabled(true);
	}

	_statPanel = STAT_ROLE;
	changePopContainerSize();
	g_pGlobalManage->showAllUI(false);
}

void FigureView::showEquipInfo()
{	
	//LH20120105
	if(g_pFigureScrollView)
	{
		g_pFigureScrollView->release();
		g_pFigureScrollView = 0;
	}

	if (!g_pFigureScrollView)
	{
		g_pFigureScrollView = FigureCreate::figureScrollViewWithCCRect(
			CCRectMake(0, 
			0,
			POSX(420),
			POSX(550)));
	}
	

	int role_cnt = 0; 
	//std::map<int ,PlayerInfoVo>* list =  RoleManage::Instance()->mercList(); 
	//std::map<int ,PlayerInfoVo>::iterator it = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list =  RoleManage::Instance()->mercListEx(); 
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = list->begin();
	if(list)
	{
		role_cnt += list->size(); 
	}
	for (int i = 0; i < role_cnt; i++)
	{
		RoleID[i] = it->second.figureBaseInfo.mercId;
		++it;
		g_pFigureScrollView->addLayerByTag(i);
	}
	g_pFigureScrollView->setAnchorPoint(CCPointZero);
	g_pFigureScrollView->setIsRelativeAnchorPoint(true);
	g_pFigureScrollView->setPosition(CCPointZero);
	if (__container->getChildByTag(RENDERZ_figureCreate))
	{
		__container->removeChildByTag(RENDERZ_figureCreate,true);
	}
	__container->addChild(g_pFigureScrollView);//jae note: zOrder is not tag, LH you know that~~~
	g_pFigureScrollView->release(); // LH20130107
	g_pFigureScrollView->setTag( RENDERZ_figureCreate );
	
	g_pFigureScrollView->showEquipInfo();
	g_pFigureScrollView->showSkillInfo();
	
	// add by LH 0509;add attributeLayer
	if (!_attrLayer)
	{
		_attrLayer = new AttributeLayer(m_viewSize);
		_attrLayer->setContentSize(m_viewSize);
		_attrLayer->setAnchorPoint(CCPointZero);
		_attrLayer->setIsRelativeAnchorPoint(true);
		_attrLayer->setPosition(ccp(POSX(480),0));
		_attrLayer->init();
		__container->addChild(_attrLayer, RENDERZ_figureCreate+1);		
		_attrLayer->release(); //LH20120109
	}
	_attrLayer->loadItems();
}

bool FigureView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (g_pFigureScrollView)
	{
		int page  = g_pFigureScrollView->currentScreen-1;
		CCLayer * cp = g_pFigureScrollView->getLayerByTag(page);
		EquiptmentItem * cn = (EquiptmentItem *)cp->getChildByTag(_highLightIndex);
		if(cn)
		{
			cn->setHighLight(false);
		}
	}

	//CCLog("touch begin in figure view");
	setTouchState(TouchState_0);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
	preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//The current need windowLayer focus
	{
		LayerManager::tipsLayer->setLastItemGID(NONEINT);
		return false;
	}

	if (g_pFigureScrollView/*_figureCreate*/ && g_pFigureScrollView->getIsTouchInContentLayer(touch) ) 
	{

		setTouchState(TouchState_1);
		return g_pFigureScrollView->ccTouchBegan(touch, event);
	}
	return false;
}

void FigureView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	
    CCPoint locationInView = touch->locationInView(touch->view());
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(locationInView);
    if(abs(movePoint.x - preTouchPoint.x) < 5)
    {
        return;
    }
	int page  = g_pFigureScrollView->currentScreen-1;
	CCLayer * cp = g_pFigureScrollView->getLayerByTag(page);
	EquiptmentItem * cn = (EquiptmentItem *)cp->getChildByTag(_highLightIndex);
	if(cn)
	{
		cn->setHighLight(false);
	}

	CCLog("touch move in figure view");

	show2Stunts(false);
	showSkillSelectPanel(0);

	g_pFigureScrollView->ccTouchMoved(touch, event);
	setTouchState(TouchState_3);
}

void FigureView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (_nTouchCount == 0)
	{
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(FigureView::count),this,0.03f,false);
	}

	CCPoint locationInView = touch->locationInView(touch->view());
	currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	if (getTouchState() == TouchState_1)
	{
		g_pFigureScrollView->ccTouchEnded(touch, event);
		int page  = g_pFigureScrollView->currentScreen-1;
		CCLayer * cp = g_pFigureScrollView->getLayerByTag(page);
		if (!cp)
		{
			return;
		}
		int i = 0;
		// equip
		for (i = 0;i<6;i++)
		{
			_highLightIndex = i+FigureCreate::TAG_EQUIP;
			EquiptmentItem * cn = (EquiptmentItem *)cp->getChildByTag(_highLightIndex);
			if (!cn)
			{
				continue;
			}
			CCPoint p = getScreenPos(cn);
			CCSize sz = cn->getChildByTag(0)->getContentSize();
			if (CCRect::CCRectContainsPoint(CCRectMake(p.x-sz.width/2,p.y-sz.height/2,sz.width,sz.height),currentTouchPoint))
			{
				if (_nClickIndex == -1)
				{
					_nClickIndex = i;
					++_nClickIndexCount;
				}
				else
				{
					if (_nClickIndex != i)
					{
						_nClickIndex = -1;
						_nClickIndexCount = 0;
					}
					else
					{
						++_nClickIndexCount;
					}
				}

				if (cn->_info->id != 0)
				{
					cn->setHighLight(true);
				}
				
				if (!cn->getChildByTag(2))
				{
					continue;
				}
				if (_nTouchCount <= 0) // single touch
				{
					_pCurSelectEquip = cn;
					GameDispatcher::getInstance()->addEventListener(GameDispatcher::SHOW_EQUIP_TIP, this, callfuncND_selector(FigureView::showEquipTips));	
				}
				else if (_nClickIndexCount >= 2) // multiple/double touch
				{
					// reset
					CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(FigureView::count),this);
					GameDispatcher::getInstance()->removeEventListener(GameDispatcher::SHOW_EQUIP_TIP);
					_nTouchCount = 0;
					_nClickIndexCount = 0;
					_nClickIndex = -1;

					// bag grid
					BagProxy * pBagProxy = (BagProxy *)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
					if (pBagProxy && pBagProxy->getSpaceGridNum()<=0)
					{
						Message::Instance()->show(ValuesUtil::Instance()->getString("EQU001"),ccc3(240,44,22),1);
						return;
					}
					int totalGrid = pBagProxy->_goodsNumber;
					int emptyGrid = 0;
					for (emptyGrid =0;emptyGrid<totalGrid;emptyGrid++)
					{
						if (!pBagProxy->_goodsList[emptyGrid]->id)
						{
							break;
						}
					}
					// figure id
					int figureID = getCurFigureID(g_pFigureScrollView->currentScreen-1);
					if (!figureID)
					{
						return;
					}
					// sitnum
					int sitnum = cn->getTag() - FigureCreate::TAG_EQUIP +1;

					// send
					FigureMediator *pFigureMediator = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
					if (pFigureMediator)
					{
						if (g_pFigureScrollView->currentScreen<=0)
						{
							return;
						}
						pFigureMediator->sendDownClotheRequest(figureID,sitnum,emptyGrid);
					}
				}
				break;
			}	
		}
		if (i<6)
		{
			return;
		}
		// skill
		bool isSelectAgain = false;
		for (i = 0;i<3;i++)
		{
			CCNode * cn = cp->getChildByTag(FigureCreate::TAG_SKILL+i+1);
			if (!cn)
			{
				continue;
			}
			
			CCPoint p = getScreenPos(cn);
			CCSize sz = cn->getContentSize();
			if (CCRect::CCRectContainsPoint(CCRectMake(p.x,p.y,sz.width,sz.height),currentTouchPoint))
			{	
				_isSelected = true ;

				setSkillHightLight(i + 1);

				switch(i)
				{
				case 0:
					//setSkillHightLight(1);
					isSelectAgain = true;
					_stateSkill = false;
					// show skill tips
					if (cn)
					{
						((SkillItem*)cn)->myTip->rollOverHander();
					}
					break;
				case 1:
					// show skill tips
					{
// 						int roleLev = RoleManage::Instance()->roleLev();
// 						if (roleLev >= 30)
						// 						{
						//setSkillHightLight(2);
							isSelectAgain = true;
							_stateSkill = false;
							
							// only main role
							if ( (RoleManage::Instance()->roleLev() >= 30) 
								&& g_pFigureScrollView
								&& g_pFigureScrollView->currentScreen > 0
								&& getCurFigureID(g_pFigureScrollView->currentScreen-1) == RoleManage::Instance()->accountInfo()->roleId)
							{
								_IsStuntsPop = _IsStuntsPop ? false : true;
								show2Stunts(_IsStuntsPop);
							}
							
							
//						}
							if ( /*(page!=0) &&*/ cn )
							{
								((SkillItem*)cn)->myTip->rollOverHander();
								if (g_pTipsSkillCanvas && g_pTipsSkillCanvas->m_alert)
								{
									if (g_pTipsSkillCanvas->m_alert->pMenu)
									{
										g_pTipsSkillCanvas->m_alert->pMenu->setIsVisible(false);
									}									
								}								
							}
					}
					break;
				case 2:
					// show skill select layers
					{
						//setSkillHightLight(3);
						isSelectAgain = true;

						if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Passive)
						{
							std::map<int, std::map<int, SkillNode> > * rankDic = &SkillManager::Instance()->_learnedSkillRankDic;
							std::map<int, std::map<int, SkillNode> >::iterator iter = rankDic->find(SkillType::PASSVIE);
							if(iter != rankDic->end())
							{
								std::map<int, SkillNode> * skillNode = &iter->second;
								if (!skillNode->empty())
								{
									_stateSkill = (0 == _stateSkill) ? 1:0;
									showSkillSelectPanel(_stateSkill);
								}
							}
						}
						else
						{
							char path[128] = {0};
							sprintf(path , ValuesUtil::Instance()->getString("WLC011").c_str() , LevLimitConst::Limit_Passive);
							Message::Instance()->show(path , ccc3(233,12,25) , 1);
						}						
					}
					break;
				default:
					break;
				}
			}
			else
			{
				if ((!_isSelected) && (!isSelectAgain))
				{
					setSkillHightLight(0);
				}
			}
		}
		if ((_isSelected) && (!isSelectAgain))
		{
			setSkillHightLight(0);
		}
	}
	else if (getTouchState() == TouchState_3)
	{
		setSkillHightLight(0);

		g_pFigureScrollView->ccTouchEnded(touch, event);
	}
}

void FigureView::showEquipTips(CCNode* pNode, void* data)
{
	if (!data)
	{
		return;
	}
	
	EquiptmentItem * pEquip = (EquiptmentItem *)data;
	if (LayerManager::tipsLayer->getLastItemGID() == pEquip->getTag())
	{
		LayerManager::tipsLayer->setLastItemGID(NONEINT);
	}
	else
	{
		TipHelps * th = pEquip->_eqTip;
		th->rollOverHander();
		LayerManager::tipsLayer->setLastItemGID(pEquip->getMyFocusGID());
	}
}

void FigureView::count(ccTime dt)
{
	++_nTouchCount;
	if (_nTouchCount >= 10)
	{
		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(FigureView::count),this);
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::SHOW_EQUIP_TIP,_pCurSelectEquip);
		GameDispatcher::getInstance()->removeEventListener(GameDispatcher::SHOW_EQUIP_TIP);
		_nTouchCount = 0;
		_nClickIndexCount = 0;
	}
}

int FigureView::getCurFigureID(int index)
{
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	int page = 0;
	for (;iter != list->end();iter++)
	{
		if (index == page)
		{
			return iter->first.id;
		}
		++page;
	}
	/*
	std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	std::map<int ,PlayerInfoVo>::iterator iter = list->begin();
	int page = 0;
	for (;iter != list->end();iter++)
	{
		if (index == page)
		{
			return iter->first;
		}
		++page;
	}
	*/
	return 0;
}

void FigureView::closeView()
{
	removeAllChildrenWithCleanup(true);
}

void FigureView::showSkillInfo()
{
	if (!g_pFigureScrollView)
	{
		return;
	}
	g_pFigureScrollView->showSkillInfo();
}

void FigureView::showSkillSelectPanel(int _state)
{
	if (_state)
	{
		if (_IsStuntsPop)
		{
			show2Stunts(!_IsStuntsPop);
		}
	}

	if (this->getChildByTag(TAG_SKILL_POPLAYER))
	{
		this->removeChildByTag(TAG_SKILL_POPLAYER,true);
	}

	if (!_state)
	{
		return;
	}

	CCUIBackground * _skillbg = new CCUIBackground();
	CCSize size = CCSIZE_SKILL_SCROLLVIEW;
	_skillbg->initWithSpriteFrame("ui.png",CCPointZero,CCPointZero,size);
	_skillbg->setIsRelativeAnchorPoint(true);
	_skillbg->setAnchorPoint(CCPointZero);
	CCSize wsz = CCDirector::sharedDirector()->getWinSize();
	if (!_skillPopLayer)
	{
		_skillPopLayer = new SkillLayer();
		if (!_skillPopLayer || !_skillPopLayer->init())
		{
			return;
		}
		_skillPopLayer->setAnchorPoint(CCPointZero);
		_skillPopLayer->setIsRelativeAnchorPoint(true);
		_skillPopLayer->setContentSize(size);
		CCPoint pos = ccp(preTouchPoint.x-size.width,preTouchPoint.y);
		_skillPopLayer->setPosition(pos);
		_skillPopLayer->setContentSize(_skillbg->getContentSize());
		_skillPopLayer->setIsTouchEnabled(true);
	}
	if (!this->getChildByTag(TAG_SKILL_POPLAYER))
	{
		this->addChild(_skillPopLayer,7,TAG_SKILL_POPLAYER);
	}
	if (!_skillPopLayer->getChildByTag(1))
	{
		_skillPopLayer->addChild(_skillbg,0,1);
	}
	if (!_skillPopLayer->getChildByTag(2))
	{
		_skillPopLayer->addSkillScrollView();
	}
	_skillPopLayer->loadSkillItems();
	//Doyang 20120712
	_skillbg->release();

	_stateSkill = _state;

	// by LONGHUI 20121014
	// new hand
	if (_state)
	{
		NewhandManager::Instance()->touchNextEvent(105);
	}	
}

void FigureView::show2Stunts(bool isStuntsPop)
{
	if (isStuntsPop)
	{
		if (_stateSkill)
		{
			showSkillSelectPanel(!_stateSkill);
		}
	}

	
	if (this->getChildByTag(TAG_STUNT_POPLAYER))
	{
		this->removeChildByTag(TAG_STUNT_POPLAYER,true);
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	}

	if (!isStuntsPop)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
		return;
	}

	StuntsLayer * pStuntsLayer = new StuntsLayer();
	if (pStuntsLayer && pStuntsLayer->init())
	{
		pStuntsLayer->setTag(TAG_STUNT_POPLAYER);
		CCPoint pos = ccp(preTouchPoint.x-POSX(50+150),preTouchPoint.y +POSX(70));
		pStuntsLayer->setPosition(pos);
		this->addChild(pStuntsLayer);
		pStuntsLayer->release();
	}

	_IsStuntsPop = isStuntsPop;
}

void FigureView::changeSkill(int figure, int rank, UpGradeInfo info)
{

}
void FigureView::updateEquipInfo(int fid, int grid)
{
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	int page = 0;
	for (iter ; iter != list->end(); iter++ )
	{
		if (fid == iter->first.id)
		{
			break;
		}
		++page;
	}
	//int nSitGrid = grid; 
	if (!g_pFigureScrollView)
	{
		return;
	}

	g_pFigureScrollView->showEquipInfo( fid, page );
}

void FigureView::updateEquipTip(int fid, int grid)
{

}

int FigureView::currentId()
{
	return _currentId;
}


void FigureView::currentId(int value)
{
	_currentId = value;
}

int32 FigureView::getTouchState()
{
	return _TouchState;
}

void FigureView::setTouchState(int32 var)
{
	_TouchState = var;
}


void FigureView::updateFigureInfo(int fid, WashVo* washValue)
{
	if(_currentId != fid) return;
	if (!g_pFigureScrollView)
	{
		return;
	}
	g_pFigureScrollView->showEquipInfo();

	PeiyangView * pv = ViewManager::getInstance()->_peiyangView;
	if (pv)
	{
		pv->loadItems(true);
	}
} 

void FigureView::step(CCTime dt)
{

}

void FigureView::changePopContainerSize()
{
	int state;
	switch(_statPanel)
	{
	case STAT_ROLE:
		state = 0;
		break;

	case STAT_PEIYANG:
		state = 1;
		break;

	case STAT_SKILL:
		state = 1;
		break;

	case STAT_TRAIN:
		state = 1;
		break;

	case STAT_IDETIFY:
		state = 1;
		break;

	default:
		state = 0;
		break;
	}
	
	FigureMainView *pParent = (FigureMainView *) this->getParent();
	if(pParent)
	{
		pParent->changeStage(state);
	}
}

void FigureView::enableButton(int tag ,bool var)
{
	if (__container )
	{
		if (__container->getChildByTag(tag))
		{
			CCMenuItemImage *_buttonImg = (CCMenuItemImage *)__container->getChildByTag(tag)->getChildByTag(TAG_BTN_IMG);
			if (_buttonImg)
			{
				_buttonImg->setIsEnabled(var);
			}
		}
	}
}

void FigureView::clickButtonEQ(CCObject* pSender)//kevin0830
{
	DropMediator * pDropMediator = (DropMediator *)g_pFacade->retrieveMediator(AppFacade_EQ_Mediator);
	if (pDropMediator)
	{
		pDropMediator->openDropCheckView();
	}
}

CCNode * FigureView::getNewHandItem( int id )
{
	if(id == 98) // train
	{
		if (__container && __container->getChildByTag(FigureView::TAG_BTN_XUNLIAN))
		{
			return __container->getChildByTag(FigureView::TAG_BTN_XUNLIAN)->getChildByTag(FigureView::TAG_BTN_IMG);
		}		
	}
	else if (id == 97) // passive skill
	{
		if (g_pFigureScrollView && g_pFigureScrollView->getLayerByTag(0))
		{
			return g_pFigureScrollView->getLayerByTag(0)->getChildByTag(FigureCreate::TAG_SKILL + 3);
		}
	}
	else if (id == 971) // skill item
	{
		if (g_pSkillScrollView
			&& g_pSkillScrollView->getLayerByTag(0))
		{
			return g_pSkillScrollView->getLayerByTag(0)->getChildByTag(0);
		}
	}
	else if (id == 980) // start train button
	{
		if (ViewManager::getInstance()->trainView 
			&& ViewManager::getInstance()->trainView->_btnStart)
		{
			return ViewManager::getInstance()->trainView->_btnStart->getChildByTag(101);
		}
	}
	else if (id == 981) // tufei button
	{
		if (ViewManager::getInstance()->trainView 
			&& ViewManager::getInstance()->trainView->_btnGold)
		{
			return ViewManager::getInstance()->trainView->_btnGold->getChildByTag(101);
		}
	}
	else if (id == 200) // peiyang panel button
	{
		return buttonMenuPeiyang;
	}
	else if (id == 201) // do peiyang button
	{
		if (ViewManager::getInstance()->_peiyangView)
		{
			return ViewManager::getInstance()->_peiyangView->_washButton;
		}
	}
	else if (id == 202) // save peiyang button
	{
		if (ViewManager::getInstance()->_peiyangView)
		{
			return ViewManager::getInstance()->_peiyangView->_acceptButton;
		}
	}
	else if (id == 1000) // close figure view button
	{
		return g_pPopManage->getBtnX();
	}
	return 0;
}

void FigureView::setSkillHightLight(int index)
{
	if (g_pFigureScrollView)
	{
		g_pFigureScrollView->setSkillHightLight(index);
	}
}

void FigureView::showButtonByTag(int tag , bool var)
{
	if (!__container)
	{
		return;
	}
	CCNode * pNode = __container->getChildByTag(tag);
	if (pNode)
	{
		pNode->setIsVisible(var);
	}
	else
	{
		switch(tag)
		{
		case TAG_BTN_PEIYANG:
			{
				_buttonPeiyang = CCMenuItemImage::itemFromNormalSprite(
					CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
					CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
					CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
					this, 
					menu_selector(FigureView::clickButtonPeiyang));
				_buttonPeiyang->setTag(TAG_BTN_IMG);
				buttonMenuPeiyang = CCMenu::menuWithItems(_buttonPeiyang, NULL);
				buttonMenuPeiyang->setTag(TAG_BTN_PEIYANG);
				buttonMenuPeiyang->setTouchLayer( TLE::WindowLayer_Common_btn );
				buttonMenuPeiyang->setPosition(ccp(POSX(176+100), POSX(588)));
				__container->addChild(buttonMenuPeiyang, RENDERZ_button);
				CCLabelTTF *pLabel1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("peiyang").c_str(),
					CCSizeMake(_buttonPeiyang->getContentSize().width,_buttonPeiyang->getContentSize().height),
					CCTextAlignmentCenter,
					g_sSimHeiFont,
					POSX(20));
				pLabel1->setColor(ccc3(255,240,0));
				pLabel1->setPosition( ccp(_csBt.width/ 2.0f,_csBt.height/2) );
				_buttonPeiyang->addChild(pLabel1);
				_buttonPeiyang->setIsVisible(var);
			}
			break;
		default:
			break;
		}
	}
	
	
	
}
