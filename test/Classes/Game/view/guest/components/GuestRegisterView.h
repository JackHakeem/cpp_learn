#ifndef _HLQS_GuestRegisterView_H_
#define _HLQS_GuestRegisterView_H_

#include "cocos2d.h"

USING_NS_CC;

class GuestRegisterView : public CCLayer
{
public:
	GuestRegisterView();
	virtual ~GuestRegisterView(){}
	
	virtual bool init();

	void onRegisterMenuClick(CCObject *pSender);
	void onBackMenuClick(CCObject *pSender);

public:
	enum LayerTag
	{
		TAG_UserPwdLayer = 0,
		TAG_RegisterLayer,
		TAG_ServersLayer,
		TAG_CreateRoleLayer
	};

	enum ItemTag
	{
		TEXTFIELD_ACCOUNT = 0,
		TEXTFIELD_PASSWD,
		TEXTFIELD_PASSWD_CONFIRM,
		FRAME_LOGIN,
	};

	CCLayer * _pRegisterLayer;
};

#endif