#ifndef _CUSTOMBUTTON_H_
#define _CUSTOMBUTTON_H_
#include "cocos2d.h"

USING_NS_CC;

class CustomButton : public CCLayer
{
public:
	CustomButton(std::string path0,std::string path1,std::string text,ccColor3B &color,CCObject * pSender,SEL_MenuHandler selector);
	virtual bool init();
	void addButton(std::string path0,std::string path1,std::string text,ccColor3B &color,CCObject * pSender,SEL_MenuHandler selector);
public:
	CCMenu * _pBtnMenu;
	CCLabelTTF * _pBtnText;
public:
	enum
	{
		Z_BTN = 0,
		Z_TXT,
	};
	enum
	{
		TAG_BTN = 0,
		TAG_TXT,
	};
};

#endif