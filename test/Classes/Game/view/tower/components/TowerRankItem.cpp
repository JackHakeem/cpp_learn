#include "TowerRankItem.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"

const float w_frame = 602;
const float h_frame = 39.0f;
const float FontSize = 30.0f;
const float FontSize3 = 20.0f;
const float FontSize2 = 24.0f;

TowerRankItem::TowerRankItem()
{
	itemVo = 0;
}

TowerRankItem::~TowerRankItem()
{}

bool TowerRankItem::init(TowerRankItemVo* guildVo)
{
	if (!LayerNode::init())
		return false;

	itemVo = guildVo;

	initView();

	return true;
}

void TowerRankItem::initView()
{
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(w_frame), POSX(h_frame-3)));
	this->addChild(_bg1, TowerRankItemZ_bg1, TowerRankItemTAG_bg1);
	_bg1->release();

	//CCLayerColor* pCol = CCLayerColor::layerWithColorWidthHeight(ccc4(255,0,0,100),POSX(w_frame), POSX(h_frame));
	//this->addChild(pCol);


	cocos2d::ccColor3B labelcolor = ccWHITE;
	float fOffset = 20.0f+35.0f;
	float fH = POSX(FontSize3+4);
	////排名
	//{
	//	char tmp[10];
	//	sprintf( tmp, "%d", itemVo->rank );
	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
	//		tmp,
	//		CCSizeMake(POSX(58),
	//		fH),
	//		CCTextAlignmentCenter,
	//		"Arial",
	//		POSX(FontSize3)
	//		);
	//	pLabel->setAnchorPoint(ccp(0, 0));
	//	pLabel->setPosition(ccp(POSX(20-fOffset), POSX(15-4)));
	//	this->addChild(pLabel);
	//	pLabel->setColor(labelcolor);		
	//}

	//层级
	{
		char tmp[10];
		sprintf( tmp, "%d", itemVo->floor );
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			tmp,
			CCSizeMake(POSX(58),
			fH),
			CCTextAlignmentCenter,
			"Arial",
			POSX(FontSize3)
			);
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(80-fOffset), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}

	//玩家
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			itemVo->name.c_str(),
			CCSizeMake(POSX(146),
			fH),
			CCTextAlignmentCenter,
			"Arial",
			POSX(FontSize3)
			);
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(140-fOffset), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}

	//公会
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			itemVo->guild.c_str(),
			CCSizeMake(POSX(146),
			fH),
			CCTextAlignmentCenter,
			"Arial",
			POSX(FontSize3)
			);
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(290-fOffset), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}

	//等级
	{
		char tmp[10];
		sprintf( tmp, "%d", itemVo->lev );
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			tmp,
			CCSizeMake(POSX(57),
			fH),
			CCTextAlignmentCenter,
			"Arial",
			POSX(FontSize3)
			);
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(440-fOffset), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}


	//留名时间
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			itemVo->date.c_str(),
			CCSizeMake(POSX(104),
			fH),
			CCTextAlignmentCenter,
			"Arial",
			POSX(FontSize3)
			);
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(500-fOffset), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}
}
//
//
//void TowerRankItem::onEnter()
//{
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Common, true);
//	CCLayer::onEnter();
//}
//
//void TowerRankItem::onExit()
//{
//	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
//	CCLayer::onExit();
//}	
//
//CCRect TowerRankItem::rect()
//{
//	CCSize s = this->getContentSize();
//	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
//}
//
//bool TowerRankItem::containsTouchLocation(CCTouch* touch)
//{
//	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
//}
//
//bool TowerRankItem::ccTouchBegan(CCTouch* touch, CCEvent* event)
//{
//	if ( !containsTouchLocation(touch) ) return false;
//
//	return true;
//}
//
//void TowerRankItem::ccTouchMoved( CCTouch* touch, CCEvent* event )
//{
//
//}
//
//void TowerRankItem::ccTouchEnded(CCTouch* touch, CCEvent* event)
//{
//
//}