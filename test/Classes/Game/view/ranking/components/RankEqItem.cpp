#include "RankEqItem.h"
#include "cocos2d.h"
#include "BaseType.h"
#include "utils/TipHelps.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/com/GoodsToolTips.h"
#include "manager/TouchLayerEnum.h"

RankEqItem::RankEqItem()
{
	myTip = 0;
}

RankEqItem::~RankEqItem()
{
	CC_SAFE_DELETE(myInfo);
	CC_SAFE_DELETE(myTip);
}

bool RankEqItem::init(const EquipItemVo& equip)
{
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		//add equipment quality frame
		char path[64] = "\0";
		sprintf(path, "pack/qualityfram_%d.png", equip.quality);
		CCSprite* pQuality = CCSprite::spriteWithSpriteFrameName(path);
		CC_BREAK_IF(! pQuality);
		this->setvisibleSize(pQuality->getContentSize());
		this->setContentSize(pQuality->getContentSize());
		pQuality->setAnchorPoint(CCPointZero);
		pQuality->setPosition(CCPointZero);
		this->addChild(pQuality);

		CCFiniteTimeAction* pActionFadeOut = CCFadeOut::actionWithDuration(0.5f);
		CCFiniteTimeAction* pActionFadeIn = pActionFadeOut->reverse();
		CCAction* pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pActionFadeOut, pActionFadeIn));
		pQuality->runAction(pAction);

		//add equipment icon
		//sprintf(path, "goods/%d.png", equip.id);
		//CCSprite* pEquip = CCSprite::spriteWithSpriteFrameName(path);

		// LH20130110
		sprintf(path, "assets/icon/goods/%d.png", equip.id);
		CCSprite* pEquip = CCSprite::spriteWithFile(path);

		CC_BREAK_IF(! pEquip);
		CCSize size = this->getContentSize();
		pEquip->setPosition(ccp(size.width / 2.0f, size.height / 2.0f));
		this->addChild(pEquip);

		//add tip
		CC_BREAK_IF(! g_pGoodsManager || ! g_pGoodsDynamicManager);
		myTip = new TipHelps();
		myTip->init(true, TipConst::NORMAL, false);
		myTip->setToolTips(this, this);

		GoodsInfo* info = new GoodsInfo();
		info->goodId = equip.id;
		info->name = equip.name;
		info->type = 2;
		info->equip_type = equip.type;
		info->quality = equip.quality;
		info->strengthen = equip.lev;
		info->stamina = equip.stamina;
		info->intellect = equip.intellect;
		info->wrist = equip.wrist;
	
		GoodsBasic* pGoodsBasic = g_pGoodsManager->getBasicGood(equip.id);
		GoodsDynamic* dynamic = g_pGoodsDynamicManager->createDynamic(info, pGoodsBasic);
		info->explain = GoodsToolTips::getGoodsTooltips(pGoodsBasic, dynamic);

		this->myInfo = info;

		//add click event
		CCMenuItem* pClickItem = CCMenuItem::itemWithTarget(this, menu_selector(RankEqItem::onClickItem));
		CC_BREAK_IF(! pClickItem);
		pClickItem->setContentSize(this->getContentSize());
		pClickItem->setAnchorPoint(CCPointZero);
		pClickItem->setPosition(CCPointZero);
		
		CCMenu* pMenu = CCMenu::menuWithItem(pClickItem);
		CC_BREAK_IF(! pMenu);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		pMenu->setTouchLayer(TLE::WindowLayer_Common_btn);
		this->addChild(pMenu);
		return true;
	} while (0);

	CCLOG("RankEqItem: init equipment false!");
	return false;
}

void RankEqItem::onClickItem(CCObject* node)
{
	myTip->rollOverHander();
}

