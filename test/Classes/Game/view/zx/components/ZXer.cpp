#include "ZXer.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "Confirm.h"
#include "socket/network/GameServerSocket.h"
#include "manager/ViewManager.h"
#include "socket/command/c46/CCMD461.h"

ZXer::ZXer()
{
	m_iIndex = 0;
	m_bCanClick = false;
}

ZXer::~ZXer()
{}

void ZXer::update(int val)
{
	

	CCMenu *buttonMenu = (CCMenu*)this->getChildByTag(100);
	if (!buttonMenu)
	{
		buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_zx-1);
		this->addChild(buttonMenu, 0, 100);	
		buttonMenu->release();	
		{
			char headstr[50];
			sprintf(headstr, "assets/ui/zx/head_%d_%d.png", m_iIndex, 1);
			CCMenuItemImage *_btn = CCMenuItemImage::itemFromNormalImage(
				headstr,
				headstr,
				this, 
				menu_selector(ZXer::clickZX) );


			buttonMenu->addChild(_btn, 0, 0);
		
		}

		{
			char headstr[50];
			sprintf(headstr, "assets/ui/zx/head_%d_%d.png", m_iIndex, 0);
			SpriteNode* falseNode = new SpriteNode();
			falseNode->initWithFile(headstr);
			this->addChild(falseNode, 0, 101);	
			falseNode->release();
		}
	}

	if (val == 0)
	{
		m_bCanClick = false;
		buttonMenu->setIsVisible(false);
		SpriteNode* falseNode = (SpriteNode*)this->getChildByTag(101);
		falseNode->setIsVisible(true);
	}
	else
	{
		m_bCanClick = true;
		buttonMenu->setIsVisible(true);
		SpriteNode* falseNode = (SpriteNode*)this->getChildByTag(101);
		falseNode->setIsVisible(false);
	}


}



bool ZXer::init(int index)
{
	if (!LayerNode::init())
	{
		return false;
	}

	m_iIndex = index;

	//bg
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/zx/zx_1.png");
		this->addChild(sp, 0);
		sp->release();
		sp->setPosition(ccp(0,0));
	}
	
	//
	{
		char name[30];
		sprintf(name, "ZX00%d", index+3);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( name ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(0, POSX(-64)));
		this->addChild(pLabel, 0);
		pLabel->setColor(ccc3(251, 240, 240));
	}
	//
	{
		int cost = 0;
		switch (index)
		{
		case 0:cost = 5000;break;
		case 1:cost = 10000;break;
		case 2:cost = 20000;break;
		case 3:cost = 40000;break;
		case 4:cost = 60000;break;
		}
		char coststr[30];
		sprintf(coststr, ValuesUtil::Instance()->getString( "ZX008" ).c_str(), cost);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(coststr, CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(0, POSX(-90)));
		this->addChild(pLabel, 0);
		pLabel->setColor(ccc3(251, 216, 0));	
	}
	return true;
}

void ZXer::clickZX(CCObject* pSender)
{
	if (!m_bCanClick)
		return;

	//
	CCMD461 cmd;
	cmd.zxerIndex = m_iIndex;
	GameServerSocket::getInstance()->sendMessage( &cmd );
}