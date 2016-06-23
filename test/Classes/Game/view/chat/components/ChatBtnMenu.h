#pragma once

#include "BaseType.h"

class ChatBtnMenu:public cocos2d::CCMenu
{
public:
	ChatBtnMenu();
	~ChatBtnMenu();

    static ChatBtnMenu* menuWithItems(CCMenuItem* item, ...);

	static ChatBtnMenu* menuWithItem(CCMenuItem* item);
	bool initWithItems(CCMenuItem* item, va_list args);
	bool init();
	void step(float dt);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent* event);
	//virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
public:
	float timer;
	//float 
};