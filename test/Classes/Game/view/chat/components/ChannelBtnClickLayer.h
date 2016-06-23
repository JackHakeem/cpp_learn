#pragma once

#include "BaseType.h"

class ChannelBtnClickLayer:public LayerNode
{
public:
	ChannelBtnClickLayer();
	~ChannelBtnClickLayer();

	bool initWithParam(
	CCObject* target0, SEL_MenuHandler selector0,
	CCObject* target1, SEL_MenuHandler selector1);
};