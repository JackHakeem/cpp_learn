#include "AttributeLayer.h"
#include "FigureCreate.h"
#include "model/player/RoleManage.h"
#include "utils/ValuesUtil.h"
#include "model/figure/LevelExpManage.h"
#include "CCUIBackground.h"
#include "control/AppFacade.h"
#include "mvc/Facade.h"
#include "view/backpack/BagMediator.h"
#include "manager/ViewManager.h"
#include "manager/LayerManager.h"
#include "PopUIBg.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/sound/SoundManager.h"
#include "Message.h"
#include "view/recruit/RecruitMediator.h"
#include "Confirm.h"

const float FontSize = 20.0f;

AttributeLayer::AttributeLayer()
{

}

AttributeLayer::AttributeLayer(CCSize &size)
{
	_layerSize = size;
}

bool AttributeLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCUIBackground* pBack = new CCUIBackground();
	pBack->initWithSpriteFrame("ui2.png", 
		ccp(POSX(-36), POSX(28)),
		ccp(0,0),
		CCSizeMake(POSX(444),POSX(504)));
	this->addChild(pBack , 0);
	pBack->release();

	return true;
}

void AttributeLayer::loadItems()
{
	for (int i = 0;i<300;i++)
	{
		if (this->getChildByTag(i))
		{
			this->removeChildByTag(i,true);
		}
 	}

	if (!g_pFigureScrollView)
	{
		return;
	}
	int nCurScreen = g_pFigureScrollView->currentScreen;
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator it = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = list->begin();
	while ((nCurScreen-1)&&(it != list->end()))
	{
		++it;
		--nCurScreen;
	}
	if (it == list->end())
	{
		return;
	} 
	
	float deltaH = (float)/*_layerSize.height/15*/42.7/* 50*/;
	// merch attribute strings
	CCLabelTTF * s_force		= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("force").c_str(),
		CCSizeMake(POSX(120), POSX(30)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(30));
	CCLabelTTF * s_stamina		= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("stamina").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_strength	= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("strength").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_intelligence = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("intelligence").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_physicAttack	= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PA").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_magicAttack	= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("MA").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_physicDefense = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PD").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_magicDefense	= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("MD").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_jiewei		= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("jiewei").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_zhanhun		= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("zhanhun").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_shengjie	= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("shengjie").c_str(),
		CCSizeMake(POSX(160), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	CCLabelTTF * s_hp	= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("hp").c_str(),
		CCSizeMake(POSX(120), POSX(28)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));

	s_force->setColor(ccc3(240,240,240));
	s_stamina->setColor(ccc3(255,220,0));
	s_strength->setColor(ccc3(255,220,0));
	s_intelligence->setColor(ccc3(255,220,0));
	s_physicAttack->setColor(ccc3(255,220,0));
	s_magicAttack->setColor(ccc3(255,220,0));
	s_physicDefense->setColor(ccc3(255,220,0));
	s_magicDefense->setColor(ccc3(255,220,0));
	s_jiewei->setColor(ccc3(255,100,0));
	s_zhanhun->setColor(ccc3(255,100,0));
	s_shengjie->setColor(ccc3(255,100,0));
	s_hp->setColor(ccc3(255,220,0));

	s_force->setPosition(ccp(POSX(60), POSX(deltaH*11+15)));
	s_stamina->setPosition(ccp(POSX(60), POSX(deltaH*10+15)));
	s_strength->setPosition(ccp(POSX(60), POSX(deltaH*9+15)));
	s_intelligence->setPosition(ccp(POSX(60), POSX(deltaH*8+15)));
	s_physicAttack->setPosition(ccp(POSX(60), POSX(deltaH*7+15)));
	s_magicAttack->setPosition(ccp(POSX(60), POSX(deltaH*6+15)));
	s_physicDefense->setPosition(ccp(POSX(60), POSX(deltaH*5+15)));
	s_magicDefense->setPosition(ccp(POSX(60), POSX(deltaH*4+15)));
	s_jiewei->setPosition(ccp(POSX(60), POSX(deltaH*3+15)));
	s_zhanhun->setPosition(ccp(POSX(220), POSX(deltaH*3+15)));
	s_shengjie->setPosition(ccp(POSX(260), POSX(deltaH*2+15)));
	s_hp->setPosition(ccp(POSX(60), POSX(deltaH*3+15)));

	this->addChild(s_force,Z_ITEM,TAG_STRING);
	this->addChild(s_stamina,Z_ITEM,TAG_STRING+1);
	this->addChild(s_strength,Z_ITEM,TAG_STRING+2);
	this->addChild(s_intelligence,Z_ITEM,TAG_STRING+3);
	this->addChild(s_physicAttack,Z_ITEM,TAG_STRING+4);
	this->addChild(s_magicAttack,Z_ITEM,TAG_STRING+5);
	this->addChild(s_physicDefense,Z_ITEM,TAG_STRING+6);
	this->addChild(s_magicDefense,Z_ITEM,TAG_STRING+7);
	this->addChild(s_jiewei,Z_ITEM,TAG_STRING+8);
	this->addChild(s_zhanhun,Z_ITEM,TAG_STRING+9);
	this->addChild(s_shengjie,Z_ITEM,TAG_STRING+10);
	this->addChild(s_hp,Z_ITEM,TAG_STRING+11);


	// follows are values
	char stamina[8];
	char enStamina[8];
	char strength[8];
	char enStrength[8];
	char intelligence[8];
	char enIntelligence[8];
	char physicAttck[32];
	char magicAttck[32];
	char physicDefense[32];
	char magicDefense[32];
	char force[8];
	char jiewei[8];
	char zhanhunlv[8];
	char needLev[8];
	char hp[32];

	sprintf(stamina,"%d",it->second.figureBaseInfo.stamina);
	sprintf(enStamina,"+ %d",it->second.figureBaseInfo.plus_sta);
	sprintf(strength,"%d",it->second.figureBaseInfo.strength);
	sprintf(enStrength,"+ %d",it->second.figureBaseInfo.plus_str);
	sprintf(intelligence,"%d",it->second.figureBaseInfo.intellect);
	sprintf(enIntelligence,"+ %d",it->second.figureBaseInfo.plus_int);
	sprintf(force,"%d",it->second.figureBaseInfo.attPoint);
	sprintf(physicAttck,"%d",it->second.figureBaseInfo.pAttack);
	sprintf(magicAttck,"%d",it->second.figureBaseInfo.mAttack);
	sprintf(physicDefense,"%d",it->second.figureBaseInfo.pDefense);
	sprintf(magicDefense,"%d",it->second.figureBaseInfo.mDefense);
	sprintf(jiewei,"%d",it->second.figureBaseInfo.rebornNum);
	sprintf(zhanhunlv,ValuesUtil::Instance()->getString("zhanhunlv").c_str(),it->second.playerBaseInfo.adLv);
	sprintf(needLev,"%d",it->second.figureBaseInfo.rebornNum*5+51);
	sprintf(hp,"%d",it->second.playerBaseInfo.hp());

	CCLabelTTF * v_stamina		= CCLabelTTF::labelWithString(stamina,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_enStamina	= CCLabelTTF::labelWithString(enStamina,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_strength	= CCLabelTTF::labelWithString(strength,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_enStrength	= CCLabelTTF::labelWithString(enStrength,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_intelligence = CCLabelTTF::labelWithString(intelligence,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_enIntelligence = CCLabelTTF::labelWithString(enIntelligence,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_force		= CCLabelTTF::labelWithString(force,CCSizeMake(POSX(220),POSX(42)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(42));
	CCLabelTTF * v_physicAttack	= CCLabelTTF::labelWithString(physicAttck,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_magicAttack	= CCLabelTTF::labelWithString(magicAttck,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_physicDefense = CCLabelTTF::labelWithString(physicDefense,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_magicDefense	= CCLabelTTF::labelWithString(magicDefense,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_jiewei	= CCLabelTTF::labelWithString(jiewei,CCSizeMake(POSX(100),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_zhanhun = CCLabelTTF::labelWithString(zhanhunlv,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_needLev	= CCLabelTTF::labelWithString(needLev,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));
	CCLabelTTF * v_hp	= CCLabelTTF::labelWithString(hp,CCSizeMake(POSX(120),POSX(28)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(28));

	v_stamina->setColor(ccc3(240,240,240));
	v_enStamina->setColor(ccc3(28,129,233));
	v_strength->setColor(ccc3(240,240,240));
	v_enStrength->setColor(ccc3(28,129,233));
	v_intelligence->setColor(ccc3(240,240,240));
	v_enIntelligence->setColor(ccc3(28,129,233));
	v_force->setColor(ccc3(12,233,25));
	v_physicAttack->setColor(ccc3(240,240,240));
	v_magicAttack->setColor(ccc3(240,240,240));
	v_physicDefense->setColor(ccc3(240,240,240));
	v_magicDefense->setColor(ccc3(240,240,240));
	v_jiewei->setColor(ccc3(28,129,233));
	v_zhanhun->setColor(ccc3(28,129,233));
	v_needLev->setColor(ccc3(77,240,240));
	v_hp->setColor(ccc3(12,233,25));

	v_force->setPosition(ccp(POSX(170), POSX(deltaH*11+12)));
	v_stamina->setPosition(ccp(POSX(230), POSX(deltaH*10+15)));
	v_enStamina->setPosition(ccp(POSX(290), POSX(deltaH*10+15)));
	v_strength->setPosition(ccp(POSX(230), POSX(deltaH*9+15)));
	v_enStrength->setPosition(ccp(POSX(290), POSX(deltaH*9+15)));
	v_intelligence->setPosition(ccp(POSX(230), POSX(deltaH*8+15)));
	v_enIntelligence->setPosition(ccp(POSX(290), POSX(deltaH*8+15)));
	v_physicAttack->setPosition(ccp(POSX(230), POSX(deltaH*7+15)));
	v_magicAttack->setPosition(ccp(POSX(230), POSX(deltaH*6+15)));
	v_physicDefense->setPosition(ccp(POSX(230), POSX(deltaH*5+15)));
	v_magicDefense->setPosition(ccp(POSX(230), POSX(deltaH*4+15)));
	v_jiewei->setPosition(ccp(POSX(170), POSX(deltaH*3+15)));
	v_zhanhun->setPosition(ccp(POSX(310), POSX(deltaH*3+15)));
	v_needLev->setPosition(ccp(POSX(220), POSX(deltaH*2+15)));
	v_hp->setPosition(ccp(POSX(230), POSX(deltaH*3+15)));

	this->addChild(v_force,Z_ITEM+1,TAG_VALUE);
	this->addChild(v_stamina,Z_ITEM+1,TAG_VALUE+1);
	this->addChild(v_enStamina,Z_ITEM+1,TAG_VALUE+2);
	this->addChild(v_strength,Z_ITEM+1,TAG_VALUE+3);
	this->addChild(v_enStrength,Z_ITEM+1,TAG_VALUE+4);
	this->addChild(v_intelligence,Z_ITEM+1,TAG_VALUE+5);
	this->addChild(v_enIntelligence,Z_ITEM+1,TAG_VALUE+6);
	this->addChild(v_physicAttack,Z_ITEM+1,TAG_VALUE+7);
	this->addChild(v_magicAttack,Z_ITEM+1,TAG_VALUE+8);
	this->addChild(v_physicDefense,Z_ITEM+1,TAG_VALUE+9);
	this->addChild(v_magicDefense,Z_ITEM+1,TAG_VALUE+10);
	this->addChild(v_jiewei,Z_ITEM+1,TAG_VALUE+11);
	this->addChild(v_zhanhun,Z_ITEM+1,TAG_VALUE+12);
	this->addChild(v_needLev,Z_ITEM+1,TAG_VALUE+13);
	this->addChild(v_hp,Z_ITEM+1,TAG_VALUE+14);

	// values bg
	CCUIBackground * _valueBg0 = new CCUIBackground();
	_valueBg0->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*11+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(50)));
	this->addChild(_valueBg0,Z_ITEM,TAG_VALUE_BG);
	_valueBg0->release();
	CCUIBackground * _valueBg1 = new CCUIBackground();
	_valueBg1->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*10+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg1,Z_ITEM,TAG_VALUE_BG+1);
	_valueBg1->release();
	CCUIBackground * _valueBg2 = new CCUIBackground();
	_valueBg2->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*9+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg2,Z_ITEM,TAG_VALUE_BG+2);
	_valueBg2->release();
	CCUIBackground * _valueBg3 = new CCUIBackground();
	_valueBg3->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*8+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg3,Z_ITEM,TAG_VALUE_BG+3);
	_valueBg3->release();
	CCUIBackground * _valueBg4 = new CCUIBackground();
	_valueBg4->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*7+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg4,Z_ITEM,TAG_VALUE_BG+4);
	_valueBg4->release();
	CCUIBackground * _valueBg5 = new CCUIBackground();
	_valueBg5->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*6+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg5,Z_ITEM,TAG_VALUE_BG+5);
	_valueBg5->release();
	CCUIBackground * _valueBg6 = new CCUIBackground();
	_valueBg6->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*5+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg6,Z_ITEM,TAG_VALUE_BG+6);
	_valueBg6->release();
	CCUIBackground * _valueBg7 = new CCUIBackground();
	_valueBg7->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*4+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg7,Z_ITEM,TAG_VALUE_BG+7);
	_valueBg7->release();
	CCUIBackground * _valueBg8 = new CCUIBackground();
	_valueBg8->initWithSpriteFrame("new/select_bg.png",ccp(POSX(150), POSX(deltaH*3+10)),ccp(0,0),CCSizeMake(POSX(60),POSX(40)));
	this->addChild(_valueBg8,Z_ITEM,TAG_VALUE_BG+8);
	_valueBg8->release();
	CCUIBackground * _valueBg9 = new CCUIBackground();
	_valueBg9->initWithSpriteFrame("new/select_bg.png",ccp(POSX(300), POSX(deltaH*3+10)),ccp(0,0),CCSizeMake(POSX(80),POSX(40)));
	this->addChild(_valueBg9,Z_ITEM,TAG_VALUE_BG+9);
	_valueBg9->release();
	CCUIBackground * _valueBg10 = new CCUIBackground();
	_valueBg10->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*2+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg10,Z_ITEM,TAG_VALUE_BG+10);
	_valueBg10->release();
	CCUIBackground * _valueBg11 = new CCUIBackground(); // HP
	_valueBg11->initWithSpriteFrame("new/select_bg.png",ccp(POSX(180), POSX(deltaH*3+10)),ccp(0,0),CCSizeMake(POSX(200),POSX(40)));
	this->addChild(_valueBg11,Z_ITEM,TAG_VALUE_BG+11);

	// hide reborn handle
	s_jiewei->setIsVisible(false);
	v_jiewei->setIsVisible(false);
	s_zhanhun->setIsVisible(false);
	v_zhanhun->setIsVisible(false);
	s_shengjie->setIsVisible(false);
	v_needLev->setIsVisible(false);
	_valueBg8->setIsVisible(false);
	_valueBg9->setIsVisible(false);
	_valueBg10->setIsVisible(false);


	// bag button	
	{
		{
			CCMenuItemSprite *_bagButtonImg = CCMenuItemSprite::itemFromNormalSprite(
				CCSprite::spriteWithSpriteFrameName("button.png"),
				CCSprite::spriteWithSpriteFrameName("button1.png"),
				this, 
				menu_selector(AttributeLayer::clickButtonBag));
			CCMenu *_buttonBag = CCMenu::menuWithItems(_bagButtonImg, NULL);
			_buttonBag->setPosition(ccp(POSX(220/*-100*/), POSX(deltaH*1+22)));
			_buttonBag->setTouchLayer(TLE::WindowLayer_Figure);
			this->addChild(_buttonBag, 0,TAG_BUTTON);

			CCLabelTTF* pbagButtonLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("BAG004").c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
			pbagButtonLabel->setPosition(ccp(_bagButtonImg->getContentSize().width/2, _bagButtonImg->getContentSize().height/2));
			_bagButtonImg->addChild(pbagButtonLabel, 0, 0);
			pbagButtonLabel->setColor(ccc3(254, 189, 0));
		}


	}
	
	
	
	// reborn button
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(pNormalSprite && pPressedSprite)
	{
		CCMenuItemSprite *_pRebornImg = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(AttributeLayer::onClickButtonRebornTips));
		CCMenu *_pButtonReborn = CCMenu::menuWithItems(_pRebornImg, NULL);
		_pButtonReborn->setPosition(ccp(POSX(300), POSX(deltaH*1+22)));
		_pButtonReborn->setTouchLayer(TLE::WindowLayer_Figure);
		_pButtonReborn->setIsVisible(false);
		this->addChild(_pButtonReborn, 0,TAG_BUTTON+1);

		CCLabelTTF* pRebornButtonLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("PY24").c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		pRebornButtonLabel->setPosition(ccp(_pRebornImg->getContentSize().width/2, _pRebornImg->getContentSize().height/2));
		_pRebornImg->addChild(pRebornButtonLabel, 0, 0);
		pRebornButtonLabel->setColor(ccc3(254, 189, 0));
	}
	

	// setAnchorPoint
	for (int i = 0;i<300;i++)
	{
		if (this->getChildByTag(i))
		{
			this->getChildByTag(i)->setAnchorPoint(CCPointZero);
			this->getChildByTag(i)->setIsRelativeAnchorPoint(true);
		}
	}


	
}

void AttributeLayer::onClickButtonRebornTips(CCObject * pSender)
{
	PeiyangView * pPeiyangView = ViewManager::getInstance()->_peiyangView;
	if (pPeiyangView)
	{
		pPeiyangView->clickRebornHandler(0);
	}
	else
	{
		clickButtonReborn(0);
	}
}

void AttributeLayer::clickButtonBag(CCObject * pSender)
{
	ViewManager::getInstance()->figureView->changeStage(1);// = _bankView;
	// add code here
	BagMediator* p = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
	p->bagPop();

	PopUIBg* _PopUIBg = (PopUIBg*)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_PopUIBg);
	if (_PopUIBg)
	{
		_PopUIBg->setBackBtnShow(true);
	}

	SoundManager::Instance()->playPopContainerEffectSound();
}

void AttributeLayer::clickButtonDismiss(CCObject * pSender)
{
	int nCurScreen = g_pFigureScrollView->currentScreen;
	int count = nCurScreen;
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	while (count-1)
	{
		++iter;
		--count;
	}
	if (iter != list->end())
	{
		Confirm* pConfirm = new Confirm();
		pConfirm->initWithParam( LangManager::getText("RCR049", iter->second.playerBaseInfo.name.c_str()).c_str(),
			this, menu_selector(AttributeLayer::shureToDismiss),
			menu_selector(AttributeLayer::cancelToDismiss));
		LayerManager::tipsLayer->addChild(pConfirm,
			TipsLayer::TipsLayerZ_confirmFrame,
			TipsLayer::TipsLayerTAG_confirmFrame);
		pConfirm->release();
	}
}


void AttributeLayer::shureToDismiss(CCObject* obj)
{
	// add code here
	if (!g_pFigureScrollView)
	{
		return;
	}
	int nCurScreen = g_pFigureScrollView->currentScreen;
	int count = nCurScreen;
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	while (count-1)
	{
		++iter;
		--count;
	}
	if (iter != list->end())
	{
		int curAccount = iter->first.id;
		RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
		if ( pRecruitMediator )
		{
			pRecruitMediator->dismissMercHandler( curAccount );
		}

	}

	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void AttributeLayer::cancelToDismiss( CCObject* obj )
{
	//remove自己
	Confirm* pConfirm = (Confirm*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pConfirm && pConfirm->getParent())
		pConfirm->getParent()->removeChild(pConfirm, true);
}

void AttributeLayer::clickButtonReborn(CCObject * pSender)
{
	// add code here
	if (!g_pFigureScrollView)
	{
		return;
	}
	int nCurScreen = g_pFigureScrollView->currentScreen;
	int count = nCurScreen;
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	while (count-1)
	{
		++iter;
		--count;
	}
	if (iter != list->end())
	{
		int curAccount = iter->first.id;
		int starLev = iter->second.figureBaseInfo.rebornNum;
		int reBornNeedLev = 51 + starLev * 5;

		if ((iter->second.playerBaseInfo._lev < reBornNeedLev))
		{
			char path[128] = {0};
			sprintf(path,ValuesUtil::Instance()->getString("PY25").c_str(),reBornNeedLev);
			Message::Instance()->show(path,ccc3(233,12,25),2.0f);
			return;
		}
		else if (iter->second.playerBaseInfo.adLv != 0)
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("PY32").c_str(),ccc3(233,12,25),2.0f);
			return;
		}
		FigureMediator * pFigureMediator = (FigureMediator *)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
		if (pFigureMediator)
		{
			pFigureMediator->sendRebornRequest(curAccount);
		}
	}
}