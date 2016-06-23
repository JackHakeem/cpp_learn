#pragma once

#include "BaseType.h"

class ListMenu:public LayerNode
{
public:
	ListMenu();
	~ListMenu();

	bool init(CCObject* target);
	void addBtn(SEL_MenuHandler selector, int tag, const char* label);
	void paiban(int type);
	void dispear(CCObject* pSender);
	void itemEnableAll(bool value);
public:
	vector<CCMenuItemSprite*> m_btns;
	CCObject* m_ptarget;
	CCMenu * m_buttonMenu;
};