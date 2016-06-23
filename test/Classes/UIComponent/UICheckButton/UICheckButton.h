#ifndef _UI_CHECK_BUTTON_H_
#define _UI_CHECK_BUTTON_H_

#include "cocos2d.h"

USING_NS_CC;

class UICheckButton : public CCMenu
{
public:
	static UICheckButton * menuWithItems(CCMenuItem* item, ...);
	
	void setIsCheck(bool isCheck);
};
#endif