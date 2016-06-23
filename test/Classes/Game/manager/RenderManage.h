#ifndef HLQS_RenderManage_H_
#define HLQS_RenderManage_H_
#include "view/interfaces/IRender.h"
#include "cocos2d.h"
#include "utils/Singleton.h"
#include "CCLayer.h"

USING_NS_CC;

class RenderManage: public cocos2d::CCLayer, public Singleton<RenderManage>
{
public:
	bool _isStop;
	int _count;
	std::vector<IRender*> _dic;
public:
	RenderManage();
	~RenderManage();
	void start();
	void nextStep(ccTime dt);
	void stop();
	void add(IRender*);
	void remove(IRender*);
	int length();
	bool isStart();
};

#endif