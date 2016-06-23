#ifndef HLQS_LevelExpManage_H_
#define HLQS_LevelExpManage_H_

#include "utils/Singleton.h"
#include "model/figure/vo/LevelExpVo.h"
#include "cocos2d.h"

class LevelExpManage: public Singleton<LevelExpManage>
{
public:
	std::map<int, LevelExpVo> _expDic;
public:
	LevelExpManage();
	void setLevelExpDic(std::map<int, LevelExpVo>& arr);
	LevelExpVo* getLevelExp(int lev);
	int getLevByExp(int exp);
};

#endif