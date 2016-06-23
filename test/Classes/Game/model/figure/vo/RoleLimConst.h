#ifndef HLQS_RoleLimConst_H_
#define HLQS_RoleLimConst_H_

class RoleLimConst
{
public:
	RoleLimConst();
	static int IsOk(int lv)
	{
		if(lv == 50)
		{
			return 1077;
		}
		else if(lv == 65)
		{
			return 1085;
		}	
		else if(lv == 80)
		{
			return 1091;
		}
		else if(lv == 95)
		{
			return 1098;
		}
		else if(lv == 100)
		{
			return 1105;
		}
		else if(lv == 110)
		{
			return 1108;
		}
		else return 0;
	}
};

#endif