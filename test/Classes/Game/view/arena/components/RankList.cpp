#include "RankList.h"
#include "ArenaUI.h"
#include "model/player/RoleManage.h"
#include "socket/command/s36/SCMD361.h"
#include "RankItem.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "model/arena/ArenaConst.h"
#include "manager/LangManager.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "CustomCD.h"
#include "manager/CDManage.h"
#include "socket/command/c18/CCMD182.h"
#include "socket/network/GameServerSocket.h"
#include "model/newhand/NewhandManager.h"
#include "manager/LevLimitConst.h"
#include "MessageInfoBox.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"

const float FontSize = 20.0f;

RankList::RankList()
{
	_accountInfo = 0;
	_pContainer = 0;
	_cdvalue = 0;
	_price = 0;
	_suiteCD = 0;
	_refreshCD =0;
	_refreshValue = 0;
	m_btnReset = 0;
}

RankList::~RankList()
{
	//std::vector<RankItem*>::iterator iter = _itemDic.begin();
	//for (;iter != _itemDic.end();iter++)
	//{
	//	RankItem * pHeroRankItem = (RankItem *)(*iter);
	//	if (pHeroRankItem && pHeroRankItem->getParent())
	//	{
	//		pHeroRankItem->removeFromParentAndCleanup(true);
	//	}
	//}
}

bool RankList::initWithParam(ArenaUI* pContainer)
{
	if (!pContainer)
		return false;
	if (!LayerNode::init())
		return false;

	_pContainer = pContainer;

	_accountInfo = RoleManage::Instance()->accountInfo();

	//quota
	CCObject* tmpoldQuota = this->getChildByTag(RankListTAG_quota);
	if (tmpoldQuota)
		this->removeChildByTag(RankListTAG_quota, true);
	CCLabelTTF* pLabelQuota = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC008").c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
	pLabelQuota->setPosition(ccp(POSX(725), POSX(640-364)));
	this->addChild(pLabelQuota, RankListZ_quota, RankListTAG_quota);
	pLabelQuota->setColor(ccc3(55, 21, 0));	
	//cd_title
	CCObject* tmpoldCDTitle = this->getChildByTag(RankListTAG_cd_title);
	if (tmpoldCDTitle)
		this->removeChildByTag(RankListTAG_quota, true);
	CCLabelTTF* pLabelCDTitle = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC016").c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
	pLabelCDTitle->setPosition(ccp(POSX(380), POSX(640-364)));
	this->addChild(pLabelCDTitle, RankListZ_cd_title, RankListTAG_cd_title);
	pLabelCDTitle->setColor(ccc3(55, 21, 0));	
	//后可再次使用
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC049").c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pLabel->setPosition(ccp(POSX(690), POSX(640-400)));
		this->addChild(pLabel, RankListZ_cd_title2, RankListTAG_cd_title2);
		pLabel->setColor(ccc3(55, 21, 0));	
	}

	//Custom CD
	_suiteCD = new CustomCD( CDManage::ARENA_CD );
	_suiteCD->setPosition( ccp(POSX(380), POSX(640-374)) );
	this->addChild( _suiteCD, RankListZ_cd, RankListTAG_cd);

	_suiteCD->release(); 

	//refresh opps CD
	_refreshCD = new CustomCD( CDManage::ARENA_OPPS_CD );
	_refreshCD->setPosition( ccp(POSX(470), POSX(640-415)) );
	this->addChild( _refreshCD, RankListZ_cd2, RankListTAG_cd2);

	_refreshCD->release(); // HWJ

	//CDManage::Instance()->addEventListener( CDManage::CDCHANGED, this, callfuncND_selector(LevyView::cdChangedHandler) ); 

	//int type = CDManage::Instance()->getLockBytype( CDManage::COLLECTION );
	//isLockHandler(type);
	///==>add by hwj 2012.0906更换挑战对象
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btnReset = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(RankList::handleResetOpps));

			_btnReset->setPosition(ccp(POSX(420), POSX(640 - 400)) );
			_btnReset->setScaleX(1.3f);
			_btnReset->setScaleY(0.7f);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btnReset, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::WindowLayer_PopUIBgTAG_btn_1);
			this->addChild(buttonMenu, RankListZ_reset, RankListTAG_reset);	
			//_btnReset->release();

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC048").c_str(), CCSizeMake(POSX(200), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(_btnReset->getContentSize().width/2, _btnReset->getContentSize().height/2));
			_btnReset->addChild(pLabel);
			pLabel->setColor(ccc3(255, 255, 255));
			pLabel->setScaleX(0.7f);
			pLabel->setScaleY(1.4f);


			m_btnReset = _btnReset;
		}
		
	}
	return true;
}

void RankList::update(SCMD361* param)
{
	_suiteCD->reinit();

	_cdvalue = param->e_cd;
	_price = param->g_price;
	//hwj
	_refreshCD->reinit();
	//_refreshValue = param->l_refreshcd;

	RankItem* item = 0;

	_itemDic.clear();
	std::vector<SCMD361Node>& arr = param->i_challengeArr;
	for (int i = 0; i < arr.size(); i++)
	{
		SCMD361Node& data = arr[i];
		//delete old
		CCObject* tmpold = this->getChildByTag(RankListTAG_item_0+i);
		if (tmpold)
			this->removeChildByTag(RankListTAG_item_0+i, true);
		//create new
		item = new RankItem();
		item->initWithParam(_pContainer, data);
		this->addChild(item, RankListZ_item_0+i, RankListTAG_item_0+i);
		//add
		_itemDic.push_back(item);// = ;
		//release
		item->release();
		item->setPosition(ccp(POSX(375+120*i), POSX(400)));
	}


	//quota_value
	char stdQuotaV[10];
	sprintf(stdQuotaV, "%d", param->f_quota);
	CCObject* tmpoldQuotaV = this->getChildByTag(RankListTAG_quota_value);
	if (tmpoldQuotaV)
		this->removeChildByTag(RankListTAG_quota_value, true);
	CCLabelTTF* pLabelQuotaV = CCLabelTTF::labelWithString(stdQuotaV, CCSizeMake(POSX(80), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
	pLabelQuotaV->setPosition(ccp(POSX(776), POSX(640-364)));
	this->addChild(pLabelQuotaV, RankListZ_quota_value, RankListTAG_quota_value);
	pLabelQuotaV->setColor(ccc3(255, 0, 0));	
	//quota_btn
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *_quota_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
			this, 
			menu_selector(RankList::clickHandler) );
			_quota_btn->setPosition(ccp(POSX(870), POSX(640-364))) ;

			_quota_btn->setScale(0.7f);

			CCMenu *buttonMenu = new CCMenu();
			buttonMenu->init();
			buttonMenu->addChild(_quota_btn, 0, 0);
			buttonMenu->setPosition(ccp(0, 0));
			buttonMenu->setTouchLayer(TLE::WindowLayer_PopUIBgTAG_btn_1);
			this->addChild(buttonMenu, RankListZ_quota_btn, RankListTAG_quota_btn);
			buttonMenu->release();

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("JJC013").c_str(), CCSizeMake(POSX(200), POSX(FontSize)),CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pLabel->setPosition(ccp(_quota_btn->getContentSize().width/2, _quota_btn->getContentSize().height/2));
			_quota_btn->addChild(pLabel);
			pLabel->setColor(ccc3(255, 255, 255));
		}
	}


	bool isReady = CDManage::Instance()->getCDReady(CDManage::ARENA_OPPS_CD);
	if (isReady)
	{
		m_btnReset->setIsEnabled(true);
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(RankListTAG_cd_title2);
		pLabel->setIsVisible(false);
	}
	else
	{
		m_btnReset->setIsEnabled(false);
		CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(RankListTAG_cd_title2);
		pLabel->setIsVisible(true);
	}
	
	// new hand
	if (!NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Arena))
	{
		NewhandManager::Instance()->touchNextScript("p" , "ARENA");
	}
	
}

void RankList::clickHandler(CCObject* pSender)
{
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_BuyArenaCount , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_BuyArenaCount);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}
	/*
	if (RoleManage::Instance()->accountInfo()->vipLev() <= 0)
	{
		LangManager::msgShow("JJC009");
		return;
	}
	*/

	if (RoleManage::Instance()->accountInfo()->vipLev() <= 2 && _pContainer->_buyed >= 5)
	{
		LangManager::msgShow("JJC010");
		return;
	}

	if (_accountInfo->gold() < _price)
	{
		LangManager::msgShow("JJC011");
		return;
	}

	Confirm* pConfirm = new Confirm();
	char strBuy[180];
	sprintf(strBuy, ValuesUtil::Instance()->getString("JJC012").c_str(), _price);
	pConfirm->initWithParam(strBuy, this, menu_selector(RankList::handleBuyArena), menu_selector(RankList::handleBuyArenaCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();

}
	
void RankList::handleResetOpps(CCObject* pSender)
{
	//reset hwj
	_pContainer->dispatchEvent(ArenaConst::RESET_OPPS, 0);
}

void RankList::handleBuyArena(CCObject* pSender)
{
	//buy
	_pContainer->dispatchEvent(ArenaConst::BUY_ARENA, 0); 
	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}
	
void RankList::handleBuyArenaCancel(CCObject* pSzzender)
{
	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void RankList::tmpClearCD(CCObject* pSender)
{
	CCMD182 cmd;
	cmd.a_type = 19; 
	cmd.b_free = 0;

	GameServerSocket* pSocket = GameServerSocket::getInstance();
	if (pSocket)
		pSocket->sendMessage(&cmd);
}