#ifndef _MAPNPCSPRITE_H_
#define _MAPNPCSPRITE_H_

#include "cocos2d.h"
#include "model/scene/vo/NPCVo.h"
using namespace cocos2d;

class MapNPCSprite: public CCSprite
{
public:
	MapNPCSprite( NPCVo* pNPCVo );
	~MapNPCSprite(void);

	NPCVo* _npcVo;
private:
};

#endif