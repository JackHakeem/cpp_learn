#ifndef HLQS_Player_effctInfo_h
#define HLQS_Player_effctInfo_h
#include "BaseType.h"

class PlayerEffectInfoVo
{
public:
	int _type;
	std::string _path;
	std::string _name;
	int _nFrameCount;
	float _time;
	int _x;
	int _y;
public:
	PlayerEffectInfoVo() : _type(0),_path(""),_name(""),_nFrameCount(0),_time(0),_x(0),_y(0)
	{

	}
};

#endif