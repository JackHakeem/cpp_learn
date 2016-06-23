#pragma once
#include "cocos2d.h"
#include "BaseType.h"

USING_NS_CC;

typedef std::map<std::string,ccColor3B> MAPSTRCOLOR;

class NoticeBanner : public CCLayer
{
public:
	NoticeBanner();
	~NoticeBanner();
	virtual bool init();

public:
	enum
	{
		TAG_Background_Sprite,
		TAG_Content_Text,
	};

	CC_SYNTHESIZE(bool,_isRun,IsRun)

public:
	void initView();
	void reLoadNotice();
	void removeNotice();

	void addNormalMessage(MAPSTRCOLOR strColorList, int time);	//添加普通广播
	void addPriorityMessage(MAPSTRCOLOR strColorList, int time);	//添加高优先级广播（后来居上）
	void showContent(MAPSTRCOLOR strColorList);

	void checkAndRun();

	void run();
	void play(ccTime dt);

	void playAction();

public:
	CCFiniteTimeAction * getAction();

public:
	std::list<MAPSTRCOLOR> _messageDic;

protected:
private:

};

extern NoticeBanner * g_pSysNotice;