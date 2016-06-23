#ifndef _ALERT_H_
#define _ALERT_H_

#include "BaseType.h"



USING_NS_CC;
class Alert: public LayerNode
{
public:
	enum
	{
		AlertZ_str0 = 0,
		AlertZ_str1,
		AlertZ_str2,
		AlertZ_str3,
		AlertZ_button0,
		AlertZ_button1,
		AlertZ_button2,
		AlertZ_button3,
		AlertZ_CCTextFieldTTF,
	};

	enum
	{
		AlertTAG_str0 = 0,
		AlertTAG_str1,
		AlertTAG_str2,
		AlertTAG_str3,
		AlertTAG_button0,
		AlertTAG_button1,
		AlertTAG_button2,
		AlertTAG_button3,
		AlertTAG_CCTextFieldTTF,
	};

	Alert();
	~Alert();

	bool initWithParam(CCRect rect, bool toRight);

	bool addStr(std::string str, cocos2d::ccColor3B color);
	bool addButton(std::string buttonName,CCObject* target, SEL_MenuHandler selector);
	void show();
	void centerShow();
	void centerShowTextInput();
	const char* getString();

	CC_PROPERTY(CCSize, _BgSize, BgSize)	
public:

	struct strinfo
	{
		std::string str;
		cocos2d::ccColor3B color;
	};

	CCMenu* pMenu;
	int32 buttonCount;
	int32 rowMaxFontCount;
	bool isRight;
	float fontSize;
	int32 rowHeight;
	
	std::list<strinfo> m_str;
};

#endif