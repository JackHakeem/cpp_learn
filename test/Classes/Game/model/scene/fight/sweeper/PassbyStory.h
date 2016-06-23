#ifndef _PASSBY_STORY_H_
#define _PASSBY_STORY_H_
#include "cocos2d.h"

USING_NS_CC;

class StoryVo;

class PassbyStory
{
public:
	PassbyStory(int storyId);
	~PassbyStory();
	
	void sweep();
	void tweenComplete();
	void endHandler();
	void dispose();
protected:
private:
	//private var facade:Facade;
	int _storyId;
};

#endif