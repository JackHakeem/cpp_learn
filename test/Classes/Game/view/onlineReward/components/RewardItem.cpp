#include "RewardItem.h"
#include "utils/ScaleUtil.h"
#include "model/backpack/GoodsManager.h"
#include "manager/TouchLayerEnum.h"
#include "CCUIBackground.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/com/GoodsDynamicManager.h"
#include "model/config/ConfigManager.h"
#include "model/player/RoleManage.h"

RewardItem::RewardItem(std::vector<std::string> &list) : _pPopTip(0)
{
	if (!CCLayer::init())
	{
		return;
	}

	_NodeList.clear();
	_NodeList = list;

	// back
	CCUIBackground * pBack = new CCUIBackground();
	pBack->initWithSpriteFrame("ui2.png" , CCPointZero , CCPointZero ,CCSizeMake(POSX(720) , POSX(120)));
	this->addChild(pBack , 0);
	
	this->setAnchorPoint(CCPointZero);
	this->setContentSize(pBack->getContentSize());

	// item
	int index = 0 ;
	std::vector<std::string>::iterator iter = list.begin();
	for (iter ; iter != list.end() ; iter++)
	{
		// get id by career
		int id = 0 , num = 0;
		std::vector<std::string> strItem = ConfigManager::splitStringByCharacter((*iter) , ",");
		if (strItem.size() > 3 )
		{
			int career = RoleManage::Instance()->roleInfo()->playerBaseInfo.career;
			if (career & 1)
			{
				id = ConfigManager::string2Int(strItem[0]);
			}
			else if (career & (1 << 1))
			{
				id = ConfigManager::string2Int(strItem[1]);
			}
			else if (career & (1 << 5))
			{
				id = ConfigManager::string2Int(strItem[2]);
			}
			else
			{
				id = ConfigManager::string2Int(strItem[0]);
			}
			num = ConfigManager::string2Int(strItem[3]);
		}
		else
		{
			id = ConfigManager::string2Int(strItem[0]);
			num = ConfigManager::string2Int(strItem[1]);
		}

		//
		char path[32] = {0};
		// grid
		CCSprite * pBackGrid = CCSprite::spriteWithSpriteFrameName("pack/unlock.png");
		CCSize size = pBackGrid->getContentSize();

		// quality
		
		GoodsBasic * pInfo = g_pGoodsManager->getBasicGood(id);
		if (pInfo && pInfo->quality)
		{
			memset(path,0,sizeof(path));
			sprintf(path,"pack/qualityfram_%d.png", pInfo->quality);
			CCSprite * pQuality = CCSprite::spriteWithSpriteFrameName(path);
			pQuality->setPosition(ccp(size.width/2 , size.height/2));
			pBackGrid->addChild(pQuality , 1 );

			if (pQuality && pInfo->quality >= 4)
			{
				CCFiniteTimeAction * pFadeTo1 = CCFadeTo::actionWithDuration(1.0f , 96);
				CCFiniteTimeAction * pFadeTo2 = CCFadeTo::actionWithDuration(1.0f , 255);
				CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeTo1 , pFadeTo2)) ;
				pQuality->runAction(pAction);
			}
		}
		
		// icon
		{
			memset(path,0,sizeof(path));
			CCSprite * pIcon1 = 0;
			CCSprite * pIcon2 = 0;
			sprintf(path , "assets/icon/goods/%d.png" ,id);
			pIcon1 = CCSprite::spriteWithFile(path);
			pIcon2 = CCSprite::spriteWithFile(path);
			if (!pIcon1 && !pIcon2)
			{
				sprintf(path , "assets/icon/goods/unknown.png" ,id);
				pIcon1 = CCSprite::spriteWithFile(path);
				pIcon2 = CCSprite::spriteWithFile(path);
				if (!pIcon1 || !pIcon2)
				{
					return;
				}
			}		

			pIcon2->setColor(ccc3(233,133,25));
			CCMenuItemSprite * pMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pIcon1,
				pIcon2,
				this,
				menu_selector(RewardItem::onClickShowTips));
			pMenuItem->setTag(id);
			pMenuItem->setPosition(ccp(size.width/2 ,size.height/2));
			CCMenu * pMenu = CCMenu::menuWithItem(pMenuItem);
			pMenu->setTouchLayer(TLE::WindowLayer - 2);
			pMenu->setPosition(CCPointZero);
			pBackGrid->addChild(pMenu , 0 );

			CCSize sizebk= pBack->getContentSize();
			pBackGrid->setPosition(ccp(index *(size.width + POSX(20)) + POSX(160) , sizebk.height/2));
			this->addChild(pBackGrid , 1);
		}
		
		// numbers
		{
			memset(path,0,sizeof(path));
			sprintf(path , "%d" , num);
			CCLabelTTF * pLab = CCLabelTTF::labelWithString( path , CCSizeMake(POSX(120) , POSX(20)) , CCTextAlignmentRight , "Arial" , POSX(20));
			pLab->setColor(ccc3( 255 , 255 ,255));
			pLab->setPosition(ccp(index *(size.width + POSX(20)) + size.width/2 + POSX(95) , POSX(25)));
			this->addChild(pLab , 2);
		}

		++index;
	}
}

RewardItem::~RewardItem()
{

}

void RewardItem::onClickShowTips(CCObject * pSender)
{
	if (!pSender)
	{
		return;
	}
	int id = ((CCNode *)pSender)->getTag();

	if (id)
	{
		initGoodsTipsInfo(id);
		timerStep();
	}
}

void RewardItem::initGoodsTipsInfo(int id)
{
	if (!id)
	{
		return;
	}
	//Add tip
	_pPopTip = new TipHelps();
	if(_pPopTip)
	{
		_pPopTip->init(true, TipConst::NORMAL);
		_pPopTip->setToolTips(this, this);
	}

	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(id);
	if (!goodBasic)
		return;

	GoodsInfo* info = new GoodsInfo();
	info->goodId = id;
	info->name = goodBasic->goodName;
	info->type = goodBasic->type;
	info->equip_type = goodBasic->equip_type;
	info->quality = goodBasic->quality; 

	if (goodBasic->type == 3)
	{//fragments
		info->explain = GoodsToolTips::getExplain(goodBasic, false, 1);
		// Add count
		char pCount[16] = {0};
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

void RewardItem::timerStep()
{
	if(_pPopTip)
	{
		_pPopTip->rollOverHander();
	}
}
