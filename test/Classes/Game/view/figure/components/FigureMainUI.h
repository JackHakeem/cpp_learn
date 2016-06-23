#ifndef HLQS_FIGUREMAINUI_H_
#define HLQS_FIGUREMAINUI_H_
#include "LayerNode.h"

USING_NS_CC;

class FigureMainUI : public LayerNode
{
public:
	FigureMainUI();
//	~FigureMainUI();
	bool init();

public:
	void addTabButton(int32 type, int32 sitNum, CCObject* target, SEL_MenuHandler selector);
	void addAllButtons();
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