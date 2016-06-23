#include "GiftPanel.h"
#include "ArenaUI.h"
#include "manager/LayerManager.h"
#include "model/arena/ArenaConst.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "socket/command/s28/SCMD285.h"
#include "model/arena/ArenaManage.h"
#include "utils/ScaleUtil.h"

const float FontSize = 28.0f;
const float FontSize_0 = 36.0f;

GiftPanel::GiftPanel()
{
	_btnGet = 0;
	_pContainer = 0;
	pBtnGetLabel =0;
}

GiftPanel::~GiftPanel()
{

}

bool GiftPanel::initWithParam(ArenaUI* pContainer)
{
	if (!LayerNode::init())
		return false;
	
	_pContainer = pContainer;

	this->setPosition(ccp(POSX((960-600)/2), POSX(640-525)));
	this->setContentSize(CCSizeMake(POSX(600), POSX(360)));

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("ui.png", ccp(0, 0), ccp(POSX(6), POSX(7)), CCSizeMake(POSX(600), POSX(360)));
	this->addChild(_bg1, GiftPanelZ_bg1, GiftPanelTAG_bg1);
	//Doyang 20120712
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(10), POSX(10)), ccp(0,0), CCSizeMake(POSX(580), POSX(260)));
	this->addChild(_bg2, GiftPanelZ_bg2, GiftPanelTAG_bg2);
	//Doyang 20120712
	_bg2->release();


	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(GiftPanel::clickClose) );
		_btnClose->setPosition(ccp(POSX(600), POSX(360)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer-1);
		this->addChild(buttonMenu, GiftPanelZ_closebtn, GiftPanelTAG_closebtn);		
	}

	//
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnGet = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
			menu_selector(GiftPanel::clickGet) );
			_btnGet->setPosition(ccp(POSX(500), POSX(210)));

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btnGet, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::TipsLayer-1);
			this->addChild(buttonMenu, GiftPanelZ_getbtn, GiftPanelTAG_getbtn);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC030").c_str(), CCSizeMake(POSX(60), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(_btnGet->getContentSize().width/2, _btnGet->getContentSize().height/2));
			_btnGet->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(254, 189, 0));
			pBtnGetLabel =  pLabel;
		}
	}

	//GiftPanelZ_rank_title
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC031").c_str(), CCSizeMake(POSX(160), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(POSX(250), POSX(300)));
		this->addChild(pLabel, GiftPanelZ_rank_title, GiftPanelTAG_rank_title);
		pLabel->setColor(ccc3(254, 189, 0));		
	}
	//GiftPanelZ_txtReward_title
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC032").c_str(), CCSizeMake(POSX(160), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(POSX(210), POSX(210)));
		this->addChild(pLabel, GiftPanelZ_txtReward_title, GiftPanelTAG_txtReward_title);
		pLabel->setColor(ccc3(254, 189, 0));		
	}
	//GiftPanelTAG_str0
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC033").c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(POSX(300), POSX(165)));
		this->addChild(pLabel, GiftPanelZ_str0, GiftPanelTAG_str0);
		pLabel->setColor(ccc3(254, 189, 0));		
	}
	return true;
}

void GiftPanel::clickGet(CCObject* pSender)
{
	_pContainer->dispatchEvent(ArenaConst::GIFT_PACKAGE, 0);
}

void GiftPanel::clickClose(CCObject* pSender)
{
	GiftPanel* pGP = (GiftPanel*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_rankReward);
	if (pGP)
	{
		pGP->setIsVisible(false);
	}
}

// 上一次排名
void GiftPanel::update(SCMD285* data, ArenaUI* pContainer)
{
	if (!data)
		return;

	_pContainer = pContainer;

	if( data->a_meRank>= 1000)
	{
		data->a_meRank = 1000;
	}

//	int d1 = (data->a_meRank+1)/1000 ;
//	d1 = d1>0?d1:10;
//	int d2 = ((data->a_meRank+1)%1000)/100;
//	d2 = d2>0?d2:10;
//	int d3 = ((data->a_meRank+1)%100)/10;
//	d3 = d3>0?d3:10;
//	int d4 = (data->a_meRank+1)%10;
//	d4 = d4>0?d4:10;

	//
	{
		char _txtRank[20];
		sprintf(_txtRank, "%04d", data->a_meRank+1);
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(GiftPanelTAG_txtReward);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(_txtRank, CCSizeMake(POSX(230), POSX(FontSize_0)), CCTextAlignmentLeft, "Arial", POSX(FontSize_0));
			pLabel->setPosition(ccp(POSX(420), POSX(300)));
			this->addChild(pLabel, GiftPanelZ_rank, GiftPanelTAG_rank);
			pLabel->setColor(ccc3(254, 0, 0));			
		}
		else
		{
			pLabel->setString(_txtRank);
		}	
	}

	//
	{
		std::string _txtReward = _pContainer->getRewardByRank(data->a_meRank);

		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(GiftPanelTAG_txtReward);
		if (!pLabel)
		{
			pLabel = CCLabelTTF::labelWithString(_txtReward.c_str(), CCSizeMake(POSX(400), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(330), POSX(210)));
			this->addChild(pLabel, GiftPanelZ_txtReward, GiftPanelTAG_txtReward);
			pLabel->setColor(ccc3(254, 0, 0));			
		}
		else
		{
			pLabel->setString(_txtReward.c_str());
		}	
	}

	//
	setRankingTip(data->a_meRank);
}

void GiftPanel::setRankingTip(int rank)
{
	_cfgRankVo = ArenaManage::Instance()->getCfgRank(rank);
	if (!_cfgRankVo)
		return;

	int index = ArenaConst::getIndexByRank(rank);
	char url[100];
	sprintf(url, "open/open_%d.png", index);
	SpriteNode* boxOpen = new SpriteNode();
	boxOpen->initWithSpriteFrameName(url);
	boxOpen->setPosition(ccp(POSX(90), POSX(290)));
	boxOpen->setScale(1.3f);
	this->addChild(boxOpen, GiftPanelZ_boxOpen, GiftPanelTAG_boxOpen);
	boxOpen->release();

	for (int i = 0; i < _cfgRankVo->interests.size(); i++)
	{
		int otherRank = _cfgRankVo->interests[i];// 从0开始 
		index = ArenaConst::getIndexByRank(otherRank+1);
		sprintf(url, "reward/reward_%d.png", index);

		SpriteNode* pic = new SpriteNode();
		pic->initWithSpriteFrameName(url);
		pic->setPosition(ccp(POSX(110 + i*140), POSX(100)));
		pic->setScale(1.7f);
		this->addChild(pic, GiftPanelZ_boxRank0+i, GiftPanelTAG_boxRank0+i);
		pic->release();
	}


}

void GiftPanel::setGiftOpt(bool value)
{
	if (_btnGet)
	{
		_btnGet->setIsEnabled(value);
	}

	if (pBtnGetLabel)
	{
		if (value)
		{
			pBtnGetLabel->setColor(ccc3(254, 189, 0));
		}
		else
		{
			pBtnGetLabel->setColor(ccc3(128, 128, 128));
		}		
	}

}