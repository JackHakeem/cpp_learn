#pragma once

#include "BaseType.h"

class MainSettingLayer:public LayerNode
{
public:
	enum
	{
		MainSettingLayerZ_accountBtn,
		MainSettingLayerZ_musicBtn,
	};

	enum
	{
		MainSettingLayerTAG_accountBtn,
		MainSettingLayerTAG_musicBtn,
	};

	MainSettingLayer();
	~MainSettingLayer();

	bool initWithParam(CCObject* target, SEL_MenuHandler selectorAccount, SEL_MenuHandler selectorMusic);

public:
};