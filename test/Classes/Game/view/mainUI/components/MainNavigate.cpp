#include "MainNavigate.h"
#include "MainNavigateX.h"
#include "MainNavigateY.h"
#include "control/AppFacade.h"
#include "view/backpack/BagMediator.h"
#include "view/figure/FigureMediator.h"
#include "view/crystal/CrystalMediator.h"
#include "view/arena/ArenaMediator.h"
#include "../MainUIMediator.h"
#include "mvc/Facade.h"
#include "events/GameDispatcher.h"
#include "manager/GlobalManage.h"
#include "view/skill/UpSkillMediator.h"
#include "view/formation/FormationMediator.h"
#include "manager/PopEventName.h"
#include "manager/ViewManager.h"
#include "RoleUI.h"
#include "manager/LayerManager.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "NewEAlert.h"
#include "utils/ValuesUtil.h"
#include "view/setting/components/SettingView.h"
#include "model/newhand/NewhandManager.h"
#include "view/newhand/components/NewHandView.h"
#include "manager/sound/SoundManager.h"
#include "view/chat/components/ChatView.h"
#include "view/chat/ChatMediator.h"
#include "control/AppFacade.h"
#include "model/chat/ChannelType.h"
#include "view/chat/components/ChatMsgManager.h"
#include "socket/command/c32/CCMD32C.h"
#include "socket/network/GameServerSocket.h"
#include "model/scene/SceneProxy.h"
#include "model/dungeonEntrys/DungeonEntrysManage.h"
#include "socket/command/c11/CCMD116.h"
#include "view/mail/MailMediator.h"
#include "view/newhand/components/NewHandHelpView.h"
#include "view/guild/components/GuildView.h"
#include "model/player/RoleManage.h"
#include "model/scene/SceneManager.h"
#include "manager/SystemManage.h"
#include "VScrollUI.h"
#include "view/task/TaskMediator.h"
#include "model/scene/vo/SceneType.h"
#include "manager/LevLimitConst.h"
#include "view/zx/ZXMediator.h"

const float ACTIONTIME = 0.2f;
const int TAG_OUT_ITEM = 1001;
//const int TAG_OUT_ITEM_LABEL = 1002;
const int TAG_MAIL = 1021;
const int TAG_MAIL_TEXT = 1022;
const int TAG_CD = 1023;
const int TAG_SMALL_MAP = 1024;
const int TAG_MAIL_LIGHT = 1025;
const int TAG_NEWHAND_HELP = 1026;
const int TAG_HIDEPLAYER_MENU = 1029;
const int TAG_SMALL_MAP_BG = 1030;
MainNavigate::MainNavigate()
{
	_mainNavigateX = 0;
	_mainNavigateY = 0;
	_isMainBtnOpen = false;
	_isCrystalOpen = false;
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_btn_class.plist");
}

MainNavigate::~MainNavigate()
{}

bool MainNavigate::init()
{
	if (!CCLayer::init())
		return false;
	
	//��Ļ���?	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//��Բ�δ򿪰�ť
	CCMenu* pMainButtonMenu = new CCMenu();
	pMainButtonMenu->init();
	pMainButtonMenu->setPosition( CCPointZero );
	this->addChild(pMainButtonMenu, MainNavigateZ_menubtn, MainNavigateTAG_menubtn);
	pMainButtonMenu->release();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_btn.plist");
	CCSprite *pNormalMainBtnSprite = CCSprite::spriteWithSpriteFrameName("mainUI/main_btn_0.png");
	CCSprite *pPressedMainBtnSprite = CCSprite::spriteWithSpriteFrameName("mainUI/main_btn_1.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/mainUI/res_mainui_btn.plist");
	if(!pNormalMainBtnSprite || !pPressedMainBtnSprite)
	{
		return false;
	}
	CCMenuItemSprite *mainBtn = CCMenuItemSprite::itemFromNormalSprite(
		pNormalMainBtnSprite,
		pPressedMainBtnSprite,
		this, 
		menu_selector(MainNavigate::handleMainBtn));

	mainBtn->setPosition(/*ccp(POSX(winSize.width - mainBtn->getContentSize().width/2+6), POSX(mainBtn->getContentSize().height/2-6))*/
		POS(ccp(840, 0), ScaleUtil::BOTTOM_RIGHT));
	mainBtn->setAnchorPoint(CCPointZero);
	pMainButtonMenu->addChild(mainBtn, 0);
	//mainBtn->release();
	pMainButtonMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);

	
	//���ؼ�Բ�δ򿪰�ť�ϵ�Xͼ��
	getBtnX();
	//X���?	if (!_mainNavigateX)
	{
		_mainNavigateX = new MainNavigateX();
		//_mainNavigateX->setPosition(ccp(0,0));
		this->addChild(_mainNavigateX, MainNavigateZ_mainNavigateX, MainNavigateTAG_mainNavigateX);
	}

	//Y Navigation
	if (!_mainNavigateY)
	{
		_mainNavigateY = new MainNavigateY();
		//_mainNavigateY->setPosition(ccp(0,0));
		this->addChild(_mainNavigateY, MainNavigateZ_mainNavigateY, MainNavigateTAG_mainNavigateY);
	}

	//��ԭʼBUTTON
	configUI();
	//����Ϊ�ر�״̬
	//setisMainBtnOpen(false);

	// small map
	/*
	{
		CCSprite * pBackSprite = new CCSprite();
		pBackSprite->initWithSpriteFrameName("mainui2/smallcircle.png");
		pBackSprite->setPosition(POS(ccp(892, 440 + 20), ScaleUtil::CENTER_RIGHT));
		pBackSprite->setOpacity(255);
		this->addChild(pBackSprite , -1 ,TAG_SMALL_MAP_BG);
		pBackSprite->release();	

		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("mapbtn/map1.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("mapbtn/map2.png");
		CCMenuItemSprite *pMapItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(MainNavigate::popUIHandlerMap) );
		if(!pMapItem)
			return false;

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		pMapItem->setPosition(POS(ccp(892, 440 + 20), ScaleUtil::CENTER_RIGHT));

		CCMenu* pMapMenu = CCMenu::menuWithItem(pMapItem);
		if(pMapMenu)
		{
			pMapMenu->setPosition(CCPointZero);
			pMapMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
			this->addChild(pMapMenu, 0, TAG_SMALL_MAP);
		}
	}
	*/
	
	//

	// out map
	// Doyang 20120723
	
	{
		CCSprite *pOutNormalSprite = CCSprite::spriteWithSpriteFrameName("mapbtn/exitcopy1.png");
		CCSprite *pOutPressedSprite = CCSprite::spriteWithSpriteFrameName("mapbtn/exitcopy2.png");
		pOutNormalSprite->setScale(0.8);
		pOutPressedSprite->setScale(0.8);
		if(!pOutNormalSprite || !pOutPressedSprite)
		{
			return false;
		}
		CCMenuItemSprite *pOutItemImage = CCMenuItemSprite::itemFromNormalSprite(
			pOutNormalSprite,
			pOutPressedSprite,
			this,
			menu_selector(MainNavigate::outOfMap) );
		if(!pOutItemImage)
			return false;
		pOutItemImage->setTag(1001);
		pOutItemImage->setPosition(POS(ccp(900, 370 + 75), ScaleUtil::CENTER_RIGHT));
		CCMenu* pOutMenu = CCMenu::menuWithItem(pOutItemImage);
		pOutMenu->setPosition( CCPointZero );
		pOutMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
		this->addChild(pOutMenu, 0, TAG_OUT_ITEM);
		pOutMenu->setIsVisible(false);

		/*
	// Doyang 20120723
	
	CCSprite *pOutNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pOutPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pOutNormalSprite || !pOutPressedSprite)
	{
		return false;
	}
	CCMenuItemSprite *pOutItemImage = CCMenuItemSprite::itemFromNormalSprite(
		pOutNormalSprite,
		pOutPressedSprite,
		this,
		menu_selector(MainNavigate::outOfMap) );
	if(!pOutItemImage)
		return false;
	pOutItemImage->setTag(1001);
	pOutItemImage->setPosition(POS(ccp(64, 370), ScaleUtil::CENTER_LEFT));
	CCMenu* pOutMenu = CCMenu::menuWithItem(pOutItemImage);
	pOutMenu->setPosition( CCPointZero );
	pOutMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
	this->addChild(pOutMenu, 0, TAG_OUT_ITEM);
	pOutMenu->setIsVisible(false);
	*/
		CCSprite * pBackSprite = new CCSprite();
		pBackSprite->initWithSpriteFrameName("mainui2/smallcircle.png");
		CCSize size = pOutItemImage->getContentSize();
		pBackSprite->setPosition(ccp( 0.8 *size.width/2 , 0.8 *size.height/2 ));
		pBackSprite->setOpacity(255);
		pOutItemImage->addChild(pBackSprite , -1);

		CCUIBackground * pMapNameBack = new CCUIBackground();
		bool var = pMapNameBack->initWithSpriteFrame("popuibg/bg1.png" , CCPointZero , CCPointZero ,CCSizeMake(POSX(200), POSX(4)) , 255);
		if (var)
		{
			CCSize size = CCDirector::sharedDirector()->getWinSizeInPixels();
			pMapNameBack->setPosition(ccp(POSX(-500) , POSX((260.0f - 75) * size.height/640)));
			pOutItemImage->addChild(pMapNameBack, 0 ,1001);
			pMapNameBack->release();
		}

		SceneVo* pSceneVo = SceneManager::Instance()->getSceneDic(RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId); // map name
		CCLabelTTF *pCopyMapName = CCLabelTTF::labelWithString(pSceneVo->name.c_str(),
			CCSizeMake(POSX(180), POSX(26)),
			CCTextAlignmentCenter,
			"",
			POSX(24));
		pCopyMapName->setPosition(ccp(POSX(100) , POSX(29)));
		pCopyMapName->setColor(ccc3(12,233,25));
		pCopyMapName->setTag(1001);
		pMapNameBack->addChild(pCopyMapName, 1 ,1001);
	}
	
//	_mainNavigateX->runAction(cocos2d::CCMoveTo::actionWithDuration(2.0, ccp(1024, 0)));
	_mainNavigateX->disappear();
	_mainNavigateY->disappear();

	//this->setIsTouchEnabled (true);

	//��������
    
    /*kevink */
	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (!chatview)
	{		
		chatview = new ChatView();
		chatview->init();
		chatview->setPosition(ccp(0, 0));
		LayerManager::intervalLayer->addChild(chatview, IntervalLayer::IntervalLayerZ_chatView, IntervalLayer::IntervalLayerTAG_chatView);	
		chatview->release();

		//
		ChatInfo msgInfo = ChatInfo();
		msgInfo.channel = ChannelType::ALL;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        msgInfo.content = ValuesUtil::Instance()->getString("CHT0531");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        msgInfo.content = ValuesUtil::Instance()->getString("CHT0532");
#else
        msgInfo.content = ValuesUtil::Instance()->getString("CHT0531");
#endif

		ChatMsgManager::Instance()->addMessage(&msgInfo);
		chatview->systemTip(&msgInfo);
	}

	// �ʼ� LH
	CCLabelTTF * pNewMailText = new CCLabelTTF();
	pNewMailText->initWithString("",CCSizeMake(POSX(60),POSX(40)),CCTextAlignmentCenter,"Arial",POSX(28));
	pNewMailText->setPosition(POS(ccp(30, 370), ScaleUtil::CENTER_LEFT));
	pNewMailText->setColor(ccc3(255,0,0));
	pNewMailText->setIsVisible(false);
	this->addChild(pNewMailText,2,TAG_MAIL_TEXT);
	pNewMailText->release();
	ViewManager::getInstance()->_mailText = pNewMailText;	

	CCSprite *pMailNormalSprite = CCSprite::spriteWithSpriteFrameName("mail/icon_normal.png");
	CCSprite *pMailPressedSprite = CCSprite::spriteWithSpriteFrameName("mail/icon_pressed.png");
	CCMenuItemSprite *pMailItemSprtie = CCMenuItemSprite::itemFromNormalSprite(
		pMailNormalSprite,
		pMailPressedSprite,
		this,
		menu_selector(MainNavigate::popUIHandlerMail));
	CCMenu * pMailMenu = CCMenu::menuWithItem(pMailItemSprtie);
	ViewManager::getInstance()->_mailButton = pMailMenu;
	pMailMenu->setPosition(POS(ccp(30, 370), ScaleUtil::CENTER_LEFT));
	pMailMenu->setIsVisible(false);
	this->addChild(pMailMenu,0,TAG_MAIL);
	//pMenuSprite->release();

	CCSprite * pLightSprite = new CCSprite();
	pLightSprite->initWithSpriteFrameName("mail/icon_pressed.png");
	pLightSprite->setPosition(POS(ccp(30, 370), ScaleUtil::CENTER_LEFT));
	pLightSprite->setIsVisible(false);
	this->addChild(pLightSprite,1,TAG_MAIL_LIGHT);
	pLightSprite->release();
	ViewManager::getInstance()->_mailLight = pLightSprite;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->updateMailText(pMailMediator->_unreadNum);
	}

	//New Hand Help // LH
	/*
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/newhand/res_help_ic.plist");
	CCSprite *pNormalHelpSprite = CCSprite::spriteWithSpriteFrameName("newhand/ic_help_normal.png");
	CCSprite *pPressedHelpSprite = CCSprite::spriteWithSpriteFrameName("newhand/ic_help_pressed.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/newhand/res_help_ic.plist");
	if(!pNormalHelpSprite || !pPressedHelpSprite)
	{
		return false;
	}
	pNormalHelpSprite->setTag(101);
	pPressedHelpSprite->setTag(102);
	CCMenuItemSprite *pNewHandHlepSprtie = CCMenuItemSprite::itemFromNormalSprite(
		pNormalHelpSprite,
		pPressedHelpSprite,
		this,
		menu_selector(MainNavigate::popUIHandlerHelp));
//	pNewHandHlepSprtie->setScale(0.2f);
	CCMenu * pHlepMenu = CCMenu::menuWithItem(pNewHandHlepSprtie);
	ViewManager::getInstance()->_helpButton = pHlepMenu;
	pHlepMenu->setPosition(POS(ccp(920, 330), ScaleUtil::CENTER_RIGHT));
	this->addChild(pHlepMenu,0,TAG_NEWHAND_HELP);


	if (RoleManage::Instance()->roleInfo()->playerBaseInfo._lev >= 31)
	{
		pHlepMenu->setIsVisible(false);
	}
	*/

	// hide other players button
	CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
	CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
	CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
	if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
	{
		return false;
	}
	CCMenuItemSprite *pHideOtherPlayersImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalNewSprite,
		pPressedNewSprite,
		pSelectedNewSprite,
		this,
		menu_selector(MainNavigate::onHideOtherPlayers));
	pHideOtherPlayersImg->setTag(1001);
	pHideOtherPlayersImg->setScaleX(1.0);
	CCMenu * pHidePlayersMenu = CCMenu::menuWithItem(pHideOtherPlayersImg);
	pHidePlayersMenu->setPosition(POS(ccp(900,470), ScaleUtil::CENTER_RIGHT));
	this->addChild(pHidePlayersMenu,0,TAG_HIDEPLAYER_MENU);
	pHidePlayersMenu->setIsVisible(false); // not used yet

	CCSize size = pHideOtherPlayersImg->getContentSize();
	CCLabelTTF * pHideText = new CCLabelTTF();
	pHideText->initWithString(ValuesUtil::Instance()->getString("WLC004").c_str(),CCSizeMake(POSX(120),POSX(30)),CCTextAlignmentCenter,"Arial",POSX(20));
	pHideText->setColor(ccc3(255,233,23));
	pHideText->setPosition(ccp(size.width/2 , size.height/2));
	pHideOtherPlayersImg->addChild(pHideText,2,1001);
	pHideText->release();

	// V scroll view
	VScrollUI * pVScrollUI = new VScrollUI();
	pVScrollUI->init();
	this->addChild(pVScrollUI , 0);
	ViewManager::getInstance()->_pVScrollUI = pVScrollUI;

	return true;
}

void MainNavigate::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::SceneUILayer+1, true);
}

bool MainNavigate::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("TLE::SceneUILayer+1");

	CCMenu* pMainButtonMenu = (CCMenu*)this->getChildByTag(MainNavigateTAG_menubtn);
	if (pMainButtonMenu)
	{
		return pMainButtonMenu->kkTouchBegan(touch, event);
		//return true;
	}
	
	return false;
}

void MainNavigate::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCMenu* pMainButtonMenu = (CCMenu*)this->getChildByTag(MainNavigateTAG_menubtn);
	if (pMainButtonMenu)
		pMainButtonMenu->kkTouchEnded(touch, event);	
}

void MainNavigate::resize()
{
	this->setContentSize(CCSizeMake(0, 0));
}

void MainNavigate::configUI()
{
	int nLev = RoleManage::Instance()->roleLev();
	//��X�����Ӱ�ť
	//1��ɫ

	_mainNavigateX->addButton(1, 0, this, menu_selector(MainNavigate::popUIHandler1));//��ɫ
	//2����
	_mainNavigateX->addButton(2, 0, this, menu_selector(MainNavigate::popUIHandler2));//����

	if (nLev >= LevLimitConst::Limit_Guild)
	{
		_mainNavigateX->addButton(7, 0, this, menu_selector(MainNavigate::popUIHandler7));//����kevin0905 //GUILD
	}
	

	if (nLev >= LevLimitConst::Limit_UpFormation)
	{
		_mainNavigateX->addButton(4, 0, this, menu_selector(MainNavigate::popUIHandler4));
	}
	

	//8ˮ��
	//_mainNavigateX->addButton(8, 0, this, menu_selector(MainNavigate::popUIHandler8));//ˮ��
	//_mainNavigateX->addButton(8, 0, this, menu_selector(MainNavigate::popUIHandlerArena));//������
			//3ǿ��
	//_mainNavigateX->addButton(3, 0, this, menu_selector(MainNavigate::popUIHandler3));
			//4��ϰ
	//_mainNavigateX->addButton(4, 0, this, menu_selector(MainNavigate::popUIHandler4));
			//5����//addButton(5, 0);//����	����Ҫ�ˣ��?ó�������Ļ����?
			//6����
	//_mainNavigateX->addButton(6, 0, this, menu_selector(MainNavigate::popUIHandler6));
			//7����
		
			//9����
	//_mainNavigateX->addButton(9, 0, this, menu_selector(MainNavigate::popUIHandler9));
			//10ѵw
	
	if (nLev >= LevLimitConst::Limit_Train)
	{
		//_mainNavigateX->addButton(10, 0, this, menu_selector(MainNavigate::popUIHandler10));
	}

	//_mainNavigateX->addButton(11, 0, this, menu_selector(MainNavigate::popUIHandler11)); // task

	if (nLev >= LevLimitConst::Limit_Mail)
	{
		_mainNavigateX->addButton(12, 0, this, menu_selector(MainNavigate::popUIHandlerMail));// mail
	}

	if (nLev >= LevLimitConst::Limit_Zhanxing)
	{
		_mainNavigateX->addButton(13, 0, this, menu_selector(MainNavigate::popUIHandler13));// zhanxing
	}

	//��Y�����Ӱ�ť
	//_mainNavigateY->addButton(1, 0, this, menu_selector(MainNavigate::popUIHandlerY1));//ziyuantian
	_mainNavigateY->addButton(3, 0, this, menu_selector(MainNavigate::popUIHandlerY3));// setting
	//_mainNavigateY->addButton(5, 0, this, menu_selector(MainNavigate::popUIHandlerY5));// mail
	_mainNavigateY->addButton(4, 0, this, menu_selector(MainNavigate::popUIHandlerY4));// activity
	//_mainNavigateY->addButton(6, 0, this, menu_selector(MainNavigate::popUIHandlerY6));// help
	_mainNavigateY->addButton(7, 0, this, menu_selector(MainNavigate::popUIHandlerMap));// town map
	_mainNavigateY->addButton(2, 0, this, menu_selector(MainNavigate::popUIHandlerY2));//world map
}

void MainNavigate::addButton(int32 type, int32 sitNum, bool isTween)
{

	// Close.
	if(getisMainBtnOpen())
	{
		setisMainBtnOpen(false);
	}
	// 20120621
	// Doyang.
	if(type >= 1 && type <= 15)
	{
		NewhandManager::Instance()->setNavigateType(NewhandManager::Navigate_BottomMain);

		if(!_mainNavigateX)
			return;

		CCSprite *pFlySprite = NULL;
		switch(type)
		{
		case 1:
			{
				
			}
			break;
		case 2:
			break;
		case 3:
			//3ǿ��
			_mainNavigateX->addButton(3, 0, this, menu_selector(MainNavigate::popUIHandler3));
			break;
		case 4:
			//4��ϰ
			_mainNavigateX->addButton(4, 0, this, menu_selector(MainNavigate::popUIHandler4));
			break;
		case 5:
			break;
		case 6:
			//6����
			_mainNavigateX->addButton(6, 0, this, menu_selector(MainNavigate::popUIHandler6));
			break;
		case 7:
			//
			_mainNavigateX->addButton(7, 0, this, menu_selector(MainNavigate::popUIHandler7));
			break;
		case 8:
			//8ˮ��
			_mainNavigateX->addButton(8, 0, this, menu_selector(MainNavigate::popUIHandler8));
			break;
		case 9:
			//9����
			_mainNavigateX->addButton(9, 0, this, menu_selector(MainNavigate::popUIHandler9));
			break;
		case 10:
			//10ѵw
			_mainNavigateX->addButton(10, 0, this, menu_selector(MainNavigate::popUIHandler10));
			break;
		case 11:
			{
				_mainNavigateX->addButton(11, 0, this, menu_selector(MainNavigate::popUIHandler11));
			}
			break;
		case 13:
			{
				_mainNavigateX->addButton(13, 0, this, menu_selector(MainNavigate::popUIHandler13));
			}
			break;
		default:
			break;
		}

		if(isTween)
		{
			char imagePath[100];
			sprintf(imagePath, "mainUI/mn_btn%d_normal.png", type);
			pFlySprite = CCSprite::spriteWithSpriteFrameName(imagePath);
			if(pFlySprite && LayerManager::newhandLayer)
			{
				// GoGoGo...
				pFlySprite->setPosition(POS(ccp(480, 320), ScaleUtil::CENTER));
				LayerManager::newhandLayer->addChild(pFlySprite, 0, 1001);

				CCFiniteTimeAction *pFlyAction = CCMoveTo::actionWithDuration(1,
					POS(ccp(900, 60), ScaleUtil::BOTTOM_RIGHT));
				CCFiniteTimeAction *pAlphaAction = CCFadeOut::actionWithDuration(0.5);
				int *p = new int;
				*p = type;
				CCCallFuncND *pCompleteFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(MainNavigate::onCompleteButtonFly), p);
				CCAction *pAction = CCSequence::actions(pFlyAction,
					pAlphaAction,
					pCompleteFunc,
					NULL);
				pFlySprite->runAction(pAction);
			}

		}

		if(type == 8){//ˮ����ť���ֺ�
			_isCrystalOpen = true;
		}
	}

	// LH20121102
	
	if(isTween)
	{
		VScrollUI * pVScroll = ViewManager::getInstance()->_pVScrollUI;
		if (!pVScroll)
		{
			return;
		}
		if( type >= 20 && type <  40)
		{
			NewhandManager::Instance()->setNavigateType(NewhandManager::Navigate_LeftVscroll);

			pVScroll->setListCount(pVScroll->getListCount() + type - 20 + 1);
			pVScroll->resetListView();

			std::string szPath = NewhandManager::Instance()->getImagePathByButtonId(type);
			CCSprite * pFlySprite = CCSprite::spriteWithSpriteFrameName(szPath.c_str());
			if(pFlySprite && LayerManager::newhandLayer)
			{
				// GoGoGo...
				pFlySprite->setPosition(POS(ccp(480, 320), ScaleUtil::CENTER));
				LayerManager::newhandLayer->addChild(pFlySprite, 0, 1001);

#if CC_NEW_VSCROLLUI_OPEN
				CCPoint pos = pVScroll->getNewHandItemPos(type - 20);
#else
				CCPoint pos = pVScroll->getNewHandItemPos(type - 20);
#endif

				CCFiniteTimeAction *pFlyAction = CCMoveTo::actionWithDuration(1.2,
					/*POS(ccp(900, 60), ScaleUtil::BOTTOM_RIGHT)*/pos);
				CCFiniteTimeAction *pAlphaAction = CCFadeOut::actionWithDuration(0.6);
				int *p = new int;
				*p = type;
				CCCallFuncND *pCompleteFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(MainNavigate::onCompleteButtonFlyForVscroll), p);
				CCAction *pAction = CCSequence::actions(pFlyAction,
					pCompleteFunc,
					pAlphaAction,
					NULL);
				pFlySprite->runAction(pAction);

			}
		}
	}
	
}

SpriteNode* MainNavigate::getBtnX()
{
	SpriteNode* pBtnX = 0;
	pBtnX = (SpriteNode*)this->getChildByTag(MainNavigateTAG_menubtnX);
	if (!pBtnX)
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		pBtnX = new SpriteNode();

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_btn_x.plist");
		pBtnX->initWithSpriteFrameName("mainUI/main_btn_2.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/mainUI/res_mainui_btn_x.plist");
		pBtnX->setAnchorPoint(ccp(0.5, 0.5));
		pBtnX->setPosition(/*ccp(POSX(winSize.width - pBtnX->getTexture()->getContentSize().width/2 - 21), POSX(pBtnX->getTexture()->getContentSize().height/2+18))*/
			POS(ccp(900, 60), ScaleUtil::BOTTOM_RIGHT));
		this->addChild(pBtnX, MainNavigateZ_menubtnX, MainNavigateTAG_menubtnX);
		
	}
	return pBtnX;
}

bool MainNavigate::getisMainBtnOpen()
{
	return _isMainBtnOpen;
}

void MainNavigate::setisMainBtnOpen(bool var)
{
	if (getisMainBtnOpen() == var)
		return;

	if (var)
	{
		_isMainBtnOpen = true;
		SpriteNode* pX = getBtnX();
		if (pX)
		{
			pX->runAction(cocos2d::CCRotateTo::actionWithDuration(ACTIONTIME, 45.5));
		}
		_mainNavigateX->setisMenuOpen(true);
		_mainNavigateY->setisMenuOpen(true);
	}
	else
	{
		_isMainBtnOpen = false;
		SpriteNode* pX = getBtnX();
		if (pX)
		{
			pX->runAction(cocos2d::CCRotateTo::actionWithDuration(ACTIONTIME, 0));
		}
		_mainNavigateX->setisMenuOpen(false);
		_mainNavigateY->setisMenuOpen(false);

	}

	// notify newhand
	NewHandView::Instance()->onMainNavigateChange(_isMainBtnOpen);


	// hide Y map button if  is in copy map
	if (_mainNavigateY)
	{
		SceneProxy * pSceneProxy = (SceneProxy *)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
		if (pSceneProxy && pSceneProxy->sceneInfoVo())
		{
			int type = pSceneProxy->sceneInfoVo()->type;
			/*
			if( (type == SceneType::STORY || type == SceneType::STORY)
				|| (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208))// world boss map
				*/
			if ( type != SceneType::CITY)
			{
				 _mainNavigateY->hideButtonByType(2 , false);
				 _mainNavigateY->hideButtonByType(7 , false);
			}
			else
			{
				_mainNavigateY->hideButtonByType(2 , true);
				_mainNavigateY->hideButtonByType(7 , true);
			}

		}
	}
	
	// chat components handle
	showChatComponents(!var);

	// reset VScroll
	if (ViewManager::getInstance()->_pVScrollUI)
	{
		ViewManager::getInstance()->_pVScrollUI->resetListView();
		//ViewManager::getInstance()->_pVScrollUI->scrollToItemByIndex(4,0);
		//((CCUIListView *)ViewManager::getInstance()->_pVScrollUI->getChildByTag(20))->scrollToEnd(0);
		//((CCUIListView *)ViewManager::getInstance()->_pVScrollUI->getChildByTag(20))->scrollToTop(0);
	}

	// help button
	
	if (ViewManager::getInstance()->_helpButton)
	{
		if ( RoleManage::Instance()->roleLev() < 31)
		{
			ViewManager::getInstance()->_helpButton->setIsVisible(!var);
		}
		else
		{
			ViewManager::getInstance()->_helpButton->setIsVisible(false);
		}
	}

	//LH20121120 show vscroll and taskuiview
	/*
	if (g_pGlobalManage->getIsInWorldBoss()
		|| g_pGlobalManage->getisInFight()
		|| g_pGlobalManage->getIsInWordMap()
		|| g_pGlobalManage->isInStory)
	{
		showVScrollAndTaskUIView(false);
	}
	else
	{
		showVScrollAndTaskUIView(true);
	}
	*/
}

void MainNavigate::handleMainBtn(CCObject* pSender)
{
	setisMainBtnOpen(!getisMainBtnOpen());
}

void MainNavigate::popUIHandler1(CCObject* pSender)
{
	//this->setisMainBtnOpen(!this->getisMainBtnOpen());
	FigureMediator* figureM = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	figureM->openFigureView();

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandler2(CCObject* pSender)
{	
	//setisMainBtnOpen(!getisMainBtnOpen());
//	BagMediator* p = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
//	p->bagPop();	kevink
	
	FigureMediator* figureM = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	figureM->openFigureView();
	
	//g_pFigureScrollView->moveToPreviousPage();

	ViewManager::getInstance()->figureView->changeStage(1);// = _bankView;
	// add code here
	BagMediator* p = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
	p->bagPop();

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandler4(CCObject* pSender)
{
	//setisMainBtnOpen(!getisMainBtnOpen());
	UpSkillMediator* p = (UpSkillMediator*)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
	p->popUpSkillView();

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}


void MainNavigate::popUIHandler3(CCObject* pSender)
{
	CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	//setisMainBtnOpen(!getisMainBtnOpen());
	GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_STRENG, 0 );

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandler6(CCObject* pSender)
{
	GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_FRIEND, 0 );

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandler7(CCObject* pSender)
{
	int tmp = 0;
	GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_GUILD, &tmp );

	SoundManager::Instance()->playPopContainerEffectSound();

}
void MainNavigate::popUIHandler8(CCObject* pSender)
{
	CrystalMediator* p = (CrystalMediator*)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	p->popCrystalView();	

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandler9(CCObject* pSender)
{
	FormationMediator * p = (FormationMediator*)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	p->openFormationView();	

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandler10(CCObject* pSender)
{
	if ( RoleManage::Instance()->_mercList.size() <= 1 )
	{
		LangManager::msgShow("TRN034");
		return;
	}
	
	FigureMediator* figureM = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	figureM->openFigureView();
	if ( figureM->_figureMainView && figureM->_figureMainView->_figureV )
	{
		figureM->_figureMainView->_figureV->clickButtonTrain( 0 );
	}

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();

	//GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_TRAIN, 0 );	
}

void MainNavigate::popUIHandler11(CCObject * pSender)
{
	TaskMediator *pTaskMediator = (TaskMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	if(pTaskMediator) 
	{
		pTaskMediator->openTaskView();
	}
}

void MainNavigate::popUIHandler13(CCObject * pSender)
{
	
	ZXMediator* p = (ZXMediator*)g_pFacade->retrieveMediator(AppFacade_ZX);
	p->OpenXHView();
	

	SoundManager::Instance()->playPopContainerEffectSound();
}

//void MainNavigate::visit()
//{
//    CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(ccp(1024-50, 50));
//    glEnable(GL_SCISSOR_TEST);
//    glScissor(convertedLocationLowerLeft.x, convertedLocationLowerLeft.y,
//              50,50);
//    CCLayer::visit();
//    glDisable(GL_SCISSOR_TEST);
//}

void MainNavigate::popUIHandlerCD(CCObject* pSender)
{
	// addCD queue to mainboard
	MainUIMediator* pMainUIMediator = (MainUIMediator*)g_pFacade->retrieveMediator( AppFacade_MainUIMediator );
	pMainUIMediator->sendNotification(Facade_Mediator, AppFacade_MainUIMediator, NULL, MainUIMediator::STARTUP_CD_LIST);

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}


void MainNavigate::popUIHandlerMap(CCObject* pSender)
{
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_MAP, 0);

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandlerArena(CCObject* pSender)
{
	//if (g_pGlobalManage->_isOnBusiness)
	//{
	//	LangManager::msgShow("TRD100");
	//	return;
	//}
	ArenaMediator* p = (ArenaMediator*)g_pFacade->retrieveMediator(AppFacade_ARENA_MEDIATOR);
	p->showArenaHandler();

	//g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}




// mail
void MainNavigate::popUIHandlerMail(CCObject* pSender)
{
	//GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_EMAIL, 0);

	//GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_ARMY, 0);
	SoundManager::Instance()->playPopContainerEffectSound();
	
	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->showMailView();
	}
	
}

void MainNavigate::popUIHandlerHelp(CCObject* pSender)
{
	NewHandHelpView* pHelpView = ViewManager::getInstance()->_helpView;
	if (!pHelpView)
	{
//		pHelpView = new NewHandHelpView();
//		pHelpView->init();
		pHelpView = new NewHandHelpView();
		ViewManager::getInstance()->_helpView = pHelpView;
	}
	if (LayerManager::windowLayer && !LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTag_Newhand_Help))
	{
		LayerManager::windowLayer->addChild(pHelpView , WindowLayer::WindowLayerZ_Newhand_Help , WindowLayer::WindowLayerTag_Newhand_Help);
		pHelpView->release();
		//		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTag_Newhand_Help , true);
	}

	pHelpView->resetView(pHelpView->_curId);
	pHelpView->setIsVisible(true);

	if (ViewManager::getInstance()->_helpButton)
	{
		ViewManager::getInstance()->_helpButton->stopAllActions();
		ViewManager::getInstance()->_helpButton->cleanup();
	}
}

void MainNavigate::popUIHandlerY1(CCObject* pSender)
{
}

void MainNavigate::popUIHandlerY2(CCObject* pSender)
{
	if(!g_pGlobalManage->_canMove)
	{
		return;
	}	

	//Doyang 20120726
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::WALK_COMPLETE,0);
	Scene *pScene = ViewManager::getInstance()->_scene;
	if(pScene && pScene->_role && pScene->_role->poseState)
	{
		pScene->_role->poseState->state(SceneConst::STAND);
	}

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::SHOW_UI_MAP, NULL);

	g_pGlobalManage->setIsInWordMap(true);
	g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandlerY3(CCObject* pSender)
{//direct new and open
	SettingView* settingView = ViewManager::getInstance()->_settingView;
	if (!settingView)
	{
		settingView = new SettingView();
		ViewManager::getInstance()->_settingView = settingView;
		settingView->init();
	}

	settingView->setisPop(!settingView->getisPop());
	if (settingView->getisPop())
	{
		settingView->release();
	}
	

	g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void MainNavigate::popUIHandlerY4(CCObject* pSender)
{
	SecNavigate * pSecNav = (SecNavigate *)ViewManager::getInstance()->_secNavigate;
	if (pSecNav)
	{
		pSecNav->popUIHandlerAct(0);
	}
}

void MainNavigate::popUIHandlerY5(CCObject* pSender)
{
	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->showMailView();
	}
}

void MainNavigate::popUIHandlerY6(CCObject* pSender)
{

}

void MainNavigate::onCompleteButtonFly( CCNode *pNode, void *data )
{
	/*if(!getisMainBtnOpen())
	{
	setisMainBtnOpen(true);
	}*/
	LayerManager::newhandLayer->removeChildByTag(1001, false);
	this->onCompleteAddButton(pNode, data);

	
		if (NewhandManager::Instance()->getNavigateType() == NewhandManager::Navigate_LeftVscroll)
		{
			if (ViewManager::getInstance()->_pVScrollUI)
			{
				ViewManager::getInstance()->_pVScrollUI->showUI(true);		
			}
		}
}

void MainNavigate::onCompleteButtonFlyForVscroll(CCNode *pNode, void *pData)
{
	LayerManager::newhandLayer->removeChildByTag(1001, false);

	if (ViewManager::getInstance()->_pVScrollUI)
	{
		if (RoleManage::Instance()->roleLev() == 2)
		{
			ViewManager::getInstance()->_pVScrollUI->addButtonByLev(RoleManage::Instance()->roleLev());
		}
		ViewManager::getInstance()->_pVScrollUI->showUI(true);
	}

	this->onCompleteAddButton(pNode, pData);

	
}

void MainNavigate::onCompleteAddButton( CCNode *pNode, void *pData )
{
	int type = *(int *)pData;
	//btn.addEventListener(MouseEvent.CLICK, this["popUIHandler" + type] as Function);
	NewhandManager::Instance()->touchNextScript("addBtn", type);

	//Doyang 20120716
	CC_SAFE_DELETE(pData);
}

CCNode * MainNavigate::getNewHandItem( int btnId )
{
	if(_mainNavigateX)
	{
		if(_mainNavigateX->getChildByTag(0))
		{
			if (btnId <20) // strength
			{
				
			}
			else if (btnId <40)
			{
				if (ViewManager::getInstance()->_pVScrollUI)
				{
					return ViewManager::getInstance()->_pVScrollUI->getNewHandItem(btnId);
				}
				return 0;
			}
			return _mainNavigateX->getChildByTag(0)->getChildByTag(btnId);
		}
	}
	return NULL;
}

void MainNavigate::outOfMap( CCObject* pSender )
{
	//this->hideOutMap();

	// add out ...
	//this->popUIHandlerY2(NULL);
	//Doyang 20120724
	SceneProxy *pSceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if(!pSceneProxy->_sceneInfoVo)
	{
		return;
	}

	if(pSceneProxy->_sceneInfoVo->type == SceneType::STORY || pSceneProxy->_sceneInfoVo->type == SceneType::WORLD_BOSS)
	{
		int cityId = DungeonEntrysManage::Instance()->getCityIDByMapID(pSceneProxy->_sceneInfoVo->id);
		CCMD116 ccmd116;
		ccmd116.triggerId = (int16)cityId;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if(pSocket)
		{
			//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
			pSocket->sendMessage(&ccmd116);
		}
	} 
	else if(pSceneProxy->_sceneInfoVo->type == SceneType::COPY)
	{
		CCMD32C ccmd32c;
		ccmd32c.a_reason = 0;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if(pSocket)
		{
			//LayerManager::loadingPic->socketWait_old(WMSG_WORLD_MAP_SKIP);
			pSocket->sendMessage(&ccmd32c);
		}
	}
}

void MainNavigate::hideOutMap()
{
	g_pGlobalManage->setIsInCopyMap(false);

	CCNode *pMenuNode = this->getChildByTag(TAG_OUT_ITEM);
	//CCNode *pMenuLabelNode = this->getChildByTag(TAG_OUT_ITEM_LABEL);
	if(pMenuNode)
	{
		pMenuNode->setIsVisible(false);
	}
// 	if(pMenuLabelNode)
// 	{
// 		pMenuLabelNode->setIsVisible(false);
// 	}

	/*
	CCMenu *pMailNode = (CCMenu *) this->getChildByTag(TAG_MAIL);
	if(pMailNode)
	{
		pMailNode->setIsVisible(true);
		pMailNode->setIsTouchEnabled(true);
	}
	CCLabelTTF *pMailTextNode = (CCLabelTTF *) this->getChildByTag(TAG_MAIL_TEXT);
	if(pMailTextNode)
	{
		pMailTextNode->setIsVisible(true);
	}
	CCSprite *pMailLightNode = (CCSprite *) this->getChildByTag(TAG_MAIL_LIGHT);
	if(pMailLightNode)
	{
		pMailLightNode->setIsVisible(true);
	}
	*/

	CCMenu *pSmallMapBgNode = (CCMenu *) this->getChildByTag(TAG_SMALL_MAP_BG);
	if(pSmallMapBgNode)
	{
		pSmallMapBgNode->setIsVisible(true);
	}

	CCMenu *pSmallMapNode = (CCMenu *) this->getChildByTag(TAG_SMALL_MAP);
	if(pSmallMapNode)
	{
		pSmallMapNode->setIsVisible(true);
		pSmallMapNode->setIsTouchEnabled(true);
	}
	
	VScrollUI * pVscroll = ViewManager::getInstance()->_pVScrollUI;
	if (pVscroll)
	{
		pVscroll->setIsVisible(true);
	}

	//SecNavigate * pSecMain = (SecNavigate *)ViewManager::getInstance()->_secNavigate;
	//if (pSecMain)
	//{
	//	pSecMain->setIsHideCenterTopItems(true);
	//}
}

void MainNavigate::showOutMap()
{
	g_pGlobalManage->setIsInCopyMap(true);

	CCNode *pMenuNode = this->getChildByTag(TAG_OUT_ITEM);
	//CCNode *pMenuLabelNode = this->getChildByTag(TAG_OUT_ITEM_LABEL);

	int curMapId = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
	if(pMenuNode)
	{
		pMenuNode->setIsVisible(!(curMapId == 1208));
	}
// 	if(pMenuLabelNode)
// 	{
// 		pMenuLabelNode->setIsVisible(!(curMapId == 1208));
// 	}

	CCMenu *pMailNode = (CCMenu *) this->getChildByTag(TAG_MAIL);
	if(pMailNode)
	{
		pMailNode->setIsVisible(false);
		pMailNode->setIsTouchEnabled(false);
	}
	CCLabelTTF *pMailTextNode = (CCLabelTTF *) this->getChildByTag(TAG_MAIL_TEXT);
	if(pMailTextNode)
	{
		pMailTextNode->setIsVisible(false);
	}
	CCSprite *pMailLightNode = (CCSprite *) this->getChildByTag(TAG_MAIL_LIGHT);
	if(pMailLightNode)
	{
		pMailLightNode->setIsVisible(false);
	}

	CCMenu *pSmallMapBgNode = (CCMenu *) this->getChildByTag(TAG_SMALL_MAP_BG);
	if(pSmallMapBgNode)
	{
		pSmallMapBgNode->setIsVisible(false);
	}

	CCMenu *pSmallMapNode = (CCMenu *) this->getChildByTag(TAG_SMALL_MAP);
	if(pSmallMapNode)
	{
		pSmallMapNode->setIsVisible(false);
		pSmallMapNode->setIsTouchEnabled(false);
	}

	VScrollUI * pVscroll = ViewManager::getInstance()->_pVScrollUI;
	if (pVscroll)
	{
		pVscroll->setIsVisible(false);
		if (!pVscroll->getIsHide())
		{
			//pVscroll->clickHideVscroll();
		}
	}
	
	//SecNavigate * pSecMain = (SecNavigate *)ViewManager::getInstance()->_secNavigate;
	//if (pSecMain)
	//{
	//	pSecMain->setIsHideCenterTopItems(false);
	//}
	
}

void MainNavigate::onHideOtherPlayers(CCObject * pSender)
{
	g_pGlobalManage->setIsHideOtherPlayers(!g_pGlobalManage->getIsHideOtherPlayers());
	bool bVar = g_pGlobalManage->getIsHideOtherPlayers();


	SystemManage::Instance()->showPlayers(!bVar);
	SceneProxy * pSceneProxy = (SceneProxy *)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if (pSceneProxy)
	{
		pSceneProxy->showPlayersHandler();
	}

	if (this->getChildByTag(TAG_HIDEPLAYER_MENU)
		&& this->getChildByTag(TAG_HIDEPLAYER_MENU)->getChildByTag(1001))
	{
		CCLabelTTF * pHideText = (CCLabelTTF * )this->getChildByTag(TAG_HIDEPLAYER_MENU)->getChildByTag(1001)->getChildByTag(1001);
		if (pHideText)
		{
			pHideText->setString(bVar ? ValuesUtil::Instance()->getString("WLC005").c_str() : ValuesUtil::Instance()->getString("WLC004").c_str() );
		}		
	}
	
}

void MainNavigate::showChatComponents(bool bhide)
{
	// chat button
	//SecNavigate * pSecNavigate = ViewManager::getInstance()->_secNavigate;
	//if (pSecNavigate)
	//{
	//	CCNode * pNode = (CCNode *)pSecNavigate->getChildByTag(14);
	//	if (pNode)
	//	{
	//		int plus = bhide ? (0) : (-1);
	//		CCFiniteTimeAction * pMove = CCMoveTo::actionWithDuration(0.3f , ccp(0, plus * POSX(110)));
	//		CCFiniteTimeAction * pFade = CCFadeOut::actionWithDuration(0.3f);
	//		CCSpawn * pAction = CCSpawn::actionOneTwo(pMove , bhide ? pFade->reverse() : pFade);
	//		
	//		pNode->runAction(pAction);
	//	}		
	//}

	ChatView* chatBtn = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatBtn);
	if (chatBtn)
	{
		int plus = bhide ? (0) : (-1);
		CCFiniteTimeAction * pMove = CCMoveTo::actionWithDuration(0.3f , ccp(0, plus * POSX(110)));
		chatBtn->runAction(pMove);
	}
	
	// chat pop
	ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
	if (chatview)
	{
		int plus = bhide ? (0) : (-1);
		CCFiniteTimeAction * pMove = CCMoveTo::actionWithDuration(0.3f , ccp(0, plus * POSX(110)));
		chatview->runAction(pMove);
	}
}

void MainNavigate::setMapName(std::string name)
{
	if (this->getChildByTag(TAG_OUT_ITEM)
		&& this->getChildByTag(TAG_OUT_ITEM)->getChildByTag(1001)
		&& this->getChildByTag(TAG_OUT_ITEM)->getChildByTag(1001)->getChildByTag(1001))
	{
		CCLabelTTF * pName = (CCLabelTTF *)this->getChildByTag(TAG_OUT_ITEM)->getChildByTag(1001)->getChildByTag(1001)->getChildByTag(1001);
		if (pName)
		{
			pName->setString(name.c_str());
		}		
	}	
}

void MainNavigate::showVScrollAndTaskUIView(bool var)
{
	if (ViewManager::getInstance()->_taskUIView)
	{
		ViewManager::getInstance()->_taskUIView->showUI(var);
	}

	if (ViewManager::getInstance()->_pVScrollUI)
	{
		if (!var)
		{
			ViewManager::getInstance()->_pVScrollUI->showUI(var);
		}
		else
		{
#if CC_NEW_VSCROLLUI_OPEN

#else
			ViewManager::getInstance()->_pVScrollUI->showUI(var);
#endif
		}
	}
}

void MainNavigate::addButtonByLev(int lev)
{
	switch (lev)
	{
	case LevLimitConst::Limit_Mail:
		{
			//_mainNavigateX->addButton(12, 0, this, menu_selector(MainNavigate::popUIHandlerMail));
			addButton(12, -1, false);
		}
		break;
	case LevLimitConst::Limit_Train:
		{
			//_mainNavigateX->addButton(10, 0, this, menu_selector(MainNavigate::popUIHandler10));
			//addButton(10, -1, false);
		}
		break;
	case LevLimitConst::Limit_Guild:
		{
			//_mainNavigateX->addButton(7, 0, this, menu_selector(MainNavigate::popUIHandler7)); 
			addButton(7, -1, false);
		}
		break;
	case LevLimitConst::Limit_Peiyang:
		{
			CCNode * pNode = ViewManager::getInstance()->figureView;
			if (pNode)
			{
				pNode = ((FigureMainView *)pNode)->_figureV;
				if (pNode)
				{
					((FigureView *)pNode)->showButtonByTag(FigureView::TAG_BTN_PEIYANG , true);
				}				
			}			
		}
		break;
	case LevLimitConst::Limit_Gua:
		{
			// tower
			TowerView * pTowerView = ViewManager::getInstance()->_pTowerView;
			if (pTowerView && pTowerView->_panelFight)
			{
				pTowerView->_panelFight->showButtonGua(true);
			}
			
			// story copy && challege copy
			//
		}
		break;
	case LevLimitConst::Limit_Magic: // or Limit_Melting
		{
			MainStrengView * pView = ViewManager::getInstance()->_mainStrengView;
			if (pView)
			{
				pView->refreshTabMenu();
			}			
		}
		break;
	case LevLimitConst::Limit_EquipHeritage:
		{
			MainStrengView * pView = ViewManager::getInstance()->_mainStrengView;
			if (pView)
			{
				pView->refreshTabMenu();
			}
		}
		break;
	case LevLimitConst::Limit_UpFormation:
		{
			//_mainNavigateX->addButton(4, 0, this, menu_selector(MainNavigate::popUIHandler4));
			addButton(4, -1, false);
		}
		break;
	case LevLimitConst::Limit_Zhanxing:
		{
			//_mainNavigateX->addButton(4, 0, this, menu_selector(MainNavigate::popUIHandler4));
			addButton(13, -1, false);
		}
		break;
	default:
		break;
	}	
}

void MainNavigate::enableMainavigate(bool bVar)
{
	setisMainBtnOpen(false);

	CCMenu* pMainButtonMenu = (CCMenu*)this->getChildByTag(MainNavigateTAG_menubtn);
	if (pMainButtonMenu)
	{
		pMainButtonMenu->setIsTouchEnabled(bVar);
		pMainButtonMenu->setIsVisible(bVar);
	}
	if (_mainNavigateX)
	{
		CCMenu* menu = (CCMenu*)_mainNavigateX->getChildByTag(MainNavigateX::MainNavigateXTAG_menubtn);
		if (menu)
		{
			menu->setIsTouchEnabled(bVar);
		}
		_mainNavigateX->setIsTouchEnabled(bVar);
	}
	if (_mainNavigateY)
	{
		CCMenu* menu = (CCMenu*)_mainNavigateY->getChildByTag(MainNavigateY::MainNavigateYTAG_menubtn);
		if (menu)
		{
			menu->setIsTouchEnabled(bVar);
		}		
		_mainNavigateY->setIsTouchEnabled(bVar);
	}
	SpriteNode* pBtnX = (SpriteNode*)this->getChildByTag(MainNavigateTAG_menubtnX);
	if (pBtnX)
	{
		pBtnX->setIsVisible(bVar);
	}
}
