#include "ActView.h"
#include "manager/PopEventName.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include <cmath>
#include "manager/LayerManager.h"
#include "KKLabelTTF.h"
#include "Confirm.h"
#include "model/player/vo/AccountInfoVo.h"
#include "model/player/RoleManage.h"
#include "HotList.h"
#include "CCUIBackground.h"
#include "../ActMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/ViewManager.h"
#include "ActItem.h"

static float FontSize = 26.0f;
static float FontSize2 = 20.0f;
static float FontSize3 = 22.0f;

ActView::ActView()
{
	_container = 0;
	_pHot = 0;
	_pAct = 0;
}


bool ActView::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	key = PopEventName::GUILD;
	/*this->setContentSize(CCSizeMake(POSX(960), POSX(758)));
	this->setPopContentSize(CCSizeMake(POSX(960), POSX(758)));*/
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	this->setPopContentSize(this->getContentSize());
	//
	_container = new LayerNode();
	this->addChild(_container, 0, 0);
	_container->setAnchorPoint(CCPointZero);
	_container->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
	_container->release();
	//
	{
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame(/*"chat/chat_6.png"*/"ui2.png", ccp(POSX(40), POSX(640-570)),ccp(0,0),
			CCSizeMake(POSX(465-40), POSX(600-145)));
		_container->addChild(_bg1, 1);
		_bg1->release();	

		SpriteNode* sp = new SpriteNode();
		sp->initWithSpriteFrameName("act/hot.png");
		_container->addChild(sp, 3);
		sp->setPosition(ccp(POSX(255), POSX(640-70)));
		sp->release();	

		SpriteNode* spup = new SpriteNode();
		spup->initWithSpriteFrameName("act/direct_up.png");
		_container->addChild(spup, 3);
		spup->setPosition(ccp(POSX(255), POSX(640-100)));
		spup->release();	

		SpriteNode* spdown = new SpriteNode();
		spdown->initWithSpriteFrameName("act/direct_up.png");
		_container->addChild(spdown, 3);
		spdown->setRotation(180.0f);
		spdown->setPosition(ccp(POSX(255), POSX(640-585)));
		spdown->release();	
	}
	{
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame(/*"chat/chat_6.png"*/"ui2.png", ccp(POSX(500), POSX(640-570)),ccp(0,0),
			CCSizeMake(POSX(925-500), POSX(600-145)));
		_container->addChild(_bg1, 1);
		_bg1->release();

		SpriteNode* sp = new SpriteNode();
		sp->initWithSpriteFrameName("act/act.png");
		_container->addChild(sp, 3);
		sp->setPosition(ccp(POSX(718), POSX(640-70)));
		sp->release();

		SpriteNode* spup = new SpriteNode();
		spup->initWithSpriteFrameName("act/direct_up.png");
		_container->addChild(spup, 3);
		spup->setPosition(ccp(POSX(718), POSX(640-100)));
		spup->release();	

		SpriteNode* spdown = new SpriteNode();
		spdown->initWithSpriteFrameName("act/direct_up.png");
		_container->addChild(spdown, 3);
		spdown->setRotation(180.0f);
		spdown->setPosition(ccp(POSX(718), POSX(640-585)));
		spdown->release();	
	}
	//
	_pHot = HotList::listViewWithCCRect(CCRectMake(POSX(50), POSX(640-560), POSX(400), POSX(600-165)), false);
	_pHot->setIsRelativeAnchorPoint(true);
	_pHot->setAnchorPoint(CCPointZero);
	_pHot->setSpacingVertical(POSX(10.0f));
	_pHot->m_pri = TLE::WindowLayer_act;
	_pHot->setWorldSpaceLeftBottomPoint(ccp(_pHot->getPosition().x + _container->getPosition().x + this->getPosition().x,
		_pHot->getPosition().y + _container->getPosition().y + this->getPosition().y));
	_pHot->setOnItemActionListener(_pHot);
	_container->addChild(_pHot, 1, TAG_HotView);
	_pHot->release();
	//
	_pAct = HotList::listViewWithCCRect(CCRectMake(POSX(510), POSX(640-560), POSX(400), POSX(600-165)), false);
	_pAct->setIsRelativeAnchorPoint(true);
	_pAct->setAnchorPoint(CCPointZero);
	_pAct->setSpacingVertical(POSX(/*10.0f*/15.0f));
	_pAct->m_pri = TLE::WindowLayer_act;
	_pAct->setWorldSpaceLeftBottomPoint(ccp(_pAct->getPosition().x + _container->getPosition().x + this->getPosition().x,
		_pHot->getPosition().y + _container->getPosition().y + this->getPosition().y));
	_pAct->setOnItemActionListener(_pAct);
	_container->addChild(_pAct, 1, TAG_ActView);
	_pAct->release();
	return true;
}

ActView::~ActView()
{
	ActMediator* pActMediator = (ActMediator*)g_pFacade->retrieveMediator(AppFacade_Act_CHANGE);
	pActMediator->_actView = 0;

	ViewManager::getInstance()->actView = 0;
}

void ActView::removeDataObjectChild()
{
	for ( std::vector<ActItem*>::iterator it = _pHot-> m_arrItem.begin();
		it != _pHot->m_arrItem.end();
		it++ )
	{
		ActItem* item = *it;
		if (item)
		{
			item->removeFromParentAndCleanup(true);
			item->release();
		}
	}
	_pHot->m_arrItem.clear();

	for ( std::vector<ActItem*>::iterator it = _pAct->m_arrItem.begin();
		it != _pAct->m_arrItem.end();
		it++ )
	{
		ActItem* item = *it;
		if (item)
		{
			item->removeFromParentAndCleanup(true);
			item->release();
		}
	}
	_pAct->m_arrItem.clear();
}



//void ActView::registerWithTouchDispatcher( void )
//{
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::IntervalLayer_guild, true );
//}
//
//bool ActView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
//{
//	return true;
//}
