#ifndef _LOGIN_SCENE_H_
#define _LOGIN_SCENE_H_

#include "cocos2d.h"
#include "CCScene.h"
#include "CCKeypadDelegate.h"

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
class LoginScene : public CCScene, public CCKeypadDelegate
#else
class LoginScene : public CCScene
#endif
{
private:
	LoginScene();
	~LoginScene();
public:

	enum
	{
		GATE_SERVER_TAG = 0,
		GAME_SERVER_TAG,
	};

	virtual bool init();

	SCENE_NODE_FUNC(LoginScene);

	static LoginScene * getInstance();

	void onGateServerConnectFailed(CCNode *pNode, void *data);
	void onGateServerConnectSuccess(CCNode *pNode, void *data);
	void onGameServerConnectFailed(CCNode *pNode, void *data);
	void onGameServerConnectSuccess(CCNode *pNode, void *data);
	
	void onLoginFailed(CCNode *pNode, void *data);
	//void onRoleChoose(CCNode *pNode, void *data);

	void clearChilds();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
#endif

};
#endif
