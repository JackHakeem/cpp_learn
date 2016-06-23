#ifndef _MessageInfoBox_H_
#define _MessageInfoBox_H_
#include "cocos2d.h"
#include "utils/Singleton.h"

USING_NS_CC;

class CCUIBackground;

class MessageInfoBox : public CCLayer,public Singleton<MessageInfoBox>
{
public:
	MessageInfoBox();
	//MessageInfoBox(std::string content,CCObject * pSender);
	virtual bool init();
	void addBackGround();
	void addContent();
	void addButton(std::string btnText, SEL_MenuHandler selector);

	void clickClose(CCObject * pSender);
	void show(std::string content,ccColor3B ccc3,SEL_MenuHandler selector = 0,std::string btnText = "");
public:
	CCMenu * _pBtnMenu;
	CCLabelTTF * _pBtnText;
	CCSize winSize;
	CCUIBackground * _pBack;
	std::string _content;
	ccColor3B _ccc3;
	int m_pri;
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