#ifndef _CONFIRM_H_
#define _CONFIRM_H_

#include "BaseType.h"

USING_NS_CC;

class Alert;
class Confirm:public LayerNode
{
public:
	Confirm();
	~Confirm();
	bool initWithParam(std::string str, CCObject* target, SEL_MenuHandler selector, SEL_MenuHandler selector2, string confirmStr = "" );
	void handleCancel(CCObject* pSender);

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
public:
	Alert* m_alert;
};

#endif