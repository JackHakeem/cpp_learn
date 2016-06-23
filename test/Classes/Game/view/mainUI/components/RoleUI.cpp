#include "RoleUI.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/ViewManager.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "../MainUIMediator.h"
#include "Message.h"
#include "view/purchase/PurchaseMediator.h"
#include "view/scene/SceneStoryMediator.h"
#include "MessageInfoBox.h"
#include "manager/GlobalManage.h"
#include "manager/PopEventName.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"

const int TAG_VIP_LAYER = 1001;
const int TAG_VIP_LABEL = 1002;
const int TAG_VIGOUR_BUFF_ICON = 1003;
const int TAG_GONG_EXP_BUFF_ICON = 1004;

RoleUI::RoleUI()
{
	_isTrialVip = false;
}

RoleUI::~RoleUI()
{

}

RoleUI::RoleUI(std::string name,int roleLev,int crystalLev,int maxHP,int hp,int energy,int vipLev,int carrer,
int gold, int silver, int silverLim, int practice, int popularity) 
{
	initView();
	setTips();
	setHead(carrer);
	setName(name);
	setRoleLev(roleLev);
	setCrystalLev(crystalLev);
	setEnergy(energy,100);
	setVipLev(vipLev);
	isAddBtnShow(vipLev);
	setGold(gold);
	setSilver(silver,silverLim);
	setPrictice(practice);
	setPopularity(popularity);
	initEvent();
	setHP(maxHP,maxHP);
}

void RoleUI::initView()
{
	this->setIsTouchEnabled(false);
	CCSize _winSize = CCDirector::sharedDirector()->getWinSize();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_figure.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_newroleui.plist");

	CCSprite * _pfigure = CCSprite::spriteWithSpriteFrameName("mainUI/figure.png");
	CCSize _roleUISzie;
	if (_pfigure && _pfigure->getTexture())
	{
		_roleUISzie = _pfigure->getTexture()->getContentSize();
	}
	
	//level bg
	{
		CCSprite *pLevBgSprite = new CCSprite();
		pLevBgSprite->initWithSpriteFrameName("newroleui/levbg.png");
		pLevBgSprite->setPosition(ccp(POSX(14) , POSX(57)));
		this->addChild(pLevBgSprite , Z_BG+4);
		pLevBgSprite->release();
	}	

	// head menu
	{
		char path[64];
		memset((void *)path,0,sizeof(path));
		sprintf(path,"assets/icon/head/%d_1.png",RoleManage::Instance()->roleInfo()->playerBaseInfo.cloth);  
		CCSprite *pNormalHeadSprite = CCSprite::spriteWithFile(path);
		CCSprite *pPressedHeadSprite = CCSprite::spriteWithFile(path);
		CCMenuItemSprite *pMenuHeadItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalHeadSprite,
			pPressedHeadSprite,
			this,
			menu_selector(RoleUI::onVipMenuClick));
		pMenuHeadItem->setPosition(CCPointZero);
		pMenuHeadItem->setScale(88.0/109.0);
		pMenuHeadItem->setTag(0);
		CCMenu * pMenuHead = CCMenu::menuWithItem(pMenuHeadItem);
		pMenuHead->setAnchorPoint(CCPointZero);
		pMenuHead->setIsRelativeAnchorPoint(true);
		pMenuHead->setPosition(ccp(POSX(37),POSX(34)));	
		this->addChild(pMenuHead,Z_BG+2,TAG_HEAD);
	}

	// buy gold menu
	{
		CCSprite *pNormalFigureSprite = CCSprite::spriteWithSpriteFrameName("newroleui/figure2.png");
		CCSprite *pPressedFigureSprite = CCSprite::spriteWithSpriteFrameName("newroleui/figure2.png");
		if(!pNormalFigureSprite || !pPressedFigureSprite)
		{
			return;
		}
		CCMenuItemSprite *_pMenuFigureItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalFigureSprite,
			pPressedFigureSprite,
			this,
			menu_selector(RoleUI::clickBuyGold));
		_pMenuFigureItem->setAnchorPoint(CCPointZero);
		_pMenuFigureItem->setIsRelativeAnchorPoint(true);
		//_pMenuFigureItem->setContentSize(CCSizeMake(POSX(_pMenuFigureItem->getContentSize().width-160),POSX(_pMenuFigureItem->getContentSize().height)));
		_pMenuFigureItem->setPosition(CCPointZero);
		CCMenu * _pMenuFigure = CCMenu::menuWithItem(_pMenuFigureItem);
		_pMenuFigure->setAnchorPoint(CCPointZero);
		_pMenuFigure->setIsRelativeAnchorPoint(true);
		_pMenuFigure->setPosition(CCPointZero);
		if (this->getChildByTag(TAG_BTN))
		{
			this->removeChildByTag(TAG_BTN,true);
		}
		this->addChild(_pMenuFigure,Z_BG,TAG_BTN);

		_pMenuFigureItem->setIsEnabled(false);
	}

	// energy bg progress
	/*
	CCSprite * pBackEnergy = ImageManager::getRealSpriteFromImagePath("newroleui/energy2.png");
	if (pBackEnergy)
	{
		pBackEnergy->setRotation(-90);
		CCProgressTimer * pEnergy = new CCProgressTimer();
		pEnergy->initWithTexture(pBackEnergy->getTexture());
		pEnergy->setSprite(pBackEnergy);
		pEnergy->setPercentage(30);
		pEnergy->setType(CCProgressTimerType::kCCProgressTimerTypeHorizontalBarLR);
		pEnergy->setPosition(ccp(POSX(100),POSX(0)));	
		this->addChild(pEnergy,Z_ITEM + 30 , TAG_ENERGY_PROGRESS);
		pEnergy->release();
	}
	*/

	{
		CCProgressTimer * pEnergy = new CCProgressTimer();
		pEnergy->initWithFile("assets/ui/mainUI/energy2.png");
		pEnergy->setPercentage(0);
		pEnergy->setType(CCProgressTimerType(2));
		pEnergy->setPosition(ccp(POSX(140),POSX(14)));
		pEnergy->setScaleX(0.98);
		this->addChild(pEnergy,Z_ITEM + 2 , TAG_ENERGY_PROGRESS);
		pEnergy->release();

		CCProgressTo * pProgressTo = CCProgressTo::actionWithDuration(0.1f, 0.0f); 
		pEnergy->runAction(pProgressTo);
	}

	// buy energy menu
	{
		CCSprite *pNormalEnergySprite = CCSprite::spriteWithSpriteFrameName("newroleui/energy2.png");
		CCSprite *pPressedEnergySprite = CCSprite::spriteWithSpriteFrameName("newroleui/energy2.png");
		if(!pNormalEnergySprite || !pPressedEnergySprite)
		{
			return;
		}
		CCMenuItemSprite *_pMenuEnergyItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalEnergySprite,
			pPressedEnergySprite,
			this,
			menu_selector(RoleUI::clickBuyEnergy));
		_pMenuEnergyItem->setAnchorPoint(CCPointZero);
		_pMenuEnergyItem->setIsRelativeAnchorPoint(true);
		_pMenuEnergyItem->setOpacity(50);
		_pMenuEnergyItem->setScaleX(0.98);
		_pMenuEnergyItem->setPosition(CCPointZero);
		CCMenu * _pMenuEnergy = CCMenu::menuWithItem(_pMenuEnergyItem);
		_pMenuEnergy->setAnchorPoint(CCPointZero);
		_pMenuEnergy->setIsRelativeAnchorPoint(true);
		_pMenuEnergy->setPosition(ccp(POSX(51),POSX(0)));	
		if (this->getChildByTag(TAG_BTN+1))
		{
			this->removeChildByTag(TAG_BTN+1,true);
		}
		this->addChild(_pMenuEnergy,Z_ITEM+1,TAG_BTN+1);
		setEnergy(RoleManage::Instance()->roleInfo()->playerBaseInfo.energy);
	}	

	// "+" icon
	{
		CCSprite * pAddIcon = new CCSprite();
		pAddIcon->initWithSpriteFrameName("newroleui/addenergy.png");
		pAddIcon->setPosition(ccp(POSX(210),POSX(16)));
		this->addChild(pAddIcon,Z_ITEM + 4);
		pAddIcon->release();
	}	

	// recharge menu
	{
		CCSprite *pNormalCharge = CCSprite::spriteWithSpriteFrameName("newroleui/recharge1.png");
		CCSprite *pPressedCharge = CCSprite::spriteWithSpriteFrameName("newroleui/recharge2.png");
		CCMenuItemSprite *pMenuChargeItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalCharge,
			pPressedCharge,
			this,
			menu_selector(RoleUI::clickBuyGold));
		pMenuChargeItem->setAnchorPoint(CCPointZero);
		pMenuChargeItem->setIsRelativeAnchorPoint(true);
		//pMenuChargeItem->setOpacity(50);
		pMenuChargeItem->setScale(0.90);
		pMenuChargeItem->setPosition(CCPointZero);
		CCMenu * pMenuCharge = CCMenu::menuWithItem(pMenuChargeItem);
		pMenuCharge->setAnchorPoint(CCPointZero);
		pMenuCharge->setIsRelativeAnchorPoint(true);
		pMenuCharge->setPosition(ccp(POSX(229),POSX(-12)));	
		this->addChild(pMenuCharge,Z_ITEM+1,TAG_BTN+2);
	}

	// this
	{
		this->setAnchorPoint(CCPointZero);
		this->setIsRelativeAnchorPoint(true);
		this->setContentSize(_roleUISzie);
		this->setPosition(POS(ccp(1,/*_winSize.height-90*/ 568),ScaleUtil::TOP_LEFT));
	}
	
	
	//Doyang 20120731
	{
		CCLayer *pVipLayer = new CCLayer();

		CCSprite *pVipNormalSprite = CCSprite::spriteWithSpriteFrameName("newroleui/vip.png");
		CCSprite *pVipPressedSprite = CCSprite::spriteWithSpriteFrameName("newroleui/vip.png");
		pVipPressedSprite->setColor(ccc3(255,12,25));
		CCMenuItemSprite *pVipMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pVipNormalSprite,
			pVipPressedSprite,
			this,
			menu_selector(RoleUI::onVipMenuClick));
		if(pVipMenuItem)
		{
			pVipMenuItem->setAnchorPoint(CCPointZero);
			pVipMenuItem->setPosition(CCPointZero);
			CCMenu *pVipMenu = CCMenu::menuWithItem(pVipMenuItem);
			pVipMenu->setTouchLayer(TLE::CCMENULAYER - 1);
			pVipMenu->setPosition(CCPointZero);
			pVipMenu->setTag(1001);
			pVipLayer->addChild(pVipMenu);
		}

		CCLabelTTF *pVipLabel = new CCLabelTTF();
		pVipLabel->initWithString("",
			CCSizeMake(POSX(100), POSX(18)),
			CCTextAlignmentCenter,
			"Arial",
			POSX(18));
		pVipLabel->setPosition(ccp(pVipMenuItem->getContentSize().width / 2,
			pVipMenuItem->getContentSize().height / 2)); 
		pVipLayer->addChild(pVipLabel, 0, TAG_VIP_LABEL);
		pVipLabel->release();

		pVipLayer->setContentSize(CCSizeMake(POSX(58), POSX(26)));
		pVipLayer->setAnchorPoint(CCPointZero);
		pVipLayer->setPosition(ccp(POSX(7), POSX(-22)));
		this->addChild(pVipLayer, -1, TAG_VIP_LAYER);
		pVipLayer->release();
	}

	CCSprite *pNormalVigourSprite = CCSprite::spriteWithFile("assets/ui/ic_vigour_buff.png");
	CCSprite *pPressedVigourSprite = CCSprite::spriteWithFile("assets/ui/ic_vigour_buff.png");
	if(!pNormalVigourSprite || !pPressedVigourSprite)
	{
		return;
	}
	CCMenuItemSprite *_pMenuVigourItem = CCMenuItemSprite::itemFromNormalSprite(
		pNormalVigourSprite,
		pPressedVigourSprite,
		this,
		menu_selector(RoleUI::clickVigourBuff));
	_pMenuVigourItem->setAnchorPoint(CCPointZero);
	_pMenuVigourItem->setIsRelativeAnchorPoint(true);
	//_pMenuVigourItem->setContentSize(CCSizeMake(POSX(_pMenuVigourItem->getContentSize().width-160),POSX(_pMenuVigourItem->getContentSize().height)));
	_pMenuVigourItem->setPosition(ccp(POSX(100), POSX(-40)));
	CCMenu * _pMenuVigour = CCMenu::menuWithItem(_pMenuVigourItem);
	_pMenuVigour->setAnchorPoint(CCPointZero);
	_pMenuVigour->setIsRelativeAnchorPoint(true);
	_pMenuVigour->setPosition(CCPointZero);
	this->addChild(_pMenuVigour,0, TAG_VIGOUR_BUFF_ICON);

	//TAG_GONG_EXP_BUFF_ICON
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithFile("assets/ui/gong/exp_icon.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithFile("assets/ui/gong/exp_icon.png");
		if(!pNormalSprite || !pPressedSprite)
		{
			return;
		}
		CCMenuItemSprite *_pMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this,
			menu_selector(RoleUI::clickGongExpBuff));
		_pMenuItem->setAnchorPoint(CCPointZero);
		_pMenuItem->setIsRelativeAnchorPoint(true);
		_pMenuItem->setPosition(ccp(POSX(140), POSX(-40)));
		CCMenu * _pMenu = CCMenu::menuWithItem(_pMenuItem);
		_pMenu->setAnchorPoint(CCPointZero);
		_pMenu->setIsRelativeAnchorPoint(true);
		_pMenu->setPosition(CCPointZero);
		this->addChild(_pMenu,0, TAG_GONG_EXP_BUFF_ICON);

		if (RoleManage::Instance()->_accountInfo._gongExpBuffCount <= 0)
			_pMenu->setIsVisible(false);//not show
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/mainUI/res_mainui_figure.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/mainUI/res_mainui_newroleui.plist");
}

void RoleUI::setTips()
{

}


SpriteNode* maskedSpriteWithSprite(std::string textureSpriteStr, std::string maskSpriteStr)
{
	CCSprite * textureSprite = CCSprite::spriteWithFile(textureSpriteStr.c_str());
	CCSprite * maskSprite = CCSprite::spriteWithFile(maskSpriteStr.c_str());

 // 1
	CCRenderTexture * rt = CCRenderTexture::renderTextureWithWidthAndHeight(maskSprite->getTexture()->getContentSize().width,
		maskSprite->getTexture()->getContentSize().height);
	//2
	maskSprite->setPosition(ccp(maskSprite->getTexture()->getContentSize().width/2,
		maskSprite->getTexture()->getContentSize().height/2));

	textureSprite->setPosition(ccp(textureSprite->getTexture()->getContentSize().width/2,
		textureSprite->getTexture()->getContentSize().height/2));

	//3
	ccBlendFunc bf1;
	bf1.src = GL_ONE;
	bf1.dst = GL_ZERO;
	maskSprite->setBlendFunc(bf1);

	ccBlendFunc bf2;
	bf2.src = GL_DST_ALPHA;
	bf2.dst = GL_ZERO;
	textureSprite->setBlendFunc(bf2);

	//4
	rt->begin();
	maskSprite->visit();
	textureSprite->visit();
	rt->end();

	//5
	SpriteNode* retval = new SpriteNode();
	retval->initWithTexture(rt->getSprite()->getTexture());
	retval->setFlipY(true);


	textureSprite->release();
	maskSprite->release();
    return retval;
    
}

void RoleUI::setHead(int carrer)
{
	char path[64];
	memset((void *)path,0,sizeof(path));
	sprintf(path,"assets/icon/head/%d_1.png",RoleManage::Instance()->roleInfo()->playerBaseInfo.cloth);  
	CCMenu * pHeadSpriteMenu = (CCMenu *)this->getChildByTag(TAG_HEAD);
	if (pHeadSpriteMenu)
	{
		CCMenuItemSprite * pMenuSprite = (CCMenuItemSprite *)pHeadSpriteMenu->getChildByTag(0);
		if (pMenuSprite)
		{
			CCSprite *pHeadSprite1 = CCSprite::spriteWithFile(path);
			pMenuSprite->setNormalImage(pHeadSprite1);
			CCSprite *pHeadSprite2= CCSprite::spriteWithFile(path);
			pMenuSprite->setSelectedImage(pHeadSprite2);
		}
	}
}

void RoleUI::setName(std::string name)
{

}

void RoleUI::setRoleLev(int roleLev)
{
	char chLev[8];
	sprintf(chLev,"%d",roleLev);
	CCLabelTTF * _roleLevText = CCLabelTTF::labelWithString(chLev,CCSizeMake(POSX(30),POSX(20)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(15));
	_roleLevText->setAnchorPoint(CCPointZero);
	_roleLevText->setIsRelativeAnchorPoint(true);
	_roleLevText->setColor(ccc3(255,215,0));
	_roleLevText->setPosition(ccp(POSX(-1),POSX(47)));
	if (this->getChildByTag(TAG_LEV))
	{
		this->removeChildByTag(TAG_LEV,true);
	}
	this->addChild(_roleLevText,Z_ITEM,TAG_LEV);
}

void RoleUI::setCrystalLev(int crystalLev)
{

}

void RoleUI::setEnergy(int energy,int maxEnergy)
{
	static int firstIgnore = 0;
	static int old_vigour = 0;
	int dis = energy - old_vigour;
	char chEnergy[32];
	sprintf(chEnergy,ValuesUtil::Instance()->getString("JINLI").c_str(),energy,MAX_ENERGY);
	CCLabelTTF * _roleEnergyText = CCLabelTTF::labelWithString(chEnergy,CCSizeMake(POSX(250),POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
	_roleEnergyText->setAnchorPoint(CCPointZero);
	_roleEnergyText->setIsRelativeAnchorPoint(true);
	_roleEnergyText->setColor(ccc3(233,233,233));
	_roleEnergyText->setPosition(ccp(POSX(80),POSX(4)));
	if (this->getChildByTag(TAG_ENERGY))
	{
		this->removeChildByTag(TAG_ENERGY,true);
	}
	this->addChild(_roleEnergyText,Z_ITEM+3,TAG_ENERGY);

	CCProgressTimer * pEnergy = (CCProgressTimer *)this->getChildByTag(TAG_ENERGY_PROGRESS);
	if (pEnergy)
	{
		float percent = maxEnergy - energy;
		if (percent <= 0.0f)
		{			percent = 1.0f;		}
		if (percent >= 100.0f)
		{
			percent = 99.0f;
		}		
		//pEnergy->setPercentage(percent);
		CCProgressTo * pAction = CCProgressTo::actionWithDuration(0.1f , percent);
		pEnergy->runAction(pAction);
		if (percent == 0.0f)
		{
			//runMyAction(pEnergy->getSprite() , getMyAction());
		}
		else
		{
			//stopMyAction(pEnergy->getSprite());
		}
	}	

	if (dis > 0  && firstIgnore != 0)
	{
		char dstShow[100];
		sprintf(dstShow, ValuesUtil::Instance()->getString("JINLI2").c_str(), dis);
		string dst = dstShow;
		LangManager::msgStr(dst);	
	}
	firstIgnore++;
	old_vigour = energy;
}

void RoleUI::setVipLev(int vipLev)
{
	//Doyang 20120731
	if(vipLev > 10) return;
	AccountInfoVo *pAccountInfo = RoleManage::Instance()->accountInfo();

	char vipChar[10];
	if(vipLev == 0 &&
		pAccountInfo && 
		pAccountInfo->_trialVip)
	{
		sprintf(vipChar,ValuesUtil::Instance()->getString("VIP101").c_str());
		_isTrialVip = true;
		if (this->getChildByTag(TAG_VIP_LAYER))
		{
			CCNode * pNode = this->getChildByTag(TAG_VIP_LAYER)->getChildByTag(1001);
			if (pNode)
			{
				runMyAction(pNode , getMyAction());
			}	
		}
	}
	else
	{
		_isTrialVip = false;
		sprintf(vipChar, "VIP%d", vipLev);
	}
	CCNode *pVipLayer = this->getChildByTag(TAG_VIP_LAYER);
	if(!pVipLayer)
	{
		return;
	}

	CCLabelTTF *pVipLabel = (CCLabelTTF *) pVipLayer->getChildByTag(TAG_VIP_LABEL);
	if(!pVipLabel)
	{
		return;
	}

	pVipLabel->setString(vipChar);
	pVipLabel->setColor(this->getVipLabelColor(vipLev));
}

bool RoleUI::isAddBtnShow(int vipLev)
{
	return true;
}

void RoleUI::setGold(int gold)
{
	char chGold[16];
	if (gold/1000000 == 0)
	{
		sprintf(chGold,"%d",gold);
	}
	else
	{
		gold = gold/10000;
		sprintf(chGold,ValuesUtil::Instance()->getString("NUM1").c_str(),gold);
	}
	CCLabelTTF * _goldText = CCLabelTTF::labelWithString(chGold,CCSizeMake(POSX(120),POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
	_goldText->setAnchorPoint(CCPointZero);
	_goldText->setIsRelativeAnchorPoint(true);
	_goldText->setColor(ccc3(244,208,93));
	_goldText->setPosition(ccp(POSX(115),POSX(36)));
	if (this->getChildByTag(TAG_GOLD))
	{
		this->removeChildByTag(TAG_GOLD,true);
	}
	this->addChild(_goldText,Z_ITEM,TAG_GOLD);
}

void RoleUI::setSilver(int num,int numLim)
{
	int numTmp = num;
	char chSliver[32];
	if (numTmp/10000000 == 0)
	{
		sprintf(chSliver,"%d",numTmp);
	}
	else
	{
		numTmp = numTmp/10000;
		sprintf(chSliver,ValuesUtil::Instance()->getString("NUM1").c_str(),numTmp);
	}
	CCLabelTTF * _sliverText = CCLabelTTF::labelWithString(chSliver,CCSizeMake(POSX(120),POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
	_sliverText->setAnchorPoint(CCPointZero);
	_sliverText->setIsRelativeAnchorPoint(true);
	if (num > RoleManage::Instance()->_accountInfo._silverLim)
	{
		_sliverText->setColor(ccc3(255,5,0));
	}
	else
	{
		_sliverText->setColor(ccc3(211,212,213));
	}
	_sliverText->setPosition(ccp(POSX(226),POSX(36)));
	if (this->getChildByTag(TAG_SLIVER))
	{
		this->removeChildByTag(TAG_SLIVER,true);
	}
	this->addChild(_sliverText,Z_ITEM,TAG_SLIVER);
}

void RoleUI::setPrictice(int practice)
{
	return; // LH20121031 unused

	char chPractice[32];
	if (practice/10000000 == 0)
	{
		sprintf(chPractice,"%d",practice);
	}
	else
	{
		practice = practice/10000;
		sprintf(chPractice,ValuesUtil::Instance()->getString("NUM1").c_str(),practice);
	}
	CCLabelTTF * _practiceText = CCLabelTTF::labelWithString(chPractice,CCSizeMake(POSX(120),POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
	_practiceText->setAnchorPoint(CCPointZero);
	_practiceText->setIsRelativeAnchorPoint(true);
	_practiceText->setColor(ccc3(255,215,0));
	_practiceText->setPosition(ccp(POSX(371),POSX(52))); 
	if (this->getChildByTag(TAG_PRACTICE))
	{
		this->removeChildByTag(TAG_PRACTICE,true);
	}
	this->addChild(_practiceText,Z_ITEM,TAG_PRACTICE);
}

void RoleUI::setPopularity(int popularity)
{

}

void RoleUI::initEvent()
{

}

void RoleUI::setHP(int HP,int maxHP)
{

}

void RoleUI::clickBuyGold(CCObject * pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //return;
#endif
	//Doyang 20120710
	//For 91
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_PURCHASE, NULL);
//	PurchaseMediator * pMediator = (PurchaseMediator *)g_pFacade->retrieveMediator(AppFacade_PURCHASE_MEDIATOR);
//	if (pMediator)
//	{
//		//g_pGlobalManage->showAllUI(false);
//
//		pMediator->openPurchaseView();
//	}
}

void RoleUI::clickBuyEnergy(CCObject * pSender)
{
	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
	if (mUImediator)
	{
		mUImediator->onRequestEnergy();
	}
}

void RoleUI::clickBuyEnergyConfirm(CCObject * pSender)
{
	clickCancel(0);
	//if (RoleManage::Instance()->accountInfo()->_vipLev < 1)
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_BuyEnergy , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_BuyEnergy);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}
	else
	{
		Confirm * _confirmBuy = new Confirm();
		char str[64];
		sprintf(str,ValuesUtil::Instance()->getString("BUYJL").c_str(),_scmd21fCopy.a_gold,_scmd21fCopy.b_energy);
		_confirmBuy->initWithParam(
			str,
			this,
			menu_selector(RoleUI::onAddEnergy),
			menu_selector(RoleUI::clickCancel));
		LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
		_confirmBuy->release();
	}
	
}

void RoleUI::clickCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
}

void RoleUI::onAddHandler(SCMD21F * cmd,int type)
{
	memcpy((void *)&_scmd21fCopy,(void*)cmd,sizeof(*cmd));
	_type = type;
	onAddEnergyAlert(cmd);
}

void RoleUI::onAddEnergyAlert(SCMD21F * cmd)
{
	int _energy = RoleManage::Instance()->_accountInfo._energy;
	int _gold = RoleManage::Instance()->_accountInfo._gold;
	if (_gold < cmd->a_gold)
	{
		//Message::Instance()->show(ValuesUtil::Instance()->getString("PY19"),ccc3(240,44,11),1);
		MessageInfoBox::Instance()->show(ValuesUtil::Instance()->getString("PY19"),ccc3(240,44,11));
	}
	else if (_energy >= MAX_ENERGY)
	{
		//Message::Instance()->show(ValuesUtil::Instance()->getString("JLFULL"),ccc3(240,44,11),1);	
		MessageInfoBox::Instance()->show(ValuesUtil::Instance()->getString("JLFULL"), ccc3(12, 233, 25));
	}
	else if (_energy > MAX_ENERGY-cmd->b_energy)
	{
		Confirm * _confirmBuy = new Confirm();
		_confirmBuy->initWithParam(
			ValuesUtil::Instance()->getString("JLOVER"),
			this,
			menu_selector(RoleUI::clickBuyEnergyConfirm),
			menu_selector(RoleUI::clickCancel));
		LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
		_confirmBuy->release();
	}
	else
	{
		clickBuyEnergyConfirm(0);
	}
}

void RoleUI::onAddEnergy(CCObject * pSender)
{
	// send msg
	clickCancel(0);
	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
	if (mUImediator)
	{
		mUImediator->onAddEnergy();
	}
}

cocos2d::ccColor3B RoleUI::getVipLabelColor(int vipLev)
{
	ccColor3B color;

	if(vipLev == 0)
	{
		//White
		color = ccc3(255, 255, 255);
	}
	else if(vipLev < 4)
	{
		//Green
		color = ccc3(0, 255, 0);
	}
	else if (vipLev < 8)
	{
		//Blue
		color = ccc3(0, 0, 255);
	}
	else if (vipLev < 10)
	{
		//Purple
		color = ccc3(219, 24, 253);
	}
	else
	{
		//Orange
		color = ccc3(255, 165, 0);
	}

	if (_isTrialVip)
	{
		color = ccc3(12, 23, 233);
	}

	return color;
}

void RoleUI::onVipMenuClick( CCObject *pSender )
{
	GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_VIP, NULL);
	if (this->getChildByTag(TAG_VIP_LAYER))
	{
		CCNode * pNode = this->getChildByTag(TAG_VIP_LAYER)->getChildByTag(1001);
		if (pNode)
		{
			stopMyAction(pNode);
		}	
	}
}

void RoleUI::runMyAction(CCNode * pNode , CCAction * pAction)
{
	if (pNode && pAction)
	{
		pNode->runAction(pAction);
	}	
}

void RoleUI::stopMyAction(CCNode * pNode)
{
	if (pNode)
	{
		pNode->stopAllActions();
	}	
}

CCAction * RoleUI::getMyAction()
{
	CCFiniteTimeAction * pFadeOut = CCFadeTo::actionWithDuration(0.5f ,128);
	CCFiniteTimeAction * pFadeIn = CCFadeTo::actionWithDuration(0.5f ,255);
	CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeOut , pFadeIn));
	return pAction;
}

void RoleUI::setVigourBuffCount( int vigourBuffCount, int maxVigourBuffCount )
{
	bool showBuffIcon = false;
	if(vigourBuffCount == maxVigourBuffCount
		&& vigourBuffCount > 0
		&& maxVigourBuffCount < 100)
	{
		// show tips
		showBuffIcon = true;
		LangManager::msgShow("DV001");
	}
	else if (vigourBuffCount > 0)
	{
		// only show buff icon
		showBuffIcon = true;
	}
	else if(vigourBuffCount == 0)
	{
		// dismiss buff icon
		showBuffIcon = false;
	}

	CCNode *pVigourBuffNode = this->getChildByTag(TAG_VIGOUR_BUFF_ICON);
	if(pVigourBuffNode)
	{
		pVigourBuffNode->setIsVisible(showBuffIcon);
	}
}

void RoleUI::clickVigourBuff( CCObject * pSender )
{
	LangManager::msgShow("DV002");
}

void RoleUI::clickGongExpBuff(CCObject * pSender)
{	
	char str[100];
	int eb = RoleManage::Instance()->_accountInfo._gongExpBuffCount;
	sprintf(str, ValuesUtil::Instance()->getString( "GONG016" ).c_str(),
		eb);
	std::string strval = str;
	LangManager::msgStr(strval);
}