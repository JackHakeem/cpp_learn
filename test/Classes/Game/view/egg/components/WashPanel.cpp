#include "WashPanel.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "model/egg/EggProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "GoodsItem.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "view/egg/EggMediator.h"
#include "model/backpack/GoodsManager.h"
#include "utils/ColorUtil.h"
#include "events/GameDispatcher.h"
#include "utils/TipHelps.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "utils/loader/KKAnimationFactory.h"
#include "Confirm.h"


#define w_bg1 POSX(928.0f)
#define h_bg1 POSX(562.0f)

#define w_bg2 POSX(910.0f)
#define h_bg2 POSX(524.0f)

const float FontSize = 24.0f;
const float FontSize2 = 24.0f;

WashPanel::WashPanel()
{
	_pic = 0;
	_goodsId = 0;
	_txtName = 0;
	_sEgg[0] = 1151;
	_sEgg[1] = 1154;
	_sEgg[2] = 1171;
	_sEgg[3] = 1172;
	_sEgg[4] = 1174;

	_picbtn = 0;

	_dispatcher = GameDispatcher::getInstance();

	_tips = 0;
}

WashPanel::~WashPanel()
{
	if (myInfo)
	{
		delete myInfo;
		myInfo = 0;
	}
	if (_tips)
		delete _tips;

}

bool WashPanel::init()
{
	if (!LayerNode::init())
		return false;

	this->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
	//
	_icon = new LayerNode();
	_icon->init();
	this->addChild(_icon, 3);
	_icon->release();
	_icon->setPosition(ccp(POSX(488), POSX(640-280)));
	//
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/egg/washpanel_itembg.png");
		_icon->addChild(sp, 1);
		sp->release();
	}
	//_txtName
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("_txtName", CCSizeMake(POSX(300), POSX(36.0f)), CCTextAlignmentCenter, "Arial", POSX(30.0f));
		pLabel->setPosition(ccp(POSX(490), POSX(640-374)));
		this->addChild(pLabel, 4);
		pLabel->setColor(ccc3(255, 255, 255));	

		_txtName = pLabel;
	}
	//
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	{
		CCUIBackground* _bg0 = new CCUIBackground();
		_bg0->initWithFile("assets/ui/ui2.png", CCPointZero,CCPointZero,screenSize);
		this->addChild(_bg0, 0);
		_bg0->release();
	}
	{
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(292), POSX(640-627)), ccp(0,0), CCSizeMake(POSX(690-292), POSX(627-63)));
		this->addChild(_bg1, 1);
		_bg1->release();
	}
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(313), POSX(640-608)), ccp(0,0), CCSizeMake(POSX(669-313), POSX(608-83)));
		this->addChild(_bg2, 1);
		_bg2->release();
	}
	//<item key="EGG036" text="恭喜你" />
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("EGG036").c_str(), CCSizeMake(POSX(300), POSX(36.0f)), CCTextAlignmentCenter, "Arial", POSX(30.0f));
		pLabel->setPosition(ccp(POSX(487), POSX(640-128)));
		this->addChild(pLabel, 5);
		pLabel->setColor(ccc3(244, 244, 85));	
	}
	//<item key="EGG037" text="获得极品奖励" />
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("EGG037").c_str(), CCSizeMake(POSX(300), POSX(36.0f)), CCTextAlignmentCenter, "Arial", POSX(30.0f));
		pLabel->setPosition(ccp(POSX(487), POSX(640-163)));
		this->addChild(pLabel, 5);
		pLabel->setColor(ccc3(244, 244, 85));	
	}
	//<item key="EGG038" text="洗礼主宰更生及给与灵命" />
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("EGG038").c_str(), CCSizeMake(POSX(300), POSX(25.0f)), CCTextAlignmentCenter, "Arial", POSX(25.0f));
		pLabel->setPosition(ccp(POSX(487), POSX(640-422)));
		this->addChild(pLabel, 5);
		pLabel->setColor(ccc3(80, 239, 243));	
	}
	//<item key="EGG039" text="可通过洗礼重新抽取奖励物品" />
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("EGG039").c_str(), CCSizeMake(POSX(300), POSX(25.0f)), CCTextAlignmentCenter, "Arial", POSX(25.0f));
		pLabel->setPosition(ccp(POSX(487), POSX(640-449)));
		this->addChild(pLabel, 5);
		pLabel->setColor(ccc3(164, 154, 147));	
	}
	//<item key="EGG040" text="每次洗礼花费20金币" />
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString("EGG040").c_str(), CCSizeMake(POSX(300), POSX(25.0f)), CCTextAlignmentCenter, "Arial", POSX(25.0f));
		pLabel->setPosition(ccp(POSX(487), POSX(640-474)));
		this->addChild(pLabel, 5);
		pLabel->setColor(ccc3(244, 244, 85));	
	}
	//name_bg
	{
		CCUIBackground* _bg2 = new CCUIBackground();
		_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(385), POSX(640-395)), ccp(0,0), CCSizeMake(POSX(597-385), POSX(395-353)));
		this->addChild(_bg2, 2);
		_bg2->release();
	}

	//X
	{
		CCMenuItemSprite* _btn = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png"), 
			CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png"), 
			this, 
			menu_selector(WashPanel::close) );
		_btn->setPosition(ccp(POSX(718), POSX(640-34)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_egg);
		this->addChild(buttonMenu);	
	}
	//洗礼
	{	
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/button3_0.png", 
			"assets/ui/egg/button3_1.png",
			"assets/ui/button2.png",
			this, 
			menu_selector(WashPanel::washHandler) );
		_btn->setPosition(ccp(POSX(407), POSX(640-560)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_egg);
		this->addChild(buttonMenu, 3);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("EGG041").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(217, 210, 193));
	}	
	//拾取
	{	
		CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/egg/button3_0.png", 
			"assets/ui/egg/button3_1.png",
			"assets/ui/button2.png",
			this, 
			menu_selector(WashPanel::getHandler) );
		_btn->setPosition(ccp(POSX(575), POSX(640-560)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_egg);
		this->addChild(buttonMenu, 3);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("EGG042").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(217, 210, 193));
	}	
	return true;
}

/** 洗礼 */
void WashPanel::washHandler(CCObject* pSender)
{
	//for(int i = 0; i < 5; i++)
	//{
	//	if(_goodsId == _sEgg[i]){i
	//		var str:String = "";
	//		str += LangManager.getText("EGG029");
	//		str += "<font color='#";
	//		str	+= ColorUtil.getGoodColor(GoodsManager.getInstance().getBasicGood(_goodsId).quality).toString(16);
	//		str += "'>";
	//		str += GoodsManager.getInstance().getBasicGood(_goodsId).goodName;
	//		str += "</font>,"
	//		str += LangManager.getText("EGG030");
	//		Alert.show(str,Sentence.PROMPT,1,okFunction,null,Sentence.CONFIRM,Sentence.CANCEL);
	//		return;
	//	}
	//}
	GoodsBasic *goodsBasic = g_pGoodsManager->getBasicGood(_goodsId);
	if(goodsBasic->type != 2)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);//close tips

		_dispatcher->dispatchEvent(EggMediator::WASH_EGG, &_eggId);		
	}
	else
	{
		Confirm* pConfirm = new Confirm();
		pConfirm->initWithParam(LangManager::getText("EGG044").c_str(), this, menu_selector(WashPanel::sureWash),menu_selector(WashPanel::sureWashCancel));
		LayerManager::preTipsLayer->addChild(pConfirm,PreTipsLayer::PreTipsLayerZ_eggWashConfirm, PreTipsLayer::PreTipsLayerTAG_eggWashConfirm);
		pConfirm->release();	
	}		
}

void WashPanel::sureWash(CCObject* pSender)
{
	//sure to wash
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);//close tips

	_dispatcher->dispatchEvent(EggMediator::WASH_EGG, &_eggId);		
	//close ui
	CCNode* pConfirm = LayerManager::preTipsLayer->getChildByTag(PreTipsLayer::PreTipsLayerTAG_eggWashConfirm);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}

void WashPanel::sureWashCancel(CCObject* pSender)
{
	//close ui
	CCNode* pConfirm = LayerManager::preTipsLayer->getChildByTag(PreTipsLayer::PreTipsLayerTAG_eggWashConfirm);
	if (pConfirm)
		pConfirm->removeFromParentAndCleanup(true);
}

/** 拾取 */
void WashPanel::getHandler(CCObject* pSender)
{
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);//close tips

	struct sdata 
	{
		int eggId;
		int num;
	};
	sdata d;
	d.eggId = _eggId;
	d.num = 1;

	_dispatcher->dispatchEvent(EggMediator::GET_EGG, &d);
}

void WashPanel::close(CCObject* pSender)
{
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);//close tips

	WashPanel* pthis = (WashPanel*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_egg_washPanel);
	if (pthis)
		pthis->removeFromParentAndCleanup(true);
}

/**
	* 更新洗礼面板上的物品显示
	* @param goodsId	物品Id
	* 
	*/		
void WashPanel::updateGoods(int goodsId, int goodsNum)
{
	if (_pic)
	{
		_pic->removeFromParentAndCleanup(true);
		_pic = 0;
	}

	_goodsId = goodsId;





	char path[50];
	//sprintf(path, "goods/%d.png", goodsId);
	sprintf(path, "assets/icon/goods/%d.png", goodsId);

	//_pic = new SpriteNode();
	//_pic->initWithSpriteFrameName(path);
	//_icon->addChild(_pic, 1);
	//_pic->release();
		
	//_pic
	{
		//CCSprite* p1 = CCSprite::spriteWithSpriteFrameName(path);
		CCMenuItemSprite* _btn = CCMenuItemImage::itemFromNormalSprite(
			//CCSprite::spriteWithSpriteFrameName(path),
			//CCSprite::spriteWithSpriteFrameName(path),
			CCSprite::spriteWithFile(path),
			CCSprite::spriteWithFile(path),
			this, 
			menu_selector(WashPanel::onTips) );
		_btn->setPosition(ccp(POSX(-2), POSX(-2)));
		//_btn->setAnchorPoint(ccp(0, 0));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( ccp( POSX(0), POSX(0)) );
		buttonMenu->setTouchLayer(TLE::TipsLayer_egg);
		//buttonMenu->setAnchorPoint(ccp(0, 0));
		_icon->addChild(buttonMenu, 4);
		_pic = buttonMenu;

		_picbtn = _btn;

	}
	//_txtNum->
	//_txtNum.text = goodsNum > 1 ? goodsNum.toString():"";

	updateTips(goodsId);

	//
	CCAnimation* clickEffect = g_pKKAnimationFactory->registAni(
		"assets/effect/strengEff/strengEff.plist",
		"streng%02d.png", 20, 0.1f);
	if ( !clickEffect )
	{
		return;
	}

	CCSprite* _clickEffectMc = (CCSprite*)_picbtn->getChildByTag(1000);

	if ( !_clickEffectMc )
	{

		_clickEffectMc = new CCSprite();
		_clickEffectMc->init();
		_picbtn->addChild(_clickEffectMc);
		_clickEffectMc->setTag(1000);
		_clickEffectMc->release();

		_clickEffectMc->setPosition(  ccp(POSX(50), POSX(50))  );

		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(WashPanel::PlayEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect ), 
			callBack, 
			NULL );
		_clickEffectMc->runAction( action );
	}
	else
	{
		if (_clickEffectMc->getIsVisible())
		{
			return;
		}
		
		cocos2d::CCCallFunc *callBack = cocos2d::CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(WashPanel::PlayEffectComplete));
		cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::actions(
			cocos2d::CCAnimate::actionWithAnimation( clickEffect ), 
			callBack, 
			NULL );
		_clickEffectMc->runAction( action );

		_clickEffectMc->setIsVisible(true);
	}

	//
}

void WashPanel::PlayEffectComplete( CCNode* pnode )
{
	CCSprite* _clickEffectMc = (CCSprite*)_pic->getChildByTag(1000);
	if ( _clickEffectMc )
	{
		_clickEffectMc->setIsVisible(false);
	}
}

CCSize WashPanel::getSrcContentSize()
{
    CCSize size = CCSizeMake(POSX(25*2), POSX( (640-152)*2));
	return size;
}

void WashPanel::updateTips(int goodsId)
{
	//??TIPS
	if (!_tips)
	{
		_tips = new TipHelps();
	}
	_tips->init(true, TipConst::BANK);
	_tips->setToolTips(this, this);

	GoodsInfo* info = new GoodsInfo();
	GoodsBasic* goods = g_pGoodsManager->getBasicGood( goodsId );
	if (!goods) return;
	info->name = goods->goodName;
	info->type = goods->type;
	info->equip_type = goods->equip_type;
	info->quality = goods->quality; 
	info->explain = GoodsToolTips::getExplain(goods, false, info->number);
	
	this->myInfo = info;


	if (_txtName)
	{
		_txtName->setColor(ColorUtil::getGoodColor(goods->quality));
		_txtName->setString(goods->goodName.c_str());
	}
}

void WashPanel::onTips(CCObject* pSender)
{
	CCNode* pTips = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow);
	if (pTips)//if tips is exist,return
		return;

	if (_tips)
		_tips->rollOverHander();
}