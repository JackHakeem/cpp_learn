#ifndef __passGiftSkin_H_
#define __passGiftSkin_H_

#include "cocos2d.h"
#include "MapAwardPanel.h"
#include "socket/command/s14/SCMD140.h"
using namespace cocos2d;

class PassGiftSkin : public CCLayer
{
public:
	PassGiftSkin( const CCRect& rect);
	~PassGiftSkin();

public:
	static PassGiftSkin* passGiftSkinWithRect( const CCRect& rect );
	void initPassGiftSkin( int honorId );

	CCRect rect();
	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	//void doAction();
	CCRect m_rect;
	void onBoxClick(CCObject *pSender);
	//SCMD140 sCMD140;
	int _honorId;
	MapAwardPanel* _passGiftView;
};

#endif