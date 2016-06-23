#include "DamageRankView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "UIListView/CCUIListView.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "LayerNode.h"
#include "manager/ViewManager.h"

DamageRankView::DamageRankView()
{

}

DamageRankView::~DamageRankView()
{

}

bool DamageRankView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->setIsTouchEnabled(false);

	loadItems();

	return true;
}

void DamageRankView::loadItems()
{
	// background
	CCUIBackground * pBack = new CCUIBackground();
	if (pBack)
	{
		bool bVar = pBack->initWithSpriteFrame("ui.png" , ccp(0,0) , ccp(0,0) , CCSizeMake(POSX(420), POSX(400)) , 255);
		if (bVar)
		{
			this->addChild(pBack , 0);
		}
		pBack->release();
	}

	// List name
	CCLabelTTF * pListNameText = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("WBS107").c_str(),
		CCSizeMake(POSX(360) , POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(24));
	pListNameText->setColor(ccc3(255,233,12));
	pListNameText->setPosition(ccp(POSX(180) , POSX(370)));
	this->addChild(pListNameText,2);

	// my damage
	char path[128] = {0};
	sprintf(path , ValuesUtil::Instance()->getString("WBS004").c_str() , 0);
	CCLabelTTF * pMyDamageText = CCLabelTTF::labelWithString(
		path,
		CCSizeMake(POSX(420) , POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(24));
	pMyDamageText->setColor(ccc3(12,233,25));
	pMyDamageText->setPosition(ccp(POSX(150) , POSX(340)));
	pMyDamageText->setTag(TAG_MyDamage_text);
	this->addChild(pMyDamageText,4);

	// show reward menu
	CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
	CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
	CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
	if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
	{
		return;
	}
	CCMenuItemSprite *pRewardMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalNewSprite,
		pPressedNewSprite,
		pSelectedNewSprite,
		this,
		menu_selector(DamageRankView::onClickShowRewordTips));
	pRewardMenuImg->setScaleX(1.3);

	CCMenu * pRewardMenu = CCMenu::menuWithItem(pRewardMenuImg);
	//pRewardMenu->setIsVisible(false);
	CCSize size = pBack->getContentSize();
	CCPoint pos = pBack->getPosition();
	pRewardMenu->setPosition(ccp(pos.x + size.width + POSX(-80), pos.y + size.height + POSX(-40)));
	this->addChild(pRewardMenu, 2);

	CCLabelTTF * pRewardNameText = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("WBS127").c_str(),
		CCSizeMake(POSX(360) , POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(24));
	pRewardNameText->setColor(ccc3(255,233,12));
	pRewardNameText->setPosition(ccp(pRewardMenu->getPosition().x , pRewardMenu->getPosition().y));
	this->addChild(pRewardNameText,3);
}

void DamageRankView::onClickShowRewordTips(CCObject * pSender)
{
	if (ViewManager::getInstance()->_pWBMainView)
	{
		ViewManager::getInstance()->_pWBMainView->ShowRewordTips(true);
	}	
}

void DamageRankView::resetMyDamage(int dmg)
{
	char path[128] = {0};
	sprintf(path , ValuesUtil::Instance()->getString("WBS004").c_str() , dmg);

	CCLabelTTF * pMyDamageText = (CCLabelTTF *)this->getChildByTag(TAG_MyDamage_text);
	if (pMyDamageText)
	{
		pMyDamageText->setString(path);
	}
}

void DamageRankView::updateDamageRankList(std::list<SCMD2C9::SCMD2C9Node> dmgRankList , int nTotalDamageLow , int nTotalDamageHigh)
{
	for (int tag = TAG_DamageList_Item ; tag <= TAG_DamageList_Item + 9 ; tag++)
	{
		this->removeChildByTag(tag , true);
	}

	std::list<SCMD2C9::SCMD2C9Node>::iterator iter = dmgRankList.begin();
	for ( ; iter != dmgRankList.end() ;iter++)
	{
		CCLabelTTF *pText = new CCLabelTTF();
		if (pText)
		{
			int percent = 0;
			char path[128] = {0};
			if(!(nTotalDamageLow == 0 && nTotalDamageHigh == 0))
			{
				percent = 100.0f *((float)iter->c_damage) / (float)((nTotalDamageHigh<<32)+ nTotalDamageLow);
			}
			//sprintf(path , ValuesUtil::Instance()->getString("WBS101").c_str() , iter->a_rank + 1 , iter->b_name.c_str() , iter->c_damage , percent);
            sprintf(path , ValuesUtil::Instance()->getString("WBS101").c_str() , iter->a_rank + 1 , iter->b_name.c_str() , iter->c_damage);
			pText->initWithString(
				path, CCSizeMake(POSX(480) , POSX(30)) , 
				CCTextAlignmentLeft , "Arial" , POSX(24));
			pText->setPosition(ccp(POSX(260) , POSX(300) + POSX(iter->a_rank * (-30) )));
			pText->setTag(TAG_DamageList_Item + iter->a_rank);
			this->addChild(pText , 3);
			pText->release();

			switch ( iter->a_rank )
			{
			case 0:
				pText->setColor(ccc3(255,0,255));
				break;
			case 1:
				pText->setColor(ccc3(0,114,227));
				break;
			case 2:
				pText->setColor(ccc3(0,236,0));
				break;
			default:
				pText->setColor(ccc3(250,250,250));
				break;
			}
		}
	}
}