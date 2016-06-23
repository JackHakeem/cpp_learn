#ifndef _LOGIN_NEW_MAIN_H_
#define _LOGIN_NEW_MAIN_H_
#include "cocos2d.h"
#include "utils/xml/tinyxml.h"
#include <list>

USING_NS_CC;

class LoginView;
class BaseThread;

class LoginNewMain : public CCLayer
{
public:
	LoginNewMain();
	virtual ~LoginNewMain();

	virtual bool init();

	void loadItems();
	void setAreaText();
	void setDefaultServerAndPort();

	bool isContainAlpha(std::string str);
	std::list<std::string> splitStringByCharacter( string o_str, string sCharacter );
	int string2Int(std::string str);
	void readFavorServInfoFromFile();

	static int loadServerListXMLBuffer( char *arr, int length, TiXmlEncoding encoding );
	static void getServerInfoFromRemote();
	void resetServList(CCNode * pTarget,void *pData);
	void resetAreaText(CCNode * pTarget,void *pData);
	void resetPos(CCNode * pTarget,void *pData);

	CCAction * getMyAction(int type);
	void runMyAction(CCNode * pNode , CCAction * pAction);

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

	enum
	{
		ActType_LRMove = 0,
		ActType_FallDown = 1,
		ActType_Cloud = 2,
	};

	//virtual void registerWithTouchDispatcher( void );
	//virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

	void onLoginMenuClick( CCObject *pSender );
	void onReturnMenuClick(CCObject *pSender);
	void onServerMenuClick(CCObject *pSender);
	void onNormalLoginMenuClick(CCObject *pSender);
	void onGuestLoginMenuClick(CCObject *pSender);

    void parseUrlAndLogin();

private:
	LoginView * _pLoginView;
	BaseThread * m_pThread;
	CCSize _winSize;
};

#endif