#ifndef _MAINNAVIGATEY_H_
#define _MAINNAVIGATEY_H_

#include "BaseType.h"

USING_NS_CC;
class MainNavigateY:public LayerNode
{
public:
	enum
	{
		MainNavigateYZ_menubtn = 0,
	};
	
	enum
	{
		MainNavigateYTAG_menubtn = 0,
	};

	enum 
	{
		MainNavigateY_ENUMTAG_1 = 1,
		MainNavigateY_ENUMTAG_2 = 2,
	};
public:
	MainNavigateY();
	~MainNavigateY();
public:

	void addButton(int32 type, int32 sitNum, CCObject* target, SEL_MenuHandler selector);
	void visit();
	void disappear();
	void hideButtonByType(int type , bool var);


	CC_PROPERTY(bool, _isMenuOpen, isMenuOpen)
public:
	int32 m_slot;
	int32 m_btnCount;
	CCPoint m_endPos;
	int32 m_lastTag;

};

#endif