#pragma once
#include "BaseType.h"

class XHExpConfVo
{
public:
	XHExpConfVo()
	{
		color = 0;
		for (int i =0; i < 10; i++)
			lv[i] = 0;

	};
	~XHExpConfVo(){};

public:
	int8 color;
	int lv[10];
};
