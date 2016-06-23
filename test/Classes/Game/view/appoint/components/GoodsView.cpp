#include "GoodsView.h"
#include "manager/TouchLayerEnum.h"
#include "../AppointMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "utils/ScaleUtil.h"
#include "model/backpack/GoodsManager.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/com/GoodsToolTips.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"

const float DOUBLE_CLICK_DIS = 0.3f;

GoodsView::GoodsView( GoodsVo *pGoodsVo, bool isAppointBlessView /*= false*/ )
{
    
    
    
	_numClick = 0;
	_popTip = NULL;
	goodsVo = pGoodsVo;
	_isAppointBlessView = isAppointBlessView;
	initGrid();
}

GoodsView::~GoodsView()
{
	if(_popTip)
	{
		CC_SAFE_DELETE(_popTip);
	}
	if(goodsVo)
	{
		CC_SAFE_DELETE(goodsVo);
	}
}

void GoodsView::initGrid()
{
	//Add background
	CCSprite *pBackgroundSprite = new CCSprite();
	if(pBackgroundSprite && pBackgroundSprite->initWithSpriteFrameName("pack/unlock.png"))
	{
		pBackgroundSprite->setAnchorPoint(CCPointZero);
		pBackgroundSprite->setPosition(CCPointZero);
		this->addChild(pBackgroundSprite);
		pBackgroundSprite->release();
	}

	if(!goodsVo)
	{
		return;
	}

	//Add pic
	CCSprite *pPicSprite = new CCSprite();
	// LH20130111
	//if(pPicSprite && pPicSprite->initWithSpriteFrameName(goodsVo->icon.c_str()))
	if(pPicSprite && pPicSprite->initWithFile(goodsVo->icon.c_str()))
	{
		pPicSprite->setAnchorPoint(CCPointZero);
		pPicSprite->setPosition(ccp(POSX(3), POSX(3)));
		this->addChild(pPicSprite);
		pPicSprite->release();
	}

	//Add quality frame
	char qualityframe[50];
	sprintf(qualityframe, "pack/qualityfram_%d.png", goodsVo->quality);
	CCSprite *pQualitySprite = new CCSprite();
	if(pQualitySprite && pQualitySprite->initWithSpriteFrameName(qualityframe))
	{
		pQualitySprite->setAnchorPoint(CCPointZero);
		pQualitySprite->setPosition(CCPointZero);
		this->addChild(pQualitySprite);
		pQualitySprite->release();
	}

	if(!_isAppointBlessView)
	{
		//Add image menu
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("pack/frame_blank.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("pack/qualityfram_5.png");
		CCMenuItemSprite *pImageItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(GoodsView::onGoodsItemClick));
		if(pImageItem)
		{
			pImageItem->setAnchorPoint(CCPointZero);
			pImageItem->setPosition(CCPointZero);
			CCMenu *pMenu = CCMenu::menuWithItem(pImageItem);
			if(pMenu)
			{
				pMenu->setTouchLayer(TLE::WindowLayer_AppointView);
				pMenu->setPosition(CCPointZero);
				this->addChild(pMenu);
			}
		}
	}

	//Add tip
	_popTip = new TipHelps();
	if(_popTip)
	{
		_popTip->init(true, TipConst::NORMAL);
		_popTip->setToolTips(this, this);
	}

	if(!goodsVo)
		return;
	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(goodsVo->id);
	if (!goodBasic)
		return;
	GoodsInfo* info = new GoodsInfo();
	/*info->sitGrid = goodInfo->a_sitGrid;
	info->id = goodInfo->b_id;*/
	info->goodId = goodsVo->id;//prototype ID
	/*info->number = goodInfo->d_number;
	info->strengthen = goodInfo->e_superLv;
	info->stamina = goodInfo->f_stamina;
	info->wrist = goodInfo->g_wrist;
	info->intellect = goodInfo->h_intellect;*/
	//info->explain = 0;
	info->name = goodBasic->goodName;
	info->type = goodBasic->type;
	info->equip_type = goodBasic->equip_type;
	info->quality = goodBasic->quality; 
	if (goodBasic->type == 3)
	{//fragments
		info->explain = GoodsToolTips::getExplain(goodBasic, false, 1);
		// Add count
		char pCount[10];
		sprintf(pCount, "%d", 1);
		CCLabelTTF *pCountLabel = CCLabelTTF::labelWithString(
			pCount,
			CCSizeMake(POSX(20), POSX(20)),
			CCTextAlignmentLeft,
			"Arial",
			POSX(20));
		pCountLabel->setColor(ccc3(255, 255, 255));
		pCountLabel->setAnchorPoint(CCPointZero);
		pCountLabel->setPosition(ccp(POSX(74), POSX(4)));
		this->addChild(pCountLabel);
	}
	else if (g_pGoodsDynamicManager->getGoodsDynamic(info->id) != 0)
	{
		info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, g_pGoodsDynamicManager->getGoodsDynamic(info->id));
	}
	else if (goodBasic->type == 2)//equipment
	{
		GoodsDynamic* dynamic = g_pGoodsDynamicManager->createDynamic(info, goodBasic);
		if (!dynamic)
		{
			cocos2d::CCLog("!dynamic   BagProxy::updateGoodList");
		}
		info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, dynamic);
	}
	else
	{
		info->explain = GoodsToolTips::getDefaultExplain(goodBasic, info->id, 0);
	}

	this->myInfo = info;
}

void GoodsView::onGoodsItemClick( CCObject *pSender )
{
	_numClick ++;
	if(_numClick >=2)
	{
		this->stopAllActions();
		doubleClick();
		return;
	}
	CCDelayTime *pDelayActoin = CCDelayTime::actionWithDuration(DOUBLE_CLICK_DIS);
	CCCallFunc *pCallbackFuc = CCCallFunc::actionWithTarget(this, callfunc_selector(GoodsView::timerStep));
	CCSequence *pAction = CCSequence::actionOneTwo(pDelayActoin, pCallbackFuc);
	this->runAction(pAction);
}

void GoodsView::timerStep()
{
	_numClick = 0;
	if(_popTip)
	{
		_popTip->rollOverHander();
	}
}

void GoodsView::doubleClick()
{
	_numClick = 0;
	AppointMediator *pAppointMediator = (AppointMediator *) g_pFacade->retrieveMediator(AppFacade_APPOINT_MEDIATOR);
	if(pAppointMediator && goodsVo)
	{
		pAppointMediator->onGoodsDoubleClick(goodsVo->id);
	}
}

void GoodsView::dispose()
{
	this->removeFromParentAndCleanup(true);
}