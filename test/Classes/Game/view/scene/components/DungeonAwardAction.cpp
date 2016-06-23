#include "DungeonAwardAction.h"

DungeonAwardAction::DungeonAwardAction( const CCRect& rect)
{
	memset( (void*)&_sCMD376, 0, sizeof(_sCMD376) );
	//CCLayerColor* pLayer = new CCLayerColor();
	//pLayer->initWithColorWidthHeight(  ccc4( 120, 255, 120, 10 ), (GLfloat)rect.size.width, (GLfloat)rect.size.height  );
	//addChild(pLayer);
}

DungeonAwardAction::~DungeonAwardAction()
{

}

DungeonAwardAction* DungeonAwardAction::DungeonAwardActionWithRect(  const CCRect& rect )
{
	DungeonAwardAction* pItem = new DungeonAwardAction(rect);
	if (!pItem->init())
	{
		return 0;
	}
	pItem->setContentSize( rect.size );
	pItem->setPosition( rect.origin );
	pItem->autorelease();

	return pItem;
}

void DungeonAwardAction::initDungeonAwardActionVo( SCMD376& sCMD376 )
{
	_sCMD376 = sCMD376;

	// DungeonAward icon
	CCSize cs = CCDirector::sharedDirector()->getWinSizeInPixels();
	//char strFormat[54];
	_pic = CCSprite::spriteWithFile( "assets/ui/report/award_box.png" );
	if ( !_pic )
	{
		assert(!"pic: not exist!");
		return;
	}
	_pic->setPosition( ccp( cs.width/2, cs.height/2 ) );
	addChild(_pic);
}

void DungeonAwardAction::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void DungeonAwardAction::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

CCRect DungeonAwardAction::rect()
{
	CCSize s = this->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool DungeonAwardAction::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool DungeonAwardAction::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if ( !containsTouchLocation(touch) ) return false;

	return true;
}

void DungeonAwardAction::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//debug("=====================战斗后提示通关奖励===============");

	//if(_dungeonView){
	//	var removefunc:Function = function(e:Event):void{
	//		trace(" _dungeonView dispose already invoke!!!");
	//		_dungeonView.dispose();
	//		_dungeonView = null;
	//	}
	//	_dungeonView.addEventListener(Event.REMOVED_FROM_STAGE, removefunc);
	//	_dungeonView.show(this._sCMD376);
	//	_dungeonView.isPop = true;
	//}

	//this._sCMD376 = null;
}