#ifndef HLQS_SceneCommand_H_
#define HLQS_SceneCommand_H_

#include "mvc/SimpleCommand.h"
#include "model/scene/SceneProxy.h"
#include "model/scene/vo/SceneInfoVo.h"
using namespace cocos2d;

class SceneCommand: public SimpleCommand
{
private:
	SceneProxy* _sceneProxy;
	//std::string _sceneRoot;
	int _loadTimes;

public:
	SceneCommand();
	~SceneCommand();

	virtual void excute(int32 command, char* data);
	void loadMap();
	void getMapData();
	void loadMapData(char* path, char* fileName);

	FindPath8 _findPath8;
	SceneInfoVo _sceneInfo;
	void setSceneInfo();
};
#endif