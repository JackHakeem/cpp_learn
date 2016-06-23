#include "RankingInfo.h"
#include "model/arena/ArenaConst.h"
#include "events/GameDispatcher.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "ArenaUI.h"
#include "socket/command/s36/SCMD361.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/TimerManage.h"
#include "utils/ScaleUtil.h"

const float FontSize = 20.0f;

RankingInfo::RankingInfo()
{
	_pContainer = 0;
	_canTake = false;
	_btnClose= 0 ;
}

RankingInfo::~RankingInfo()
{
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/arena/res_arena_closed.pvr.ccz");
}


bool RankingInfo::initWithParam(ArenaUI* pContainer)
{
	if (!LayerNode::init())
		return false;

	_pContainer = pContainer;
	return true;
}

// 更新即时排名 
void RankingInfo::updateRanking(int rank)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/arena/res_arena_closed.plist");
	//
	CCMenu* pLabel = (CCMenu*)this->getChildByTag(RankingInfoTAG_btnClose);
	if (pLabel)
		pLabel->removeFromParentAndCleanup(true);

	int index = ArenaConst::getIndexByRank(rank);
	char url[100];
	sprintf(url, "arena/closed_%d.png", index);
	
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName(url);
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName(url);
	CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this, 
		menu_selector(RankingInfo::clickBox) );
	_btnClose->setPosition(ccp(POSX(375),POSX(640-100)));

	CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
    buttonMenu->setPosition( CCPointZero );
	buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
	this->addChild(buttonMenu, RankingInfoZ_btnClose, RankingInfoTAG_btnClose);	
	//
	//
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(RankingInfoTAG_str0);
		if (!pLabel)
		{
			char str0[100];
			sprintf(str0, ValuesUtil::Instance()->getString("JJC027").c_str(), rank+1);
			pLabel = CCLabelTTF::labelWithString(str0, CCSizeMake(POSX(430), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(650), POSX(640-(75+25*0))));
			this->addChild(pLabel, RankingInfoZ_str0, RankingInfoTAG_str0);
			pLabel->setColor(ccc3(55, 21, 0));
		}	
		else
		{
			char str0[100];
			sprintf(str0, ValuesUtil::Instance()->getString("JJC027").c_str(), rank+1);
			pLabel->setString(str0);
		}
	}
	//
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(RankingInfoTAG_str1);
		if (!pLabel)
		{
			char str0[100];
			sprintf(str0, ValuesUtil::Instance()->getString("JJC028").c_str(), _pContainer->getRewardByRank(rank).c_str());
			pLabel = CCLabelTTF::labelWithString(str0, CCSizeMake(POSX(430), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(650), POSX(640-(75+25*1))));
			this->addChild(pLabel, RankingInfoZ_str1, RankingInfoTAG_str1);
			pLabel->setColor(ccc3(55, 21, 0));
		}	
		else
		{
			char str0[100];
			sprintf(str0, ValuesUtil::Instance()->getString("JJC028").c_str(), _pContainer->getRewardByRank(rank).c_str());
			pLabel->setString(str0);
		}

	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/arena/res_arena_closed.plist");
}

void RankingInfo::updatePackage(SCMD285* param)
{
	a_meRank = param->a_meRank;
	b_time = param->b_time;
	c_rewards = param->c_rewards;
	d_rankArr = param->d_rankArr;

			
	std::string _txtGetDate = TimerManage::formatServerTimeToDate(param->b_time);
	//
	{
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(RankingInfoTAG_str2);
		if (!pLabel)
		{
			char str0[100];
			sprintf(str0, ValuesUtil::Instance()->getString("JJC029").c_str(), _txtGetDate.c_str());
			pLabel = CCLabelTTF::labelWithString(str0, CCSizeMake(POSX(430), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(POSX(650), POSX(640-(75+25*2))));
			this->addChild(pLabel, RankingInfoZ_str2, RankingInfoTAG_str2);
			pLabel->setColor(ccc3(55, 21, 0));
		}	
	}

	_canTake = false;
	std::string rewardStr = "";
	for (int i = 0; i < param->c_rewards.size(); i++)
	{
		if (param->c_rewards[i].b_num > 0)
		{
			_canTake = true;
		}
	}

	if (_canTake)
	{
		if (_btnClose)
		{
			_btnClose->setIsEnabled(true);
		}		
	}
	else
	{
		
		if (_btnClose)
		{
			_btnClose->setIsEnabled(false);
		}
	}

	_pContainer->setGiftOpt(_canTake);
}


// 点击宝箱打开礼包面板
void RankingInfo::clickBox(CCObject* pSender)
{
	if (_pContainer)
		_pContainer->openGiftPanel();
}