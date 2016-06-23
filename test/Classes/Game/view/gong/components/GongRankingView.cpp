#include "GongRankingView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "PopUIBg.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "socket/network/GameServerSocket.h"
#include "manager/ViewManager.h"
#include "view/gong/GongMediator.h"


GongRankingView::GongRankingView()
{
	_pContainer = 0;
}

GongRankingView::~GongRankingView()
{

}

void GongRankingView::update(int curwave, std::vector<GongRanking>& vGongRanking)
{
	//第%d波怪兽正在攻城
	{
		char str[100];
		sprintf(str, ValuesUtil::Instance()->getString( "GONG001" ).c_str(), curwave);
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			str,
			CCSizeMake(POSX(500), POSX(50)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(40) );
		txtLabel->setPosition( ccp(POSX(328), POSX(640-230)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5);
		txtLabel->setColor(ccc3(255, 0, 0));
	}

	//还有%d波怪兽正在行进途中......"
	if (curwave < 15)
	{
		char str[100];
		sprintf(str, ValuesUtil::Instance()->getString( "GONG004" ).c_str(), 15-curwave);
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			str,
			CCSizeMake(POSX(500), POSX(50)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(30) );
		txtLabel->setPosition( ccp(POSX(318), POSX(640-490)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5);
		txtLabel->setColor(ccc3(255, 204, 0));
	}

	cocos2d::ccColor3B nodeColors[5] = 
	{ccc3(255, 204, 0), 
	ccc3(255, 0, 234),
	ccc3(0, 126, 255),
	ccc3(0, 255, 12),
	ccc3(255, 255, 255)};

	int size = vGongRanking.size();
	if (size > 5)
		size = 5;
	for (int i = 0; i < size; i++)
	{
		GongRanking& node = vGongRanking[i];
		//name
		{
			char str[30];
			sprintf(str, "%s", node.name.c_str());
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				str,
				CCSizeMake(POSX(200), POSX(50)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(30) );
			txtLabel->setPosition( ccp(POSX(360), POSX(640-305-i*30)) );
			txtLabel->setAnchorPoint(ccp(0,0));
			_pContainer->addChild( txtLabel, 5);
			txtLabel->setColor(nodeColors[i]);
		}
		//%d fen
		{
			char str[30];
			sprintf(str, ValuesUtil::Instance()->getString( "GONG003" ).c_str(), node.killed);

			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
				str,
				CCSizeMake(POSX(200), POSX(50)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(30) );
			txtLabel->setPosition( ccp(POSX(522), POSX(640-305-i*30)) );
			txtLabel->setAnchorPoint(ccp(0,0));
			_pContainer->addChild( txtLabel, 5);
			txtLabel->setColor(nodeColors[i]);
		}
	}

}

bool GongRankingView::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	key = 0;
	setNeedBg(NeedBg_NO);

	{
		//
		_pContainer = new LayerNode();
		_pContainer->init();
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		this->addChild(_pContainer, 0);
		_pContainer->release();
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	_pContainer->addChild(_bg0, 0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(229), POSX(640-577)), ccp(0,0), CCSizeMake(POSX(747-229), POSX(577-103)));
	_pContainer->addChild(_bg1, 1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(243), POSX(640-498)), ccp(0,0), CCSizeMake(POSX(736-243), POSX(498-157)));
	_pContainer->addChild(_bg2, 2);
	_bg2->release();

	//X
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(GongRankingView::clickClose) );
		_btnClose->setPosition(ccp(POSX(745), POSX(640-112)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_gong-1);
		_pContainer->addChild(buttonMenu, 5);		
	}
	//confirm btn
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::WindowLayer_gong-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(GongRankingView::clickClose) );
		_btn->setPosition(ccp(POSX(480), POSX(640-537)));


		buttonMenu->addChild(_btn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "CF001" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
	}

	//冰之城
	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "GONG005" ).c_str(),
			CCSizeMake(POSX(200), POSX(50)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(30) );
		txtLabel->setPosition( ccp(POSX(360), POSX(640-160)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5);
		txtLabel->setColor(ccc3(12, 255, 0));
	}
	//防务警报!
	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "GONG000" ).c_str(),
			CCSizeMake(POSX(300), POSX(50)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(30) );
		txtLabel->setPosition( ccp(POSX(468), POSX(640-160)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5);
		txtLabel->setColor(ccc3(255, 204, 0));
	}

	//击退怪兽排行榜:
	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "GONG002" ).c_str(),
			CCSizeMake(POSX(500), POSX(50)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(30) );
		txtLabel->setPosition( ccp(POSX(384), POSX(640-268)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5);
		txtLabel->setColor(ccc3(255, 240, 240));
	}


	return true;
}

void GongRankingView::clickClose(CCObject* pSender)
{
	if (this->getParent())
	{
		GongMediator * pGongMediator = (GongMediator*)g_pFacade->retrieveMediator(AppFacade_GONG);
		if (pGongMediator)
		{
			pGongMediator->m_pRankingView = 0;
		}

		this->setisPop(false);
	}
}