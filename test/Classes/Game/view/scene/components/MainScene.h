 //
//  MainScene.h
//  HLQS
//
//  Created by edward liu on 12-2-23.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_MainScene_h
#define HLQS_MainScene_h
#include "cocos2d.h"
#include "CCKeypadDelegate.h"

using namespace cocos2d;

class MainScene : public cocos2d::CCScene, public CCKeypadDelegate
{
private:
    MainScene();
public:
	~MainScene();
	static MainScene * getInstance();
	static void  destroyInstance();
	static MainScene * Instance();
    virtual bool init();
    void menuCloseCallback(CCObject* pSender);
    SCENE_NODE_FUNC(MainScene);
    
    virtual void keyBackClicked();
    virtual void keyMenuClicked();
};

#endif
