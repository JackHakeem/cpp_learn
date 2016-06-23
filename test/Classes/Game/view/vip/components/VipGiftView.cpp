#include "VipGiftView.h"
#include "manager/TouchLayerEnum.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "utils/ScaleUtil.h"
#include "model/backpack/GoodsManager.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/com/GoodsToolTips.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/vo/GoodsDynamic.h"

VipGiftView::VipGiftView( int goodsId, int count )
{
	_goodsId = goodsId;
	_count = count;
	_popTip = NULL;

	initGrid();
}

VipGiftView::~VipGiftView()
{
	if (myInfo)
	{
		delete myInfo;
		myInfo = 0;
	}
	if(_popTip)
	{
		CC_SAFE_DELETE(_popTip);
	}
}

void VipGiftView::initGrid()
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

	if(_goodsId <= 0)
	{
		return;
	}

	//Add pic
	CCSprite *pPicSprite = new CCSprite();
	char pIcon[30];
	sprintf(pIcon, "assets/icon/goods/%d.png", _goodsId);
	if(pPicSprite && pPicSprite->initWithFile(pIcon))
	{
		pPicSprite->setAnchorPoint(CCPointZero);
		pPicSprite->setPosition(ccp(POSX(3), POSX(3)));
		this->addChild(pPicSprite);
		pPicSprite->release();
	}


	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(_goodsId);
	if (!goodBasic)
		return;

	//Add quality frame
	char qualityframe[50];
	sprintf(qualityframe, "pack/qualityfram_%d.png", goodBasic->quality);
	CCSprite *pQualitySprite = new CCSprite();
	if(pQualitySprite && pQualitySprite->initWithSpriteFrameName(qualityframe))
	{
		pQualitySprite->setAnchorPoint(CCPointZero);
		pQualitySprite->setPosition(CCPointZero);
		this->addChild(pQualitySprite);
		pQualitySprite->release();
	}


	//Add image menu
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("pack/frame_blank.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("pack/qualityfram_5.png");
	CCMenuItemSprite *pImageItem = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this,
		menu_selector(VipGiftView::onGoodsItemClick));
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

	//Add tip
	_popTip = new TipHelps();
	if(_popTip)
	{
		_popTip->init(true, TipConst::NORMAL);
		_popTip->setToolTips(this, this);
	}

	GoodsInfo* info = new GoodsInfo();
	/*info->sitGrid = goodInfo->a_sitGrid;
	info->id = goodInfo->b_id;*/
	info->goodId = _goodsId;//prototype ID
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


	// silver
	/*if(_goodsId == 2)
	{
	char newIntro[50];
	sprintf(newIntro, goodBasic->intro.c_str(), _count);
	goodBasic->intro = newIntro;
	}*/


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

		CC_SAFE_DELETE(dynamic);//jae note
	}
	else
	{
		info->explain = GoodsToolTips::getDefaultExplain(goodBasic, info->id, 0);
	}

	this->myInfo = info;
}

void VipGiftView::onGoodsItemClick( CCObject *pSender )
{
	this->timerStep();
}

void VipGiftView::timerStep()
{
	if(_popTip)
	{
		_popTip->rollOverHander();
	}
}

void VipGiftView::dispose()
{
	this->removeFromParentAndCleanup(true);
}