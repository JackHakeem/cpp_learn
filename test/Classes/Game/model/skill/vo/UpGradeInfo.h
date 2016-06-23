#ifndef HLQS_UpGradeInfo_H_
#define HLQS_UpGradeInfo_H_

#include "BaseType.h"

class SUBSKILLTIPS
{
public:
	SUBSKILLTIPS()
	{
		name = "";
		color_name = cocos2d::ccc3(255,255,255);
		rank = 0;
		lev = 0;
		needLevel = 0;
		icon = 0;
		desc = "";
		style = 0;
	}

	~SUBSKILLTIPS()
	{
	}
	std::string			name;
	cocos2d::ccColor3B  color_name;
	int32 rank;
	int32 lev;
	int32 needLevel;
	int32 icon;
	std::string desc;
	int32 style;
};

class UpGradeInfo
{
public:
	int id;
	int lev;
	bool active;
	std::string name;
	int rank;
	int icon;
	std::string desc;
	int cdTime;
	int needLevel;
	int skillExp;
	SUBSKILLTIPS* subTips;

public:
	UpGradeInfo()
	{
		id = 0;
		lev = 0;
		active = false;
		rank = 0;
		icon = 0;
		cdTime = 0;
		needLevel = 0;
		skillExp = 0;
		subTips = 0;
	}
	~UpGradeInfo()
	{
		CC_SAFE_DELETE( subTips );
	}
};

#endif