#ifndef HLQS_UIBaseView_H_
#define HLQS_UIBaseView_H_
#include "LayerNode.h"

USING_NS_CC;

class UIBaseView : public LayerNode
{
public:
	UIBaseView();
//	virtual ~UIBaseView();
	bool init();

public:
	void addTabButton(int32 type, int32 sitNum, CCObject* target, SEL_MenuHandler selector);
	virtual void addAllButtons();
	void keepButton2State();
public:
	void clickButtonHandler0(CCObject *pSender);

public:
	enum
	{
		TAG_TAB = 100,

	};

	int _btnCount;
};

#endif