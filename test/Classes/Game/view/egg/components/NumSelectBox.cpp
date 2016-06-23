#include "NumSelectBox.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "model/egg/EggProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "GoodsItem.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "view/egg/EggMediator.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"
#include "events/GameDispatcher.h"
#include "TextFieldTTF.h"

#define w_bg1 POSX(928.0f)
#define h_bg1 POSX(562.0f)

#define w_bg2 POSX(910.0f)
#define h_bg2 POSX(524.0f)

const float FontSize = 24.0f;
const float FontSize2 = 24.0f;

NumSelectBox::NumSelectBox()
{
	_txtItemNum = 0;
	_num = 1;

	_dispatcher = GameDispatcher::getInstance();
}

NumSelectBox::~NumSelectBox()
{}

bool NumSelectBox::init()
{
	if (!LayerNode::init())
		return false;

	////
	//_icon = new LayerNode();
	//_icon->init();
	//this->addChild(_icon, 3);
	//_icon->release();
	//_icon->setPosition(ccp(POSX(488), POSX(640-280)));
	////
	//{
	//	SpriteNode* sp = new SpriteNode();
	//	sp->initWithFile("assets/ui/egg/NumSelectBox_itembg.png");
	//	_icon->addChild(sp, 1);
	//	sp->release();
	//}
	//_txtItemNum
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("_txtName", CCSizeMake(POSX(300), POSX(36.0f)), CCTextAlignmentLeft, "Arial", POSX(30.0f));
		pLabel->setPosition(ccp(POSX(343), POSX(640-498+200)));
		pLabel->setAnchorPoint(ccp(0, 0));
		this->addChild(pLabel, 4);
		pLabel->setColor(ccc3(255, 255, 255));	

		_txtItemNum = pLabel;
	}
	//ÊýÁ¿
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("EGG043").c_str(), CCSizeMake(POSX(100), POSX(36.0f)), CCTextAlignmentLeft, "Arial", POSX(30.0f));
		pLabel->setPosition(ccp(POSX(323), POSX(640-498+140)));
		pLabel->setAnchorPoint(ccp(0, 0));
		this->addChild(pLabel, 4);
		pLabel->setColor(ccc3(255, 255, 255));	
	}
	//_txtNum
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithFile("assets/ui/guild/select.png", ccp(POSX(390), POSX(640-498+130)),ccp(0,0),
			CCSizeMake(POSX(570-390), POSX(244-180)));
		this->addChild(_bg, 3);
		_bg->release();
	}
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		//pTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
		pTextField->setString("1");
		pTextField->setIsNumber(true, 10);
		pTextField->m_frame = CCSizeMake(POSX(300), POSX(30));
	//	pTextField->setFieldSize(CCSizeMake(POSX(100),POSX(50)));
	//	pTextField->setUp(this, POSX(380));
		this->addChild(pTextField, 4);
		pTextField->setPosition(ccp(POSX(560), POSX(640-498+168)));
		pTextField->release();
		_txtNum = pTextField;
	}
	//
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	{
		CCUIBackground* _bg0 = new CCUIBackground();
		_bg0->initWithFile("assets/ui/ui2.png", CCPointZero,CCPointZero,screenSize);
		this->addChild(_bg0, 0);
		_bg0->release();
	}
	{
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(292), POSX(640-478-10)), ccp(0,0), CCSizeMake(POSX(690-292), POSX(478-203)));
		this->addChild(_bg1, 1);
		_bg1->release();
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(313), POSX(640-478)), ccp(0,0), CCSizeMake(POSX(669-313), POSX(478-223)));
		this->addChild(_bg2, 1);
		_bg2->release();
	}

	//X
	{
		CCMenuItemSprite* _btn = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png"), 
			CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png"), 
			this, 
			menu_selector(NumSelectBox::close) );
		_btn->setPosition(ccp(POSX(718), POSX(640-34-140)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_egg);
		this->addChild(buttonMenu);	
	}
	//MAX
	{	
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/button3_0.png", 
			"assets/ui/egg/button3_1.png",
			"assets/ui/button2.png",
			this, 
			menu_selector(NumSelectBox::maxHandler) );
		_btn->setPosition(ccp(POSX(610), POSX(640-498+186+30)));
		_btn->setScaleX(0.6f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_egg);
		this->addChild(buttonMenu, 3);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("MAX", CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(217, 210, 193));
		pLabel->setScaleX(1.4f);
	}	
	//Ê°È¡
	{	
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/button3_0.png", 
			"assets/ui/egg/button3_1.png",
			"assets/ui/button2.png",
			this, 
			menu_selector(NumSelectBox::pickHandler) );
		_btn->setPosition(ccp(POSX(960/2), POSX(640-478+40)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_egg);
		this->addChild(buttonMenu, 3);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("EGG042").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(217, 210, 193));
	}	
	return true;
}

void NumSelectBox::setInfo(int eggId, std::string name, int num)
{
	char str_txtItemNum[60];
	sprintf(str_txtItemNum, "%s x %d", name.c_str(), num);
	_txtItemNum->setString(str_txtItemNum);

	char str_tetNum[20];
	sprintf(str_tetNum, "%d", num);
	_txtNum->setString(str_tetNum);

	_eggId = eggId;
	_total = num;
}

void NumSelectBox::maxHandler(CCObject* pSender)
{
	char str[20];
	sprintf(str, "%d", _total);
	_txtNum->setString(str);

	_num = _total;
}

void NumSelectBox::pickHandler(CCObject* pSender)
{
	std::string numstr = ((KKTextFieldTTF*)_txtNum->m_pTrackNode)->getString();
	_num = atoi(numstr.c_str());
	if(_num < 1 || _num > _total){
		char str[30];
		sprintf(str, ValuesUtil::Instance()->getString( "EGG001" ).c_str(), _total);
		LangManager::msgStr(str);
	}else{
		struct sdata
		{
			int eggId;
			int num;
		};
		sdata d;
		d.eggId = _eggId;
		d.num = _num;
		_dispatcher->dispatchEvent(EggMediator::GET_EGG, &d);
	}
}

void NumSelectBox::close(CCObject* pSender)
{
	NumSelectBox* pthis = (NumSelectBox*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_egg_NumSelectBox);
	if (pthis)
		pthis->removeFromParentAndCleanup(true);
}

