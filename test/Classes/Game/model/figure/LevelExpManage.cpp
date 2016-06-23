#include "model/figure/LevelExpManage.h"
#include "../player/FigureBaseManage.h"

LevelExpManage::LevelExpManage()
{
}

void LevelExpManage::setLevelExpDic(std::map<int, LevelExpVo>& arr)
{
	_expDic = arr;
	FigureBaseManage::Instance()->resetCfgMercList();
}

LevelExpVo* LevelExpManage::getLevelExp(int lev)
{
	std::map<int, LevelExpVo>::iterator iter = _expDic.find(lev);
	if(iter == _expDic.end())
		return NULL;

	return &(iter->second);
}

int LevelExpManage::getLevByExp(int exp)
{
	int lev = 1;
	std::map<int, LevelExpVo>::iterator iter = _expDic.begin();
	for(; iter != _expDic.end(); ++iter)
	{
		if(iter->second.countExp <= exp)
		{
			lev = (iter->first) > lev ? (iter->first) :lev;
		}
	}
	return lev;
}