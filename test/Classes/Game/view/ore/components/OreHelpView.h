#pragma once

#include "BaseType.h"

class OreHelpView:public LayerNode
{
public:
	OreHelpView();
	~OreHelpView();

	bool init();
	void clickClose(CCObject* pSender);
public:
	LayerNode* _pContainer;
};