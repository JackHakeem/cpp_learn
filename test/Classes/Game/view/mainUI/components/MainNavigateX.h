#ifndef _MAINNAVIGATEX_H_
#define _MAINNAVIGATEX_H_

#include "BaseType.h"

USING_NS_CC;
class MainNavigateX:public LayerNode
{
public:
	enum
	{
		MainNavigateXZ_menubtn = 0,
	};
	
	enum
	{
		MainNavigateXTAG_menubtn = 0,
	};

	enum 
	{
		MainNavigateX_ENUMTAG_1 = 1,
		MainNavigateX_ENUMTAG_2 = 2,
	};
public:
	MainNavigateX();
	~MainNavigateX();
public:

	void addButton(int32 type, int32 sitNum, CCObject* target, SEL_MenuHandler selector);
	void visit();
	void disappear();

	void rePosition();
	void reSort(int a[] , int len);
	int getIndex(int n );

	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);

	CC_PROPERTY(bool, _isMenuOpen, isMenuOpen)
public:
	int32 m_slot;
	int32 m_btnCount;
	CCPoint m_endPos;
	int32 m_lastTag;
	int m_posArr[32];
};

#endif