#include "AppointBlessView.h"
#include "CCMenuItem.h"
#include "CCMenu.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "CCSprite.h"
#include "model/backpack/GoodsManager.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/appoint/vo/GoodsVo.h"
#include "GoodsView.h"
#include "CCUIBackground.h"
#include "model/appoint/AppointManager.h"
#include "model/appoint/vo/AppointBlessVo.h"
#include "events/GameDispatcher.h"

const int POS_ITEM_CELL_X = 84;
const int POS_ITEM_CELL_Y = 290;
const int SIZE_DIS_ITEM_X = 8;
const int SIZE_DIS_ITEM_Y = 12;

const int TAG_BUTTON_BASE = 1050;
const int TAG_BUTTON_CLOSE = 1100;

const int TAG_PARENT = 1001;
void AppointBlessView::initView()
{
	this->setIsTouchEnabled(true);

	CCLayer *pParent = new CCLayer();
	pParent->setAnchorPoint(CCPointZero);
	pParent->setPosition(POS(ccp(0, 80), ScaleUtil::CENTER_TOP));
	this->addChild(pParent, 0, TAG_PARENT);
	pParent->release();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCUIBackground *pBackground1 = new CCUIBackground();
	pBackground1->initWithSpriteFrame("ui.png", ccp(POSX(55), 0), ccp(POSX(6), POSX(7)), CCSizeMake(POSX(960 - 110), POSX(440)));
	pParent->addChild(pBackground1);
	pBackground1->release();

	CCUIBackground *pBackground2 = new CCUIBackground();
	pBackground2->initWithSpriteFrame("ui2.png", ccp(POSX(65), POSX(10)), CCPointZero, CCSizeMake(POSX(960 - 130), POSX(420)));
	pParent->addChild(pBackground2);
	pBackground2->release();

	CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
	CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
	CCMenuItemSprite *pCloseImage = CCMenuItemSprite::itemFromNormalSprite(
		pCloseNormalSprite,
		pClosePressedSprite,
		this, 
		menu_selector(AppointBlessView::onMenuItemClickListener) );
	pCloseImage->setPosition(ccp(POSX(960) - pCloseImage->getContentSize().width,
		POSX(430)));
	pCloseImage->setTag(TAG_BUTTON_CLOSE);

	CCMenu *buttonMenu = CCMenu::menuWithItem(pCloseImage);
	buttonMenu->setPosition(ccp(0, 0));
	buttonMenu->setTouchLayer(-2001);
	pParent->addChild(buttonMenu, 0, TAG_BUTTON_CLOSE);

	buildList();
}

void AppointBlessView::buildList()
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	std::list<AppointBlessVo *> &list = AppointManager::Instance()->_appointBlessArr;
	std::list<AppointBlessVo *>::iterator it;
	int id = 0;
	for(it = list.begin(); it != list.end(); ++it)
	{
		AppointBlessVo *pBlessVo = (AppointBlessVo *) *it;
		if(!pBlessVo)
			continue;

		CCLayer *pItemCell = createItemCell(id, pBlessVo);
		if(pItemCell)
		{
			pParent->addChild(pItemCell);
			pItemCell->release();
		}

		++id;
		if(id > 2)
		{
			id = 0;
		}
	}
}

void AppointBlessView::updateGoodsState( int lev )
{

}

void AppointBlessView::updateExchangeState( int blessValue )
{
	CCLayer *pParent = (CCLayer *) this->getChildByTag(TAG_PARENT);
	if(!pParent)
		return;

	std::list<AppointBlessVo *> &list = AppointManager::Instance()->_appointBlessArr;
	std::list<AppointBlessVo *>::iterator it;
	int id = 0;
	for(it = list.begin(); it != list.end(); ++it)
	{
		AppointBlessVo *pBlessVo = (AppointBlessVo *) *it;
		if(!pBlessVo)
			continue;

		int tag = id + pBlessVo->goodsType * 3;
		CCNode *pItemCell = pParent->getChildByTag(tag);
		if(!pItemCell)
			continue;

		CCMenu *pMenu = (CCMenu *) pItemCell->getChildByTag(tag + TAG_BUTTON_BASE);
		if(!pMenu)
			continue;

		CCMenuItemImage *pMenuImage = (CCMenuItemImage *) pMenu->getChildByTag(tag + TAG_BUTTON_BASE);
		if(!pMenuImage)
			continue;

		pMenuImage->setIsEnabled(pBlessVo->blessValue <= blessValue);

		++id;
		if(id > 2)
		{
			id = 0;
		}
	}
}

CCLayer * AppointBlessView::createItemCell( int id, AppointBlessVo *pData )
{
	if(!pData)
	{
		return NULL;
	}
	AppointManager *pAppointManager = AppointManager::Instance();
	int type = pData->goodsType;
	int tag = id + type * 3;
	CCLayer *pItemCellLayer = new CCLayer();
	pItemCellLayer->setPosition(ccp(POSX(POS_ITEM_CELL_X + (type * (384 + SIZE_DIS_ITEM_X))),
		POSX(POS_ITEM_CELL_Y - (id * (120 + SIZE_DIS_ITEM_Y)))));
	pItemCellLayer->setAnchorPoint(CCPointZero);
	pItemCellLayer->setTag(tag);

	//Add bg
	CCUIBackground *pBackground = new CCUIBackground();
	pBackground->initWithSpriteFrame("ui2.png", CCPointZero, CCPointZero, CCSizeMake(POSX(384), POSX(120)));
	if(pBackground)
	{
		pItemCellLayer->addChild(pBackground);
		pBackground->release();
	}

	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(pData->goodsId);
	if(!goodBasic)
	{
		return pItemCellLayer;
	}

	GoodsVo *pGoodsVo = new GoodsVo();
	pGoodsVo->id = pData->goodsId;
	pGoodsVo->quality = goodBasic->quality;
	char pIcon[128];
	//sprintf(pIcon, "goods/%d.png", pData->goodsId);
	sprintf(pIcon, "assets/icon/goods/%d.png", pData->goodsId); // LH20130111
	pGoodsVo->icon  = pIcon;
	GoodsView *pIconView = new GoodsView(pGoodsVo, true);
	pIconView->setAnchorPoint(CCPointZero);
	pIconView->setPosition(ccp(POSX(8), POSX(10)));
	pItemCellLayer->addChild(pIconView);
	pIconView->release();

	//116 74
	//Add name label
	ccColor3B color;
	
	switch(goodBasic->quality)
	{
	case 6:
		color = ccc3(255, 0, 0);
		break;
	case 5:
		color = ccc3(255, 138, 0);
		break;
	default:
		color = ccc3(228, 0, 255);
		break;
	}

	CCLabelTTF *pNameLabel = CCLabelTTF::labelWithString(
		goodBasic->goodName.c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(20));
	pNameLabel->setColor(color);
	pNameLabel->setPosition(ccp(POSX(116), POSX(74)));
	pNameLabel->setAnchorPoint(CCPointZero);
	pItemCellLayer->addChild(pNameLabel);

	//Add bless value label
	char pBlessValue[100];
	sprintf(pBlessValue, "%d", pData->blessValue);
	CCLabelTTF *pBlessLabel = CCLabelTTF::labelWithString(
		pBlessValue,
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(20));
	pBlessLabel->setColor(ccc3(248, 202, 113));
	pBlessLabel->setPosition(ccp(POSX(116), POSX(24)));
	pBlessLabel->setAnchorPoint(CCPointZero);
	pItemCellLayer->addChild(pBlessLabel);

	//Add exchange button

	
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(pNormalSprite && pPressedSprite && pSelectdSprite)
	{
		CCMenuItemSprite *pExchangeMenuImage = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			pSelectdSprite,
			this,
			menu_selector(AppointBlessView::onMenuItemClickListener));
		pExchangeMenuImage->setTag(TAG_BUTTON_BASE + tag);
		pExchangeMenuImage->setPosition(ccp(POSX(274), POSX(30)));
		pExchangeMenuImage->setAnchorPoint(CCPointZero);
		pExchangeMenuImage->setScaleX(0.826f);
		CCMenu *pExchangeMenu = CCMenu::menuWithItems(pExchangeMenuImage, NULL);
		pExchangeMenu->setPosition(CCPointZero);
		pExchangeMenu->setTouchLayer(-2001);
		pExchangeMenuImage->setIsEnabled(pData->blessValue <= pAppointManager->getBlessValue());
		pItemCellLayer->addChild(pExchangeMenu, 0, TAG_BUTTON_BASE + tag);
	}
	

	CCLabelTTF *pExchangeLabel = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("APT025").c_str(),
		CCSizeMake(POSX(80), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	pExchangeLabel->setColor(ccc3(255, 255, 255));
	pExchangeLabel->setPosition(ccp(POSX(324), POSX(54)));
	pItemCellLayer->addChild(pExchangeLabel);
	return pItemCellLayer;
}

AppointBlessView::AppointBlessView()
{
    this->setIsTouchEnabled(true);
}

void AppointBlessView::onMenuItemClickListener( CCObject *pSender )
{
	CCMenu *pMenu = (CCMenu *) pSender;
	if(!pMenu)
		return;

	int tag = pMenu->getTag();
	switch(tag)
	{
	case TAG_BUTTON_BASE + 0:
	case TAG_BUTTON_BASE + 1:
	case TAG_BUTTON_BASE + 2:
	case TAG_BUTTON_BASE + 3:
	case TAG_BUTTON_BASE + 4:
	case TAG_BUTTON_BASE + 5:
		{
			std::list<AppointBlessVo *> &list = AppointManager::Instance()->_appointBlessArr;
			std::list<AppointBlessVo *>::iterator it;
			int goodsId = 0;
			int id = tag - TAG_BUTTON_BASE;
			for(it = list.begin(); it != list.end(); ++it)
			{
				if(id == 0)
				{
					AppointBlessVo *pBlessVo = (AppointBlessVo *) *it;
					if(pBlessVo)
					{
						goodsId = pBlessVo->goodsId;
					}
					break;
				}
				-- id;
			}
			int *pInt = new int;
			*pInt = goodsId;
			GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::BLESS_EXCHANGE, pInt);
			CC_SAFE_DELETE(pInt);
		}
		break;

	case TAG_BUTTON_CLOSE:
		this->removeFromParentAndCleanup(true);
		break;
	}
}

bool AppointBlessView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void AppointBlessView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -2000, true);
}

