#ifndef HLQS_SceneStoryProxyCommand_H_
#define HLQS_SceneStoryProxyCommand_H_
#include "mvc/SimpleCommand.h"
#include "cocos2d.h"

USING_NS_CC;

class RoleManage;
class StoryProxy;
class SceneProxy;

class SceneStoryProxyCommand: public SimpleCommand
{
public:
	SceneStoryProxyCommand();
	~SceneStoryProxyCommand();
	void execute(int32 command, char* data);

	void joinElement();

public:
	enum
	{
		SHOW_NEXT = 0,
		JOIN_ELEMENT
	};

	RoleManage * _roleManage;
	StoryProxy * _storyProxy;
	SceneProxy * _sceneProxy;
};

#endif