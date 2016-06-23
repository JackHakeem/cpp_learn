#include "PassGiftSkin.h"
#include "utils/ScaleUtil.h"
#include "../ReportMediator.h"
#include "view/honor/HonorMediator.h"
#include "model/honor/vo/HonorManage.h"
#include "manager/TouchLayerEnum.h"
#include "manager/sound/SoundManager.h"

const int TOUCH_LAYER = -2000;
PassGiftSkin::PassGiftSkin( const CCRect& rect)
{
	//memset( &sCMD140, 0, sizeof(sCMD140) );
	_passGiftView = 0;
	_honorId = 0;

	//CCLayerColor* pLayer = new CCLayerColor();
	//pLayer->initWithColorWidthHeight(  ccc4( 120, 255, 120, 100 ), (GLfloat)rect.size.width, (GLfloat)rect.size.height  );
	//addChild(pLayer);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/report/res_report.plist");
}

PassGiftSkin::~PassGiftSkin()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/report/res_report.plist");
}

PassGiftSkin* PassGiftSkin::passGiftSkinWithRect(  const CCRect& rect )
{
	PassGiftSkin* pItem = new PassGiftSkin(rect);
	if (!pItem->init())
	{
		return 0;
	}
	pItem->setContentSize( rect.size );
	pItem->setPosition( rect.origin );
	//pItem->autorelease();

	return pItem;
}

void PassGiftSkin::initPassGiftSkin( int honorId )
{
	_honorId = honorId;

	CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("report/award_box_normal.png");
	CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("report/award_box_pressed.png");
	CCMenuItemSprite *pItemImage = CCMenuItemImage::itemFromNormalSprite(
		p1,
		p2,
		this,
		menu_selector(PassGiftSkin::onBoxClick));
	pItemImage->setAnchorPoint(CCPointZero);
	pItemImage->setPosition( ccp( m_rect.size.width/2 - POSX(80), 0 ) );
	CCMenu *pBoxMenu = CCMenu::menuWithItem(pItemImage);
	pBoxMenu->setTouchLayer(TOUCH_LAYER - 1);
	pBoxMenu->setPosition(CCPointZero);
	this->addChild(pBoxMenu);

	CCSprite* _pic = CCSprite::spriteWithSpriteFrameName( "report/click_award.png" );
	if ( !_pic ) return;
	_pic->setAnchorPoint( CCPointZero );
	_pic->setPosition( ccp( m_rect.size.width/2, POSX(230) ) );
	CCFiniteTimeAction *moveToAction = CCMoveTo::actionWithDuration(0.3, ccp( m_rect.size.width/2, POSX(230) ));
	CCFiniteTimeAction *moveBackAction = CCMoveTo::actionWithDuration(0.3, ccp( m_rect.size.width/2, POSX(210) ));
	CCAction *pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(moveToAction, moveBackAction));
	_pic->runAction(pAction);
	this->addChild(_pic);

	_passGiftView = new MapAwardPanel();
	_passGiftView->init();
}

void PassGiftSkin::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TOUCH_LAYER, true);
	CCLayer::onEnter();
}

void PassGiftSkin::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

CCRect PassGiftSkin::rect()
{
	CCSize s = this->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool PassGiftSkin::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool PassGiftSkin::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//if ( !containsTouchLocation(touch) ) return false;

	return true;
}

void PassGiftSkin::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//doAction();

	//g_pHonorMediator->updateHonorAwardComplete(_honorId);

	//Doyang 20120725
	//HonorGoodVo* honorGoodsVo = HonorManage::Instance()->getHonorGoodsVo(_honorId);
	//if ( honorGoodsVo )
	//{
	//	g_pReportMediator->_arward->init( honorGoodsVo );
	//}
	//if (  CCNode* pObject = (CCNode*)this->getParent()  )
	//{
	//	pObject->removeChild( this, true );
	//}
	//
	////this->setIsVisible(false);
	//SoundManager::Instance()->playOpenBoxEffectSound();
}

void PassGiftSkin::onBoxClick( CCObject *pSender )
{
	HonorGoodVo* honorGoodsVo = HonorManage::Instance()->getHonorGoodsVo(_honorId);
	if ( honorGoodsVo )
	{
		g_pReportMediator->_arward->init( honorGoodsVo );
	}
	if (  CCNode* pObject = (CCNode*)this->getParent()  )
	{
		pObject->removeChild( this, true );
	}
	
	//this->setIsVisible(false);
	SoundManager::Instance()->playOpenBoxEffectSound();
}


//void passGiftSkin::doAction()
//{
//	cocos2d::CCLog("=====================战斗后提示通关奖励===============");
//
//	if( _passGiftView )
//	{
//		//var removefunc:Function = function(e:Event):void
//		//{
//		//	trace(" _dungeonView dispose already invoke!!!");
//		//	_dungeonView.dispose();
//		//	_dungeonView = null;
//		//}
//		//_dungeonView.addEventListener(Event.REMOVED_FROM_STAGE, removefunc);
//		_passGiftView->show(sCMD140);
//		_passGiftView->setisPop( !_passGiftView->getisPop() );
//		if ( _passGiftView->getisPop() )
//		{
//			//this->setIsVisible( false );
//			this->removeAllChildrenWithCleanup(true);
//			if ( this->getParent() )
//			{
//				this->getParent()->removeChild( this, true );
//			}
//			
//		}
//	}
//
//	memset( &sCMD140, 0, sizeof(sCMD140) );
//}
