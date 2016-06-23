#include "ZXView.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "CCUIBackground.h"
#include "manager/ViewManager.h"
#include "Confirm.h"
#include "view/zx/ZXMediator.h"
#include "XHView.h"
#include "ZXer.h"
#include "ZXDuiView.h"
#include "socket/command/c46/CCMD466.h"
#include "socket/command/c46/CCMD467.h"
#include "socket/command/c46/CCMD468.h"
#include "model/zx/XHConfManager.h"
#include "socket/command/c46/CCMD461.h"
#include "ZXCollectXH.h"
#include "../../../manager/VIPMgr.h"
#include "../../../manager/VIPLimitConst.h"
#include "../../../../UIComponent/MessageInfoBox.h"
#include "../../../model/player/RoleManage.h"

ZXView::ZXView()
{
	_pContainer = 0;

	m_bFirstOpenXH = true;
	
}

ZXView::~ZXView()
{}

bool ZXView::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	{
		//
		_pContainer = new LayerNode();
		_pContainer->init();
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		this->addChild(_pContainer, 1);
		_pContainer->release();
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	this->addChild(_bg0, 0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(16.0f), POSX(12.0f)), ccp(0,0), CCSizeMake(POSX(928.0f), POSX(562.0f)));
	_pContainer->addChild(_bg1, 1);
	_bg1->release();

	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(25.0f), POSX(32.0f)), ccp(0,0), CCSizeMake(POSX(931.0f-25.0f), POSX(604.0f-438.0f)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(25.0f), POSX(640-436.0f)), ccp(0,0), CCSizeMake(POSX(931.0f-25.0f), POSX(428.0f-87.0f)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();
	}

	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(ZXView::clickClose) );
		_btnX->setPosition(ccp(screenSize.width-_btnX->getContentSize().width/2, 
			screenSize.height-_btnX->getContentSize().height/2));


		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->addChild(_btnX, 0, 0);
		buttonMenu->setPosition(ccp(0, 0));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_zx-1);
		this->addChild(buttonMenu, 5);
		buttonMenu->release();
	}
	//title
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/zx/title.png");
		_pContainer->addChild(sp, 3);
		sp->release();
		sp->setPosition(ccp(POSX(474), POSX(640-74)));
	}
	//xh_0
	{
		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_zx-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();


		{
			CCMenuItemImage *_btn = CCMenuItemImage::itemFromNormalImage(
				"assets/ui/zx/zx_0.png",
				"assets/ui/zx/zx_0.png",
				this, 
				menu_selector(ZXView::clickBackXH) );


			buttonMenu->addChild(_btn, 0);
			_btn->setPosition(ccp(POSX(847), POSX(640-524)));
		}
	}
	//bag
	{
		for (int i = 0; i < 12; i++)
		{
			m_pBank[i] = new LayerNode();
			m_pBank[i]->init();
			m_pBank[i]->setPosition(POSX(122+138*(i%6)), POSX(640-142-125*(i/6)));
			_pContainer->addChild(m_pBank[i], 5, ZXViewTAG_BAG+i);
			m_pBank[i]->release();

			{
				SpriteNode* sp = new SpriteNode();
				sp->initWithFile("assets/ui/zx/cellbg.png");
				m_pBank[i]->addChild(sp, 0);
				sp->release();
				sp->setPosition(ccp(POSX(0), POSX(0)));
			}
		}
	}

	//ZXer
	{
		for (int i = 0; i < 5; i++)
		{
			m_pZXer[i] = new ZXer();
			m_pZXer[i]->init(i);
			_pContainer->addChild(m_pZXer[i], 5, ZXViewTAG_ZXEr+i);
			m_pZXer[i]->release();
			m_pZXer[i]->setPosition(ccp(POSX(98+154*i), POSX(640-500)));


			m_pZXer[i]->update(0);
		}

		for (int i = 0; i < 4; i++)
		{
			SpriteNode* sp = new SpriteNode();
			sp->initWithFile("assets/ui/zx/zx_arrow.png");
			_pContainer->addChild(sp, 5);
			sp->release();
			sp->setPosition(ccp(POSX(173+154*i), POSX(640-500)));
		}
	}
	//今日还可以免费占星    次
	{	
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX009" ).c_str(), CCSizeMake(POSX(400), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0,0));
		pLabel->setPosition(ccp(POSX(30), POSX(640-361)));
		_pContainer->addChild(pLabel, 5);
		pLabel->setColor(ccc3(251, 240, 240));
	}
	//积分
	{	
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX010" ).c_str(), CCSizeMake(POSX(100), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0,0));
		pLabel->setPosition(ccp(POSX(30), POSX(640-413)));
		_pContainer->addChild(pLabel, 5);
		pLabel->setColor(ccc3(251, 240, 240));
	}
	//一键XX
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_zx-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		
		{//一键占星
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(ZXView::clickOneKeyZX) );
			_btn->setPosition(ccp(POSX(586), POSX(640-399)));


			buttonMenu->addChild(_btn, 0);

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX011" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(251, 216, 0));
		}
		{//一键拾取
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(ZXView::clickOneKeyCollect) );
			_btn->setPosition(ccp(POSX(724), POSX(640-399)));


			buttonMenu->addChild(_btn, 0);

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX012" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(251, 216, 0));
		}
		{//一键卖出
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(ZXView::clickOneKeySell) );
			_btn->setPosition(ccp(POSX(858), POSX(640-399)));


			buttonMenu->addChild(_btn, 0);

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX013" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(251, 216, 0));
		}
		{//积分兑换
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(ZXView::clickDuiHuan) );
			_btn->setPosition(ccp(POSX(331), POSX(640-399)));


			buttonMenu->addChild(_btn, 0);

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ZX014" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(251, 216, 0));
		}
	}
	return true;
}

void ZXView::clickOneKeyZX(CCObject* pSender)
{
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_AutoZhanXing , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_AutoZhanXing);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	CCMD461 cmd;
	cmd.zxerIndex = 255;
	GameServerSocket::getInstance()->sendMessage( &cmd );
}

void ZXView::clickOneKeyCollect(CCObject* pSender)
{
	CCMD467 cmd;
	cmd.a_bankPos = 255;
	GameServerSocket::getInstance()->sendMessage( &cmd );
	////这里需要同步
	//LayerManager::loadingPic->socketWait( WMSG_ZX_RESPONSE, 0, 0);
}

void ZXView::clickOneKeySell(CCObject* pSender)
{	
	CCMD466 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );
	//这里需要同步
	//LayerManager::loadingPic->socketWait( WMSG_ZX_RESPONSE, 0, 0);
}

void ZXView::clickDuiHuan(CCObject* pSender)
{
	if (this->getParent())
	{
		ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
		if (pZXMediator)
		{
			this->setIsVisible(false);

			//
			if (LayerManager::tipsLayer->getChildByTag( TipsLayer::TipsLayerTAG_ZXDuiView))
			{
				LayerManager::tipsLayer->removeAllChildrenWithCleanup(TipsLayer::TipsLayerTAG_ZXDuiView);
			}
			
			ZXDuiView* pZXDuiView = new ZXDuiView();
			pZXDuiView->init();
			LayerManager::tipsLayer->addChild(pZXDuiView, TipsLayer::TipsLayerZ_ZXDuiView, TipsLayer::TipsLayerTAG_ZXDuiView);
			pZXDuiView->release();		
		}	
	}
}

void ZXView::clickBackXH(CCObject* pSender)
{
	if (this->getParent())
	{
		ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
		if (pZXMediator)
		{
			//
			CCMD468 cmd;
			GameServerSocket::getInstance()->sendMessage( &cmd );

			pZXMediator->m_pXHView->setIsVisible(true);
			
			this->removeFromParentAndCleanup(true);
		}	
	}
}

void ZXView::clickClose(CCObject* pSender)
{
	if (this->getParent())
	{
		ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
		if (pZXMediator)
		{
			pZXMediator->m_pXHView->clickClose(0);
			pZXMediator->m_pXHView = 0;
		}	
	}
}

void ZXView::clickBankXH(CCObject* pSender)
{
	CCNode* pBtn = (CCNode*)pSender;
	CCMD467 cmd;
	cmd.a_bankPos = pBtn->getTag();
	GameServerSocket::getInstance()->sendMessage( &cmd );
	//这里需要同步
	//LayerManager::loadingPic->socketWait( WMSG_ZX_RESPONSE, 0, 0);
}

void ZXView::updateZXerState(int totlestate)
{
	for (int i = 0; i < 5; i++)
	{
		if (m_pZXer[i])
		{
			int substate = ((totlestate >> i) & 1);
			m_pZXer[i]->update(substate);
		}
	}
}

void ZXView::buildBankXH(std::list<SCMD464_465Node>& a_XHList)
{
	//select new node
	
	if (!m_bFirstOpenXH)
	{
		//
		for (std::list<SCMD464_465Node>::iterator it = a_XHList.begin(); it != a_XHList.end(); it++)
		{
			bool isnew = true;
			SCMD464_465Node& node = *it;
			for (int i = 0; i < 12; i++)
			{
				if (/*m_iXHWorldID[i].b_id == 0 || */node.b_id == 0 || m_iXHWorldID[i].b_id == node.b_id)
				{//node is old
					isnew = false;
					break;
				}
			}
			if (isnew)
			{
				XHConfVo* conf = XHConfManager::Instance()->getXHConf(node.c_goodId);
				if (!conf)
					break;

				char str[100];
				sprintf(str, ValuesUtil::Instance()->getString( "ZX025" ).c_str(), conf->name.c_str());
				LangManager::msgStr(str);	

			}
		}
		//
		for (int i = 0; i < 12; i++)
		{
			//beCollect or sell
			bool canMoveAni = true;

			if (m_iXHWorldID[i].b_id == 0)
			{//这里没物品
				canMoveAni = false;
			}
			if (m_iXHWorldID[i].c_goodId == 0)
			{//是尘埃
				canMoveAni = false;
			}
			if (a_XHList.size() != 12)
			{
				canMoveAni = false;
			}

			{//非尘埃，是否已经不存在
				for (std::list<SCMD464_465Node>::iterator it = a_XHList.begin(); it != a_XHList.end(); it++)
				{
					SCMD464_465Node& node = *it;

					if (m_iXHWorldID[i].b_id != 0 && 
						m_iXHWorldID[i].b_id == node.b_id)
					{
						canMoveAni = false;
						break;
					}
				
				}		
			}

			if (canMoveAni)
			{
				char picpath[50];
				sprintf(picpath, "assets/ui/zx/xh%02d.png", m_iXHWorldID[i].c_goodId);
				ZXCollectXH* sp = new ZXCollectXH();
				sp->initWithFile(picpath);
				sp->setPosition(m_pBank[m_iXHWorldID[i].a_sitGrid]->getPosition());

				_pContainer->addChild(sp, 10);
				sp->release();
				CCMoveTo* act1 = cocos2d::CCMoveTo::actionWithDuration(1.0f, ccp(POSX(847), POSX(640-524)));

				CCAction* act = cocos2d::CCSequence::actions(act1,
					CCCallFuncN::actionWithTarget(sp, callfuncN_selector(ZXCollectXH::removeself)),
					0);


				sp->runAction(act);

			}

		}
	}


	for (std::list<SCMD464_465Node>::iterator it = a_XHList.begin(); it != a_XHList.end(); it++)
	{

		SCMD464_465Node& node = *it;
		XHConfVo* conf = XHConfManager::Instance()->getXHConf(node.c_goodId);
		if (!conf)
			continue;

		if (!m_pBank[node.a_sitGrid])
			continue;


		
		m_pBank[node.a_sitGrid]->removeChildByTag(ZXViewBankTAG_name, true);
		//m_pBank[node.a_sitGrid]->removeChildByTag(ZXViewBankTAG_pic, true);
		
		//pic
		CCMenu *buttonMenu = (CCMenu *)m_pBank[node.a_sitGrid]->getChildByTag(ZXViewBankTAG_pic);
		if (buttonMenu)
		{
			CCMenuItemImage *_oldbtn = (CCMenuItemImage*)buttonMenu->getChildByTag(node.a_sitGrid);
			if (_oldbtn)
			{
				_oldbtn->unselected();
				buttonMenu->m_pSelectedItem = 0;
			}
			buttonMenu->removeChildByTag(node.a_sitGrid, true);
		}
		else
		{
			buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
			buttonMenu->setTouchLayer(TLE::IntervalLayer_zx-1);
			m_pBank[node.a_sitGrid]->addChild(buttonMenu, 1, ZXViewBankTAG_pic);
			buttonMenu->release();
		}
		if (node.b_id == 0)
			continue;//here no xh
		{
			char picpath[50];
			sprintf(picpath, "assets/ui/zx/xh%02d.png", node.c_goodId);
			CCMenuItemImage *_btn = CCMenuItemImage::itemFromNormalImage(
				picpath,
				picpath,
				this, 
				menu_selector(ZXView::clickBankXH) );
			_btn->setTag(node.a_sitGrid);

			buttonMenu->addChild(_btn, 0);
			
		}
		//name
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(conf->name.c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(20));
		pLabel->setPosition(ccp(POSX(0), POSX(-55)));
		m_pBank[node.a_sitGrid]->addChild(pLabel, 1, ZXViewBankTAG_name);
		//pLabel->setColor(ccc3(251, 216, 0));
		switch (conf->color)
		{
		case 0: pLabel->setColor(ccc3(192, 192, 192)); break;//hui
		case 1: pLabel->setColor(ccc3(33, 255, 33)); break;//green
		case 2: pLabel->setColor(ccc3(74, 74, 255)); break;//blue
		case 3: pLabel->setColor(ccc3(202, 60, 177)); break;//purple
		case 4: pLabel->setColor(ccc3(254, 147, 39)); break;//orange
		case 5: pLabel->setColor(ccc3(247, 51, 40)); break;//red
		default:
			break;
		}
	}

	//reset XH world id
	for (std::list<SCMD464_465Node>::iterator it = a_XHList.begin(); it != a_XHList.end(); it++)
	{
		SCMD464_465Node& node = *it;
		m_iXHWorldID[node.a_sitGrid] = node;
	} 

	m_bFirstOpenXH = false;
}


void ZXView::updateScore(int32 val)
{
	//score
	CCLabelTTF* pLabel = (CCLabelTTF*)_pContainer->getChildByTag(ZXViewTAG_ZXSCORE);
	if (!pLabel)
	{
		char numstr[20]; 
		sprintf(numstr, "%d", val);
		

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(numstr, CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0,0));
		pLabel->setPosition(ccp(POSX(30+90), POSX(640-413)));
		_pContainer->addChild(pLabel, 5, ZXViewTAG_ZXSCORE);
		pLabel->setColor(ccc3(255, 255, 255));
	}
	else
	{
		char numstr[20]; 
		sprintf(numstr, "%d", val);
		pLabel->setString(numstr);
	}
}

void ZXView::updateZXerFreeCountToday(uint32 val)
{
	//score
	CCLabelTTF* pLabel = (CCLabelTTF*)_pContainer->getChildByTag(ZXViewTAG_ZXFREECOUNT);
	if (!pLabel)
	{
		char numstr[20]; 
		sprintf(numstr, "%d", val);
		

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(numstr, CCSizeMake(POSX(60), POSX(28)), CCTextAlignmentLeft, "Arial", POSX(20));
		pLabel->setAnchorPoint(ccp(0,0));
		pLabel->setPosition(ccp(POSX(30+226), POSX(640-361)));
		_pContainer->addChild(pLabel, 5, ZXViewTAG_ZXFREECOUNT);
		pLabel->setColor(ccc3(50, 255, 255));
	}
	else
	{
		char numstr[20]; 
		sprintf(numstr, "%d", val);
		pLabel->setString(numstr);
	}
}