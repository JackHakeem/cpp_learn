#pragma once

#include "BaseType.h"

class ChangeQuality
{
public:
	static int getQuality(std::string key)
	{
		if ("3_101" == key)
			return 4;
		else if ("3_102" == key)
			return 3;
		else if ("2_101" == key)
			return 6;
		else if ("2_102" == key)
			return 4;
		else 
			return 0;
	}
};
