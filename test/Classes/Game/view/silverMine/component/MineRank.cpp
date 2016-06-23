#include "MineRank.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/LangManager.h"
#include "manager/LayerManager.h"

MineRank::MineRank()
{
	_txtOwn = 0;
	
}

MineRank::~MineRank()
{}

bool MineRank::init()
{
	if (!LayerNode::init())
		return false;
	//bg1
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("ui2.png", ccp(POSX(240), POSX(640-570)),ccp(6,7),
		CCSizeMake(POSX(960-240*2), POSX(570-70)));
	this->addChild(_bg1, 0);
	_bg1->release();
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	this->addChild(blackBG, -1);
	blackBG->setPosition(ccp(0, 0));
	//
	{
		SpriteNode* title = new SpriteNode();
		title->initWithSpriteFrameName("rank_title.png");
		title->setPosition(ccp(POSX(960/2), POSX(550)));
		this->addChild(title, 1);
		title->release();
	}
	//
	//close
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite, 
			this, 
			menu_selector(MineRank::close) );
		_btn->setPosition(ccp(POSX(960-240), POSX(570)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_silvermine_rank);
		this->addChild(buttonMenu);	
	}
	//silver
	{
		char str[50];
		sprintf(str, "%s %d", ValuesUtil::Instance()->getString("SLM057").c_str(), 0);
		_txtOwn = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentCenter, "Arial", POSX(22.0f));
		_txtOwn->setPosition(ccp(POSX(960/2), POSX(500)));
	//	_txtOwn->setAnchorPoint(ccp(0, 0));
		this->addChild(_txtOwn, 2);
		_txtOwn->setColor(ccc3(255, 210, 40));	
	}

	return true;
}

void MineRank::updateSilver(int silver)
{
	if (!_txtOwn)
		return;
	char str[50];
	sprintf(str, "%s %d", ValuesUtil::Instance()->getString("SLM057").c_str(), silver);
	_txtOwn->setString(str);
}

void MineRank::close(CCObject* pSender)
{
	MineRank* oldp = (MineRank*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineRank);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}

void MineRank::updateRank(std::list<SCMD367Node>&  arr)
{
	// "txt_No00"  "txt_No01"
	// txt_No10   txt_No11

	for (int i = 0; i < itemarr.size(); i++)
	{
		LayerNode* item = itemarr[i];
		if (item)
			item->removeFromParentAndCleanup(true);
		itemarr[i] = 0;
	}

	int count = arr.size();
	int index = 0;
	for (std::list<SCMD367Node>::iterator it = arr.begin(); it != arr.end(); it++, index++)
	{
		SCMD367Node node = *it;
		LayerNode* item = new LayerNode();
		item->init();
		this->addChild(item);
		item->release();
		item->setPosition(ccp(POSX(280), POSX(450 - index*40)));
		itemarr.push_back(item);
		//
		{
			char str[50];
			sprintf(str, "%d. %s", index+1, node.c_playerName.c_str());
			CCLabelTTF* _txt = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
			_txt->setPosition(ccp(POSX(0), POSX(0)));
			_txt->setAnchorPoint(ccp(0, 0));
			item->addChild(_txt, 1);
			_txt->setColor(ccc3(240, 210, 68));	
		}
		//
		{
			char str[20];
			sprintf(str, "%d", node.d_silver);
			CCLabelTTF* _txt = CCLabelTTF::labelWithString(str, CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
			_txt->setPosition(ccp(POSX(200), POSX(0)));
			_txt->setAnchorPoint(ccp(0, 0));
			item->addChild(_txt, 1);
			_txt->setColor(ccc3(240, 210, 68));	
		}
	}
}
