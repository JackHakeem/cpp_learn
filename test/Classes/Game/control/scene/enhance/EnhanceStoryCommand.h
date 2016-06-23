#ifndef HLQS_EhanceProxyCommand_H_
#define HLQS_EhanceProxyCommand_H_

#include "cocos2d.h"
#include "mvc/SimpleCommand.h"

USING_NS_CC;

class RoleManage;

class EnhanceStoryCommand : public SimpleCommand
{
public:
	EnhanceStoryCommand();
	~EnhanceStoryCommand();

public:
	virtual void excute(int command, char* data);
protected:

private:
	RoleManage * _roleManage;
};


#endif