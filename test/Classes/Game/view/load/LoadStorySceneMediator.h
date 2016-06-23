#ifndef _LOAD_STORY_MEDIATOR_H_
#define _LOAD_STORY_MEDIATOR_H_
#include "cocos2d.h"
#include "mvc/Mediator.h"

USING_NS_CC;

class LoadStorySceneMediator : public Mediator
{
public:
	LoadStorySceneMediator();
	~LoadStorySceneMediator();
	virtual void handleNotification( int M2Vcmd, char* data);

public:
	enum
	{
		SHOW_PROCESS = 0,
	};

	//virtual char[] listNotificationInterests();
	
	void showLoadProgress();

protected:
private:
};

#endif