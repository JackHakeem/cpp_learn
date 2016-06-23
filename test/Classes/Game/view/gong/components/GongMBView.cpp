#include "GongMBView.h"
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
#include "socket/command/c44/CCMD448.h"
#include "socket/command/s44/SCMD44A.h"
#include "KKLabelTTF.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"

GongMBView::GongMBView()
{
	_pContainer = 0;
}

GongMBView::~GongMBView()
{

}

void GongMBView::update(std::string heroname, std::vector<SCMD44ANode>& mbNames)
{
	//上一次怪物对冰之城的袭击中，[%s]击退最多怪物，名列第一
	if (heroname.size() > 0)
	{

		if (this->getChildByTag(Tag_Label))
		{
			this->removeChildByTag(Tag_Label , true);
		}
		char str[100];
		sprintf(str, ValuesUtil::Instance()->getString( "GONG006" ).c_str(), heroname.c_str());
		std::string strval = str;
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(20, 36.0f, CCSizeMake(150, 200));
		pLabel->add(strval, ccc3(255, 204, 0));
		pLabel->setPosition(ccp(POSX(153), POSX(400)));

		_pContainer->addChild(pLabel, 5);

		pLabel->release();
	}
	else
	{

		if (this->getChildByTag(Tag_Label))
		{
			this->removeChildByTag(Tag_Label , true);
		}
		char str[100];
		sprintf(str, ValuesUtil::Instance()->getString( "GONG017" ).c_str());
		std::string strval = str;
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(20, 36.0f, CCSizeMake(150, 200));
		pLabel->add(strval, ccc3(255, 204, 0));
		pLabel->setPosition(ccp(POSX(153), POSX(400)));
		pLabel->setTag(Tag_Label);
		this->addChild(pLabel, 5);
		pLabel->release();

		return;
	}

	cocos2d::ccColor3B nodeColors[5] = 
	{ccc3(255, 204, 0), 
	ccc3(255, 0, 234),
	ccc3(0, 126, 255),
	ccc3(0, 255, 12),
	ccc3(255, 255, 255)};

	int size = mbNames.size();
	if (size > 5)
		size = 5;
	for (int i = 0; i < size; i++)
	{
		SCMD44ANode& node = mbNames[i];
		//name
		{
			char str[100];
			sprintf(str, ValuesUtil::Instance()->getString( "GONG008" ).c_str(), node.name.c_str());
			std::string strval = str;
			KKLabelTTF* pLabel = new KKLabelTTF();
			pLabel->init(20, 30.0f, CCSizeMake(115, 70));
			pLabel->add(strval, nodeColors[i]);
			pLabel->setPosition(ccp(POSX(633), POSX(640-110-i*70)));
			_pContainer->addChild(pLabel, 5);
			pLabel->release();
		}
	}

}

bool GongMBView::init()
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
		this->addChild(_pContainer, 2);
		_pContainer->release();
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	this->addChild(_bg0, 0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(125), POSX(640-600)), ccp(0,0), CCSizeMake(POSX(828-125), POSX(600-68)));
	_pContainer->addChild(_bg1, 1);
	_bg1->release();

	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(136), POSX(640-456)), ccp(0,0), CCSizeMake(POSX(331-136), POSX(456-78)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();	
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(338), POSX(640-456)), ccp(0,0), CCSizeMake(POSX(616-338), POSX(456-78)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();	
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(624), POSX(640-456)), ccp(0,0), CCSizeMake(POSX(331-136), POSX(456-78)));
		_pContainer->addChild(_bg2, 2);
		_bg2->release();	
	}
	//X
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(GongMBView::clickClose) );
		_btnClose->setPosition(ccp(POSX(827), POSX(640-71)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_gong-1);
		_pContainer->addChild(buttonMenu, 5);		
	}
	//confirm btn
	{
		int popuAwardMsgIndex[3] = {18, 13, 14};
		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::WindowLayer_gong-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		for (int i = 0; i < 3; i++)
		{
			CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
			CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(GongMBView::clickMB) );
			_btn->setPosition(ccp(POSX(260+220*i), POSX(640-493)));
			_btn->setTag(i);

			buttonMenu->addChild(_btn, 0);

			char strname[10];
			sprintf(strname, "GONG0%02d", 9+i);
			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( strname ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(20));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(251, 216, 0));

			{
				char strname2[20];
				sprintf(strname2, "GONG0%02d", popuAwardMsgIndex[i]);
				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( strname2 ).c_str(),
					CCSizeMake(POSX(200), POSX(30)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
				txtLabel->setPosition( ccp(POSX(260+220*i), POSX(640-543)) );
				_pContainer->addChild( txtLabel, 5);
				txtLabel->setColor(ccc3(255, 204, 0));
			}
			
			{
				CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
					ValuesUtil::Instance()->getString( "GONG012" ).c_str(),
					CCSizeMake(POSX(200), POSX(30)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
				txtLabel->setPosition( ccp(POSX(260+220*i), POSX(640-578)) );
				_pContainer->addChild( txtLabel, 5);
				txtLabel->setColor(ccc3(255, 204, 0));
			}
		}
	}

	//冰之城守护者
	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "GONG015" ).c_str(),
			CCSizeMake(POSX(300), POSX(50)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(30) );
		txtLabel->setPosition( ccp(POSX(960/2), POSX(640-107)) );
		_pContainer->addChild( txtLabel, 5);
		txtLabel->setColor(ccc3(0, 240, 254));
	}
	//
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/gong/herobg.png");
		_pContainer->addChild( sp, 3);
		sp->release();
		sp->setPosition(ccp(POSX(478), POSX(640-280)));
	}
	//
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/gong/hero.png");
		_pContainer->addChild( sp, 4);
		sp->release();
		sp->setPosition(ccp(POSX(478), POSX(640-280)));
	}
	return true;
}

void GongMBView::clickClose(CCObject* pSender)
{
	if (this->getParent())
	{
		GongMediator * pGongMediator = (GongMediator*)g_pFacade->retrieveMediator(AppFacade_GONG);
		if (pGongMediator)
		{
			pGongMediator->m_pMBView = 0;
		}

		this->setisPop(false);
	}
}

void GongMBView::clickMB(CCObject* pSender)
{
	int tag = ((CCNode*)pSender)->getTag();
	
	if ((tag == 1) && !VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_GoldMobai , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_GoldMobai );
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	if ((tag == 2) && !VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_DingjiMobai, RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_DingjiMobai );
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	CCMD448 cmd;
	cmd.a_MBType = tag;
	GameServerSocket::getInstance()->sendMessage( &cmd );	
}
