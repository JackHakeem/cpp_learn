#ifndef _SCENE_STORY_MEDIATOR_H_
#define _SCENE_STORY_MEDIATOR_H_
#include "cocos2d.h"
#include "mvc/Mediator.h"
#include "../BaseMediator.h"
#include "../interfaces/IElement.h"
#include "../../model/scene/vo/StoryScript.h"
#include "components/StoryScene.h"

USING_NS_CC;

class SceneStoryMediator : public BaseMediator
{
public:
	SceneStoryMediator();
	~SceneStoryMediator();
	virtual void handleNotification( int M2Vcmd, char* data );
	
	StoryScene * getStoryScene();
	void tweenToTargetStartStory(int storyID);
	void intoStory(char * data);// 
	void loadStoryFace();
	bool inspectElements(std::vector<StoryScript> *);	// 	
	bool inspectScripts(std::vector<StoryScript> *);		// 
	void buildStoryScene();
	void outStoryHandler(char * data);
	void outStory(char * data);	// 
	void addPlayer(char * data);
	void removePlayer(char * data);
	void addNPC(char * data);
	void removeNPC(char * data);
	void addItem(char * data);
	void removeItem(char * data);
	void showNext(char * data);
	void getNext(char * data);
	void mapShortcut();
	void storyCallback(CCNode * pNode , void * data);

public:
	enum
	{
		ROLE_MOVETOTARGET_STARTSTORY = 0,
		ADDPLAYER,
		REMOVEPLAYER,
		ADDNPC,
		REMOVENPC,
		ADDITEM,
		REMOVEITEM,
		INTO_STORY,
		OUT_STORY,
		SHOW_NEXT,
		STORY_SHORTCUT
	};

	StoryVo * _storyVo;
	StoryScene * _storyScene;
};
#endif