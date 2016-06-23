#ifndef _MAP_ELEMENT_H_
#define _MAP_ELEMENT_H_

#include "BaseType.h"

class NPCVo;
class SmallMapElement:public LayerNode
{
public:
	enum
	{
		MapElementZ_icon,
		MapElementZ_txt,
	};
	enum
	{
		MapElementTAG_icon,
		MapElementTAG_txt,
	};
	SmallMapElement();
	bool createElement(int32 type, bool isRole, char* txt=0 ,NPCVo * vo = 0);//data:Object,color:uint,size:int,type:int,isRole:Boolean,txt:String = null
	void iconSetRotation(float var);

	void autoFind(CCObject * pSender);
public:

};

#endif