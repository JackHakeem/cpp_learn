#include "WorldBossMainView.h"
#include "BoostView.h"
#include "BossHPView.h"
#include "DamageRankView.h"
#include "DeathView.h"
#include "QuitView.h"
#include "utils/ScaleUtil.h"
#include "model/battle/FightProxy.h"
#include "model/player/RoleManage.h"
#include "view/fight/callback/FightFollowWorldBossAction.h"
#include "control/AppFacade.h"
#include "utils/ValuesUtil.h"
#include "manager/ViewManager.h"
#include "manager/TouchLayerEnum.h"
#include "view/chat/components/ChatBtnMenu.h"

WorldBossMainView::WorldBossMainView()
{
	_timeCnt = 0;
}

WorldBossMainView::~WorldBossMainView()
{

}

bool WorldBossMainView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	_winSize = CCDirector::sharedDirector()->getWinSize();
	this->setContentSize(_winSize);
	//this->setPosition(ccp(_winSize.width/2 , _winSize.height/2));
	this->setIsRelativeAnchorPoint(true);
	this->setIsTouchEnabled(false);
	//
	loadBoostView();
	loadBossHPView();
	loadDamageRankView();
	loadDeathView();
	loadQuitView();
	loadShowRankListMenu();
	loadChatMenu();

	ShowRewordTips(true);
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(WorldBossMainView::closeStep),this,1,false);

	return true;
}

void WorldBossMainView::closeStep(ccTime dt)
{
	++_timeCnt;
	if (_timeCnt > 10)
	{
		ShowRewordTips(false);
		_timeCnt = 0;
		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(WorldBossMainView::closeStep),this);
	}
}

void WorldBossMainView::loadChatMenu()
{
	// chat menu
	//CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//CCSprite *pSelectedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//CCMenuItemSprite *pChatMenuImg = CCMenuItemSprite::itemFromNormalSprite(
	//	pNormalSprite,
	//	pPressedSprite,
	//	pSelectedSprite,
	//	this,
	//	menu_selector(WorldBossMainView::onClickChat));

	//CCMenu * pChatMenu = CCMenu::menuWithItem(pChatMenuImg);
	//pChatMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
	//pChatMenu->setTag(TAG_Chat_Menu);
	//pChatMenu->setPosition(ccp(_winSize.width/2 + POSX(45) , _winSize.height /2+ POSX(45)));
	//this->addChild(pChatMenu, 0);

	//{
	//	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
	//	CCMenuItemSprite *_button = CCMenuItemSprite::itemFromNormalSprite(
	//		pNormalSprite,
	//		pPressedSprite,
	//		this,
	//		menu_selector(SecNavigate::popUIHandlerChatOpen));

	//	if(_button)
	//	{
	//		ChatBtnMenu*_btnChatBtnMenu = ChatBtnMenu::menuWithItems(_button, 0);
	//		if(_btnChatBtnMenu)
	//		{
	//			_btnChatBtnMenu->setPosition(CCPointZero);
	//			_button->setPosition(POS(ccp(44, 45), ScaleUtil::BOTTOM_LEFT));
	//			_btnChatBtnMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
	//			addChild(_btnChatBtnMenu, 0, 14);
	//			//_button->release();
	//		}
	//	}	
	//}

}

void WorldBossMainView::onClickChat(CCObject * pSender)
{
	if (ViewManager::getInstance()->_secNavigate)
	{
		ViewManager::getInstance()->_secNavigate->popUIHandlerChatOpen(0);
	}
}

void WorldBossMainView::loadShowRankListMenu()
{
	// show rank list menu
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite || !pPressedSprite || !pSelectdSprite)
	{
		return;
	}
	CCMenuItemSprite *pShowMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		pSelectdSprite,
		this,
		menu_selector(WorldBossMainView::onClickShowRankList));

	pShowMenuImg->setScaleX(1.2);
	CCMenu * pShowMenu = CCMenu::menuWithItem(pShowMenuImg);
	//pShowMenu->setIsVisible(false);
	pShowMenu->setPosition(ccp(_winSize.width/2 + POSX(220) , _winSize.height + POSX(45)));
	this->addChild(pShowMenu, 0);

	CCPoint pos = pShowMenu->getPosition();
	CCSize size = pShowMenuImg->getContentSize();

	CCLabelTTF * pShowText = new CCLabelTTF();
	if (pShowText)
	{
		bool var = pShowText->initWithString(ValuesUtil::Instance()->getString("WBS113").c_str() , 
			CCSizeMake(POSX(150) , POSX(30)) , CCTextAlignmentCenter , "Arial" ,POSX(24));
		if (var)
		{
			//pShowText->setIsVisible(false);
			pShowText->setTag(TAG_ShowRank_Menu);
			pShowText->setPosition(ccp(pos.x , pos.y));
			pShowText->setColor(ccc3(255,233,12));
			this->addChild(pShowText , 0);
			pShowText->release();
		}
	}
}

void WorldBossMainView::onClickShowRankList(CCObject * pSender)
{
	DamageRankView * pDamageRankView = (DamageRankView *)this->getChildByTag(TAG_DamageView);
	if (pDamageRankView)
	{
		bool bVar = pDamageRankView->getIsVisible();
		pDamageRankView->setIsVisible(!bVar);

		CCLabelTTF * pShowText = (CCLabelTTF *)this->getChildByTag(TAG_ShowRank_Menu);
		if (pShowText)
		{
			std::string strText = bVar ? ("WBS112") : ("WBS113"); 
			pShowText->setString(ValuesUtil::Instance()->getString(strText.c_str()).c_str());
		}
	}
}

void WorldBossMainView::loadBoostView()
{
	BoostView * pBoostView = new BoostView();
	if (pBoostView)
	{
		pBoostView->init();
		pBoostView->setTag(TAG_BoostView);
		pBoostView->setPosition(ccp(POSX(150) , _winSize.height - POSX(200)));
		this->addChild(pBoostView,0);
		pBoostView->release();
	}
}

void WorldBossMainView::loadBossHPView()
{
	BossHPView * pBossHPView = new BossHPView();
	if (pBossHPView)
	{
		pBossHPView->init();
		pBossHPView->setPosition(ccp(_winSize.width /2 , _winSize.height - POSX(80)));
		pBossHPView->setTag(TAG_BossHPView);
		this->addChild(pBossHPView,0);
		pBossHPView->release();
	}
}

void WorldBossMainView::loadDamageRankView()
{
	DamageRankView * pDamageRankView = new DamageRankView();
	if (pDamageRankView)
	{
		pDamageRankView->init();
		pDamageRankView->setPosition(ccp(_winSize.width + POSX(50) , _winSize.height/2 + POSX(110)));
		pDamageRankView->setTag(TAG_DamageView);
		this->addChild(pDamageRankView,0);
		pDamageRankView->release();
	}
}

void WorldBossMainView::loadDeathView()
{
	DeathView * pDeathView = new DeathView();
	if (pDeathView)
	{
		pDeathView->init();
		pDeathView->setIsVisible(false);
		pDeathView->setPosition(ccp(_winSize.width/2 , _winSize.height /2 - POSX(60)));
		pDeathView->setTag(TAG_DeathView);
		this->addChild(pDeathView,0);
		pDeathView->release();

		/*
		// add fight call back
		FightProxy *pFightProxy = (FightProxy *) g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
		if (pFightProxy)
		{
			int curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
			if (curMapID == 1208)
			{
				pFightProxy->_bData._callbacks.push_back(new FightFollowWorldBossAction());
			}
		}
		*/
	}
}

void WorldBossMainView::loadQuitView()
{
	QuitView * pQuitView = new QuitView();
	if (pQuitView)
	{
		pQuitView->init();
		pQuitView->setPosition(ccp(POSX(80) , _winSize.height /2 + POSX(45)));
		pQuitView->setTag(TAG_QuitView);
		this->addChild(pQuitView,0);
		pQuitView->release();
	}
}

void WorldBossMainView::ShowRewordTips(bool bVar)
{
	if (!this->getChildByTag(TAG_RewordTips))
	{
		// layer color
		CCLayerColor * pLayerColor = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,200));
		if (!pLayerColor)		{return;		}
		pLayerColor->setPosition(_winSize.width/2 , _winSize.height/2);
		pLayerColor->setTag(TAG_RewordTips);
		this->addChild(pLayerColor, 9 );

		CCSize backSize;
		// background
		CCUIBackground * pBack = new CCUIBackground();
		if (pBack)
		{
			bool bVar = pBack->initWithSpriteFrame("ui.png" , ccp(0,0) , ccp(0,0) , CCSizeMake(POSX(600), POSX(430)) , 255);
			if (bVar)
			{
				backSize = pBack->getContentSize();
				pBack->setPosition(ccp(_winSize.width/2 - backSize.width/2 + POSX(130), _winSize.height/2 - backSize.height/2  + POSX(20)));
				pLayerColor->addChild(pBack , 0);
			}
			pBack->release();
		}

		// title
		CCLabelTTF * pTitleLabelText = new CCLabelTTF();
		if (pTitleLabelText)
		{
			bool bVar = pTitleLabelText->initWithString(ValuesUtil::Instance()->getString("WBS129").c_str() , 
				CCSizeMake(POSX(360) , POSX(30)) , 
				CCTextAlignmentCenter , "Arial" , POSX(26));
			if (bVar)
			{
				pTitleLabelText->setColor(ccc3(255,233,12));
				pTitleLabelText->setPosition(ccp(_winSize.width/2  + POSX(130), _winSize.height/2 + backSize.height /2 -POSX(20)));
				pLayerColor->addChild(pTitleLabelText , 1);
			}
			pTitleLabelText->release();
		}

		// tips texts
		for (int i = 0 ; i <= 10 ; i++)
		{
			char path[32] = {0};
			sprintf(path , "WBS%d" , 130+i);
			std::string strText = ValuesUtil::Instance()->getString(path);
			CCLabelTTF * pLabelText = new CCLabelTTF();
			if (pLabelText)
			{
				bool bVar = pLabelText->initWithString(strText.c_str() , CCSizeMake(POSX(720) , POSX(300)) , CCTextAlignmentLeft , "Arial" , POSX(28));
				if (bVar)
				{
					pLabelText->setPosition(ccp(_winSize.width/2 + POSX(50) + POSX(180), _winSize.height/2+  backSize.height /2 + POSX((i+3) * (-30) )  + POSX(20)));
					pLayerColor->addChild(pLabelText , 2);
				}
				pLabelText->release();

				switch ( i )
				{
				case 0:
					pLabelText->setColor(ccc3(255,0,255));
					break;
				case 1:
					pLabelText->setColor(ccc3(0,114,227));
					break;
				case 2:
					pLabelText->setColor(ccc3(0,236,0));
					break;
				default:
					pLabelText->setColor(ccc3(250,250,250));
					break;
				}
			}
		}

		// close menu
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CCMenuItemSprite *pCloseMenuImg = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(WorldBossMainView::onClickCloseRewordTips));

		CCMenu * pCloseMenu = CCMenu::menuWithItem(pCloseMenuImg);
		//pCloseMenu->setIsVisible(false);
		pCloseMenu->setPosition(ccp(pBack->getPosition().x + backSize.width + POSX(-32), pBack->getPosition().y + backSize.height - POSX(10)));
		pLayerColor->addChild(pCloseMenu, 1);

		// set visible
		pLayerColor->setIsVisible(bVar);
	}
	else
	{
		this->getChildByTag(TAG_RewordTips)->setIsVisible(bVar);
	}	
}

void WorldBossMainView::onClickCloseRewordTips(CCObject * pSender)
{
	if (this->getChildByTag(TAG_RewordTips))
	{
		this->getChildByTag(TAG_RewordTips)->setIsVisible(false);
	}

	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(WorldBossMainView::closeStep),this);
}