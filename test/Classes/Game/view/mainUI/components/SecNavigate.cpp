#include "SecNavigate.h"
#include "view/dungeonEntrys/DungeonEntrysMediator.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/RoleManage.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "manager/GlobalManage.h"
#include "Message.h"
#include "model/scene/vo/SceneType.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h" 
#include "view/arena/ArenaMediator.h"
#include "view/chat/ChatMediator.h"
#include "manager/TouchLayerEnum.h"
#include "MessageInfoBox.h"
#include "view/chat/components/ChatBtnMenu.h"
#include "view/report/ReportMediator.h"
#include "manager/ViewManager.h"
#include "view/backpack/BagMediator.h"
#include "PopUIBg.h"
#include "manager/sound/SoundManager.h"
#include "view/act/ActMediator.h"
#include "view/egg/EggMediator.h"
#include "manager/LevLimitConst.h"
#include "view/ore/OreMediator.h"

#include "view/gong/GongMediator.h"

#include "model/newhand/NewhandManager.h"
#include "view/task/components/TaskType.h"
#include "model/scene/NPCManager.h"
#include "model/trader/TraderProxy.h"


#define Tag_SecMenuItem (1)

SecNavigate::SecNavigate()
{
	_btnConvey = 0;
    _btnReport = 0;
	_btnChatBtnMenu = 0;
	_buttonIds.clear();
	initView();
}

void SecNavigate::initView()
{
	//CCSize winSizePixels = CCDirector::sharedDirector()->getWinSizeInPixels();
    
    int x = 780, y = 590;
	//Doyang 20120829
	//CCMenuItemImage *_button = NULL;
	if(RoleManage::Instance()->roleInfo() && RoleManage::Instance()->roleInfo()->playerBaseInfo.lev() >= 7)
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/door.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/doorpre.png");
		CCMenuItemSprite *_button = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(SecNavigate::popUIHandler330));

		if(_button)
		{
			_btnConvey = CCMenu::menuWithItems(_button, 0);
			if(_btnConvey)
			{
				_btnConvey->setPosition(CCPointZero);
				//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
				//_button->setPosition(ccp(-300.0f, -50.0f));
				_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
				_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
				addChild(_btnConvey, 0, TAG_ENTRANCE);
				//_button->release();
			}
		}
		_buttonIds.push_back(TAG_ENTRANCE);
        x -= 97;
        if(x < 300)
        {
            x = 780;
            y -= 90;
        }
	}

	// Doyang for DailyTask
	if(RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_DailyTask)
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/dailytask1.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/dailytask2.png");
		CCMenuItemSprite* _button = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,//pNormalSprite,
			pPressedSprite,//pPressedSprite,
			this,
			menu_selector(SecNavigate::popUIHandlerDailyTaskEx));

		if(_button)
		{
			_btnConvey = CCMenu::menuWithItems(_button, 0);
			if(_btnConvey)
			{
				_btnConvey->setPosition(CCPointZero);
				//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
				//_button->setPosition(ccp(-300.0f, -50.0f));
				_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
				_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
				addChild(_btnConvey, 0, TAG_DAILY_TASK_EX);
				//_button->release();
			}
			_buttonIds.push_back(TAG_DAILY_TASK_EX);
			x -= 97;
			if(x < 300)
			{
				x = 780;
				y -= 90;
			}
		}
	}
	

    

	//
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Egg)
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/eggbtn.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/eggbtnpre.png");
		CCMenuItemSprite* _button = CCMenuItemImage::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(SecNavigate::popUIHandler320));

		if(_button)
		{
			_btnConvey = CCMenu::menuWithItems(_button, 0);
			if(_btnConvey)
			{
				_btnConvey->setPosition(CCPointZero);
				//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
				//_button->setPosition(ccp(-300.0f, -50.0f));
				_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
				_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
				addChild(_btnConvey, 0, TAG_EGG);
				//_button->release();
			}
		}
		_buttonIds.push_back(TAG_EGG);
        x -= 97;
        if(x < 300)
        {
            x = 780;
            y -= 90;
        }
	}

	
	////////////////////////////////////
	CCNode* chatBtn = (CCNode*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatBtn);
	if (!chatBtn)
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_1.png");
		CCMenuItemSprite *_button = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(SecNavigate::popUIHandlerChatOpen));

		if(_button)
		{
			_btnChatBtnMenu = ChatBtnMenu::menuWithItems(_button, 0);
			if(_btnChatBtnMenu)
			{
				_btnChatBtnMenu->setPosition(CCPointZero);
				_button->setPosition(POS(ccp(44, 45), ScaleUtil::BOTTOM_LEFT));
				_btnChatBtnMenu->setTouchLayer(TLE::IntervalLayer_chat);
				LayerManager::intervalLayer->addChild(_btnChatBtnMenu, IntervalLayer::IntervalLayerZ_chatBtn, IntervalLayer::IntervalLayerTAG_chatBtn);
			}
		}	
	}

    //added by chenjian Begin
	//report button
	//if(RoleManage::Instance()->roleInfo() && g_pGlobalManage && (g_pGlobalManage->getIsInCopyMap()))
    {
		CCSprite * pBackSprite = new CCSprite();
		pBackSprite->initWithSpriteFrameName("mainui2/smallcircle.png");
		//pBackSprite->setPosition(POS(ccp(/*30*/650.0f, /*450*/590.0f), /*ScaleUtil::CENTER_LEFT*/ScaleUtil::CENTER_RIGHT));
		pBackSprite->setOpacity(255);
		//this->addChild(pBackSprite , -1 , 1001);
		//pBackSprite->release();

        CCMenuItemImage *_button = CCMenuItemImage::itemFromNormalImage(
                "assets/ui/report/btn_report_normal.png",
                "assets/ui/report/btn_report_pressed.png",
                this,
                menu_selector(SecNavigate::popUIHandlerReportOpen));
        if (_button)
        {
			_button->setScale(0.8);
			CCSize size = _button->getContentSize();
			pBackSprite->setPosition(ccp( size.width/2 , size.height/2 ));
			pBackSprite->setScale(1.25);
			_button->addChild(pBackSprite , -1);
			pBackSprite->release();
            _btnReport = CCMenu::menuWithItems(_button, 0);
            if (_btnReport)
            {
                _btnReport->setPosition(CCPointZero);
                _button->setPosition(POS(ccp(680.0f, 590.0f), ScaleUtil::CENTER_TOP));
                _btnReport->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
                addChild(_btnReport, 0);
				_btnReport->setIsVisible(false);
            }
        }
    }
	//added by chenjian End
}

void SecNavigate::popUIHandler331(CCObject* pSender)
{
	GongMediator* p = (GongMediator*)g_pFacade->retrieveMediator(AppFacade_GONG);
	if (p)
		p->openRankingView();
}

void SecNavigate::popUIHandler320(CCObject* pSender)
{
	EggMediator* p = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if (p)
		p->uiLoadHandler();

	SoundManager::Instance()->playPopContainerEffectSound();	
}

void SecNavigate::popUIHandler330(CCObject* pSender)
{
		/*CCUIBackground* _bagContainer = new CCUIBackground();
	_bagContainer->initWithSpriteFrame("ui.png", ccp(0,-20), ccp(0,0), CCSizeMake(464,550));
	addChild(_bagContainer)*/

	//MainUIMediator* pMainUIMediator = (MainUIMediator*)g_pFacade->retrieveMediator( AppFacade_MainUIMediator );
	//pMainUIMediator->sendNotification(Facade_Mediator, AppFacade_MainUIMediator, NULL, MainUIMediator::STARTUP_SEC_NAV);

	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	int mapId = 0;
	if(info)
		mapId = info->playerBaseInfo._mapId;
	SceneVo* sceneVo = SceneManager::Instance()->getSceneDic(mapId);
	if(g_pGlobalManage && (g_pGlobalManage->_canMove == false /*|| g_pGlobalManage->_isOnBusiness*/))
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("MUI125"));
		return;
	}
	else
	{
		if(sceneVo && sceneVo->type != SceneType::CITY)
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("MUI124"));
		}
		else
		{
			DungeonEntrysMediator* pMainUIMediator = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
			if(pMainUIMediator)
				pMainUIMediator->sendNotification(Facade_Mediator, AppFacade_DungeonEntrysMediator, NULL, DungeonEntrysMediator::OPEN_DUNGEON_ENTRYS_VIEW);
		}
	}
	//setConveyHighLight(false);
}

/**
* SHOW_UI_LEVY
*/
void SecNavigate::popUIHandler327Levy( CCObject* pSender )
{
	GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_LEVY, 0 );
}
/**
* SHOW_GOLD_PANEL
*/
void SecNavigate::popUIHandler327( CCObject* pSender )
{
	GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_GOLD_PANEL, 0 );
}

/**
* KEVIN tmp open arena
*/
void SecNavigate::popUIHandlerArenaOpen( CCObject* pSender )
{
	//if (g_pGlobalManage->_isOnBusiness)
	//{
	//	LangManager::msgShow("TRD100");
	//	return;
	//}	
	
	ArenaMediator* p = (ArenaMediator*)g_pFacade->retrieveMediator(AppFacade_ARENA_MEDIATOR);
	p->showArenaHandler();
}

/**
* KEVIN tmp open chat
*/
void SecNavigate::popUIHandlerChatOpen( CCObject* pSender )
{	
	ChatMediator* p = (ChatMediator*)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
	if (p)
		p->showChatViewHandler();
}

CCNode * SecNavigate::getNewHandItem( int btnId )
{
	int nBtnId = btnId;
	if (nBtnId >32000 && nBtnId<=35009)
	{
		nBtnId = (int)(nBtnId/100);
	}

	if (this->getChildByTag(nBtnId))
	{
		return this->getChildByTag(nBtnId)->getChildByTag(Tag_SecMenuItem);
	}
	
	return 0;
}

void SecNavigate::addButton( int type, int sitNum, bool isTween )
{
	CCNode * pCurAddNode = 0;
	int nType = type;
 	if (nType >32000 && nType<=35009)
	{
		nType = (int)(nType/100);
	}
	
	if(nType>=320 && nType<=350)
	{
		// open one button
		if ( nType==TAG_TRADER )
		{
			TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
			if (_traderProxy && (_traderProxy->_restTraderCnt==0))
			{
				return;
			}
		}
		

		bool isExist = false;
		std::list<int>::iterator iter = _buttonIds.begin();
		for (iter ; iter != _buttonIds.end() ; iter++)
		{
			if (*iter == nType)
			{
				isExist = true;
				_buttonIds.erase(iter);
				this->removeChildByTag(nType , true);
				this->removeChildByTag(1000+nType, true);
				break;
			}
		}

		_buttonIds.push_back(nType);
		
		
		greater<int> gt;
		_buttonIds.sort(gt);

		// add all top buttons
		CCNode * pNode = 0;
		int x = 700 + 80, y = 598;
		std::list<int>::iterator it;
		for(it = _buttonIds.begin(); it != _buttonIds.end(); ++ it)
		{
			int id = *it;
			this->removeChildByTag(id, true);
			this->removeChildByTag(1000+id, true);
			switch(id)
			{
			case TAG_GONG:
				{
					CCMenuItemImage *pButton = CCMenuItemImage::itemFromNormalImage(
						"assets/ui/gong/xi.png",//pNormalMainBtnSprite,
						"assets/ui/gong/xi.png",//pPressedMainBtnSprite,
						this,
						menu_selector(SecNavigate::popUIHandler331));
					if(pButton)
					{
						CCMenu* _btnLevy = CCMenu::menuWithItems(pButton, 0);
						if(_btnLevy)
						{
							_btnLevy->setPosition(CCPointZero);
							pButton->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnLevy->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnLevy, 0, TAG_GONG);
						}
					}
					pNode = pButton;				
				}
				break;
			case 330:
				{
					 continue; // LH20121031

					CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/arena/res_arena_enter.plist");
					CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("arena/enter_normal.png");
					CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("arena/enter_pressed.png");
					CCMenuItemSprite *pButton = CCMenuItemSprite::itemFromNormalSprite(
						pNormalSprite,
						pPressedSprite,
						this,
						menu_selector(SecNavigate::popUIHandlerArenaOpen));

					if(pButton)
					{
						_btnConvey = CCMenu::menuWithItems(pButton, 0);
						if(_btnConvey)
						{
							_btnConvey->setPosition(CCPointZero);
							pButton->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnConvey, 0, 330);
							//_button->release();
						}
					}
					CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/arena/res_arena_enter.plist");
					pNode = pButton;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}	
				}
				break;
			case 326:
				continue;
				break;

			case TAG_LEVY:
				{
					 continue; // LH20121031

					CCSprite *pNormalMainBtnSprite = CCSprite::spriteWithSpriteFrameName("mainUI/gold_levy_btn.png");
					CCSprite *pPressedMainBtnSprite = CCSprite::spriteWithSpriteFrameName("mainUI/gold_levy_btn_on.png");
					if(!pNormalMainBtnSprite || !pPressedMainBtnSprite)
					{
						return ;
					}
					CCMenuItemSprite *pButton = CCMenuItemSprite::itemFromNormalSprite(
						pNormalMainBtnSprite,
						pPressedMainBtnSprite,
						this,
						menu_selector(SecNavigate::popUIHandler327Levy));
					if(pButton)
					{
						CCMenu* _btnGoldLevy = CCMenu::menuWithItems(pButton, 0);
						if(_btnGoldLevy)
						{
							_btnGoldLevy->setPosition(CCPointZero);
							pButton->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnGoldLevy->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnGoldLevy, 0, TAG_LEVY);
						}
					}
					pNode = pButton;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}	
				}
				break;

			case TAG_GOLD_LEVY:
				{
					// continue;// LH20121031

					CCSprite *pNormalMainBtnSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/award.png");
					CCSprite *pPressedMainBtnSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/awardpre.png");
					if(!pNormalMainBtnSprite || !pPressedMainBtnSprite)
					{
						return ;
					}
					CCMenuItemSprite *pButton = CCMenuItemSprite::itemFromNormalSprite(
						pNormalMainBtnSprite,
						pPressedMainBtnSprite,
						this,
						menu_selector(SecNavigate::popUIHandler327));
					if(pButton)
					{
						CCMenu* _btnLevy = CCMenu::menuWithItems(pButton, 0);
						if(_btnLevy)
						{
							_btnLevy->setPosition(CCPointZero);
							//_btnLevy->setPosition(winSizePixels.width, winSizePixels.height);
							//_button->setPosition(ccp(-200.0f, -50.0f));
							pButton->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnLevy->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnLevy, 0, TAG_GOLD_LEVY);
						}
					}
					pNode = pButton;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}	
				}
				break;
			case TAG_ENTRANCE:
				{
					CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/door.png");
					CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/doorpre.png");
					CCMenuItemSprite *_button = CCMenuItemSprite::itemFromNormalSprite(
						pNormalSprite,
						pPressedSprite,
						this,
						menu_selector(SecNavigate::popUIHandler330));

					if(_button)
					{
						_btnConvey = CCMenu::menuWithItems(_button, 0);
						if(_btnConvey)
						{
							_btnConvey->setPosition(CCPointZero);
							//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
							//_button->setPosition(ccp(-300.0f, -50.0f));
							_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnConvey, 0, TAG_ENTRANCE);
							//_button->release();
						}
					}
					pNode = _button;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}	
				}
				break;
			case TAG_EGG:
				{
					CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/eggbtn.png");
					CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/eggbtnpre.png");
					CCMenuItemSprite* _button = CCMenuItemSprite::itemFromNormalSprite(
						pNormalSprite,//pNormalSprite,
						pPressedSprite,//pPressedSprite,
						this,
						menu_selector(SecNavigate::popUIHandler320));

					if(_button)
					{
						_btnConvey = CCMenu::menuWithItems(_button, 0);
						if(_btnConvey)
						{
							_btnConvey->setPosition(CCPointZero);
							//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
							//_button->setPosition(ccp(-300.0f, -50.0f));
							_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnConvey, 0, TAG_EGG);
							//_button->release();
						}
					}
					pNode = _button;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}	
				}
				break;
			case TAG_FIRST_PURCASE:
				{
					if(RoleManage::Instance()->accountInfo()->_vipLev < 1)
					{
						//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/purchase/res_purchase_btn.plist");
						CCSprite *pPurNormalSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/firstcharge.png");
						CCSprite *pPurPressedSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/firstchargepre.png");
						if(pPurNormalSprite && pPurPressedSprite)
						{
							CCMenuItemSprite *pButton = CCMenuItemSprite::itemFromNormalSprite(
								pPurNormalSprite,
								pPurPressedSprite,
								this,
								menu_selector(SecNavigate::popUIHandlerFirstPurchaseOpen));
							CCMenu *pFirstChaseMenu = CCMenu::menuWithItems(pButton, 0);
							if(pFirstChaseMenu)
							{
								pFirstChaseMenu->setPosition(CCPointZero);
								//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
								//_button->setPosition(ccp(-300.0f, -50.0f));
								pButton->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
								pFirstChaseMenu->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
								addChild(pFirstChaseMenu, 0, TAG_FIRST_PURCASE);
								//_button->release();
							}
							pNode = pButton;
							if (id == nType)
							{
								pCurAddNode = pNode;
							}	
						}

						//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/purchase/res_purchase_btn.plist");


					}
                    else 
                    {
                        continue;
                    }
				}
				break;
			case TAG_ACT:
				{	
					 continue; // LH20121031
				}
				break;
			case TAG_LOGIN_REWARD:
				{	

					CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("reward/loginreward1.png");
					CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("reward/loginreward2.png");
					CCMenuItemSprite* _button = CCMenuItemSprite::itemFromNormalSprite(
						pNormalSprite,//pNormalSprite,
						pPressedSprite,//pPressedSprite,
						this,
						menu_selector(SecNavigate::popUIHandlerLoginReward));

					if(_button)
					{
						_btnConvey = CCMenu::menuWithItems(_button, 0);
						if(_btnConvey)
						{
							_btnConvey->setPosition(CCPointZero);
							//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
							//_button->setPosition(ccp(-300.0f, -50.0f));
							_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnConvey, 0, TAG_LOGIN_REWARD);
							//_button->release();
						}
					}
					pNode = _button;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}	
				}
				break;

			case TAG_DAILY_TASK_EX:
				{
					if (RoleManage::Instance()->roleLev() < LevLimitConst::Limit_DailyTask)
					{
						break;
					}

					CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/dailytask1.png");
					CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("secsmallui/dailytask2.png");
					CCMenuItemSprite* _button = CCMenuItemSprite::itemFromNormalSprite(
						pNormalSprite,//pNormalSprite,
						pPressedSprite,//pPressedSprite,
						this,
						menu_selector(SecNavigate::popUIHandlerDailyTaskEx));

					if(_button)
					{
						_btnConvey = CCMenu::menuWithItems(_button, 0);
						if(_btnConvey)
						{
							_btnConvey->setPosition(CCPointZero);
							//_btnConvey->setPosition(POS(ccp(960.0f, 640.0f), ScaleUtil::CENTER_TOP));
							//_button->setPosition(ccp(-300.0f, -50.0f));
							_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnConvey->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnConvey, 0, TAG_DAILY_TASK_EX);
							//_button->release();
						}
					}
					pNode = _button;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}
				}
				break;

			case TAG_TRADER:
				{
					if (RoleManage::Instance()->roleLev() < LevLimitConst::Limit_Paoshang)
					{
						break;
					}

					TraderProxy* _traderProxy = (TraderProxy*)g_pFacade->retrieveProxy(AppFacade_CITY_TRADER_CHANGE);
					if (_traderProxy && (_traderProxy->_restTraderCnt==0))
					{
						break;
					}

					CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
						"assets/ui/mainUI/secsmallui_trader.plist");
					CCMenuItemSprite* _button = CCMenuItemSprite::itemFromNormalSprite(
						CCSprite::spriteWithSpriteFrameName("secsmallui/trader_btn_nor.png"),
						CCSprite::spriteWithSpriteFrameName("secsmallui/trader_btn_pre.png"),
						this,
						menu_selector(SecNavigate::popUIHandlerTrader) );

					if(_button)
					{
						_btnTrader = CCMenu::menuWithItems(_button, 0);
						if(_btnTrader)
						{
							_btnTrader->setPosition(CCPointZero);
							_button->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
							_btnTrader->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
							addChild(_btnTrader, 0, TAG_TRADER);
						}
					}
					pNode = _button;
					if (id == nType)
					{
						pCurAddNode = pNode;
					}
				}
				break;

			default:
				continue;
				break;
			}

			if (pNode)
			{
				pNode->setTag(Tag_SecMenuItem);
				pNode->setScale(0.9);
			}
			

			// background icon
			CCSprite * pBackSprite = new CCSprite();
			pBackSprite->initWithSpriteFrameName("mainui2/smallcircle.png");
			pBackSprite->setPosition(POS(ccp(x, y), ScaleUtil::CENTER_TOP));
			pBackSprite->setOpacity(255);
			this->addChild(pBackSprite , -1 ,1000+id);
			pBackSprite->release();

			x -= 97;
			if(x < 300)
			{
				x = 780;
				y -= 90;
			}
		}
	}


	// isTween ; show fly action 
	if(isTween)
	{
		if (!pCurAddNode)
		{
			return;
		}
		if (( type >= 320 && type <=  350) || (type > 32000 && type <=  35009))
		{
			int nId = type;
			if (nId > 32000 && nId <=  35009)
			{
				nId = (int)(nId / 100);
			}			
			std::string szPath = NewhandManager::Instance()->getImagePathByButtonId(nId);
			CCSprite * pFlySprite = CCSprite::spriteWithSpriteFrameName(szPath.c_str());
			if(pFlySprite && LayerManager::newhandLayer)
			{
				// GoGoGo...
				pFlySprite->setPosition(POS(ccp(480, 320), ScaleUtil::CENTER));
				LayerManager::newhandLayer->addChild(pFlySprite, 0, 1001);

				CCPoint pos = pCurAddNode->getPosition();

				CCFiniteTimeAction *pFlyAction = CCMoveTo::actionWithDuration(1.2,
					/*POS(ccp(900, 60), ScaleUtil::BOTTOM_RIGHT)*/pos);
				CCFiniteTimeAction *pAlphaAction = CCFadeOut::actionWithDuration(0.6);
				int *p = new int;
				*p = type;
				CCCallFuncND *pCompleteFunc = CCCallFuncND::actionWithTarget(this, callfuncND_selector(MainNavigate::onCompleteButtonFly), p);
				CCAction *pAction = CCSequence::actions(pFlyAction,
					pAlphaAction,
					pCompleteFunc,
					NULL);
				pFlySprite->runAction(pAction);
			}

			if (type == TAG_TRADER)
			{
				CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
					"assets/ui/mainUI/secsmallui_trader.plist");
			}
			
		}
	}
}

void SecNavigate::popUIHandlerAct(CCObject* pSender)
{
//KC1011
	ActMediator* p = (ActMediator*)g_pFacade->retrieveMediator(AppFacade_Act_CHANGE);
	p->pop();

	SoundManager::Instance()->playPopContainerEffectSound();
}

void SecNavigate::popUIHandlerFirstPurchaseOpen( CCObject* pSender )
{
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_FIRST_PURCHASE, NULL);
}

void SecNavigate::addButtonAward()
{
	CCNode* node = this->getChildByTag(TAG_MAPAWARD);
	if (node)
	{
		node->setIsVisible(true);
		return;
	}	

	CCMenuItemSprite *pButton = CCMenuItemSprite::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("mainUI/award_btn.png"),
		CCSprite::spriteWithSpriteFrameName("mainUI/award_btn_press.png"),
		this,
		menu_selector(SecNavigate::popUIHandlerAward));
	if(pButton)
	{
		CCMenu* _btnGoldLevy = CCMenu::menuWithItems(pButton, 0);
		if(_btnGoldLevy)
		{
			_btnGoldLevy->setPosition(CCPointZero);
			pButton->setPosition(POS(ccp(313+139/2-120, 540), ScaleUtil::CENTER_TOP));
			_btnGoldLevy->setTouchLayer(TLE::SceneUILayer_MainNavigateTAG_menubtn);
			addChild(_btnGoldLevy, 0, TAG_MAPAWARD);
		}
	}
	
	SoundManager::Instance()->playPopContainerEffectSound();
}

void SecNavigate::popUIHandlerAward(CCObject* obj)
{
	//g_pReportMediator->openAward( g_pReportMediator->_arward->_honorId );
	g_pReportMediator->openAwardWithoutGift();
}

void SecNavigate::removeBtnAward()
{
	CCMenu* pMKenu = (CCMenu*)getChildByTag(TAG_MAPAWARD);
	if (pMKenu)
	{
		pMKenu->removeFromParentAndCleanup(true);
	}	
}

void SecNavigate::hideBtnAward()
{
	CCMenu* pMKenu = (CCMenu*)getChildByTag(TAG_MAPAWARD);
	if (pMKenu)
	{
		pMKenu->setIsVisible(false);
	}	
}

//Begin chenjian 20121011
void SecNavigate::popUIHandlerReportOpen( CCObject* pSender )
{
	//ReportMediator* p = (ReportMediator*)g_pFacade->retrieveMediator(AppFacade_Report_CHANGE);
	//if (p)
	//	p->showReportView();
	GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_REPORT, 0 );

	SoundManager::Instance()->playPopContainerEffectSound();
}

void SecNavigate::popUIHandlerOre(CCObject* pSender)
{
	OreMediator * pOreMediator = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
	if (pOreMediator)
	{
		pOreMediator->OpenView();
	}
}

void SecNavigate::popUIHandlerLoginReward(CCObject* pSender)
{
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_REWARD , 0);
}

void SecNavigate::setIsReportBtnVisible(bool value)
{
	if(_btnReport != 0)
	{
		// _btnReport->setIsVisible(value); LH20130110
	}
}
//End chenjian 20121011

void SecNavigate::setIsShowCenterTopItems(bool var)
{
	for (int nTag = 320 ; nTag <= 350; nTag++)
	{
		if (this->getChildByTag(nTag))
		{
			this->getChildByTag(nTag)->setIsVisible(var);
		}
	}

	for (int nTag = 1320 ; nTag <= 1350; nTag++)
	{
		if (this->getChildByTag(nTag))
		{
			this->getChildByTag(nTag)->setIsVisible(var);
		}
	}
}

void SecNavigate::popUIHandlerDailyTaskEx( CCObject* pSender )
{
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_DAILY_TASK_EX, NULL);
}

void SecNavigate::popUIHandlerTrader( CCObject* pSender )
{
	if (g_pGlobalManage->_isOnBusiness)
	{
		struct StructTemp
		{
			int id;
			string name;
			int lv;
			int type;
		} param;

		param.id = RoleManage::Instance()->accountInfo()->accountId;
		param.name = RoleManage::Instance()->accountInfo()->name;
		param.lv = RoleManage::Instance()->roleLev();
		param.type = 3;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_ROB_INFO, &param );
	}
	else
	{
		int param = 4;
		GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_CITY_TRADER, &param);
	}	
}

void SecNavigate::addButtonByLev(int lev)
{
	switch (lev)
	{
	case LevLimitConst::Limit_Entrance:
		{
			addButton(TAG_ENTRANCE , -1, false);		
		}
		break;
	case LevLimitConst::Limit_Egg:
		{
			addButton(TAG_EGG , -1, false);	
		}
		break;
	case LevLimitConst::Limit_GoldLevy:
		{
			addButton(TAG_GOLD_LEVY , -1, false);	
		}
		break;
	case LevLimitConst::Limit_DailyTask:
		{
			addButton(TAG_DAILY_TASK_EX , -1, false);	
		}
		break;
	case LevLimitConst::Limit_Levy:
		{
			if (ViewManager::getInstance()->levyView)
			{
				ViewManager::getInstance()->levyView->showLevyButton();
			}
		}
		break;
	default:
		break;
	}	
}

void SecNavigate::fadeDailyTaskExBtn( bool fade )
{
	CCMenu *pNode = (CCMenu *) this->getChildByTag(TAG_DAILY_TASK_EX);

	if(!pNode)
	{
		return;
	}
	if(fade)
	{
		CCFiniteTimeAction * pFadeOut = CCFadeTo::actionWithDuration (0.8f , 128);
		CCFiniteTimeAction * pFadeIn = CCFadeTo::actionWithDuration (0.8f , 255);
		CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeOut , pFadeIn));

		pNode->runAction(pAction);
	}
	else
	{
		pNode->stopAllActions();
		pNode->setOpacity(255);
	}
	
}

void SecNavigate::removeButton(int tag)
{
	if (this->getChildByTag(tag))
	{
		this->removeChildByTag(tag , true);
	}

	if (this->getChildByTag(tag + 1000))
	{
		this->removeChildByTag(tag + 1000 , true);
	}

	std::list<int>::iterator iter;
	for(iter = _buttonIds.begin(); iter != _buttonIds.end(); )
	{
		if (*iter == tag)
		{
			_buttonIds.erase(iter++);
		}		
		else
			iter++;
	}

}
