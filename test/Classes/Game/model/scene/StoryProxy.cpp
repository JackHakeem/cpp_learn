#include "StoryProxy.h"
#include "vo/SceneConst.h"
#include "StoryManager.h"
#include "control/AppFacade.h"
#include "view/scene/SceneStoryMediator.h"
#include "mvc/Proxy.h"

StoryProxy::StoryProxy()
{
	_story = 0;
	_round = 0;
}

StoryProxy::~StoryProxy()
{

}

void StoryProxy::addNPC(NPCVo info,int index,int vis)
{
	//Doyang 20120712
	/*struct _StructElement_ *element = new _StructElement_;
	element->type = NPC_TYPE;
	element->id = info->id;
	_elementDic.insert(make_pair(index,*element));*/

	_StructElement_ element;
	element.type = NPC_TYPE;
	element.id = info.id;
	std::map<int, _StructElement_>::iterator it = _elementDic.find(index);
	if(it != _elementDic.end())
	{
		_elementDic.erase(it);
	}
	_elementDic.insert(make_pair(index, element));

	struct _INFO_
	{
		NPCVo info;
		int vis;
	} Info;
	Info.info = info;
	Info.vis = vis;

	sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,(char*)&Info,SceneStoryMediator::ADDNPC);
}

void StoryProxy::addPlayer(PlayerBaseVo &info,int index,int vis)
{
	//struct _StructElement_ *element = new _StructElement_;

	//Doyang 20120717
	struct _StructElement_ strElement;
	strElement.type = PLAYER_TYPE;
	strElement.id = info.id;
	_elementDic.insert(make_pair(index,strElement));

	struct _INFO_
	{
		PlayerBaseVo info;
		int vis;
	} Info;
	Info.info = info;
	Info.vis = vis;

	sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,(char*)&Info,SceneStoryMediator::ADDPLAYER);
}

void StoryProxy::addItem(ItemVo &info,int index,int vis)
{
	//Doyang 20120717
	struct _StructElement_ element;
	element.type = ITEM_TYPE;
	element.id = info.getID();
	_elementDic.insert(make_pair(index,element));

	struct _INFO_
	{
		ItemVo info;
		int vis;
	} Info;
	Info.info = info;
	Info.vis = vis;

	sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,(char*)&Info,SceneStoryMediator::ADDITEM);
}

std::string StoryProxy::getType(int index)
{
	if (_elementDic.find(index) != _elementDic.end())
	{
		return _elementDic[index].type;
	}
	return 0;
}

int StoryProxy::getId(int index)
{
	if (_elementDic.find(index) != _elementDic.end())
	{
		return _elementDic[index].id;
	}
	return -1;
}

void StoryProxy::setStoryId(int id)
{
	_story = StoryManager::Instance()->getStory(id);
}

StoryVo *StoryProxy::getStoryVo()
{
	return _story;
}

bool StoryProxy::storyHasTailFight()
{
	bool bTail = false;
	if (((StoryVo*)&_story) && _story->arrt)
	{
		bTail = true;
	}
	return bTail;
}

void StoryProxy::showNext()
{
	//StoryScript storyNode;
	if (_story->script.size() > _round)
	{
		StoryScript& storyNode = _story->script[_round];
		++_round;
		CCLog("STORY:next story,index %d",storyNode.index);
		sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,(char *)&storyNode,SceneStoryMediator::SHOW_NEXT);
	} 
	else
	{
        //Doyang 20120718
//		int style;
//		StoryScript& storyNode = _story->script[_story->script.size()-1];
//		if (storyNode._tox<0 && storyNode._toy<0)
//		{
//			style = 0;
//		}
		dispose();
		CCLog("STORY:out story");
		sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,0,SceneStoryMediator::OUT_STORY);
	}
}

void StoryProxy::dispose()
{
	_storyId = 0;
	_round = 0;
	_elementDic.clear();
}
