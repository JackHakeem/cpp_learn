#ifndef _LOGIN_REGISTER_H_
#define _LOGIN_REGISTER_H_
#include "BaseType.h"
#include <string>


USING_NS_CC;

class LoginRegister : public CCLayer
{
public:
	LoginRegister();
	~LoginRegister();

	enum
	{
		Tag_Bg,
		Tag_Account_Bg,
	};
	virtual bool init();

	void loadItems();

public:
	void onBackMenuClick(CCObject *pSender);
	void onRegisterConfirmMenuClick(CCObject *pSender);
};

#endif