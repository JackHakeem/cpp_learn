#include "TraderGoodsItem.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "model/player/RoleManage.h"
#include "TraderView.h"

TraderGoodsItem::TraderGoodsItem()
{
	itemVo = 0;
	_nameEquipment = 0;
}

TraderGoodsItem::~TraderGoodsItem()
{}

bool TraderGoodsItem::initVo(TraderGoodsVo* guildVo)
{
	itemVo = guildVo;

	initView();

	return true;
}

void TraderGoodsItem::initView()
{
	this->setContentSize(CCSizeMake(POSX(127), POSX(216)));
	//
	SpriteNode* unlock = new SpriteNode();
	unlock->initWithSpriteFrameName("pack/unlock.png");
	this->addChild(unlock);
	unlock->setPosition(ccp(POSX(15),POSX(93)));
	unlock->setAnchorPoint(CCPointZero);
	unlock->release();

	char x[128]={0};
	sprintf(x, "trader_good0%d.png", itemVo->goodsId);
	_good = new SpriteNode();
	_good->initWithSpriteFrameName(x);
	this->addChild(_good);
	_good->setPosition(ccp(POSX(15),POSX(93)));
	_good->setAnchorPoint(CCPointZero);
	_good->release();

	{
		// name
		_nameEquipment = CCLabelTTF::labelWithString( itemVo->goodsName.c_str(),
			CCSizeMake( POSX(103), POSX(30) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(27) );
		_nameEquipment->setColor(  ccYELLOW  );
		_nameEquipment->setAnchorPoint(CCPointZero);
		_nameEquipment->setPosition( ccp( POSX(15), POSX(35+20) ) );
		addChild( _nameEquipment );
	}

	int silver = static_cast<int>( (4000*(RoleManage::Instance()->roleLev()/10))
		* TraderView::GetGoodQuality(itemVo->goodsId) );
	int pop = TraderView::getBasePop(itemVo->goodsId);
	CCLabelTTF* silLabel = CCLabelTTF::labelWithString( LangManager::getText("TRD108", silver).c_str(),
		CCSizeMake( POSX(140), POSX(24) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
	silLabel->setColor(  ccWHITE  );
	silLabel->setAnchorPoint(CCPointZero);
	silLabel->setPosition( ccp( POSX(0), POSX(35-10+3) ) );
	addChild( silLabel );

	silLabel = CCLabelTTF::labelWithString( LangManager::getText("TRD109", pop).c_str(),
		CCSizeMake( POSX(140), POSX(24) ), CCTextAlignmentCenter, g_sSimHeiFont, POSX(20) );
	silLabel->setColor(  ccWHITE  );
	silLabel->setAnchorPoint(CCPointZero);
	silLabel->setPosition( ccp( POSX(0), POSX(35-26) ) );
	addChild( silLabel );

	this->setIsTouchEnabled(true);
}

bool TraderGoodsItem::init()
{
	if (!LayerNode::init())
		return false;
	
	return true;
}


