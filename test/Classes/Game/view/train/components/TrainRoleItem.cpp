#include "TrainRoleItem.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "model/player/RoleManage.h"
#include "utils/ColorUtil.h"
#include "utils/ValuesUtil.h"
#include "model/train/vo/TrainManager.h"

#define CCSIZE_ITEM_SIZE CCSizeMake(POSX(420),POSX(120))

TrainRoleItem::TrainRoleItem(int id , int acctId)
{
	if (!CCLayer::init())
	{
		return;
	}

	this->setContentSize(CCSIZE_ITEM_SIZE);

	setMerhId(id);

	// back
	{
		CCUIBackground * pBack = new CCUIBackground();
		pBack->initWithSpriteFrame("ui2.png" , CCPointZero , CCPointZero , CCSIZE_ITEM_SIZE);
		this->addChild(pBack , 0);
		pBack->release();
	}

	char path[128] = {0};
	// head
	{
		CCSprite * headbg = new CCSprite();
		headbg->initWithSpriteFrameName("formation/formation_block_open.png");
		CCSize size = headbg->getContentSize();
		headbg->setPosition(ccp(size.width/2 + POSX(10), CCSIZE_ITEM_SIZE.height/2));
		this->addChild(headbg,1);
		headbg->release();

		CCSprite * head = new CCSprite();
		memset(path,0,sizeof(path));
		sprintf(path,"assets/icon/head/%d.png", id);
		if (head->initWithFile(path))
		{
			head->setPosition(ccp(size.width/2 + POSX(10), CCSIZE_ITEM_SIZE.height/2));
			this->addChild(head,2);
			head->release();

			headbg->setScale((float)(head->getContentSize().width+POSX(4))/size.width);
		}
	}

	//int accountId = RoleManage::Instance()->getAccountIdByMerhId(id);
	setAcountId(acctId);
	PlayerInfoVo * pInfo = RoleManage::Instance()->getMercenary(acctId);
	if (!pInfo)
	{
		return;
	}
	
	// name
	{
		CCLabelTTF * pNameLabel = CCLabelTTF::labelWithString(pInfo->playerBaseInfo.name.c_str() , CCSizeMake(POSX(210) , POSX(30)) , CCTextAlignmentLeft, "Arial" , POSX(28));
		pNameLabel->setColor(ColorUtil::getMerchColor(pInfo->playerBaseInfo.color));
		pNameLabel->setAnchorPoint(ccp(0,0.5));
		pNameLabel->setPosition(ccp(POSX(160) , POSX(90)));
		this->addChild(pNameLabel , 1);
	}

	// level
	{
		memset(path , 0 , sizeof(path));
		sprintf(path , ValuesUtil::Instance()->getString("TRN035").c_str() , pInfo->playerBaseInfo.lev());
		CCLabelTTF * pLevelLabel = CCLabelTTF::labelWithString(path , CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentLeft, "Arial" , POSX(28));
		pLevelLabel->setColor(ccc3(222,222,222));
		pLevelLabel->setAnchorPoint(ccp(0,0.5));
		pLevelLabel->setPosition(ccp(POSX(160) , POSX(30)));
		pLevelLabel->setTag(Tag_LevelLabel);
		this->addChild(pLevelLabel , 1);
	}

	// career
	{
		memset(path , 0 , sizeof(path));
		sprintf(path,"CAR%d",pInfo->playerBaseInfo.career);
		CCLabelTTF * pCareerLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString(path).c_str() , CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentLeft, "Arial" , POSX(28));
		pCareerLabel->setColor(ccc3(255,215,0));
		pCareerLabel->setAnchorPoint(ccp(0,0.5));
		pCareerLabel->setPosition(ccp(POSX(300) , POSX(30)));
		this->addChild(pCareerLabel , 1);
	}
	
	// Gou
	
	showIsTrained(getAcountId());
}

void TrainRoleItem::showIsTrained(int accountID)
{
	TrainVo* trainVo = TrainManager::Instance()->getVoByMercId(accountID);
	setIsTrained(!!trainVo);
}

void TrainRoleItem::setIsTrained(bool var)
{
	if (this->getChildByTag(Tag_IsTrainedBg))
	{
		this->removeChildByTag(Tag_IsTrainedBg , true);
	}

	if (this->getChildByTag(Tag_IsTrainedGou))
	{
		this->removeChildByTag(Tag_IsTrainedGou , true);
	}

	if (var)
	{
		CCSprite *pBgSprite = CCSprite::spriteWithSpriteFrameName("peiyang/bg_kuang.png");
		if(pBgSprite)
		{
			pBgSprite->setPosition(ccp(CCSIZE_ITEM_SIZE.width - POSX(30) , POSX(60)));
			pBgSprite->setTag(Tag_IsTrainedBg);
			this->addChild(pBgSprite , 1);
		}

		CCSprite *pIconSprite = CCSprite::spriteWithSpriteFrameName("peiyang/gou1.png");
		if(pIconSprite)
		{
			pIconSprite->setPosition(ccp(CCSIZE_ITEM_SIZE.width - POSX(30) , POSX(60)));
			pIconSprite->setTag(Tag_IsTrainedGou);
			this->addChild(pIconSprite , 2);
		}
	}
}

void TrainRoleItem::updateLevelLabel(int level)
{
	CCLabelTTF * pLab = (CCLabelTTF *)this->getChildByTag(Tag_LevelLabel);
	if (pLab)
	{
		char path[64] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("TRN035").c_str() , level);
		pLab->setString(path);
	}
}

TrainRoleItem::~TrainRoleItem()
{

}