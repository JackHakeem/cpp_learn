#ifndef _LOGIN_TEXT_H_
#define _LOGIN_TEXT_H_
#include "cocos2d.h"
#include "LayerNode.h"
#include "utils/Singleton.h"
#include "LoginTxtItem.h"
USING_NS_CC;

class LoginTxt : public LayerNode, public Singleton<LoginTxt>
{
public:
	LoginTxt();
	virtual ~LoginTxt();

	enum ViewTag
	{
		TEXTFIELD_ACCOUNT = 0,
		TEXTFIELD_PASSWD,
		FRAME_LOGIN,
	};
public:
	virtual bool init();
 	void start();
 	void createMsg();
 	void dispose();

	void layout();
	void onTime(float dt );
	void show( std::string msg, ccColor3B color = ccc3(0, 255, 0), float delay = 2.0);

public:
	CCMutableArray<LoginTxtItem*> _msgList;
};
#endif