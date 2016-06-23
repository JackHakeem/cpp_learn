#ifndef _TowerConfirm_H_
#define _TowerConfirm_H_

#include "BaseType.h"

USING_NS_CC;

class Alert;
class TowerConfirm:public LayerNode
{
public:
	TowerConfirm();
	~TowerConfirm();
	bool initWithParam(std::string str,
		CCObject* target, SEL_MenuHandler selector, SEL_MenuHandler selector2, string TowerConfirmStr = "" );
	void handleCancel(CCObject* pSender);
	void diappear(CCObject* pSender);
	bool initWithString(std::string str);
public:
	Alert* m_alert;

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
};

#endif