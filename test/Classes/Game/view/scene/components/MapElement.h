#ifndef _MAPELEMENT_H__
#define _MAPELEMENT_H__
#include "BaseType.h"
#include "model/scene/vo/LiveThingVo.h"

struct MovieClip
{
	int x;
	int y;
	int type;
	MovieClip()
	{
		x = 0;
		y = 0;
		type = 0;
	}
};

struct TextField
{
	std::string text;
	uint32 textColor;
	int autoSize;
	bool wordWrap;
	int x;
	int y;
};

class MapElement
{
public:
	LiveThingVo* data;
	std::string bitmap;
	uint color;
	int size;
	//std::string shopText;

	//std::string _icon;
	//int _iconType;
	MovieClip _icon;
	TextField shopText;

	MapElement( LiveThingVo* pLiveThingVo, uint uColor,int iSize,int type, bool isRole, std::string txt = "" )
	{
		data = pLiveThingVo;
		color = uColor;
		size = iSize;
		_icon.type = type;

		shopText.text = txt;
		shopText.textColor = 0x99ff00;
		//shopText.x = -shopText.width/2;
	}

};

#endif