#pragma once

class ChangeSmallType
{
public:
	static int smallType(int key)
	{
		int smallType = 0;
		switch(key)
		{
			case 1:
				smallType = 1;
				break;
			case 2:
				smallType = 2;
				break;
			case 3:
				smallType = 3;
				break;
			case 4:
				smallType = 5;
				break;
			case 6:
				smallType = 4;
				break;
			case 7:
				smallType = 6;
				break;
		}
		return smallType;
	}
};