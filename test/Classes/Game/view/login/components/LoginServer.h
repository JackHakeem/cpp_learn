#ifndef _LOGIN_SERVER_H_
#define _LOGIN_SERVER_H_

#include "cocos2d.h"

USING_NS_CC;

class AreaListView;
class ServerListView;
class ServerNewListView;

class LoginServer : public CCLayer
{
public:
	LoginServer();
	~LoginServer();

	virtual bool init();
	virtual void visit();

	void loadItems();
	void loadListView();
	void addServQQ();
	void EnableConfirmButton(bool var);
	void setDefaultServerAndPort();

	void resetListView();
	void saveFavorServInfo();

	void setLastLoginServer(std::string str);
	void setRecommendedServer(std::string str);
	void setSelectedServer(std::string str);
	void enableConfirmButton(bool var);

public:
	void onBackMenuClick(CCObject *pSender);
	void onServerConfirmMenuClick(CCObject *pSender);
	void onNewServerConfirmMenuClick(CCObject *pSender);

public:

	enum
	{
		Z_BG = 0,
		Z_LISTVIEW,
		Z_BTN
	};
	enum
	{
		TAG_AREA_LIST = 0,
		TAG_SERV_LIST,
		TAG_SER_QQ = 101,
		Tag_Login_Server_Bg,
		TAG_MENU_CONFIRM = 201,
		TAG_MENU_CONFIRM_IMG,
		TAG_Last_Server = 301,
		TAG_Recommended_Server,
		TAG_Selected_Server,
	};

	AreaListView * _pAeraListView;
	ServerListView * _pServListView;
	ServerNewListView * _pServNewListView;

	CCSize _winSize;

};

#endif