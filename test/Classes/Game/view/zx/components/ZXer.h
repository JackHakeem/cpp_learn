#pragma once

#include "LayerNode.h"

class ZXer:public LayerNode
{
public:
	ZXer();
	~ZXer();

	bool init(int index);
	void update(int val);
	void clickZX(CCObject* pSender);
public:
	int m_iIndex;
	bool m_bCanClick;
};