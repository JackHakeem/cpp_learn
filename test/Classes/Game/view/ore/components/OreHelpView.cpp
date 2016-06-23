#include "OreHelpView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "view/ore/OreMediator.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "socket/network/GameServerSocket.h"
#include "manager/ViewManager.h"
#include "OreView.h"
#include "view/dungeonEntrys/components/DungeonGUAMsgItem.h"

OreHelpView::OreHelpView()
{}

OreHelpView::~OreHelpView()
{}

bool OreHelpView::init()
{
	if (!LayerNode::init())
		return false;

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
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(175), POSX(38)), ccp(0,0), CCSizeMake(POSX(610), POSX(564)));
	_pContainer->addChild(_bg1, 1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(175+24), POSX(38+25)), ccp(0,0), CCSizeMake(POSX(560), POSX(516)));
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
			menu_selector(OreHelpView::clickClose) );
		_btnClose->setPosition(ccp(POSX(175+610), POSX(38+564)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);		
	}

	for (int i = 0; i < 4; i++)
	{
		char strname[10];
		sprintf(strname, "ORE3%d", 3+i);
		char str[180];
		sprintf(str, ValuesUtil::Instance()->getString(strname).c_str());
		DungeonGUAMsgItem* node = DungeonGUAMsgItem::itemStrFactory(str, ccc3(255,255,255));
		_pContainer->addChild(node, 8);
		node->setPosition(ccp(POSX(175+34), POSX(38+500 - i*30)));
	}

	return true;
}

void OreHelpView::clickClose(CCObject* pSender)
{
	//show
	if (ViewManager::getInstance()->oreView)
		ViewManager::getInstance()->oreView->setIsVisible(true);
	//delete
	if (this->getParent())
		this->removeFromParentAndCleanup(true);
}