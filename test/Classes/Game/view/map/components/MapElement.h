#ifndef _MAPELEMENT_H_
#define _MAPELEMENT_H_

#include "BaseType.h"

class MapElement:public LayerNode
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
	MapElement();
	bool createElement(int32 type, bool isRole, char* txt=0);//data:Object,color:uint,size:int,type:int,isRole:Boolean,txt:String = null
	void iconSetRotation(float var);
public:

};

#endif