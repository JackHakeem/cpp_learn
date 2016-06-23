#ifndef __DungeonAwardAction_H_
#define __DungeonAwardAction_H_

#include "cocos2d.h"
#include "socket/command/s37/SCMD376.h"
using namespace cocos2d;


class DungeonAwardAction : public CCLayer
{
public:
	DungeonAwardAction( const CCRect& rect);
	~DungeonAwardAction();

public:
	static DungeonAwardAction* DungeonAwardActionWithRect( const CCRect& rect );
	void initDungeonAwardActionVo( SCMD376& sCMD376 );

	CCRect rect();
	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	CCRect m_rect;
	CCSprite* _pic;

	SCMD376 _sCMD376;
};

#endif