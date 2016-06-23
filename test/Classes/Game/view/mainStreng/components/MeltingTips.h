#ifndef __MeltingTips_H_
#define __MeltingTips_H_

#include "cocos2d.h"
#include "LayerNode.h"
using namespace cocos2d;

class MeltingTipsVo;

class MeltingTips : public LayerNode
{
public:
	MeltingTips();
	~MeltingTips();

public:
	bool init();
};

#endif