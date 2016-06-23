#pragma once

#include "BaseType.h"

class AccountSettingLayer:public LayerNode
{
public:
	enum
	{
		AccountSettingLayerZ_centerBtn,
	};

	enum
	{
		AccountSettingLayerTAG_centerBtn,
	};

	AccountSettingLayer();
	~AccountSettingLayer();

	bool init();
	//bool initWithParam(CCObject* target, SEL_MenuHandler selectorAccount, SEL_MenuHandler selectorMusic);
	void center(CCObject* pSender);

public:
};