#ifndef _STORYMANAGER_H_
#define _STORYMANAGER_H_

#include "cocos2d.h"
#include "utils/Singleton.h"
#include "vo/StoryVo.h"
#include "vo/StoryModelVo.h"
#include "vo/StoryScript.h"
#include "vo/StoryElement.h"

using namespace cocos2d;
class BattleLayer;
class StoryManager: public Singleton<StoryManager>
{
public:
	std::map<int, StoryVo> _storyDic;
	std::map<int, StoryModelVo> _storyModelDic;

public:
    StoryManager();
    virtual ~StoryManager();

	void setStorys(StoryVo * info);
	StoryVo * getStory(int id);
	void setStoryModel(StoryModelVo * info);
	StoryModelVo * getStoryModel(int id);
	void setStoryScriptType();

	std::vector<StoryElement> createElemenet(std::string element);
	std::vector<StoryScript> createScript(std::string script);
};

#endif