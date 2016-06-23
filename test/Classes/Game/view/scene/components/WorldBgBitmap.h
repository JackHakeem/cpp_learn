#ifndef HLQS_WorldBgBitmap_H_
#define HLQS_WorldBgBitmap_H_
#include "BgBitmap.h"

class WorldBgBitmap: public BgBitmap
{
public:
	WorldBgBitmap();
	virtual void load(CCLayer* layer, CCPoint pos);
	virtual void dispose();
public:
	CCSprite* _mapSprite;
};

#endif