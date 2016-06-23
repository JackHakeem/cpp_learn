#pragma once

#include "BaseType.h"

class RequestAddInVo
{
public:
	RequestAddInVo()
	{
		ID = 0;
		name = "";
		hiredID = 0;
		mainLev = 0;
	}

	int32 ID;
	std::string name;
	int32 hiredID;
	int32 mainLev;
};