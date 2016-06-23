#ifndef HLQS_LvSpiritVo_H_
#define HLQS_LvSpiritVo_H_

class LvSpiritVo
{
public:
	int id;
	int lev;
	int type;
	int nowExp;
	int needExp;
	std::string tips;
	
public:
	LvSpiritVo()
	{
		id = 0;
		lev = 0;
		type = 0;
		nowExp = 0;
		needExp = 0;
	}
};

#endif