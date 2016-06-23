#include "LoadingLayer.h"

#include "manager/TouchLayerEnum.h"
#include "../TimerManage.h"
#include "../LangManager.h"
#include "utils/ScaleUtil.h"

LoadingLayer::LoadingLayer()
{
	m_actionSprite = 0;
}

LoadingLayer::~LoadingLayer()
{}

bool LoadingLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	//make touch enabled
	this->setIsTouchEnabled(true);

	
	CCSize cs = CCDirector::sharedDirector()->getWinSizeInPixels();

	CCNode* sp = this->getChildByTag(1);
	if (!sp)
	{
		m_actionSprite = CCSprite::spriteWithSpriteFrameName( "ui/loading.png" );
		if(m_actionSprite)
		{
			m_actionSprite->setPosition( ccp( POSX(960/2), POSX(640/2) ) );
			this->addChild( m_actionSprite, 0, 1 );
		}	
	}


	//float fTimeOut = 30.0f;
	//CCActionInterval*  actionBy = CCRotateBy::actionWithDuration(fTimeOut ,  360*30/2);
	//m_actionSprite->runAction( CCSequence::actions(actionBy, 0));

	this->setIsVisible( false );
	return true;
}

//begin
void LoadingLayer::registerWithTouchDispatcher()
{
	//this-> setIsTouchEnabled (true);
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -4, true);
	//CCLayer::onEnter();
}

bool LoadingLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("TLE::LoadingLayer");
	return true;
}

void LoadingLayer::socketWait( PacketID_t idMessage, CCNode* tar, SEL_CallFuncND selector )
{
	this->setIsVisible( true );

	m_actionSprite->stopAllActions();
	CCTouchDispatcher::sharedDispatcher()->removeDelegate( this );
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::LoadingLayer, true);

	float fTimeOut = 8.0f;
	CCActionInterval*  actionBy = CCRotateBy::actionWithDuration(fTimeOut ,  360*30/2);
	m_actionSprite->runAction( CCSequence::actions(actionBy, 0));

	m_releaseLockMessage = idMessage;
	
	m_vCallback.m_pSelectorTarget = tar;
	m_vCallback.m_pCallFuncND = selector;

	TimerManage::Instance()->add( fTimeOut, schedule_selector(LoadingLayer::TimeOutreleaseLock), this );
}

void LoadingLayer::socketWait_old( PacketID_t idMessage )
{
	/*this->setIsVisible( true );

	m_actionSprite->stopAllActions();
	CCTouchDispatcher::sharedDispatcher()->removeDelegate( this );
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::LoadingLayer, true);

	float fTimeOut = 30.0f;
	CCActionInterval*  actionBy = CCRotateBy::actionWithDuration(fTimeOut ,  360*30/2);
	m_actionSprite->runAction( CCSequence::actions(actionBy, 0));

	m_releaseLockMessage = idMessage;

	TimerManage::Instance()->add( fTimeOut, schedule_selector(LoadingLayer::TimeOutreleaseLock), this );*/
}

void LoadingLayer::releaseLock( PacketID_t idMessage )
{
	if ( getIsVisible()
		&& (idMessage == m_releaseLockMessage) )
	{
		this->setIsVisible( false );
		CCTouchDispatcher::sharedDispatcher()->removeDelegate( this );

		if ( m_actionSprite )
		{
			m_actionSprite->stopAllActions();
		}

		TimerManage::Instance()->remove( schedule_selector(LoadingLayer::TimeOutreleaseLock), this );
	}
}

void LoadingLayer::TimeOutreleaseLock( ccTime ct )
{
	this->setIsVisible( false );
	CCTouchDispatcher::sharedDispatcher()->removeDelegate( this );

	if ( m_actionSprite )
	{
		m_actionSprite->stopAllActions();
		m_vCallback.execute();//when timeout run
		m_vCallback.m_pSelectorTarget = 0;
	}

	LangManager::msgShow( "NETTIMEOUT" );
	TimerManage::Instance()->remove( schedule_selector(LoadingLayer::TimeOutreleaseLock), this );
}