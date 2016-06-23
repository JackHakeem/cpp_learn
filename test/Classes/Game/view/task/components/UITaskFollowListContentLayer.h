#ifndef _UI_TASK_FOLLOW_LIST_CONTENT_LAYER_H_
#define _UI_TASK_FOLLOW_LIST_CONTENT_LAYER_H_

#include "cocos2d.h"
#include "BaseType.h"

class UITaskFollowListContentLayer : public LayerNode
{
public:
	UITaskFollowListContentLayer(cocos2d::CCSize layerSize);
	~UITaskFollowListContentLayer(){};

	virtual bool init();
	virtual void visit();

	static UITaskFollowListContentLayer *initWithWidthHeight(cocos2d::CCSize layerSize);
};
#endif