#ifndef _HEADITEM_H_
#define _HEADITEM_H_
#include "BaseType.h"
#include "SpriteNode.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/player/vo/PlayerBaseVo.h"
#include "model/player/vo/FigureBaseVo.h"

/*
         JiuGongGe layout to play the characters
*/


class HeadItem : public SpriteNode
{

public:
	uint32 _mySitNum;
	uint32 _figureId ;
	int32   _clickNum; 
    bool isHasCopy; 
	bool isMove ;
	CCSize _pLeftGridSize;
 
public:
	HeadItem(uint32 sitGrid ,  PlayerInfoVo info, float scale);
	void initHeadInfo(PlayerBaseVo playerBase , FigureBaseVo figureBase, float scale);
	void setPlayIcon(bool set);


};
#endif