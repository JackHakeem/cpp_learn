#ifndef HLQS_TouchCityNode_H_
#define HLQS_TouchCityNode_H_
#include "BaseType.h"
#define KUANG_H 88
#define KUANG_W 138

USING_NS_CC;

class TouchCityNode: public LayerNode
{
public:
	int _nodeId;
	bool _isFocused;
	enum
	{
		NODE_FOCUSED = 0,
	};

public:
	TouchCityNode();
	TouchCityNode(int nodeId);
	void setSpriteIcon(bool open, bool isFocused = false);
};

#endif