#pragma once
#include "BaseType.h"

class XHTipsInfoVo
{
public:
	XHTipsInfoVo()
	{
		color = 0;
		name = "";
		curlv = 0;
		curExp = 0;
		effecttype = 0;
		effectval = 0.0f;
	};
	~XHTipsInfoVo(){};

public:
	int8 color;
	std::string name;
	int curlv;
	int curExp;
	int8 effecttype;
	float effectval;
};
