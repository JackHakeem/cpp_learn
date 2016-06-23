#ifndef _LOGIN_VIEW_H_
#define _LOGIN_VIEW_H_
#include "cocos2d.h"
USING_NS_CC;

class LoginMain;
class LoginNewMain;
class LoginRegister;
class LoginServer;
class LoginCreateRole;

class LoginView : public CCLayer
{
public:
	LoginView();
	~LoginView();

	virtual bool init();

	void addEventListeners();
	void addBackGround();

	// add layers
	void addLoginMainLayer();
	void addNewLoginMainLayer();
	void addRegisterLayer();
	void addServerListLayer();
	void addCreateRoleLayer();

	void LoginView::resetPos(CCNode * pTarget,void *pData);
	void doCallback(CCNode * pNode , void * data);

	CCAction * getMyAction(int type);
	void runMyAction(CCNode * pNode , CCAction * pAction);

	CC_SYNTHESIZE(std::string,selectedArea,SelectedArea);
	CC_SYNTHESIZE(std::string,selectedServ,SelectedServ);
	// events
// 	void onLoginMenuClick(CCObject *pSender);
// 	void onServerMenuClick(CCObject *pSender);
// 	void onRegisterConfirmMenuClick(CCObject *pSender);
// 	void onServerConfirmMenuClick(CCObject *pSender);
// 	void onBackMenuClick(CCObject *pSender);
// 	void onEnterGameMenuClick(CCObject *pSender);
// 	void onNameGeneratorMenuClick(CCObject *pSender);
// 	void onNormalLoginMenuClick(CCObject *pSender);
// 	void onGuestLoginMenuClick(CCObject *pSender);

public:
	void onLoginUnRegister(CCNode *pNode, void *data);
	void onLoginVersionErr(CCNode *pNode, void *data);
	void onLoginForbidden(CCNode *pNode, void *data);
	void onLoginSuccess(CCNode *pNode, void *data);
	void onLoginCreateRole( CCNode *pNode, void *data );
public:

	enum LayerTag
	{
		TAG_UserPwdLayer = 0,
		TAG_UserPwdLayer_new,
		TAG_RegisterLayer,
		TAG_ServersLayer,
		TAG_CreateRoleLayer,
		TAG_LoginBg1,
		TAG_LoginBg2,
		TAG_Cloud1,
		TAG_Cloud2,
		TAG_Cloud3,
	};

	enum ItemTag
	{
		TEXTFIELD_ACCOUNT = 0,
		TEXTFIELD_PASSWD,
		TEXTFIELD_PASSWD_CONFIRM,
		TEXTFIELD_ROLECREATE,
		FRAME_LOGIN,
		NORMAL_CHECK_BTN,
		GUEST_CHECK_BTN
	};

	enum
	{
		ActType_LRMove = 0,
		ActType_FallDown = 1,
		ActType_Cloud1 = 2,
		ActType_Cloud2 = 3,
		ActType_Orbit1 = 4,
		ActType_Fade1 = 5,
	};

	LoginMain * _pLoginMainLayer;
	LoginNewMain * _pNewLoginMainLayer;
	LoginRegister * _pRegisterLayer;
	LoginServer * _pServersLayer;
	LoginCreateRole * _pCreateRoleLayer;

	CCSize _winSize;
	CCPoint *_pos;
};
#endif