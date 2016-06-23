#pragma once
#include "BaseType.h"

class XHConfVo
{
public:
	XHConfVo()
	{
		type = 0;
		color = 0;
		name = "";
		effecttype = 0;
		for (int i =0; i < 10; i++)
			lv[i] = 0;
		score = 0;
	};
	~XHConfVo(){};

public:
	int8 type;
	int8 color;
	std::string name;
	int8 effecttype;
	float lv[10];
	int32 score;
};
