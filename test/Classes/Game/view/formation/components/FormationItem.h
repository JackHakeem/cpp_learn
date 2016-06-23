#ifndef _FORMATIONITEM_H_
#define _FORMATIONITEM_H_
#include "model/player/vo/PlayerInfoVo.h"
#include "SpriteNode.h"
#include "model/player/vo/PlayerBaseVo.h"


/*
 *     In the formation JiuGongGe play characters
*/
class FormationItem : public SpriteNode
{

public:

	 
	uint32 sitGrid;
	uint32 _figureId ;
	int _clickNum ;
	 
	 
	bool isHasCopy;
	bool isMove ;
 
	SpriteNode* _mark ;
  
public:

	FormationItem(int sitGrid , PlayerInfoVo* info );
	void  initHeadInfo(PlayerBaseVo playerBase, FigureBaseVo  figureBase);

};

#endif