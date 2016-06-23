#ifndef _LOGIN_CREATEROLE_H_
#define _LOGIN_CREATEROLE_H_
#include "cocos2d.h"

USING_NS_CC;

class LoginCreateRole : public CCLayer
{
public:
	LoginCreateRole();
	~LoginCreateRole();

	virtual bool init();

	void loadItems();
	std::string initName();

public:
	//CCSprite * _pHightLight;
	int _nSelectModel;
	int _curSelectSex;
	enum
	{
		TAG_SPRITE_MODEL = 101,
	};

	enum
	{
		TAG_Login_Creat_RoleBg = 201,
		TAG_Login_Creat_Friend1,
		TAG_Login_Creat_Friend2,
		TAG_SPRITE_INPUT,
		TAG_SPRITE_HIGHLIGHT,
	};

	enum
	{
		Z_SPRITE_BG = 0,
		Z_SPRITE_INPUT = 2,
		Z_SPRITE_RANDOM_BTN,
	};
public:
	void onNameGeneratorMenuClick(CCObject *pSender);
	void onEnterGameMenuClick(CCObject *pSender);
	void onSelectModel(CCObject * pSender);
};

#endif