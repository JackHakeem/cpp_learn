#ifndef HLQS_WashVo_H_
#define HLQS_WashVo_H_

class WashVo
{
public:
	int strength;
	int intellect;
	int stamina;

public:
	WashVo()
	{
		strength = 0;
		intellect = 0;
		stamina = 0;
	}

	std::string getName(int type)
	{
		switch(type)
		{
		case 1:
			return "tige";
			break;
		case 2:
			return "wanli";
			break;
		case 3:
			return "zhili";
			break;
		default:
			break;
		}
        return "";
	}
};

#endif