//
//  SceneManager.h
//  HLQS_IPAD
//
//  Created by hui long on 12-2-27.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_IPAD_SceneManager_h
#define HLQS_IPAD_SceneManager_h

#include "cocos2d.h"
#include "utils/Singleton.h"
#include "vo/SceneVo.h"
using namespace cocos2d;
class BattleLayer;
class SceneManager: public Singleton<SceneManager>
{
public:
	std::map<int, SceneVo> _sceneDic;
	std::map<int, std::vector<int> > _scenePidDic;
	//_scenePreIdDic;
	//_sceneNextIdDic;
public:
    SceneManager();
    virtual ~SceneManager();

	void setMapDic(SceneVo* sceneVo);
	SceneVo* getSceneDic(int id);
	std::vector<SceneVo*> getWorldSceneDic();
	std::vector<int>* getChildByPid(int pid);
	std::vector<SceneVo*> getCityScenes();
	std::vector<SceneVo*> getChallengeMapIDs();

	int getCurMapType();
};

#endif