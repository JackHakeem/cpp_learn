#include "SceneStoryProxyCommand.h"
#include "model/player/RoleManage.h"
#include "model/scene/StoryProxy.h"
#include "model/scene/SceneProxy.h"
#include "model/scene/vo/StoryModelVo.h"
#include "model/scene/StoryManager.h"
#include "model/scene/vo/NPCVo.h"
#include "model/scene/vo/ItemVo.h"
#include "model/scene/vo/SceneConst.h"

SceneStoryProxyCommand::SceneStoryProxyCommand()
{
	_roleManage = RoleManage::Instance();
	_storyProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
	_sceneProxy = (SceneProxy *)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
}

SceneStoryProxyCommand::~SceneStoryProxyCommand()
{

}

void SceneStoryProxyCommand::execute(int32 command, char* data)
{
	switch(command)
	{
	case JOIN_ELEMENT:
		joinElement();
		break;
	case SHOW_NEXT:
		_storyProxy->showNext();
		break;
	}
}

void SceneStoryProxyCommand::joinElement()
{
	if(!_storyProxy->getStoryVo()) {return;}

	int i = 0;
	CCPoint focusPos= _sceneProxy->_focusPos;
	//var focusPos:Point = TileUtil.changePixsToTile(focus);
	std::vector<StoryElement> vcElement = _storyProxy->getStoryVo()->elemenet;
	std::vector<StoryElement>::iterator iter = vcElement.begin();
	while (iter != vcElement.end())
	{
		StoryElement storyNode = *iter;
		if((0 == storyNode.type)) // 玩家
		{  
			PlayerInfoVo * info = _roleManage->roleInfo();
			if (!info){return;}

			//Doyang 20120717
			PlayerBaseVo playVo;
			playVo.x = storyNode.x;  
			playVo.y = storyNode.y; 
			playVo._hp = 1;
			playVo.cloth = info->playerBaseInfo.cloth;
			playVo.accountId = _roleManage->_accountInfo.accountId;
			playVo.name =  info->playerBaseInfo.name;
			playVo.state = storyNode.dir;
			_storyProxy->addPlayer(playVo,i,storyNode.vis);
		}
		else if ((1 == storyNode.type)||(2 == storyNode.type)) // NPC或者怪物 
		{
			StoryModelVo * modelVo = StoryManager::Instance()->getStoryModel(storyNode.id);
			if (!modelVo)	{return;}			
			NPCVo npcVo;
			npcVo.x = storyNode.x;
			npcVo.y = storyNode.y; 
			npcVo.id = modelVo->id;
			npcVo._resId = modelVo->resid;
			npcVo.name = modelVo->name;
			npcVo._hp = 1;	//默认一点血，否则为死亡状态
			npcVo.state= storyNode.dir;
			npcVo.action = SceneConst::STORY;
			_storyProxy->addNPC(npcVo,i,storyNode.vis);
		}
		else if (3 == storyNode.type) // 物品
		{
			StoryModelVo * modelVo = StoryManager::Instance()->getStoryModel(storyNode.id);
			ItemVo itemVo;
			itemVo.x = storyNode.x;
			itemVo.y = storyNode.y;
			itemVo.setId(storyNode.id);
			itemVo.setResId(modelVo->resid);  //
			itemVo.setName(modelVo->name);
			_storyProxy->addItem(itemVo, i, storyNode.vis);
		}		
		++iter;
		++i;
	}

	// by LH 0730
	_storyProxy->showNext();
}