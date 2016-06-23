#ifndef HLQS_StoryProxy_H_
#define HLQS_StoryProxy_H_
#include "mvc/Proxy.h"
#include "vo/StoryVo.h"
#include "vo/NPCVo.h"
#include "../player/vo/PlayerBaseVo.h"
#include "vo/ItemVo.h"
#include "vo/StoryElement.h"

using namespace cocos2d;

typedef struct _StructElement_
{
	std::string type;
	int id;
	// 		_StructElement()
	// 		{
	// 			type = "";
	// 			id = 0;
	// 		}
} StructElement;

class IAction;

class StoryProxy: public Proxy
{
public:
	StoryProxy();
	~StoryProxy();
public:
	void addNPC(NPCVo info,int index,int vis);
	void addPlayer(PlayerBaseVo &info,int index,int vis);
	void addItem(ItemVo &info,int index,int vis);
	std::string getType(int index);
	int getId(int index);
	void setStoryId(int id);
	StoryVo *getStoryVo();
	bool storyHasTailFight();
	void showNext();
	void dispose();

public:
	StoryVo * _story;

	std::list<IAction *> storyCallbackActionList; 
	
	std::map<int/*index*/,struct _StructElement_> _elementDic;
	//std::map<int/*index*/,StoryElement> _elementDic;
	int _storyId;
	int _round;
	//_dispatcher:GameDispatcher;
};

#endif