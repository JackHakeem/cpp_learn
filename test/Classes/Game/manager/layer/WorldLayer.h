#ifndef _WORLD_LAYER_H_
#define _WORLD_LAYER_H_
#include "LayerNode.h"

class WorldLayer : public LayerNode
{
public:
	WorldLayer(){}
	~WorldLayer(){}

	virtual bool init() {return true;}
};

#endif