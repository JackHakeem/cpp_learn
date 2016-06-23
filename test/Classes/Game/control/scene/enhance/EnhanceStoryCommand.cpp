#include "EnhanceStoryCommand.h"
#include "model/player/RoleManage.h"

EnhanceStoryCommand::EnhanceStoryCommand()
{
	_roleManage = RoleManage::Instance();
}

EnhanceStoryCommand::~EnhanceStoryCommand()
{

}

void EnhanceStoryCommand::excute(int command, char* data)
{
	int storyId;
	PlayerInfoVo* info = _roleManage->roleInfo();
	if (!info){return;}
	switch(info->playerBaseInfo._mapId)
	{
	case 1050:
		storyId = 1020;
		//this.facade.sendNotification(SceneStoryMeiator.ROLE_MOVETOTARGET_STARTSTORY, storyId);
		break;
	}
}

