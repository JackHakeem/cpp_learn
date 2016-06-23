#ifndef _LAYERNODE_H_
#define _LAYERNODE_H_
#include "BaseType.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "FocusNode.h"

class LayerNode : public cocos2d::CCLayer, public CCIEventDispatcher, public FocusNode
{
public:
	bool init()
	{
		if (!CCLayer::init())
			return false;
		return true;
	}

	virtual ~LayerNode(){}

	CC_SYNTHESIZE(cocos2d::CCSize, visibleSize, visibleSize);
};

#endif