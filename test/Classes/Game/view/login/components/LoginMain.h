#ifndef _LOGIN_MAIN_H_
#define _LOGIN_MAIN_H_
#include "cocos2d.h"
#include "utils/xml/tinyxml.h"
#include <list>

USING_NS_CC;

class LoginView;
class BaseThread;

class LoginMain : public CCLayer
{
public:
	LoginMain();
	~LoginMain();

	virtual bool init();

	void loadItems();
	void setAreaText();
	void setDefaultServerAndPort();

	std::list<std::string> splitStringByCharacter( string o_str, string sCharacter );
	int string2Int(std::string str);
	void readFavorServInfoFromFile();

	static int loadServerListXMLBuffer( char *arr, int length, TiXmlEncoding encoding );
	static void getServerInfoFromRemote();
	void resetServList(CCNode * pTarget,void *pData);

	CC_SYNTHESIZE(std::string,selectedArea,SelectedArea);
	CC_SYNTHESIZE(std::string,selectedServ,SelectedServ);

public:

	enum
	{
		TAG_AREA_TEXT = 32,
		TAG_PWD_TEXT,
		TAG_PWD_LABBG,
		TAG_GUESTLOGIN_DES_TEXT,
		Tag_UserPass_Bg,
		Tag_Account_Bg,
		TAG_AREA,
	};

	virtual void registerWithTouchDispatcher( void );
	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	void onLoginMenuClick( CCObject *pSender );
	void onRegisterMenuClick(CCObject *pSender);
	void onServerMenuClick(CCObject *pSender);
	void onNormalLoginMenuClick(CCObject *pSender);
	void onGuestLoginMenuClick(CCObject *pSender);

    void parseUrlAndLogin();

private:
	LoginView * _pLoginView;
	BaseThread * m_pThread;
};

#endif