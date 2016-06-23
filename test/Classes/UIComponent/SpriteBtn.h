#pragma once

#include "BaseType.h"

class SpriteBtnFactory
{
public:
	static CCMenuItemSprite* make(const char* name, float w, float h, CCObject* target, SEL_MenuHandler selector);
};

